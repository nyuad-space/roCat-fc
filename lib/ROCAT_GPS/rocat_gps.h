#ifndef ROCAT_GPS
#define ROCAT_GPS

#include <Wire.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <scheduler.h>

#define GNSS_I2C_SCL PA8
#define GNSS_I2C_SDA PC9
#define GNSS_I2C_RST PD10

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
    uint16_t getMonth();
    uint16_t getDay();
    uint16_t getHour();
    uint16_t getMinute();
    uint16_t getSecond();

    bool Callback();
    bool onEnable();
    void onDisable();
    bool checkStatus();
};

#endif