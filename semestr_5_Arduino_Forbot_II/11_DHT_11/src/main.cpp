
/*
At the very end, it is worth mentioning the last function sewn into our library, which converts temperature to the Fahrenheit scale: dht.toFahrenheit(). 
In practice, in our case, its call would look as follows:
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
  // Collect temp value.
  int temperatura = dht.getTemperature();

  if (dht.getStatusString() == "OK")
  {
    Serial.print(wilgotnosc);
    Serial.print("%RH | ");
    Serial.print(dht.toFahrenheit(temperatura));
    Serial.println("F");

  }

  delay(dht.getMinimumSamplingPeriod());
}