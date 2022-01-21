// Entrée analogique à utiliser (entre 0 et 5 pour un Arduino UNO)
int entreeAnalogique = 1;
 
// Valeur de la résistance de mesure R1 en ohms
#define R1 10000.0
 
void setup()
{
// Initialisation de la communication série
Serial.begin(115200);
}
 
 
void loop()
{
// Lecture de l'entrée analogique
float valeurLue = (float)analogRead(entreeAnalogique);
 
// calcul de la valeur de la résistance en ohms
float resistanceLue = R1*(1023-valeurLue /valeurLue);
 
// affichage de la valeur de la résistance dans la console série
Serial.print("\r");
Serial.print("Resistance : ");
Serial.print(resistanceLue);
Serial.println(" Ohms");
 
// attendre 1 seconde avant la prochaine mesure
//delay(1000);
}
