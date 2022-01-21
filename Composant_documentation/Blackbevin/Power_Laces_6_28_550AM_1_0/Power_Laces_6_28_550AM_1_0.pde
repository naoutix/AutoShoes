#include <Servo.h>

Servo myservo; // creates servo objects
Servo myservo2; 

int forcePin = 0; // analog pin 0 connected to force sensor
int ledPin = 2; // digital pin 2 connected to LED
int switchPin = 19;  // sets unlock switch to analog pin 5
int valF;  // value of force sensor
int valS; // value of switch
int thresHold = 500; // defines force sensor pressure threshold
int servoUnlock = 0; // sets main servo to neutral unlaced position (0 degrees)
int servoLock = 180;  // sets main servo to laced position (180 degrees)
int servoUnlock2 = 180; // sets auxillary servo to neutral unlaced position (0 degrees)
int servoLock2 = 0; // sets auxillary servo to laced position (180 degrees)

void setup()
{
  pinMode(ledPin, OUTPUT); // digital pin 2 is output for LED
  pinMode(switchPin, INPUT);  // analog pin 5 is input for switch
  myservo.attach(9); // attaches the servos to pins 9 and 10
  myservo2.attach(10); 
  myservo.write(servoUnlock);  // move both servos into unlaced positions
  myservo2.write(servoUnlock2);
}

void loop() 
{
  valF = analogRead(forcePin); // read value of force sensor
  valS = digitalRead(switchPin); // read value of switch
  
  if (valF>=thresHold) { // waits for force sensor to equal or pass pressure threshold and then:
    delay(1000); // waits for foot to settle into place in shoe
    myservo2.write(servoLock2); // sets auxillary servo to locked position
    delay(1000);  // waits one second
    myservo.write(servoLock);  // sets main servo to locked position
    delay(1000);  // waits one second
    digitalWrite(ledPin, HIGH);  // turns on LED untill servo unlocked. Remove this line to save battery life.
    }
    
    if (valS == HIGH) {  // waits for switch to be pressed, and then:
      myservo2.write(servoUnlock2); // unlocks auxillary servo
      delay(1000);  // waits two seconds
      myservo.write(servoUnlock);  // unlocks main servo
      delay(500);  // wait, then blink LED 7 times
      digitalWrite(ledPin, LOW);
      delay(200);
      digitalWrite(ledPin, HIGH);
      delay(200);
        digitalWrite(ledPin, LOW);
      delay(200);
      digitalWrite(ledPin, HIGH);
      delay(200);
        digitalWrite(ledPin, LOW);
      delay(200);
      digitalWrite(ledPin, HIGH);
      delay(200);
        digitalWrite(ledPin, LOW);
      delay(200);
      digitalWrite(ledPin, HIGH);
      delay(200);
        digitalWrite(ledPin, LOW);
      delay(200);
      digitalWrite(ledPin, HIGH);
      delay(200);
        digitalWrite(ledPin, LOW);
      delay(200);
      digitalWrite(ledPin, HIGH);
      delay(200);
        digitalWrite(ledPin, LOW);
      delay(200);
      digitalWrite(ledPin, HIGH);
      delay(200);
      digitalWrite(ledPin, LOW); // turns LED off
      delay(1000);
    }

}

