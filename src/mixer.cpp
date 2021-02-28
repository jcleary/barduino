#include <Arduino.h>
#include "pumps.h"
#include "mixer.h"
#include <Wire.h> 

Cocktail drinks[MAX_DRINKS];

int nextDrink = 0;

void addDrink(Cocktail newDrink);

void loadDrinks()
{
    addDrink({"Vodka & Orange", {{ vodka, 50}, {orange, 280}}});    
    addDrink({"Gin & Tonic", {{gin, 50}, {tonic, 280}}});    
    addDrink({"Sex On The Beach", {{vodka, 50}, {peach_schnapps, 25}, {cranberry, 50}, {orange, 140}}});  
    addDrink({"100m Tonic", {{tonic, 100}}});    
    addDrink({"100m OJ", {{orange, 100}}});    
    addDrink({"25ml Peach Schnaps", {{peach_schnapps, 25}}});    
    // addDrink({"Margarita", {}});        
    // addDrink({"Cosmopolitan", {}});    
    // addDrink({"Mojito", {}});  
    // addDrink({"Old Fashioned", {}});
    // addDrink({"Bellini", {}});          
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

int lastDrinkId() {
    return nextDrink - 1;
}


void pour(Cocktail drink, LiquidCrystal_I2C lcd)
{
  lcd.clear();

  lcd.setCursor(7,0);
  lcd.print("Mixing");
  lcd.setCursor((20 - drink.name.length()) / 2, 1);  
  lcd.print(drink.name);

  int pumps[PUMPS] = {};

  int maxVolume = 0;

  // sets the number of mls each pump has to dispense
  // also works out the macVolume so we can count down  
  for (byte i = 0; i < MAX_INGREDIENTS; i++)
  {        
    int pumpNo = drink.recipe[i][0];
    int mls = drink.recipe[i][1];

    if(mls > 0) {
      pumps[pumpNo] = mls;      
      if (mls > maxVolume) {
        maxVolume = mls;
      }
    }
  }

  Serial.println("maxVolume: " + String(maxVolume));

  // start pumps
  for (byte i = 0; i < PUMPS; i++) {
    if (pumps[i] > 0) {
      pumpOn(i);
    }
    // debug info show how much each pump will dispense
    Serial.println("pumping pump no " + String(i) + " for " + String(pumps[i]) + "ml");
  }

  for(int i = maxVolume; i > 0; i--) {
    lcd.setCursor(8, 3);
    float remaining = 100 - (((float)i / (float)maxVolume) * 100);
    lcd.print(String((int)remaining) + "%  ");

    delay(MILLISECONDS_TO_MLS);

    for (byte i = 0; i < PUMPS; i++) {
      if (pumps[i] > 0) { 
        pumps[i]--;

        if (pumps[i] == 0) {
          Serial.println("Stopping pump " + String(i));
          pumpOff(i);
        }
      }      
    }    
  }
}
