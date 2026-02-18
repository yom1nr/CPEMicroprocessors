#define BLYNK_TEMPLATE_ID "TMPL68BmSPPKa"
#define BLYNK_TEMPLATE_NAME "PP007"
#define BLYNK_AUTH_TOKEN "fvzsENnYmWv3yJD7KQdHwnID7Y1HfXME"

#include "DHTesp.h"
#define Pin_DHT22 15

#define BLYNK_PRINT Serial 
#define LED_22    22 
#define LED_23    23 
#define SWitch_18 18 
 
#include <WiFi.h> 
#include <WiFiClient.h> 
#include <BlynkSimpleEsp32.h> 

DHTesp dht;
char ssid[] = "Tucklyz"; 
char pass[] = "pond17399"; 
 
BlynkTimer timer; 
char sBuffer[60]; 
 
BLYNK_WRITE(V0) { 
  int value = param.asInt(); 
  digitalWrite(LED_22, value); 
} 
 
BLYNK_WRITE(V1) { 
  int value = param.asInt(); 
  digitalWrite(LED_23, value); 
} 

void myTimerEvent() { 
  int value = digitalRead(SWitch_18); 
  float Tempp = dht.getTemperature();
  float Humid = dht.getHumidity();
  Blynk.virtualWrite(V2, value); 
  Blynk.virtualWrite(V3, Tempp); 
  Blynk.virtualWrite(V4, Humid); 
  sprintf(sBuffer, "Data: S=%d, T=%0.2f, H=%0.2f", value, Tempp, Humid); 
  Serial.println(sBuffer); 
} 
 
void setup() { 
  Serial.begin(115200); 
  pinMode(LED_22, OUTPUT); 
  pinMode(LED_23, OUTPUT); 
  pinMode(SWitch_18, INPUT_PULLUP); 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); 
  dht.setup(Pin_DHT22,DHTesp::DHT22);
  timer.setInterval(1000L, myTimerEvent); 
} 
 
void loop() { 
  Blynk.run(); 
  timer.run(); 
} 
