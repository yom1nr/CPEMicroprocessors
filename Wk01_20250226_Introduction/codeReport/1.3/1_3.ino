int leds[] = {23, 22, 21, 19}; 

int pushButton = 15;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(pushButton, INPUT_PULLUP);
}

void loop() {
  int state = digitalRead(pushButton);

  if (state == LOW) { 
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], HIGH);
    }
  } 
  else {
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], LOW);
    }
  }
}