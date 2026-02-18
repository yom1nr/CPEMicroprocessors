int pushA = 4;
int mypin[] = {23, 22, 21, 19, 18, 5, 17, 16};
int count = 0;
int led = 0;
void setup() {
  Serial.begin(115200);
  pinMode(pushA, INPUT_PULLUP);
  for (int i = 0 ; i < 8 ; i++){
    pinMode(mypin[i], OUTPUT);
    digitalWrite(mypin[i], HIGH);
  }
}
void loop() {
  int bSA = digitalRead(pushA);
  if(bSA == LOW && count%4 == 0){
    while(digitalRead(pushA) == LOW) delay(100);
    while(digitalRead(pushA) == HIGH){
      while(true){
        if(digitalRead(pushA) == LOW) break;
        digitalWrite(mypin[led], LOW);
        delay(100);
        digitalWrite(mypin[led], HIGH);
        led++;
        if(led == 8) led = 0;
      }
    }
    count++;
  }else if(bSA == LOW && count%4 == 1){
    while(digitalRead(pushA) == LOW) delay(100);
    while(digitalRead(pushA) == HIGH){
        if(digitalRead(pushA) == LOW) break;
        digitalWrite(mypin[led], LOW);
    }
    count++;
  }else if(bSA == LOW && count%4 == 2){
    while(digitalRead(pushA) == LOW) delay(100);
    while(digitalRead(pushA) == HIGH){
      while(true){
        if(digitalRead(pushA) == LOW) break;
        digitalWrite(mypin[led], LOW);
        delay(100);
        digitalWrite(mypin[led], HIGH);
        led--;
        if(led == -1) led = 7;
      }
    }
    count++;
  }else if(bSA == LOW && count%4 == 3){
    while(digitalRead(pushA) == LOW) delay(100);
    while(digitalRead(pushA) == HIGH){
        if(digitalRead(pushA) == LOW) break;
        digitalWrite(mypin[led], LOW);
      }
      count++;
    }
    
}
