void setup() {
  pinMode(8, OUTPUT);
  
}
 
void loop() {
    digitalWrite(8, LOW); // change state of output to low
    delay(1000); // wait 1 second
    digitalWrite(8, HIGH); // change state to high
    delay(1000); // wait 200 ms
    
}