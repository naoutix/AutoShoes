/*
 Mesure on Arduino Nano ATmega328P(Old Bootloader)
 
 */
//-- MOTEUR A --
int ENA = 5; //Connecté à Arduino pin 5(sortie pwm)
int IN1 = 2; //Connecté à Arduino pin 2
int IN2 = 3; //Connecté à Arduino pin 3


//--Mesure --
unsigned long nbpoint = 1000;
unsigned long deltaT = 10000;//(ms)
unsigned long Te = (int)deltaT/nbpoint;

void setup() {
  Serial.begin(9600);
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);

  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);
  analogWrite(ENA,0);

}


void loop() {
  String c ="";
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);
  analogWrite(ENA,0);
  if (Serial.available()) {  
    while (Serial.available()>0){
    c= Serial.readString();
    }
  }
  if (c[0]=='a')
  {
    unsigned long Tab[2][nbpoint];
    unsigned long t0=millis();
    unsigned long timer = 0;
    int i;
    for(i=0;i < nbpoint;i++)
    {
      timer = millis();
      Tab[0][i]=timer-t0;
      Tab[1][i]=mesureB(255,A0);
      delay(Te); 
      i++;
    }
  }
}


float mesureB(int x,char broche){
  
  unsigned int Sensormoy = 0;
  
  for (int i=1;i<=x;i++){
    unsigned int sensorValue = analogRead(broche); 
    Sensormoy+=sensorValue;
  }
  return Sensormoy/x;
}
