/*
Let's use the knowledge we've gained to write a program that will flash the Arduino's built-in LED at random. 
Let's assume that the length of the light is to vary from about 100ms to 990ms. 
On the other hand, the time when the LED is off will be in the range of 50-490ms. 
Both values should change in intervals, every 10ms.
*/

#define LED 13

void setup() {
  pinMode(LED, OUTPUT);
  randomSeed(analogRead(0));
}
 
void loop() {
  int time_turn_on = random(10, 100); 
  int time_turn_off = random(5, 50); 
  
  time_turn_on = time_turn_on * 10; //Value from 100 - 990, increments of 10
  time_turn_off = time_turn_off * 10; //Value in the range of 50 - 490, increments of 10
 
  digitalWrite(LED, HIGH);
  delay(time_turn_on);
  digitalWrite(LED, LOW);
  delay(time_turn_off);
}