/*
Suppose we want the LED to light up for 10 seconds when the button is pressed. 
After that time it is to be off, of course only until the button is pressed again.
*/

void setup() {
  pinMode(8, OUTPUT);
  pinMode(7, INPUT_PULLUP); // pin 7 as switch input
  digitalWrite(8, LOW);     // switch off the LED
}
 
void loop() {
   if (digitalRead(7) == LOW){ // if the switch is pressed then turn on the LED
    digitalWrite(8, HIGH);
    delay(10000);   // add delay 10 s = 10000 ms
    digitalWrite(8, LOW);  //then switch off LED
}
}