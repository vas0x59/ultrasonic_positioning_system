#include <Arduino.h>
#include <SPI.h>
#include "RF24.h"

#define TRIG1_PIN 4
#define TRIG2_PIN 5
#define TRIG3_PIN 6
#define TRIG4_PIN 7
#define ECHO1_PIN 2
#define SENDING_PIN 13

#define DELAY_SENDING 40

long timeStartSignal, timeEndSignal;

#define NRF_CE A4
#define NRF_CSN A5

#define NRF_CHANEL 42

RF24 radio(NRF_CE, NRF_CSN);
float sound_const = 58.0;

struct Radio_msg
{
    int base_id;
    float sound_const;
    unsigned long time_stamp;
};


void send_nrf(int base_id, float sc)
{
    Radio_msg msg;
    msg.base_id = base_id;
    msg.sound_const = sc;
    msg.time_stamp = millis();
    radio.write(&msg, sizeof(msg));
}
void setup_nrf()
{
    radio.begin();
    delay(2);
    radio.setChannel(NRF_CHANEL);
    radio.setDataRate(RF24_1MBPS); 
    radio.setPALevel(RF24_PA_HIGH); 

}

void send_us(int pin)
{
    digitalWrite(SENDING_PIN, LOW);
    digitalWrite(pin, LOW);
    delayMicroseconds(2);
    digitalWrite(SENDING_PIN, HIGH);
    digitalWrite(pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(SENDING_PIN, LOW);
    digitalWrite(pin, LOW);
}

void setup()
{
    // put your setup code here, to run once:
    pinMode(TRIG1_PIN, OUTPUT);
    pinMode(TRIG2_PIN, OUTPUT);
    pinMode(TRIG3_PIN, OUTPUT);
    pinMode(TRIG4_PIN, OUTPUT);
    pinMode(SENDING_PIN, OUTPUT);
    pinMode(ECHO1_PIN, INPUT);
    Serial.begin(115200);
}

void loop()
{
    send_us(TRIG1_PIN);
    send_nrf(1, sound_const);
    delay(DELAY_SENDING);
    send_us(TRIG2_PIN);
    send_nrf(2, sound_const);
    delay(DELAY_SENDING);
    send_us(TRIG3_PIN);
    send_nrf(3, sound_const);
    delay(DELAY_SENDING);
    send_us(TRIG4_PIN);
    send_nrf(4, sound_const);
    delay(DELAY_SENDING);
    // Serial.println(String(len2) + " " + String(len3));

    // put your main code here, to run repeatedly:
}