/*
Our next circuit will be a switched traffic light circuit. 
Our main goal will be to write a program that will display 
the next correct sequence of lights when a button is pressed. 
Let's assume such a cycle of lights:

[...] -> Green -> Orange -> Red -> Red + Orange[...].

*/

void setup() {
  //Switch
  pinMode(7, INPUT_PULLUP); 
  //Pins
  pinMode(8, OUTPUT); //Green LED
  pinMode(9, OUTPUT); //Yellow LED
  pinMode(10, OUTPUT); //Red LED
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW); 

}
 
void loop()
{
    // Switch on traffic light by pressing the switch.
    if (digitalRead(7) == LOW){
        //loop 
        while(true) { // Traffic lights sequnce stops if you press the switch.
            // Green light
            digitalWrite(8, HIGH);
            digitalWrite(9, LOW);
            digitalWrite(10, LOW); 
            delay(3000);
            // Orange light
            digitalWrite(8, LOW);
            digitalWrite(9, HIGH);
            digitalWrite(10, LOW); 
            delay(3000);
            // Red light
            digitalWrite(8, LOW);
            digitalWrite(9, LOW);
            digitalWrite(10, HIGH);
            delay(3000);
            // Yellow + red
            digitalWrite(8, LOW);
            digitalWrite(9, HIGH);
            digitalWrite(10, HIGH);
            delay(3000);
         }
    }
}

