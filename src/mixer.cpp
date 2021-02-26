#include <Arduino.h>
#include "pumps.h"
#include "mixer.h"

Cocktail drinks[MAX_DRINKS];

int nextDrink = 0;

void addDrink(Cocktail newDrink);

void loadDrinks()
{
    addDrink({"Vodka & Orange", {{ vodka, 50}, {orange, 280}}});    
    addDrink({"Gin & Tonic", {{gin, 50}, {tonic, 280}}});    
    addDrink({"Sex On The Beach", {}});  
    addDrink({"Margarita", {}});        
    addDrink({"Cosmopolitan", {}});    
    addDrink({"Mojito", {}});  
    addDrink({"Old Fashioned", {}});
    addDrink({"Bellini", {}});          
};

void addDrink(Cocktail newDrink) {
    if (nextDrink >= MAX_DRINKS) {
        Serial.println("ERROR: dirnk was not added");
    } else {
        Serial.println("Adding " + newDrink.name);
        drinks[nextDrink] = newDrink;
        nextDrink++;
    }
}

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