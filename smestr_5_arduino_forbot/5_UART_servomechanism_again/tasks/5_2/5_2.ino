/*
Go back to homework 2.4, which can be found in the third part of the Arduino course, and perform it this time using the switch instruction.
Task 2.4: Change the LED_two_way.ino program so that it sends an appropriate message through the terminal if the wrong color is selected.

*/

#define red_LED 7
#define green_LED 8
char selected_LED;

void setup()
{
    Serial.begin(9600); // set the baud of transmission
    Serial.println("Hello World");
    pinMode(green_LED, OUTPUT);
    pinMode(red_LED, OUTPUT);
    digitalWrite(red_LED, LOW);
    digitalWrite(green_LED, LOW);
}

void loop()
{
    if (Serial.available() > 0)
    {
        selected_LED = Serial.read();
        switch (selected_LED)
        {
        case 'R':
        {
            Serial.println("Light's red LED up.");
            digitalWrite(red_LED, HIGH);
            digitalWrite(green_LED, LOW);
            break;
        }

        case 'G':
        {
            Serial.println("Light's green LED up.");
            digitalWrite(green_LED, HIGH);
            digitalWrite(red_LED, LOW);
            break;
        }
        }
    }
}