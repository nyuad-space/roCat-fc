#include "config.h"

void setup() {
  LED.begin();
  LED.show();
}

void loop() {
  LED.setPixelColor(0, 64, 50, 64);
  LED.show();
}