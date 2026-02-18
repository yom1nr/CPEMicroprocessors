int leds[] = {12, 13, 5, 18, 19, 21, 22, 23}; 
int sw1 = 15; 
int mode = -1;
int currentLED = 0;
unsigned long lastRunTime = 0; 

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
  pinMode(sw1, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(sw1) == LOW) {
    delay(20);
    
    if (digitalRead(sw1) == LOW) {
      
      mode++; 
      if (mode > 3) mode = 0;
      
      while(digitalRead(sw1) == LOW) {
        delay(10);
      }
    }
  }

  if (mode == -1) {
  } 
  else if (mode == 1 || mode == 3) {
    digitalWrite(leds[currentLED], HIGH);
  }
  else {
    digitalWrite(leds[currentLED], HIGH);
    if (millis() - lastRunTime > 200) {
      lastRunTime = millis();
      
      digitalWrite(leds[currentLED], LOW);

      if (mode == 0) {
        currentLED++;
        if (currentLED > 7) currentLED = 0;
      } 
      else if (mode == 2) {
        currentLED--;
        if (currentLED < 0) currentLED = 7;
      }

      digitalWrite(leds[currentLED], HIGH);
    }
  }
}