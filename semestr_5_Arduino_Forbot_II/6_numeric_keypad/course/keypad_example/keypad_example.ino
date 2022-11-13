/*
The first use of the numeric keypad
To begin with, it's a good idea to write a test program that will check if a key is pressed. 
If it is, the corresponding character will be sent to the computer via the UART.
To begin, we connect the keyboard to the Arduino using pins 2 through 9 as shown in the figure below. 
The order of the pins is important so that we can read the pressed buttons correctly.

The keyboard can be plugged into a contact board (the buttons will then face down, however). 
So it is worth using wires and connecting it directly to the Arduino. 
To do this, you need to "create" 8 male-female wires.

KeyPad library

Of course, with Arduino we will find a ready-made library that will make it even easier for us to use such keypads. 
In this case, it will be a library called Keypad. It can be found directly in the library manager or on GitHub: https://github.com/Chris--A/Keypad
*/

#include <Keypad.h> //keypad library
 
const byte ROWS = 4;   //how many rows
const byte COLS = 4;  //how many columns
 
byte rowPins[ROWS] = {5, 4, 3, 2}; //rows pins
byte colPins[COLS] = {6, 7, 8, 9}; //colums pins
 
char keys_map[ROWS][COLS] = { //keys mapping
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
 
Keypad keyboard = Keypad(makeKeymap(keys_map), rowPins, colPins, ROWS, COLS ); //keypad initialization
 
void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char pressed_key  = keyboard.getKey();
  
  if (pressed_key){
    Serial.println(pressed_key);
  }
}