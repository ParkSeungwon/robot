#pragma once
#include "explorerHat.hpp"

class Console
{
public:
	Console();	
	int command_func(int c);

protected:
	std::string command_str[5][5];
	void (Console::*func_ptr[5][5])();
	Lcd lcd;
	
private:
	int next_command();
	int prev_command();
	int command;
	int fd;

	void command_list();
	void w();
	void range_finder();
	void test_motors();
	void I2C_read();
	void I2C_write();
	void shutdown();
	void camera_on();
};


