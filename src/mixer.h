#pragma once
#include <Arduino.h>

const int TOTAL_DRINKS = 40;
const int TOTAL_INGREDIENTS = 5; 
const int MILLISECONDS_TO_MLS = 70;

struct Cocktail {
  String code;  
  int recipe[TOTAL_INGREDIENTS][2];
} ;

extern Cocktail drinks[TOTAL_DRINKS];

void flashGreen();
void setupDrinks();
void mixCocktail(String drinkSelection);
