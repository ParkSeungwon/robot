#include "explorerHat.hpp"
#include <wiringPiI2C.h>
#include <wiringPi.h>

uint8_t Analog::gain_bit[6] = { 0x0000, 0x0200, 0x0400, 0x0600, 0x0800, 0x0A00};
//								6144	4096	2048	1024	512		256
Analog::Analog(int ch)
{
	fd = wiringPiI2CSetup(0x48);
	wiringPiI2CWrite(fd, 0x0);
	switch(ch-1) {
		case 0: channel_bit = 0x4000; break;
		case 1: channel_bit = 0x5000; break;
		case 2: channel_bit = 0x6000; break;
		case 3: channel_bit = 0x7000; break;
		default: channel_bit = 0x4000;
	}
}

uint16_t Analog::read(int gain, uint8_t sampling_bit)
{
	uint8_t bit = 0x0003 | 0x0100 | 0x8000;
	bit |= channel_bit;
	bit |= sampling_bit;//default is 1600 per second
	if(gain > 5) gain = 5;
	else if(gain < 0) gain = 0;
	bit |= gain_bit[gain];

	int sampling_per_second;
	switch(sampling_bit) {
		case 0x0080: sampling_per_second = 1600; break;
		case 0x0000: sampling_per_second = 128; break;
		case 0x0020: sampling_per_second = 250; break;
		case 0x0040: sampling_per_second = 490; break;
		case 0x0060: sampling_per_second = 920; break;
		case 0x00A0: sampling_per_second = 2400; break;
		case 0x00C0: sampling_per_second = 3300; break;
		default: sampling_per_second = 1600; 
	}
	int d = 1000 / sampling_per_second + 1;
	uint16_t data;
	wiringPiI2CWriteReg8(fd, 1, bit);
	delay(d);
	data = wiringPiI2CReadReg16(fd, 0);
	return data;
}

