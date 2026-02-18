int pushA = 16;
int pushB = 4;
int pushC = 15;
int pushD = 13;
int pushE = 12;
int pushF = 14;
int pushG = 27;
int pushH = 26;
int mypin[] = {23, 22, 21, 19, 18, 5, 17};
void setup() {
  Serial.begin(115200);
  pinMode(pushA, INPUT_PULLUP);
  pinMode(pushB, INPUT_PULLUP);
  pinMode(pushC, INPUT_PULLUP);
  pinMode(pushD, INPUT_PULLUP);
  pinMode(pushE, INPUT_PULLUP);
  pinMode(pushF, INPUT_PULLUP);
  pinMode(pushG, INPUT_PULLUP);
  pinMode(pushH, INPUT_PULLUP);
  for (int i = 0 ; i < 7 ; i++){
    pinMode(mypin[i], OUTPUT);
    digitalWrite(mypin[i], LOW);
  }
}
void loop() {
  int bSA = digitalRead(pushA);
  int bSB = digitalRead(pushB);
  int bSC = digitalRead(pushC);
  int bSD = digitalRead(pushD);
  int bSE = digitalRead(pushE);
  int bSF = digitalRead(pushF);
  int bSG = digitalRead(pushG);
  int bSH = digitalRead(pushH);
  int count = bSA + bSB + bSC + bSD + bSE + bSF + bSG + bSH;
  if(count == 8){
    for (int i = 0; i < 7;i++){
      digitalWrite(mypin[i], LOW);
      if(i == 6){
        digitalWrite(mypin[i], HIGH);
      }
    }
  }
  else if(bSA == LOW && count == 7){
    for (int i = 0; i < 7;i++){
      digitalWrite(mypin[i], HIGH);
      if(i == 6){
        digitalWrite(mypin[i], LOW);
      }
    }
  }
  else if(bSB == LOW && count == 7){
    for (int i = 0; i < 7;i++){
      digitalWrite(mypin[i], LOW);
      if(i == 1 || i == 2 ){
        digitalWrite(mypin[i], HIGH);
      }
    }
  }
   else if(bSC == LOW && count == 7){
    for (int i = 0; i < 7;i++){
      digitalWrite(mypin[i], HIGH);
      if(i == 2 || i == 5){
        digitalWrite(mypin[i], LOW);
      }
    }
  }
  else if(bSD == LOW && count == 7){
    for (int i = 0; i < 7;i++){
      digitalWrite(mypin[i], HIGH);
      if(i == 4 || i == 5 ){
        digitalWrite(mypin[i], LOW);
      }
    }
  }
  else if(bSE == LOW && count == 7){
    for (int i = 0; i < 7;i++){
      digitalWrite(mypin[i], HIGH);
      if(i == 0 || i == 3 || i == 4){
        digitalWrite(mypin[i], LOW);
      }
    }
  }
  else if(bSF == LOW && count == 7){
    for (int i = 0; i < 7;i++){
      digitalWrite(mypin[i], HIGH);
      if(i == 1 || i == 4 ){
        digitalWrite(mypin[i], LOW);
      }
    }
  }
  else if(bSG == LOW && count == 7){
    for (int i = 0; i < 7;i++){
      digitalWrite(mypin[i], HIGH);
      if(i == 1){
        digitalWrite(mypin[i], LOW);
      }
    }
  }
  else if(bSH == LOW && count == 7){
    for (int i = 0; i < 7;i++){
      digitalWrite(mypin[i], LOW);
      if(i == 0 || i == 1 || i == 2){
        digitalWrite(mypin[i], HIGH);
      }
    }
  }
  else if(count < 7){
    for (int i = 0; i < 7;i++){
      digitalWrite(mypin[i], HIGH);
      if(i == 1 || i == 2){
        digitalWrite(mypin[i], LOW);
      }
    }
  }
}
