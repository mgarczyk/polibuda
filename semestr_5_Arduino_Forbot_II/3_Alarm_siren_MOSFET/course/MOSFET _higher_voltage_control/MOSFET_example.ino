/*
By this I mean cases in which we need to control devices that require, for example, 9V or 12V. 
There are components that will not be able to work with the voltage provided by the Arduino, which is 5V. 
Here, MOSFET-type transistors will be helpful.
Of course, the other advantage of control by those "small intermediaries" is their much higher current strength. 
From a single Arduino pin can safely draw about 20mA. After using MOSFETs it will be whole amps!

IRL540N MOSFET + Arduino + buzzer:
Control signal through a 10k resistor to the gate (left lead of the MOSFET),
Arduino ground to the source (right lead). 
From the drain (middle lead) we run a wire, which we plug into the board (so that it does not connect to any other signal),
Additional wire from the VIN from the Arduino we plug into the board.
Put a buzzer between the wires and a resistor in parallel with it. 

Now everything should work properly. We can enjoy the buzzer powered by a higher voltage! It is worth checking how the circuit will behave for other frequencies. 
Did the higher voltage change the response to different frequencies? 
Let this remain an exercise for the willing.
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