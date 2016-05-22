#include <HC_SR04_lib.h>

const int Triger_Pin = 8;
const int Echo_Pin = 9;
unsigned long Lectura = 0;

HC_SR04Dev Sensor_A(Triger_Pin,Echo_Pin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  if (Sensor_A.Sync() == HC_SR04_READ_OK)
  {
    Lectura = Sensor_A.Read();
    Serial.print("Lectura OK: ");
    Serial.print(Lectura);
    Serial.println(" Centimeters");
  }
  else
  {
    //Lectura = Sensor_A.Read();
    Serial.println("Error !!");
    //Serial.println(Lectura);
  }
}
