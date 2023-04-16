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
#define PHOTORESISTOR A0
#define DS18B20 A1
#define LED_BAR A2

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);                                        // 2x16 HD44780 LCD init
Adafruit_NeoPixel LED_bar = Adafruit_NeoPixel(8, LED_BAR, NEO_GRB + NEO_KHZ800); // WS2812 LED bar init
OneWire oneWire(DS18B20);                                                        // One wire line init
DallasTemperature sensors(&oneWire);
DeviceAddress termomeher_outside = {0x28, 0x14, 0x2F, 0x78, 0x0E, 0x0, 0x0, 0x4E}; // init our DS18B20 sensor by it's address
DHT dht;                                                                           // humidity sensor init
unsigned long last_refresh = 0;
unsigned long actual_time = 0;

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
  LED_bar.setPixelColor(0, LED_bar.Color(0,0,0));
  LED_bar.show();
  lcd.clear();
 
}

int photoresistor_read()
{
  int photoresistor_read = analogRead(PHOTORESISTOR);
  if (photoresistor_read > 200) // values greater than 200 will be visible only if we use very heavy lights, not possible in normal conditions.
    photoresistor_read = 200;
  int brightness = map(photoresistor_read, 0, 200, 1, 100);
  return brightness;
}

void LCD_write(float temp, int humid, int brightness)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:" + String(temp) + "C" + " H:" + String(humid) + "%RH");
  lcd.setCursor(0, 1);
  lcd.print("B:" + String(brightness) + "%");
}

void loop()
{
  actual_time = millis();
  if (actual_time - last_refresh >= 5000UL || last_refresh == 0UL)
  {
    sensors.requestTemperatures();
    float temp = sensors.getTempC(termomeher_outside);
    int humid = dht.getHumidity();
    int brightness = photoresistor_read();
    LCD_write(temp, humid, brightness);
    last_refresh = actual_time;
  }
}