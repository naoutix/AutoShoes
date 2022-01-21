//-- MOTEUR A --
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

//-- Capteur courant --
float OFFSET =2.500650408-0.0480952;

//--Bouton--
int BoutonOFFSET = 4;
int BoutonLACE   = 12;
int BoutonUN     = 7;
int BoutonPULSE  = 8;

//RGB
const byte PIN_LED_R = 9;
const byte PIN_LED_G = 10;
const byte PIN_LED_B = 11;

boolean etatBouton;
boolean Lace;
boolean pulse;  
boolean un;



// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  AFMS.begin();
  
  //Configurer les broches comme sortie
  // Moteur A - Ne pas tourner (désactivation moteur)
  myMotor->setSpeed(255);
  
  // Direction du Moteur A

  //Bouton
  pinMode(BoutonOFFSET,INPUT);
  pinMode(BoutonLACE,INPUT);
  pinMode(BoutonUN,INPUT);
  pinMode(BoutonPULSE,INPUT);
  
  //RGB
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  displayColor(0, 128, 0);

  //Initialise
  intitialise();
}


// the loop routine runs over and over again forever:
void loop() {
  myMotor->run(RELEASE);
  displayColor(15, 32, 32);
  //Fonctions ingenieurs
   etatBouton  = digitalRead(BoutonOFFSET);
   Lace        = digitalRead(BoutonLACE);
   pulse       = digitalRead(BoutonPULSE);
   un          = digitalRead(BoutonUN);
  //Serial.println(etatBouton);
  /*while (etatBouton){
    intitialise();
    etatBouton  = digitalRead(BoutonOFFSET);
    }
   */
  float mesure =(mesureB(255,A0)-OFFSET)*0.66*1000*5/1023;
  Serial.println(mesure,4);
  while (Lace){
    displayColor(128,0,0);  
    lacage(255,255,A0);
    Lace        = digitalRead(BoutonLACE);
    }
  while (pulse){
    displayColor(0,128,0); 
    myMotor->run(FORWARD);
    delay(100);
    pulse       = digitalRead(BoutonPULSE);
    }
  while (un){
    displayColor(0,128,0);
    myMotor->run(BACKWARD);
    delay(100);
    un          = digitalRead(BoutonUN);
    }
}




void displayColor(byte r, byte g, byte b) {
  // Version anode commune
  analogWrite(PIN_LED_R, r);
  analogWrite(PIN_LED_G, g);
  analogWrite(PIN_LED_B, b);
}



float mesureB(int x,char broche){
  
  unsigned int Sensormoy = 0;
  
  for (int i=1;i<=x;i++){
    unsigned int sensorValue = analogRead(broche); 
    Sensormoy+=sensorValue;
  }
  return Sensormoy/x;
}


void intitialise(){
  OFFSET=mesureB(255,A0);
  }


void lacage(int vit,int moy,char broche){
  float mesure =(mesureB(255,A0)-OFFSET)*0.66*1000*5/1023;
  intitialise();
  myMotor->run(FORWARD);
  delay(400);
  while(mesure <= 30){
      mesure =(mesureB(255,A0)-OFFSET)*0.66*1000*5/1023;
      Serial.println(mesure,4);
    }
 Serial.println(mesure,4);  
   
  }
