#ifndef LPS35HW_h
#define LPS35HW_h

#include <Arduino.h>
#include <Wire.h>

const int PRESS_OUT_H = 0x2A;
const int PRESS_OUT_L = 0x29;
const int PRESS_OUT_XL = 0x28;
const int TEMP_OUT_L = 0x2B;
const int TEMP_OUT_H = 0x2C;
const int FIFO_CTRL = 0x14;
const int CTRL_REG1 = 0x10;
const int CTRL_REG2 = 0x11;

class Lps35hw
{
public:
	float get_pressure();
	float get_temperature();
	void init();
	Lps35hw(int adr);

private:
	int _adr;
};
//test

#endif
