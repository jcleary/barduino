#include <Arduino.h>
#include "pumps.h"

byte pumpPin1(byte pumpNo);
byte pumpPin2(byte pumpNo);

void setupPumps()
{
  for (byte pumpNo = 0; pumpNo < PUMPS; pumpNo++)
  {
    pinMode(pumpPin1(pumpNo), OUTPUT);
    pinMode(pumpPin2(pumpNo), OUTPUT);
  }
}

void pumpOn(byte pumpNo)
{
  Serial.println("Pump " + String(pumpNo) + " on");
  digitalWrite(pumpPin1(pumpNo), HIGH);
  digitalWrite(pumpPin2(pumpNo), LOW);
}

void pumpOff(byte pumpNo)
{
  Serial.println("Pump " + String(pumpNo) + " off");
  digitalWrite(pumpPin1(pumpNo), LOW);
  digitalWrite(pumpPin2(pumpNo), LOW);
}

void pumpReverse(byte pumpNo)
{
  Serial.println("Pump " + String(pumpNo) + " reverse");
  digitalWrite(pumpPin1(pumpNo), LOW);
  digitalWrite(pumpPin2(pumpNo), HIGH);
}

byte pumpPin1(byte pumpNo)
{
  return pump0pin0 + (pumpNo * 2);
}

byte pumpPin2(byte pumpNo)
{
  return pumpPin1(pumpNo) + 1;
}