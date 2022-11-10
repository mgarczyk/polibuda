/*
Observe what happens, in one of the extreme positions of the potentiometer. 
What do you think is the cause of this?
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
    Serial.println(read_value); //If we set the potentometer to minimum, then the read_value = 0
    delay(read_value); //When read_value = 0, then the delay is 0 ms and the LED won't blink.
    digitalWrite(LED, LOW);
    delay(read_value);
}