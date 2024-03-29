/*
This function does not take any argument. It simply returns the number of milliseconds that have elapsed since the Arduino was started. Each second, is 1000 ms, so the returned value will grow very quickly. 
It is necessary to ensure that the variable to which we write the information is sufficiently capacious. To do this, we use the unsigned long data type

The variables storing the time are of unsigned long type, so to avoid problems with comparing values, the number of milliseconds was written with the addition of UL (1000UL).
This ensures that the compiler will treat 1000 as a value of unsigned long type.

*/

#include <Arduino.h>
unsigned long actual_time = 0;
unsigned long remember_time = 0;
unsigned long time_diff = 0;
 
void setup(){
  Serial.begin(9600);
}
 
void loop(){
  actual_time = millis();
  time_diff = actual_time - remember_time;
  if (time_diff >= 1000UL) {
    remember_time = actual_time;
    Serial.println(actual_time);
  }
}