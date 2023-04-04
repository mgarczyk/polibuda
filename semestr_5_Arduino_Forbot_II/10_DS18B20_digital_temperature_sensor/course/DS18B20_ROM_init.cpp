/*
Connecting sensors to a single data line is possible because the manufacturer has assigned a unique address to each sensor manufactured.
For more elaborate projects, it is worth using just these addresses.
Then we can uniquely identify our sensors.
Of course, the address cannot be found on the housing - it must be read out by software.

Here we can use the demo program File → Examples → OneWire → DS18x20
//ROM = 28 14 2F 78 E 0 0 4E
*/

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(A0);                 // Connection to A0
DallasTemperature sensors(&oneWire); // Transmitting information to the library
DeviceAddress thermometerOutside = {0x28, 0x14, 0x2F, 0x78, 0x0E, 0x0, 0x0, 0x4E}; //init sensor by ROM address

void setup()
{
  Serial.begin(9600);
  sensors.begin(); 
}
void loop()
{
  sensors.requestTemperatures(); // Sensor temperature retrieval
  Serial.print("Actual: ");
  Serial.println(sensors.getTempC(thermometerOutside));
  delay(500);
}