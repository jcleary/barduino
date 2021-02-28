#pragma once
#include <Arduino.h>

const byte vodka          = 0;
const byte gin            = 1;
const byte peach_schnapps = 2;

const byte cranberry  = 5;
const byte orange     = 6;
const byte tonic      = 7;

const int PUMPS = 8;

const byte pump0pin0 = 30;

void setupPumps();
void pumpOn(byte pumpNo);
void pumpOff(byte pumpNo);
void pumpReverse(byte pumpNo);
