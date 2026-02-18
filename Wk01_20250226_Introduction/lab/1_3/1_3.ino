// กำหนดขา LED 4 ดวงเดิม
int leds[] = {23, 22, 21, 19}; 

// กำหนดขาสวิตช์
int pushButton = 15;

  // ตั้งค่าขา LED เป็น Output
void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(pushButton, INPUT_PULLUP);
}

void loop() {
  // อ่านค่าจากสวิตช์ (กด = 0, ไม่กด = 1)
  int state = digitalRead(pushButton);

    // === ถ้า "กดสวิตช์ไฟลงกราวด์ได้ค่า 0 ===
  if (state == LOW) { 
    // สั่งให้ LED ทุกดวง "ติด"
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], HIGH);
    }
  } 
    // === ถ้า "ไม่กดสวิตช์ค่าเป็น 1 ===
  else {
    // สั่งให้ LED ทุกดวง "ดับ"
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], LOW);
    }
  }
}