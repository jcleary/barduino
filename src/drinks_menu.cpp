#include <Arduino.h>
#include "mixer.h"
#include "joystick.h"
#include "drinks_menu.h"
#include "developer_menu.h"

DrinksMenu::DrinksMenu() {
  title = "Select a drink:";
}

void DrinksMenu::addDrink(Cocktail drink)
{
  drinks[itemCount] = drink;
  items[itemCount] = drink.name;
  itemCount++;
}

void DrinksMenu::selectItem()
{
  int select = 1;

  lcd->clear();

  lcd->setCursor((20 - drinks[selection].name.length()) / 2, 0);
  lcd->print(drinks[selection].name);

  lcd->setCursor(3, 2);
  lcd->print("[Hit me] Back ");

  delay(500);
  while (true)
  {
    readJoystick();

    if (clicked == 0)
    {
      waitForDepress();
      if (select == 1)
      {
        pour(drinks[selection], *lcd);
      }
      return;
    }
    else if (xPosition > rightThreshold)
    {
      select = 0;
      lcd->setCursor(3, 2);
      lcd->print(" Hit me [Back]");
    }
    else if (xPosition < leftThreshold)
    {
      select = 1;
      lcd->setCursor(3, 2);
      lcd->print("[Hit me] Back ");
    }

    delay(50);
  }
}

void DrinksMenu::selectSecretItem() 
{
  DeveloperMenu devMenu;
  devMenu.lcd = lcd;
  devMenu.start();
  //maintenanceMenu();
}

