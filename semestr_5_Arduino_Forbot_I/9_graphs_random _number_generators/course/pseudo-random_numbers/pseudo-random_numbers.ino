/*
Sometimes we expect a program to work in an "unpredictable" way. 
A practical example? 
A robot that rotates at a random angle when it detects an obstacle, or a simple game in which the computer performs its movement with an unpredictable delay. 
In the previous example, I used just such values to demonstrate drawing graphs simultaneously for different data.

Responsible for returning a random value is the random(); function, which can take two arguments. 
With them we shape the range from which the numbers are drawn. 
In practice, we most often use the function in one of two ways. With specifying only the upper range:

random(500); // Random number from the range 0-499

Then the returned value will be a number in the range from 0 to a number one smaller than the one entered in parentheses. We can also affect the lower limit of the range.  To do this, just add a second argument:

random(100, 500); //a random number in the range 100-499

Remember!

The maximum number drawn will always be 1 less than the upper range we specified!


To improve the performance of the random algorithm, 
it would be best to start with a different value as the first, initial one before each start.

This number, on the basis of which subsequent numbers are generated, 
is called the seed/seed, in English it is referred to as random seed. 
You can find more on this subject on Wikipedia (entry: pseudorandom number generator). 
For us, the most important thing is that in the Arduino language there is also such a concept - we have an influence on this seed. A function is used for this:

randomSeed(initial_value);

In its argument, marked here as value_beginning, you should specify every time.... a random value. 
But I messed up, didn't I? 
To draw numbers, we need a random value. Do you have any idea how to get it? 
If not, take a peek at this lesson on the ADC in Arduino.

What happens when we don't connect any signal to the read input? 
Then we collect "garbage" from the environment, which is.... precisely random. 
Until now, this has been a problem for us. However, here we will use these values for a good purpose.

In order to make our Arduino use "more random" numbers, we can do so at first:

randomSeed(analogRead(A0));

This way, every time the program starts, we will measure the random voltage prevailing at the A0 input. Further this value will be fed as a seed to the pseudo-random number generator.
*/

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
}
 
void loop() {
  Serial.println(random(300));
  delay(1000);
}