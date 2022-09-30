/*
It's time for the last exercise in this part of the Arduino course.
This time, let's add a buzzer, a component that makes sound, to our circuit.
This component has two inputs, when you apply Vcc to one of them and connect the other one to ground.
Buzzer will start making a loud sound.
It is not very pleasant, so I suggest leaving the sticker on it (this makes the sound produced quieter).
As you can easily guess from the inscription, this label protects the inside of the buzzer when washing the circuit boards.
This is done, mainly to remove traces of soldering.


This time we will write a function to check whether an object is within a certain distance from the sensor.
 If it is, an alarm (buzzer sound) will sound.
*/

#define TRIGGER 12
#define ECHO 11
#define BUZZER 2
const int time_that_sound_travel_1_cm = 58; // in microseconds

void setup()
{
    Serial.begin(9600);
    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(BUZZER, OUTPUT);
}

void start_measurement()
{
    digitalWrite(TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER, LOW);
}


int measure_distance(long distance)
{
    long time = pulseIn(ECHO, HIGH);
    distance = time / time_that_sound_travel_1_cm;
    return distance;
}

void check_scope(long distance, int a, int b)
{
    if ((distance > a) && (distance < b))
    {
        digitalWrite(BUZZER, HIGH); // Turn on buzzer
    }
    else
    {
        digitalWrite(BUZZER, LOW); // Turn off buzzer when the object is out of scope
    }
}



void loop()
{
    start_measurement();
    long distance = measure_distance(distance);
    check_scope(distance, 10, 25); // Turn on buzzer when the object is beetwen 10 - 25 [cm] from sensor.
    Serial.println(String("Distance: ") + distance + String(" [cm]"));
    delay(100);
}
