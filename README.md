TODO:
Initial:
Set up taskscheduler


### Logical Operations:
Since TaskScheduler will be executing each function seperately they can be coded as seperate functions
- Data Pulling:
    - BarometerPull
    - CurrentPull
    - IMUPull
    - LoRa Receive (interrupt)?
    - Pull from any attached sensors
- Data Writing:
    - Write to Flash
        Does not necessarily need to be with every read loop, can be after <256 bytes needs to be stored for optimal timing
    - Write to SD (after landing)
        Depends on state determination
    - Ping back ground station with health
- Misc:
    - State Determination (i.e. when should it start recording and when to stop and write to flash)
    - State Indicaton (i.e. buzzer etc)
    - Actuation with state for payload or flight actions


## Libraries
Managed by PlatformIO:
    Barometer - pololu/LPS@^3.0.1
    Buzzer - arduinogetstarted/ezBuzzer@^1.0.0
    Current - adafruit/Adafruit INA219@^1.2.1
    Flash - lowpowerlab/SPIFlash@^101.1.3
    GNSS - sparkfun/SparkFun u-blox GNSS Arduino Library@^2.2.22
    LoRa - lowpowerlab/RFM69@^1.5.2
    PWM - robtillaart/PCA9634@^0.2.7
    SD - adafruit/SD@0.0.0-alpha+sha.041f788250
    Scheduler - arkhipenko/TaskScheduler@^3.7.0

Manually Added in lib folder:
    IMU - LIS2DW12 2.1.0 - https://github.com/stm32duino/LIS2DW12

Related Wikis:
    https://github.com/arkhipenko/TaskScheduler/wiki