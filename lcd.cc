#include "explorerHat.hpp"
#include <wiringPi.h>
#include <lcd.h>
#include <sr595.h>
#include <iostream>

using namespace std;

Lcd::Lcd(int data, int clock, int latch)
{
	DPIN = data; CPIN = clock; LPIN = latch;
	wiringPiSetupGpio();//to be sure to operate
	sr595Setup(100, 6, DPIN, CPIN, LPIN);
	fd = lcdInit(2, 16, 4, 100, 101, 102, 103, 104, 105, 0, 0, 0, 0);
}

void Lcd::clear() { 
	lcdClear(fd);
}

void Lcd::cursor(int x, int y) {
	lcdPosition(fd, x, y);
}

void Lcd::puts(string s) {
	lcdPuts(fd, s.c_str());
	cout << s;
	if(s != " ") cout << endl;
}

