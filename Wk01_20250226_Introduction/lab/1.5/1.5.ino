// ขา LED 8 ดวง (ตามที่คุณตั้งค่าไว้)
int leds[] = {12, 13, 5, 18, 19, 21, 22, 23}; 

// ขาสวิตช์ 2 ตัว
int sw1 = 15; // กดแล้ววิ่ง ซ้าย -> ขวา
int sw2 = 4;  // กดแล้ววิ่ง ขวา -> ซ้าย (เพิ่มสวิตช์นี้เข้ามา)

// ตัวแปรจำสถานะ
int currentLED = 0;      // ตำแหน่งไฟปัจจุบัน
int direction = 1;       // ทิศทาง: 1 = ไปขวา (เพิ่ม), -1 = ไปซ้าย (ลด)

void setup() {
  // ตั้งค่าขา LED
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }
  
  // ตั้งค่าขาสวิตช์ (ต่อแบบ Active LOW ทั้งคู่)
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
}

void loop() {
  // 1. ตรวจสอบการกดปุ่ม (เช็คก่อนทำงานเสมอ)
  if (digitalRead(sw1) == LOW) {
    direction = 1; // ตั้งทิศให้วิ่งไปทางขวา (Index เพิ่มขึ้น)
  }
  
  if (digitalRead(sw2) == LOW) {
    direction = -1; // ตั้งทิศให้วิ่งไปทางซ้าย (Index ลดลง)
  }

  // 2. สั่งงาน LED ดวงปัจจุบัน
  digitalWrite(leds[currentLED], HIGH);
  delay(250); // ความเร็วไฟวิ่ง
  digitalWrite(leds[currentLED], LOW);

  // 3. คำนวณตำแหน่งดวงถัดไป ตามทิศทาง (direction)
  currentLED = currentLED + direction;

  // 4. เช็คขอบเขต (Boundary Check) เพื่อให้วนลูป
  if (currentLED > 7) {       // ถ้าวิ่งเลยตัวขวาสุด
    currentLED = 0;           // ให้วนกลับมาตัวซ้ายสุด
  } 
  else if (currentLED < 0) {  // ถ้าวิ่งเลยตัวซ้ายสุด
    currentLED = 7;           // ให้วนกลับไปตัวขวาสุด
  }
}