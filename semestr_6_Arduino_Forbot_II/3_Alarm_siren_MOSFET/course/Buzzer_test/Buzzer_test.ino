/*
Buzzer without generator is not a polar element (we can connect it freely). However, for the sake of principle and your own peace of mind, I recommend sticking to accepted standards
and connecting the black wire to ground.

Tone function:
With the help comes a very simple tone() function, which takes 3 arguments:
    1) The pin on which the signal is to be generated,
    2) The frequency of this signal,
    3) Duration - this parameter is not mandatory.

To generate sound with the tone() function, a counter (timer) built into the Arduino is used, 
which is also responsible for generating the PWM signal. 
Therefore, using this function also affects the ability to generate PWM on outputs 3 and 11.
*/


 
void setup() {
  pinMode(A5, OUTPUT); 
}
 
void loop() {
  tone(A5, 1000); 
  delay(100);  
  noTone(A5); 
  delay(1000);
}