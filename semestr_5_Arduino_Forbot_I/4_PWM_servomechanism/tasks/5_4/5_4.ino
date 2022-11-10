/*
Write a program that rotates the servo to a position sent to the Arduino via the UART.
The transmitted numbers must be in the range of 0-180, otherwise display an appropriate message.
*/

#include <Servo.h>

#define servo_pin 9
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
    if (Serial.available() > 0)
    {
        position = Serial.parseInt();
        if (position >= 0 && position < 180)
        {
            servo.write(position);
            delay(5000);
        }
        else
            Serial.println("Postion should be in range from 0 to 180. Try again.");
    }
    else
    {
        Serial.println("Send data via serial port.");
        delay(5000);
    }
}
