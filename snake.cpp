#include "snake.h"
#include "display.h"
#include "input.h"

const uint16_t MAX_SNAKE_LENGTH = 512;
uint8_t snakeX[MAX_SNAKE_LENGTH];
uint8_t snakeY[MAX_SNAKE_LENGTH];
uint8_t snakeLength = 2;
uint8_t appleX;
uint8_t appleY;
DPad lastInput = DPAD_RIGHT;

void initSnake() {
  snakeX[0] = 2;
  snakeY[0] = 1;
  snakeX[1] = 1;
  snakeY[1] = 1;
  appleX = random(N_DISPLAYS * 8);
  appleY = random(8);
  setPixel(appleX, appleY, true);
}

void updateSnake() {
  DPad input = getDPadState();
  if (input != DPAD_NONE && ((input + 2) % 4) != lastInput) {
    lastInput = input;
  }
  uint8_t newSnakeX = snakeX[0];
  uint8_t newSnakeY = snakeY[0];
  newSnakeX += (lastInput == DPAD_LEFT) ? -1 : 0;
  newSnakeX += (lastInput == DPAD_RIGHT) ? 1 : 0;
  newSnakeY += (lastInput == DPAD_UP) ? -1 : 0;
  newSnakeY += (lastInput == DPAD_DOWN) ? 1 : 0;
  newSnakeX %= N_DISPLAYS * 8;
  newSnakeY %= 8;
  if (newSnakeX == appleX && newSnakeY == appleY) {
    snakeLength++;
    setPixel(appleX, appleY, false);
    appleX = random(N_DISPLAYS * 8);
    appleY = random(8);
    setPixel(appleX, appleY, true);
  } else {
    setPixel(snakeX[snakeLength - 1], snakeY[snakeLength - 1], false);
  }
  for (uint8_t i = snakeLength; i > 0; i--) {
    if (newSnakeX == snakeX[i] && newSnakeY == snakeY[i]) {
      // game lost
      delay(2000);
      // reset the system
      asm volatile ("jmp 0");
    }
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }
  snakeX[0] = newSnakeX;
  snakeY[0] = newSnakeY;
  setPixel(snakeX[0], snakeY[0], true);
  updateDisplay();

  uint8_t delayLength = 200 - snakeLength * 5;
  if (delayLength < 40) delayLength = 40;
  delay(delayLength);
}
