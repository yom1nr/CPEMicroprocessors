#include <Arduino.h>


const int segment_pins[] = {13, 12, 14, 27, 26, 25, 33}; // a, b, c, d, e, f, g


const byte segment_code[] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111, // 9
  B01110111, // A
  B01111100, // B
  B00111001, // C
  B01011110, // D
  B01111001, // E
  B01110001  // F
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segment_pins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 16; i++) {
    displaySegment(segment_code[i]);
    delay(500); 
  }
}

void displaySegment(byte value) {
  for (int i = 0; i < 7; i++) {
    byte bit_value = bitRead(value, i); 
    digitalWrite(segment_pins[i], bit_value); 
  }
}
