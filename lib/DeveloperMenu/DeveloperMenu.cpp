#include <Arduino.h>
#include <DeveloperMenu.h>
#include <Joystick.h>
#include <Pumps.h>
#include <PumpMenu.h>

DeveloperMenu::DeveloperMenu()
{
  title = "  Developer menu";
  items[itemCount++] = "Prime";
  items[itemCount++] = "Purge";
  items[itemCount++] = "Exit";
  exitItemNo = 2;
}

void DeveloperMenu::selectItem()
{
  switch (selection)
  {
  case 0:
    showPumpMenu("Prime");
    break;

  case 1:
    showPumpMenu("Purge");
    break;
  }
}

void DeveloperMenu::showPumpMenu(String verb)
{
  PumpMenu menu("Purge");
  menu.lcd = lcd;
  menu.start();
}

