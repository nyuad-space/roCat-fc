#ifndef ROCAT_LORA
#define ROCAT_LORA

#include <SPI.h>
#include <RH_RF69.h>
// #include <scheduler.h>

#define LORA_SPI_INT PB10
#define LORA_SPI_CS PG9

#define LORA_SPI_RST PE10
#define LORA_SPI_SCK PF7
#define LORA_SPI_MISO PF8
#define LORA_SPI_MOSI PF9

#define LORA_FREQ 915.0
#define PREAMBLE_LEN 8

class Transceiver
{
private:
    RH_RF69 *LoRa;
    long measurements_delay;
    long previous_time = 0;
    uint8_t *output_buffer[64];
    uint32_t buffer[RH_RF69_MAX_MESSAGE_LEN];
    uint16_t offset = 0;
    uint32_t packet_id = 0;

public:
    Transceiver(long measurements_delay);
    ~Transceiver();

    bool timeElapsed();
    void storeInBuffer(uint8_t *packet, int size);

    bool Callback();
    bool OnEnable();
    void OnDisable();

    bool CheckStatus();
};

#endif