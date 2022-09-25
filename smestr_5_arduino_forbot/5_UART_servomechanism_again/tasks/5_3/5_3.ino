/*
Refine the circuit with an analog indicator. Try to add a calibration mechanism. 
Find another practical use for such a circuit!
Hint: Light up the photoresistor with an LED, to find max value.
*/

#include <Servo.h>
#define PHOTRESISTOR A1
#define SWITCH_MIN 8
#define SWITCH_MAX 9
byte postion = 0;
int position_before = 0;
int max_brightness_value = 0;
int min_brightness_value = 0;
Servo servomechanism; //servo object

// when the MAX_SWITCH is pressed then you should use very bright source of light e.g. flashlight from your smartphone to set max brightness value
int max_brightness_calibration(int photoresistor_value){
     while (digitalRead(SWITCH_MAX) == LOW)
    { 
        max_brightness_value = photoresistor_value;
        delay(100);
    }
    return max_brightness_value;
}

// when the MIN_SWITCH is pressed then you should turn off all the light sources to set min brightness value
int min_brightness_calibration(int photoresistor_value){
     while (digitalRead(SWITCH_MIN) == LOW)
    { 
        min_brightness_value = photoresistor_value;
        delay(100);
    }
    return min_brightness_value;
}

void setup(){
    servomechanism.attach(11); //atatch servo
    pinMode(SWITCH_MAX, INPUT_PULLUP);
    pinMode(SWITCH_MIN, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop(){
    int photoresistior_value = analogRead(PHOTRESISTOR);
    max_brightness_value = max_brightness_calibration(photoresistior_value);
    min_brightness_value = min_brightness_calibration(photoresistior_value);
    postion = map(photoresistior_value, 0, max_brightness_value, 0, 180); //map ADC value to degrees that are understand by servo
    if (abs(postion - position_before) > 5){ //chek is new position is diffrent that previous about 5 degree
        servomechanism.write(postion);
        position_before = postion;
    }
    Serial.println(String("Photoresistor ADC value: ") + photoresistior_value);
    delay(1000);
}


