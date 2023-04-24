/*
The first parameter is the diode number (counting from zero). 
The second parameter is the color. 
As it happens in the world of computers, we have to express it in the form of a large number.
For us, as humans, it will be much easier if we can describe the color with three smaller numbers. 
Then each of them will be able to account for the brightness of one component, that is, 
we will separately give the brightness for red, green and blue. 
Here another construction comes to our aid: ruler.Color(0, 0, 0).

*/

#include <Adafruit_NeoPixel.h> 
 
Adafruit_NeoPixel LED_line = Adafruit_NeoPixel(8, A0, NEO_GRB + NEO_KHZ800);
 
void setup() {
  LED_line.begin(); 
  LED_line.show(); 
  LED_line.setPixelColor(0, LED_line.Color(0, 255, 0)); 
  LED_line.show(); 
}
 
void loop() {
 
}