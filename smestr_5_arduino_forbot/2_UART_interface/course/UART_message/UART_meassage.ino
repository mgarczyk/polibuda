void setup(){
    Serial.begin(9600); //set the baud of transmission
    Serial.println("Hello World");
}

void loop(){
    delay(5000);
    Serial.println("5 sec");
}