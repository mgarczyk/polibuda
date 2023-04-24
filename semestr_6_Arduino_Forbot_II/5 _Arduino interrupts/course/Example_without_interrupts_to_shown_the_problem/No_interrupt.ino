/*
The main loop of the program is short, and its only task is to check the state of the reed switch. 
There is no way for such a program not to catch the opening of the reed switch. 
However, a simple change in the program is enough to make the situation look completely different....
Let's expand the program, so that the loop circuit takes a relatively long time. 
We will achieve such an effect by adding a control - let the flashing of the diode built into the Arduino (pin 13) signal the work of the "alarm".

Let's see how the program will perform now! The alarm no longer works well. 
The whole thing reacts to sensor changes differently - sometimes immediately, sometimes only after 4 seconds, and sometimes not at all.
With an alarm system, something like this can't happen. 
While the activation of the alarm after a few seconds we are able to accept, 
the complete lack of response disqualifies such a solution. 
If a thief entered quickly through a window, our system would not even have time to notice it.

We cannot afford that a critical task (noting an alarm) is not completed.


*/

#define LED_R 10
#define LED_G 11
#define LED_B 12
#define LED_SYG 9
#define REED_SWITCH 0
 
void setup() {
  pinMode(LED_R, OUTPUT); //LEDs as output.
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_SYG, OUTPUT);
  pinMode(REED_SWITCH, INPUT_PULLUP); //Reed switch as input
  digitalWrite(LED_R, LOW); 
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_SYG , LOW);
}
 
void LED_alarm(){
  if (digitalRead(REED_SWITCH) == LOW) { //If the sensor shorted
    digitalWrite(LED_R, LOW); //State OK - green LED
    digitalWrite(LED_G, HIGH);
  } else {
    digitalWrite(LED_R, HIGH); //ALARM status - red LED  
    digitalWrite(LED_G, LOW);
  }
}

void blink_LED(int LED){
  digitalWrite(LED, HIGH); //LED blinking
  delay(2000);
  digitalWrite(LED, LOW);
  delay(2000);  
}

void loop() {
  LED_alarm();
  blink_LED(LED_SYG);
}

