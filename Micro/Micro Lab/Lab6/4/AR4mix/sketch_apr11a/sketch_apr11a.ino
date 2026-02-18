#define ON LOW
#define OFF HIGH
#define TIME 200

uint8_t led[] = {32,33,25,26,27,14,12,13};
uint8_t led_left[] = {32,33,25,26};
uint8_t led_right[] = {27,14,12,13};

void setup() {
  Serial.begin(115200);
  for (uint8_t i = 0;i<8;i++){
    pinMode(led[i], OUTPUT);
  }
  
  
}

void loop() {
  move_in();
  delay(TIME);
  move_out();
  delay(TIME);
  bb();
  delay(TIME);
}

void move_out(){
  for (int i = 3;i>=0;i--){
    digitalWrite(led_left[i], ON);
    digitalWrite(led_right[3-i], ON);
    delay(TIME);
    digitalWrite(led_left[i], OFF);
    digitalWrite(led_right[3-i], OFF);
    delay(TIME);
  }
}
void move_in(){
  for (int i = 0;i<4;i++){
    digitalWrite(led_left[i], ON);
    digitalWrite(led_right[3-i], ON);
    delay(TIME);
    digitalWrite(led_left[i], OFF);
    digitalWrite(led_right[3-i], OFF);
    delay(TIME);
  }
}

void bb(){
    digitalWrite(led_left[0], ON);
    digitalWrite(led_right[3], ON);
    delay(TIME);
    digitalWrite(led_left[0], OFF);
    digitalWrite(led_right[3], OFF);
    delay(TIME);
}
