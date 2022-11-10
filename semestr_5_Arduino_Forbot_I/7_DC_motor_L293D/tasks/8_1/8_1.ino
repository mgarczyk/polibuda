/*

Add two more diodes to the circuit and simulate the other motor with them.
Write a program that will perform the sequence: both forward, both in opposite directions, both backward and so on in a circle.
Of course, between the change of direction, keep an interval of, say: 2 seconds.

*/

#define SPEED_CONTROL_ENG_1 6
#define TURN_RIGHT_ENG_1 7
#define TURN_LEFT_ENG_1 8
#define SPEED_CONTROL_ENG_2 11
#define TURN_RIGHT_ENG_2 12
#define TURN_LEFT_ENG_2 13

void setup()
{
    pinMode(SPEED_CONTROL_ENG_1, OUTPUT);
    digitalWrite(SPEED_CONTROL_ENG_1, HIGH);
    pinMode(TURN_LEFT_ENG_1, OUTPUT);
    pinMode(TURN_RIGHT_ENG_1, OUTPUT);
    pinMode(SPEED_CONTROL_ENG_2, OUTPUT);
    digitalWrite(SPEED_CONTROL_ENG_2, HIGH);
    pinMode(TURN_LEFT_ENG_2, OUTPUT);
    pinMode(TURN_RIGHT_ENG_2, OUTPUT);
}

// Both engines forward (RIGHT)
void forward()
{
    digitalWrite(TURN_RIGHT_ENG_1, HIGH);
    digitalWrite(TURN_LEFT_ENG_1, LOW);
    digitalWrite(TURN_RIGHT_ENG_2, HIGH);
    digitalWrite(TURN_LEFT_ENG_2, LOW);
    delay(3000);
}

// Different sides
void different_sides()
{
    digitalWrite(TURN_RIGHT_ENG_1, HIGH); // Engine No. 1 - Forward
    digitalWrite(TURN_LEFT_ENG_1, LOW);
    digitalWrite(TURN_RIGHT_ENG_2, LOW); // Engine No. 2 - Backward
    digitalWrite(TURN_LEFT_ENG_2, HIGH);
    delay(3000);
}

// Both engines backwards (LEFT)
void backwards()
{
    digitalWrite(TURN_RIGHT_ENG_1, LOW);
    digitalWrite(TURN_LEFT_ENG_1, HIGH);
    digitalWrite(TURN_RIGHT_ENG_2, LOW);
    digitalWrite(TURN_LEFT_ENG_2, HIGH);
    delay(3000);
}

void loop()
{
    forward();
    different_sides();
    backwards();
   
}