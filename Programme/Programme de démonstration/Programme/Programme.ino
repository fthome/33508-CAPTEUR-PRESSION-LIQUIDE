#include "Pierron_33508.h"

MS5837 sensor;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
const int btnPin = 2;
int indexAffichage = 0;
unsigned long temps;

float pressure_prec;
float pressure;
float temperature;
float temperature_prec;
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

void setup() {
  pinMode(btnPin, INPUT_PULLUP);
  lcd.createChar(0, unit_p);
  lcd.createChar(1, unit_t);
  lcd.begin(8, 1);
  lcd.setCursor(1, 0);
  lcd.print("PIERRON");

  delay(1000);
  attachInterrupt(0, bouton, FALLING);
  Serial.begin(9600);
  Wire.begin();

  while (!sensor.init())
  {
    Serial.println("Init failed!");
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("\n\n\n");
    delay(5000);
  }

  sensor.setModel(MS5837::MS5837_02BA);
  sensor.setFluidDensity(997);
}

void loop() {
  sensor.read();

  pressure = sensor.pressure();
  temperature = sensor.temperature();

  if (pressure < 0) pressure = pressure_prec;

  if (temperature < 0) temperature = temperature;

  affich();
  Serial.print("{\"MODELE\":{\"MODELE\":\"33508\",\"VERSION\":\"1\"},\"DATAS\":{\"Pression\":");
  Serial.print(pressure);
  Serial.print(",\"Temperature\":");
  Serial.print(temperature);
  Serial.println("}}");

  pressure_prec = pressure;
  temperature_prec = temperature;
  delay(500);
}

void bouton() {
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

void affich() {
  lcd.clear();

  if (indexAffichage == 0)
  {
    if (pressure < 1000) lcd.setCursor(1, 0);
    else lcd.setCursor(0, 0);
    lcd.print(String(pressure, 1));
    lcd.setCursor(7, 0);
    lcd.write(byte(0));
  }
  else
  {
    if (temperature < 0)
    {
      if (temperature > -10) lcd.setCursor(2, 0);
      else lcd.setCursor(1, 0);
      lcd.print(String(temperature, 1));
    }
    else
    {
      if (temperature < 10) lcd.setCursor(3, 0);
      else lcd.setCursor(2, 0);
      lcd.print(String(temperature, 1));
    }

    lcd.setCursor(7, 0);
    lcd.write(byte(1));

  }
}
