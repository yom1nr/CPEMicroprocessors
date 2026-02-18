#include <HardwareSerial.h>

HardwareSerial SerialPort(2);

int myLED[] = { 15, 4, 5, 18, 19, 21, 22, 23 };

int data[8][8] = {
  { 0, 0, 1, 1, 0, 0, 0, 1 },
  { 0, 0, 1, 1, 0, 0, 1, 0 },
  { 0, 0, 1, 1, 0, 0, 1, 1 },
  { 0, 0, 1, 1, 0, 1, 0, 0 },
  { 0, 0, 1, 1, 0, 1, 0, 1 },
  { 0, 0, 1, 1, 0, 1, 1, 0 },
  { 0, 0, 1, 1, 0, 1, 1, 1 },
  { 0, 0, 1, 1, 1, 0, 0, 0 }
};

void setup() {
  // put your setup code here, to run once:
  SerialPort.begin(19200, SERIAL_8N1, 16, 17);
  Serial.begin(19200);

  for (int i = 0; i < 8; i++) {
    pinMode(myLED[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (SerialPort.available()) {
    int ascii = SerialPort.parseInt();
    if (ascii == 49) {
      Serial.println(49);
      outPut(0);
    }
    if (ascii == 50) {
      Serial.println(50);
      outPut(1);
    }
    if (ascii == 51) {
      Serial.println(51);
      outPut(2);
    }
    if (ascii == 52) {
      Serial.println(52);
      outPut(3);
    }
    if (ascii == 53) {
      Serial.println(53);
      outPut(4);
    }
    if (ascii == 54) {
      Serial.println(54);
      outPut(5);
    }
    if (ascii == 55) {
      Serial.println(55);
      outPut(6);
    }
    if (ascii == 56) {
      Serial.println(56);
      outPut(7);
    }
  }
}

void outPut(int x) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(myLED[i], data[x][i]);
  }
}
