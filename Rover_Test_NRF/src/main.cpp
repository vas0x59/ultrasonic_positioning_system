#include <Arduino.h>
#include <SPI.h>
#include "RF24.h"

#define NRF_CE A4
#define NRF_CSN A5

#define NRF_CHANEL 42

struct Radio_msg
{
    int base_id;
    float sound_const;
    unsigned long time_stamp;
};

Radio_msg last_msg;
// const uint64_t pipes[] = {0xF0F1F2F3F4L, };
byte addresses[][6] = {"ping", "back"};
RF24 radio(NRF_CE, NRF_CSN);

float dist_to_base[4] = {0, 0, 0, 0};

void setup_nrf()
{
    radio.begin();
    delay(2);
    radio.setChannel(NRF_CHANEL);
    radio.setDataRate(RF24_1MBPS);
    radio.setPALevel(RF24_PA_HIGH);
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1, addresses[0]);
    radio.startListening();
}

void us_echo(int base_id)
{
}

void setup()
{
    setup_nrf();
    // put your setup code here, to run once:
}

void loop()
{
    if (radio.available())
    {
        radio.read(&last_msg, sizeof(Radio_msg));
        us_echo(last_msg.base_id);
    }
    // put your main code here, to run repeatedly:
}