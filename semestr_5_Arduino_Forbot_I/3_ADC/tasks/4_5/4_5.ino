/*
Use two photoresistors as separate voltage dividers.
Place them on the extreme sides of the contact plate.
Ideally, you should tilt them even minimally outward.
Display the values of both sensors in the terminal.
What happens when you wave your hand in front of the board (making a shadow) or shine a flashlight at it?
By analyzing the difference between the measurements from the two sensors,
are you able to write a program that determines which side of the plate the stronger light source is on?
Try to indicate the direction on 5 LEDs (more to the left, center, more to the right, etc.)!
*/

#define PHOTORESISTOR_DOWN A0
#define PHOTORESISTOR_UP A1
#define LED_RED_UP 12
#define LED_YELLOW_UP 11
#define LED_GREEN 10
#define LED_YELLOW_DOWN 9
#define LED_RED_DOWN 8
int downside_photoresitor_value = 0;
int upside_photoresistor_value = 0;
int upside_downside_diff = 0;

void turn_off_LEDs()
{
    digitalWrite(LED_RED_UP, LOW);
    digitalWrite(LED_YELLOW_UP, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW_DOWN, LOW);
    digitalWrite(LED_RED_DOWN, LOW);
}

void setup()
{
    Serial.begin(9600);
    pinMode(LED_RED_UP, OUTPUT);
    pinMode(LED_YELLOW_UP, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW_DOWN, OUTPUT);
    pinMode(LED_RED_DOWN, OUTPUT);
    turn_off_LEDs();
}

void read_value_of_photoresistors(int *upside_photoresistor_value, int *downside_photoresitor_value){
    *upside_photoresistor_value = analogRead(PHOTORESISTOR_UP);
    *downside_photoresitor_value = analogRead(PHOTORESISTOR_DOWN);
    Serial.println(String("Upside: ") + *upside_photoresistor_value);
    Serial.println(String("Downside: ") + *downside_photoresitor_value);
}

// Scale the value from 1 to 10
void scale_value_of_photoresistors(int *upside_photoresistor_value, int *downside_photoresitor_value){
    *upside_photoresistor_value = map(*upside_photoresistor_value, 0, 1023, 1, 10);
    *downside_photoresitor_value = map(*downside_photoresitor_value, 0, 1023, 1, 10);
    Serial.println(String("Upside: ") + *upside_photoresistor_value);
    Serial.println(String("Downside: ") + *downside_photoresitor_value);
}

int compute_the_diffrence(int upside_photoresistor_value, int downside_photoresistor_value){
    // Below variable is in range from -10 to 10 now, and with that knoweldage we could create conditions
    upside_downside_diff = upside_photoresistor_value - downside_photoresitor_value; 
    Serial.println(upside_downside_diff);
    return upside_downside_diff;

}

void select_LED(int upisde_down_diff){
    if (upside_downside_diff >= -10 && upside_downside_diff <= -7)
    {
        digitalWrite(LED_RED_DOWN, HIGH);
    }
    else if (upside_downside_diff >= -6 && upside_downside_diff <= -3)
    {
        digitalWrite(LED_YELLOW_DOWN, HIGH);
    }
    else if (upside_downside_diff >= -2 && upside_downside_diff <= 2)
    {
        digitalWrite(LED_GREEN, HIGH);
    }
    else if (upside_downside_diff >= 3 && upside_downside_diff <= 6)
    {
        digitalWrite(LED_YELLOW_UP, HIGH);
    }
    else if (upside_downside_diff >= 7 && upside_downside_diff <= 10)
    {
        digitalWrite(LED_RED_UP, HIGH);
    }else{
        Serial.println("Read error.");
    }
}

void loop()
{
    turn_off_LEDs();
    read_value_of_photoresistors(&upside_photoresistor_value, &downside_photoresitor_value);
    scale_value_of_photoresistors(&upside_photoresistor_value, &downside_photoresitor_value);
    upside_downside_diff = compute_the_diffrence(upside_photoresistor_value, downside_photoresitor_value);
    select_LED(upside_downside_diff);
    delay(100);
}

