#include <stdio.h>
#include <softPwm.h>
#include "explorerHat.hpp"
#include <wiringPi.h>
using namespace std;

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

Input::Input() {
	in[0] = 23;
	in[1] = 22;
	in[2] = 24;
	in[3] = 25;
	for(int i=0; i<4; i++) pinMode(in[i], INPUT);
}

bool Input::read(int num) {
	return digitalRead(in[num-1]);
}
