#include <Arduino.h>
#include "pumps.h"

void setupPumps()
{
  int pumps[PUMPS] = {spirit1, spirit2, spirit3, spirit4, mix1, mix2, mix3, mix4, mix5, mix6, mix7, mix8};
  for (byte i = 0; i < PUMPS; i++)  
    pinMode(pumps[i], OUTPUT);
}