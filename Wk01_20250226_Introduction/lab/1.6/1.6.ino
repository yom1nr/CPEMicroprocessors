int leds[] = {12, 13, 5, 18, 19, 21, 22, 23}; 
int sw1 = 15; 
int mode = -1; // -1=เริ่ม, 0=ซ้ายไปขวา, 1=หยุด, 2=ขวาไปซ้าย, 3=หยุด
int currentLED = 0;
unsigned long lastRunTime = 0; 

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW); // ปิดหมดตอนเริ่ม
  }
  pinMode(sw1, INPUT_PULLUP);
}

void loop() {
  // ============================================
  // 1. เช็คปุ่มกด (แบบแก้ปุ่มเบิ้ล 100%)
  // ============================================
  if (digitalRead(sw1) == LOW) { // ถ้าเจอกดปุ่ม
    delay(20); // รอสัญญาณนิ่ง (Debounce)
    
    if (digitalRead(sw1) == LOW) { // เช็คซ้ำว่ากดจริงไหม
      
      // >>> เปลี่ยนโหมดตรงนี้ <<<
      mode++; 
      if (mode > 3) mode = 0; // ถ้าเกินโหมด 3 วนกลับไป 0
      
      // >>> ทีเด็ดคือบรรทัดนี้: รอจนกว่าจะ "ปล่อยมือ" <<<
      while(digitalRead(sw1) == LOW) {
        delay(10); // ไม่ทำอะไร รอปล่อยปุ่มอย่างเดียว
      }
    }
  }

  // ============================================
  // 2. ทำงานตามโหมด (Logic เดิม)
  // ============================================
  if (mode == -1) {
    // ไฟดับหมด
  } 
  else if (mode == 1 || mode == 3) {
    // โหมดหยุด: ไฟติดค้าง (ไม่ต้องทำอะไรเพิ่ม มันจะค้างสถานะล่าสุดไว้เอง)
    digitalWrite(leds[currentLED], HIGH);
  }
  else {
    // โหมดวิ่ง (0 หรือ 2)
    digitalWrite(leds[currentLED], HIGH);
    if (millis() - lastRunTime > 200) { // ปรับความเร็วตรงนี้
      lastRunTime = millis();
      
      digitalWrite(leds[currentLED], LOW); // ดับดวงเก่า

      if (mode == 0) { // วิ่งขวา (เพิ่ม)
        currentLED++;
        if (currentLED > 7) currentLED = 0;
      } 
      else if (mode == 2) { // วิ่งซ้าย (ลด)
        currentLED--;
        if (currentLED < 0) currentLED = 7;
      }

      digitalWrite(leds[currentLED], HIGH); // ติดดวงใหม่
    }
  }
}