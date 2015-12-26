#include "explorerHat.hpp"
#include <wiringPi.h>

RangeFinder::RangeFinder(int trig, int echo)
{
	ECHO = echo;
	TRIG = trig;
	pinMode(ECHO, INPUT);
	pinMode(TRIG, OUTPUT);
}

int RangeFinder::read_distance()
{
	clock_t start, stop;
	digitalWrite(TRIG, HIGH);
	delay(1);
	digitalWrite(TRIG, LOW);
	while(digitalRead(ECHO) == 0);
	start = micros();
	while(digitalRead(ECHO) == 1);
	stop = micros();
	//printf("start= %d", start);
	//printf("stop= %d", stop);
	return (stop - start)/40;
}

