#include <Arduino.h>
#include "pumps.h"
#include "mixer.h"
#include "keypad.h"

String drinkSelection;

void setup()
{
  Serial.begin(115200);
  drinkSelection = String();
  setupPumps();
  setupDrinks();
}

void loop()
{    
  mixCocktail("23");

  delay(1000);
}

void old_loop()
{  
  char key = getKey();

  if (key != NO_KEY)
  {
    if (key == '*')
    {      
      drinkSelection = "";      
    }
    else if (key == '#')
    {
      mixCocktail(drinkSelection);
      drinkSelection = "";
    }
    else
    {
      drinkSelection.concat(key);
    }
  }
}

