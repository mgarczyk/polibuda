/*
Our goal is to write a few lines with which the diode will slowly flash. 
In other words, we will be in a loop to change the fill of the PWM signal with which it will be controlled.
*/

#define LED 3
int change = 5;
int duty_cycle = 0;

void setup() {
  pinMode(LED, OUTPUT);
}
 
void loop() {
  analogWrite(LED, duty_cycle);
  if (duty_cycle < 255){
    duty_cycle += change;
  }else{
    duty_cycle = 0;
  }
  delay(50);
}