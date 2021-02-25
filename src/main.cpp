#include <Arduino.h>
#include "pumps.h"
#include "mixer.h"
#include "keypad.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int yAxis = 7;
const int xAxis = 6;
const int joyClick = 52;
const int upThreshold = 422;
const int downThreshold = 622;
const int leftThreshold = 422;
const int rightThreshold = 622;

String drinkSelection;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);  

int selection = 0;
int yPosition;
int xPosition;
int clicked;

void drawScreen();
void confirmationScreen();
void readJoystick();
void pour();

void setup()
{
  Serial.begin(115200);
  pinMode(joyClick, INPUT_PULLUP);

  lcd.init();   
  lcd.backlight();
  
  drinkSelection = String();

  setupPumps();
  setupDrinks();
  drawScreen();
}

void loop() 
{
  readJoystick();

  if (yPosition < upThreshold) {     
    selection = (selection + MAX_DRINKS - 1) % MAX_DRINKS;
    drawScreen();
    delay(500);
  } else if (yPosition > downThreshold) {    
    selection = (selection + 1) % MAX_DRINKS;
    drawScreen();
    delay(500);
  } else if (clicked == 0) {
    confirmationScreen();
    drawScreen();
    delay(500);
  }

  delay(10);
}

void confirmationScreen()
{
  int select = 1;

  lcd.clear();

  lcd.setCursor((20 - drinks[selection].name.length()) / 2, 0);
  lcd.print(drinks[selection].name);

  lcd.setCursor(3, 2);
  lcd.print("[Hit me] Back ");

  delay(500);
  while (true) {
    readJoystick();

    if (clicked == 0) {
      if (select == 1) {
        pour();
      }
      return;
    } else if (xPosition > rightThreshold) {
      select = 0;
      lcd.setCursor(3, 2);
      lcd.print(" Hit me [Back]");
    } else if (xPosition < leftThreshold) {
      select = 1;
      lcd.setCursor(3, 2);
      lcd.print("[Hit me] Back ");
    }

    delay(50);
  }
}

void drawScreen()
{
  int drink;

  // debug info
  Serial.print("Selection: ");
  Serial.print(selection);
  Serial.println(" " + drinks[selection].name);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select a drink:");

  lcd.setCursor(0, 2);
  lcd.print(">");
  for(int i = 0; i < 3; i++) {
    drink = (i + selection + MAX_DRINKS - 1) % MAX_DRINKS;
    lcd.setCursor(1, i+1);
    lcd.print(drinks[drink].name);
  }
}


void pour()
{
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Mixing ...");
  lcd.setCursor(0,1);
  lcd.print(drinks[selection].name);

  for(int i=0; i < 20; i++) {
    lcd.setCursor(i,3);
    lcd.print('>');
    delay(200);
  }
}

void readJoystick()
{
  yPosition = analogRead(yAxis);
  xPosition = analogRead(xAxis);
  clicked = digitalRead(joyClick);
}