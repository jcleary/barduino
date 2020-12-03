#include <Arduino.h>
#include "cocktails.h"
#include "pumps.h"

#define NO_KEY 0

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

int keyPadAnalogPin = 3;  
int keyDelay = 50;
unsigned int keyVal1 = 0;  
unsigned int keyVal2 = 0;  

String drinkSelection;  

void dispense(Cocktail drink);
unsigned int getKey();
void mixCocktail();
char getMatrixValue(int val);

void setup() {      
  Serial.begin(9600);  
  drinkSelection = String();  
  setupPumps();
}


void loop() {  
  char key = getKey(); 

  if (key != NO_KEY){  
    if (key == '*') {  
      drinkSelection = "";  
    }
    else if (key == '#') {        
      mixCocktail();
      drinkSelection = "";
    }
    else {
      drinkSelection.concat(key);  
    }    
  }
}


void dispense(Cocktail drink) {
  for(byte i = 0; i < sizeof(drink.recipe); i++) {
    if (drink.recipe[i][0] > 0) {
      digitalWrite(drink.recipe[i][0], HIGH);    
    }
  }
  delay(1500);

  for(byte i = 2; i <= 13; i++) {
    digitalWrite(i, LOW); 
  }  
}


void mixCocktail() {  
  Cocktail c = getCocktailByCode(drinkSelection);
  if ( c.code != "" ) {
    dispense(c);
  }
}

unsigned int getKey() {
  keyVal1 = analogRead(keyPadAnalogPin); Serial.println(keyVal1); 
  delay(keyDelay);
  keyVal2 = analogRead(keyPadAnalogPin); 
  if(keyVal1 > keyVal2) {
    keyVal1 = max(keyVal1, keyVal2); 
    return getMatrixValue(keyVal1);  
  }
  else 
    return NO_KEY;  
}

char getMatrixValue(int val) {
  switch(val) {
    case 930 : return keys[0][0];
    case 912 : return keys[0][1];
    case 894 : return keys[0][2];
    case 877 : return keys[0][3];
    case 852 : return keys[1][0];
    case 837 : return keys[1][1];
    case 822 : return keys[1][2];
    case 808 : return keys[1][3];
    case 787 : return keys[2][0];
    case 774 : return keys[2][1];
    case 761 : return keys[2][2];
    case 749 : return keys[2][3];
    case 731 : return keys[3][0];
    case 719 : return keys[3][1];
    case 708 : return keys[3][2];
    case 698 : return keys[3][3];
    default : return NO_KEY;
  }
}



