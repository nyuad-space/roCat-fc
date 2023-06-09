#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include <rocat_gps.h>
#include <rocat_baro.h>
// #include <rocat_imu.h>
#include <rocat_lora.h>
#include <rocat_flash.h>
#include <rocat_scheduler.h>
//
#include <SD.h> //Need to create custom lib
// #include <scheduler.h>
// Mising current sensor, buzzer, led lib/functions
// Missing state indicaton logic

#define RF95_FREQ 915.0

RHSoftwareSPI LORA_SPI;

#define IMU_GYRO_INT1 PB12
#define IMU_GYRO_INT2 PD8
#define IMU_ACCEL_INT1 PD11
#define IMU_ACCEL_INT2 PD12
#define IMU_SPI_SCK PB13
#define IMU_SPI_MISO PB14
#define IMU_SPI_MOSI PB15
#define IMU_SPI_CS_ACCEL PD9
#define IMU_SPI_CS_GYRO PD13

SPIClass IMU_ACCEL = SPIClass(IMU_SPI_MOSI, IMU_SPI_MISO, IMU_SPI_SCK);
SPIClass IMU_GYRO = SPIClass(IMU_SPI_MOSI, IMU_SPI_MISO, IMU_SPI_SCK);
// #define RF95_CS PE11
// #define RF95_INT PB11
// #define RF95_RST PF15
// #define RF95_MOSI PE14
// #define RF95_MISO PE13
// #define RF95_SCK PE12

// #define LED_PIN PF10      // PF10
// #define NUM_LEDS 1

// #define CUR_I2C_SDA PF0 // PF0
// #define CUR_I2C_SCL PF1 // PF1

// #define HDRM4_DO 1 // PE2
// #define HDRM4_DI 2 // PE3

// #define BUZZER PD1

#endif