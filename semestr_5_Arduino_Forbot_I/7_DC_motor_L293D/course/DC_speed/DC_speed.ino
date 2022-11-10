/*
For further testing, you will need the knowledge from the article PWM and Arduino. 
As you may have guessed, all you need to do is apply a PWM signal to the ENABLE1 pin (of the L293D chip) to control the speed of the motor!
There is nothing to elaborate on. It's time to write a simple program that will alternately spin the motors slower or faster. 
Remember that the glowing of the diode is visible only above a certain PWM signal filling threshold, and the same will happen with the motors. 
Each will spin from a slightly different value. 
*/

#define SPEED_CONTROL 6
#define TURN_RIGHT 7
#define TURN_LEFT 8


void setup() { 
  pinMode(SPEED_CONTROL, OUTPUT);
  digitalWrite(SPEED_CONTROL, HIGH); 
  pinMode(TURN_LEFT, OUTPUT);
  pinMode(TURN_RIGHT, OUTPUT);
} 
 
void loop()  {   
  analogWrite(SPEED_CONTROL, 100); //LOW RPM
  digitalWrite(TURN_RIGHT, LOW); 
  digitalWrite(TURN_LEFT, HIGH);
  delay(3000); 
  
  analogWrite(SPEED_CONTROL, 255); //HIGH RPM
  digitalWrite(TURN_RIGHT, LOW); 
  digitalWrite(TURN_LEFT, HIGH);
  delay(3000);                 
}