#include <rocat_change_state.h>

CHANGE_STATE::CHANGE_STATE(Transceiver *transceiver,
                           IMU *imu,
                           Barometer *barometer,
                           GPS *gps,
                           long measurements_delay) : Task(TASK_MILLISECOND, TASK_FOREVER, &scheduler, false),
                                                      measurements_delay(measurements_delay),
                                                      previous_time(0)
{
    this->transcevier = transceiver;
    this->barometer = barometer;
    this->gps = gps;
    this->imu = imu;
}

CHANGE_STATE::~CHANGE_STATE() {}

bool CHANGE_STATE::measurementsReady()
{

    long current_time = millis();
    if (current_time - this->previous_time >= this->measurements_delay)
    {
        this->previous_time = current_time;
        return true;
    }
    return false;
}

bool CHANGE_STATE::storePressure(float pressure)
{

    float sum = 0;
    for (int i = 0; i < PRESSURE_BUFFER_SIZE; i++)
    {
        sum += this->pressure_buffer[i];
    }

    this->pressure_buffer[this->pressure_index] = pressure;
    this->pressure_index++;
    this->pressure_index = (this->pressure_index >= PRESSURE_BUFFER_SIZE) ? 0 : this->pressure_index;

    return (sum / PRESSURE_BUFFER_SIZE < pressure) ? true : false;
}

bool CHANGE_STATE::Callback()
{
    long current_time = millis();
    if (measurementsReady())
    {
        State event = PRELAUNCH;
        float height, accZ, pressure, temperature;
        bool descent;

        // Data Collection
        pressure = this->barometer->getPressure();
        temperature = this->barometer->getTemperature();
        height = this->gps->getAltitude();
        accZ = this->imu->getAccelerationZ() * G_FACTOR;

        descent = storePressure(pressure);

        // State Updates
        switch (current_state)
        {
        case PRELAUNCH:
            if (this->transcevier->getButton() == PRELAUNCH_BUTTON)
            {
                current_state = LAUNCH_READY;
                this->transcevier->buttonNone();
            }
            else if (this->transcevier->getButton() == END_BUTTON)
            {
                current_state = END;
                this->transcevier->buttonNone();
            }
            break;

        case LAUNCH_READY:
            if (this->transcevier->getButton() == LAUNCH)
            {
                current_state = POWERED_FLIGHT;
                this->transcevier->buttonNone();
            }
            else if (this->transcevier->getButton() == END_BUTTON)
            {
                current_state = END;
                this->transcevier->buttonNone();
            }
            else if (accZ > LAUNCH_ACC_THRESHOLD)
            {
                current_state = POWERED_FLIGHT;
            }
            break;

        case POWERED_FLIGHT:
            if (accZ < BURNOUT_ACC_THRESHOLD)
            {
                /* Change the state */
                current_state = UNPOWERED_FLIGHT;
            }
            break;

        case UNPOWERED_FLIGHT:
            if (descent)
            {
                current_state = POST_DROUGE;
            }
            break;

        case POST_DROUGE:
            if (height < AGL_THRESHOLD)
            {
                /* Change the state */
                current_state = POST_MAIN;
            }
            else if (this->transcevier->getButton() == END_BUTTON)
            {
                current_state = END;
                this->transcevier->buttonNone();
            }
            break;

        case POST_MAIN:
            if (!descent)
            {
                current_state = END;
            }
            else if (this->transcevier->getButton() == END_BUTTON)
            {
                current_state = END;
                this->transcevier->buttonNone();
            }
            break;

        case END:
            if (this->transcevier->getButton() == PRELAUNCH_BUTTON)
            {
                current_state = PRELAUNCH;
                this->transcevier->buttonNone();
            }
            else if (this->transcevier->getButton() == WRITE_SD)
            {
                current_state = SD_WRITE;
                this->transcevier->buttonNone();
            }
            break;
        }
    }

    return false;
}

bool CHANGE_STATE::OnEnable()
{
    return true;
}

void CHANGE_STATE::OnDisable()
{
}