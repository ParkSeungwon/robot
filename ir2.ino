#include <Wire.h>
#include <IRremote.h>
#define SLAVE_ADDRESS 0x04
int data_to_send = 0;
int number;
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
	pinMode(13, OUTPUT);
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
	Serial.println(results.value, HEX);
        irrecv.resume();
    }
    delay(100);
}

// callback for received data
void receiveData(int byteCount){
	while(Wire.available()) {
		number = Wire.read();
		Serial.print("data received: ");
		Serial.println(number);

		if (number == 30){
		}
	}
}


// callback for sending data
void sendData(){
	Wire.write(data_to_send);
}




