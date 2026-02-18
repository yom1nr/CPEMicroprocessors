#define LED1 15
#define LED2 5
hw_timer_t *timer = NULL;
void onTimer() {
  digitalWrite(LED2, !digitalRead(LED2));
}
void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 300000, true);
  timerAlarmEnable(timer);
}
void loop() {
  digitalWrite(LED1, !digitalRead(LED1));
  delay(500);
}
