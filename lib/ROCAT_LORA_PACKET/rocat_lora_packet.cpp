#include <rocat_lora_packet.h>

LoRa_Packet::LoRa_Packet(Transceiver *driver, GPS *gps, Barometer *barometer, IMU *imu, long measurements_delay) : Task(TASK_MILLISECOND, TASK_FOREVER, &scheduler, false),
                                                                                                                   measurements_delay(measurements_delay),
                                                                                                                   previous_time(0)
{
    this->driver = driver;
    this->gps = gps;
    this->barometer = barometer;
    this->imu = imu;
    long measurements_delay;
}

LoRa_Packet::~LoRa_Packet() {}

bool LoRa_Packet::measurementsReady()
{
    long current_time = millis();
    if (current_time - this->previous_time >= this->measurements_delay)
    {
        this->previous_time = current_time;
        return true;
    }
    return false;
}

bool LoRa_Packet::Callback()
{
    long current_time = millis();
    if (measurementsReady())
    {
        char packet[PACKET_SIZE];
        snprintf(packet, PACKET_SIZE, "%.1d,%.4d,%.4d,%.4d,%.5d,%ld,%ld,%ld,%ld,%ld,%ld\n",
                 (int8_t)(current_state),
                 (this->gps->getAltitude()),
                 (this->gps->getLongitude()),
                 (this->gps->getLatitude()),
                 (uint16_t)(this->barometer->getPressure() * PRESSURE_FACTOR),
                 (uint16_t)(this->imu->getAccelerationX() * ACCELERATION_FACTOR),
                 (uint16_t)(this->imu->getAccelerationY() * ACCELERATION_FACTOR),
                 (uint16_t)(this->imu->getAccelerationZ() * ACCELERATION_FACTOR),
                 (uint16_t)(this->imu->getGyroX() * GYRO_FACTOR),
                 (uint16_t)(this->imu->getGyroX() * GYRO_FACTOR),
                 (uint16_t)(this->imu->getGyroX() * GYRO_FACTOR));
        this->driver->storeInBuffer((uint8_t *)packet, PACKET_SIZE);
        return true;
    };
    return false;
}

bool LoRa_Packet::OnEnable()
{
    return true;
}

void LoRa_Packet::OnDisable()
{
}
