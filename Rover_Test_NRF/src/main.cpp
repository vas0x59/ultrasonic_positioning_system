#include <Arduino.h>
#include <SPI.h>
#include "RF24.h"

#define NRF_CE A4
#define NRF_CSN A5

#define NRF_CHANEL 42
// const uint64_t pipes[] = {0xF0F1F2F3F4L, };
byte addresses[][6] = {"ping","back"};
RF24 radio(NRF_CE, NRF_CSN);

void setup_nrf()
{
    radio.begin();
    delay(2);
    radio.setChannel(NRF_CHANEL);
    radio.setDataRate(RF24_1MBPS); 
    radio.setPALevel(RF24_PA_HIGH); 
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1, addresses[0]);
    
}

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}