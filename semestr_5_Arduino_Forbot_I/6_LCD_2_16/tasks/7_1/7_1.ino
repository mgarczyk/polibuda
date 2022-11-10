/*
Write a program that will display on the screen in the first line your name, and in the second line the address forbot.pl
*/

#include <LiquidCrystal.h> 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 
 
void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); 
  lcd.print("Hello World!");
  lcd.setCursor(0, 1); 
  lcd.print("Marcel, Forbot");
  lcd.cursor();
}
 
void loop() {
  //Other way to blink cursor
  lcd.noCursor(); 
  delay(500); 
  lcd.cursor(); 
  delay(500); 
}
