int led[] = {23, 22, 21, 19};
int pushButton = 4;

void setup() {
  pinMode(pushButton, INPUT_PULLUP); //กำหนดให้ pushButton เป็นการอินพุทแบบกด
  for(int i = 0 ; i < 4 ; i++){ //กำหนดให้ led ทั้ง 4 pin เป็นเอาท์พุท
     pinMode(led[i], OUTPUT);
     digitalWrite(led[i], HIGH);
  }
}

void loop() {
  int buttonState = digitalRead(pushButton);
  if(buttonState == LOW){
    for(int i = 0 ; i < 4 ; i++){
      digitalWrite(led[i], LOW);
    }
  }else{
    for(int i = 0 ; i < 4 ; i++){
      digitalWrite(led[i], HIGH);
    }
  }
}
