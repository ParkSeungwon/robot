#include "explorerHat.hpp"
#include <wiringPi.h>

bool Stepper::stp[8][4] = {
		{1,0,0,0},
		{1,1,0,0},
		{0,1,0,0},
		{0,1,1,0},
		{0,0,1,0},
		{0,0,1,1},
		{0,0,0,1},
		{1,0,0,1}
};

Stepper::Stepper(int s1, int s2, int s3, int s4)
{
	s[0] = s1; s[1] = s2; s[2] = s3; s[3] = s4;
	angle = 0;
	pinMode(s[0], OUTPUT);
	pinMode(s[1], OUTPUT);
	pinMode(s[2], OUTPUT);
	pinMode(s[3], OUTPUT);
}

void Stepper::counter_clock(int step)
{
	for(int k=0; k<step; k++){
		for(int i=0; i<8; i++) {
			for(int j=0; j<4; j++) {
				digitalWrite(s[j], stp[i][j]);
			}
			delay(1);
		}
		angle--;
	}
}

void Stepper::clock(int step)
{
	if(step < 0) counter_clock(-step);
	else {	
		for(int k=0; k<step; k++) {
			for(int i=0; i<8; i++) {
				for(int j=0; j<4; j++) {
					digitalWrite(s[j], stp[7-i][j]);
				}
				delay(1);
			}
			angle++;
		}
	}
}

int Stepper::to_angle(int a)
{
	if(a > 128) a = 128;
	if(a < -128) a = -128;
	int move = a - angle;
	clock(move);
	return angle = a;
}


