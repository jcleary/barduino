#include <Arduino.h>
#include "pumps.h"

void setupPumps()
{  
  for (byte i = 0; i < PUMPS; i++) {
    pinMode(pump0pin0 + (i * 2), OUTPUT);
    pinMode(pump0pin0 + (i * 2) + 1, OUTPUT);
  }
}

void pumpOn(byte pumpNo) {
  Serial.println("Pump " + String(pumpNo) + " on");
  digitalWrite(pumpPin1(pumpNo), HIGH);
  digitalWrite(pumpPin2(pumpNo), LOW); 
}

void pumpOff(byte pumpNo) {
  Serial.println("Pump " + String(pumpNo) + " off");
  digitalWrite(pumpPin1(pumpNo), LOW);
  digitalWrite(pumpPin2(pumpNo), LOW); 
}

void pumpReverse(byte pumpNo) {
  Serial.println("Pump " + String(pumpNo) + " reverse");
  digitalWrite(pumpPin1(pumpNo), LOW);
  digitalWrite(pumpPin2(pumpNo), HIGH); 
}


byte pumpPin1(byte pumpNo) {
  return pump0pin0 + (pumpNo * 2);
}

byte pumpPin2(byte pumpNo) {
  return pumpPin1(pumpNo) + 1;
}