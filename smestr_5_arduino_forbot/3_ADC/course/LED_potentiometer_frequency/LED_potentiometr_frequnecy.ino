/*
Here's the fastest way to build a device that flashes an LED at a frequency controlled by a potentiometer. 
*/

#define LED 2
float read_value = 0;

void setup(){
    Serial.begin(9600);
    digitalWrite(LED, LOW);

}

void loop(){
    digitalWrite(LED, HIGH);
    read_value = analogRead(A0);
    Serial.println(read_value);
    delay(read_value);
    digitalWrite(LED, LOW);
    delay(read_value);
}