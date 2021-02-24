#include <Arduino.h>
#include "pumps.h"
#include "mixer.h"
#include "keypad.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int yAxis = 7;
const int xAxis = 8;
const int joyClick = 52;
const int upThreshold = 422;
const int downThreshold = 622;

String drinkSelection;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);  

int selection = 0;
int yPosition;
int clicked;

void drawScreen();
void selectionScreen();
void readJoystick();

void setup()
{
  Serial.begin(115200);

  lcd.init();   
  lcd.backlight();

  pinMode(joyClick, INPUT_PULLUP);
  
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
    selectionScreen();
    drawScreen();
  }

  delay(500);

  

  // Serial.println(yPosition);
  // Serial.println(selection);
}

void selectionScreen()
{
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(drinks[selection].name);

  lcd.setCursor(3, 2);
  lcd.print("[ Yes ]  No ");

  delay(500);
  while (true) {
    readJoystick();

    if (clicked == 0) {
      return;
    }

    delay(50);
  }
}

void readJoystick()
{
  yPosition = analogRead(yAxis);
  clicked = digitalRead(joyClick);
}



void test_loop()
{    
  mixCocktail("23");

  delay(1000);
}



void drawScreen()
{
  // debug info
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
  }
}

