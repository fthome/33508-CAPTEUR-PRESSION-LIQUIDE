

/*******************************************************

********************************************************/

// {

#include "Lps35hw.h"
#include <LiquidCrystal.h>

Lps35hw capteur =  Lps35hw(0x5C);

const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8; // après modif carte

const int btnPin = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int indexAffichage = 0;
unsigned long temps;
float pression;
float temperature;

String pres;

byte unit_p[8] = {
  B00001,
  B00010,
  B00100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
};


byte unit_t[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B01000,
  B00100,
  B00010,
  B00001,
};





void setup(){
    pinMode(btnPin, INPUT_PULLUP); 
    lcd.createChar(0, unit_p);
    lcd.createChar(1, unit_t);
    lcd.begin(8, 1);
    lcd.setCursor(1, 0);
    // Print a message to the LCD.
    lcd.print("hello!");
    
    delay(1000);
    attachInterrupt(0,bouton,FALLING);
   Serial.begin(9600);
   capteur.init();
    
}

void bouton()
{
  if (indexAffichage == 0)
  {
    indexAffichage = 1;
  }
  else
  {
    indexAffichage = 0;
  }
  affich();
}

void affich()
{
  lcd.clear();
  
  if (indexAffichage == 0)
  {
    if(pression < 1000) lcd.setCursor(1, 0);
    else lcd.setCursor(0, 0);
    lcd.print(String(pression,1));        
    lcd.setCursor(7, 0);
    lcd.write(byte(0));
  }
  else
  {
    if(temperature < 0)
    {
      if(temperature > -10) lcd.setCursor(2, 0);
      else lcd.setCursor(1, 0);
      lcd.print(String(temperature,1));   
    }
    else
    {
      if(temperature < 10) lcd.setCursor(3, 0);
      else lcd.setCursor(2, 0);
      lcd.print(String(temperature,1));   
    }
         
    lcd.setCursor(7, 0);
    lcd.write(byte(1));
    
  }
}


void loop()
{

  pression = capteur.get_pressure();
  temperature = capteur.get_temperature();


  affich();

  Serial.print("{\"MODELE\":{\"MODELE\":\"33508\",\"VERSION\":\"1\"},\"DATAS\":{\Pression\:");
  Serial.print(pression);
  Serial.print(",\Temperature\:");
  Serial.print(temperature);
  Serial.println("}}");
  delay(500);  

}
