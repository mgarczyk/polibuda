/*
It's time for the first simple program. This time we want to test the glowing of each color separately, 
and at the end combine all the colors.
*/

#define red 3
#define green 5
#define blue 6
 
void setup() {
  //set up pins
  pinMode(red, OUTPUT); 
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void light_up_red(){      
  digitalWrite(red, HIGH);  
  digitalWrite(blue, LOW);   
  digitalWrite(green, LOW);  
}

void light_up_green(){      
  digitalWrite(red, LOW);  
  digitalWrite(blue, HIGH);   
  digitalWrite(green, LOW);  
}


void light_up_blue(){      
  digitalWrite(red, LOW);  
  digitalWrite(blue, LOW);   
  digitalWrite(green, HIGH);  
}

void turn_off(){
  digitalWrite(red, LOW);  
  digitalWrite(blue, LOW);   
  digitalWrite(green, LOW); 
}
 
void loop() {
  light_up_red();
  delay(2000);
  light_up_green();
  delay(2000);
  light_up_blue();
  delay(2000);
  turn_off();
  delay(2000);
  // We light each one in turn, without extinguishing the previous ones
  digitalWrite(red, HIGH); 
  delay(2000);          
  digitalWrite(green, HIGH);
  delay(2000);          
  digitalWrite(blue, HIGH);
  delay(2000);  
  turn_off();
  delay(2000);
}