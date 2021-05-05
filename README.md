# 33508-CAPTEUR-DE PRESSION DANS UN LIQUIDE
Un appareil de de mesure de la pression étanche composé de
- Un capteur de pression étanche  LPS35HW
- Un afficheur LCD 1x8 (HD44780)
- Un arduinon nano
- Un bouton poussoir + intérupteur marche/arrêt

#Acquisition

Le produit est utilisable avec le programme d'acquisition [PIANODE](https://www.pierron.fr/fileuploader/download/download/?d=0&file=custom%2Fupload%2Fpianode.zip)

![capteur de pression dans un liquide 33508](/details/img_33508.png)
## Schémas
![carte principale](/details/img_carte_principale.png)
![carte capteur](/details/img_carte_capteur.png)

## Examples
### Arduino / C++
```


/*******************************************************

********************************************************/

// {

#include <Lps35hw.h>
#include <LiquidCrystal.h>

Lps35hw capteur =  Lps35hw(0x5C);

const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;

const int btnPin = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int indexAffichage = 0;
unsigned long temps;
float pression;
float temperature;

String pres;

byte unit_p[8] = {B00001,B00010,B00100,B01000,B00000,B00000,B00000,B00000};
byte unit_t[8] = {B00000,B00000,B00000,B00000,B01000,B00100,B00010,B00001};

void setup(){
    Serial.begin(9600);
    pinMode(btnPin, INPUT_PULLUP);
    lcd.createChar(0, unit_p);
    lcd.createChar(1, unit_t);
    lcd.begin(8, 1);
    lcd.setCursor(1, 0);
    lcd.print("hello!");
    delay(1000);
    attachInterrupt(0,bouton,FALLING);
    capteur.init();
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

void bouton()
{
  if (indexAffichage == 0) indexAffichage = 1;
  else indexAffichage = 0;
  affich();
}

```
## A propos

PIERRON ASCO-CELDA (https://www.pierron.fr/)
