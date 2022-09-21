/*
Based on the above program, write your own, which will make each successive jump to a new position after a longer time (200ms, 250ms, etc.).
*/

#include <Servo.h> 
#define servo_pin 9

Servo servo;  //Object that refer to the servo
int position = 0; //postion of servo in range of 0 degree to 180 degree
int change = 5; 

void setup() 
{ 
  servo.attach(servo_pin);  
} 
 
void loop() 
{  
  if (position < 180) { 
    servo.write(position); //move
  } else { 
    position = 0;
  }    
  position += change; 
  delay(500);                 
}