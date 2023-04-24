/*
Write a program that will play a short melody when motion is detected.
Such a device can be placed, for example, at the door to inform about a new person entering the room.
*/

#include "pitches.h"
#define LED_R 10
#define LED_G 11
#define LED_B 12
#define PIR 2
#define BUZZER A5

void setup()
{
    pinMode(LED_R, OUTPUT); // LEDs as output
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(A5, OUTPUT); // Buzzer output
    pinMode(PIR, INPUT); // PIR as input
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
}

void play_melody()
{
    // Iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 8; thisNote++)
    {
        // To calculate the note duration, take one second divided by the note type.
        // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(BUZZER, melody[thisNote], noteDuration);
        // To distinguish the notes, set a minimum time between them.
        int pauseBetweenNotes = noteDuration * 2;
        delay(pauseBetweenNotes);
        noTone(BUZZER);
    }
}

void LED_alarm()
{
    if (digitalRead(PIR) == HIGH) // If motion is detected
    {
        digitalWrite(LED_R, HIGH); // ALARM status - red LED
        digitalWrite(LED_G, LOW);
        play_melody();
    }
    else
    {
        digitalWrite(LED_R, LOW); // OK status - green LED
        digitalWrite(LED_G, HIGH);
        noTone(BUZZER);
    }
}
void loop()
{
    LED_alarm();
}