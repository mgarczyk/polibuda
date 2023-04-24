/*

What are external interrupts?
Interrupts, is a mechanism that allows, under the influence of an external signal,
to immediately interrupt the executed part of the program and go to a specific function.
For example, regardless of what the program is doing when the reed switch is opened, we need to note an alarm.
This is a task that we could call time-critical for the entire device.
Seemingly, a simple loop that checks the state of the input is enough. However, we can't always afford to let the program deal only with checking the sensor.
Sometimes we will need to communicate with the computer (UART) or control other parts of the system, all of which takes up valuable time, during which we could miss the signal from the alarm sensor.

Interruptions in everyday life:
To illustrate the problem, I will use a "real life" example.
You are expecting an important package so important that you specifically stay at home and wait for the courier.
As it happens in such situations, the intercom has just stopped working, and the courier does not have your number.
At the same time, spending the day at home, you would like to do something else - such as cooking soup.
The plan for today: we cook soup!

Version 1 (without interruptions).
Throughout the day, you have to regularly go to the window and check if maybe the courier has already arrived(?).
You cut one carrot, add it to the soup and go look out the window.
You cut another carrot and go to the window again.
Not only do you have to interrupt both tasks, but to make matters worse, the courier may arrive just as you are cutting the vegetables.
The courier doesn't have time, so he will leave after a while,
and you won't even notice that you've already missed his arrival!

Version 2 (with interruptions).
This time you have no intention of going to the window every now and then.
That's why you smile at your elderly neighbor, who looks out the window all day (everyone probably has one)
You ask her to knock on your wall the moment she notices the courier.
From then on, you devote yourself entirely to cutting carrots.
All day at ease, without going to the window.
Suddenly you hear knocking on the wall - for you this is a very important signal - "something" has appeared,
which should be done at this exact moment.
The courier has pulled up and is waiting, this task is time-critical.
Therefore, without hesitation, you interrupt the current task
(even being in the middle of slicing) and you go to pick up the package.
When you pick it up and return to the apartment you will be able to continue making soup where you left off.
Thanks to the help of your neighbor who interrupted your work, you were able to devote yourself to other tasks, and, importantly, there was no way you could miss the arrival of the courier.

Interruptions in the world of microcontrollers:

The above description, intentionally detached from programming, but note that:

    Cooking soup → regular program operation (e.g., signaling device status, communicating with the computer, controlling components).
    Arrival of a courier → time-critical task, e.g., detection of an alarm by a PIR sensor or pressing a button by the user.
    Anything that requires a "here and now" response.
    No one wants the device to notice a button press only after 5 sec.
    Neighbor → interrupt handling mechanism.
    Knocking on the wall → reporting an interrupt.
    Receiving a package → handling an interrupt.

With this, we have worked out the interrupt mechanism!
I hope that it is already understood in what situations it will be helpful and what benefits it brings. To be sure, the advantages of interrupts:
We have a "helper" , which takes care of watching the input (sensor) in the background.
This helper works in parallel with the microcontroller executing the program.
We don't have to "waste" time checking the sensor frequently.
The use of an interrupt guarantees that the event will be handled exactly when needed. Even if it will be necessary to interrupt the executing part of the program.

Interrupts in Arduino

At first, in the setup() function, you need to make an interrupt declaration. We will use the rather long attachInterrupt command, the syntax of which is as follows:
        attachInterrupt(digitalPinToInterrupt(PIN), FUNCTION, REACTION_TO);

The issue is quite complex, so I have discussed each argument in more detail as a separate subsection.

Interrupt pin - digitalPinToInterrupt(PIN)
The first argument of the function that declares an interrupt is to specify the pin to be used as an external interrupt.
Interrupts are a mechanism built into microcontrollers - it is not just a programming procedure.
As you can see on the Arduino UNO board, the interrupt labeled INT.1 occurs on pin #2, and INT.1 on pin #3.

Function called in an interrupt.
When the microcontroller receives information about an external interrupt it will abort the current task and execute the code that will be in the function we wrote.
It is its name that is the second argument of attachInterrupt().
This will be an ordinary function, the kind we wrote a lot of during the Level I Arduino course.
However, it cannot take any arguments or return any.
By now it is worth remembering that a good function called in an interrupt,
is one that takes a short time to execute!
No waiting, no difficult calculations, no conditions waiting for other signals, etc.
I will not write more on this subject now, because it will be much easier to understand it in practice.

When should the interrupt (REACTION_TO) be reported?
We already know which pin is to act as an external interrupt and what code is to execute.
As the last parameter of the attachInterrupt function,
we need to provide information about "what" the interrupt mechanism should react to.
We can choose:
LOW - calling the interrupt whenever there is a low state at the input.
CHANGE - calling when the value on the pin changes (from high to low and vice versa).
RISING - calling when there is a change of value from low to high state.
FALLING - calling when there is a change of value from high to low state.

It's time for the first program that will use the interrupt.
To begin with, we'll look at checking the state of the PIR sensor, since it's already connected to the pin that handles the interrupt.

At first glance, this code should not do anything, because there is no instruction in the main loop loop(). 
Just load the program to see otherwise. 
When a change in the logic state of the sensor output (from low to high) is detected, the red LED lights up.
We used a rising edge triggered interrupt (RISING), 
because we are interested in the situation when the sensor output changes state from low 0 V, to a high state of 3.3 V, i.e. rising.


This is interesting because nowhere "directly" programmatically do we check the state of the sensor! 
This is done for us by the hardware mechanism responsible for interrupts, which reacts to a change in the state of the sensor.
Note that when motion is detected, an interrupt is reported only once - when the sensor begins to see motion and the signal at its output changes from low to high.


Moreover, the operation of this mechanism will not be sensitive, to things placed in the main loop. 
For example, we can add there a flashing diode (connected to pin 13), 
which would normally cause delayed reactions to the signal from the sensor.

*/

#define LED_R 10
#define LED_G 11
#define LED_B 12
#define LED_SYG 13
#define PIR 2
 
void setup() {
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
  attachInterrupt(digitalPinToInterrupt(PIR), move_detected, RISING); // Interrupt that react on raising slope.
  attachInterrupt(digitalPinToInterrupt(PIR), no_move, FALLING); // Interrupt that react on falling slope.
 
}
 

