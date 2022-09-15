/*
Choose a free pin and connect the second LED to it. 
Write a program that will turn on both LEDs. 
Then write a program that will make both LEDs flash alternately.
*/

void setup() {
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
 
  
}
 
void loop() {
    digitalWrite(7, HIGH); // LED connected to port 7 lights up
    digitalWrite(8, LOW);  // LED connected to port 8 didin't lights up
    delay(1000); 
    digitalWrite(7, LOW);   // LED connected to port 7 didin't lights up
    digitalWrite(8, HIGH);  // LED connected to port 8 lights up
    delay(1000); 
    
}