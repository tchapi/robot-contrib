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


#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 6
#define TxD 7

#define DEBUG_ENABLED  1
 
SoftwareSerial blueToothSerial(RxD,TxD);

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
  
        Serial.begin(9600);
        pinMode(RxD, INPUT);
        pinMode(TxD, OUTPUT);
        setupBlueToothConnection();
        //wait 1s and flush the serial buffer
        delay(1000);
        Serial.flush();
        blueToothSerial.flush();

}

void setupBlueToothConnection()
{
  blueToothSerial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
  blueToothSerial.print("\r\n+STWMOD=0\r\n");//set the bluetooth work in master mode
  blueToothSerial.print("\r\n+STNA=Robot\r\n");//set the bluetooth name as "SeeedBTMaster"
  blueToothSerial.print("\r\n+STOAUT=1\r\n");
  blueToothSerial.print("\r\n+STAUTO=0\r\n");// Auto-connection is forbidden here
  delay(2000); // This delay is required.
  blueToothSerial.print("\r\n+INQ=1\r\n");//make the master inquire
  Serial.println("Done setuping Bluetooth.");
  delay(2000); // This delay is required.
  btConnectable = true;
}

//================================================================
// doAction()
//================================================================
void doAction(char cmd) {
	
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
}

//================================================================
// loop()
//================================================================
void loop(){

  char recvChar;
  while(1){
    if(blueToothSerial.available()){//check if there's any data sent from the remote bluetooth shield
      digitalWrite(LED,HIGH);
      recvChar = blueToothSerial.read();
      Serial.print(recvChar);
      doAction(recvChar);
    }
    if(Serial.available()){//check if there's any data sent from the local serial terminal, you can add the other applications here
      recvChar  = Serial.read();
      blueToothSerial.print(recvChar);
    }
    digitalWrite(LED,LOW);
  }
  
}

//================================================================
// motor control
//================================================================


void backward()
{
	analogWrite(speedPinA, speed);
	analogWrite(speedPinB, speed);

	digitalWrite(pinB2,LOW);
	digitalWrite(pinB1,HIGH);
	digitalWrite(pinA2,HIGH);
	digitalWrite(pinA1,LOW);
}

void forward()
{
	analogWrite(speedPinA, speed);
	analogWrite(speedPinB, speed);
	
	digitalWrite(pinB2,HIGH);
	digitalWrite(pinB1,LOW);
	digitalWrite(pinA2,LOW);
	digitalWrite(pinA1,HIGH);
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
