#include <rocat_lora_packet.h>

LoRa_Packet::LoRa_Packet(Transceiver *driver, GPS *gps, Barometer *barometer, IMU *imu, State *state, long measurements_delay) : measurements_delay(measurements_delay), previous_time(0)
{
    this->driver = driver;
    this->gps = gps;
    this->barometer = barometer;
    this->imu = imu;

    long measurements_delay;
    this->state = state;
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
        snprintf(packet, PACKET_SIZE, "%.1d,%.5d,%.4d,%.4d,%.4d,%ld,%ld,%ld",
                 (int8_t)(current_state),
                 (uint16_t)(this->barometer->getPressure()),
                 (uint16_t)(this->imu->getAccelerationX()),
                 (uint16_t)(this->imu->getAccelerationY()),
                 (uint16_t)(this->imu->getAccelerationZ()),
                 (this->gps->getAltitude()),
                 (this->gps->getLatitude()),
                 (this->gps->getLongitude()));
        this->driver->storeInBuffer((uint8_t *)packet, PACKET_SIZE);
        return true;
    }
    return false;
}

bool LoRa_Packet::OnEnable()
{
    return true;
}

void LoRa_Packet::OnDisable()
{
}
