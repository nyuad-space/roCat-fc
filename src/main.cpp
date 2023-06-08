#include "config.h"

Adafruit_NeoPixel LED(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
RH_RF95 rf95(RF95_CS, RF95_INT);
Adafruit_INA219 ina219;
ezBuzzer buzzer(BUZZER);
LPS lps;

void setup()
{
  LED.begin();
  LED.show();
}

void loop()
{
  LED.setPixelColor(0, 0, 0, 255);
  LED.show();
  delay(1000);
  LED.setPixelColor(0, 0, 0, 0);
  LED.show();
  delay(1000);
}