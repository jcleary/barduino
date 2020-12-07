#include <Arduino.h>
#include "pumps.h"
#include "mixer.h"

Cocktail drinks[TOTAL_DRINKS];

void flashGreen();

void setupDrinks()
{
    int i = 0;

    // Vodka & Coke
    drinks[i++] = {
        "22",
        {
            {coke, 25},
            {vodka, 250},
            {0, 100},
            {0,0},
            {0,0}
        }};

    // Gin & Tonic
    drinks[i++] = {
        "23",
        {
            {gin, 25},
            {tonic, 100}
        }};
};

Cocktail getCocktailByCode(String code)
{
    Cocktail drink;

    for (byte i = 0; i < TOTAL_DRINKS; i++)
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
    for (byte i = 0; i < TOTAL_INGREDIENTS; i++)
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
        flashGreen();
    }
}

void flashGreen()
{
    int testPin = mix8;

    digitalWrite(testPin, HIGH);
    delay(500);
    digitalWrite(testPin, LOW);
    delay(500);
}