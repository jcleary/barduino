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
  addDrink({.name = "Vodka & Orange",      .recipe = {{vodka, 50}, {orange, 280}}});
  addDrink({.name = "Margarita",           .recipe = {{tequila, 50}, {triple_sec, 20}, {lime_juice, 25}}});
  addDrink({.name = "Barduino Hurricane",  .recipe = {{rum, 50}, {vodka, 50}, {lime_juice, 25}, {orange, 225}}, .aftershot = {grenadine, 12}});
  addDrink({.name = "Orange Daiquir",      .recipe = {{rum, 60}, {orange, 20}, {lime_juice, 15}},               .aftershot = {grenadine, 10}});
  addDrink({.name = "Tequila Sunrise",     .recipe = {{tequila, 50}, {orange, 100}, {lime_juice, 20}},          .aftershot = {grenadine, 30}});
  addDrink({.name = "Sex in McDs Bathroo", .recipe = {{vodka, 50}, {triple_sec, 50}, {peach_schnapps, 50}, {orange, 150}, {lime_juice, 25}}, .aftershot = {grenadine, 12}});
  
}