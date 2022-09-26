/*
Program is used to display the value of the voltage present on the photoresistor. 
The photoresistor with the resistor form a voltage divider, while this voltage is applied to the analog input A0.
*/

#include <LiquidCrystal.h> 
#define PHOTORESISTOR A0
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
double voltage_read = 0;
 
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voltage read: ");
  lcd.setCursor(0,1);
  lcd.print("0.00V"); 
   
}
 
void loop() {

    voltage_read = 5 * analogRead(PHOTORESISTOR) / 1023.0;
    lcd.setCursor(0,1);
    lcd.print(voltage_read); 
    delay(250);

}
