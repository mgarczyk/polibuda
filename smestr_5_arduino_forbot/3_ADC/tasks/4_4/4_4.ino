/*

Try writing a simple game.
After starting the program, turn the potentiometer to a random place and press a button.
Then the Arduino should display a message on the PC:

Enter a number:

If the number sent to the Arduino agrees with the ADC reading by +/- 50, the player wins.
Otherwise, the yellow LED turns on and the player has 2 more tries. When the wrong number is entered each time,
a red LED turns on on the contact board. On the other hand, in case of a win, a green one is turned on.

*/

#define LED_RED 8
#define LED_YELLOW 9
#define LED_GREEN 10
#define POTENTIOMETER A0
int potentiometer_value = 0;
int recived_data = 0;
int counter = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
}

int read_value_from_potentometer(int read_value)
{
    read_value = analogRead(POTENTIOMETER);
    return read_value;
}

void reset_game()
{
    Serial.println("RESET");
    potentiometer_value = 0;
    recived_data = 0;
    counter = 0;
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
}

void won_game()
{
    Serial.println("You won, congratulations!!!");
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    delay(10000);
    reset_game(); // after win we wait 10s, and reset the game state basiclly by reset those variables
}

void lose_game()
{
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    Serial.println("You lose.");
    delay(5000);
    reset_game(); // after win we wait 5s, and reset the game state basiclly by reset those variables
}

void try_again()
{
    Serial.println("Try again.");
    counter += 1;
    digitalWrite(LED_RED, HIGH);
    delay(3000);
    digitalWrite(LED_RED, LOW);
    if (counter >= 1 && counter <= 2)
        digitalWrite(LED_YELLOW, HIGH);
    else
    {
        lose_game();
    }
    
}

// Number should send number via serial port.

void loop()
{
    potentiometer_value = read_value_from_potentometer(potentiometer_value);
    if (Serial.available() > 0)
    {
        recived_data = (Serial.readStringUntil('\n')).toInt();
        if (recived_data >= 0 && recived_data <= 1023)
        {
            if (recived_data == potentiometer_value)
            {
                won_game();
            }
            else
            {
                try_again();
            }
        }
        else
        {
            Serial.println("Number should be in range from 0 to 1023. Try again.");
        }
    }
}
