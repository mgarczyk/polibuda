/*
As was discussed in earlier parts of the course, it is also possible to declare a variable that will store a non-integer number, such as: 3.141592. 
So far we have not dealt with such examples, because it is good practice to avoid numbers with fractional parts on microcontrollers.
*/

void setup() { 
  Serial.begin(9600); 
  int number = 1000;
  Serial.println(number);       
  Serial.println(number, DEC);  
  Serial.println(number, OCT);  
  Serial.println(number, BIN);
  Serial.println(number, HEX);
  float PI_number = 3.1415; 
  Serial.println(PI_number, 4); // 4 decimal places
  Serial.println(PI_number, 0); //0 decimal places
  Serial.println(PI); //Pi constant in Arduino

} 
 
void loop() { 
}

/*
Why did this command result in the display of the value 3.14? 
We didn't even declare such a variable anywhere. 
Well, the value of the number Pi is so often used that in many languages you can find ready-made constants that are equally approximations of the number Pi. 
In the case is PI, which will be converted to the corresponding value anywhere in the program.

However, let's go back by memory to the maximum precision that microcontrollers offer us, 
it turns out that the constant PI has the properties of a float variable, that is, it only accepts 7 digits! 
Any more is wrong, because the most accurate notation of non-integer values in the binary system does not allow us to obtain the corresponding "true Pi".


*/