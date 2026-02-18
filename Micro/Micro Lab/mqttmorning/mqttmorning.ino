#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"
#include <TM1638plus.h>

// Pin definitions for TM1638
#define STROBE_TM 19
#define CLOCK_TM 18
#define DIO_TM 5
bool high_freq = true;
TM1638plus tm(STROBE_TM, CLOCK_TM, DIO_TM, high_freq);

#define pinDHT22 17
DHTesp dht;
const char* ssid = "IPLEUM";
const char* password = "qqaasszz";
const char* mqtt_server = "broker.emqx.io";
const char *topic = "CH";
const char* myTopic = "CH";
const int mqtt_port = 1883;

#define LedPin1 15
#define LedPin2 13

#define MSG_BUFFER_SIZE (100)
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];
int value = 0;

uint8_t buttons, stsLED = 00;
uint8_t SegValue[] = {1, 2, 3, 4, 6, 7, 8, 9};

void setup_wifi() {
  delay(10);
  Serial.print("/nConnecting to "); Serial.println(ssid);
  WiFi.mode(WIFI_STA); WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println(""); Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32 Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(myTopic);
      client.publish(myTopic, "LET'S GO BRATHER");
      Serial.println("Connected");
      client.subscribe("SOD");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");

  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  Serial.println(msg);

  if (msg == "1") {
    digitalWrite(LedPin1, HIGH); // เปิด LED
    Serial.println("LED is ON");
  } else if (msg == "0") {
    digitalWrite(LedPin1, LOW); // ปิด LED
    Serial.println("LED is OFF");
  }
  if (msg == "2") {
    digitalWrite(LedPin2, HIGH); // เปิด LED
    Serial.println("LED is ON");
  } else if (msg == "3") {
    digitalWrite(LedPin2, LOW); // ปิด LED
    Serial.println("LED is OFF");
  }
}

void showSeg() {
  for (uint8_t i = 0; i < 8; i++) {
    tm.displayHex(i, SegValue[i]);
  }
}

void showLED(uint8_t value) {
  for (uint8_t i = 0; i < 8; i++) {
    tm.setLED(i, value & 1);
    value = value >> 1;
  }
}

String getSegValues(uint8_t start, uint8_t end) {
  String value = "";
  for (uint8_t i = start; i <= end; i++) {
    value += String(SegValue[i]);
  }
  return value;
}

void setup() {
  Serial.begin(115200);
  pinMode(LedPin1, OUTPUT);
  pinMode(LedPin2, OUTPUT);
  dht.setup(pinDHT22, DHTesp::DHT22);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  while (!client.connected()) {
    reconnect();
  }

  client.publish("SOD", "ON");
  client.subscribe("SOD");

  // Initialize TM1638
  tm.displayBegin();
  showLED(stsLED);
  showSeg();
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();
    String leftSeg = getSegValues(0, 3);
    String rightSeg = getSegValues(4, 7);
    snprintf(msg, MSG_BUFFER_SIZE, "Tempp = %0.2f, Humid = %0.2f, Left Segments = %s, Right Segments = %s", temperature, humidity, leftSeg.c_str(), rightSeg.c_str());
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(myTopic, msg);
    lastMsg = millis();
  }

  buttons = tm.readButtons();
  Serial.println(buttons, HEX);
  for (uint8_t k = 0; k < 8; k++) {
    if ((buttons >> k) & 1) {
      SegValue[k] = (SegValue[k] >= 9) ? 0 : SegValue[k] + 1;
      stsLED = stsLED ^ (1 << k);
      showLED(stsLED);
      showSeg();
      while ((buttons >> k) & 1) {
        buttons = tm.readButtons();
        delay(50);
      }
    }
  }
  delay(100);
}
