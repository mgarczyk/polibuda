/*
We will get an even better effect if we add a button to the program. By default, if we used delay() this function would block the ability to check inputs immediately.
You would have to hold the button until the program reached the check line. This would work infrequently, because delay() would freeze the program for several seconds.
*/

#include <Arduino.h>
#define LED1 3
#define LED2 4
#define SWITCH 5
unsigned long actual_time = 0;
unsigned long remember_time_LED_1 = 0;
unsigned long remember_time_LED_2 = 0;
unsigned long blink_time_LED_1 = 1000;
unsigned long blink_time_LED_2 = 200;
int LED_1_state = LOW;
int LED_2_state = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);
}

void switch_enable()
{
  if (digitalRead(SWITCH) == LOW)
  {
    blink_time_LED_1 = 100;
  }
  else
  {
    blink_time_LED_1 = 1000;
  }
}

void loop()
{
  actual_time = millis();
  switch_enable();
  if (actual_time - remember_time_LED_1 >= blink_time_LED_1)
  {
    remember_time_LED_1 = actual_time;
    LED_1_state = !LED_1_state;
    digitalWrite(LED1, LED_1_state);
  }
  else if (actual_time - remember_time_LED_2 >= blink_time_LED_2)
  {
    remember_time_LED_2 = actual_time;
    LED_2_state = !LED_2_state;
    digitalWrite(LED2, LED_2_state);
  }
}