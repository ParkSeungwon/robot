#include "console.h"
#include <sstream>

Console::Console() {
	command_str[0][1] = "command list";
	command_str[1][2] = "w";
	command_str[0][2] = "range finder";
	command_str[0][3] = "test motors";
	command_str[0][4] = "I2C write";
	command_str[1][1] = "I2C read";
	command_str[4][4] = "shutdown";
	command_str[1][3] = "camera on";
	
	func_ptr[0][1] = &command_list;
	func_ptr[1][2] = &w;
	func_ptr[0][2] = &range_finder;
	func_ptr[0][3] = &test_motors;
	func_ptr[0][4] = &I2C_write;
	func_ptr[1][1] = &I2C_read;
	func_ptr[4][4] = &shutdown;
	func_ptr[1][3] = &camera_on;
}


int Console::command_func(int i) {
	std::stringstream s;
	if(i >= 1 && i <= 4) {
		command = 10 * command + i;
		if(command > 99) command /= 10;
	}
	else if(i == 8) func_ptr[command/10][command%10]();
	else if(i == 7) command = command / 10; 
	else if(i == 5) command = next_command();
	else if(i == 6) command = prev_command();

	s.str("");
	s << command;
	lcd.clear();
	lcd.cursor(0, 0);
	lcd.puts(s.str());
	
	lcd.puts(". ");
	lcd.puts(command_str[command/10][command%10]);
	lcd.cursor(0,1);
	lcd.puts("8:x,7:<-,5:+,6:-");
	return command;
}


int Console::next_command() {
	for(int i=0; i<=4; i++) {
		for(int j=0; j<=4; j++) {
			if(command_str[i][j] != "") {
				if(i*10+j > command) return i*10+j;
			}
		}
	}
	return 1;// circle  to first
}

int Console::prev_command() {
	for(int i=4; i>=0; i--) {
		for(int j=4; j>=0; j--) {
			if(command_str[i][j] != "") {
				if(i*10+j < command) return i*10+j;
			}
		}
	}
	return 44;//circle to last
}


