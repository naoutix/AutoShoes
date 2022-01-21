/*
 AutoShoes program on arduino uno 
 
 */


//-- Timer --
#include <TimerOne.h>
#define Te 40000

//-- Capteur vitesse --
volatile long int count      = 0;
volatile double vitesse = 0;
volatile double acceleration=0;
#define interupt 0
//define PPR 341.2
#define PPR 375.56

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
#define pinC A2

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

//-- Bluetooth --
#include <SoftwareSerial.h>
#define Rx 13
#define Tx 4
#define baudRate 9600
SoftwareSerial BTserial(Rx,Tx);
long unsigned int temps=0;




void setup() 
{
//--Init Bluetooth --
 Serial.begin(115200);
  BTserial.begin(baudRate);
  Serial.print("Sketch:   ");   Serial.println(__FILE__);
  Serial.print("Uploaded: ");   Serial.println(__DATE__);
  Serial.print("BTserial started at "); Serial.println(baudRate);
  while (!Serial) {
    ;               //Need for native USB
  }
  Serial.println("Goodnight moon!"); //Test
  BTserial.println("Hello, world?");
  
  //Activation Carte Adafruit Motor Shield v2.3
  AFMS.begin();

  //init MOTOR
  myMotor->setSpeed(255);

  //Capteur vitesse
  attachInterrupt(interupt,tops,RISING);
  pinMode(2,INPUT_PULLUP);
  Timer1.initialize(Te);
  Timer1.attachInterrupt( timerIsr );

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
  String commande="";
  
  //Scan users
   Lace        = digitalRead(BoutonLACE);
   pulse       = digitalRead(BoutonPULSE);
   un          = digitalRead(BoutonUN);
  if (BTserial.available()){
    int len = 0;
    while (commande.substring(len-4,len-2)!= String("/c")){
      commande +=BTserial.readString();
      len = commande.length();     
    }
    commande.remove(len-4,len-2);
    Serial.print(commande);
  }
  if ((millis()-temps)>10000){
    BTserial.println("Type a/c for autolacing");
    BTserial.println("Type +/c for manuel lacing +");
    BTserial.println("Type -/c for manuel lacing -");
    temps = millis();
    }
   
  //--Action users--

  // MODE LACAGE
  while (Lace || commande[0] == 'a'){
    displayColor(128,0,0);  
    lacage(150,255,pinC);
    Lace        = digitalRead(BoutonLACE);
    blinkRGB(2,3);
    commande="";
    }
   double temps =0;
   
  // MODE REGLAGE MANUELLE +
  while (pulse || commande[0] == '+' ){
    displayColor(0,128,0); 
    myMotor->run(FORWARD);
    pulse       = digitalRead(BoutonPULSE);
    commande="";
    }
    
  // MODE REGLAGE MANUELLE -
  while (un || commande[0] == '-'){
    displayColor(0,128,0);
    myMotor->run(BACKWARD);
    un          = digitalRead(BoutonUN);
    commande="";
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
  
  long unsigned int Sensormoy = 0;
  
  for (int i=1;i<=x;i++){
    long unsigned int sensorValue = analogRead(broche); 
    Sensormoy+=sensorValue;
  }
  double moy = Sensormoy/x;
  return moy;
}


// -- OFFSET --
void intitialise()
{
  OFFSET=mesureB(50,pinC);
  }



// -- Fonctions Capteur de vitesse --
void tops ()
{
  count++;
  }
  
void timerIsr()
{
  acceleration=count-vitesse;
  vitesse = count;
  
  count=0;
}




// -- LACAGE --
void lacage(int vit,int moy,char broche)
{

  //Capteur Courant
  intitialise();
  
  //Demarage Moteur
  myMotor->setSpeed(vit);
  myMotor->run(FORWARD);
  BTserial.println("Autolacing...");
  
  double mesure=0;
  double acc=0;
  double mesureold=(mesureB(50,pinC)-OFFSET)*11.235;
  long unsigned int timer=micros();
  int peak=0;
  
  //Attente de saturation tension ou vitesse trop basse
  while((mesure <= 900 || peak==0) && (acc > -20))
  {
      //Mesure Courant
      mesure =(mesureB(50,pinC)-OFFSET)*11.235;//10^3*(5/1023)/0.435

      //Detection du pic
      double derivative=(mesureold-mesure)/(micros()-timer);
      if (derivative >400){
        peak=1;
        }
      
      timer =micros();
      mesureold=mesure;
      
      //mesure acceleration
      acc=acceleration*10.456;//2*pi/PPR/(Te)^2
    }
    myMotor->run(RELEASE);
    BTserial.println("Lacing DONE");  
  }



//fonction pour faire blink la RGB
void blinkRGB(int timer,int number){
  int i;
  for (i =0 ; i <= number;i++)
    { 
      displayColor(230,230,0);
      delay(timer);
      displayColor(0,0,0);
      delay(timer);
    }
  }



//Mesure courant vitesse
void mesuretab(float mesure){
      float Rpm =(1200/PPR)*vitesse;//60/0,05/PPR*tops
      String car ="I(mA):";
      car +=mesure;
      car +="  V(RPM):";
      car +=Rpm;
      BTserial.println(car);
      Serial.println(car);
  }
