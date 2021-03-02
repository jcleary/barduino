#pragma once
#include <Arduino.h>

// pins
const int yAxis = 7;
const int xAxis = 6;
const int joyClick = 52;

// thresholds
const int upThreshold = 422;
const int downThreshold = 622;
const int leftThreshold = 422;
const int rightThreshold = 622;

extern int clicked;
extern int yPosition;
extern int xPosition;

void readJoystick();
void waitForDepress();
