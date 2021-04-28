#include "Arduino.h"

const char ADDR[] = { 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52 };
const char DATA[] = { 23, 25, 27, 29, 31, 33, 35, 37 };
const int RWB = 53;
const int CLOCK = 21;

void setup() {
  for (int n = 0; n < 16; ++n) {
    pinMode(ADDR[n], INPUT);
  }
  for (int n = 0; n < 8; ++n) {
    pinMode(DATA[n], INPUT);
  }
  pinMode(RWB, INPUT);
  pinMode(CLOCK, INPUT);

  attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING);

  Serial.begin(57600);
  Serial.println("Starting...");
}

void loop() {
  //
}

void onClock() {
  char output[15];

  unsigned int address = 0;
  for (int n = 0; n < 16; ++n) {
    int bit = digitalRead(ADDR[n]) ? 1 : 0;
    Serial.print(bit);
    address = (address << 1) + bit;
  }

  Serial.print("  ");

  unsigned int data = 0;
  for (int n = 0; n < 8; ++n) {
    int bit = digitalRead(DATA[n]) ? 1 : 0;
    Serial.print(bit);
    data = (data << 1) + bit;
  }

  sprintf(output, "  %04x  %c  %02x", address, digitalRead(RWB) ? 'r' : 'w', data);
  Serial.println(output);
}
