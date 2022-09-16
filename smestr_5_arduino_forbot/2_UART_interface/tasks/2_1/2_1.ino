/*
    Check what happens when you select speeds in the terminal window that are different from those set in the Arduino. 
    When do errors appear? How do they manifest themselves? 
    As you will see for yourself, the errors are quite characteristic, it is worth remembering.
*/

void setup(){
    Serial.begin(9600); //set the baud of transmission
    Serial.println("Hello World");
}

void loop(){
    delay(5000);
    Serial.println("5 sec");
}