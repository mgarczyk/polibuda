/*
Connecting multiple (traditional) RGB LEDs
*/

//First one
#define red 3
#define green 5
#define blue 6
 
//Second one
#define red2 9
#define green2 10
#define blue2 11
 
void setup() {
  pinMode(red, OUTPUT); 
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(blue2, OUTPUT);
}

//LED flashing, using different colors
void loop() {
  digitalWrite(red, HIGH); 
  digitalWrite(green2, HIGH);   
  delay(1000);
  digitalWrite(red, LOW);
  digitalWrite(green2, LOW);
  digitalWrite(blue, HIGH);
  digitalWrite(red2, HIGH);      
  delay(1000);
  digitalWrite(blue, LOW);
  digitalWrite(red2, LOW);     
}