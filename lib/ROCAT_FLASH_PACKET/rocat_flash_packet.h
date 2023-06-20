#ifndef ROCAT_FLASH_PACKET_H
#define ROCAT_FLASH_PACKET_H

#include <rocat_scheduler.h>
#include <rocat_flash.h>

#include <rocat_gps.h>
#include <rocat_baro.h>
#include <rocat_imu.h>
#include <rocat_state.h>

#define PACKET_SIZE 37

#define PRESSURE_FACTOR 1000
#define TEMPERATURE_FACTOR 100000
#define ACCELERATION_FACTOR 1000000
#define GYRO_FACTOR 100000

class Flash_Packet : public Task
{
private:
    uint8_t *buffer;
    Flash *flash;
    GPS *gps;
    Barometer *barometer;
    IMU *imu;
    long measurements_delay;
    long previous_time = 0;

public:
    Flash_Packet(Flash *flash, IMU *imu, Barometer *barometer, GPS *gps, long measurements_delay);
    ~Flash_Packet();

    bool measurementsReady();

    bool Callback();
    bool OnEnable();
    void OnDisable();
};

#endif