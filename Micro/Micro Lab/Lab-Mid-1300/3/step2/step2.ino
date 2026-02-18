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
  uint8_t buttons = tm.readButtons();
  static char display_text[9] = "--------";
  for (uint8_t i = 0; i < 8; i++) {
    if (buttons & (1 << i)) {
      for (int j = 0; j < 7; j++) {
        display_text[j] = display_text[j + 1];
      }
      display_text[7] = '1' + i;
      tm.displayText(display_text);
      break;
    }
  }
  delay(100);
}
