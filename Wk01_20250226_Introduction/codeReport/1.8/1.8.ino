int leds[] = {12, 13, 5, 18, 19, 21, 22, 23}; 
int sw1 = 15; 

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(sw1, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(sw1) == LOW) {
    
    int waitTime = 20; 

    for (int i = 0; i < 10; i++) {
      
      controlAllLeds(HIGH);
      if (smartDelay(waitTime) == false) return;

      controlAllLeds(LOW);
      if (smartDelay(waitTime) == false) return;

      waitTime = waitTime + 30;
    }

    controlAllLeds(HIGH);
    
    while (digitalRead(sw1) == LOW) {
      delay(10); 
    }
  } 
  
  controlAllLeds(LOW);
}

void controlAllLeds(int state) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(leds[i], state);
  }
}

bool smartDelay(int ms) {
  for (int i = 0; i < ms; i += 10) { 
    if (digitalRead(sw1) == HIGH) {
      return false;
    }
    delay(10);
  }
  return true; 
}