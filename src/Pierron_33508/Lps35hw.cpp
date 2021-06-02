
#include "Lps35hw.h"


Lps35hw::Lps35hw(int adr): _adr(adr)
{
	
}

void Lps35hw::init()
{
	Serial.println(_adr);
	Wire.begin();
    
	Wire.beginTransmission(_adr);
    Wire.write(FIFO_CTRL);
    Wire.write(0x00);
    Wire.endTransmission();

    Wire.beginTransmission(_adr);
    Wire.write(CTRL_REG1);
    Wire.write(0x10);
    Wire.endTransmission();
	
	Wire.beginTransmission(_adr);
    Wire.write(CTRL_REG2);
    Wire.write(0x11);
    Wire.endTransmission();
}


float Lps35hw::get_pressure()
{
int press_h;    
int press_l;    
int press_xl;
float pressure_lbs;    
float pressure; 

	

    Wire.beginTransmission(_adr);
    Wire.write(PRESS_OUT_XL);
    Wire.endTransmission();

    Wire.requestFrom(_adr, 3);
    if (3 <= Wire.available()) 
    {
        press_xl = Wire.read();
        press_l = Wire.read();
        press_h = Wire.read();
    }
    Wire.endTransmission();
	
    pressure_lbs = (press_h * 256.0 * 256.0) + (press_l * 256.0) + press_xl;
    pressure = pressure_lbs / 4096;

	return pressure;	
}

float Lps35hw::get_temperature()
{
int temp_h;    
int temp_l;    
float temperature;      

	
	
    Wire.beginTransmission(_adr);
    Wire.write(TEMP_OUT_L);
    Wire.endTransmission();

    Wire.requestFrom(_adr, 2);
    if (2 <= Wire.available()) 
    {
		temp_l = Wire.read();
		
        temp_h = Wire.read();
		
    }
    Wire.endTransmission();
	
    temperature = ((temp_h * 256) + temp_l); 
    temperature = temperature / 100 ;
	
	return temperature;
}