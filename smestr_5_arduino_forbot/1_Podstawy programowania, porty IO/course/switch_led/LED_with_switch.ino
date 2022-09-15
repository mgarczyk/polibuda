/*
Very often we want the programmed circuit to be able to respond to external signals. 
This time we will connect a button to the Arduino in addition to the diode.
*/

void setup() {
  pinMode(8, OUTPUT);
  pinMode(7, INPUT_PULLUP); // pin 7 as switch input
  digitalWrite(8, LOW);     // switch off the LED
}
 
void loop() {
   if (digitalRead(7) == LOW){ // if the switch is pressed then turn on the LED
    digitalWrite(8, HIGH); 
   }else{
    digitalWrite(8, LOW); 
   }
}