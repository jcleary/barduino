#include <Arduino.h>
#include "pumps.h"

void setupPumps() {
  pinMode(spirit1, OUTPUT);
  pinMode(spirit2, OUTPUT);
  pinMode(spirit3, OUTPUT);
  pinMode(spirit4, OUTPUT);

  pinMode(mix1, OUTPUT);
  pinMode(mix2, OUTPUT);
  pinMode(mix3, OUTPUT);
  pinMode(mix4, OUTPUT);
  pinMode(mix5, OUTPUT);
  pinMode(mix6, OUTPUT);
  pinMode(mix7, OUTPUT);
  pinMode(mix8, OUTPUT);   
}