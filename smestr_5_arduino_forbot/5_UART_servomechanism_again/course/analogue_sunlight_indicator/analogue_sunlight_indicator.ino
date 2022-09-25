/*
It's time for the promised use of servo in practice. Currently, more and more information is presented digitally, i.e. on a display.
However, some values, such as temperature, light intensity, etc., are better presented on traditional analog indicators. That is, ones with a pointer.
Therefore, we will now build an analog sunshine indicator using a microserver. 
The pointer placed on its arm will indicate the amount of light falling on the sensor. 
For this you will need an Arduino with a photoresistor connected in a voltage divider circuit and a servo.
*/

#include <Servo.h>
#define PHOTRESISTOR A1
byte postion = 0;
int position_before = 0;
Servo servomechanism; //servo object

void setup(){
    servomechanism.attach(11); //atatch servo
    Serial.begin(9600);
    
}

void loop(){
    int photoresistior_value = analogRead(PHOTRESISTOR);
    postion = map(photoresistior_value, 0, 950, 0, 180); //map ADC value to degrees that are understand by servo
    if (abs(postion - position_before) > 5){ //chek is new position is diffrent that previous about 5 degree
        servomechanism.write(postion);
        position_before = postion;
    }
    Serial.println(String("Photoresistor ADC value: ") + photoresistior_value);
    delay(100);
}


