/*
It's time to discuss the very frequently used switch control statement. 
It is used in situations where, based on one variable, we perform several different actions depending on the value we have checked.
In order to understand the switch instruction, I will use an example, which will then be solved in two ways - traditionally and by a new method. 
So, let's assume that we want to write a program that reads the ADC value, and then sends it back to us in the form of a decimal, hexadecimal, octal or binary number. 
It all depends on our choice.

*/

int read_data = 0; 
#define POTENTOMETER A0
void setup() {
  Serial.begin(9600); 
}
 
void loop() {
  int read_potentometer = analogRead(POTENTOMETER); 
  
  if(Serial.available() > 0) {
    read_data = Serial.read(); 
  }
  
  switch (read_data) {
    case 'd':
      Serial.println(read_potentometer, DEC);
    break;
    case 'h':
      Serial.println(read_potentometer, HEX);
    break;
    case 'o':
      Serial.println(read_potentometer, OCT);
    break;
    case 'b':
      Serial.println(read_potentometer, BIN);
    break;
  }
 
  delay(1000); 
}