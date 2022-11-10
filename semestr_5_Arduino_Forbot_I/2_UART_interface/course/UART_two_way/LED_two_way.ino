/*
The task of our program, is to turn on the green or red LED for 1 second, when the appropriate command is sent to the Arduino.
*/

#define red_LED 7
#define green_LED 8
String selected_LED = "";

void setup(){
    Serial.begin(9600); //set the baud of transmission
    Serial.println("Hello World");
    pinMode(green_LED, OUTPUT);
    pinMode(red_LED, OUTPUT);
    digitalWrite(red_LED, LOW);
    digitalWrite(green_LED, LOW);
}

void loop(){
    if (Serial.available() > 0){
        selected_LED = Serial.readStringUntil('\n');
        if (selected_LED == "red" or selected_LED == "Red"){
             Serial.println("Light's red LED up.");
             digitalWrite(red_LED, HIGH);
             digitalWrite(green_LED, LOW);
        }else if(selected_LED == "green" or selected_LED == "Green"){
            Serial.println("Light's green LED up.");
            digitalWrite(green_LED, HIGH);
            digitalWrite(red_LED, LOW);
        }else{
            Serial.println("Error, wrong command.");
        }
    }
}