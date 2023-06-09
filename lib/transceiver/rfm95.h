//Not finished

// #ifndef RFM95_H
// #define RFM95_H

// #include <SPI.h>
// #include <RH_RF95.h>
// #include <scheduler.h>

// #define RF95_FREQ 915.0
// #define PREAMBLE_LEN 8

// // #define RF95_CS PE11
// // #define RF95_INT PB11
// // #define RF95_RST PF15
// // #define RF95_MOSI PE14
// // #define RF95_MISO PE13
// // #define RF95_SCK PE12

// enum Button
// {
//     NONE,
//     PRELAUNCH_BUTTON,
//     LAUNCH,
//     DROGUE,
//     MAIN,
//     END,
//     RESET
// };

// class Transceiver : public Task
// {
// private:
//     RH_RF95 *driver;
//     uint8_t *output_buffer[128];
//     uint8_t buffer[RH_RF95_MAX_MESSAGE_LEN];
//     long measurements_delay;
//     long previous_time = 0;
//     uint16_t offset = 0;
//     uint32_t packet_id = 0;
//     Button button = NONE;

// public:
//     Transceiver(int RF95_CS, int RF95_INT, long measurements_delay);
//     ~Transceiver();

//     bool timeElapsed();
//     void storeInBuffer(uint8_t *packet, int size);
//     Button getButton();
//     void buttonNone();

//     bool Callback();
//     bool OnEnable();
//     void OnDisable();
//     bool checkStatus();
// };

// #endif
