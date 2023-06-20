#ifndef ROCAT_LORA_PACKET_H
#define ROCAT_LORA_PACKET_H

#include <rocat_scheduler.h>
#include <rocat_lora.h>

#include <rocat_gps.h>
#include <rocat_baro.h>
#include <rocat_imu.h>
#include <rocat_state.h>

#define PACKET_SIZE 31

#define PRESSURE_FACTOR 10
#define TEMPERATURE_FACTOR 1000
#define ACCELERATION_FACTOR 10000
#define GYRO_FACTOR 1000

class LoRa_Packet : public Task
{
private:
    uint8_t *buffer;
    Transceiver *driver;
    GPS *gps;
    Barometer *barometer;
    IMU *imu;
    long measurements_delay;
    long previous_time = 0;

public:
    LoRa_Packet(Transceiver *Transceiver, GPS *gps, Barometer *barometer, IMU *imu, long measurements_delay);
    ~LoRa_Packet();

    bool measurementsReady();

    bool Callback();
    bool OnEnable();
    void OnDisable();
};

#endif