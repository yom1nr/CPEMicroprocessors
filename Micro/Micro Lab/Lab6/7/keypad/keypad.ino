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
  Serial.print(bSA);
  Serial.print(bSB);
  Serial.print(bSC);
  Serial.print(bSD);
  Serial.print(bSE);
  Serial.print(bSF);
  Serial.print(bSG);
  Serial.println(bSH);
  
}
