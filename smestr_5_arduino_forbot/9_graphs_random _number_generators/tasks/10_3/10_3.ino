/*
Write a program that works like an electronic dice. 
Connect a button to the Arduino. 
Each time you press it, it should send a drawn value to the computer (via the UART) - from 1 to 6, of course.
*/

#define SWITCH 2

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(10));
  pinMode(SWITCH, INPUT_PULLUP);
}
 
void loop() {

  if (digitalRead(SWITCH) == LOW){
    Serial.println(random(1, 6));
    delay(1000);
  }
  
  
}