/*
It's time for the first program that will move the servo arm. 
To do this, connect the circuit according to the assembly diagram below. 
First, it is necessary to connect the battery. Secondly, we need to use the LM7805 stabilizer.
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
  delay(100);                 
}