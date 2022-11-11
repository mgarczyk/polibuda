/*
As the test with the for loop showed, such a buzzer also allows you to generate other sounds - it all depends on the chosen frequency. 
So we can create a simple alarm siren, we should choose loudest (resonance) frequency 3500-4000 Hz
*/
 
void setup() {
  pinMode(A5, OUTPUT); 
}
 
void loop() {
  tone(A5, 4000); 
  delay(150);  
  tone(A5, 3500); 
  delay(150);
}