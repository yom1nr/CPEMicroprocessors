#include "LedController.hpp"
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "DHTesp.h"


const char* ssid = "GS_home stay";
const char* password = "657657657";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

#define Pin_DIN 21 
#define Pin_CS 19 
#define Pin_CLK 18 
#define Pin_DHT22 4 
DHTesp dht;
LedController<1, 1> lc;

void setup() {
  Serial.begin(115200);
  lc = LedController<1, 1>(Pin_DIN, Pin_CLK, Pin_CS);
  lc.setIntensity(8);
  lc.clearMatrix();
  dht.setup(Pin_DHT22, DHTesp::DHT22);

  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  timeClient.begin();
  timeClient.setTimeOffset(25200); 
}

void loop() {
  timeClient.update();
  String LEDTIME = timeClient.getFormattedTime();
  int seconds = timeClient.getSeconds(); // ดึงค่าวินาที

  float t_celsius = dht.getTemperature();
  float f = dht.toFahrenheit(t_celsius); 
  float h = dht.getHumidity();          

  lc.clearMatrix();

  // --- เงื่อนไขตามวินาทีที่คุณกำหนด ---

  // 1. วินาทีเป็น 5, 6, 7, 8, 9 แสดงอุณหภูมิฟาเรนไฮต์ (เช่น 12.34 F)
  if (seconds >= 5 && seconds <= 9) {
    int f_int = (int)f;
    int f_dec = (int)(f * 100) % 100;

    lc.setDigit(0, 5, f_int / 10, false);
    lc.setDigit(0, 4, f_int % 10, true);   // จุดทศนิยม
    lc.setDigit(0, 3, f_dec / 10, false);
    lc.setDigit(0, 2, f_dec % 10, false);
    lc.setRow(0, 0, B01110001);            // ตัว 'F'
    
    Serial.print("Displaying Temp (F): "); Serial.println(f);
  } 
  // 2. วินาทีเป็น 35, 36, 37, 38, 39 แสดงความชื้น (เช่น 56.78 H)
  else if (seconds >= 35 && seconds <= 39) {
    int h_int = (int)h;
    int h_dec = (int)(h * 100) % 100;

    lc.setDigit(0, 5, h_int / 10, false);
    lc.setDigit(0, 4, h_int % 10, true);   // จุดทศนิยม
    lc.setDigit(0, 3, h_dec / 10, false);
    lc.setDigit(0, 2, h_dec % 10, false);
    lc.setRow(0, 0, B00110111);            // ตัว 'H'
    
    Serial.print("Displaying Humid: "); Serial.println(h);
  }
  // 3. เวลาปกติ
  else {
    lc.setDigit(0, 7, LEDTIME.charAt(0) - '0', false);
    lc.setDigit(0, 6, LEDTIME.charAt(1) - '0', false);
    lc.setRow(0, 5, B00000001); 
    lc.setDigit(0, 4, LEDTIME.charAt(3) - '0', false);
    lc.setDigit(0, 3, LEDTIME.charAt(4) - '0', false);
    lc.setRow(0, 2, B00000001); 
    lc.setDigit(0, 1, LEDTIME.charAt(6) - '0', false);
    lc.setDigit(0, 0, LEDTIME.charAt(7) - '0', false);
  }

  delay(1000); 
}