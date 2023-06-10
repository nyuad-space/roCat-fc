#include <config.h>
#include <Arduino.h>
#include <SPIFlash.h>

// SPIClass FLASHSPI(SPIFLASH_MOSI, SPIFLASH_MISO, SPIFLASH_SCK);
SPIFlash flashdriver(PA4, 0xEF60);

void setup()
{
  Serial.begin(115200);
  
  while (!Serial)
  {
    delay (100);
  }
  Serial.println("Serial success");
  
  delay(100);

  flashdriver.wakeup();
  if(!flashdriver.initialize())
  {
    Serial.println("SPI FLASH Init Error!");
  }
  Serial.println("SPI FLASH Init success");
  delay(100);
}

void loop()
{
  Serial.println("Writing to flash");
  uint32_t counter = 0;
  flashdriver.chipErase();
  Serial.print("Done");
  // uint32_t counter = 520192;

  // while(counter<520192+256){
  //   Serial.print(flashdriver.readByte(counter), HEX);
  //   counter++;
  //   if (counter%16 == 0) Serial.println(); else Serial.print('.');
  //   }
  //   Serial.println();
}
