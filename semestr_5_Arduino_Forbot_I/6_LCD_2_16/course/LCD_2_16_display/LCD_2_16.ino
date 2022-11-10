/*
As in the case of servos in Arduino, we will find a separate library to facilitate working with text displays. 
This time its name is LiquidCrystal. 
*/

#include <LiquidCrystal.h> // LCD library
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Arduino pins that we are using to control display  (2 (RS), 3 (Enable), 4 (D4), 5 (D5), 5 (D6) i 7 (D7)).
 
void setup() {
  lcd.begin(16, 2); //Declare type of display in our case it's 2x16 (2 rows, 16 characters)
  //The function lcd.setCursor(position, line) sets the cursor at the specified position. 
  //For example, the notation (0,0) means the beginning of the text from the first character, the first line. 
  lcd.setCursor(0, 0); 
  lcd.print("Hello World!"); 
  lcd.setCursor(0, 1); 
  lcd.print("On Forbot");
  lcd.blink(); //blinking cursor
}
 
void loop() {
}