#include <rocat_imu.h>

IMU::IMU(long measurement_delay) : measurement_delay(measurement_delay)
{
    this->Acceldriver = new Bmi088Accel(IMU_ACCEL, IMU_SPI_CS_ACCEL);
    this->Gyrodriver = new Bmi088Gyro(IMU_GYRO, IMU_SPI_CS_GYRO);
};

IMU::~IMU(){};

bool IMU::measurementReady()
{
    long current_time = millis();
    if (current_time - this->previous_time >= this->measurement_delay)
    {
        this->previous_time = current_time;
        return true;
    }
    return false;
}

float IMU::getAccelerationX()
{
    return acc_x;
}

float IMU::getAccelerationY()
{
    return acc_y;
}

float IMU::getAccelerationZ()
{
    return acc_z;
}

float IMU::getGyroX()
{
    return gyro_x;
}

float IMU::getGyroY()
{
    return gyro_y;
}

float IMU::getGyroZ()
{
    return gyro_z;
}

bool IMU::Callback()
{
    if (measurementReady())
    {
        this->Acceldriver->begin();
        this->Acceldriver->readSensor();
        this->Gyrodriver->begin();
        this->Gyrodriver->readSensor();
        return true;
    }
    return false;
}

bool IMU::OnEnable()
{
    this->Acceldriver->begin();
    this->Gyrodriver->begin();
    return true;
}

void IMU::OnDisable()
{
}

bool IMU::CheckStatus()
{
    bool Accelstatus = this->Acceldriver->getDrdyStatus();
    bool Gyrostatus = this->Gyrodriver->getDrdyStatus();
    return (Accelstatus && Gyrostatus);
}