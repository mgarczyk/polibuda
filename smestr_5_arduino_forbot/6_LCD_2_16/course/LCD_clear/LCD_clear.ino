/*
Testing the LCD display of texts, you may notice that they sometimes overlap. 
The display does not automatically clear its contents (this has its advantages). 
However, if we want to remove all the text we use the lcd.clear() function. 
*/

#include <LiquidCrystal.h> 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 
 
void setup() {
  lcd.begin(16, 2); 
}
 
void loop() {
  lcd.setCursor(0, 0); 
  lcd.print("Hello World!"); 
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 1); 
  lcd.print("On Forbot");
  delay(1000);
  lcd.clear();
  
}

