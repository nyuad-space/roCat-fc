#include "config.h"

// SPIClass IMU_GYRO = SPIClass(IMU_SPI_MOSI, IMU_SPI_MISO, IMU_SPI_SCK);
// SPIClass IMU_ACC = SPIClass(IMU_SPI_MOSI, IMU_SPI_MISO, IMU_SPI_SCK);
// SPIClass LoRa_SPI = SPIClass(RF95_MOSI, RF95_MISO, RF95_SCK);
// Adafruit_NeoPixel LED(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
// RH_RF95 rf95(RF95_CS, RF95_INT);
// Adafruit_INA219 ina219;
// ezBuzzer buzzer(BUZZER);
// LPS lps;
// Bmi088Gyro gyro(IMU_GYRO, PD13);
// Bmi088Accel accel(IMU_ACC, PD9);
// LoRaClass LORA_123;

void setup()
{ 
  Serial.begin(115200);
  while(!Serial)
  {
    delay(1);
  }
  delay(1000);
  
}

void loop()
{

}
