/*
For hobby projects, designers are most likely to go for a very inexpensive PIR sensor module with the designation HC-SR501.
It is it that we will now deal with. T
he most important information about this module:

    - permissible supply voltage: 5-20 V,
    - current consumption: from 40 uA in standby, up to 150 uA,
    - output signal: 0 / 3.3V,
    - adjustable range: 3-7 m,
    - viewing angle: 120º.

As you can see, we can power this sensor directly from the Arduino, because it works correctly already from 5 V, moreover,
it draws a relatively very small current, so it will not affect the operation of the rest of the circuit (as it did, for example, when using a servo).
It can also be used in battery-powered designs without a problem.

The HC-SR501 module will work practically right out of the box.
By default, the whole thing works in retriggering mode. This mode means that when motion is detected,
a high state will appear on the output and it will be maintained for a certain time (Tx),
and each time motion is detected again, the time (Tx) will count down again from zero.

In simpler terms: there will be a high state on the output as long as the sensor
will detect motion + the time set on the Tx potentiometer.

During operation in the mode, non-retriggering, the output will receive a high state only once, after that the sensor's output will go low -
regardless of the detection of further movements during.
*/

#define LED_R 10
#define LED_G 11
#define LED_B 12
#define PIR 2

void setup()
{
    pinMode(LED_R, OUTPUT); // LEDs as output
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(PIR, INPUT); // PIR as input
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
}

void LED_alarm()
{
    if (digitalRead(PIR) == LOW) // If motion is detected
    {                             
        digitalWrite(LED_R, LOW); // ALARM status - red LED
        digitalWrite(LED_G, HIGH);
    }
    else
    {
        digitalWrite(LED_R, HIGH); // OK status - green LED
        digitalWrite(LED_G, LOW);
    }
}
void loop()
{
   LED_alarm();
}