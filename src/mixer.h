#pragma once
#include <Arduino.h>

const int TOTAL_DRINKS = 40;
const int TOTAL_INGREDIENTS = 5; 

struct Cocktail {
  String code;  
  int recipe[TOTAL_INGREDIENTS][2];
} ;

extern Cocktail drinks[TOTAL_DRINKS];

void setupDrinks();
void mixCocktail(String drinkSelection);
