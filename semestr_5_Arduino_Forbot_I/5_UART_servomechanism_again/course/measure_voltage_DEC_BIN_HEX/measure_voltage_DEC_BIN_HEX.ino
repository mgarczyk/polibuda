/*
It's time to put the above information into practice. 
The purpose of our program is to measure the voltage value on pin A5 and then display it in the terminal. 
However, this time it is not enough to display the number in decimal. 
In addition - on one line - values in HEX, OCT and BIN are to be displayed. Of course, the whole thing is to be nicely formatted!
*/

#define POTENTOMETER A5
int potentometer_value = 0;

void setup() { 
  pinMode(A5, INPUT_PULLUP);
  Serial.begin(9600);
} 
 
void loop() { 
  potentometer_value = analogRead(POTENTOMETER);
  Serial.print("Read: ");
  Serial.print("\t[DEC] ");
  Serial.print(potentometer_value, DEC);
  Serial.print("\t[HEX] ");
  Serial.print(potentometer_value, HEX);
  Serial.print("\t[BIN] ");
  Serial.print(potentometer_value, BIN);
  Serial.print("\t[OCT] ");
  Serial.print(potentometer_value, OCT);
  Serial.print("\n");
  delay(5000);
}
