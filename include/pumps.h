#pragma once
#include <Arduino.h>

const byte vodka      = 0;
const byte orange     = 1;
const byte gin        = 2;
const byte coke       = 3;
const byte tonic      = 4;
const byte lemonade   = 5;

const int PUMPS = 8;

const byte pump0pin0 = 30;

void setupPumps();
void pumpOn(byte pumpNo);
void pumpOff(byte pumpNo);
void pumpReverse(byte pumpNo);
byte pumpPin1(byte pumpNo);
byte pumpPin2(byte pumpNo);