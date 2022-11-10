/*
Write a program that represents the distance of an obstacle from the sensor on a ruler of LEDs. T
Closer the obstacle is to the sensor, the more LEDs should light up.
*/

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
#define GREEN_LED_DOWN 3
#define GREEN_LED_UP 4
#define YELLOW_LED_DOWN 5
#define YELLOW_LED_UP 6
#define RED_LED_DOWN 7
#define RED_LED_UP 8
const int time_that_sound_travel_1_cm = 58; // in microseconds

void setup()
{
    Serial.begin(9600);
    pinMode(TRIGGER, OUTPUT);
    pinMode(GREEN_LED_DOWN, OUTPUT);
    pinMode(GREEN_LED_UP, OUTPUT);
    pinMode(YELLOW_LED_DOWN, OUTPUT);
    pinMode(YELLOW_LED_UP, OUTPUT);
    pinMode(RED_LED_DOWN, OUTPUT);
    pinMode(RED_LED_UP, OUTPUT);
    pinMode(ECHO, INPUT);
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

int map_distance(long distance, int distance_mapped)
{
    distance_mapped = map(distance, 0, 400, 0, 5); // we have 6 LED's that indicates how far the object is from sensor, minimum distance is 0 cm and max is 400 cm
    return distance_mapped;
}

void reset_LEDs()
{
    digitalWrite(GREEN_LED_DOWN, LOW);
    digitalWrite(GREEN_LED_UP, LOW);
    digitalWrite(YELLOW_LED_DOWN, LOW);
    digitalWrite(YELLOW_LED_UP, LOW);
    digitalWrite(RED_LED_DOWN, LOW);
    digitalWrite(RED_LED_UP, LOW);
}




// The closer the object is to the sensor, the more LEDs light up.
void check_scope(int distance_mapped)
{
    switch (distance_mapped)
    {
    case 0:
        reset_LEDs();
        digitalWrite(GREEN_LED_DOWN, HIGH);
        digitalWrite(GREEN_LED_UP, HIGH);
        digitalWrite(YELLOW_LED_DOWN, HIGH);
        digitalWrite(YELLOW_LED_UP, HIGH);
        digitalWrite(RED_LED_DOWN, HIGH);
        digitalWrite(RED_LED_UP, HIGH);
        break;
    case 1:
        reset_LEDs();
        digitalWrite(GREEN_LED_DOWN, HIGH);
        digitalWrite(GREEN_LED_UP, HIGH);
        digitalWrite(YELLOW_LED_DOWN, HIGH);
        digitalWrite(YELLOW_LED_UP, HIGH);
        digitalWrite(RED_LED_DOWN, HIGH);
        break;
    case 2:
        reset_LEDs();
        digitalWrite(GREEN_LED_DOWN, HIGH);
        digitalWrite(GREEN_LED_UP, HIGH);
        digitalWrite(YELLOW_LED_DOWN, HIGH);
        digitalWrite(YELLOW_LED_UP, HIGH);
        break;

    case 3:
        reset_LEDs();
        digitalWrite(GREEN_LED_DOWN, HIGH);
        digitalWrite(GREEN_LED_UP, HIGH);
        digitalWrite(YELLOW_LED_DOWN, HIGH);
        break;

     case 4:
        reset_LEDs();
        digitalWrite(GREEN_LED_DOWN, HIGH);
        digitalWrite(GREEN_LED_UP, HIGH);
        break;

    case 5:
        reset_LEDs();
        digitalWrite(GREEN_LED_DOWN, HIGH);
        break;

    default:
        break;
    }
}

void loop()
{
    start_measurement();
    long distance = measure_distance(distance);
    int distance_mapped = map_distance(distance, distance_mapped);
    check_scope(distance_mapped); // Turn on buzzer when the object is beetwen 10 - 25 [cm] from sensor.
    Serial.println(String("Distance: ") + distance + String(" [cm]"));
    delay(5);
}
