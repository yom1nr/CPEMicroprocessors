int leds[] = {12, 13, 5, 18, 19, 21, 22, 23}; // เรียงขาจาก ซ้าย -> ขวา
int pushButton = 15;

// เพิ่มตัวแปร global เพื่อจำตำแหน่งปัจจุบัน
int currentLED = 0; 

void setup() {
  // วนลูปตั้งค่าขา LED ทั้ง 8 ดวงเป็น OUTPUT
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }
  
  // ตั้งค่าขาสวิตช์
  pinMode(pushButton, INPUT_PULLUP);
}

void loop() {
  // 1. สั่งให้ไฟดวงปัจจุบัน "ติด"
  digitalWrite(leds[currentLED], HIGH);
  
  // 2. หน่วงเวลา (ความเร็วไฟวิ่ง)
  delay(300); 
  
  // 3. สั่งให้ไฟดวงปัจจุบัน "ดับ"
  digitalWrite(leds[currentLED], LOW);

  // 4. เช็คปุ่ม เพื่อคำนวณว่า "ดวงต่อไป" จะเป็นดวงไหน?
  // (โค้ดจะเช็คตรงนี้ทุกครั้งที่ไฟกระพริบ 1 ครั้ง ไม่ต้องรอครบ 8 ดวง)
  if (digitalRead(pushButton) == LOW) {
    // === กรณี: กดปุ่ม (วิ่งไปทางขวา / เพิ่มขึ้น) ===
    currentLED++; 
    
    // ถ้าเกินดวงสุดท้าย (7) ให้วนกลับไปดวงแรก (0)
    if (currentLED > 7) {
      currentLED = 0;
    }
  } 
  else {
    // === กรณี: ไม่กดปุ่ม (วิ่งไปทางซ้าย / ลดลง) ===
    currentLED--;
    
    // ถ้าต่ำกว่าดวงแรก (0) ให้วนกลับไปดวงสุดท้าย (7)
    if (currentLED < 0) {
      currentLED = 7;
    }
  }
}