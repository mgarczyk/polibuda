/*
As I mentioned earlier, the function responsible for handling the interrupt cannot return any value through the standard return mechanism. 
You can, of course, "get around" this by using global variables, for example. 
However, you need to remember that all global variables used inside the interrupt function should be declared with a special prefix - volatile.

The use of the prefix volatile will make the compiler not try to optimize this variable, 
thus avoiding many difficult to detect errors. If optimization was enabled, 
the program could "not notice" that the value of the variable was changed in an interrupt.

Let's try to create a program that will count how many times the PIR sensor has detected motion,
 and depend on this the color of the RGB LED. To do this, 
 simply increase the value of the variable that will count the number of rising edges in the corresponding interrupt.

*/

#define LED_R 10
#define LED_G 11
#define LED_B 12
#define PIR 2
 
volatile int counter = 0;
 
void setup() {
  pinMode(LED_R, OUTPUT); 
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(PIR, INPUT); //PIR as output
    
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, LOW);
 
  attachInterrupt(digitalPinToInterrupt(PIR), motion, RISING); 
}
 
void loop() {
  if (counter < 3) { // Acceptable - green color
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);    
  } else if (counter < 6) { // It's starting to get threatening - blue color
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);   
  } else {  //Alarm - motion detected more than 6 times - red color
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);       
  }
}
 
void motion() { 
  counter++; //Another motion
}