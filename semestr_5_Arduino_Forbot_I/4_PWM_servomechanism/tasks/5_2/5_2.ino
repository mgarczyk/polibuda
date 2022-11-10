#define LED 3
int change = 5;
int duty_cycle = 0;
int lighten_up = true;

void setup() {
  pinMode(LED, OUTPUT);
}
 
void lighten_LED(){
     if (duty_cycle < 255 && lighten_up == true)
        duty_cycle += change;
    else
        lighten_up = false;
}

void dim_LED(){
     if (duty_cycle > 0 && lighten_up == false)
        duty_cycle -= change;
    else
        lighten_up = true;
}


void loop() {
    analogWrite(LED, duty_cycle);
    lighten_LED();
    dim_LED();
    delay(50);
}