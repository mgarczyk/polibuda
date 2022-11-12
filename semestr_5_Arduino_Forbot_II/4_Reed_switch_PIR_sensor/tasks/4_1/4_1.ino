/*
Use a buzzer without a generator (discussed in the previous section of the course) and write a program that will trigger an audible alarm immediately when the reed switch is swung.
Its re-contact (e.g., by closing the door) should not turn off the audible signal.
*/
#define reed_switch 0
#define LED_R 10
#define LED_G 11
#define LED_B 12
#define BUZZER A5

void setup()
{
    pinMode(LED_R, OUTPUT); // LED as output
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(reed_switch, INPUT_PULLUP); // reed witch as input
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
}

void LED_alarm()
{
    if (digitalRead(reed_switch) == LOW)  // If the sensor shorted
    {                            
        digitalWrite(LED_R, LOW); // State OK - green LED
        digitalWrite(LED_G, HIGH);
    }
    else
    {
        digitalWrite(LED_R, HIGH); // ALARM status - red LED
        digitalWrite(LED_G, LOW);
        tone(BUZZER, 4000);
    }
}

void loop()
{
    LED_alarm();
}