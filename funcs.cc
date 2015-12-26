#include "console.h"
#include <sstream>
#include <unistd.h>
using namespace std;

void Console::command_list() {
	lcd.clear();
	int k = 0;
	for(int i=0; i<=4; i++) {
		for(int j=0; j<=4; j++) {
			if(command_str[i][j] != "") {//cannot use member in static func
				s.str("");
				s << i*10+j;
				st = s.str() + string(". ") + command_str[i][j];
				lcd.cursor(0, k++ % 2);
				lcd.puts(st);
				for(int i=0; i<16-st.length(); i++) lcd.puts(string(" "));	
				delay(1000);
			}
		}
	}
}

void Console::w() {
	FILE* fp = popen("who", "r");
	if(fp == NULL) perror("popen() error");
	while(fgets(buffer, 1024, fp)) lcd.puts(string(buffer));
	pclose(fp);
	delay(2000);
}

void Console::range_finder() {
	RangeFinder range;
	stringstream s;
	for(int i=0; i<5; i++) {
		lcd.clear();
		s.str("");//clear stringstream or it stacks
		s << range.read_distance();
		st = "distance= " + s.str() + "cm";
		s.str("");
		s << step.get_angle();
				
		lcd.cursor(0,0);
		lcd.puts(st);
		lcd.cursor(0,1);
		st = "at angle " + s.str();
		lcd.puts(st);
		delay(2000);
	}
}

void Console::test_motors() {
	Motor mt;
	Stepper step;
	mt.fw();
	step.clock(100);
			//servo.pulse(70);
			//for(int i; i<10; i++) {
			//	servo.pulse(-50 + 10*i);
			//	delay(100);
			//}
	delay(2000);
	mt.bw();
	step.clock(-200);
		//servo.pulse(50);
	delay(2000);
	mt.stop();

	lcd.puts(string("3"));
}

void Console::shutdown() {
	lcd.puts(string("ending"));
	execl("/usr/bin/sudo", "/usr/bin/sudo", "/sbin/shutdown", "-h", "now");
}

void Console::camera_on() {
	lcd.puts(string("camera on"));
	execl("raspvid", "raspvid", "-t", "999999", "-w", "800", "-h", "600", "-o", "–", "|", "nc", "192.168.0.5", "5001");
}

void Console::I2C_read() {
	stringstream s;
	FILE* fd;
	s.str("");
	s << wiringPiI2CRead(fd);
	lcd.clear();
	lcd.puts(s.str());
	delay(2000);

}

void Console::I2C_write() {
	wiringPiI2CWrite(fd, 30);
}
