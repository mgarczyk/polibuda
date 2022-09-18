/*
It's time to use a new element and build something that will have practical applications. 
In this exercise, we will use a photoresistor, an element whose resistance changes under the influence of incident light (the more you illuminate it, the lower the resistance).
*/

#define LED 8
int read_value = 0;

void setup(){
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

}

void loop(){
    read_value = analogRead(A0);
    Serial.println(read_value);
    if (read_value < 70){ // manually set the value for which the light will turn on
        digitalWrite(LED, HIGH);
    }else{
        digitalWrite(LED, LOW);
    }
    delay(50);
}