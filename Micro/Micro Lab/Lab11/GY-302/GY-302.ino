#include <Wire.h>
#include <BH1750.h>
BH1750 lightMeter;
#define LED 15

void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test begin"));
}
void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  if(lux<10){
    digitalWrite(LED,HIGH);
  }
  else{
    digitalWrite(LED,LOW);
  }
  delay(1000);
}
