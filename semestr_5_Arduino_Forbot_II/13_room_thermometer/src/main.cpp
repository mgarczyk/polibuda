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
#define MAX_MIN_DSIPLAY 9
#define DHT11_PIN 10
#define SET_UP_WATCH 11
#define SECOND_BUTTON 12
#define THIRD_BUTTON 13
#define PHOTORESISTOR A0
#define DS18B20 A1
#define LED_BAR A2

// VARIABLES AND OBEJCTS
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);                                        // 2x16 HD44780 LCD init
Adafruit_NeoPixel LED_bar = Adafruit_NeoPixel(8, LED_BAR, NEO_GRB + NEO_KHZ800); // WS2812 LED bar init
OneWire oneWire(DS18B20);                                                        // One wire line init
DallasTemperature sensors(&oneWire);
DeviceAddress termomeher_outside = {0x28, 0x14, 0x2F, 0x78, 0x0E, 0x0, 0x0, 0x4E}; // init our DS18B20 sensor by it's address
DHT dht;                                                                           // humidity sensor init
unsigned long sensors_last_refresh = 0;
unsigned long senosors_refresh_time = 5000UL;
unsigned long watch_last_refresh = 0;
unsigned long watch_refresh_time = 1000UL;
unsigned long max_min_last_reset = 0;
unsigned long max_min_reset_time = 43200000UL; // 12h in miliseconds
unsigned long actual_time = 0;
volatile int state = 0; // state 0 - display temp, humid, etc., state 1 - set up watch, state 2
float temp = 0;
int humid = 0;
int brightness = 0;
float max_temp = 0;
float min_temp = 1000;
int max_humid = 0;
int min_humid = 1000;
int max_brightness = 0;
int min_brightness = 1000;
int hours = 0;
int minutes = 0;
int seconds = 0;
bool second_button_state = true;
bool last_second_button_state = true;
bool third_button_state = true;
bool last_third_button_state = true;

// SETUP
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
  pinMode(SET_UP_WATCH, INPUT_PULLUP);
  Serial.begin(9600);
}

// LCD display
void LCD_data(float temp, int humid, int brightness)
{
  lcd.setCursor(0, 0);
  lcd.print("T:" + String(temp) + "C" + " H:" + String(humid) + "%RH");
  lcd.setCursor(0, 1);
  lcd.print("B:" + String(brightness) + "%");
}

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

void LCD_max_min()
{
  lcd.setCursor(0, 0);
  lcd.print("T: " + String(max_temp) + "C " + String(min_temp) + "C");
  lcd.setCursor(0, 1);
  lcd.print("H: " + String(max_humid) + "%    " + String(min_humid) + "%");
}

void clear_LED_bar()
{
  for (int i = 0; i < 8; i++)
  {
    LED_bar.setPixelColor(i, LED_bar.Color(0, 0, 0));
  }
  LED_bar.show();
}

// STATE 1 - Watch SET UP
void check_watch_set_up()
{
  if (digitalRead(SET_UP_WATCH) == LOW)
  {
    clear_LED_bar();
    LED_bar.setPixelColor(0, LED_bar.Color(200, 200, 0));
    LED_bar.show();
    delay(2000);
    clear_LED_bar();
    digitalWrite(SET_UP_WATCH, HIGH);
    state = 1;
  }
}

void change_hours()
{
  second_button_state = digitalRead(SECOND_BUTTON);
  if (second_button_state != last_second_button_state)
  {
    if (second_button_state == LOW)
    {
      if (hours < 23)
        hours++;
      else
        hours = 0;
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("Hour: " + String(hours));
      digitalWrite(SECOND_BUTTON, HIGH);
    }
  }
  last_second_button_state = second_button_state;
  delay(50);
}

void change_minutes()
{
  third_button_state = digitalRead(THIRD_BUTTON);
  if (last_third_button_state != third_button_state)
  {
    if (third_button_state == LOW)
    {
      if (minutes < 59)
        minutes++;
      else
        minutes = 0;
      lcd.setCursor(0, 1);
      lcd.clear();
      lcd.print("Minute: " + String(minutes));
      digitalWrite(THIRD_BUTTON, HIGH);
    }
  }
  last_third_button_state = third_button_state;
  delay(50);
}

void display_temp_on_LED_bar(float temp)
{
  clear_LED_bar();
  temp = map(temp, 0, 40, 1, 8);
  for (int i = 0; i < temp; i++)
  {
    LED_bar.setPixelColor(i, LED_bar.Color(20, 0, 0));
  }
  LED_bar.show();
}

void exit_watch_set_up_mode()
{
  if (digitalRead(SET_UP_WATCH) == LOW)
  {
    clear_LED_bar();
    LED_bar.setPixelColor(0, LED_bar.Color(0, 0, 200));
    LED_bar.show();
    seconds = 0;
    delay(2000);
    clear_LED_bar();
    display_temp_on_LED_bar(temp);
    digitalWrite(SET_UP_WATCH, HIGH);
    state = 0;
  }
}

// WATCH

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

// STATE 0 - ROOM THERMOMETER
int photoresistor_read()
{
  int photoresistor_read = analogRead(PHOTORESISTOR);
  if (photoresistor_read > 200) // values greater than 200 will be visible only if we use very heavy lights, not possible in normal conditions.
    photoresistor_read = 200;
  int brightness = map(photoresistor_read, 0, 200, 1, 100);
  return brightness;
}

void get_data_from_sensors(float *t, int *h, int *b)
{
  sensors.requestTemperatures();
  *t = sensors.getTempC(termomeher_outside);
  *h = dht.getHumidity();
  *b = photoresistor_read();
}

void check_is_temp_should_be_displayed()
{
  third_button_state = digitalRead(THIRD_BUTTON);
  if (third_button_state != last_third_button_state)
  {
    if (third_button_state == LOW)
    {
      display_temp_on_LED_bar(temp);
      digitalWrite(THIRD_BUTTON, HIGH);
      delay(50);
    }
  }
  last_third_button_state = third_button_state;
}

void display_humid_on_LED_bar(float humid)
{

  clear_LED_bar();
  humid = map(humid, 1, 100, 1, 8);
  for (int i = 0; i < humid; i++)
  {
    LED_bar.setPixelColor(i, LED_bar.Color(0, 0, 20));
  }
  LED_bar.show();
}

void check_is_humid_should_be_display()
{
  second_button_state = digitalRead(SECOND_BUTTON);
  if (second_button_state != last_second_button_state)
  {
    if (second_button_state == LOW)
    {
      display_humid_on_LED_bar(humid);
      digitalWrite(SECOND_BUTTON, HIGH);
      delay(50);
    }
  }
  last_second_button_state = second_button_state;
}

void check_max_min_values()
{
  if (temp > max_temp)
    max_temp = temp;
  if (humid > max_humid)
    max_humid = humid;
  if (brightness > max_brightness)
    max_brightness = brightness;
  if (temp < min_temp)
    min_temp = temp;
  if (humid < min_humid)
    min_humid = humid;
  if (brightness < min_brightness)
    min_brightness = brightness;
}

void refresh_sensors_time()
{
  if (actual_time - sensors_last_refresh >= senosors_refresh_time || sensors_last_refresh == 0UL)
  {
    get_data_from_sensors(&temp, &humid, &brightness);
    check_max_min_values();
    LCD_data(temp, humid, brightness);
    sensors_last_refresh = actual_time;
  }
  else if (actual_time - watch_last_refresh >= watch_refresh_time)
  {
    watch_refresh();
  }
  else if (actual_time - max_min_last_reset >= max_min_reset_time)
  {
    max_temp = 0;
    min_temp = 1000;
    max_humid = 0;
    min_humid = 1000;
    max_brightness = 0;
    min_brightness = 1000;
  }
}

void check_max_min_display_mode()
{
  if (digitalRead(MAX_MIN_DSIPLAY) == LOW)
  {
    state = 2;
    seconds += 2;
    digitalWrite(MAX_MIN_DSIPLAY, HIGH);
    delay(2000);
    lcd.clear();
  }
}

void exit_max_min_display_mode()
{
  if (digitalRead(MAX_MIN_DSIPLAY) == LOW)
  {
    state = 0;
    seconds += 2;
    digitalWrite(MAX_MIN_DSIPLAY, HIGH);
    delay(2000);
    lcd.clear();
  }
}

void room_thermometer()
{
  actual_time = millis();
  refresh_sensors_time();
  check_watch_set_up();
  check_max_min_display_mode();
  check_is_humid_should_be_display();
  check_is_temp_should_be_displayed();
}

void loop()
{
  switch (state)
  {
  case 0:
    room_thermometer();
    break;
  case 1:
    exit_watch_set_up_mode();
    change_hours();
    change_minutes();
    break;
  case 2:
    actual_time = millis();
    if (actual_time - watch_last_refresh >= watch_refresh_time)
    {
      seconds_check();
      watch_last_refresh = actual_time;
    }
    LCD_max_min();
    exit_max_min_display_mode();
    break;
  }
}