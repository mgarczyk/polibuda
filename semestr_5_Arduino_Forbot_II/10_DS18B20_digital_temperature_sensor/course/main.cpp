/*
Finally, it would be useful to expand our thermometer with another temperature indicator. 
A line of RGB LEDs, which we already learned at the beginning of the course, will be ideal here. 
Let's assume that each of the 8 LEDs symbolizes 5ºC.
*/

#include <Adafruit_NeoPixel.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
 
//Konfiguracja linijki
Adafruit_NeoPixel linijka = Adafruit_NeoPixel(8, A1, NEO_GRB + NEO_KHZ800);
 
OneWire oneWire(A0); //Podłączenie do A0
DallasTemperature sensors(&oneWire); //Przekazania informacji do biblioteki
 
DeviceAddress termometrZewnetrzny = {0x28, 0x14, 0x2F, 0x78, 0x0E, 0x0, 0x0, 0x4E};

void termometrRGB(int temperatura) {
  //Sprawdzamy, czy temperatura jest w odpowiednim zakresie
  if (temperatura > 40) {
    temperatura = 40;
  } else if (temperatura < -40) {
    temperatura = -40;
  }
 
  //Wyczysc linijkę
  linijka.clear();
  
  if (temperatura >= 0) {
    //Dla wartosci dodatnich
     temperatura = map(temperatura, 0, 40, 1, 8); 
      
     int i = 0;
     for (i = 0; i < temperatura; i++) {
        linijka.setPixelColor(i, linijka.Color(255, 0, 0)); //Dioda nr i świeci na czerwono
     }
     
  } else {
    //Dla wartosci ujemnych
     temperatura = map(temperatura, -40, 0, 1, 8);
     int i = 0;
     for (i = 8; i > temperatura; i--) {
        linijka.setPixelColor(i, linijka.Color(0, 0, 255)); //Dioda nr i świeci na niebiesko
     }
  }
 
  linijka.show(); 
}

void setup(void) {
  Serial.begin(9600);
  sensors.begin(); //Inicjalizacja czujnikow
  linijka.begin(); //Inicjalizacja
}
 
void loop(void) { 
  sensors.requestTemperatures(); //Pobranie temperatury czujnika
  Serial.print("Aktualna temperatura: ");
  Serial.println(sensors.getTempC(termometrZewnetrzny));  //Wyswietlenie informacji
  int tempLinijka = sensors.getTempC(termometrZewnetrzny);
  termometrRGB(tempLinijka);
  delay(500);
}
 