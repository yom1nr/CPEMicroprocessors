#include <HardwareSerial.h>

HardwareSerial SerialPort(2);

int mySW[] = {15, 4, 5, 18, 19, 21, 22, 23};


void setup() {
  // put your setup code here, to run once:
  SerialPort.begin(19200, SERIAL_8N1, 16, 17);
  Serial.begin(19200);

  for (int i = 0 ; i < 8 ; i++){
    pinMode(mySW[i], INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(mySW[0]) == 0 ){
    SerialPort.print(49);
    Serial.print(49);
  }
  if(digitalRead(mySW[1]) == 0 ){
    SerialPort.print(50);
    Serial.print(50);
  }
  if(digitalRead(mySW[2]) == 0 ){
    SerialPort.print(51);
    Serial.print(51);
  }
  if(digitalRead(mySW[3]) == 0 ){
    SerialPort.print(52);
    Serial.print(52);
  }
  if(digitalRead(mySW[4]) == 0 ){
    SerialPort.print(53);
    Serial.print(53);
  }
  if(digitalRead(mySW[5]) == 0 ){
    SerialPort.print(54);
    Serial.print(54);
  }
  if(digitalRead(mySW[6]) == 0 ){
    SerialPort.print(55);
    Serial.print(55);
  }
  if(digitalRead(mySW[7]) == 0 ){
    SerialPort.print(56);
    Serial.print(56);
  }
  delay(150);
}
