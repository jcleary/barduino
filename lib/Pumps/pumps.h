#pragma once
#include <Arduino.h>
#include <Pump.h>

const int PUMPS = 8;

extern Pump pumps[PUMPS];

void pumpOn(byte pumpNo);
void pumpOff(byte pumpNo);
void pumpReverse(byte pumpNo);
void allPumpOff();
