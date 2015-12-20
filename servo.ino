int servopin=9;// Define the digital interface #9,connect servo signal wire
int myangle;// Define Angle variables
int pulsewidth;// Define Pulse width variables
int val;

void servopulse(int servopin,int myangle)// Define a pulse function
{
	pulsewidth=(myangle*11)+500;//Turn the angle into Pulse width value 500-2480
	digitalWrite(servopin,HIGH);// Turn up the servo interface level
	delayMicroseconds(pulsewidth);//Delay the microseconds of the pulse width value
	digitalWrite(servopin,LOW);// Turn down the servo interface level

	delay(20-pulsewidth/1000);
}

void setup()
{
	pinMode(servopin,OUTPUT);// Set servo interface as output
	Serial.begin(9600);//Connect to serial port,baud rate is 9600. Serial.println("servo=o_seral_simple ready" ) ;
}

void loop()//Turn 0-9 into 0-180 degree angle, and make the LED blink relevantly.
{
	val=Serial.read();//Read serial ports value
	if(val>'0'&&val<='9')
	{
		val=val-'0';// Turn characteristic quantity into numerical variable
		val=val*(180/9);// Turn figure into angle degree 
		Serial.print("moving servo to ");
		Serial.print(val,DEC);
		Serial.println();
		for(int i=0;i<=50;i++) // Give the servo enough time to rotate to appointed angle
		{
		servopulse(servopin,val);//Quote pulse function
		}
	}
}
