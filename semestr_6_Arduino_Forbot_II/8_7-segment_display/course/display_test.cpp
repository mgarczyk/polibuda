#include <Arduino.h>
/*
Now you can move on to the program, which is trivial, we simply control 7 LEDs....
The following example should run each of the segments (from A to F) in turn.
*/

#define SEG_D 4
#define SEG_B 5
#define SEG_G 6
#define SEG_A 7
#define SEG_F 8
#define SEG_C 9
#define SEG_E 10

void setup()
{
    // Configure pins as outputs
    pinMode(SEG_A, OUTPUT);
    pinMode(SEG_B, OUTPUT);
    pinMode(SEG_C, OUTPUT);
    pinMode(SEG_D, OUTPUT);
    pinMode(SEG_E, OUTPUT);
    pinMode(SEG_F, OUTPUT);
    pinMode(SEG_G, OUTPUT);

    // Segments test
    digitalWrite(SEG_A, HIGH);
    delay(800);
    digitalWrite(SEG_B, HIGH);
    delay(800);
    digitalWrite(SEG_C, HIGH);
    delay(800);
    digitalWrite(SEG_D, HIGH);
    delay(800);
    digitalWrite(SEG_E, HIGH);
    delay(800);
    digitalWrite(SEG_F, HIGH);
    delay(800);
    digitalWrite(SEG_G, HIGH);
}

void loop()
{
}