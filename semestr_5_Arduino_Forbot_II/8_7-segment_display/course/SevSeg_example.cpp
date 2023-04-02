/*
Ready-made library for 7-seg displays.
Of course, for the "sensible" use of 7-segment displays you will find many libraries that will do more difficult things in the background. 
I didn't want to start with a ready-made one right away, because some readers might not understand the principle of such a display - hence such hand-carving of the code "around"...
It's time to run our 7-segment displays using a ready-made library, which will make it easier to use them in other projects. 
On the Internet you can find at least a few such ready-made functions, during the further description we will use the SevSeg Library.
*/



#include <Arduino.h>
#include "SevSeg.h"
#define SEG_D 4
#define SEG_B 5
#define SEG_G 6
#define SEG_A 7
#define SEG_F 8
#define SEG_C 9
#define SEG_E 10
#define DISP_1 11
#define DISP_2 12

SevSeg sevseg; //Instantiate a seven segment controller object
 
void setup() {
  byte numDigits = 2;   //number of displays
  byte digitPins[] = {11, 12}; //pins that enable those displays
  byte segmentPins[] = {7, 5, 9, 4, 10, 8, 6}; //pins of segments A-G
  bool resistorsOnSegments = true; // Use 'true' if on digit pins
  byte hardwareConfig = N_TRANSISTORS; // See README.md for options
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments); //init
}
 
void loop() {
  sevseg.setChars("37");
  sevseg.refreshDisplay();
}