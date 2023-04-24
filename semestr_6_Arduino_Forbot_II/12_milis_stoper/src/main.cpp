/*
When going down the stairs in the evening, we always turn on the light.
Similarly, when walking through a dark hallway. This is an ideal task to automate! This time, let's assume that the situation is as follows:
There is a staircase right next to the front door, on top of that we have small corridors at the bottom and top.
Let's assume that we want to activate the light when motion is detected.
When the PIR sensor notices someone near the stairs it will activate the light for 180 seconds or until the door is opened.
*/

#include <Arduino.h>
#define REED_SWITCH 3
#define LIGHT 4
#define PIR 5

unsigned long actual_time = 0;
unsigned long light_start = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LIGHT, OUTPUT);
  pinMode(REED_SWITCH, INPUT_PULLUP);
  pinMode(PIR, INPUT);
}

void loop()
{
  actual_time = millis();
  if (digitalRead(REED_SWITCH) == HIGH)
  {
    digitalWrite(LIGHT, LOW);
    light_start = 0; //reset after door was opened
  }
  else if (digitalRead(PIR) == HIGH)
  {
    light_start = actual_time;
    digitalWrite(LIGHT, HIGH);
  }

  if (actual_time - light_start >= 180000UL)
  {
    digitalWrite(LIGHT, LOW);
  }
}