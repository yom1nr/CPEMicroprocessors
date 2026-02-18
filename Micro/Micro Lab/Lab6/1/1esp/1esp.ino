int led = 21;
// the setup routine runs once when you press reset:
void setup() {
  pinMode(led, OUTPUT);
}
// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);
  delay(300);
  digitalWrite(led, LOW);
  delay(300);
  digitalWrite(led, HIGH);
  delay(300);
  digitalWrite(led, LOW);
  delay(1000);
  digitalWrite(led, HIGH);
  delay(300);
  digitalWrite(led, LOW);
  delay(300);
  digitalWrite(led, HIGH);
  delay(300);
  digitalWrite(led, LOW);
  delay(1000);
}
