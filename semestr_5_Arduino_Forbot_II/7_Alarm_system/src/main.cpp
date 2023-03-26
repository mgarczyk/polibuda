/*
Our alarm system will consist of a numeric keypad, a sounder, a beacon, a motion sensor (PIR) and a door-opening sensor (reed switch).

Of course, the whole thing can work in many different ways. I decided that my alarm will work as follows: when the power is turned on, we enter standby mode.
The alarm does nothing but wait for it to be armed. When you press the A key (like Alarm), the arming procedure takes place.

After a few seconds (time to leave the room), the alarm starts working - from now on our room is guarded.
The moment we detect movement in the room, the alarm begins to immediately signal the threat.

Does the alarm have time to notice a fast thief?

If we detect the opening of the door, we give the user a few seconds to disarm the alarm, which involves entering a four-digit code.
If the pin code is wrong or not entered, the alarm will also be triggered.

*/

#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#define BUZZER 11
#define CONCRATRON 10
#define PIR 12

const byte ROWS = 4;
const byte COLS = 4;
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {6, 7, 8, 9};
char keys[ROWS][COLS] = { // keymap map
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);     // keypad init
Adafruit_NeoPixel LED_bar = Adafruit_NeoPixel(8, A0, NEO_GRB + NEO_KHZ800); // LED bar init
volatile int alarm_state = 1;
volatile int confirmation_time = 3;
volatile int max_time_to_alarm = 5000;
char code_alarm[4] = {'1', '2', '3', '4'};


// STATE 1 - standby
void arming_visuals()
{
  LED_bar.setPixelColor(0, LED_bar.Color(255, 165, 0));
  LED_bar.show();
  tone(BUZZER, 500, 1000);
  delay(500);
  LED_bar.setPixelColor(0, LED_bar.Color(0, 0, 0));
  LED_bar.show();
  delay(500);
}

void arming_confirmation_visuals()
{
  LED_bar.setPixelColor(0, LED_bar.Color(255, 165, 0));
  LED_bar.show();
}

void arming_confirmation(char pressed_key)
{
  while (pressed_key == 'A' or pressed_key == 0)
  {
    arming_confirmation_visuals();
    pressed_key = keypad.getKey();
    if (pressed_key == 'B')
    {
      for (int i = 0; i < confirmation_time; i++)
      {
        arming_visuals();
      }
      alarm_state = 2;
    }
    else
    {
      alarm_state = 1;
    }
  }
}

void arming_the_alarm()

{
  char pressed_key = 0;
  pressed_key = keypad.getKey();
  if (pressed_key == 'A')
  {
    arming_confirmation(pressed_key);
  }
}

void standby()
{
  LED_bar.setPixelColor(0, LED_bar.Color(0, 15, 0));
  LED_bar.show();
  arming_the_alarm();
}

// STATE 2 - minitoring
int monitoring()
{
  if (digitalRead(PIR) == HIGH)
  {
    return 4;
  }
  else if (digitalRead(CONCRATRON) == 1)
  {
    return 3;
  }
  return 2;
}

void minitoring_visuals()
{
  LED_bar.setPixelColor(0, LED_bar.Color(15, 0, 0));
  LED_bar.show();
  delay(1000);
  LED_bar.setPixelColor(0, LED_bar.Color(0, 0, 0));
  LED_bar.show();
  delay(1000);
}

void PIR_interrupt()
{
  if (alarm_state == 2)
    alarm_state = 4;
}

// STATE 3 - disarming the alarm
void disarming_visuals()
{
  LED_bar.setPixelColor(0, LED_bar.Color(221, 160, 221));
  LED_bar.show();
}

int disarming_alarm()
{
  disarming_visuals();
  for (int i = 0; i < sizeof(code_alarm); i++)
  {
    char key_tmp = NO_KEY;
    do
    {
      key_tmp = keypad.getKey();
      delay(10);
      max_time_to_alarm-=10; //We have to count time in miliseconds, because we wait on key press. When user press the key there is maybe 50ms for AVR to get it, delay must be smaller.
    }while (key_tmp == NO_KEY && max_time_to_alarm > 0);
    if (key_tmp != code_alarm[i] or max_time_to_alarm == 0)
     return 4;
  }
  return 1;
}

// STATE 4 - alarming!
void alarming()
{
  for (int i = 0; i < 8; i++)
  {
    LED_bar.setPixelColor(i, LED_bar.Color(15, 0, 0));
    LED_bar.show();
  }
  delay(100);
  for (int i = 0; i < 8; i++)
  {
    LED_bar.setPixelColor(i, LED_bar.Color(0, 0, 15));
    LED_bar.show();
  }
  delay(100);
  tone(BUZZER, 4000, 100);
}

void setup()
{
  pinMode(BUZZER, OUTPUT);
  pinMode(CONCRATRON, INPUT_PULLUP);
  pinMode(PIR, INPUT_PULLUP);
  LED_bar.begin();
  LED_bar.show();
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(PIR), PIR_interrupt, RISING);
}

void loop()
{
  
  switch (alarm_state)
  {
  case 1:
    standby();
    break;
  case 2:
    minitoring_visuals();
    alarm_state = monitoring();
    break;
  case 3:
    disarming_visuals();
    alarm_state = disarming_alarm();
    break;
  case 4:
    alarming();
    break;
  }
}