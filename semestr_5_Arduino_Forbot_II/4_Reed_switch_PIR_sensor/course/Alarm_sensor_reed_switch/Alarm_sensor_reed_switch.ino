/*
The first, very simple alarm sensor is the reed switch. It is used at doors and windows. 
It consists of two parts: a properly formed sheet metal (inside a glass tube) and a magnet attached to the door/window.

When the magnet is brought close to the tube, the inner plates make contact and current flows from one, to the other lead of the sensor. 
So, from the Arduino's point of view, the situation is analogous to using ordinary buttons.

It's time to check the sensor's behavior in practice. 
To do this, we connect a simple test circuit. 
A standard RGB LED will serve as an indicator of the alarm status. 
If the window/door is closed, the diode should glow green, otherwise red.
*/

#define reed_switch 0
#define LED_R 10
#define LED_G 11
#define LED_B 12

 
void setup() {
  pinMode(LED_R, OUTPUT); //LED as output
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(reed_switch, INPUT_PULLUP); //reed witch as input
  digitalWrite(LED_R, LOW); 
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
}
 
void loop() {
  if (digitalRead(reed_switch) == LOW) { //If the sensor shorted
    digitalWrite(LED_R, LOW); //State OK - green LED
    digitalWrite(LED_G, HIGH);
  } else {
    digitalWrite(LED_R, HIGH); //ALARM status - red LED  
    digitalWrite(LED_G, LOW);
  }
}