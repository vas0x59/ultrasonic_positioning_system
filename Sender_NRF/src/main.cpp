#include <Arduino.h>
#include <SPI.h>
#include "RF24.h"

#define TRIG1_PIN 4
#define TRIG2_PIN 5
#define TRIG3_PIN 6
#define TRIG4_PIN 7
#define ECHO1_PIN 2
#define SENDING_PIN 13

#define DELAY_SENDING 50
#define DELAY_FLIGHT 10
long timeStartSignal, timeEndSignal;

#define NRF_CE A5
#define NRF_CSN A4

#define NRF_CHANEL 42
// const uint64_t pipes[] = {0xF0F1F2F3F4L, };
byte addresses[][6] = {"ping","back"};


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
    radio.stopListening();  

    // radio.startFastWrite
    Radio_msg msg;
    msg.base_id = base_id;
    msg.sound_const = sc;
    msg.time_stamp = millis();
    radio.write(&msg, sizeof(Radio_msg));
}
void setup_nrf()
{
    Serial.println("SETUP NRF START");
    radio.begin();
    delay(2);
    radio.setChannel(NRF_CHANEL);
    radio.setDataRate(RF24_2MBPS); 
    radio.setPALevel(RF24_PA_HIGH); 
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
    Serial.println("SETUP NRF END");


    
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
    Serial.println("Send US");
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
    setup_nrf();
}

void loop()
{
    send_nrf(0, sound_const);
    delay(DELAY_FLIGHT);
    send_us(TRIG1_PIN);
    
    delay(DELAY_SENDING);

    send_nrf(1, sound_const);
    delay(DELAY_FLIGHT);
    send_us(TRIG2_PIN);
    
    delay(DELAY_SENDING);

    send_nrf(2, sound_const);
    delay(DELAY_FLIGHT);
    send_us(TRIG3_PIN);
    
    delay(DELAY_SENDING);

    send_nrf(3, sound_const);
    delay(DELAY_FLIGHT);
    send_us(TRIG4_PIN);
    
    delay(DELAY_SENDING);
    // Serial
    // Serial.println(String(len2) + " " + String(len3));

    // put your main code here, to run repeatedly:
}