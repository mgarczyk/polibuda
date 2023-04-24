/*
As promised, we now return to the topic of measuring the minimum and maximum temperature.
This time we will solve the "problem" of pre-assigning the values of the variables differently.
At the beginning we also declare two new variables.
We don't have to worry about their value, because a little below in the setup() function we will assign them a one-time value for the first reading performed.

*/

#include <OneWire.h>
#include <DallasTemperature.h>

float tempMAX = 0;
float tempMIN = 0;

OneWire oneWire(A0);                 // Connection to A0
DallasTemperature sensors(&oneWire); // Transmitting information to the library

void setup()
{
  Serial.begin(9600);
  sensors.begin(); // Sensors init
  sensors.requestTemperatures();
  tempMAX = sensors.getTempCByIndex(0);
  Serial.print("First maximum value: ");
  Serial.print(tempMAX);
  Serial.println("*C");
  tempMIN = sensors.getTempCByIndex(0);
  Serial.print("First minimal value: ");
  Serial.print(tempMIN);
  Serial.println("*C");
}

void loop()
{
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  if (temp > tempMAX)
  {
    tempMAX = temp;
    Serial.print("New maximum value: ");
    Serial.print(tempMAX);
    Serial.println("*C");
  }

  if (temp < tempMIN)
  {
    tempMIN = temp;
    Serial.print("New minimal value: ");
    Serial.print(tempMIN);
    Serial.println("*C");
  }

  delay(1000);
}