/*
Finally, it would be useful to expand our thermometer with another temperature indicator.
A line of RGB LEDs, which we already learned at the beginning of the course, will be ideal here.
Let's assume that each of the 8 LEDs symbolizes 5ºC.
*/

#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DallasTemperature.h>

Adafruit_NeoPixel LED_bar = Adafruit_NeoPixel(8, A1, NEO_GRB + NEO_KHZ800);
OneWire oneWire(A0);
DallasTemperature sensors(&oneWire);
DeviceAddress termomeher_outside = {0x28, 0x14, 0x2F, 0x78, 0x0E, 0x0, 0x0, 0x4E};

int check_is_range(int temp)
{
  if (temp > 40)
  {
    temp = 40;
  }
  else if (temp < -40)
  {
    temp = -40;
  }
  return temp;
}

void positive_values(int temp)
{
  temp = map(temp, 0, 40, 1, 8);
  for (int i = 0; i < temp; i++)
  {
    LED_bar.setPixelColor(i, LED_bar.Color(255, 0, 0));
  }
}

void negative_values(int temp)
{
  temp = map(temp, -40, 0, 1, 8);
  for (int i = 8; i > temp; i--)
  {
    LED_bar.setPixelColor(i, LED_bar.Color(0, 0, 255));
  }
}

void RGB_thermomether(int temp)
{
  temp = check_is_range(temp);
  LED_bar.clear();
  if (temp >= 0)
  {
    positive_values(temp);
  }
  else
  {
    negative_values(temp);
  }

  LED_bar.show();
}

void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  LED_bar.begin();
}

void loop(void)
{
  sensors.requestTemperatures(); 
  Serial.print("Aktualna temp: ");
  Serial.println(sensors.getTempC(termomeher_outside)); 
  int tempLinijka = sensors.getTempC(termomeher_outside);
  RGB_thermomether(tempLinijka);
  delay(500);
}
