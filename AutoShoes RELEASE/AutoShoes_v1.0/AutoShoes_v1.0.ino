//-- MOTEUR A --
int ENA = 5; //Connecté à Arduino pin 5(sortie pwm)
int IN1 = 2; //Connecté à Arduino pin 2
int IN2 = 3; //Connecté à Arduino pin 3

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
  
  //Configurer les broches comme sortie
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner (désactivation moteur)
  
  // Direction du Moteur A
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);
  analogWrite(ENA,0);

  //Bouton
  pinMode(BoutonOFFSET,INPUT);
  pinMode(BoutonLACE,INPUT);
  pinMode(BoutonUN,INPUT);
  pinMode(BoutonPULSE,INPUT);
  
  //RGB
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  displayColor(0, 0, 0);

  //Initialise
  intitialise();
}


// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);
  analogWrite(ENA,0);
  displayColor(15,32,32);

  //Fonctions ingenieurs
   etatBouton  = digitalRead(BoutonOFFSET);
   Lace        = digitalRead(BoutonLACE);
   pulse       = digitalRead(BoutonPULSE);
   un          = digitalRead(BoutonUN);
  //Serial.println(etatBouton);
  while (etatBouton){
    intitialise();
    etatBouton  = digitalRead(BoutonOFFSET);
    }
  float mesure =(mesureB(255,A0)-OFFSET)*0.66*1000*5/1023;
  Serial.println(mesure,4);
  while (Lace){
    displayColor(128,0,0);
    lacage(255,255,A0);
    Lace        = digitalRead(BoutonLACE);
    Serial.println(Lace);
    }
  while (pulse){
    displayColor(0,128,0);
    analogWrite(ENA,255);
    delay(100);
    pulse       = digitalRead(BoutonPULSE);
    }
  while (un){
    displayColor(0,128,0);
    digitalWrite(IN1,HIGH); 
    digitalWrite(IN2,LOW);
    analogWrite(ENA,255);
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



unsigned int mesureB(int x,char broche){
  
  unsigned int voltagemoy = 0;
  
  for (int i=1;i<=x;i++){
    float sensorValue = analogRead(broche);
    
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    unsigned int voltage = sensorValue;
    
    voltagemoy+=voltage;
  }
  return voltagemoy/x;
}


void intitialise(){
  OFFSET=mesureB(255,A0);
  }


void lacage(int vit,int moy,char broche){
  intitialise();
  analogWrite(ENA,vit);
  delay(400);
  while((mesureB(moy,broche)-OFFSET)*0.66*1000 <= 50){
      float mesure =(mesureB(255,A0)-OFFSET)*0.66*1000*5/1023;
      Serial.println(mesure,4);
    }
  analogWrite(ENA,0);
  }
