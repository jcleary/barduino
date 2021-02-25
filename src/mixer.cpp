#include <Arduino.h>
#include "pumps.h"
#include "mixer.h"

Cocktail drinks[MAX_DRINKS];


void loadDrinks()
{
    int i = 0;

    drinks[i++] = {
        "Vodka & Orange",
        {
            {orange, 280},
            {vodka, 50}
        }};

    drinks[i++] = {
        "Not Vodka Orange",
        {
            {gin, 50},
            {tonic, 250}
        }};

    drinks[i++] = {
        "Not Vodka Orange",
        {
            {gin, 50},
            {tonic, 250}
        }};    

    drinks[i++] = {
        "Sex On The Beach",
        {
            {gin, 50},
            {tonic, 250}
        }};  

    drinks[i++] = {
        "Margarita",
        {
            {gin, 50},
            {tonic, 250}
        }};        

    drinks[i++] = {
        "Cosmopolitan",
        {
            {gin, 50},
            {tonic, 250}
        }};    

    drinks[i++] = {
        "Mojito",
        {
            {gin, 50},
            {tonic, 250}
        }};  

    drinks[i++] = {
        "Old Fashioned",
        {
            {gin, 50},
            {tonic, 250}
        }};    

   drinks[i++] = {
        "Bellini",
        {
            {gin, 50},
            {tonic, 250}
        }};            

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