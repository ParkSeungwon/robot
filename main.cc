#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <lcd.h>
#include <string>

using namespace std;
#include "explorerHat.hpp"

int main()
{
	wiringPiSetupGpio();
	fd = wiringPiI2CSetup(0x04);
	char ch;
	
	int p = 50;
	int a = 0;
	
	Touch touch;
	Light red(RED);
	Light blue(BLUE);
	Light green(GREEN);
	Light yellow(YELLOW);

	string str;

	int i=0,j=0;
	Console con;
	while(1) {
		while(!(i = touch.read())) ;
		if(i == j) j = 0;//to avoid twice hitting
		else {
			switch(i) {
				case 1: blue.blink(); break;		
				case 2: yellow.blink(); break;
				case 3: red.blink(); 	break;
				case 4: green.blink(); 	break;
				default: ;
			}
			j = i;
			con.command_func(i);
		}
	}
	
//	while(1) {
//		switch(ch = getchar()) {
//			case '7': mt.lf(); break;
//			case '9': mt.rf(); break;
//			case '1': mt.lb(); break;
//			case '3': mt.rb(); break;
//			case '5': mt.stop(); break;
//			case 'w': servo.pulse(p += 10); break;
//			case 's': servo.pulse(p -= 10); break;
//			case 'a': step.clock(a = -10); break;
//			case 'd': step.clock(a = 10); break;
//			case '4': mt.left(); break;
//			case '6': mt.right(); break;
//			case '8': mt.fw(); break;
//			case '2': mt.bw(); break;
//			case 'q': return 0;
//			default: ; 
//		}}
	
}

