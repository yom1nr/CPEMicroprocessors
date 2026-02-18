#include <WiFi.h>
#include "DHTesp.h"
#define pinDHT22 22
DHTesp dht;
const char* ssid = "Tucklyz p";
const char* password = "pond17399";

int pinTest1 = 15; // Pin for LED 1
int pinTest2 = 23; // Pin for LED 2
int pinTest3 = 4; // Pin for LED 3
int pinTest4 = 16; // Pin for LED 4

String LED1State = "OFF";
String LED2State = "OFF";
String LED3State = "OFF";
String LED4State = "OFF";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println();
  String thisBoard = ARDUINO_BOARD;
  Serial.println(thisBoard);
  dht.setup(pinDHT22, DHTesp::DHT22);
  pinMode(pinTest1, OUTPUT); // set the LED pin mode
  pinMode(pinTest2, OUTPUT); // set the LED pin mode
  pinMode(pinTest3, OUTPUT); // set the LED pin mode
  pinMode(pinTest4, OUTPUT); // set the LED pin mode

  delay(10);
  Serial.print("\n\nConnecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

int value = 0;
bool LED_Status1 = LOW;
bool LED_Status2 = LOW;
bool LED_Status3 = LOW;
bool LED_Status4 = LOW;

void loop() {
  digitalWrite(pinTest1, LED_Status1);
  digitalWrite(pinTest2, LED_Status2);
  digitalWrite(pinTest3, LED_Status3);
  digitalWrite(pinTest4, LED_Status4);
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");

    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<html><body>");
            client.println("<h1>The ESP-32 Update web page without refresh</h1>");
            client.println("<p>");
            client.println("</p>");
            client.println("<a href=\"/ledon1\"><button style=\"background-color: #EC5151;\">LED 1 On</button></a>");
            client.println("<a href=\"/ledon2\"><button style=\"background-color: #EC5151;\">LED 2 On</button></a>");
            client.println("<a href=\"/ledon3\"><button style=\"background-color: #EC5151;\">LED 3 On</button></a>");
            client.println("<a href=\"/ledon4\"><button style=\"background-color: #EC5151;\">LED 4 On</button></a><br>");
            client.println("<br><a href=\"/ledoff1\"><button style=\"background-color: #4075E1;\">LED 1 Off</button></a>");
            client.println("<a href=\"/ledoff2\"><button style=\"background-color: #4075E1;\">LED 2 Off</button></a>");
            client.println("<a href=\"/ledoff3\"><button style=\"background-color: #4075E1;\">LED 3 Off</button></a>");
            client.println("<a href=\"/ledoff4\"><button style=\"background-color: #4075E1;\">LED 4 Off</button></a>");
            client.println("</body></html>");
            client.println("<p>State of [LED1,LED2,LED3,LED4] is >> " + LED1State + ", " + LED2State + ", " + LED3State + ", " + LED4State + "</p>");
            client.println("<p>DHT-22 sensor: Temp = " + String(temperature) + "C , Humidity = " + String(humidity) + "%</p>");
            client.println("</br><a href=\"https://web.facebook.com/pangpond.nattapat.9\">By Nadthapat Phuttruksa</a>");
            client.println("</br><a href=\"https://github.com/Tucklyz\">Click</a>");
   

            break;
          }
          else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /ledon1")) {
          LED_Status1 = HIGH;
          LED1State = "ON";
        }
        if (currentLine.endsWith("GET /ledoff1")) {
          LED_Status1 = LOW;
          LED1State = "OFF";
        }
        if (currentLine.endsWith("GET /ledon2")) {
          LED_Status2 = HIGH;
          LED2State = "ON";
        }
        if (currentLine.endsWith("GET /ledoff2")) {
          LED_Status2 = LOW;
          LED2State = "OFF";
        }
        if (currentLine.endsWith("GET /ledon3")) {
          LED_Status3 = HIGH;
          LED3State = "ON";
        }
        if (currentLine.endsWith("GET /ledoff3")) {
          LED_Status3 = LOW;
          LED3State = "OFF";
        }
        if (currentLine.endsWith("GET /ledon4")) {
          LED_Status4 = HIGH;
          LED4State = "ON";
        }
        if (currentLine.endsWith("GET /ledoff4")) {
          LED_Status4 = LOW;
          LED4State = "OFF";
        }
      }
    }

    client.stop();
    Serial.println("Client Disconnected.");
  }
}
