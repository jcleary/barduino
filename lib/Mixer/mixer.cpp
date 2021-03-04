#include <Arduino.h>
#include <Pumps.h>
#include <Mixer.h>
#include <Wire.h>

Cocktail drinks[MAX_DRINKS];

int nextDrink = 0;

void addDrink(Cocktail newDrink)
{
  if (nextDrink >= MAX_DRINKS)
  {
    Serial.println("ERROR: dirnk was not added");
  }
  else
  {
    Serial.println("Adding " + newDrink.name);
    drinks[nextDrink] = newDrink;
    Serial.println(newDrink.aftershot.mls);
    nextDrink++;
  }
}

int lastDrinkId()
{
  return nextDrink - 1;
}

void pour(Cocktail drink, LiquidCrystal_I2C lcd)
{
  lcd.clear();

  lcd.setCursor(7, 0);
  lcd.print("Mixing");
  lcd.setCursor((20 - drink.name.length()) / 2, 1);
  lcd.print(drink.name);

  int pumps[PUMPS] = {};
  int ratios[PUMPS] = {};

  int maxVolume = 0;

  // sets the number of mls each pump has to dispense
  // also works out the maxVolume so we can count down
  for (byte i = 0; i < MAX_INGREDIENTS; i++)
  {
    int pumpNo = drink.recipe[i].pumpNo;
    int mls = drink.recipe[i].mls;

    if (mls > 0)
    {
      pumps[pumpNo] = mls;
      if (mls > maxVolume)
      {
        maxVolume = mls;
      }
    }
  }
  Serial.println("maxVolume: " + String(maxVolume));

  // calculates the ratios so that pumps can be pulsed to help with mixing
  for (byte i = 0; i < PUMPS; i++)
  {
    if (pumps[i] > 0)
    {
      ratios[i] = maxVolume / pumps[i];
      Serial.println("Pump no " + String(i) + " has a mod of " + String(ratios[i]));
    }
  }

  for (int i = maxVolume; i > 0; i--)
  {
    lcd.setCursor(8, 3);
    float remaining = 100 - (((float)i / (float)maxVolume) * 100);
    lcd.print(String((int)remaining) + "%  ");

    delay(MILLISECONDS_TO_MLS);

    for (byte p = 0; p < PUMPS; p++)
    {
      if ((pumps[p] > 0) && ((i % ratios[p]) == 0))
      {
        pumps[p]--;
        pumpOn(p);
      }
      else
      {
        pumpOff(p);
      }
    }
  }

  allPumpOff();

  // aftershot
  if (drink.aftershot.mls > 0)
  {
    Serial.println("Pumping aftershot through pump " + String(pumpNo));
    pumpOn(drink.aftershot.pumpNo);
    delay(MILLISECONDS_TO_MLS * drink.aftershot.mls);
    pumpOff(drink.aftershot.pumpNo);
  }
}
