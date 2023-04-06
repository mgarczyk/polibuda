/*
It is time to expand the above example to flash two LEDs independently. Only then will the advantage of this solution become apparent.
This time we want one diode to change its state more often than the other.
*/

#include <Arduino.h>
#define LED1 3
#define LED2 4
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
}

void loop()
{
  actual_time = millis();

  if (actual_time - remember_time_LED_1 >= blink_time_LED_1)
  {
    remember_time_LED_1 = actual_time;
    LED_1_state = !LED_1_state;
    digitalWrite(LED1, LED_1_state);
  }
  else if(actual_time - remember_time_LED_2 >= blink_time_LED_2)
  {
    remember_time_LED_2 = actual_time;
    LED_2_state = !LED_2_state;
    digitalWrite(LED2, LED_2_state);
  }
}