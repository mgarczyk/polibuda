/*

It's time for the first program in which we will use the above, quite intricate, circuit. 
At first, we will deal with controlling the direction of the motor's rotation. 
Let's leave speed control for later. 
As mentioned, at the moment the following Arduino pins are responsible for one of the motors:

    6 (PWM) - speed control
    7, 8 - control of the direction of rotation

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
  digitalWrite(TURN_RIGHT, LOW); //Engine No. 1 - left rotation (backward)
  digitalWrite(TURN_LEFT, HIGH); 
  delay(3000);
  
  digitalWrite(TURN_RIGHT, HIGH); //Engine No. 1 - right rotation (forward)
  digitalWrite(TURN_LEFT, LOW); 
  delay(3000);                          
}