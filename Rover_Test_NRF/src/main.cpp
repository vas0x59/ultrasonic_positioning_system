#include <Arduino.h>
#include <SPI.h>
#include "RF24.h"

#define NRF_CE A4
#define NRF_CSN A5

#define NRF_CHANEL 42
#define ECHO1_PIN 2
#define SENDING_PIN 3
#define DELAY_SENDING 40

#define DEBUG_FREQ 3.0

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
long timeStartSignal, timeEndSignal;

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
    digitalWrite(SENDING_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(SENDING_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(SENDING_PIN, LOW);

    while (digitalRead(ECHO1_PIN) == LOW)
        ;
    timeStartSignal = micros();
    timeEndSignal = micros();
    while ((digitalRead(ECHO1_PIN) == HIGH) && ((timeEndSignal - timeStartSignal) < (1000 * (DELAY_SENDING - 2))))
    {
        timeEndSignal = micros();
    }
    timeEndSignal = micros();

    // float len2 = pulseIn(ECHO1_PIN, HIGH) / 58;
    dist_to_base[base_id - 1] = ((timeEndSignal - timeStartSignal) / last_msg.sound_const) * 20.00;
}
unsigned long last_debug_t;
void setup()
{
    setup_nrf();
    // put your setup code here, to run once:
    last_debug_t = millis();
    Serial.begin(115200);
}



void loop()
{
    if (radio.available())
    {
        radio.read(&last_msg, sizeof(Radio_msg));
        us_echo(last_msg.base_id);
    }
    if ((millis() - last_debug_t) >= (1000.0 / DEBUG_FREQ)) {
        for (int i = 0; i < 4; i++)
        {
            Serial.print(" len");
            Serial.print(i+1);
            Serial.print(": ");
            Serial.print(dist_to_base[i]);
        }
        Serial.println();
    }
    // put your main code here, to run repeatedly:
}