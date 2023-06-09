#include <rocat_baro.h>

Barometer::Barometer(long measurement_delay) : Task(TASK_MILLISECOND, TASK_FOREVER, &scheduler, false),
                                               measurement_delay(measurement_delay),
                                               previous_time(0), pressure(-1),
                                               temperature(-1)
{
    this->SPI_BARO = SPIClass(BARO_SPI_MOSI, BARO_SPI_MISO, BARO_SPI_SCK);
    this->SPI_BARO.begin();
    this->driver = new Adafruit_LPS22();
}

Barometer::~Barometer() {}

float Barometer::getTemperature()
{
    return this->temperature;
}

float Barometer::getPressure()
{
    return this->pressure;
}

bool Barometer::measurementReady()
{
    long current_time = millis();
    if (current_time - this->previous_time >= this->measurement_delay)
    {
        this->previous_time = current_time;
        return true;
    }
    return false;
}

bool Barometer::Callback()
{
    if (measurementReady())
    {
        sensors_event_t pressure;
        sensors_event_t temp;
        this->temp_driver->getEvent(&temp);
        this->pressure_driver->getEvent(&pressure);
        this->temperature = temp.temperature;
        this->pressure = pressure.pressure;
        return true;
    }
    return false;
}

bool Barometer::OnEnable()
{
    this->temp_driver = this->driver->getTemperatureSensor();
    this->pressure_driver = this->driver->getPressureSensor();
    return true;
}

void Barometer::OnDisable()
{
}

bool Barometer::checkStatus()
{
    return this->driver->begin_SPI(BARO_SPI_CS, &this->SPI_BARO);
}