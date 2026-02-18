#include "DHTesp.h"
#include "LedController.hpp"
#define Pin_DIN 19 
#define Pin_CS 18 
#define Pin_CLK 5
#define Pin_DHT22 15

DHTesp dht;
LedController<1, 1> lc;
void setup() {
  Serial.begin(115200);
  lc = LedController<1, 1> (Pin_DIN, Pin_CLK, Pin_CS);
  lc.setIntensity(8);
  lc.clearMatrix();
  dht.setup(Pin_DHT22,DHTesp::DHT22);
}

void loop() {
  float h = dht.getHumidity();
  float t = dht.getTemperature();
  Serial.print("Temperature: "); Serial.print(t); Serial.print(" *C\t");
  Serial.print("Humidity: "); Serial.print(h); Serial.print(" %\n");
  int tp = (int)(t * 10); int hd = (int)(h * 10);
  int Tempp2 = tp/100; int Tempp1 = (tp/10)%10; int Tempp0 = tp%10;
  int Humi2 = hd/100; int Humi1 = (hd/10)%10; int Humi0 = hd%10;
  lc.setDigit(0, 7, Tempp2, false);
  lc.setDigit(0, 6, Tempp1, true);
  lc.setDigit(0, 5, Tempp0, false);
  lc.setRow(0, 4, B00001101); 
  lc.setDigit(0, 3, Humi2, false);
  lc.setDigit(0, 2, Humi1, true);
  lc.setDigit(0, 1, Humi0, false);
  lc.setRow(0, 0, B00010111); 
  delay(2000);
}
