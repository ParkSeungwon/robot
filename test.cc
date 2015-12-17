#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <lcd.h>
#include <string>
#include <unistd.h>

using namespace std;
#include "explorerHat.hpp"

int main()
{
	Lcd lcd;
	lcd.clear();
	lcd.puts(string("test"));
}
