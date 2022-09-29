/*
All we need is to change the fill of the PWM signal smoothly, for example, every 25 ms.
The code is simple and presents as follows, as the counter variable i is responsible for the fill level of the PWM signa
*/


#define SPEED_CONTROL 6
#define TURN_RIGHT 7
#define TURN_LEFT 8


void setup() { 
  pinMode(SPEED_CONTROL, OUTPUT); 
  pinMode(TURN_RIGHT, OUTPUT); 
  pinMode(TURN_LEFT, OUTPUT);
  digitalWrite(TURN_RIGHT, LOW); 
  digitalWrite(TURN_LEFT, HIGH);
} 
 
void loop()  { 
  for (int i = 0; i <= 255; i++) {
      analogWrite(SPEED_CONTROL, i); //Smooth engine acceleration
      delay(25);
  }
}