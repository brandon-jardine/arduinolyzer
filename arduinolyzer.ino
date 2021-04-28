#include "Arduino.h"

const char ADDR[] = { 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52 };
const int CLOCK = 23;

void setup() {
  for (int n = 0; n < 16; ++n) {
    pinMode(ADDR[n], INPUT);
  }
  pinMode(CLOCK, INPUT);

  attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING);

  Serial.begin(57600);
}

void loop() {
  //
}

void onClock() {
  for (int n = 0; n < 16; ++n) {
    int bit = digitalRead(ADDR[n]) ? 1 : 0;
    Serial.print(bit);
  }
  Serial.println();
}
