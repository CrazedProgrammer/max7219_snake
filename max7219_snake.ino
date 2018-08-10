#include "display.h"
#include "snake.h"
#include "input.h"

void setup() {
  Serial.begin(9600);

  initDisplay();
  initInput();

  initSnake();
}

void loop() {
  updateSnake();
  updateDisplay();
}
