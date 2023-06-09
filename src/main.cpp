#include <config.h>
#include <Adafruit_LPS2X.h>
Adafruit_LPS22 barometer;
SPIClass SPI_BARO;

void setup()
{ 
  Serial.begin(115200);
  //Stop if serial error
  while(!Serial)
  {
    Serial.println("Serial error... Check wires and reload");
    delay(1);
  }
  //Wait for setups
  delay(100);
  //Barometer setup
  if (!barometer.begin_SPI(BARO_SPI_CS, BARO_SPI_SCK, BARO_SPI_MISO, BARO_SPI_MOSI))
  {
    Serial.println("Failed to find sensor");
    while(1) 
    {
      delay(1);
    }
  }
  Serial.println("Found sensor!");
}

void loop()
{
  sensors_event_t temp;
  sensors_event_t presssure;
  barometer.getEvent(&presssure, &temp);
  Serial.print(temp.temperature);
  Serial.print(",");
  Serial.println(presssure.pressure);
  delay(100);
}
