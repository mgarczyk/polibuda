/*
You have to communicate with the sensor via a 1-wire interface. 
However, this requires studying the datasheet note to know what information to send to the sensor and how to interpret what comes back to us.
Such experiments are encouraged for those who are not afraid of long programs.
In the course, however, we will focus on the library: Arduino-Temperature-Control-Library. 
For its correct operation, you still need the OneWire library. 
The process of installing new packages has already appeared in the course several times (at least in part 2), so I will not repeat it.

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
  Serial.print("Actual: ");
  Serial.println(sensors.getTempCByIndex(0));  
  delay(500);
}