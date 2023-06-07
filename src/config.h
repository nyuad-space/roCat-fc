#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <SPI.h>
#include <RH_RF95.h>
#include <Adafruit_NeoPixel.h>

#define RF95_FREQ 915.0

#define RF95_CS 64  // PF11
#define RF95_INT 70 // PB11
#define RF95_RST 68 // PF15

#define LED_PIN PF10      // PF10
#define NUM_LEDS 1
Adafruit_NeoPixel LED(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

#define CUR_I2C_SDA 10 // PF0
#define CUR_I2C_SCL 11 // PF1

#define HDRM4_DO 1 // PE2
#define HDRM4_DI 2 // PE3

#endif