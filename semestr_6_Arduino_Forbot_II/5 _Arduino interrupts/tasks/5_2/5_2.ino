/*
Write a program that uses interrupts to change the state of the LED to the opposite after each detection of motion by the PIR sensor. 
That is: first detection - lights up, second detection does not light up, etc.
*/

#define LED_R 10
#define LED_G 11
#define LED_B 12
#define PIR 2
 
volatile bool lights = true;
 
void setup() {
  pinMode(LED_R, OUTPUT); 
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(PIR, INPUT); //PIR as output
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
  attachInterrupt(digitalPinToInterrupt(PIR), motion, RISING); 
}
 
void loop() {
  if (lights == true){
    digitalWrite(LED_G, HIGH);
  }else{
    digitalWrite(LED_G, LOW);
  }
}
 
void motion() { 
  lights = !lights; //Another motion (negate previous state)
}