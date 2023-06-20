#ifndef ROCAT_LORA
#define ROCAT_LORA

#include <SPI.h>
#include <RHSoftwareSPI.h>
#include <RH_RF69.h>
#include <rocat_scheduler.h>
#include <rocat_state.h>

#define LORA_SPI_INT PB10
#define LORA_SPI_CS PG9

#define LORA_SPI_RST PE10
#define LORA_SPI_SCK PF7
#define LORA_SPI_MISO PF8
#define LORA_SPI_MOSI PF9

#define LORA_FREQ 915.0
#define PREAMBLE_LEN 8

enum Button
{
    NONE,
    PRELAUNCH_BUTTON,
    LAUNCH,
    END_BUTTON,
    RESET_BUTTON,
    WRITE_SD
};

class Transceiver : public Task
{
private:
    RH_RF69 *LoRa;
    RHSoftwareSPI LORA_SPI;
    long measurements_delay;
    long previous_time = 0;
    uint8_t *output_buffer[64];
    uint32_t buffer[RH_RF69_MAX_MESSAGE_LEN];
    uint16_t offset = 0;
    uint32_t packet_id = 0;
    Button button = NONE;

public:
    Transceiver(long measurements_delay);
    ~Transceiver();

    bool timeElapsed();
    void storeInBuffer(uint8_t *packet, int size);
    Button getButton();
    void buttonNone();

    bool Callback();
    bool OnEnable();
    void OnDisable();

    bool CheckStatus();
};

#endif