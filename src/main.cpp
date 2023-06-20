#include "BMI088.h"
#include <Arduino.h>
#include <config.h>
#include <SPI.h>

/* accel object */
Bmi088Accel accel(IMU_ACCEL, IMU_SPI_CS_ACCEL);
/* gyro object */
Bmi088Gyro gyro(IMU_GYRO, IMU_SPI_CS_GYRO);

void setup()
{
  int status;
  /* USB Serial to print data */
  Serial.begin(115200);
  while (!Serial)
  {
  }
  /* start the sensors */
  status = accel.begin();
  if (status < 0)
  {
    Serial.println("Accel Initialization Error");
    Serial.println(status);
    while (1)
    {
    }
  }
  status = gyro.begin();
  if (status < 0)
  {
    Serial.println("Gyro Initialization Error");
    Serial.println(status);
    while (1)
    {
    }
  }
}

void loop()
{
  /* read the accel */
  accel.readSensor();
  /* read the gyro */
  gyro.readSensor();
  /* print the data */
  Serial.print(accel.getAccelX_mss() * 1000000);
  Serial.print("\t");
  Serial.print(accel.getAccelY_mss());
  Serial.print("\t");
  Serial.print(accel.getAccelZ_mss());
  Serial.print("\t");
  Serial.print(gyro.getGyroX_rads());
  Serial.print("\t");
  Serial.print(gyro.getGyroY_rads());
  Serial.print("\t");
  Serial.print(gyro.getGyroZ_rads()*1000);
  Serial.print("\t");
  Serial.print(accel.getTemperature_C());
  Serial.print("\n");
  /* delay to help with printing */
  delay(20);
}