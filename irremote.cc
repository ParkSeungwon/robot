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
	Lcd lcd;

	int i2c, i2c_back, flag;
	while(1) {
		i2c = wiringPiI2CRead(fd);
		if(i2c > 1000) {
			stringstream t, h;
			t << i2c/1000;
			h << i2c%1000;
			lcd.cursor(0,0);
			lcd.puts(t.str());
			lcd.cursor(0,1);
			lcd.puts(h.str());
		}
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
					lcd.puts(string("lcd"));
					break;
				case 253://+
				case 103://-
					break;
				case 111://>>
					step.clock(10); flag = 1; break;
				case 31://<<
					step.clock(-10); flag = -1; break;
				case 87://>
					cout << "Run" << endl << "nc -l -p 5001 | mplayer -fps 31 -cache 1024 -" << endl;
					system("raspivid -t 15000 -w 800 -h 600 -o - | nc 192.168.0.5 5001");
					break;
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
}
