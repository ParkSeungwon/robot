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
Lcd lcd;
Motor mt;
Pwm servo;
Stepper step;
RangeFinder range;

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
	command_str[1][3] = "camera on";

//	Lcd lcd2;
//	lcd2.clear();
//	lcd2.puts(string("testing"));
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

int next_command(int com) {
	for(int i=0; i<=4; i++) {
		for(int j=0; j<=4; j++) {
			if(command_str[i][j] != "") {
				if(i*10+j > com) return i*10+j;
			}
		}
	}
	return 1;// circle  to first
}

int prev_command(int com) {
	for(int i=4; i>=0; i--) {
		for(int j=4; j>=0; j--) {
			if(command_str[i][j] != "") {
				if(i*10+j < com) return i*10+j;
			}
		}
	}
	return 44;//circle to last
}


int command_func(int i) {
	stringstream s;
	if(i >= 1 && i <= 4) {
		command = 10 * command + i;
		if(command > 99) command /= 10;
	}
	else if(i == 8) execute_command(command);
	else if(i == 7) command = command / 10; 
	else if(i == 5) command = next_command(command);
	else if(i == 6) command = prev_command(command);

	s.str("");
	s << command;
	lcd.clear();
	lcd.cursor(0, 0);
	lcd.puts(s.str());
	
	lcd.puts(". ");
	lcd.puts(command_str[command/10][command%10]);
	lcd.cursor(0,1);
	lcd.puts("8:x,7:<-,5:+,6:-");
	return command;
}

int execute_command(int com) {
	stringstream s;
	string st;
	int k = 0;
	FILE* fp;
	char buffer[1024];

	switch(com) {
		case 1:
			lcd.clear();
			k = 0;
			for(int i=0; i<=4; i++) {
				for(int j=0; j<=4; j++) {
					if(command_str[i][j] != "") {
						s.str("");
						s << i*10+j;
						st = s.str() + string(". ") + command_str[i][j];
						lcd.cursor(0, k++ % 2);
						lcd.puts(st);
						for(int i=0; i<16-st.length(); i++) lcd.puts(string(" "));	
						delay(1000);
					}
				}
			}
			break;
		case 12:
			fp = popen("who", "r");
			if( fp == NULL) perror("popen() error");
			while(fgets(buffer, 1024, fp)) lcd.puts(string(buffer));
			pclose(fp);
			delay(2000);
			break;
		case 2:
			for(int i=0; i<5; i++) {
				lcd.clear();
				s.str("");//clear stringstream or it stacks
				s << range.read_distance();
				st = "distance= " + s.str() + "cm";
				s.str("");
				s << step.get_angle();
						
				lcd.cursor(0,0);
				lcd.puts(st);
				lcd.cursor(0,1);
				st = "at angle " + s.str();
				lcd.puts(st);
				delay(2000);
			}
			break;
		case 3:
			mt.fw();
			step.clock(100);
					//servo.pulse(70);
					//for(int i; i<10; i++) {
					//	servo.pulse(-50 + 10*i);
					//	delay(100);
					//}
			delay(2000);
			mt.bw();
			step.clock(-200);
				//servo.pulse(50);
			delay(2000);
			mt.stop();

			lcd.puts(string("3"));
			break;
		case 4:
			wiringPiI2CWrite(fd, 30);
			break;
		case 11:
			s.str("");
			s << wiringPiI2CRead(fd);
			lcd.clear();
			lcd.puts(s.str());
			delay(2000);
			break;
		
		case 44:
			lcd.puts(string("ending"));
			execl("/usr/bin/sudo", "/usr/bin/sudo", "/sbin/shutdown", "-h", "now");
			break;

		case 13:
			lcd.puts(string("camera on"));
			execl("raspvid", "raspvid", "-t", "999999", "-w", "800", "-h", "600", "-o", "–", "|", "nc", "192.168.0.5", "5001");
			break;

		default:;
	}
}

