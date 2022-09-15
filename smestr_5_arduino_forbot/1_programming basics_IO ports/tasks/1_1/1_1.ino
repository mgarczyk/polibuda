/*
Check at what lowest value of delay you will be able to notice the flashing of the LED. 
*/
void setup() {
  pinMode(8, OUTPUT);
  
}
 
void loop() {
    digitalWrite(8, LOW); // change state of output to low
    delay(10); // wait 1 second
    digitalWrite(8, HIGH); // change state to high
    delay(10); // wait 200 ms
    
}
