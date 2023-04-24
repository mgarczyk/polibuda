/*
Extend the program so that it can handle 2 temperature sensors and display their results side by side.
The third value displayed (on a new line) should be the difference between the 2 readings.
*/

#include <Arduino.h>
#define LM35_1 A0
#define LM35_2 A1


void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // Converting ADC reading to temperature as described in the course
    float temp_LM35_1 = ((analogRead(LM35_1) * 5.0) / 1024.0) * 100;
    float temp_LM35_2 = ((analogRead(LM35_2) * 5.0) / 1024.0) * 100;
    float temp_diff = temp_LM35_2 - temp_LM35_1;
    // Sending via UART the current temperature
    Serial.println("Actual temperature sensors 1 and 2: ");
    Serial.println(temp_LM35_1, temp_LM35_2);
    Serial.println("*C");
    Serial.println("Actual temperature diffrence: ");
    Serial.println(temp_diff);
    Serial.println("*C");
    delay(1000);
}