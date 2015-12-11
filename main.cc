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
	wiringPiSetupGpio();
	
	char ch;
	Motor mt;
	Pwm servo;
	Stepper step;
	int p = 50;
	int a = 0;
	
	Touch touch;
	Lcd lcd;
	Light red(RED);
	Light blue(BLUE);
	Light green(GREEN);
	Light yellow(YELLOW);
	RangeFinder range;

	FILE *fp;
	char buffer[1024];
	stringstream s;
	string str;

	int i=0,j=0;
	while(1) {
		while(!(i = touch.read())) ;
		if(i == j) j = 0;//to avoid twice hitting
		else {
			switch(i) {
				case 1: 
					blue.blink(); 
					fp = popen("who", "r");
					if( fp == NULL) perror("popen() error");
					while(fgets(buffer, 1024, fp)) lcd.puts(string(buffer));
					pclose(fp);
					break;
					
				case 2: 
					yellow.blink(); 
				
					for(int i=0; i<5; i++) {
						s.str("");//clear stringstream or it stacks
						s << range.read_distance();
						str = "distance= " + s.str() + "cm";
						lcd.cursor(0,0);
						lcd.clear();
						lcd.puts(str);
						delay(2000);
					}
					break;
					
				case 3: 
					red.blink(); 
					mt.fw();
					step.clock(100);
					servo.pulse(70);
					//for(int i; i<10; i++) {
					//	servo.pulse(-50 + 10*i);
					//	delay(100);
					//}
					delay(2000);
					mt.bw();
					step.clock(-200);
					servo.pulse(50);
					delay(2000);
					mt.stop();

					lcd.puts(string("3"));
					break;
					
				case 4: 
					green.blink();
					lcd.puts(string("4"));
					break;
					
				case 8: lcd.clear(); break;
				
				case 5: 
					lcd.puts(string("ending"));
					execl("/usr/bin/sudo", "/usr/bin/sudo", "/sbin/shutdown", "-h", "now");
				default: ;
			}
			j = i;
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
