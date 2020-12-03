#include <Arduino.h>
#include "cocktails.h"
#include "pumps.h"

Cocktail drinks[80] = {
  { 
    // Vodka & Coke    
    "22",    
    { 
      { vodka, 25 }, 
      { coke, 250 } ,
      { lemonade, 100 },        
    }
  },
  {
    // Gin & Tonic
    "23",    
    { 
      { gin, 25 }, 
      { tonic, 250 } 
    }
  }
};

Cocktail getCocktailByCode(String code) {
  Cocktail drink = nilDrink;     

  for(byte i=0; i < sizeof(drinks); i++) {
    if (drinks[i].code == code) {
      drink = drinks[i];
    }
  } 
  return (drink);     
};              