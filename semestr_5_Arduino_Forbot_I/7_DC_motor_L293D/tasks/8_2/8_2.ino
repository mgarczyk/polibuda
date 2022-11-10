
/*
Write a program that uses 2 for loops to smoothly accelerate and decelerate an engine.
*/

#define SPEED_CONTROL 6
#define TURN_RIGHT 7
#define TURN_LEFT 8


void setup() { 
  pinMode(SPEED_CONTROL, OUTPUT); 
  pinMode(TURN_RIGHT, OUTPUT); 
  pinMode(TURN_LEFT, OUTPUT);
} 
 
void forward(){
  digitalWrite(TURN_RIGHT, HIGH); 
  digitalWrite(TURN_LEFT, LOW);
}

void bacward(){
   digitalWrite(TURN_RIGHT, LOW); 
   digitalWrite(TURN_LEFT, HIGH);
}

void acceleration(){
     for (int i = 0; i <= 255; i++) {
      analogWrite(SPEED_CONTROL, i); //Calm engine acceleration
      delay(25);
  }
    
}

void deacceleration(){
    for (int i = 255; i >= 0; i--) {
      analogWrite(SPEED_CONTROL, i); //Calm engine deacceleration
      delay(25);
  }
}

void loop()  { 
    forward();
    acceleration();
    deacceleration();
    bacward();
    acceleration();
    deacceleration();
}