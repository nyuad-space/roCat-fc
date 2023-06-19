#ifndef ROCAT_FLASH_H
#define ROCAT_FLASH_H

#include <SPIFlash.h>
// #include <scheduler.h>

#define FIRST_PAGE_OFFSET 256
#define MAX_DATA_UNITS 131072

class Flash
{
private:
    SPIFlash *driver;
    long measurement_delay;
    long previous_time = 0;
    char *storage_buffer[128];
    int32_t memory_unit_offset = 0;
    int unit_size = 128;

public:
    Flash(uint8_t FLASH_CS, long measurement_delay);
    ~Flash();

    bool measurementReady();

    void storeInBuffer(int8_t *packet, int size);

    bool Callback();
    bool OnEnable();
    void OnDisable();
    bool CheckStatus();
};

#endif