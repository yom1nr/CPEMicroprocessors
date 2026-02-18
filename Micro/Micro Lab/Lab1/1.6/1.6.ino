const int brakeSwitch = 4; 
const int numLEDs = 8;
int debounceDelay = 100;
int numFlashes = 0;
int led[] = {23, 22, 21, 19, 18, 5, 17, 16}; 

void setup() {
  pinMode(brakeSwitch, INPUT_PULLUP); 
  for (int i = 0; i < numLEDs; i++) {
    pinMode(led[i], OUTPUT); 
    digitalWrite(led[i], LOW); 
  }
}

void loop() {
  int switchState = digitalRead(brakeSwitch); 
  if(switchState == LOW){
    if(numFlashes < 10){
      for (int j = 0; j < numLEDs; j++) {
        digitalWrite(led[j], LOW);
      }
      delay(100);
      for (int j = 0; j < numLEDs; j++) {
        digitalWrite(led[j], HIGH);
      }
      numFlashes++;
      delay(debounceDelay*numFlashes);
    }else{
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(led[i], LOW); 
      }
    }
  }else {
    numFlashes = 0;
    for(int i = 0 ; i < numLEDs ; i++){
      digitalWrite(led[i], HIGH);
    }
  }
}
