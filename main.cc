#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <iostream>
#include <lcd.h>
#include <string>
#include <unistd.h>

using namespace std;
#include "explorerHat.hpp"

PI_THREAD(range_thread)
{
	RangeFinder range;
	while(1) {
		printf("distance = %d cm\n", range.read_distance());
		delay(2000);
	}
}

PI_THREAD(touch_thread)
{
	Touch touch;
	Lcd lcd;
	Light red(RED);
	Light blue(BLUE);
	Light green(GREEN);
	Light yellow(YELLOW);
	int i=0,j=0;
	while(1) {
		while(!(i = touch.read())) ;
		if(i == j) j = 0;//to avoid twice hitting
		else {
			switch(i) {
				case 1: 
					blue.blink(); 
					lcd.puts(string("1"));
					break;
				case 2: 
					yellow.blink(); 
					lcd.puts(string("2")); 
					break;
				case 3: 
					red.blink(); 
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
}	


int main()
{
	wiringPiSetupGpio();
	
	piThreadCreate(range_thread);
	piThreadCreate(touch_thread);

	char ch;
	Motor mt;
	Pwm servo;
	Stepper step;
	int p = 50;
	int a = 0;
	while(1) {
		switch(ch = getchar()) {
			case '7': mt.lf(); break;
			case '9': mt.rf(); break;
			case '1': mt.lb(); break;
			case '3': mt.rb(); break;
			case '5': mt.stop(); break;
			case 'w': servo.pulse(p += 10); break;
			case 's': servo.pulse(p -= 10); break;
			case 'a': step.clock(a = -10); break;
			case 'd': step.clock(a = 10); break;
			case '4': mt.left(); break;
			case '6': mt.right(); break;
			case '8': mt.fw(); break;
			case '2': mt.bw(); break;
			case 'q': return 0;
			default: ; 
		}
	}
}
