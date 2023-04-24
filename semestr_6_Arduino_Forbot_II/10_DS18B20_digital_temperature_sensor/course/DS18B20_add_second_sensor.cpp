/*
The big advantage of digital sensors is that they communicate through more elaborate mechanisms, which bring many advantages. 
For example, in this case, multiple sensors can be connected to the same pin.

*/


#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(A0); // Connection to A0
DallasTemperature sensors(&oneWire); //Transmitting information to the library

void setup() {
  Serial.begin(9600);
  sensors.begin(); //Sensors intit
}

void loop() {
  sensors.requestTemperatures(); // Sensor temperature retrieval
  Serial.print("First sensor: ");
  Serial.println(sensors.getTempCByIndex(0));  
  Serial.print("Second sensor: ");
  Serial.println(sensors.getTempCByIndex(1));  
  delay(500);
}