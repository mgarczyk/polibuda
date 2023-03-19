
/*
Unfortunately, sometimes there may be some communication problems or other errors.
Then the screen will show the temperature and humidity of 0. The library we use still contains some interesting functions that will avoid such problems.
An example of an erroneous reading.
First of all, there is no need to enter "rigidly" the time after which the next reading can take place.
With the dht.getMinimumSamplingPeriod() function, it is possible to retrieve information about the time to wait while using a particular sensor.
Secondly, with the dht.getStatusString() function, we can check whether the reading of the measurements went without error.
If it did, the above function will return "OK" to us. If there is an error, we will get the appropriate information, e.g. "TIMEOUT".
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