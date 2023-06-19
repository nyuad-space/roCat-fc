#ifndef ROCAT_FLASH_PACKET_H
#define ROCAT_FLASH_PACKET_H

#include <rocat_flash.h>

#include <rocat_gps.h>
#include <rocat_baro.h>
#include <rocat_imu.h>
#include <rocat_state.h>

#define PACKET_SIZE 128

class Flash_Packet
{
private:
    uint8_t *buffer;
    Flash *flash;
    GPS *gps;
    Barometer *barometer;
    IMU *imu;
    State *state;

    long measurements_delay;
    long previous_time = 0;

public:
    Flash_Packet(Flash *flash, IMU *imu, Barometer *barometer, GPS *gps, State *state, long measurements_delay);
    ~Flash_Packet();

    bool measurementsReady();

    bool Callback();
    bool OnEnable();
    void OnDisable();
};

#endif