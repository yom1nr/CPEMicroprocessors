#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "DHTesp.h"
#include "LedController.hpp" // เปลี่ยนเป็น Library มาตรฐาน

// กำหนดขาที่ต่อกับ ESP32
#define DHT_PIN 4
#define DIN_PIN 21 
#define CS_PIN 19  
#define CLK_PIN 18 

const char* ssid = "SUT_IoTs";
const char* password = "MaiMeeJingJing";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
DHTesp dht;

// ใช้ LedControl แบบปกติ (DIN, CLK, CS, จำนวนจอ)
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

void setup() {
  Serial.begin(115200);

  // 1. ตั้งค่าเซนเซอร์ DHT22
  dht.setup(DHT_PIN, DHTesp::DHT22);

  // 2. ตั้งค่าหน้าจอ MAX-7219
  lc.shutdown(0, false);       // เปิดการทำงานหน้าจอ
  lc.setIntensity(0, 8);       // ปรับความสว่าง (0-15)
  lc.clearDisplay(0);          // ล้างหน้าจอ

  // 3. เชื่อมต่อ WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  
  // 4. เริ่มต้น NTP Client (+7 ชั่วโมง = 25200 วินาที)
  timeClient.begin();
  timeClient.setTimeOffset(25200);
}

void loop() {
  timeClient.update(); 

  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();
  int currentSecond = timeClient.getSeconds();

  if (currentSecond >= 5 && currentSecond <= 11) {
    
    float tempC = dht.getTemperature();
    float tempF = (tempC * 1.8) + 32.0; 
    
    Serial.print("Temperature: ");
    Serial.print(tempF);
    Serial.println(" F");
    
    int tempInt = (int)(tempF * 10); 
    int tTens = (tempInt / 100) % 10; 
    int tOnes = (tempInt / 10) % 10;  
    int tDec  = tempInt % 10;         

    lc.clearDisplay(0); // ล้างจอก่อนแสดงอุณหภูมิ
    
    if(tTens > 0) {
       lc.setDigit(0, 5, tTens, false); 
    }
    
    lc.setDigit(0, 4, tOnes, true);  
    lc.setDigit(0, 3, tDec, false);  
    lc.setChar(0, 1, 'F', false); 
    
  } else {
    Serial.print("Time: ");
    Serial.println(timeClient.getFormattedTime());
    
    // แสดงเวลา HH-MM-SS
    lc.setDigit(0, 7, currentHour / 10, false); 
    lc.setDigit(0, 6, currentHour % 10, false); 
    lc.setChar(0, 5, '-', false); 

    lc.setDigit(0, 4, currentMinute / 10, false); 
    lc.setDigit(0, 3, currentMinute % 10, false); 
    lc.setChar(0, 2, '-', false); 

    lc.setDigit(0, 1, currentSecond / 10, false); 
    lc.setDigit(0, 0, currentSecond % 10, false); 
  }

  delay(1000); 
}