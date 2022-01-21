/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/

// the setup routine runs once when you press reset:
double sensorValue=0;
double old =0;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  //int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  //float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  //Serial.println(1000*voltage/(5-voltage));
  //int temps = micros();
  double sensorValue=mesureB(20);
  //temps = micros()-temps;
  //Serial.println(temps);
  //Serial.println(sensorValue);
  //Serial.println((sensorValue-513)* 11.137);
  Serial.println((sensorValue-old)*11.137);
  delay(1);
  old = sensorValue;
  
}

float mesureB(int x)
{
  long unsigned int Sensormoy = 0;
  for (int i=1;i<=x;i++){
    int sensorValue = analogRead(A0); 
    Sensormoy=Sensormoy+sensorValue;
  }
  float moy=Sensormoy/x;
  return moy;
}
