/*
It's time for a more elaborate design. 
This time, depending on the position in which the potentiometer slider is placed, we will turn on the corresponding one of the LEDs. 
*/
#define LED_RED_DOWN 8 
#define LED_RED_UP 9 
#define LED_YELLOW 10 
#define LED_GREEN_DOWN 11
#define LED_GREEN_UP 12 
int read_value = 0;

void setup() {
    Serial.begin(9600); 
    pinMode(LED_RED_DOWN, OUTPUT);   
    pinMode(LED_RED_UP, OUTPUT);   
    pinMode(LED_YELLOW, OUTPUT);   
    pinMode(LED_GREEN_DOWN, OUTPUT);   
    pinMode(LED_GREEN_UP, OUTPUT);   
}

int read_value_from_potentometer(int read_value){
    read_value = analogRead(A0);
    /* From documentation map() - Re-maps a number from one range to another. 
    That is, a value of fromLow would get mapped to toLow, a value of fromHigh to toHigh, values in-between to values in-between, etc.
    Parameters:
    value: the number to map.
    fromLow: the lower bound of the value’s current range.
    fromHigh: the upper bound of the value’s current range.
    toLow: the lower bound of the value’s target range.
    toHigh: the upper bound of the value’s target range.
    */
    read_value = map(read_value, 0, 1010, 1, 5); //At one of the extreme positions of the potentiometer, you may notice that the diodes behave strangely. 
    //Then it is best by trial and error to change the maximum value of the ADC, which is set in the map() function.
    Serial.println(read_value);
    return read_value;
    
}


void light_up_LED(int read_value){
    switch (read_value){
        case 1 : 
                digitalWrite(LED_RED_DOWN, HIGH);
                break;
        case 2 :
                 digitalWrite(LED_RED_UP, HIGH);
                 break;
        case 3 :
                 digitalWrite(LED_YELLOW, HIGH);
                 break;
        case 4 :
                 digitalWrite(LED_GREEN_DOWN, HIGH);
                 break;
        case 5 :
                 digitalWrite(LED_GREEN_UP, HIGH);
                 break;
        default :
                break;
                
    }
}


void loop() {
    digitalWrite(LED_RED_DOWN, LOW);
    digitalWrite(LED_RED_UP, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN_DOWN, LOW);
    digitalWrite(LED_GREEN_UP, LOW);
    read_value = read_value_from_potentometer(read_value);
    light_up_LED(read_value);
    delay(50);
 
}