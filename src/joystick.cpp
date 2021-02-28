#include <Arduino.h>
#include "joystick.h"

int clicked;
int yPosition;
int xPosition;

void readJoystick()
{
  yPosition = analogRead(yAxis);
  xPosition = analogRead(xAxis);
  clicked = digitalRead(joyClick);
}

