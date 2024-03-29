/*
For the advanced - generating melodies
If you find yourself in the world of music you can generate various melodies.
File > Examples > Digital > toneMelody.
There you will find an example program that generates a simple melody.
*/

#include "pitches.h"

// notes in the melody:
int melody[] = {
    NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
    NOTE_AS3, NOTE_AS4, 0, 0,
    NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
    NOTE_AS3, NOTE_AS4, 0, 0,
    NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
    NOTE_DS3, NOTE_DS4, 0, 0,
    NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
    NOTE_DS3, NOTE_DS4, 0, 0, 
    NOTE_DS4, NOTE_CS4, NOTE_D4, NOTE_CS4, 
    NOTE_DS4, NOTE_DS4, NOTE_GS3, NOTE_G3, 
    NOTE_CS4, NOTE_C4, NOTE_FS4, NOTE_F4, 
    NOTE_E3, NOTE_AS4, NOTE_A4, NOTE_GS4, 
    NOTE_DS4, NOTE_B3, NOTE_AS3, NOTE_A3, 
    NOTE_GS3, 0, 0, 0};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
    12, 12, 12, 12,
    12, 12, 6, 3,
    12, 12, 12, 12,
    12, 12, 6, 3,
    12, 12, 12, 12,
    12, 12, 6, 3,
    12, 12, 12, 12,
    12, 12, 6, 6, 
    18, 18, 18, 6, 
    6, 6, 6, 6, 
    6, 18, 18, 18, 
    18, 18, 18, 10, 
    10, 10, 10,  10, 
    10, 3, 3, 3};

void setup()
{
    pinMode(A5, OUTPUT);
}

void play_melody()
{
    // Iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 8; thisNote++)
    {
        // To calculate the note duration, take one second divided by the note type.
        // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(A5, melody[thisNote], noteDuration);
        // To distinguish the notes, set a minimum time between them.
        int pauseBetweenNotes = noteDuration * 2;
        delay(pauseBetweenNotes);
        noTone(A5);
    }
}

void loop()
{
    play_melody();
}
