
const int mesure=200;

void setup() {
  Serial.begin(9600);

}

void loop() {
  double sensorM=0;
  double sensorm=712;
  long unsigned int timer = micros();
  while (micros()-timer<5000000){
    float sensorValue=mesureB(50);
    if (sensorValue>sensorM){
      sensorM=sensorValue;
      }
     if (sensorValue<sensorm){
      sensorm=sensorValue;
      }
     }
     Serial.println(sensorM-sensorm);
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
