#pragma once
#include <Arduino.h>

struct Cocktail {
  String code;  
  int recipe[5][2];
} ;

Cocktail nilDrink = { "", {} };

Cocktail getCocktailByCode(String code);