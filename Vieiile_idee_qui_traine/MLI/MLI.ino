/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/

unsigned long Te=200;
long double sensorValue = 0;
unsigned long delta=0;
#define OFFSET 2.5

void setup() {  
  Serial.begin(9600);
}



void loop() {
  // read the input on analog pin 0:
  sensorValue = 0;
  int count = 0;
  delta =0;
  unsigned long timer = millis();
  while (delta <= Te)
  { 
   sensorValue += analogRead(A0);
   count++;
   delta =millis()-timer;

  }
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0)/count;
  // print out the value you read:
  Serial.println((voltage-2.5));
}
