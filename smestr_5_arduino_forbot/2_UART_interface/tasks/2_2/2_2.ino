/*
What happend when you move the counter variable intialization to main loop?
*/

void setup(){
    Serial.begin(9600); //set the baud of transmission
    Serial.println("Hello World");
}

void loop(){
    int counter = 0;
    counter += 1;
    delay(1000);
    Serial.println(counter);
}