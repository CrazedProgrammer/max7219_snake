#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

const uint8_t N_DISPLAYS = 4;

void initDisplay();
void updateDisplay();
void setPixel(uint8_t x, uint8_t y, bool on);

#endif /* DISPLAY_H */
