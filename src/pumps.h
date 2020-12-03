#pragma once
#include <Arduino.h>

const byte spirit1 = 2;
const byte spirit2 = 3;
const byte spirit3 = 4;
const byte spirit4 = 5;

const byte mix1 = 6;
const byte mix2 = 7;
const byte mix3 = 8;
const byte mix4 = 9;
const byte mix5 = 10;
const byte mix6 = 11;
const byte mix7 = 12;
const byte mix8 = 13;

// Spirits
const byte vodka = spirit1;
const byte gin = spirit2;

// Mixers
const byte coke = mix1;
const byte tonic = mix2;
const byte lemonade = mix8;

const byte PUMPS = 12;

void setupPumps();