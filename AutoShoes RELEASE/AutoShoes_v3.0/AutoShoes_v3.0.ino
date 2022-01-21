//-- Timer --
#include <TimerOne.h>
#define Te 400000

//-- Capteur vitesse --
volatile int count      = 0;
volatile double vitesse = 0;
#define interupt 0
#define PPR 341.2

//-- Moteur CC --
/*
  Modèle fait selon la bibilothèque Adafruit
  Carte     : AFMS
  Motor M1  : myMotor
  
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

//-- Capteur courant --
float OFFSET =2.500650408-0.0480952;

//-- Interface Users  --
#define BoutonLACE   12
#define BoutonUN     7                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
#define BoutonPULSE  8
boolean Lace;
boolean pulse;  
boolean un;

//-- RGB --
#define PIN_LED_R 5
#define PIN_LED_G 6
#define PIN_LED_B 11


void setup() 
{
  //--Init Bluetooth
  Serial.begin(baudRate);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.print("BTserial started at "); Serial.println(baudRate);
  Serial.println("Goodnight moon!"); //Test
  
  //Ativation Carte Adafruit Motor Shield v2.3
  AFMS.begin();

  //init
  myMotor->setSpeed(255);

  //Capteur vitesse
  pinMode(2,INPUT_PULLUP);

  //Interface Users
  pinMode(BoutonLACE,INPUT);
  pinMode(BoutonUN,INPUT);
  pinMode(BoutonPULSE,INPUT);
  
  //RGB
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  displayColor(0, 128, 0);

  //Initialise capteur courant
  intitialise();
}



void loop() 
{
  //Default setting
  myMotor->run(RELEASE);
  displayColor(15, 32, 32);
  intitialise();
  
  //Scan users
   Lace        = digitalRead(BoutonLACE);
   pulse       = digitalRead(BoutonPULSE);
   un          = digitalRead(BoutonUN);

   //mesure courant
  float mesure =(mesureB(255,A0)-OFFSET)*0.66*1000*5/1023;
  //mesuretab(0,mesure);
  
  //Action users

  // MODE LACAGE
  while (Lace){
    displayColor(128,0,0);  
    lacage(255,255,A0);
    Lace        = digitalRead(BoutonLACE);
    blinkRGB();
    }
    
  // MODE REGLAGE MANUELLE +
  while (pulse){
    displayColor(0,128,0); 
    myMotor->run(FORWARD);
    delay(100);
    pulse       = digitalRead(BoutonPULSE);
    }
  
  // MODE REGLAGE MANUELLE -
  while (un){
    displayColor(0,128,0);
    myMotor->run(BACKWARD);
    delay(100);
    un          = digitalRead(BoutonUN);
    }


    
}



// -- Permet de changer de Couleur de la RGB --
void displayColor(byte r, byte g, byte b) 
{
  // Version anode commune
  analogWrite(PIN_LED_R, r);
  analogWrite(PIN_LED_G, g);
  analogWrite(PIN_LED_B, b);
}


// -- Mesure une moyenne sur x mesure sur la dite broche --

float mesureB(int x,char broche)
{
  
  unsigned int Sensormoy = 0;
  
  for (int i=1;i<=x;i++){
    unsigned int sensorValue = analogRead(broche); 
    Sensormoy+=sensorValue;
  }
  return Sensormoy/x;
}


// -- OFFSET --
void intitialise()
{
  OFFSET=mesureB(255,A0);
  }


// -- Fonctions Capteur de vitesse --
void tops ()
{
  count++;
  }
  
void timerIsr()
{
  vitesse = count;
  count=0;
}


// -- LACAGE --
void lacage(int vit,int moy,char broche)
{
  //Capteur vitesse
  mesuretab(1,0,0);

  //Capteur Courant
  float mesure =(mesureB(255,A0)-OFFSET)*0.66*1000*5/1023;

  //Demarage Moteur
  myMotor->setSpeed(vit);
  myMotor->run(FORWARD);

  //Temps d'init du capteur
  delay(200);
  intitialise();
  
  //Temps minimal d'execution
  delay(200);

  float Aread=0;
  //Attente de saturation tension ou vitesse trop basse
  //while(mesure <= 50 && vitesse > 50){
  //while(mesure <= 50 ){
  OFFSET=2.5;
  while(1==1){
    //Falcutatif retour ingenieur
      Aread=mesureB(255,A0);
      mesure =(Aread-OFFSET)*3.2258;//0.66*1000*5/1023
      mesuretab(0,mesure,Aread);
    }
    myMotor->run(RELEASE);
   
   //Demontage
   mesuretab(2,0,0);  
  }



//fonction pour faire blink de la RGB
void blinkRGB(){
  int i;
  for (i =0 ; i <= 3;i++)
    { 
      displayColor(230,230,0);
      delay(1000);
      displayColor(0,0,0);
      delay(500);
    }
  }



//Mesure courant vitesse
void mesuretab(int mode,float mesure,float Aread){

  //MODE MESURE
  if (mode==0)
  {  
      Serial.print("\r");
      Serial.print("\r");
      Serial.print("Courant(mA):");
      Serial.print(mesure,4);
      Serial.print("  Vitesse(tops):");
      Serial.print(vitesse); 
      Serial.print("  vitesse(RPM):");
      float Rpm =(150/PPR)*vitesse;
      Serial.print(Rpm);
      Serial.print(" Real Amp(mA):");
      Serial.print(Aread,4);
      Serial.print("  OFFSET:");
      Serial.print(OFFSET);   
      }

  //MODE MONTAGE
  else if (mode == 1)
  {
      attachInterrupt(interupt,tops,RISING);
      Timer1.initialize(Te);
      Timer1.attachInterrupt( timerIsr );
    
    }

   //MODE DEMONTAGE
   else if (mode == 2)
   {
      detachInterrupt(interupt);
      Timer1.detachInterrupt();
      Timer1.disablePwm(9);
      Timer1.disablePwm(10);
    }
  
  }
