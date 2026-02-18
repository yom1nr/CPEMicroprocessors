#if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#define DEVICE "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#define DEVICE "ESP8266"
#endif

// DHT
#include "DHTesp.h"
#define Pin_DHT22 18
DHTesp dht;

// Light sensor
#include <Wire.h>
#include <BH1750.h>
// int LED = 15;
BH1750 lightMeter;

// Rotary
#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"
#define ROTARY_ENCODER_A_PIN 16
#define ROTARY_ENCODER_B_PIN 17
#define ROTARY_ENCODER_BUTTON_PIN 5
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

// WiFi AP SSID
#define WIFI_SSID "Tucklyz"
// WiFi password
#define WIFI_PASSWORD "pond17399"

  #define INFLUXDB_URL "https://us-east-1-1.aws.cloud2.influxdata.com"
  #define INFLUXDB_TOKEN "tXDIwqplkOZCXrMUJb8Dej1SnYImGcCti1Bzm9qMKz9-A3IUdnacY03EGuCD6W8dnn9N9-TceokUcRhiJkfohQ=="
  #define INFLUXDB_ORG "DEV"
  #define INFLUXDB_BUCKET "PP"

// Set timezone string according to https://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
// Examples:
//  Pacific Time: "PST8PDT"
//  Eastern: "EST5EDT"
//  Japanesse: "JST-9"
//  Central Europe: "CET-1CEST,M3.5.0,M10.5.0/3"
#define TZ_INFO "WET0WEST,M3.5.0/1,M10.5.0"

// InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
// InfluxDB client instance without preconfigured InfluxCloud certificate for insecure connection
//InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);

// Data point
Point sensor("wifi_status");

void IRAM_ATTR readEncoderISR() {
  rotaryEncoder.readEncoder_ISR();
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  // Setup DHT
  dht.setup(Pin_DHT22, DHTesp::DHT22);

  // Setup Rotary
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  bool circleValues = false;
  rotaryEncoder.setBoundaries(0, 1000, circleValues);
  rotaryEncoder.setAcceleration(250);

  // Setup Light sensor
  // pinMode(LED, OUTPUT);
  Wire.begin();
  lightMeter.begin();

  // Setup wifi
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to wifi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();

  // Add tags
  sensor.addTag("device", DEVICE);
  sensor.addTag("SSID", WiFi.SSID());

  // Alternatively, set insecure connection to skip server certificate validation
  //client.setInsecure();

  // Accurate time is necessary for certificate validation and writing in batches
  // For the fastest time sync find NTP servers in your area: https://www.pool.ntp.org/zone/
  // Syncing progress and the time will be printed to Serial.
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Check server connection
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}

float Rotary_Angle;
void loop() {

  // float DHT22_Tempp = random(1000, 3000) / 100.0;
  // float DHT22_Humid = random(4000, 6000) / 100.0;
  // float GY_302 = random(7000, 9000) / 100.0;
  // float Rotary_Angle = random(10000, 11000) / 100.0;

  float DHT22_Humid = dht.getHumidity();
  float DHT22_Tempp = dht.getTemperature();
  float GY_302 = lightMeter.readLightLevel();

  if (rotaryEncoder.encoderChanged()) {
    Rotary_Angle = rotaryEncoder.readEncoder();
  }
  if (rotaryEncoder.isEncoderButtonClicked()) {
    rotary_onButtonClick();
  }
  
  Serial.println(DHT22_Tempp);
  Serial.println(DHT22_Humid);
  Serial.println(GY_302);
  Serial.println(Rotary_Angle);
  
  // Store measured value into point
  sensor.clearFields();
  // Report RSSI of currently connected network
  sensor.addField("DHT22_Tempp", DHT22_Tempp);
  sensor.addField("DHT22_Humid", DHT22_Humid);
  sensor.addField("GY_302", GY_302);
  sensor.addField("Rotary_Angle", Rotary_Angle);

  // Print what are we exactly writing
  Serial.print("Writing: ");
  Serial.println(client.pointToLineProtocol(sensor));
  // If no Wifi signal, try to reconnect it
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi connection lost");
  }
  // Write point
  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  delay(30);
}

void rotary_onButtonClick() {
  static unsigned long lastTimePressed = 0;  // Soft debouncing
  if (millis() - lastTimePressed < 500) {
    return;
  }
  lastTimePressed = millis();
  Serial.print("button pressed ");
  Serial.print(millis());
  Serial.println(" milliseconds after restart");
}

void rotary_loop() {
  //dont print anything unless value changed
  if (rotaryEncoder.encoderChanged()) {
    Rotary_Angle = rotaryEncoder.readEncoder();
  }
  if (rotaryEncoder.isEncoderButtonClicked()) {
    rotary_onButtonClick();
  }
}
