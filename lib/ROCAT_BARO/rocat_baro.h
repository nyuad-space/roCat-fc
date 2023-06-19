#ifndef ROCAT_BARO
#define ROCAT_BARO

#include <SPI.h>
#include <Adafruit_LPS2X.h>
// #include <scheduler.h>

#define BARO_SPI_CS PG11
#define BARO_SPI_SCK PG13
#define BARO_SPI_MOSI PG14
#define BARO_SPI_MISO PG12
#define BARO_SPI_INT PG10

class Barometer
{
private:
    Adafruit_LPS22 *driver;
    Adafruit_Sensor *temp_driver, *pressure_driver;
    SPIClass SPI_BARO;
    long measurement_delay;
    long previous_time = 0;
    float pressure;
    float temperature;

public:
    Barometer(long measurement_delay);
    ~Barometer();

    bool measurementReady();
    float getTemperature();
    float getPressure();

    bool Callback();
    bool OnEnable();
    void OnDisable();
    bool CheckStatus();
};

#endif