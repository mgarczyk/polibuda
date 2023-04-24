/*
Now we can move on to the more interesting part, 
which is to take advantage of the fact that with such LEDs we can get any colors we want. 
All we need to do is to properly generate the PWM signal. 
I believe that everyone already understands the idea, 
so I will limit myself to just a simple example. 
This will help us move faster to programmable diodes.

To begin with the program in the simplest version. 
PWM is controlled by using the analogWrite(pin, fill) function, 
where the fill is a value from 0 to 255, 
which translates into its adjustment in the range of 0-100%.
*/

#include <Adafruit_NeoPixel.h>
//First one
#define red 3
#define green 5
#define blue 6
 
//Second one
#define red2 9
#define green2 10
#define blue2 11
 
  
void setup() {
  pinMode(red, OUTPUT); 
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(blue2, OUTPUT);
  randomSeed(analogRead(A5));
}

void smooth_transition(int random_change){
    for (int change = 0; change < 255; change++){
        analogWrite(red, random_change);  
        analogWrite(green, change);
        analogWrite(blue, 255 - change);   
        analogWrite(red2, change);  
        analogWrite(green2, 255 - change);
        analogWrite(blue2, random_change);
        delay(10);
    }
}

void smooth_transition_backwards(int random_change ){
    for (int change = 255; change > 0; change--){
        analogWrite(red, random_change);  
        analogWrite(green, change);
        analogWrite(blue, 255 - change);   
        analogWrite(red2, change);  
        analogWrite(green2, 255 - change);
        analogWrite(blue2, random_change);
        delay(10);
    }
}

void loop(){
    int random_change = random(255);
    smooth_transition(random_change);
    smooth_transition_backwards(random_change);
}