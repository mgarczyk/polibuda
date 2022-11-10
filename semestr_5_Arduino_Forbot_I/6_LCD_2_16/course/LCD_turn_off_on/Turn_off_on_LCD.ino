/*
Turning the display on and off.
The title says it all, we can turn on or off what is displayed on the screen. 
Note, however, that these functions only disable the display of text.
*/

#include <LiquidCrystal.h>     
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 

void setup()
{
    lcd.begin(16, 2); 
    lcd.setCursor(0, 0);
    lcd.print("Hello World!");
    lcd.setCursor(0, 1);
    lcd.print("On Forbot.");
}

void loop()
{
    lcd.noDisplay(); 
    delay(500);
    lcd.display();
    delay(500);
}