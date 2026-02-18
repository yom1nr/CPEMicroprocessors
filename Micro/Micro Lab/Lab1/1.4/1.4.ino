int led[] = {23, 22, 21, 19, 18, 5, 17, 16};
int pushButton = 4;

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT_PULLUP);
  for(int i = 0 ; i < 8 ; i++){
     pinMode(led[i], OUTPUT);
     digitalWrite(led[i], HIGH);
  }
  
}

void loop() {
  int buttonState = digitalRead(pushButton);
  if(buttonState == LOW){
    for(int i = 0 ; i < 8 ; i++){
      if(digitalRead(pushButton) == HIGH) break;
      digitalWrite(led[i], LOW);
      delay(100);
      digitalWrite(led[i], HIGH);
    }
  }else{
    for(int i = 7 ; i >= 0 ; i--){
      if(digitalRead(pushButton) == LOW) break;
      digitalWrite(led[i], LOW);
      delay(100);
      digitalWrite(led[i], HIGH);
    }
  }
}
