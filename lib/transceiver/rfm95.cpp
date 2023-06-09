//Not finished

// #include <rfm95.h>

// Transceiver::Transceiver(int RF95_CS, int RF95_INT, long measurement_delay) : Task(TASK_MILLISECOND, TASK_FOREVER, &scheduler, false),
//                                                                               measurements_delay(measurement_delay), previous_time(0)
// {
//     this->driver = new RH_RF95(RF95_CS, RF95_INT);
// }

// Transceiver::~Transceiver() {}

// bool Transceiver::timeElapsed()
// {
//     long current_time = millis();
//     if (current_time - this->previous_time >= this->measurements_delay)
//     {
//         this->previous_time = current_time;
//         return true;
//     }
//     return false;
// }

// void Transceiver::storeInBuffer(uint8_t *packet, int size)
// {
//     memcpy(this->output_buffer, packet, size);
// }

// Button Transceiver::getButton()
// {
//     return this->button;
// }

// void Transceiver::buttonNone()
// {
//     this->button = NONE;
// }

// bool Transceiver::Callback()
// {

//     long current_time = millis();

//     if (timeElapsed())
//     {
//         if (this->offset == 0)
//         {
//             char message[RH_RF95_MAX_MESSAGE_LEN];
//             snprintf(message, sizeof(message), "ooo\n", this->packet_id);
//             memcpy(message + PREAMBLE_LEN, (char *)this->output_buffer + this->offset, 45);
//             Serial.write(message, 45 + PREAMBLE_LEN);
//             Serial.println();
//             this->driver->send((uint8_t *)message, 45 + PREAMBLE_LEN);
//             this->driver->waitPacketSent();
//             this->offset = 46;
//         }
//     }

//     if (this->driver->available())
//     {
//         uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
//         uint8_t len = sizeof(buf);
//         if (this->driver->recv(buf, &len))
//         {
//             if (!len)
//                 return false;
//             Serial.println((char *)buf);
//             buf[len] = 0;
//         }

//         if (strcmp((char *)buf, "prelaunch") == 0)
//         {
//             this-> button = PRELAUNCH_BUTTON;
//         }
//         else if (strcmp((char *)buf, "launch") == 0)
//         {
//             this->button = LAUNCH;
//         }
//         else if (strcmp((char *)buf, "end") == 0)
//         {
//             this->button = END;
//         }
//         else if (strcmp((char *)buf, "drogue") == 0)
//         {
//             this->button = DROGUE;
//         }
//         else if (strcmp((char *)buf, "main") == 0)
//         {
//             this->button = MAIN;
//         }
//         else if (strcmp((char *)buf, "reset") == 0)
//         {
//             this->button = RESET;
//             NVIC_SystemReset();
//             Serial.println("Reset!");
//             Serial.println();
//         }
//     }
//     return true;
// }

// bool Transceiver::OnEnable()
// {
//     if (!(this->driver->setFrequency(RF95_FREQ)))
//     {
//         return false;
//     }

//     // range from 14-20 for power, 2nd arg must be false for 69HCW
//     this->driver->setTxPower(20, true);


//     return true;
// }
