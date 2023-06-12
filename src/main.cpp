#include <Arduino.h>
#include <SPI.h>
#include <RH_RF69.h>

#define RF69_FREQ 915.0

#define RFM69_CS PG9
#define RFM69_INT PB10
#define RFM69_RST PE10

#define RFM69_SCK PF7
#define RFM69_MISO PF8
#define RFM69_MOSI PF9

RH_RF69 rf69(RFM69_CS, RFM69_INT);

void setup()
{
  Serial.begin(115200);
  SPI.setSCLK(RFM69_SCK);
  SPI.setMISO(RFM69_MISO);
  SPI.setMOSI(RFM69_MOSI);

  pinMode(RFM69_RST, OUTPUT);
  delay(10);
  digitalWrite(RFM69_RST, LOW);

  while (!Serial)
  {
    Serial.println("Serial Monitor Not Ready!");
    delay(100);
  }
  Serial.println("Serial MOnitor Ready!");

  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  if(!rf69.init())
  {
    Serial.println("Initialization failed!");
    while(1);
  }
  Serial.println("Initialization success");

  if (!rf69.setFrequency(RF69_FREQ))
  {
    Serial.println("Set Freqeuency Failed.");
  }
  Serial.println("Set Frequency Success");

  rf69.setTxPower(18, true);

  Serial.print("RFM69 radio @"); 
  Serial.print((int)RF69_FREQ);
  Serial.println(" MHz");

}

int16_t packetnum = 0;

void loop()
{
  delay(1000);

  char radiopacket [20] = "Hello World #";
  itoa(packetnum++, radiopacket+13, 10);
  Serial.print("Sending... ");
  Serial.println(radiopacket);

  rf69.send((uint8_t *)radiopacket, strlen(radiopacket));
  rf69.waitPacketSent();

  Serial.println("Sent!");
}