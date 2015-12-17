#include <string>
using namespace std;
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <softPwm.h>
#include <sr595.h>
#include <lcd.h>
#include "explorerHat.hpp"
#include <time.h>


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

Light::Light(Color c)
{
	pinMode(c, OUTPUT);
	color = c;
	status = false;
}

bool Light::on()
{
	digitalWrite(color, HIGH);
	status = true;
	return status;
}

bool Light::blink()
{
	digitalWrite(color, HIGH);
	delay(100);
	digitalWrite(color, LOW);
	return status = false;
}

bool Light::off()
{
	digitalWrite(color, LOW);
	status = false;
	return status;
}

bool Light::toggle()
{
	if(status) off();
	else on();
	return status;
}

Lcd::Lcd(int data, int clock, int latch)
{
	DPIN = data; CPIN = clock; LPIN = latch;
	sr595Setup(100, 6, DPIN, CPIN, LPIN);
	fd = lcdInit(2, 16, 4, 100, 101, 102, 103, 104, 105, 0, 0, 0, 0);
}

void Lcd::puts(string s) {
	lcdPuts(fd, s.c_str());
	printf("%s", s.c_str());
}

Touch::Touch()
{
	fd = wiringPiI2CSetup(0x28);
	wiringPiI2CWrite(fd, 0x0);
}

int Touch::read()
{
	if(wiringPiI2CReadReg8(fd, 0) == 1) {
		int v = wiringPiI2CReadReg8(fd, 3);
	//	printf("val=%d", v);
		wiringPiI2CWriteReg8(fd, 0, 0);
		wiringPiI2CWriteReg8(fd, 3, 0);
	
		switch(v) {
			case 0x10: return 1;
			case 0x20: return 2;
			case 0x40: return 3;
			case 0x80: return 4;
			case 0x1: return 5;
			case 0x2: return 6;
			case 0x4: return 7;
			default: return 8;
		}
	}
	return 0;
}

Pwm::Pwm(int pin)
{
	pinMode(pin, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(400);
	pwmSetRange(1024);
	pin_number = pin;
}

int Pwm::pulse(int pl)
{
	if(pl < 30) pl = 30;
	if(pl > 90) pl = 90;
	pwmWrite(pin_number, pl);
	digitalWrite(pin_number, LOW);
	return pl;
}

Motor::Motor(int rf, int rb, int lf, int lb)
{
	RF = rf; RB = rb; LF = lf; LB = lb;
	pinMode(26, OUTPUT);//RF
	pinMode(21, OUTPUT);//RB
	pinMode(19, OUTPUT);//LF
	pinMode(20, OUTPUT);//LB
}

void Motor::rf()
{
	digitalWrite(RF, HIGH);
	digitalWrite(RB, LOW);
}

void Motor::rb()
{
	digitalWrite(RB, HIGH);
	digitalWrite(RF,LOW);
}

void Motor::rs()
{
	digitalWrite(RF, LOW);
	digitalWrite(RB, LOW);
}

void Motor::ls()
{
	digitalWrite(LF, LOW);
	digitalWrite(LB, LOW);
}

void Motor::lf()
{
	digitalWrite(LF, HIGH);
	digitalWrite(LB, LOW);
}

void Motor::lb()
{
	digitalWrite(LB, HIGH);
	digitalWrite(LF, LOW);
}

void Motor::fw()
{
	rf();
	lf();
}

void Motor::bw()
{
	rb();
	lb();
}

void Motor::stop()
{
	rs();
	ls();
}

void Motor::left()
{
	rf();
	ls();
}

void Motor::right()
{
	lf();
	rs();
}

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
