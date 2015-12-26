#include "explorerHat.hpp"
#include <wiringPi.h>

Motor::Motor(int rf, int rb, int lf, int lb)
{
	RF = rf; RB = rb; LF = lf; LB = lb;
	pinMode(RF, OUTPUT);//RF
	pinMode(RB, OUTPUT);//RB
	pinMode(LF, OUTPUT);//LF
	pinMode(LB, OUTPUT);//LB
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


