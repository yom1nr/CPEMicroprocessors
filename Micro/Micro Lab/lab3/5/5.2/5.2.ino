#include "LedController.hpp"
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "DHTesp.h"

const char* ssid = "Tucklyz p";
const char* password = "pond17399";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

#define Pin_DIN 19 // D19 
#define Pin_CS 18 // D18 
#define Pin_CLK 5 // D5 
#define Pin_DHT22 4 // D4 
DHTesp dht;
LedController<1, 1> lc;

void setup() {
  Serial.begin(115200);
  lc = LedController<1, 1>(Pin_DIN, Pin_CLK, Pin_CS);
  lc.setIntensity(8);
  lc.clearMatrix();
  dht.setup(Pin_DHT22, DHTesp::DHT22);

  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED )
  { delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();
  timeClient.setTimeOffset(25200); // +7Hour = (7H x 60Min x 60Sec = 25200 Sec)
  Serial.println();
}
String LEDTIME;
void loop() {
  timeClient.update();
  Serial.print("Time -> "); Serial.print(timeClient.getEpochTime());
  Serial.print(" -> "); Serial.println(timeClient.getFormattedTime());
  LEDTIME = timeClient.getFormattedTime();
  Serial.println(LEDTIME);
  String set =  LEDTIME.substring(6, 8);
  int seconds = set.toInt();
  // int num = (int)set[2];
  Serial.println(seconds);
  float t = dht.getTemperature();
  int Tempp2 = (int)t / 10;
  int Tempp1 = (int)t % 10;
  int Tempp0 = (int)(t * 10) % 10;
  int Tempp = (int)(t * 100) % 10;
  Serial.print("Temperature: "); Serial.print(t); Serial.print(" *C\t");

  if (seconds >= 5 && seconds <= 11) {
    lc.setRow(0, 7, B00000000);
    lc.setRow(0, 6, B00000000);
    lc.setDigit(0, 5, Tempp2, false);
    lc.setDigit(0, 4, Tempp1, true);
    lc.setDigit(0, 3, Tempp0, false);
    lc.setDigit(0, 2, Tempp, false);
    lc.setRow(0, 1, B00000000);
    lc.setRow(0, 0, B00001101);
    delay(1000);
  } else {
    lc.setDigit(0, 7, LEDTIME.charAt(0), false);
    lc.setDigit(0, 6, LEDTIME.charAt(1), false);
    lc.setRow(0, 5, 0B00000001);
    lc.setDigit(0, 4, LEDTIME.charAt(3), false);
    lc.setDigit(0, 3, LEDTIME.charAt(4), false);
    lc.setRow(0, 2, 0B00000001);
    lc.setDigit(0, 1, LEDTIME.charAt(6), false);
    lc.setDigit(0, 0, LEDTIME.charAt(7), false);
    delay(1000);
  }
  lc.clearMatrix();
}
