/*
Connect a potentiometer to the circuit as a voltage divider. 
Then use an ADC to measure the voltage set on the potentiometer. 
The higher it is, the closer the servo should be to its extreme right position.
*/

#include <Servo.h>

#define servo_pin 9
#define potentometer A0
Servo servo;      // Object that refer to the servo
int position = 0; // postion of servo in range of 0 degree to 180 degree

void setup()
{
    Serial.begin(9600);
    servo.attach(servo_pin);
    servo.write(0);
}

void loop()
{
    // KEY LINE - We map the value of voltage from potentometer converted by ADC to unit that is actually unterstand by servo, i.g. degrees.
    position = map(analogRead(potentometer), 0, 1023, 0, 180);
    Serial.println(String("Servo postion: ") + position);
    servo.write(position);
}
