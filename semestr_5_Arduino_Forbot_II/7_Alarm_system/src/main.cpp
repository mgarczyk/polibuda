/*
Our alarm system will consist of a numeric keypad, a sounder, a beacon, a motion sensor (PIR) and a door-opening sensor (reed switch).

Of course, the whole thing can work in many different ways. I decided that my alarm will work as follows: when the power is turned on, we enter standby mode. 
The alarm does nothing but wait for it to be armed. When you press the A key (like Alarm), the arming procedure takes place.

After a few seconds (time to leave the room), the alarm starts working - from now on our room is guarded. 
The moment we detect movement in the room, the alarm begins to immediately signal the threat.

Does the alarm have time to notice a fast thief?

If we detect the opening of the door, we give the user a few seconds to disarm the alarm, which involves entering a four-digit code. 
If the pin code is wrong or not entered, the alarm will also be triggered.

*/

#include <Keypad.h> 
#include <Adafruit_NeoPixel.h> 
#define BUZZER 11
#define CONCRATRON 10
#define PIR 12

const byte ROWS = 4; 
const byte COLS = 4; 
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {6, 7, 8, 9}; 
char keys[ROWS][COLS] = { //keymap map
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); //keypad init
Adafruit_NeoPixel LED_bar = Adafruit_NeoPixel(8, A0, NEO_GRB + NEO_KHZ800); //LED bar init
volatile int alarm_state = 1;
 
void alarm_siren(){
  tone(BUZZER, 4300); 
  delay(150);  
}


void alarming(){
  for (int i=0; i<8; i++){
     LED_bar.setPixelColor(i, LED_bar.Color(15, 0, 0));
     LED_bar.show();
  }
  delay(100);
  for (int i=0; i<8; i++){
     LED_bar.setPixelColor(i, LED_bar.Color(0, 0, 15));
     LED_bar.show();
  }
  delay(100);
  alarm_siren();
}

void armed_decision(){
   if (digitalRead(PIR) == HIGH) {
        alarm_state = 4; 
      }else if(digitalRead(CONCRATRON) == 1){
        alarm_state = 4;
      }
}

void armed_blinking(){
    LED_bar.setPixelColor(0, LED_bar.Color(15, 0, 0)); 
    LED_bar.show();
    delay(1000);
    LED_bar.setPixelColor(0, LED_bar.Color(0, 0, 0)); 
    LED_bar.show();
    delay(1000);
}


void arming_confirmation(char pressed_key){
  LED_bar.setPixelColor(0, LED_bar.Color(255,165,0));
  while(pressed_key == 'A' or pressed_key == 0){
    LED_bar.show();
    pressed_key = keypad.getKey();
    if (pressed_key == 'B') alarm_state = 2;
    else alarm_state = 1;
  }
}

void arming_the_alarm(char pressed_key){
    pressed_key = keypad.getKey();
    if (pressed_key == 'A'){ 
      arming_confirmation(pressed_key);
    }
}

void standby(char pressed_key){
    LED_bar.setPixelColor(0, LED_bar.Color(0, 15, 0));
    LED_bar.show();
    arming_the_alarm(pressed_key);
}

void PIR_interrupt(){
  if (alarm_state == 2 or alarm_state == 3)
      alarm_state = 4;
}

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(CONCRATRON, INPUT_PULLUP);
  pinMode(PIR, INPUT_PULLUP);
  LED_bar.begin();
  LED_bar.show();
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(PIR), PIR_interrupt, RISING);
}
 
void loop() {
  char pressed_key = 0;
  switch(alarm_state){ 
    case 1:
      standby(pressed_key);
    break;
    case 2:
      armed_blinking();
      armed_decision();
    break;
    case 3:
      
 
    break;
    
    case 4:
      alarming();
    break;
  }
}