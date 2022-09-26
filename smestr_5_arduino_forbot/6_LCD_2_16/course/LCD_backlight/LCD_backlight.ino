/*
Finally, one more curiosity. 
I mentioned earlier that we do not have the ability to control the backlight. 
Are you sure? After all, it is just a light emitting diode. 
What if we were to connect it to the microcontroller? It would be enough to rearrange one wire.
The experience could be detrimental to the Arduino. 
Check how much current your backlight draws. You can find information about current measurements in the electronics course. 
It's a good idea to connect the backlight through a resistor or transistor for safety!
*/

#include <LiquidCrystal.h> 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 
#define PWM 11

void setup() {
  lcd.begin(16, 2); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello World!");
  lcd.setCursor(0,1);
  lcd.print("Marcel Forbot"); 
}

int brightness = 0;    
int change = 5;   
 
void loop()
{
  analogWrite(PWM, brightness); //Generate a PWM signal with a specified fill.  
  brightness = brightness + change; //In the next cycle, change the brightness by the value of the change variable
 
  if (brightness == 0 || brightness == 255) { //If filling is 0% or 100%
    change = 0-change; //To change the change sign (start changing in the opposite direction)
  }     
   
  delay(30);   
}