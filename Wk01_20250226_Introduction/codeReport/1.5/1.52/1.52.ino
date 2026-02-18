int leds[] = {12, 13, 5, 18, 19, 21, 22, 23}; 
int sw1 = 15;
int sw2 = 4;
int currentLED = 0;
int direction = 1;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }
  
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(sw1) == LOW) {
    while(digitalRead(sw1) == LOW){
            delay(10);
    }
    direction = 1;
  }
  
  if (digitalRead(sw2) == LOW) {
    while(digitalRead(sw2) == LOW){
      delay(10);
    }
    direction = -1;
  }

  digitalWrite(leds[currentLED], HIGH);
  delay(250);
  digitalWrite(leds[currentLED], LOW);

  currentLED = currentLED + direction;

  if (currentLED > 7) {
    currentLED = 0;
  } 
  else if (currentLED < 0) {
    currentLED = 7;
  }
}