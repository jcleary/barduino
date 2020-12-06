#include <Arduino.h>
#include "pumps.h"
#include "mixer.h"

Cocktail getCocktailByCode(String code)
{
    Cocktail drinks[80] = {
        {// Vodka & Coke
         "22",
         {
             {vodka, 25},
             {coke, 250},
             {lemonade, 100},
         }},
        {// Gin & Tonic
         "23",
         {{gin, 25},
          {tonic, 250}}}};

    Cocktail drink;

    for (byte i = 0; i < sizeof(drinks); i++)
    {
        if (drinks[i].code == code)
        {
            drink = drinks[i];
        }
    }
    return (drink);
};

void dispense(Cocktail drink)
{
    for (byte i = 0; i < sizeof(drink.recipe); i++)
    {
        if (drink.recipe[i][0] > 0)
        {
            digitalWrite(drink.recipe[i][0], HIGH);
        }
    }
    delay(1500);

    for (byte i = 2; i <= 13; i++)
    {
        digitalWrite(i, LOW);
    }
}

void mixCocktail(String drinkSelection)
{
    Cocktail c = getCocktailByCode(drinkSelection);
    if (c.code != "")
    {
        dispense(c);
    }
}