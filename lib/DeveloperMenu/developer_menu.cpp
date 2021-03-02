#include <Arduino.h>
#include "developer_menu.h"
#include "joystick.h"
#include "pumps.h"

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
    primeAllPumps();
    break;

  case 1:
    purgeAllPumps();
    break;
  }
}

void DeveloperMenu::primeAllPumps()
{
  lcd->clear();
  lcd->setCursor(6, 1);
  lcd->print("Priming");

  lcd->setCursor(6, 3);
  lcd->print("[ Stop ]");

  for (byte i = 0; i < PUMPS; i++)
    pumpOn(i);

  do
  {
    readJoystick();
  } while (clicked != 0);
  waitForDepress();

  for (byte i = 0; i < PUMPS; i++)
    pumpOff(i);
}

void DeveloperMenu::purgeAllPumps()
{
  lcd->clear();
  lcd->setCursor(6, 1);
  lcd->print("Purging");

  lcd->setCursor(6, 3);
  lcd->print("[ Stop ]");

  for (byte i = 0; i < PUMPS; i++)
    pumpReverse(i);

  do
  {
    readJoystick();
  } while (clicked != 0);
  waitForDepress();

  for (byte i = 0; i < PUMPS; i++)
    pumpOff(i);
}

