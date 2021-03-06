#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <lcd.h>
#include <string>
#include <unistd.h>

using namespace std;
#include "explorerHat.hpp"

int main()
{
	wiringPiSetupGpio();
	int fd = wiringPiI2CSetup(0x04);
	Motor mt;
	Stepper step;

	int i2c, i2c_back, flag;
	while(1) {
		i2c = wiringPiI2CRead(fd);
		if(i2c != i2c_back) {
			switch(i2c) {
				case 207://1
					mt.lf(); break;
				case 231://2
					mt.fw(); break;
				case 133://3
					mt.rf(); break;
				case 239://4
					mt.left(); break;
				case 199://5
					mt.stop(); break;
				case 165://6
					mt.right(); break;
				case 189://7
					mt.lb(); break;
				case 181://8
					mt.bw(); break;
				case 173://9
					mt.rb(); break;
				case 151://0

				case 253://+
				case 103://-
					break;
				case 111://>>
					step.clock(10); flag = 1; break;
				case 31://<<
					step.clock(-10); flag = -1; break;
				case 87://>

				case 79://C
				case 221://TEST
				case 61://undo
				case 29://menu
					cout << "menu" << endl;
					mt.fw();
					break;
				case 93://power
					cout << "shutdown in progress" << endl;
					system("/usr/bin/sudo /sbin/shutdown -h now");
					break;
			}
			i2c_back = i2c;
		}
		if(i2c == 255) {
				if(flag == 1) step.clock(10);
				else if(flag == -1) step.clock(-10);
		}
	}

	Lcd lcd;
	lcd.clear();
	string s = "test";
	lcd.cursor(0,0);
	lcd.puts(s);
	delay(1000);
	Light red(RED);
	red.on();
	delay(1000);
}
