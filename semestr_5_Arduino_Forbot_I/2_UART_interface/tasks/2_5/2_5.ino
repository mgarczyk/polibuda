/*
Write a program that when you send the color of a diode will change its state to the opposite. 
If the diode is on, it will be turned off, and vice versa. 
Hint: remember to use additional bool variables that will remember the current state of the LEDs.
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

void change_red_LED_state(bool red_LED_state){
    if (red_LED_state == true){
        digitalWrite(red_LED, LOW);
    }else{
        digitalWrite(red_LED, HIGH);
    }
}

void change_green_LED_state(bool green_LED_state){
    if (green_LED_state == true){
        digitalWrite(green_LED, LOW);
    }else{
        digitalWrite(green_LED, HIGH);
    }
}

void choose_LED(String selected_LED, bool red_LED_state, bool green_LED_state){
     if (Serial.available() > 0){
        selected_LED = Serial.readStringUntil('\n');
        if (selected_LED == "red" or selected_LED == "Red"){
            change_red_LED_state(red_LED_state);
        }else if(selected_LED == "green" or selected_LED == "Green"){
            change_green_LED_state(green_LED_state);
        }else{
            Serial.println("Error, wrong command.");
        }
    }
}

void loop(){
    bool red_LED_state = digitalRead(red_LED);
    bool green_LED_state = digitalRead(green_LED);
    choose_LED(selected_LED, red_LED_state, green_LED_state);
}
 