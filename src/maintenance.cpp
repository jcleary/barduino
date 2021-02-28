#include <Arduino.h>
#include "maintenance.h"
#include "lcd.h"
#include "joystick.h"

const int MENU_ITEMS = 3;
String menu[MENU_ITEMS] = {"Prime", "Purge", "Exit"};

void drawMaintenanceMenu(int selection);
void primeAllPumps();
void purgeAllPumps();

void maintenanceMenu()
{
  int selection = 0;

  drawMaintenanceMenu(selection);

  do
  {
    readJoystick();
    delay(50);

    if (yPosition < upThreshold && selection > 0)
    {
      drawMaintenanceMenu(--selection);
      delay(500);
    }
    else if (yPosition > downThreshold && selection < (MENU_ITEMS - 1))
    {
      drawMaintenanceMenu(++selection);
      delay(500);
    } else if (clicked == 0) {
      waitForDepress();
      switch(selection) {
        case 0:
          primeAllPumps();
          break;

        case 1:
          purgeAllPumps();
          break;

        case 2:
          return;
      }
    }

  } while (true);
}

void drawMaintenanceMenu(int selection)
{
  int item;

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Developer Menu");

  lcd.setCursor(0, 2);
  lcd.print(">");
  for (int i = 0; i < 3; i++)
  {
    item = selection - 1 + i;
    if (item >= 0 && item < MENU_ITEMS)
    {
      lcd.setCursor(1, i + 1);
      lcd.print(menu[item]);
    }
  }
}

void primeAllPumps() 
{
  lcd.clear();
  lcd.setCursor(6,1);
  lcd.print("Priming");




}

void purgeAllPumps()
{

}
