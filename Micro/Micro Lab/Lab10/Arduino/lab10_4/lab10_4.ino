String Cmd, strData;
int strInt, strlength, Pulse = 0, Freq = 0, Duty = 100, FullDelay = 500;
char buffer[40];

int DelayOn = 0;
int DelayOff = 0;

int LED = 23;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    strData = Serial.readString();
    strlength = strData.length();
    Cmd = strData.substring(0, 1);
    strInt = strData.substring(2, strlength).toInt();

    if (Cmd == "P") {
      if (strInt >= 10 && strInt <= 999 || strInt == 0) Pulse = strInt;
      sprintf(buffer, "read P = %S --> %d", strData, strInt);
      Serial.println(buffer);
    }

    if (Cmd == "D") {
      if (strInt >= 10 && strInt <= 99) Duty = strInt;
      sprintf(buffer, "read D = %S --> %d", strData, strInt);
      Serial.println(buffer);
    }

    if (Cmd == "G") {
      sprintf(buffer, "read G = %S", "Run ESP32");
      Serial.println(buffer);
      runESP32();
    }

    if (Cmd == "?") {
      Serial.println("By: Nadthapat Phuttaruksa");
      sprintf(buffer, "Pulse=%d, Duty-Cycle=%d", Pulse, Duty);
      Serial.println(buffer);
      runESP32();
    }

    sprintf(buffer, "Pulse=%d, Duty-Cycle=%d, Cmd=%s", Pulse, Duty, Cmd);
    Serial.println(buffer);
  }
  
}

void runESP32() {
  if(Duty == 100){
    DelayOn = FullDelay;
    DelayOff = FullDelay;
  }else
  {
    DelayOn = Duty / 100.0 * FullDelay;
    DelayOff = FullDelay - DelayOn;
  }
  Serial.println(DelayOn);
  Serial.println(DelayOff);

  if (Pulse == 0) {
    while (true) {
      digitalWrite(LED, HIGH);
      delay(DelayOn);
      digitalWrite(LED, LOW);
      delay(DelayOff);
    }
  } else {
    for (int i = 0; i < Pulse; i++) {
      digitalWrite(LED, HIGH);
      delay(DelayOn);
      digitalWrite(LED, LOW);
      delay(DelayOff);
    }
  }
  digitalWrite(LED, HIGH);
}
