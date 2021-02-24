#pragma once
#include <Arduino.h>

const int MAX_DRINKS = 10;
const int MAX_INGREDIENTS = 5; 
const int MILLISECONDS_TO_MLS = 20;

struct Cocktail {
  String code;  
  String name;
  int recipe[MAX_INGREDIENTS][2];
} ;

extern Cocktail drinks[MAX_DRINKS];

void flashGreen();
void setupDrinks();
void mixCocktail(String drinkSelection);
