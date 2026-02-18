int pushA = 4;
int pushB = 15;
int mypin[] = {23, 22, 21, 19, 18, 5, 17, 16};
void setup() {
  Serial.begin(115200);
  pinMode(pushA, INPUT_PULLUP);
  pinMode(pushB, INPUT_PULLUP);
  for (int i = 0 ; i < 7 ; i++){
    pinMode(mypin[i], OUTPUT);
    digitalWrite(mypin[i], HIGH);
  }
}
void loop() {
  int bSA = digitalRead(pushA);
  int bSB = digitalRead(pushB);
  if(bSA == LOW)
  {
  while(digitalRead(pushA) == LOW) delay(100);
  while(digitalRead(pushB) == HIGH){
  for (int i = 0; i < 8;i++){
    if(digitalRead(pushB) == LOW) break;
    digitalWrite(mypin[i], LOW);
    delay(100);
    digitalWrite(mypin[i], HIGH);
    }
  }
  }
  else if(bSB == LOW){
  while(digitalRead(pushB) == LOW) delay(100);
  while(digitalRead(pushA) == HIGH){
    for (int i = 7; i >= 0;i--){
      if(digitalRead(pushA) == LOW) break;
      digitalWrite(mypin[i], LOW);
      delay(100);
      digitalWrite(mypin[i], HIGH);
      }
    }
  }
  
}
