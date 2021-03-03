#include <Arduino.h>
#include <Joystick.h>

int clicked;
int yPosition;
int xPosition;

void readJoystick()
{
  yPosition = analogRead(yAxis);
  xPosition = analogRead(xAxis);
  clicked = digitalRead(joyClick);
}

void waitForDepress()
{
  do {
    readJoystick();
  } while (clicked == 0);
}
