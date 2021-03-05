#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

const int MAX_DRINKS = 12;
const int MAX_INGREDIENTS = 6;
const int MILLISECONDS_TO_MLS = 700;

struct Ingredient
{
  int pumpNo;
  int mls;
};

struct Cocktail
{
  String name;
  Ingredient recipe[MAX_INGREDIENTS];
  Ingredient aftershot;
};


extern Cocktail drinks[MAX_DRINKS];

void pour(Cocktail drink, LiquidCrystal_I2C lcd);
int lastDrinkId();
void addDrink(Cocktail newDrink);