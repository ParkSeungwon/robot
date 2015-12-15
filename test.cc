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

Motor mt;
Pwm servo;
Stepper step;
RangeFinder range;
//Lcd lcd;

string command_str[5][5];
int fd, command;
int command_func(int);
int execute_command(int);

int main()
{
	command_str[0][1] = "command list";
	command_str[1][2] = "w";
	command_str[0][2] = "range finder";
	command_str[0][3] = "test motors";
	command_str[0][4] = "I2C write";
	command_str[1][1] = "I2C read";
	command_str[4][4] = "shutdown";

	Lcd lcd;
	lcd.clear();
	lcd.puts(string("testing"));
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
	int command = 0;
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
			command_func(i);
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

int command_func(int i) {
	stringstream s;
	if(i >= 1 && i <= 4) {
		command = 10 * command + i;
		if(command > 99) command /= 10;
	}
	else if(i == 8) execute_command(command);
	else if(i == 7) command = command / 10; 
	
	s.str("");
	s << command;
//	lcd.clear();
//	lcd.cursor(0, 0);
//	lcd.puts(s.str());
//	lcd.cursor(1, 0);
//	lcd.puts(command_str[command/10][command%10]);
	return command;
}

int execute_command(int com) {
}

