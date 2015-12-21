#include <Wire.h>
#include <IRremote.h>
#define SLAVE_ADDRESS 0x04
int data_to_send = 0;
int number;
int RECV_PIN = 11;
int servo1_pin = 9, servo2_pin = 10;
int angle1 = 0, angle2 = 0;
int pulsewidth;
int xpot = 0, ypot = 1, kpot = 2;
int xval, yval, kval;
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
	pinMode(13, OUTPUT);
	pinMode(servo1_pin, OUTPUT);
	Serial.begin(9600); // start serial for output
	// initialize i2c as slave
	Wire.begin(SLAVE_ADDRESS);

	// define callbacks for i2c communication
	Wire.onReceive(receiveData);
	Wire.onRequest(sendData);
	irrecv.enableIRIn();
	Serial.println("Ready!");
}

void loop() {
    if(irrecv.decode(&results)) {
		data_to_send = results.value;
		if(data_to_send == 0xff02fd) servopulse(servo1_pin, angle1 +=10);//+
		else if(data_to_send == 0xff9867) servopulse(servo1_pin, angle1 -=10);//-
		else if(data_to_send == 0xffb04f) servopulse(servo2_pin, angle2 += 10);//C
		else if(data_to_send == 0xff6897) servopulse(servo2_pin, angle2 -= 10);//0
		Serial.println(results.value, HEX);
		irrecv.resume();
    }

	xval = analogRead(xpot);
	yval = analogRead(ypot);
	kval = analogRead(kpot);
	if(xval<400 || xval>600 || yval<400 || yval>600 || kval<500) {
		angle1 = yval * 180/1010;
		angle2 = xval * 180/1010;
		servopulse(servo1_pin, angle1);
		servopulse(servo2_pin, angle2);
		Serial.println(xval);
		Serial.println(yval);
		if(kval < 500) Serial.println("On");
		else Serial.println("Off");
	}

//	Serial.println(data_to_send);
	if(analogRead(kpot)<500) Serial.println("ON");
	else Serial.println("Off");
    delay(500);
}

// callback for received data
void receiveData(int byteCount){
	while(Wire.available()) {
		number = Wire.read();
		Serial.print("data received: ");
		Serial.println(number);
		if(number == 30) ;
	}
}


// callback for sending data
void sendData(){
	Wire.write(data_to_send);
}

void servopulse(int servopin,int myangle)// Define a pulse function
{
	pulsewidth=(myangle*11)+500;//Turn the angle into Pulse width value 500-2480
	digitalWrite(servopin,HIGH);// Turn up the servo interface level
	delayMicroseconds(pulsewidth);//Delay the microseconds of the pulse width value
	digitalWrite(servopin,LOW);// Turn down the servo interface level

	delay(20-pulsewidth/1000);
}



