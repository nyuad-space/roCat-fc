#include <rocat_lora.h>

Transceiver::Transceiver(long measurement_delay) : measurements_delay(measurement_delay),
                                                   previous_time(0)
{
    this->LoRa = new RH_RF69(LORA_SPI_CS, LORA_SPI_INT);
}

Transceiver::~Transceiver() {}

bool Transceiver::timeElapsed()
{
    long current_time = millis();
    if (current_time - this->previous_time >= this->measurements_delay)
    {
        this->previous_time = current_time;
        return true;
    }
    return false;
}

void Transceiver::storeInBuffer(uint8_t *packet, int size)
{
    memcpy(this->output_buffer, packet, size);
}

bool Transceiver::Callback()
{
    long current_time = millis();

    if (timeElapsed())
    {
        if (this->offset == 0)
        {
            char message[RH_RF69_MAX_MESSAGE_LEN];
            snprintf(message, sizeof(message), "#%.4ld:0\n", this->packet_id);
            memcpy(message + PREAMBLE_LEN, (char *)this->output_buffer + this->offset, 45);
            Serial.write(message, 45 + PREAMBLE_LEN);
            Serial.println();
            this->LoRa->send((uint8_t *)message, 45 + PREAMBLE_LEN);
            this->LoRa->waitPacketSent();
            this->offset = 0;
            this->packet_id++;
        }

        if (this->LoRa->available())
        {
            uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
            uint8_t len = sizeof(buf);
            if (this->LoRa->recv(buf, &len))
            {
                if (!len)
                    return false;
                Serial.println((char *)buf);
            }
        }
    }
    return true;
}

bool Transceiver::OnEnable()
{
    if (!(this->LoRa->setFrequency(LORA_FREQ)))
    {
        return false;
    }

    // range from 14-20 for power, 2nd arg must be true for 69HCW
    this->LoRa->setTxPower(20, true);

    // The encryption key has to be the same as the one in the server
    uint8_t key[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                     0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    this->LoRa->setEncryptionKey(key);

    return true;
}

void Transceiver::OnDisable()
{
    delete this->buffer;
    delete this->LoRa;
}

bool Transceiver::CheckStatus()
{
    return this->LoRa->init();
}