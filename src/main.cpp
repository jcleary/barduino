#include <Arduino.h>
#include "pumps.h"
#include "mixer.h"
#include "keypad.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int yAxis = 7;
const int upThreshold = 422;
const int downThreshold = 622;

String drinkSelection;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);  

int selection = 0;
int yPosition;

void drawScreen();

void setup()
{
  Serial.begin(115200);

  lcd.init();   
  lcd.backlight();
  
  drinkSelection = String();
  setupPumps();
  setupDrinks();
  drawScreen();
}

void loop() 
{

  yPosition = analogRead(yAxis);

  if (yPosition < upThreshold) {     
    selection = (selection + MAX_DRINKS - 1) % MAX_DRINKS;
    drawScreen();
    delay(500);
  } else if (yPosition > downThreshold) {    
    selection = (selection + 1) % MAX_DRINKS;
    drawScreen();
    delay(500);
  }

  delay(50);
  

  // Serial.println(yPosition);
  // Serial.println(selection);
}



void test_loop()
{    
  mixCocktail("23");

  delay(1000);
}

void old_loop()
{  
  char key = getKey();

  if (key != NO_KEY)
  {
    if (key == '*')
    {      
      drinkSelection = "";      
    }
    else if (key == '#')
    {
      mixCocktail(drinkSelection);
      drinkSelection = "";
    }
    else
    {
      drinkSelection.concat(key);
    }
  }
}

void drawScreen()
{
  Serial.print("Selection: ");
  Serial.println(selection);



  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select a drink:");

  lcd.setCursor(0, 1);
  lcd.print(">");
  for(int i = 0; i < 3; i++) {    
    lcd.setCursor(1, i+1);
    lcd.print(drinks[(i + selection) % MAX_DRINKS].name);

    Serial.print("Drink: ");
    Serial.println((i + selection) % MAX_DRINKS);
  }
}

