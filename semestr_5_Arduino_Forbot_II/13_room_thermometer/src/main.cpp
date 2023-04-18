#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"

#define RS 3
#define E 4
#define D4 5
#define D5 6
#define D6 7
#define D7 8
#define DHT11_PIN 10
#define SET_UP_watch 11
#define SET_UP_HOURS 12
#define SET_UP_MINUTES 13
#define PHOTORESISTOR A0
#define DS18B20 A1
#define LED_BAR A2

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);                                        // 2x16 HD44780 LCD init
Adafruit_NeoPixel LED_bar = Adafruit_NeoPixel(8, LED_BAR, NEO_GRB + NEO_KHZ800); // WS2812 LED bar init
OneWire oneWire(DS18B20);                                                        // One wire line init
DallasTemperature sensors(&oneWire);
DeviceAddress termomeher_outside = {0x28, 0x14, 0x2F, 0x78, 0x0E, 0x0, 0x0, 0x4E}; // init our DS18B20 sensor by it's address
DHT dht;                                                                           // humidity sensor init
unsigned long sensors_last_refresh = 0;
unsigned long watch_last_refresh = 0;
unsigned long actual_time = 0;
volatile int state = 0; // state 0 - display temp, humid, etc., state 1 - set up watch, state 2
int hours = 0;
int minutes = 0;
int seconds = 0;
bool hour_button_state = true;
bool last_hour_button_state = true;
bool minute_button_state = true;
bool last_minute_button_state = true;

void LCD_watch()
{
  lcd.setCursor(5, 7);
  if (hours < 10 && minutes < 10 && seconds < 10)
    lcd.print(" W:0" + String(hours) + ":0" + String(minutes) + ":0" + String(seconds));
  else if (hours < 10 && minutes < 10)
    lcd.print(" W:0" + String(hours) + ":0" + String(minutes) + ":" + String(seconds));
  else if (hours < 10 && seconds < 10)
    lcd.print(" W:0" + String(hours) + ":" + String(minutes) + ":0" + String(seconds));
  else if (minutes < 10 && seconds < 10)
    lcd.print(" W:" + String(hours) + ":0" + String(minutes) + ":0" + String(seconds));
  else if (hours < 10)
    lcd.print(" W:0" + String(hours) + ":" + String(minutes) + ":" + String(seconds));
  else if (minutes < 10)
    lcd.print(" W:" + String(hours) + ":0" + String(minutes) + ":" + String(seconds));
  else if (seconds < 10)
    lcd.print(" W:" + String(hours) + ":" + String(minutes) + ":0" + String(seconds));
  else
    lcd.print(" W:" + String(hours) + ":" + String(minutes));
}

void setup()
{
  dht.setup(DHT11_PIN);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Welcome!");
  lcd.setCursor(0, 1);
  lcd.print("Wait for measure!");
  LED_bar.begin();
  LED_bar.show();
  LED_bar.setPixelColor(0, LED_bar.Color(0, 255, 0));
  LED_bar.show();
  delay(2000);
  LED_bar.setPixelColor(0, LED_bar.Color(0, 0, 0));
  LED_bar.show();
  lcd.clear();
  pinMode(SET_UP_watch, INPUT_PULLUP);
  Serial.begin(9600);
}

int photoresistor_read()
{
  int photoresistor_read = analogRead(PHOTORESISTOR);
  if (photoresistor_read > 200) // values greater than 200 will be visible only if we use very heavy lights, not possible in normal conditions.
    photoresistor_read = 200;
  int brightness = map(photoresistor_read, 0, 200, 1, 100);
  return brightness;
}

void LCD_data(float temp, int humid, int brightness)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:" + String(temp) + "C" + " H:" + String(humid) + "%RH");
  lcd.setCursor(0, 1);
  lcd.print("B:" + String(brightness) + "%");
}

void go_to_watch_setup_mode()
{
  if (digitalRead(SET_UP_watch) == LOW)
  {
    LED_bar.setPixelColor(0, LED_bar.Color(200, 0, 0));
    LED_bar.show();
    delay(2000);
    digitalWrite(SET_UP_watch, HIGH);
    state = 1;
  }
}

void exit_watch_set_up_mode()
{
  if (digitalRead(SET_UP_watch) == LOW)
  {
    LED_bar.setPixelColor(0, LED_bar.Color(0, 0, 200));
    LED_bar.show();
    seconds = 0;
    delay(2000);
    digitalWrite(SET_UP_watch, HIGH);
    state = 0;
  }
}

void hours_check()
{
  if (hours < 23)
    hours++;
  else
    hours = 0;
}

void minutes_check()
{

  if (minutes < 59)
    minutes++;
  else
  {
    minutes = 0;
    hours_check();
  }
}

void seconds_check()
{
  if (seconds < 59)
    seconds++;
  else
  {
    seconds = 0;
    minutes_check();
  }
}

void watch_refresh()
{
  seconds_check();
  LCD_watch();
  watch_last_refresh = actual_time;
}

void get_data_from_sensors(float *t, float *h, float *b)
{
  sensors.requestTemperatures();
  *t = sensors.getTempC(termomeher_outside);
  *h = dht.getHumidity();
  *b = photoresistor_read();
}

void sensors_refresh()
{
  float temp, humid, brighthness;
  get_data_from_sensors(&temp, &humid, &brighthness);
  LCD_data(temp, humid, brighthness);
  sensors_last_refresh = actual_time;
}

void working_normally()
{
  actual_time = millis();
  go_to_watch_setup_mode();
  if (actual_time - sensors_last_refresh >= 5000UL || sensors_last_refresh == 0UL)
  {
    sensors_refresh();
  }
  else if (actual_time - watch_last_refresh >= 1000UL)
  {
    watch_refresh();
  }
}

void change_hours()
{
  hour_button_state = digitalRead(SET_UP_HOURS);
  if (hour_button_state != last_hour_button_state)
  {
    if (hour_button_state == LOW)
    {
      if (hours < 23)
        hours++;
      else
        hours = 0;
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("Hour: " + String(hours));
      digitalWrite(SET_UP_HOURS, HIGH);
    }
  }
  last_hour_button_state = hour_button_state;
  delay(50);
}

void change_minutes()
{
  minute_button_state = digitalRead(SET_UP_MINUTES);
  if (last_minute_button_state != minute_button_state)
  {
    if (minute_button_state == LOW)
    {
      if (minutes < 59)
        minutes++;
      else
        minutes = 0;
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("Minute: " + String(minutes));
      digitalWrite(SET_UP_MINUTES, HIGH);
    }
  }
  last_minute_button_state = minute_button_state;
  delay(50);
}

void loop()
{
  switch (state)
  {
  case 0:
    working_normally();
    break;
  case 1:
    Serial.println(digitalRead(SET_UP_watch));
    exit_watch_set_up_mode();
    change_hours();
    change_minutes();
    break;
  }
}