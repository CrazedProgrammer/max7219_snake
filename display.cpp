#include "display.h"
#include <LedControl.h>

LedControl lc = LedControl(10, 12, 11, N_DISPLAYS);
uint8_t displayLines[N_DISPLAYS * 8];
uint8_t updatedLines[N_DISPLAYS];

void initDisplay() {
  for (uint8_t i = 0; i < N_DISPLAYS; i++) {
    // put your setup code here, to run once:
    lc.shutdown(i,false);// turn off power saving, enables display
    lc.setIntensity(i,5);// sets brightness (0~15 possible values)
    lc.clearDisplay(i);// clear screen
  }
}

void updateDisplay() {
  for (uint8_t line = 0; line < N_DISPLAYS * 8; line++) {
    if (updatedLines[line / 8] & (1 << (line % 8))) {
      lc.setRow(line / 8, 7 - line % 8, displayLines[line]);
      updatedLines[line / 8] &= ~(1 << (line % 8));
    }
  }
}

void setPixel(uint8_t x, uint8_t y, bool on) {
  if (x < N_DISPLAYS * 8 && y < 8) {
    if (on) {
      displayLines[y + (x / 8) * 8] |= 1 << (x % 8);
    } else {
      displayLines[y + (x / 8) * 8] &= ~(1 << (x % 8));
    }
    updatedLines[x / 8] |= 1 << y;
  }
}
