#include <Wire.h>
#include <BH1750.h>
#include <TM1638plus.h>

#define  pin_STB 5
#define  pin_CLK 17
#define  pin_DIO 16

BH1750 lightMeter;
TM1638plus tm(pin_STB, pin_CLK , pin_DIO, true);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test begin"));
  tm.displayBegin();
  tm.brightness(6);
}

void loop() {
  float Luxfloat = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(Luxfloat);
  Serial.println(" lx");
  int IntLux = (int)(Luxfloat * 100);
  int IntLux4 = IntLux % 10; IntLux /= 10;
  int IntLux3 = IntLux % 10; IntLux /= 10;
  int IntLux2 = IntLux % 10; IntLux /= 10;
  int IntLux1 = IntLux % 10; IntLux /= 10;
  int IntLux0 = IntLux % 10; IntLux /= 10;
  tm.reset();
  IntLux0 = Luxfloat < 100 ? ' '  - 0x30 : IntLux0;
  IntLux1 = Luxfloat < 10 ? ' ' - 0x30 : IntLux1;
  tm.displayASCII(0, 0x30 + IntLux0);
  tm.displayASCII(1, 0x30 + IntLux1);
  tm.displayASCIIwDot(2, 0x30 + IntLux2);
  tm.displayASCII(3, 0x30 + IntLux3);
  tm.displayASCII(4, 0x30 + IntLux4);
  tm.displayASCII(5, ' ');
  tm.displayASCII(6, 'L');
  tm.displayASCII(7, 'u');
  delay(2000);
}
