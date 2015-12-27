#include <wiringPi.h>
#include "console.h"
using namespace std;

int main()
{
	char ch;
	
	int p = 50;
	int a = 0;
	
	Touch touch;
	Light red(RED);
	Light blue(BLUE);
	Light green(GREEN);
	Light yellow(YELLOW);

	string str;

	int i=0,j=0;
	Console con;
	while(1) {
		while(!(i = touch.read())) ;
		if(i == j) j = 0;//to avoid twice hitting
		else {
			switch(i) {
				case 1: blue.blink(); break;		
				case 2: yellow.blink(); break;
				case 3: red.blink(); 	break;
				case 4: green.blink(); 	break;
				default: ;
			}
			j = i;
			con.command_func(i);
		}
	}
}

