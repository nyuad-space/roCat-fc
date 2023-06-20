#ifndef ROCAT_GPS
#define ROCAT_GPS

#include <rocat_scheduler.h>
#include <Wire.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

#define GNSS_I2C_RST PD10
#define GNSS_I2C_SCL PA8
#define GNSS_I2C_SDA PC9

class GPS : public Task
{
private:
    SFE_UBLOX_GNSS *driver;
    long measurement_delay;
    long previous_time = 0;
    int32_t altitudeMSL;
    int32_t latitude;
    int32_t longitude;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;

public:
    GPS(long measurement_delay);
    ~GPS();

    bool measurementReady();

    int32_t getAltitude();
    int32_t getLatitude();
    int32_t getLongitude();

    uint16_t getYear();
    uint8_t getMonth();
    uint8_t getDay();
    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();

    bool Callback();
    bool OnEnable();
    void OnDisable();
    bool CheckStatus();
};

#endif