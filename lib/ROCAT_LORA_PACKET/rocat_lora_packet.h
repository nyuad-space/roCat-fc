#ifndef ROCAT_LORA_PACKET_H
#define ROCAT_LORA_PACKET_H

#include <rocat_lora.h>

#include <rocat_gps.h>
#include <rocat_baro.h>
#include <rocat_imu.h>
#include <rocat_state.h>

#define PACKET_SIZE 0

class LoRa_Packet
{
private:
    uint8_t *buffer;
    Transceiver *driver;
    GPS *gps;
    Barometer *barometer;
    IMU *imu;
    State *state;

    long measurements_delay;
    long previous_time = 0;

public:
    LoRa_Packet(Transceiver *Transceiver, GPS *gps, Barometer *barometer, IMU *imu, State *state, long measurements_delay);
    ~LoRa_Packet();

    bool measurementsReady();

    bool Callback();
    bool OnEnable();
    void OnDisable();
};

#endif