/*
Try to simplify the above program so that you do not need to use the conditional if statement. 
Hint: think about what effect the type of the fill variable has on the operation of the program.
*/


#define LED 3
int change = 5;
byte duty_cycle = 0;

void setup() {
  pinMode(LED, OUTPUT);
}
 
void loop() {
  analogWrite(LED, duty_cycle);
  duty_cycle += change;
  delay(50);
}