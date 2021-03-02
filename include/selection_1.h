#pragma once
#include <Arduino.h>
#include "mixer.h"

const byte vodka = 0;
const byte peach_schnapps = 1;
const byte triple_sec = 2;
const byte tequila = 3;
const byte rum = 4;
const byte lime_juice = 5;
const byte orange = 6;
const byte grenadine = 7;

void loadDrinks()
{
  addDrink({"Vodka & Orange", {{vodka, 50}, {orange, 280}}});
  addDrink({"Margarita", {{tequila, 50}, {triple_sec, 20}, {lime_juice, 25}}});
  addDrink({"Barduino Hurricane", {{rum, 50}, {vodka, 50}, {lime_juice, 25}, {orange, 225}, {grenadine, 12}}});

  //addDrink({"Cosmopolitan", {{lime_juice, 50}, {triple_sec, 15}, {cranberry, 30}});

  addDrink({"Orange Daiquir", {{rum, 60}, {orange, 20}, {grenadine, 10}, {lime_juice, 15}}});
  addDrink({"Tequila Sunrise", {{tequila, 50}, {orange, 100}, {grenadine, 30}, {lime_juice, 20}}});
};