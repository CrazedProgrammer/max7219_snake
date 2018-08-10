#ifndef INPUT_H
#define INPUT_H

enum DPad {
  DPAD_NONE = 0,
  DPAD_RIGHT = 1,
  DPAD_UP = 2,
  DPAD_LEFT = 3,
  DPAD_DOWN = 4
};

void initInput();
DPad getDPadState();
bool getButtonPressed();

#endif /* INPUT_H */
