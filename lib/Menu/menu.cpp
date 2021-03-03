#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Joystick.h>
#include <Menu.h>

void Menu::start()
{
  Serial.println("menuItems: "  +String(itemCount));
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
    else if (yPosition > downThreshold && selection < (itemCount -1))
    {
      selection += 1;
      refreshMenu();
      delay(200);
    }
    else if (clicked == 0)
    {
      waitForDepress();
      if (selection == exitItemNo) {
        return;
      }
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
  Serial.println(" " + items[selection]);

  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print(title);

  lcd->setCursor(0, 2);
  lcd->print(">");
  for (int i = 0; i < 3; i++)
  {
    int item = selection - 1 + i;
    if (item >= 0 && item < itemCount)
    {
      lcd->setCursor(1, i + 1);
      lcd->print(items[item]);
    }
  }
}
