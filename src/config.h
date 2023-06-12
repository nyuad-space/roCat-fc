#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <rocat_baro.h>
#include <rocat_gps.h>
#include <rocat_imu.h>

#define RF95_FREQ 915.0

#define RF95_CS PE11
#define RF95_INT PB11
#define RF95_RST PF15
#define RF95_MOSI PE14
#define RF95_MISO PE13
#define RF95_SCK PE12

#define LED_PIN PF10      // PF10
#define NUM_LEDS 1

#define CUR_I2C_SDA PF0 // PF0
#define CUR_I2C_SCL PF1 // PF1

#define HDRM4_DO 1 // PE2
#define HDRM4_DI 2 // PE3

#define BUZZER PD1

#define SPIFLASH_JEDEC 0xEF40
#define SPIFLASH_CS PA4
#define SPIFLASH_SCK PA5
#define SPIFLASH_MISO PA6
#define SPIFLASH_MOSI PA7

#define RF69_FREQ 915.0

#define SPI5_0_RFM69_CS PG9
// #define SPI5_1_RFM69_CS PE5
// #define SPI5_2_RFM69_CS PE6
#define SPI5_RFM69_SCK PF7
#define SPI5_RFM69_MISO PF8
#define SPI5_RFM69_MOSI PF9

#define SPI5_RFM69_RST PE10 // B01_D1
#define SPI5_RFM69_INT PB10 // B01_D2

#endif