#ifndef ROCAT_IMU
#define ROCAT_IMU

#include <SPI.h>
#include <BMI088.h>
#include <scheduler.h>

#define IMU_GYRO_INT1 PB12
#define IMU_GYRO_INT2 PD8
#define IMU_ACCEL_INT1 PD11
#define IMU_ACCEL_INT2 PD12
#define IMU_SPI_SCK PB13
#define IMU_SPI_MISO PB14
#define IMU_SPI_MOSI PB15
#define IMU_SPI_CS_ACCEL PD9
#define IMU_SPI_CS_GYRO PD13

SPIClass IMU_ACCEL = SPIClass(IMU_SPI_MOSI, IMU_SPI_MISO, IMU_SPI_SCK);
SPIClass IMU_GYRO = SPIClass(IMU_SPI_MOSI, IMU_SPI_MISO, IMU_SPI_SCK);

class IMU : public Task
{
private:
    Bmi088Accel *Acceldriver;
    Bmi088Gyro *Gyrodriver;
    long measurement_delay;
    long previous_time = 0;
    float acc_x, acc_y, acc_z;
    float gyro_x, gyro_y, gyro_z;

public:
    IMU(long measurement_delay);
    ~IMU();

    bool measurementReady();

    float getAccelerationX();
    float getAccelerationY();
    float getAccelerationZ();

    float getGyroX();
    float getGyroY();
    float getGyroZ();

    bool Callback();
    bool OnEnable();
    void OnDisable();
    bool checkStatus();
};

#endif