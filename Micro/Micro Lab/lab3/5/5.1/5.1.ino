#include "DHTesp.h"
#include "LedController.hpp"
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define Pin_DIN 13 // D19 
#define Pin_CS 12  // D18 
#define Pin_CLK 14 // D5 

DHTesp dht;
LedController<1, 1> lc;
const char* ssid = "Gam";
const char* password = "gam1010467";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup() {
  Serial.begin(115200);

  lc = LedController<1, 1>(Pin_DIN, Pin_CLK, Pin_CS); // <-- This line is causing the error

  lc.setIntensity(8);
  lc.clearMatrix();


  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
  timeClient.setTimeOffset(25200); // +7Hour = (7H x 60Min x 60Sec = 25200 Sec)
}

void loop() {
  timeClient.update();

  Serial.print("Time -> ");
  Serial.print(timeClient.getEpochTime());
  Serial.print(" -> ");
  Serial.println(timeClient.getFormattedTime());

  int hour = timeClient.getHours();
  int minute = timeClient.getMinutes();
  int second = timeClient.getSeconds();

  // Display time on 7-segment display
  lc.setDigit(0, 7, hour / 10, false);
  lc.setDigit(0, 6, hour % 10, false);
  lc.setRow(0, 5, B00000001);
  lc.setDigit(0, 4, minute / 10, false);
  lc.setDigit(0, 3, minute % 10, false);
  lc.setRow(0, 2, B00000001);
  lc.setDigit(0, 1,  second / 10, false);
  lc.setDigit(0, 0, second % 10, false);
  delay(1000); // Update every second
}
