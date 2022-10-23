/*
main.c
*/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#define GPIO_PINS_ALL GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
//NWD
int count_gcd(int a, int b)
{
    int temp;
    while (b != 0)
    {
        temp = a % b;

        a = b;
        b = temp;
    }
    return a;
}


int main(void)
{
//
// Set the clocking to run directly from the crystal.
//
ROM_SysCtlClockSet (SYSCTL_SYSDIV_20 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
//
// Enable GPIOA, GPIOJ, GPIOC, GPIOA, GPIO G
//
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOA); //display H_counter
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOB); //display gcd(H,J)
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOE); //display J_counter
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOF); //display lcm(H, J)
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOG); //display diffrence between H and J as abs
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOH);
SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOJ);


//
// Set all GPIOA and GPIOE pins as outputs
//
GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PINS_ALL);
GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PINS_ALL);
GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PINS_ALL);
GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PINS_ALL);
GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, GPIO_PINS_ALL);

//
// Set all GPIOJ AND GPIOH pins (6, 7) as inputs
//
GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_7);
GPIOPinTypeGPIOInput(GPIO_PORTH_BASE, GPIO_PIN_7);


uint8_t port_H_counter = 0;
uint8_t port_J_counter = 0;


for (;;)
{
//
// Check button press and write data to port
//
if (GPIOPinRead(GPIO_PORTH_BASE,GPIO_PIN_7) == GPIO_PIN_7){
    port_H_counter++;
}else if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_7) == GPIO_PIN_7){
    port_J_counter++;
}

uint8_t diffrent_H_J_abs = abs(port_H_counter - port_J_counter); //count difference as abs

if (port_H_counter >= port_J_counter){
    GPIOPinWrite (GPIO_PORTG_BASE, 255, diffrent_H_J_abs);
}else{
    GPIOPinWrite (GPIO_PORTG_BASE, 255, diffrent_H_J_abs+128);
}

uint8_t GCD_H_J = count_gcd(port_H_counter, port_J_counter);
uint8_t LCM_H_J = (port_H_counter *  port_J_counter) / GCD_H_J;



GPIOPinWrite (GPIO_PORTA_BASE, 255, port_H_counter);
GPIOPinWrite (GPIO_PORTB_BASE, 255, GCD_H_J);
GPIOPinWrite (GPIO_PORTE_BASE, 255, port_J_counter);
GPIOPinWrite (GPIO_PORTF_BASE, 255, LCM_H_J);

;
SysCtlDelay(SysCtlClockGet() / 10);
}

return 0;
}
