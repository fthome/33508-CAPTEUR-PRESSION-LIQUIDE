# 33508 Capteur de pression dans un liquide

CAPTEUR DE PRESSION DANS UN LIQUIDE [33508](https://www.pierron.fr/capteur-de-pression-dans-un-liquide.html)

Cet appareil est particulièrement conçu pour mesurer et étudier la pression absolue P dans un liquide, en fonction de la hauteur h de liquide qui sépare le capteur de pression de la surface du liquide. On retrouvera ainsi le principe de l'hydrostatique :
P<sub>A</sub> - P<sub>B</sub> = ρ.g.h.

![E1-33508](/img/E1-33508.png)

Il comprend une sonde dont le capteur plonge dans une grande éprouvette remplie de liquide.
Cette sonde est constituée par : 

![E2-33508](/img/E2-33508.png)

Ainsi, pour retrouver le principe de l'hydrostatique, il suffit de plonger le capteur dans l'éprouvette remplie d'eau. En modifiant la position du capteur dans l'eau, on mesure directement la pression absolue P en fonction d’h. Il reste alors à exploiter les mesures et la courbe P = f(h).
Le capteur P-T est connecté à une carte Arduino™ programmée pour exploiter les données du capteur et les afficher sur l'écran. Elle offre la possibilité aux professeurs qui le souhaitent, d'initier les élèves à la programmation : à cet effet, un port mini-USB externe est disponible sur la carte. Une fois qu'on a conçu le programme pour piloter l'ensemble carte-capteur-afficheur, il suffit de le téléverser sur la carte.

Logiciel d'acquisition "Pianode":

![E3-33508](/img/E3-33508.png)

# RESSOURCES À TÉLÉCHARGER :

Logiciel d'acquisition : [PIANODE](https://github.com/pierron-asco-celda/InterfacePIANODE_USB)

Ressource utilisation : [NOTICE-33508](https://www.pierron.fr/fileuploader/download/download/?d=0&file=custom%2Fupload%2F33508.pdf)

# Schémas :
![E4-33508](/img/E4-33508.png)
![SCH-P-33508](/img/SCH-P-33508.png)
![SCH-C-33508](/img/SCH-C-33508.png)
![BRD-33508](/img/BRD-33508.png)

# Complément sur la programmation :
L’accès au capteur se fera par le bus I2C à l’adresse suivante : 0x5c.
– La ligne SDA (données) est connectée à la broche A4 de la carte Arduino™;
– la ligne SCL (horloge) est connectée à la broche A5 de la carte Arduino™.

Exemple de lignes de code donnant accès aux données du capteur : 
```cpp
#include "Lps35hw.h"
Lps35hw capteur(0x5c) ;
float pression = capteur.get_pressure();
float temperature = capteur.get_temperature();
```

Pour utiliser l’afficheur en parallèle, il sera nécessaire d’utiliser la bibliothèque LiquidCrystal
disponible dans l’IDE Arduino™ (dans la rubrique gestionnaire de bibliothèque, rechercher 
« LiquidCrystal » et cliquer sur Installer)
Les lignes de code à intégrer au programme seront les suivantes :
```cpp
#include <LiquidCrystal.h>
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
```

# Exemple :
### Arduino / C++
```cpp
// Baud rate 9600;*

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
## À propos :
<br>
En cas de difficultés, il y a toujours possibilité de télécharger le programme d’origine à partir 
des « ressources » sur le site [www.pierron.fr](https://www.pierron.fr)
<br>
<div style="text-align: justify">*Le débit en bauds est un taux de transfert de données en unités de bits par seconde (bps). Si le débit en bauds est de 9600, cela signifie que la possibilité d’envoyer des données est de 9600 bits en une seconde. 1 caractère est identique à 1 octet.</div>
<br>

PIERRON ASCO-CELDA (https://www.pierron.fr/)
