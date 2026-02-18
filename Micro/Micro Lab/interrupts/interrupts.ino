#include "LedController.hpp"
#define Pin_DIN 18
#define Pin_CS 19
#define Pin_CLK 21
#define Inc_Pin 23 // +
#define Dec_Pin 22 // -
LedController<1, 1> lc;
volatile int counter = 0;
int myCounter = 0;
int lastCOunter = 99;
unsigned long sw1_time = 0;
unsigned long last_sw1_time = 0;
unsigned long sw2_time = 0;
unsigned long last_sw2_time = 0;

void IRAM_ATTR Inc() {
  sw1_time = millis();
  if (sw1_time - last_sw1_time > 150) {
    myCounter++;
    last_sw1_time = sw1_time;
  }
}

void IRAM_ATTR Dec() {
  sw2_time = millis();
  if (sw2_time - last_sw2_time > 150) {
    myCounter--;
    last_sw2_time = sw2_time;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Monitoring interrupts: ");
  pinMode(Inc_Pin, INPUT_PULLUP);
  pinMode(Dec_Pin, INPUT_PULLUP);
  lc = LedController<1, 1>(Pin_DIN, Pin_CLK, Pin_CS);
  lc.setIntensity(8);
  lc.clearMatrix();
  attachInterrupt(Inc_Pin, Inc, FALLING);
  attachInterrupt(Dec_Pin, Dec, FALLING);
}

void loop() {
  if (lastCOunter != myCounter) {
    Serial.print("An interrupt has occurred. Total: ");
    Serial.println(myCounter);
    lastCOunter = myCounter;
  }
  lc.setDigit(0, 0, myCounter, false);
}
