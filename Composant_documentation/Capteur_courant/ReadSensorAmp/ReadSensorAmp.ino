const float OFFSET =2.500650408 +0.025780952;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0/1023.0);
  float mesure = (voltage-OFFSET);
  Serial.println(mesure,4);
  delay(100);

}
