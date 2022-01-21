  /*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
long int baudRate = 9600;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(baudRate);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  while (!Serial) {
    ;               // wait for serial port to connect. Needed for native USB port only
  }

  mySerial.begin(baudRate);// set the data rate for the SoftwareSerial port
  Serial.print("BTserial started at "); Serial.println(baudRate);
  Serial.println("Goodnight moon!");
  mySerial.println("Hello, world?");
}

void loop() {
  if (mySerial.available()) {
    Serial.print("Leo:");
    while (mySerial.available()>0){
      
    
    Serial.write(mySerial.read());
    delay(1);
    }
  }
  if (Serial.available()) {
    
    Serial.print("You:");
    while (Serial.available()>0){
    char c= Serial.read();
    Serial.print(c);
    mySerial.write(c);
    delay(1);
    }
  }
}
