/*
Let's imagine a situation where the Arduino would be mounted in the role of a window opening beacon, to whose frame a special button/sensor is mounted. 
The whole mechanism works in such a way that when the window is closed the button is shorted to ground, otherwise the circuit is broken.
*/

# define red_LED 7
# define green_LED 8
# define window_sensor 9

void setup(){
    Serial.begin(9600); //set the baud of transmission
    Serial.println("Hello World");
    pinMode(red_LED, OUTPUT); 
    pinMode(green_LED, OUTPUT);
    pinMode(window_sensor, INPUT_PULLUP); 
    digitalWrite(red_LED, LOW);
    digitalWrite(green_LED, LOW);
}

void loop(){
    digitalWrite(red_LED, LOW);
    digitalWrite(green_LED, LOW);
    if(digitalRead(window_sensor) == LOW){
        digitalWrite(green_LED, HIGH);

    }else{
        digitalWrite(red_LED, HIGH);
        Serial.println("Warning, window is open.");
        while(digitalRead(window_sensor) == HIGH) { // Wait for closing the window.
            delay(25);  // Add some delay to avoid interference.
        };
   
    }
}