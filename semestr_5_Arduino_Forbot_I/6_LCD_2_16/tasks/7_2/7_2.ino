/*
The display has a certain inertia. 
Check out what happens when we try to show new data too quickly (by deleting the contents of the screen with each loop).
*/

#include <LiquidCrystal.h> 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 
 
void setup() {
  lcd.begin(16, 2);
}
 
void loop() {
  lcd.setCursor(0, 0); 
  lcd.print("Hello World!"); 
  lcd.setCursor(0, 1); 
  lcd.print("On Forbot");
  lcd.clear();
}