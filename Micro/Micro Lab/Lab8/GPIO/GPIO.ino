#include <Arduino.h>
#include "LedController.hpp"

#define Pin_DIN 19 // D19 
#define Pin_CS 18  // D18 
#define Pin_CLK 5 // D5 

struct Button {
  const uint8_t PIN;
  uint32_t nKeyPresses;
  bool pressed;
};

unsigned long button_time = 0;
unsigned long last_button_time = 0;

Button button1 = {23, 0, false}; // ปุ่มสำหรับการเพิ่มค่า
Button button2 = {22, 0, false}; // ปุ่มสำหรับการลดค่า
LedController<1, 1> lc;
void IRAM_ATTR isr() {
  button_time = millis();
  if (digitalRead(button1.PIN) == LOW && button_time - last_button_time > 250) {
    button1.nKeyPresses++;
    button1.pressed = true;
    last_button_time = button_time;
  }
  if (digitalRead(button2.PIN) == LOW && button_time - last_button_time > 250 && button1.nKeyPresses ) {
    button1.nKeyPresses--;
    button2.pressed = true;
    last_button_time = button_time;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(button1.PIN, INPUT_PULLUP);
  pinMode(button2.PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN, isr, FALLING);
  attachInterrupt(button2.PIN, isr, FALLING);

  lc = LedController<1, 1>(Pin_DIN, Pin_CLK, Pin_CS);
  lc.setIntensity(8);
  lc.clearMatrix();
}

void loop() {
  if (button1.pressed) {
    Serial.printf("Button has been pressed %u times\n", button1.nKeyPresses);
    button1.pressed = false;
  }

  if (button2.pressed) {
    Serial.printf("Button has been pressed %u times\n", button1.nKeyPresses);
    button2.pressed = false;
  }
  Led();
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 60000) {
    Led_ID();
    lastMillis = millis();
    detachInterrupt(button1.PIN);
    detachInterrupt(button2.PIN);
    Serial.println("Interrupts Detached!");
  }
}

void Led(){
  int t = button1.nKeyPresses;
  lc.setRow(0, 7,B01100111);
  lc.setRow(0, 6,B00000101);
  lc.setRow(0, 5,B01001111);
  lc.setRow(0, 4,B11011011);
  lc.setRow(0, 3,B00000000);
  lc.setDigit(0, 2,(t/100)%10, false);
  lc.setDigit(0, 1,(t/10)%10, false);
  lc.setDigit(0, 0,t%10, false);
}

void Led_ID(){
  lc.setRow(0, 7,B00000001);
  lc.setRow(0, 6,B00000001);
  lc.setRow(0, 5,B00000001);
  lc.setRow(0, 4,B00000001);
  lc.setRow(0, 3,B00000001);
  lc.setRow(0, 2,B00000001);
  lc.setRow(0, 1,B00000001);
  lc.setRow(0, 0,B00000001);
}
