#include "explorerHat.hpp"
#include <wiringPiI2C.h>

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


