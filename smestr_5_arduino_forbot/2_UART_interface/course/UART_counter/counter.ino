/*
Theory behind us - now it's time for practice. 
Let's start with something very simple. 
To begin with, let our program write out the value of the variable we are going to increment in each loop.
*/

int counter = 0;

void setup(){
    Serial.begin(9600); //set the baud of transmission
    Serial.println("Hello World");
}

void loop(){
    counter += 1;
    delay(1000);
    Serial.println(counter);
}