#define BLYNK_TEMPLATE_ID "TMPL68BmSPPKa"
#define BLYNK_TEMPLATE_NAME "PP007"
#define BLYNK_AUTH_TOKEN "fvzsENnYmWv3yJD7KQdHwnID7Y1HfXME"
#define BLYNK_PRINT Serial

#include <TM1638plus.h>
#include "DHTesp.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define STROBE_TM 19
#define CLOCK_TM 18
#define DIO_TM 5
#define Pin_DHT22 15
bool high_freq = true;

char ssid[] = "Tucklyz";
char pass[] = "pond17399";

BlynkTimer timer;

DHTesp dht;
TM1638plus tm(STROBE_TM, CLOCK_TM , DIO_TM, high_freq);
uint8_t SegValue[] = {1, 2, 3, 4, 6, 7, 8, 9};
uint8_t buttons, stsLED = 00;

void setup() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.setup(Pin_DHT22,DHTesp::DHT22);
  tm.displayBegin();
  Serial.begin(115200);
  showLED(stsLED);
  showSeg();

  timer.setInterval(20000L, sendToBlynk);
}

void loop() {
  delay(100);
  float h = dht.getHumidity();
  float t = dht.getTemperature();
  Serial.print("Temperature");  Serial.print(t);  Serial.print("*C\t");
  Serial.print("Humidity");  Serial.print(h);  Serial.print("%\n");

  Serial.print("Left 4 Digits: ");
  for (int i = 0; i <= 3; i++) {
    Serial.print(SegValue[i]);
  }
  Serial.print("\tRight 4 Digits: ");
  for (int i = 4; i <= 7; i++) {
    Serial.print(SegValue[i]);
  }
  Serial.println();
  
  buttons = tm.readButtons();
  Serial.println(buttons, HEX);
  for (uint8_t k = 0; k < 8; k++) {
    if ((buttons >> k) & 1) {
      SegValue[k] = (SegValue[k] >= 9) ? 0 : SegValue[k] + 1;
      //stsLED = stsLED ^ (1 << k);
      //showLED(stsLED);
      showSeg();
      while ((buttons >> k) & 1) {
        buttons = tm.readButtons();
        delay(50);
      }
    }
  }


  Blynk.run();
  timer.run();
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

void sendToBlynk() {
  float h = dht.getHumidity();
  float t = dht.getTemperature();
  int leftPart = 0;
  int rightPart = 0;
  for (int i = 0; i < 4; i++) {
    leftPart = leftPart * 10 + SegValue[i];  
  }
  for (int i = 4; i < 8; i++) {
    rightPart = rightPart * 10 + SegValue[i];  
  }
  // ส่งข้อมูลไปที่ Blynk
  Blynk.virtualWrite(V3, t);         
  Blynk.virtualWrite(V4, h);         
  Blynk.virtualWrite(V1, leftPart);  
  Blynk.virtualWrite(V2, rightPart);
}

BLYNK_WRITE(V0) { 
  int value = param.asInt(); 
  tm.setLED(0, value & 1);
  value = value >> 1; 
}
