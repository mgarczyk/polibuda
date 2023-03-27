#include <Arduino.h>
/*

Add buttons to the circuit to build a counter:

    S1 - increase the digit shown on the display by 1,
    S2 - decrease the digit shown on the display by 1,
    S3 - resetting the circuit. - basiclly arduino reset button

*/

#define INCR 2
#define DECR 3
#define SEG_D 4
#define SEG_B 5
#define SEG_G 6
#define SEG_A 7
#define SEG_F 8
#define SEG_C 9
#define SEG_E 10

volatile int counter = 0;

void display(int digit)
{
    // The switch instruction sets the corresponding states on the outputs
    // depending on the specified digit
    switch (digit)
    {
    case 0:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, LOW);
        break;

    case 1:
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
        break;

    case 2:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, HIGH);
        break;

    case 3:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, HIGH);
        break;

    case 4:
        digitalWrite(SEG_A, LOW);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, HIGH);
        break;

    case 5:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, HIGH);
        break;

    case 6:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, HIGH);
        break;

    case 7:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, LOW);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, LOW);
        break;

    case 8:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, HIGH);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, HIGH);
        break;

    case 9:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, HIGH);
        digitalWrite(SEG_C, HIGH);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, HIGH);
        digitalWrite(SEG_G, HIGH);
        break;

    default:
        digitalWrite(SEG_A, HIGH);
        digitalWrite(SEG_B, LOW);
        digitalWrite(SEG_C, LOW);
        digitalWrite(SEG_D, HIGH);
        digitalWrite(SEG_E, LOW);
        digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_G, HIGH);
        break;
    }
}

void increment()
{
    counter += 1;
}

void decrement()
{
    counter -= 1;

}

void setup()
{
    // Configure pins as outputs
    pinMode(SEG_A, OUTPUT);
    pinMode(SEG_B, OUTPUT);
    pinMode(SEG_D, OUTPUT);
    pinMode(SEG_E, OUTPUT);
    pinMode(SEG_F, OUTPUT);
    pinMode(SEG_G, OUTPUT);
    pinMode(INCR, INPUT_PULLUP);
    pinMode(DECR, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(DECR), decrement, FALLING);
    attachInterrupt(digitalPinToInterrupt(INCR), increment, FALLING);
   
}

void loop()
{
   for (counter = 0; counter < 12; counter++)
    {
        display(counter);
        delay(1000);
    }
  
}
