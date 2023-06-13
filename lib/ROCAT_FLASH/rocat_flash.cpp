#include <rocat_flash.h>

Flash::Flash(uint8_t FLASH_CS, long measurement_delay) : Task(TASK_MILLISECOND, TASK_FOREVER, &scheduler, false), measurement_delay(measurement_delay)
{
    this->driver = new SPIFlash(FLASH_CS, 0xEF60);
}

Flash::~Flash() {}

bool Flash::measurementReady()
{
    long current_time = millis();
    if (current_time - this->previous_time >= this->measurement_delay)
    {
        this->previous_time = current_time;
        return true;
    }
    return false;
}

void Flash::storeInBuffer(int8_t *packet, int size)
{
    memcpy(this->storage_buffer, packet, size);
}

bool Flash::Callback()
{

}

bool Flash::OnEnable()
{
    int32_t offset_read = 0;
    this->driver->readBytes(0, &offset_read, 4);
    this->memory_unit_offset = (offset_read > 0) ? offset_read : 0;
    Serial.print("Memory Offset: ");
    Serial.println(this->memory_unit_offset);

    //If memory is almost full
    if (this->memory_unit_offset > (int32_t)(MAX_DATA_UNITS * 0.95))
    {
        Serial.println("Memory full...cleaning memory!");
        this->driver->chipErase();
        Serial.println("Memory Emptied!");
    }
    return true; 
}

void Flash::OnDisable()
{

}

bool Flash::checkStatus()
{
    return this->driver->initialize();
}
