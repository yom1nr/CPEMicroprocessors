#include <TM1638plus.h>

#define pin_STB 21
#define pin_CLK 19
#define pin_DIO 18

TM1638plus tm(pin_STB, pin_CLK, pin_DIO, true);

void setup() {
  Serial.begin(115200);
  tm.displayBegin();
  tm.brightness(6);
  tm.displayText("--------");
}

void loop() { 
  uint8_t keys = tm.readButtons();
  static uint8_t current_display = 0;
  for (uint8_t i = 0; i < 8; i++) {
    if (keys & (1 << i)) {
      if (current_display != (i + 1)) {
        current_display = i + 1;
        char text[9];
        snprintf(text, sizeof(text), "%d-------", current_display);
        tm.displayText(text);
      }
      while (keys == tm.readButtons()) {
        delay(50);
      }
    }
  }
  delay(100);
}
