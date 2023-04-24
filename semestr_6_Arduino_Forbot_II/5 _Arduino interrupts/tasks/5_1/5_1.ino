/*
Write a program that uses interrupts to trigger an alarm (illumination of the red LED) not immediately after the sensor detects motion, but only after the motion stops.
*/


#define LED_R 10
#define LED_G 11
#define LED_B 12
#define LED_SYG 13
#define PIR 2
 
void setup() {
  Serial.begin(9600);
  pinMode(LED_R, OUTPUT); //LED as output
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_SYG, OUTPUT);
  pinMode(PIR, INPUT); //PIR as output
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, LOW);
  
}
 
void move_detected() {
    digitalWrite(LED_G, LOW); 
    digitalWrite(LED_R, HIGH); //Move - Red LED
     
}

void no_move() {
    digitalWrite(LED_R, LOW); //No move - Green LED
    digitalWrite(LED_G, HIGH);
}



void loop() {
  Serial.println(String(digitalRead(2)));
  attachInterrupt(digitalPinToInterrupt(PIR), move_detected, FALLING); // Interrupt that react on falling slope. 
 
}
 

