#include <Arduino.h>
#include <Pumps.h>
#include <Pump.h>

Pump pumps[PUMPS];

void pumpOn(byte pumpNo)
{
  pumps[pumpNo].on();
}

void pumpOff(byte pumpNo)
{
  pumps[pumpNo].off();
}

void allPumpOff()
{
  for (byte i = 0; i < PUMPS; i++)
    pumpOff(i);
}

void pumpReverse(byte pumpNo)
{
  pumps[pumpNo].reverse();
}

