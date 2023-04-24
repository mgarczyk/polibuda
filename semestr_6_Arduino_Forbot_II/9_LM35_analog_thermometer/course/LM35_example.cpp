/*
The task of the program will be to read the voltage on pin A0 and convert it accordingly. \
As it is written in the documentation 1°C is 10 mV. Therefore, first the ADC value must be converted to voltage.
As a reminder, we do this by multiplying the reading times 5, and then divide this result by 1024 (the operating range of the ADC is 0...1023).
1024 => 5V
1 => x
1024x = 1*5
x = (1*5V)/1024 = ~0,0049V
To get degrees Celcius at the end we multiply the resulting value times 100 (ADC read is in volts, 10mV is 1 degree, then 100 times 10mv is equal to 1V)).
*/
#include <Arduino.h>
#define LM35 A0
void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // Converting ADC reading to temperature as described in the course
    float temp = ((analogRead(LM35) * 5.0) / 1024.0) * 100;
    // Sending via UART the current temperature
    Serial.print("Actual temperature: ");
    Serial.print(temp);
    Serial.println("*C");
    delay(1000);
}