#pragma once
#include <Arduino.h>

const int MAX_DRINKS = 9;
const int MAX_INGREDIENTS = 5; 
const int MILLISECONDS_TO_MLS = 700;

struct Cocktail {
  String name;
  int recipe[MAX_INGREDIENTS][2];
} ;

extern Cocktail drinks[MAX_DRINKS];

void loadDrinks();
void dispense(Cocktail drink);