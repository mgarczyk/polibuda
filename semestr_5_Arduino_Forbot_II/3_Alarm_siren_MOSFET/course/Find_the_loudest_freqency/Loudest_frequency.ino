/*
Buzzer without generator is not a polar element (we can connect it freely). However, for the sake of principle and your own peace of mind, I recommend sticking to accepted standards
and connecting the black wire to ground.
/*
Each buzzer at a certain characteristic frequency begins to make loud sounds. 
Specifically, we are talking about the resonant frequency. 
You can check it in the documentation, but I now encourage you to take an experimental approach.
*/

void setup() {
  pinMode(A5, OUTPUT); 
}
 
/*
Why does the for loop execute from a frequency of 31Hz to 65535Hz? This is the limitation of the tone() function, 
which on the Arduino UNO can generate signals with frequencies mixed in such a range.
*/

void loop() {
  for(int freq = 31; freq<=65535; freq++){
    tone(A5, freq);     
  }
}