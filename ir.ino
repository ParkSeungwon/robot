//This is source for arduino side.
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
int rpin = 3, bpin = 5, gpin = 6;
int xval, yval, kval;
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
	pinMode(13, OUTPUT);
	pinMode(servo1_pin, OUTPUT);
	pinMode(servo1_pin, OUTPUT);
	pinMode(rpin, OUTPUT);
	pinMode(gpin, OUTPUT);
	pinMode(bpin, OUTPUT);
	Serial.begin(9600); // start serial for output
	// initialize i2c as slave
	Wire.begin(SLAVE_ADDRESS);

	// define callbacks for i2c communication
	Wire.onReceive(receiveData);
	Wire.onRequest(sendData);
	irrecv.enableIRIn();
	Serial.println("Ready!");
	analogWrite(rpin, 255);
	analogWrite(bpin, 255);
	analogWrite(gpin, 255);
}

void loop() {
    if(irrecv.decode(&results)) {
		data_to_send = results.value;
		if(data_to_send == 0xff02fd) {
			analogWrite(bpin, 0);//+
			delay(1000);
			analogWrite(bpin, 255);
		}
		else if(data_to_send == 0xff9867) analogWrite(rpin, 0); //-
		else if(data_to_send == 0xffb04f) analogWrite(gpin, 0); //C
		else if(data_to_send == 0xff6897) servopulse(servo2_pin, angle2 -= 10);//0
		Serial.println(results.value, HEX);
		irrecv.resume();
    }

	xval = analogRead(xpot);
	yval = analogRead(ypot);
	kval = analogRead(kpot);
	if(xval<400 || xval>600) {
		angle2 = xval * 180 / 1024;//does not get proper calculation->float?
		servopulse(servo2_pin, angle2);
		Serial.println(angle2);
	}
	if(yval<400 || yval>600) {
		angle1 = yval /5;
		Serial.println("yval:");
		Serial.println(angle1);
		servopulse(servo1_pin, angle1);
	}
	if(kval < 500) {
		Serial.println("On");
		analogWrite(rpin, 255);
		analogWrite(bpin, 255);
		analogWrite(gpin, 255);
	}
}

// callback for received data
void receiveData(int byteCount){
	while(Wire.available()) {
		number = Wire.read();
		Serial.print("data received: ");
		Serial.println(number);
		if(number == 30) {
			int i;
			analogWrite(rpin,255);
			analogWrite(bpin,255);
			analogWrite(gpin,255);  //off
			analogWrite(rpin,0);
			delay(1000);    //hong
			analogWrite(gpin,220);
			delay(1000);   //cheng
			analogWrite(rpin,0);
			analogWrite(gpin,120);
			delay(1000);   //huang
			analogWrite(rpin,255);
			analogWrite(gpin,0);
			delay(1000);   //lv  
			analogWrite(bpin,0);
			delay(1000);   //qing
			analogWrite(gpin,255);
			analogWrite(bpin,0);
			delay(1000);   //lan
			analogWrite(rpin,0);
			analogWrite(gpin,255);
			delay(1000);   //zi 
			analogWrite(gpin,0);
			delay(1000);   //bai   
			for(i=255;i>0;i--) {
				analogWrite(rpin,i);
				delay(10);
			}
			for(i=255;i>0;i--) {
				analogWrite(gpin,i);
				delay(10);
			}
			for(i=0;i<255;i++) {
				analogWrite(rpin,i);
				delay(10);
			}
			for(i=255;i>0;i--) {
				analogWrite(bpin,i);
				delay(10);
			}
			for(i=0;i<255;i++) {
				analogWrite(gpin,i);
				delay(10);
			}
			for(i=255;i>0;i--) {
				analogWrite(rpin,i);
				delay(10);
			}
			analogWrite(gpin,0);
			analogWrite(bpin,0);
			analogWrite(rpin,0);
		}
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



