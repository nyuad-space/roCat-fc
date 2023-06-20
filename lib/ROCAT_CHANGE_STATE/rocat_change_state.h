#ifndef ROCAT_CHANGE_STATE_H
#define ROCAT_CHANGE_STATE_H

#include <rocat_scheduler.h>
#include <SPI.h>
#include <Arduino.h>
#include <rocat_baro.h>
#include <rocat_imu.h>
#include <rocat_gps.h>
#include <rocat_state.h>
#include <rocat_lora.h>

/*** Factors ***/
#define PRESSURE_FACTOR 10
#define TEMPERATURE_FACTOR 1000
#define ACCELERATION_FACTOR 10000
#define GYRO_FACTOR 1000
#define LAUNCH_ACC_THRESHOLD 20
#define BURNOUT_ACC_THRESHOLD 2
#define AGL_THRESHOLD 1000
#define PRESSURE_BUFFER_SIZE 5
#define G_FACTOR 9.80665

class CHANGE_STATE : public Task
{
private:
    uint8_t *buffer;
    float pressure_buffer[PRESSURE_BUFFER_SIZE] = {2000};
    Transceiver *transcevier;
    Barometer *barometer;
    GPS *gps;
    IMU *imu;
    State *state;
    int pressure_index = 0;
    long measurements_delay;
    long previous_time = 0;

public:
    CHANGE_STATE(
        Transceiver *transceiver,
        IMU *imu,
        Barometer *barometer,
        GPS *gps,
        long measurements_delay);
    ~CHANGE_STATE();

    bool measurementsReady();
    bool storePressure(float pressure_5);

    // Task virtual methods
    bool Callback();
    bool OnEnable();
    void OnDisable();
};

// enum Event
// {
//     PRELAUNCH,
//     LAUNCH_READY,
//     POWERED_FLIGHT,
//     UNPOWERED_FLIGHT,
//     POST_DROGUE,
//     POST_MAIN,
//     END,
//     SD_WRITE
// };

#endif