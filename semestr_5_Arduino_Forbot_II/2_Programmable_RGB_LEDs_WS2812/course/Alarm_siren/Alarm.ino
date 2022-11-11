/*
Alarm beacon

The first version of the siren will be very simple. 
We want all the LEDs to light alternately red or blue. Of course, 
we will not manually trigger each of them.To do this, we will use two for loops. 
The task of the first one will be to set all the LEDs to red. 
In order to make our traffic light flash quickly, we need to add support for the second color and a small delay. 
The program implementing this example looks as follows.
*/

#include <Adafruit_NeoPixel.h> //Dołączenie biblioteki
 

Adafruit_NeoPixel LED_line = Adafruit_NeoPixel(8, A0, NEO_GRB + NEO_KHZ800);
 
void setup() {
  LED_line.begin(); 
  LED_line.show(); 
}
 
void loop() {
  int i = 0;
  for (i = 0; i < 8; i++) {  
    LED_line.setPixelColor(i, LED_line.Color(255, 0, 0)); 
  }
  
  LED_line.show();
  delay(250);
 
   for (i = 0; i < 8; i++) {  
    LED_line.setPixelColor(i, LED_line.Color(0, 0, 255)); 
  }
  
  LED_line.show(); 
  delay(250);  
}