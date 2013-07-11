/*
 * This Arduino sketch controls a robot with two motors.
 * 
 * The commands are 'l','r','f','b' and come in via Bluetooth attached 
 * to the serial pins 0 and 1 (RX,TX).
 * 
 * The motors are then switched on for a short amount of time to make the
 * robot move a bit forward or backward or to turn left/right.
 * 
 * Apache License 2.0
 * http://www.apache.org/licenses/LICENSE-2.0.html
 * 
 * 2013, Bearstech, Marcus Bauer
 * 
 */


//-----------------------
// variables & constants
//-----------------------

//
// the control pins for speed and direction
//
// motor A
int pinA1	= 8;
int pinA2	= 11;
int speedPinA	= 9;

// motor B
int pinB1	= 12;
int pinB2	= 13;
int speedPinB	= 10;

int  speed = 150;


//------------------------

const int LED = 5;		// a LED on pin 5, nice for debugging. goes on when data on BT received.
boolean btConnectable = false;	// set by the bluetooth board when connected
char cmd = ' ';

//================================================================
// setup
//================================================================
void setup() {

	//
	// motor init
	//
	pinMode(pinA1,OUTPUT);
	pinMode(pinA2,OUTPUT);
	pinMode(speedPinA,OUTPUT);
	
	pinMode(pinB1,OUTPUT);
	pinMode(pinB2,OUTPUT);
	pinMode(speedPinB,OUTPUT);
  
	pinMode(LED, OUTPUT);
  
	//
	// bluetooth stuff
	//
	Serial.begin(38400);
	delay(100);
	// set bluetooth name
	Serial.print("\r\n+STNA=Robot\r\n");
	delay(100);
	// permit paired device to connect
	Serial.print("\r\n+STOAUT=1\r\n"); // 
	delay(100);
	// auto-connection forbidden
	Serial.print("\r\n+STAUTO=0\r\n");
	delay(100);
	// set to slave mode
	Serial.print("\r\n+STWMOD=0\r\n");
	delay(2000); // must be 2000 cf. seed docs
	// make connectable
	Serial.print("\r\n+INQ=1\r\n");
	btConnectable = true;
	delay(500);

	// signalize that we are done with setup()
	//analogWrite(LED_STRIP, 50);
}

//================================================================
// loop()
//================================================================
void loop(){
  
	if (cmd == 'f') {
		forward();
		delay(400);
		stop();
	}
	else if (cmd == 'b') {
		backward();
		delay(400);
		stop();
	}
	else if (cmd == 'l') {
		left();
		delay(120);
		stop();
	}
	else if (cmd == 'r') {
		right();
		delay(120);
		stop();
	}
	
	cmd = ' ';
	digitalWrite(LED, LOW);
}


//================================================================
// serialEvent()
//================================================================
void serialEvent() {
	
	digitalWrite(LED, HIGH);
			
	while (Serial.available()) {

		char inChar = (char)Serial.read(); 

		if (inChar != '\n')
			cmd = inChar;

	}
}

//================================================================
// motor control
//================================================================


void backward()
{
	analogWrite(speedPinA, speed);
	analogWrite(speedPinB, speed);
	digitalWrite(pinB2,HIGH);
	digitalWrite(pinB1,LOW);
	digitalWrite(pinA2,LOW);
	digitalWrite(pinA1,HIGH);
}

void forward()
{
	analogWrite(speedPinA, speed);
	analogWrite(speedPinB, speed);
	
	digitalWrite(pinB2,LOW);
	digitalWrite(pinB1,HIGH);
	digitalWrite(pinA2,HIGH);
	digitalWrite(pinA1,LOW);
}

void left()
{
	analogWrite(speedPinA, speed);
	analogWrite(speedPinB, speed);
	
	digitalWrite(pinB2,HIGH);
	digitalWrite(pinB1,LOW);
	digitalWrite(pinA2,HIGH);
	digitalWrite(pinA1,LOW);
}

void right()
{
	analogWrite(speedPinA, speed);
	analogWrite(speedPinB, speed);
	
	digitalWrite(pinB2,LOW);
	digitalWrite(pinB1,HIGH);
	digitalWrite(pinA2,LOW);
	digitalWrite(pinA1,HIGH);
}

void stop()
{
	digitalWrite(speedPinA,LOW);
	digitalWrite(speedPinB,LOW);
	delay(400);
}
