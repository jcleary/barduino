#pragma once
#include <Arduino.h>
#include <Mixer.h>
#include <Menu.h>

class DrinksMenu : public Menu
{
public:  
  DrinksMenu();
  void addDrink(Cocktail drink);  

protected:  
  Cocktail drinks[MAX_DRINKS];  
  void selectItem();  
  void selectSecretItem();
};