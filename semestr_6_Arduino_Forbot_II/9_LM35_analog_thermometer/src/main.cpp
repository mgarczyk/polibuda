/*
The thermometer should send information about the current temperature to the computer every 2 seconds.
Two buttons should cause the currently stored extreme temperatures to be displayed.
*/

#include <Arduino.h>
#define LM35 A0
#define TEMP_MAX 2
#define TEMP_MIN 3
float tempMAX = 0;
float tempMIN = 150;

void send_max_temp()
{
  Serial.print("Maximum recorded temperature: ");
  Serial.print(tempMAX);
  Serial.println("*C");
}

void send_min_temp()
{
  Serial.print("Minimum recorded temperature: ");
  Serial.print(tempMIN);
  Serial.println("*C");
}

void setup()
{
  Serial.begin(9600);
  pinMode(TEMP_MAX, INPUT_PULLUP);
  pinMode(TEMP_MIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TEMP_MAX), send_max_temp, RISING);
  attachInterrupt(digitalPinToInterrupt(TEMP_MIN), send_min_temp, RISING);
}

void loop()
{
  float temp = ((analogRead(LM35) * 5.0) / 1024.0) * 100;

  if (temp > tempMAX)
  {
    tempMAX = temp;
  }

  if (temp < tempMIN)
  {
    tempMIN = temp;
  }

  Serial.print("Actual temperature: ");
  Serial.print(temp);
  Serial.println("*C");
  delay(2000);
}