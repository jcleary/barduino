#pragma once
#include <Arduino.h>
#include "mixer.h"
#include "menu.h"

class DrinksMenu : public Menu
{
public:  
  DrinksMenu();
  void addDrink(Cocktail drink);  

protected:  
  Cocktail drinks[MAX_DRINKS];  
  void selectItem();  
};