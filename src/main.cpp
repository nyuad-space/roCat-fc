#include "config.h"

SPIClass IMU_GYRO = SPIClass(IMU_SPI_MOSI, IMU_SPI_MISO, IMU_SPI_SCK);
SPIClass IMU_ACC = SPIClass(IMU_SPI_MOSI, IMU_SPI_MISO, IMU_SPI_SCK);
SPIClass LoRa_SPI = SPIClass(RF95_MOSI, RF95_MISO, RF95_SCK);
Adafruit_NeoPixel LED(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
RH_RF95 rf95(RF95_CS, RF95_INT);
Adafruit_INA219 ina219;
ezBuzzer buzzer(BUZZER);
LPS lps;
SFE_UBLOX_GNSS myGNSS;
Bmi088Gyro gyro(IMU_GYRO, PD13);
Bmi088Accel accel(IMU_ACC, PD9);
LoRaClass LORA_123;

void setup()
{ 
  Serial.begin(115200);
  while(!Serial)
  {
    delay(1);
  }
  delay(1000);

  // //IMU
  // int status;

  // status = gyro.begin();
  // if(status < 0) {
  //   Serial.println("Gyro Initialization Error");
  //   Serial.println(status);
  //   while (1) {}
  // }
  // Serial.println("Gyro Initialization");

  // status = accel.begin();
  // if(status < 0) {
  //   Serial.println("Accel Initialization Error");
  //   Serial.println(status);
  //   while (1) {}
  // }
  // Serial.println("Accel Initialization");
  // //GNSS
  // Wire.setSCL(PA8);
  // Wire.setSDA(PC9);
  // Wire.begin();
  
  //LoRa
  pinMode(RF95_CS, OUTPUT);
  pinMode(RF95_RST, OUTPUT);
  pinMode(RF95_INT, INPUT);
  LORA_123.setPins(RF95_CS, RF95_RST, RF95_INT);
  LORA_123.setSPI(LoRa_SPI);
  LORA_123.begin(915E6);
  if (!LORA_123.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("Starting LoRa!");
  
  // //GNSS
  // if(myGNSS.begin() == false)
  // {
  //   Serial.print("u-blox GNSS not detected at default I2C adress.");
  // }
  // myGNSS.setI2COutput(COM_TYPE_UBX);
  // myGNSS.saveConfiguration(VAL_CFG_SUBSEC_IOPORT);
  // myGNSS.enableDebugging();

}

int16_t packetnum = 0;  

void loop()
{
  // delay(100);
  // //GNSS
  // long latitude = myGNSS.getLatitude();
  // Serial.print("Latitude: ");
  // Serial.print(latitude);
  // Serial.println();

  // long longitude = myGNSS.getLongitude();
  // Serial.print("Longitude: ");
  // Serial.print(longitude);
  // Serial.println();

  // long altitude = myGNSS.getAltitude();
  // Serial.print("Altitude: ");
  // Serial.print(altitude);
  // Serial.println();

  // Serial.print(myGNSS.getYear());
  // Serial.print(myGNSS.getMonth());
  // Serial.print(myGNSS.getDay());
  // Serial.println();

  // Serial.println("*****************************************");

    // received a packet
    Serial.print("Received packet '");
  
    // read packet
    while (LORA_123.available()) {
      Serial.print((char)LORA_123.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LORA_123.packetRssi());
  //IMU
  // /* read the gyro */
  // gyro.readSensor();
  // Serial.print(gyro.getGyroX_rads());
  // Serial.print(",");
  // Serial.print(gyro.getGyroY_rads());
  // Serial.print(",");
  // Serial.print(gyro.getGyroZ_rads());
  // Serial.println("");



  // accel.readSensor();
  // Serial.print(accel.getAccelX_mss());
  // Serial.print(",");
  // Serial.print(accel.getAccelY_mss());
  // Serial.print(",");
  // Serial.print(accel.getAccelZ_mss());
  // Serial.println("");
}
