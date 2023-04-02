#define LM35 A0
/*
But let's assume that measuring the temperature in the range of 0-100°C is enough for us.
Let's build a room thermometer with the function of storing the minimum and maximum temperature.
*/

#include <Arduino.h>
float tempMAX = 0;
float tempMIN = 150;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  float temp = ((analogRead(LM35) * 5.0) / 1024.0) * 100;

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