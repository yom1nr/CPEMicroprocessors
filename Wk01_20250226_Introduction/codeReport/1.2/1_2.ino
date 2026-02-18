int led[] = {23, 22, 21, 19};
void setup() {
  for(int i = 0 ; i < 4 ; i++){
     pinMode(led[i], OUTPUT);
     digitalWrite(led[i], HIGH);
  }
}

void loop() {
  for(int i = 0 ; i < 4 ; i++){
    digitalWrite(led[i], LOW);
    delay(500);
    digitalWrite(led[i], HIGH);
  }
}
