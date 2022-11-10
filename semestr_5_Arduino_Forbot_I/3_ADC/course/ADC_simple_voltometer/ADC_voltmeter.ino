/*
Simple voltmeter from 0 up to 5 V
This task is easy and consists only in proper conversion of the read value. 
We know that the input voltage varies from 0-5V, and from the ADC we get 1024 values (we count from 0 to 1023). 
*/

float read_value = 0;

void setup(){
    Serial.begin(9600); 
}

void loop(){
    read_value =(5 * analogRead(A0)) / 10;
    Serial.println(read_value);
    delay(200);
}