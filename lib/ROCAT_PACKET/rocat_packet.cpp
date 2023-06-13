#include <rocat_packet.h>

Packet::Packet(Transceiver *driver, IMU *imu, Barometer *barometer, GPS *gps, long measurements_delay) : Task(TASK_MILLISECOND, TASK_FOREVER, &scheduler, false), measurements_delay(measurements_delay), previous_time(0)
{
    this->driver = driver;
    this->barometer = barometer;
    this->gps = gps;
    this->imu = imu;
}

Packet::~Packet() {}

bool Packet::measurementsReady()
{

    long current_time = millis();
    if (current_time - this->previous_time >= this->measurements_delay)
    {
        this->previous_time = current_time;
        return true;
    }
}

bool Packet::Callback()
{
    long current_time = millis();
    if (measurementsReady())
    {
        char packet[PACKET_SIZE];
        snprintf(packet, PACKET_SIZE, "%.1d,%.5d,%.4d,%.4d,%.4d,%.4d,%.4d,%.4d,%ld,%ld,%ld\n",
                 // Get Current state
                 0,
                 (this->barometer->getPressure()),
                 (this->imu->getAccelerationX()),
                 (this->imu->getAccelerationY()),
                 (this->imu->getAccelerationZ()),
                 (this->imu->getGyroX()),
                 (this->imu->getGyroY()),
                 (this->imu->getGyroZ()),
                 (this->gps->getAltitude()),
                 (this->gps->getLatitude()),
                 (this->gps->getLongitude()));
        this->driver->storeInBuffer((uint8_t *) packet, PACKET_SIZE);
        return true;
    };
    return false;
}

bool Packet::OnEnable()
{
    return true;
}

void Packet::OnDisable()
{
}