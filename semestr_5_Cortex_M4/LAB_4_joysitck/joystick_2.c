
    #include <stdint.h>
    #include <stdbool.h>
    #include "inc/hw_memmap.h"
    #include "driverlib/fpu.h"
    #include "driverlib/sysctl.h"
    #include "driverlib/rom.h"
    #include "driverlib/pin_map.h"
    #include "driverlib/uart.h"
    #include "grlib/grlib.h"
    #include "drivers/ili9341_240x320x262K.h"
    #include "utils/uartstdio.h"
    #include "driverlib/gpio.h"
    #define GPIO_PINS_ALL GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7

    void draw_rectangle(int i16XMin, int i16YMin, int i16XMax, int i16YMax, int Clr, tContext sContext, tRectangle sRect){
        sRect.i16XMin = i16XMin;
        sRect.i16YMin = i16YMin;
        sRect.i16XMax = i16XMax;
        sRect.i16YMax = i16YMax;
        GrContextForegroundSet(&sContext, Clr);
        GrRectFill(&sContext, &sRect);

    }

    void moving_rectangle(int actual_x, int actual_y, int size, int Ckr,  tContext sContext, tRectangle sRect){
        draw_rectangle(actual_x, actual_y, actual_x+size, actual_y+size, ClrGreen, sContext, sRect);
        while(true){
            if (GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_0) == GPIO_PIN_0){
                draw_rectangle(actual_x, actual_y, actual_x + size, actual_y + size, ClrBlack, sContext, sRect);
                actual_y -=  size;
                draw_rectangle(actual_x, actual_y, actual_x + size, actual_y + size, ClrGreen, sContext, sRect);
            }
            else if(GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_5) == GPIO_PIN_5){
                draw_rectangle(actual_x, actual_y, actual_x + size, actual_y + size, ClrBlack, sContext, sRect);
                actual_y += size;
                draw_rectangle(actual_x, actual_y, actual_x + size, actual_y + size, ClrGreen, sContext, sRect);
            }
            else if(GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_7) == GPIO_PIN_7){  //TODO zmień na PORTK bo nie zadziała na płytce
                    draw_rectangle(actual_x, actual_y, actual_x + size, actual_y + size, ClrBlack, sContext, sRect);
                    actual_x-=size;
                    draw_rectangle(actual_x, actual_y, actual_x + size, actual_y + size, ClrGreen, sContext, sRect);
            }
            else if(GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_4) == GPIO_PIN_4){
                    draw_rectangle(actual_x, actual_y, actual_x + size, actual_y + size, ClrBlack, sContext, sRect);
                    actual_x += size;
                    draw_rectangle(actual_x, actual_y, actual_x + size, actual_y + size, ClrGreen, sContext, sRect);
            }
            ROM_SysCtlDelay(ROM_SysCtlClockGet()/2);     
        }

    }

    int main(void)
    {
    // Enable lazy stacking for interrupt handlers. This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    ROM_FPULazyStackingEnable();
    // Set the clocking to run directly from the crystal.
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    // Initialize the display driver.
    ILI9341_240x320x262K_Init();
    //Initialize the graphics context.
    tContext sContext;
    tRectangle sRect;
    GrContextInit(&sContext, &g_sILI9341_240x320x262K);
    //Enable ports
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOK);
    // Set all GPIOB pins as inputs
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PINS_ALL);
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PINS_ALL);
    moving_rectangle(100, 100, 20, ClrGreen, sContext, sRect);
   
}

