#ifndef ROCAT_PACKET_H
#define ROCAT_PACKET_H

#include <scheduler.h>
#include <SPI.h>
#include <Arduino.h>
#include <rocat_lora.h>
#include <rocat_gps.h>
#include <rocat_baro.h>
#include <rocat_imu.h>

#define PACKET_SIZE 128

class Packet : public Task
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
    Packet(Transceiver *transceiver, IMU *imu, Barometer *barometer, GPS *gps, long measurements_delay);
    ~Packet();

    bool measurementsReady();

    bool Callback();
    bool OnEnable();
    void OnDisable();
};

#endif