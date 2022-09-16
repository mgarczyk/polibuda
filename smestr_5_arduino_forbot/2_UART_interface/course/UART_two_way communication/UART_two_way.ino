/*
The task of the first program will be to "listen" for our name. 
When we send it, the Arduino should greet us with the message "Hello Name!", where, of course, the previously sent name will be inserted.

*/

String recived_data = "";

void setup(){
    Serial.begin(9600); //set the baud of transmission
    Serial.println("Hello World");
}

void loop(){
    if (Serial.available() > 0){ // Get the number of bytes (characters) available for reading from the serial port. This is data that’s already arrived and stored in the serial receive buffer (which holds 64 bytes).
        recived_data = Serial.readStringUntil('\n');
        Serial.println("Welcome " + recived_data );
    }
}