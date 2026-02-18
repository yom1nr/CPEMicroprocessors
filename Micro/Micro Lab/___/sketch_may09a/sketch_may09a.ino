#define LED 15
const int ledPin1 = 22;  // กำหนดหมายเลขของพินสำหรับ LED ที่ 1
const int ledPin2 = 23;  // กำหนดหมายเลขของพินสำหรับ LED ที่ 2
const long interval1 = 500;         // กำหนดช่วงเวลาของ LED ที่ 1 (ms)
const long interval2 = 300;         // กำหนดช่วงเวลาของ LED ที่ 2 (ms)
unsigned long previousMillis1 = 0;  // เก็บค่าเวลาล่าสุดของ LED ที่ 1
unsigned long previousMillis2 = 0;  // เก็บค่าเวลาล่าสุดของ LED ที่ 2
#define BUTTON 4
#define PRESSED LOW
#define TIME_TURNOFF 5000

enum {BT_RELEASE, BT_PRESS, BT_PRESS_WAIT} bt_state = BT_RELEASE;
uint32_t bt_timer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(ledPin1, OUTPUT);  // กำหนดโหมดของพิน LED ที่ 1 เป็น OUTPUT
  pinMode(ledPin2, OUTPUT);  // กำหนดโหมดของพิน LED ที่ 2 เป็น OUTPUT
  pinMode(BUTTON, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(bt_state);
  Serial.println(BT_RELEASE);
  Serial.println(BT_PRESS);
  Serial.println(BT_PRESS_WAIT);
  Serial.println(digitalRead(BUTTON));
  Serial.println("================");
  unsigned long currentMillis = millis();  // ดึงค่าเวลาปัจจุบัน

  // สร้างหน้าที่สำหรับ LED ที่ 1
  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;               // บันทึกค่าเวลาปัจจุบัน
    digitalWrite(ledPin1, !digitalRead(ledPin1));  // เปลี่ยนสถานะของ LED ที่ 1
  }

  // สร้างหน้าที่สำหรับ LED ที่ 2
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;               // บันทึกค่าเวลาปัจจุบัน
    digitalWrite(ledPin2, !digitalRead(ledPin2));  // เปลี่ยนสถานะของ LED ที่ 2
  }

  switch (bt_state) {
    case BT_RELEASE:
      if (digitalRead(BUTTON) == PRESSED) bt_state = BT_PRESS;
      break;
    case BT_PRESS:
      bt_timer = millis();
      if (digitalRead(BUTTON) == PRESSED) bt_state = BT_PRESS_WAIT;
      else bt_state = BT_RELEASE;
      break;
    case BT_PRESS_WAIT:
      if (digitalRead(BUTTON) == PRESSED) {
        digitalWrite(LED, millis() - bt_timer < TIME_TURNOFF);
      }
      else bt_state = BT_RELEASE;
      break;
  }
}
