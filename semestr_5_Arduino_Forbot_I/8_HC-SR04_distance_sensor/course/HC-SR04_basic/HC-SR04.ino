/*
We will create a circuit that will take distance measurements at regular intervals and display them on a computer screen.
The description of the leads is physically on the sensor, but for the sake of formality I present it below.
   1. Vcc - 5V
   2. Trig
   3. Echo
   4. Gnd

MORE INFO:
Note the new function delayMicroseconds();, this is nothing more than the equivalent of the well-known function delay();.
The difference is probably obvious. The new function counts down time in microseconds.
Let me just remind you that the delay function used so far measures milliseconds.

The sequence that starts the measurement is very simple.
First, we set a low signal on the pin connected to the sensor's trigger input.
2 microseconds are enough, then we set the high state to 10 microseconds.
The sensor takes a measurement and returns the results on the echo pin.

The question is how to read it?
Is there a UART or other communication interface needed for this?
No, fortunately this sensor is very simple and the measured distance is represented by a pulse (high state) on the echo pin.
Its length is proportional to the distance. The longer it is, the greater the measured distance.
This is where a new function available in Arduino will come in handy.

result = pulseIn(11, HIGH);

The function, in its simplest form, takes only two arguments. The number of the pin to be checked and the logic level (low/high) to be measured.

*/

#define ECHO 11
#define TRIGGER 12
const int time_that_sound_travel_1_cm = 58; //in microseconds

void setup()
{
    Serial.begin(9600);
    pinMode(TRIGGER, OUTPUT); // TRIGGER as OUTPUT
    pinMode(ECHO, INPUT);     // ECHO as INPUT
}

void start_measurement(){
    digitalWrite(TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER, LOW);
}

int measured_distance(long distance){
    long time = pulseIn(ECHO, HIGH);
    distance = time / time_that_sound_travel_1_cm;
    return distance;
 
}


void loop()
{
    start_measurement();
    long distance = measured_distance(distance);
    Serial.println(String("Distance: ") + distance + String(" [cm]"));
    delay(500);
}