#define ON LOW
#define OFF HIGH
#define TIME 500
uint8_t led[] = {22,18,23,5,21,4,19,15};

void setup() {
  Serial.begin(115200);
  for (uint8_t i = 0;i<8;i++){
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }
  
}

void loop() {
  left_right();
  for (uint8_t i = 0;i<8;i++){
    digitalWrite(led[i], LOW);
  }
}
void left_right(){
  for (int i = 0;i<8;i++){
    digitalWrite(led[i], ON);
    delay(TIME);
    digitalWrite(led[i], OFF);
    delay(TIME);
    
    
  }
}
