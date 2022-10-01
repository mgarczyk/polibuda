/*
Find out what happens if, instead of the seed read from the analog input, a constant value is entered there. 
How will the pseudo-random number generator behave then?
*/

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(10));
}
 
void loop() {
  Serial.println(random(300));
  delay(1000);
}