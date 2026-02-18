int led = 2; //กำหนดให้ led เป็น pin2;

void setup() { 
  pinMode(led, OUTPUT); //กำหนดสถานะ led(pin2) เป็น Output
}

void loop() {
  digitalWrite(led, HIGH); //กำหนดให้ led ติด
  delay(100); //ดีเลย์ 100 มิลลิวินาที หรือ 0.1 วินาที
  digitalWrite(led, LOW); //กำหนดให้ led ดับ
  delay(100);
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(1000); //ดีเลย์ 1000 มิลลิวินาที หรือ 1 วินาที
}
