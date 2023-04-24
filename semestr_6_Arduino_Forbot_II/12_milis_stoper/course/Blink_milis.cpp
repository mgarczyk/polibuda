/*
This function does not take any argument. It simply returns the number of milliseconds that have elapsed since the Arduino was started. Each second, is 1000 ms, so the returned value will grow very quickly. 
It is necessary to ensure that the variable to which we write the information is sufficiently capacious. To do this, we use the unsigned long data type

The variables storing the time are of unsigned long type, so to avoid problems with comparing values, the number of milliseconds was written with the addition of UL (1000UL).
This ensures that the compiler will treat 1000 as a value of unsigned long type.

*/

#include <Arduino.h>
#define LED1 3
unsigned long actual_time = 0;
unsigned long remember_time_LED_1 = 0;
unsigned long time_diff = 0;
int LED_1_state = LOW;
 
void setup(){
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
}
 
void loop(){
  actual_time = millis();
  time_diff = actual_time - remember_time_LED_1;
  if (time_diff >= 1000UL) {
    remember_time_LED_1 = actual_time;
    Serial.println(actual_time);
    LED_1_state = !LED_1_state;
    digitalWrite(LED1, LED_1_state);
    
  }
}