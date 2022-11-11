/*
Alarm siren - version two
This time the siren is to consist of 4 red and 4 blue LEDs. Moreover, they are not supposed to turn on at once, but one, after the other. 
To make this happen inside a loop, call show() and insert a delay.
Running such a loop will cause each diode to turn on successively in blue. 
Now you need to extend the program in such a way as to change the color - of course, 
you only need one condition for this. In it's simplest form, it will look as follows.
*/
#include <Adafruit_NeoPixel.h> 
 

Adafruit_NeoPixel LED_line = Adafruit_NeoPixel(8, A0, NEO_GRB + NEO_KHZ800);
 
void setup() {
  LED_line.begin(); //Inicjalizacja
  LED_line.show(); 
}
 
void loop() {
 int i = 0;
  for (i = 0; i < 8; i++) {
    if (i < 4) {
      LED_line.setPixelColor(i, LED_line.Color(255, 0, 0)); 
    } else {
      LED_line.setPixelColor(i, LED_line.Color(0, 0, 255));      
    }
    
    LED_line.show(); 
    delay(100);
  }
  LED_line.clear();
}