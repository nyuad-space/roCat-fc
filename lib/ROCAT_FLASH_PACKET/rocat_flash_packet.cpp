#include <rocat_flash_packet.h>

Flash_Packet::Flash_Packet(Flash *flash, IMU *imu, Barometer *barometer, GPS *gps, long measurements_delay) : Task(TASK_MILLISECOND, TASK_FOREVER, &scheduler, false),
                                                                                                              measurements_delay(measurements_delay),
                                                                                                              previous_time(0)
{
    this->flash = flash;
    this->barometer = barometer;
    this->gps = gps;
    this->imu = imu;
}

Flash_Packet::~Flash_Packet() {}

bool Flash_Packet::measurementsReady()
{

    long current_time = millis();
    if (current_time - this->previous_time >= this->measurements_delay)
    {
        this->previous_time = current_time;
        return true;
    }
}

bool Flash_Packet::Callback()
{
    long current_time = millis();
    if (measurementsReady())
    {
        char packet[PACKET_SIZE];
        snprintf(packet, PACKET_SIZE, "%.1d,%.5d,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld\n",
                 (int8_t)(current_state),
                 (this->barometer->getPressure() * PRESSURE_FACTOR),
                 (this->imu->getAccelerationX() * ACCELERATION_FACTOR),
                 (this->imu->getAccelerationY() * ACCELERATION_FACTOR),
                 (this->imu->getAccelerationZ() * ACCELERATION_FACTOR),
                 (this->imu->getGyroX() * GYRO_FACTOR),
                 (this->imu->getGyroY() * GYRO_FACTOR),
                 (this->imu->getGyroZ() * GYRO_FACTOR),
                 (this->gps->getAltitude()),
                 (this->gps->getLatitude()),
                 (this->gps->getLongitude()));
        this->flash->storeInBuffer((int8_t *)packet, PACKET_SIZE);
        return true;
    };
    return false;
}

bool Flash_Packet::OnEnable()
{
    return true;
}

void Flash_Packet::OnDisable()
{
}