/*
As mentioned, variables have their limitations. 
Change the declaration of the variable counter from int to byte, which can hold numbers in the range 0-255. 
What happens when this value is exceeded? Watch the displayed results carefully!
*/

byte counter = 0;

void setup(){
    Serial.begin(9600); //set the baud of transmission
    Serial.println("Hello World");
}

void loop(){
    counter += 1;
    delay(100);
    Serial.println(counter);
}