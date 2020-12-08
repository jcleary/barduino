#include <Arduino.h>
#include "pumps.h"
#include "mixer.h"

Cocktail drinks[MAX_DRINKS];

void setupDrinks()
{
    int i = 0;

    // Vodka & Coke
    drinks[i++] = {
        "22",
        {
            {coke, 250},
            {vodka, 25}
        }};

    // Gin & Tonic
    drinks[i++] = {
        "23",
        {
            {gin, 50},
            {tonic, 250}
        }};
};

Cocktail getCocktailByCode(String code)
{
    Cocktail drink;

    for (byte i = 0; i < MAX_DRINKS; i++)
    {
        if (drinks[i].code == code)        
            drink = drinks[i];        
    }
    return (drink);
};

void dispense(Cocktail drink)
{
    int recipe[MAX_INGREDIENTS][2];
    int maxVolume = 0;

    for (byte i = 0; i < MAX_INGREDIENTS; i++)
    {
        recipe[i][0] = drink.recipe[i][0];
        recipe[i][1] = drink.recipe[i][1];

        if (drink.recipe[i][0] > 0)
        {
            digitalWrite(drink.recipe[i][0], HIGH);
            //if (drink.recipe[i][1] > maxVolume) {
                maxVolume = max(drink.recipe[i][1], maxVolume);
            //}            
        }
    }

    for(;maxVolume > 0; maxVolume --) {

        delay(MILLISECONDS_TO_MLS); 
        for (byte i = 0; i < MAX_INGREDIENTS; i++)
        {
            if (recipe[i][1] > 0) {
                recipe[i][1]--;
            } else {
                digitalWrite(recipe[i][0], LOW);
            }
        }
    }
    

    for (byte i = 2; i <= 13; i++)
    {
        digitalWrite(i, LOW);
    }
}

void mixCocktail(String drinkSelection)
{
    Serial.print("Searching for drink: ");
    Serial.println(drinkSelection);

    Cocktail c = getCocktailByCode(drinkSelection);
    if (c.code != "")    
        dispense(c);        
    
}


void flashGreen()
{
    int testPin = mix8;

    digitalWrite(testPin, HIGH);
    delay(100);
    digitalWrite(testPin, LOW);
    delay(100);
}