/*
We  run the code written in the previous lesson. Only two changes need to be made.
The first, is to display the result on a new line without the unit.
The second is to increase the frequency of measurements a bit - this will make the graph smoother.
*/

#define TRIGGER 12
#define ECHO 11
#define BUZZER 2
const int time_that_sound_travel_1_cm = 58; // in microseconds
const int max_range_of_sensor_in_cm = 400;

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

int measure_distance(int distance)
{
    long time = pulseIn(ECHO, HIGH);
    distance = time / time_that_sound_travel_1_cm;
    return distance;
}

int check_measured_distance(int distance)
{
    if (distance < 0)
    {
        distance = 0;
    }
    else if (distance > max_range_of_sensor_in_cm)
    {
        distance = max_range_of_sensor_in_cm;
    }
    return distance;
}

void loop()
{
    start_measurement();
    int distance = measure_distance(distance);
    distance = check_measured_distance(distance); //Check is the distance is in the range of sensor and correct it if not.
    Serial.print(">Distance [cm]:"); // In this way we create plot in Teleplot main screen.
    Serial.println(distance);        // That value will be plotted via Teleplot
    delay(100);
}
