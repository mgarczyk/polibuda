/*
Write a program that reads the information of two photoresistors and a potentiometer. Then, when the button connected to the Arduino is pressed, send a line containing information once:

"Photoresistor 1: XXX, photoresistor: XXX, potentiometer: XXX, button pressed XX times".

Where instead of X, the correct values will appear, of course.
*/

#define POTENTOMETER A0
#define TACT_SWITCH 8
#define PHOTORESISTOR_DOWN A1
#define PHOTORESISTOR_UP A2
int press_counter = 0;

void setup() { 
  Serial.begin(9600); 
  pinMode(POTENTOMETER, INPUT);
  pinMode(PHOTORESISTOR_DOWN, INPUT);
  pinMode(PHOTORESISTOR_DOWN, INPUT);
  pinMode(TACT_SWITCH, INPUT_PULLUP);
} 
 
void loop() { 
    if (digitalRead(TACT_SWITCH) == LOW){
        press_counter += 1;
        int photoresistor_down_value = analogRead(PHOTORESISTOR_DOWN);
        int photoresistor_up_value = analogRead(PHOTORESISTOR_UP);
        int potentometer_value = analogRead(POTENTOMETER);
        Serial.print(String("Photoresistor_down: ") + photoresistor_down_value + String(", photoresistor_up: ") + photoresistor_up_value);
        Serial.println(String(", potentometer: ") + potentometer_value + String(", press counter: ") + press_counter);
        delay(500);
    }    
}
