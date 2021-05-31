# 33508-CAPTEUR-DE PRESSION DANS UN LIQUIDE

CAPTEUR DE PRESSION DANS UN LIQUIDE [33508](https://www.pierron.fr/capteur-de-pression-dans-un-liquide.html)

Cet appareil est particulièrement conçu pour mesurer et étudier la pression absolue P dans un liquide, en fonction de la hauteur h de liquide qui sépare le capteur de pression de la surface du liquide. On retrouvera ainsi le principe de l'hydrostatique :
P↓A|- P↓B| = ρ.g.h.
Il comprend une sonde dont le capteur plonge dans une grande éprouvette remplie de liquide.
Cette sonde est constituée par :

![h33508](/details/h33508.png)

Ainsi, pour retrouver le principe de l'hydrostatique, il suffit de plonger le capteur dans l'éprouvette remplie d'eau. En modifiant la position du capteur dans l'eau, on mesure directement la pression absolue P en fonction de h. Il reste alors à exploiter les mesures et la courbe P = f(h).
Le capteur P-T est connecté à une carte Arduino™ programmée pour exploiter les données du capteur et les afficher sur l'écran. Elle offre la possibilité aux professeurs qui le souhaitent, d'initier les élèves à la programmation : à cet effet, un port mini-USB externe est disponible sur la carte. Une fois qu'on a conçu le programme pour piloter l'ensemble carte-capteur-afficheur, il suffit de le téléverser sur la carte.

![2h33508](/details/2h33508.png)

<br/>

# RESSOURCES À TÉLÉCHARGER :

Logiciel d'acquisition : [PIANODE](https://github.com/pierron-asco-celda/InterfacePIANODE_USB)

Ressource : [NOTICE](https://www.pierron.fr/fileuploader/download/download/?d=0&file=custom%2Fupload%2F33508.pdf)

<br/>

# Schémas :
![carte principale](/details/img_carte_principale.png)
![carte capteur](/details/img_carte_capteur.png)

<br/>

# Exemples :
### Arduino / C++
```
// Baud rate 9600

#include "Lps35hw.h"
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
