/*
Of course, the Arduino IDE is changing over time. Recently, there was a very convenient option there that allows you to quickly draw diagrams from the information sent over the UART.
To draw a graph we need, preferably at regular intervals, to send numbers to the computer in a new line. 
To begin with, let's create a circuit that will draw a graph of the voltage measured at the A0 input, to which we will connect a potentiometer in the role of a voltage divider.
*/

#define POTENTIOMETER A0

void setup() {
  Serial.begin(9600); 
}
 
void loop() {
  int potentiometer_value = analogRead(POTENTIOMETER); 
  Serial.print(">Potentiometer [Ω]:");     //In this way we create plot in Teleplot main screen
  Serial.println(potentiometer_value); //That value will be plotted via Teleplot
  delay(200); 
}