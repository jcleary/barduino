#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "joystick.h"
#include "menu.h"

void Menu::start()
{
  Serial.println("menuItems: "  +String(menuItems));
  refreshMenu();

  while (true)
  {
    readJoystick();

    if (yPosition < upThreshold && selection > 0)
    {
      selection -= 1;
      refreshMenu();
      delay(200);
    }
    else if (yPosition > downThreshold && selection < (menuItems -1))
    {
      selection += 1;
      refreshMenu();
      delay(200);
    }
    else if (clicked == 0)
    {
      waitForDepress();
      selectItem();
      refreshMenu();
    }
    else if (xPosition > rightThreshold)
    {
      int i = 300;
      do
      {
        readJoystick();
        i--;
        delay(10);
      } while (i > 0 && xPosition > rightThreshold);
      if (i == 0)
      {
        selectSecretItem();
        refreshMenu();
      }
    }

    delay(10);    
  }  
}

void Menu::refreshMenu()
{
  // debug info
  Serial.print("Selection: " + String(selection));  
  Serial.println(" " + options[selection]);

  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print(menuTitle);

  lcd->setCursor(0, 2);
  lcd->print(">");
  for (int i = 0; i < 3; i++)
  {
    int item = selection - 1 + i;
    if (item >= 0 && item < menuItems)
    {
      lcd->setCursor(1, i + 1);
      lcd->print(options[item]);
    }
  }
}
