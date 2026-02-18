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
    
    // --- Step 1: กระพริบ 10 ครั้ง ---
    for (int i = 0; i < 10; i++) {
      
      // สั่งติด
      controlAllLeds(HIGH);
      // หน่วงเวลา 100ms (ถ้าปล่อยมือระหว่างนี้ ให้ return ออกจาก loop ทันที)
      if (smartDelay(100) == false) return; 

      // สั่งดับ
      controlAllLeds(LOW);
      if (smartDelay(100) == false) return; 
    }

    // --- Step 2: ถ้าครบ 10 ครั้งแล้วยังกดอยู่ -> ให้ติดค้าง ---
    controlAllLeds(HIGH);
    
    // วนลูปเช็คสถานะกดค้าง (ถ้าปล่อยมือเมื่อไหร่ หลุดลูปนี้ทันที)
    while (digitalRead(sw1) == LOW) {
      delay(10); 
    }
  } 
  
  // 2. ถ้าปล่อยเบรก (หรือหลุดมาจากข้างบน) -> สั่งดับให้หมด
  controlAllLeds(LOW);
}

// ==========================================
// ฟังก์ชันเสริม: สั่ง LED ทุกดวง (ให้โค้ดดูสะอาด)
// ==========================================
void controlAllLeds(int state) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(leds[i], state);
  }
}

// ==========================================
// ฟังก์ชันเสริม: หน่วงเวลาแบบฉลาด (Smart Delay)
// ==========================================
// คืนค่า true ถ้าหน่วงเวลาจนครบ
// คืนค่า false ถ้ามีการ "ปล่อยมือ" ระหว่างรอ
bool smartDelay(int ms) {
  for (int i = 0; i < ms; i += 5) { // ซอยเวลาเป็นรอบละ 10ms
    if (digitalRead(sw1) == HIGH) { // เช็คปุ่มทุกๆ 10ms
      return false; // เจอปล่อยมือ! ส่งสัญญาณบอกให้หยุดทำงาน
    }
    delay(10);
  }
  return true; // เวลาครบ ไม่มีใครปล่อยมือ
}