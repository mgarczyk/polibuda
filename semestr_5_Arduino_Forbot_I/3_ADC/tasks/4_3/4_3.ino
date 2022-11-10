/*
Develop the smart light program so that when the diode is turned on, it sends (once) to the PC information about what voltage appeared on the divider.
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
    if (read_value < threshold){ // now we can use potentometer to set the threshold, below that the lamp light up
        digitalWrite(LED, HIGH);

        Serial.println("Voltage on voltage divider: ");
        Serial.println(5 * read_value / 1023.0);
    }else{
        digitalWrite(LED, LOW);
    }
    delay(1000); // set larger delay to see how much the read_value is diffrent than threshold
}