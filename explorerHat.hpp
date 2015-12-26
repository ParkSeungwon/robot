#pragma once
#include <string>
#include <stdint.h>

enum Color { BLUE = 4, YELLOW = 17, RED = 27, GREEN = 5 };

class Light
{
public:
	Light(Color clr);
	bool status;
	bool on();
	bool off();
	bool toggle();
	bool blink();

protected:
	Color color;
};

class Lcd
{
public:
	Lcd(int data = 15, int clock = 8, int latch = 14);
	void clear();
	void cursor(int x, int y);
	void puts(std::string s);
	
protected:
	int fd;

private:
	int DPIN, CPIN, LPIN;
};

class Touch
{
public:
	Touch();
	int read();//read touch number, none is pressed then return 0

protected:
	int fd;
};

class Input
{
public:
	Input();
	bool read(int i);

protected:
	int in[4];
};

class Pwm
{
public:
	Pwm(int pin=18);
	~Pwm() {pulse(50);}
	int pulse(int pl);//30~90
protected:
	int pin_number;
};

class Motor
{
public:
	Motor(int rf = 26, int rb = 21, int lf = 19, int lb = 20);
	~Motor() {stop();}
	void rf(); void rb(); void rs();
	void lf(); void lb(); void ls();
	void fw(); void bw(); void stop();
	void left(); void right();

private:
	int RF, RB, LF, LB;
};

class Stepper
{
public:
	Stepper(int s1 = 6, int s2 = 12, int s3 = 13, int s4 = 16);
	~Stepper() {to_angle(0);}
	void clock(int step);
	int to_angle(int a);//-128~128 180 degree
	int get_angle() {return angle;}

private:
	int s[4];
	static bool stp[8][4];
	int angle;
	void counter_clock(int step);
};

class RangeFinder
{
public:
	RangeFinder(int trig = 10, int echo = 22);
	int read_distance();

private:
	int ECHO, TRIG;
};

class Analog
{
public:
	Analog(int ch);
	uint16_t read(int gain, uint8_t sampling_bit = 0x0080);

protected:
	int fd;
	uint8_t channel_bit;
	static uint8_t gain_bit[6];
};

