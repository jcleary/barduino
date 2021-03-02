#pragma once
#include <Arduino.h>

const int PUMPS = 8;

const byte pump0pin0 = 30;

void setupPumps();
void pumpOn(byte pumpNo);
void pumpOff(byte pumpNo);
void pumpReverse(byte pumpNo);
