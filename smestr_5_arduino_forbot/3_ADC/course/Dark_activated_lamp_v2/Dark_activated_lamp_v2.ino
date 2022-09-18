/*
This time the task is obvious. 
As before, we want to create a light that will be activated after dark. 
However, it should be much easier to adjust. Do you have any ideas on how to accomplish this?
*/

#define LED 8
#define photoresistor A0
#define potentometer A1
int read_value = 0;
int threshold = 0;

void setup(){
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);


}

void loop(){
    read_value = analogRead(A0);
    threshold = analogRead(A1);  // set the threshold
    Serial.println("Read value: ");
    Serial.println(read_value);
     Serial.println("Threshold: ");
    Serial.println(threshold);
    if (read_value < threshold){ // now we can use potentometer to set the threshold, below that the lamp light up
        digitalWrite(LED, HIGH);
    }else{
        digitalWrite(LED, LOW);
    }
    delay(1000); // set larger delay to see how much the read_value is diffrent than threshold
}