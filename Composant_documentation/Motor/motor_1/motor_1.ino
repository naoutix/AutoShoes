//-- MOTEUR A --
int ENA=5; //Connecté à Arduino pin 5(sortie pwm)
int IN1=2; //Connecté à Arduino pin 2
int IN2=3; //Connecté à Arduino pin 3

//-- MOTEUR B --
int ENB=6; //Connecté à Arduino pin 6(Sortie pwm)
int IN3=4; //Connecté à Arduino pin 4
int IN4=7; //Connecté à Arduino pin 7


void setup() {
  // put your setup code here, to run once:
  pinMode(ENA,OUTPUT);//Configurer les broches comme sortie
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner (désactivation moteur)
// Direction du Moteur A
  digitalWrite(IN1,LOW); 
  digitalWrite(IN2,HIGH);
}

void loop() {
    // Moteur A - Plein régime
  analogWrite(ENA,255);

}
