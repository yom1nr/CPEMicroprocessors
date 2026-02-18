int leds[] = {12, 13, 5, 18, 19, 21, 22, 23};
int pushButton = 15;

int currentLED = 0; 

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }
  
  pinMode(pushButton, INPUT_PULLUP);
}

void loop() {
  digitalWrite(leds[currentLED], HIGH);
  
  delay(300); 
  
  digitalWrite(leds[currentLED], LOW);

  if (digitalRead(pushButton) == LOW) {
    currentLED++; 
    
    if (currentLED > 7) {
      currentLED = 0;
    }
  } 
  else {
    currentLED--;
    
    if (currentLED < 0) {
      currentLED = 7;
    }
  }
}