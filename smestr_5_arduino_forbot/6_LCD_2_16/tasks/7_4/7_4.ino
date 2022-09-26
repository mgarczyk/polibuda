/*
Write a program that is a simple stopwatch. When one button is pressed, the measurement starts and the current time appears on the screen.
When the second button is pressed, the screen says "End" and the measured time in seconds appears.
*/

#include <LiquidCrystal.h>
#define START_STOPER 10
#define RESET_STOPER 11
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int part_of_second = 0;
int seconds = 0;
int minutes = 0;

void setup()
{
    lcd.begin(16, 2);
    pinMode(START_STOPER, INPUT_PULLUP);
    pinMode(RESET_STOPER, INPUT_PULLUP);
    lcd.setCursor(0, 0);
    lcd.print("Stop");
    lcd.setCursor(0, 1);
    lcd.print("00:00:00");
}

void reset()
{
    setup();
    part_of_second = 0;
    seconds = 0;
    minutes = 0;
}

void stop_the_stoper()
{
    while (digitalRead(START_STOPER) == LOW)
    {
        lcd.setCursor(0, 0);
        lcd.print("Stop!");
    }
}

int count_part_of_seconds()
{
    delay(100);
    return 10;
}

void print_LCD()
{
    if (minutes < 10)
    {
        if (seconds < 10)
            lcd.print("0" + String(minutes) + ":0" + String(seconds) + ":" + String(part_of_second));
        else
        {
            lcd.print("0" + String(minutes) + ":" + String(seconds) + ":" + String(part_of_second));
        }
    }
    else
    {
        if (seconds < 10)
            lcd.print(String(minutes) + ":0" + String(seconds) + ":" + String(part_of_second));
        else
        {
            lcd.print(String(minutes) + ":" + String(seconds) + ":" + String(part_of_second));
        }
    }
}

void loop()
{

    if (digitalRead(START_STOPER) == LOW)
    {
        delay(500);
        while (digitalRead(START_STOPER == HIGH))
        {
            lcd.setCursor(0, 0);
            lcd.print("Start");
            if (digitalRead(RESET_STOPER) == LOW)
            {
                reset();
                break;
            }
            else if (digitalRead(START_STOPER) == LOW)
            {
                stop_the_stoper();
            }

            if (part_of_second < 90)
            {
                part_of_second += count_part_of_seconds();
                lcd.setCursor(0, 1);
                print_LCD();
            }
            else if (seconds < 59)
            {
                part_of_second = -10;
                seconds += 1;
            }
            else
            {
                seconds = -1;
                minutes += 1;
            }
        }
    }
}
