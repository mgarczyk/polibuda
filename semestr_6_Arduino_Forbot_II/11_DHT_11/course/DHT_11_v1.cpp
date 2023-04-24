/*
Now in the main loop you can already go to the readings. Here two functions will come in handy.
The first to get the humidity information in %RH: dht.getHumidity() and the second to read the temperature in °C: dht.getTemperature().
*/

#include "DHT.h"
#define DHT11_PIN 2
DHT dht;

void setup()
{
  Serial.begin(9600);
  dht.setup(DHT11_PIN);
}

void loop()
{
  // Collect humidity value.
  int wilgotnosc = dht.getHumidity();
  Serial.print(wilgotnosc);
  Serial.print("%RH | ");

  // Collect temp value.
  int temperatura = dht.getTemperature();
  Serial.print(temperatura);
  Serial.println("*C");

  delay(1000);
}