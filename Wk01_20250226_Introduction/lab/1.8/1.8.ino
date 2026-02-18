int leds[] = {12, 13, 5, 18, 19, 21, 22, 23}; 
int sw1 = 15; 

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(sw1, INPUT_PULLUP);
}

void loop() {
  // 1. เช็คว่า "กดเบรก" หรือไม่?
  if (digitalRead(sw1) == LOW) {
    
    // กำหนดความเร็วเริ่มต้น (เร็วมาก = 50ms)
    int waitTime = 20; 

    // --- Step 1: กระพริบ 10 ครั้ง (แบบช้าลงเรื่อยๆ) ---
    for (int i = 0; i < 10; i++) {
      
      // สั่งติด
      controlAllLeds(HIGH);
      if (smartDelay(waitTime) == false) return; // ถ้าปล่อยมือ ออกทันที

      // สั่งดับ
      controlAllLeds(LOW);
      if (smartDelay(waitTime) == false) return; // ถ้าปล่อยมือ ออกทันที

      // >>> หัวใจสำคัญ: เพิ่มเวลาหน่วงขึ้นเรื่อยๆ (ยิ่งมาก ยิ่งช้า) <<<
      waitTime = waitTime + 30; // บวกเพิ่มรอบละ 50ms (ปรับเลขนี้ได้ถ้าอยากให้ช้าลงอีก)
    }

    // --- Step 2: เมื่อครบ 10 ครั้ง (ช้าสุดๆ แล้ว) -> ให้ติดค้าง ---
    controlAllLeds(HIGH);
    
    // วนลูปเช็คสถานะกดค้าง (รอปล่อยมือ)
    while (digitalRead(sw1) == LOW) {
      delay(10); 
    }
  } 
  
  // 2. ถ้าปล่อยเบรก -> สั่งดับให้หมด
  controlAllLeds(LOW);
}

// ==========================================
// ฟังก์ชันเสริม: สั่ง LED ทุกดวง
// ==========================================
void controlAllLeds(int state) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(leds[i], state);
  }
}

// ==========================================
// ฟังก์ชันเสริม: หน่วงเวลาแบบฉลาด (Smart Delay)
// ==========================================
bool smartDelay(int ms) {
  for (int i = 0; i < ms; i += 10) { 
    if (digitalRead(sw1) == HIGH) { // เช็คตลอดเวลาว่าปล่อยมือไหม
      return false; // ปล่อยมือ! หยุดทำงาน
    }
    delay(10);
  }
  return true; 
}