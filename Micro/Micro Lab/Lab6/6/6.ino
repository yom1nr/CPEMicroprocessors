#include <Arduino.h>

// Define pin connections for 7-segment display
#define SEG_A 13
#define SEG_B 12
#define SEG_C 14
#define SEG_D 27
#define SEG_E 26
#define SEG_F 25
#define SEG_G 33
#define SEG_DP 32

// Define pin connections for switches
#define SWITCH_PLUS_TWO 23
#define SWITCH_PLUS_ONE 22
#define SWITCH_MINUS_ONE 21
#define SWITCH_MINUS_TWO 19

int count = 5; // Initial value of count

void setup() {
  // Initialize 7-segment display pins as outputs
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(SEG_DP, OUTPUT);

  // Initialize switch pins as inputs with pull-up resistors
  pinMode(SWITCH_PLUS_TWO, INPUT_PULLUP);
  pinMode(SWITCH_PLUS_ONE, INPUT_PULLUP);
  pinMode(SWITCH_MINUS_ONE, INPUT_PULLUP);
  pinMode(SWITCH_MINUS_TWO, INPUT_PULLUP);

  // Initialize serial communication
  Serial.begin(9600);

  // Display initial count value on 7-segment display
  displayCount(count);
}

void loop() {
  // Check if switch to increment count by two is pressed
    if (count>=9) {
      count=9;
      displayCount(count);
  }
  if (count<=0) {
      count=0;
      displayCount(count);
  }
  if (digitalRead(SWITCH_PLUS_TWO) == LOW) {
    delay(50); // Debounce delay
    count += 2;
    displayCount(count);
  }

  // Check if switch to increment count by one is pressed
  if (digitalRead(SWITCH_PLUS_ONE) == LOW) {
    delay(50); // Debounce delay
    count+=1;
    displayCount(count);
  }

  // Check if switch to decrement count by one is pressed
  if (digitalRead(SWITCH_MINUS_ONE) == LOW) {
    delay(50); // Debounce delay
    count-=1;
    displayCount(count);
  }

  // Check if switch to decrement count by two is pressed

  if (digitalRead(SWITCH_MINUS_TWO) == LOW) {
    delay(50); // Debounce delay
    count -= 2;
    displayCount(count);
  }

  // Display current count on Serial Monitor
  Serial.print("Count: ");
  Serial.println(count);
}

void displayCount(int num) {
  switch (num) {
    case 0:
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, HIGH);
      digitalWrite(SEG_F, HIGH);
      digitalWrite(SEG_G, LOW);
      digitalWrite(SEG_DP, LOW);
      break;
    case 1:
      digitalWrite(SEG_A, LOW);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, LOW);
      digitalWrite(SEG_E, LOW);
      digitalWrite(SEG_F, LOW);
      digitalWrite(SEG_G, LOW);
      digitalWrite(SEG_DP, LOW);
      break;
    case 2:
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, LOW);
      digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, HIGH);
      digitalWrite(SEG_F, LOW);
      digitalWrite(SEG_G, HIGH);
      digitalWrite(SEG_DP, LOW);
      break;
    case 3:
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, LOW);
      digitalWrite(SEG_F, LOW);
      digitalWrite(SEG_G, HIGH);
      digitalWrite(SEG_DP, LOW);
      break;
    case 4:
      digitalWrite(SEG_A, LOW);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, LOW);
      digitalWrite(SEG_E, LOW);
      digitalWrite(SEG_F, HIGH);
      digitalWrite(SEG_G, HIGH);
      digitalWrite(SEG_DP, LOW);
      break;
    case 5:
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, LOW);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, LOW);
      digitalWrite(SEG_F, HIGH);
      digitalWrite(SEG_G, HIGH);
      digitalWrite(SEG_DP, LOW);
      break;
    case 6:
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, LOW);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, HIGH);
      digitalWrite(SEG_F, HIGH);
      digitalWrite(SEG_G, HIGH);
      digitalWrite(SEG_DP, LOW);
      break;
    case 7:
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, LOW);
      digitalWrite(SEG_E, LOW);
      digitalWrite(SEG_F, LOW);
      digitalWrite(SEG_G, LOW);
      digitalWrite(SEG_DP, LOW);
      break;
    case 8:
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, HIGH);
      digitalWrite(SEG_F, HIGH);
      digitalWrite(SEG_G, HIGH);
      digitalWrite(SEG_DP, LOW);
      break;
    case 9:
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, LOW);
      digitalWrite(SEG_E, LOW);
      digitalWrite(SEG_F, HIGH);
      digitalWrite(SEG_G, HIGH);
      digitalWrite(SEG_DP, LOW);
      break;
  }
}
