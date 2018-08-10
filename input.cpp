#include "input.h"
#include <Arduino.h>

// This implements inputs from an analog joystick.

const uint16_t DX_PIN = A0;
const uint16_t DY_PIN = A1;
const uint16_t DP_PIN = 7;

void initInput() {
  pinMode(DP_PIN, INPUT);
  digitalWrite(DP_PIN, HIGH);
}

DPad getDPadState() {
  float dx = (float)analogRead(DX_PIN) / 512.0f - 1.0f;
  float dy = (float)analogRead(DY_PIN) / 512.0f - 1.0f;
  float direction = atan2(dx, dy);
  DPad state = DPAD_NONE;
  if (dx < -0.1f || dx > 0.1f || dy < -0.1f || dy > 0.1f) {
    state = (DPad)((int16_t)((direction + 1.25 * PI) / (0.5f * PI) + 2.0f) % 4 + 1);
  }
  return state;
}

bool getButtonPressed() {
  return !digitalRead(DP_PIN);
}
