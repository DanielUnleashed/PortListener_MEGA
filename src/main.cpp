#include <Arduino.h>

#define CLOCK 50
#define RWB 52
#define ADDRESS_START 23
#define DATA_START 24

void setup() {
  Serial.begin(9600);

  pinMode(CLOCK, INPUT);
  pinMode(RWB, INPUT);

  for(uint8_t i = 0; i < 16; i++) pinMode(ADDRESS_START + i*2, INPUT);

  for(uint8_t i = 0; i < 8; i++) pinMode(DATA_START + i*2, INPUT);

  Serial.println("Port Listener START!");
}

bool lastClockState = false;

void loop() {
  bool currentClockState = digitalRead(CLOCK);
  // Print on HIGH rise
  if(currentClockState != lastClockState && currentClockState){
    uint16_t address = 0;
    for(uint8_t i = 0; i < 16; i++){
      uint16_t bit = digitalRead(ADDRESS_START+i*2);
      address = address | (bit<<i);
      Serial.print(bit);
    }
  
    Serial.print("\t");

    uint8_t data = 0;
    for(uint8_t i = 0; i < 8; i++){
      uint8_t bit = digitalRead(DATA_START+i*2);
      data = (data << 1) | bit;
      Serial.print(bit);
    }

    char readOrWrite = digitalRead(RWB)?'r':'w';

    char output[50];
    sprintf(output, "\tAdd: %04x\tData: %02x\t%c\n", address, data, readOrWrite);
    Serial.print(output);
  }
  lastClockState = currentClockState;
}

