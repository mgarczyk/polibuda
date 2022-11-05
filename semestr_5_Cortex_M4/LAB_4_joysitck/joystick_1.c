//*****************************************************************************
// hello.c - Simple hello world example.
//
// Maciej Kucia July 2013
//
// This is part of revision 1.0 of the EK-LM4F232 Firmware Package.
//*****************************************************************************
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

const unsigned char TI_logo[(16*2)+5] = {
IMAGE_FMT_1BPP_UNCOMP, 16,0, 16,0,
0x0f,0xff,0x0f,0xff,0x0f,0xf3,0x0f,0xfa,0x0f,0x8f,0x0f,0x89,0x81,0x99,0x81,0x19,0x03,0x09,0x07,0x89,0x07,0xdf,0x3f,0xee,0x7f,0xf0,0xff,0xf8,0xff,0xf9,0xff,0xfb}; 

int
main(void)
{
    tContext sContext;
    tRectangle sRect;
    //
    // Enable lazy stacking for interrupt handlers. This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    ROM_FPULazyStackingEnable();
    //
    // Set the clocking to run directly from the crystal.
    //
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    //
    // Initialize the display driver.
    //
    ILI9341_240x320x262K_Init();
    //
    // Initialize the graphics context.
    //
    GrContextInit(&sContext, &g_sILI9341_240x320x262K);
    //
    // Flush any cached drawing operations.
    //
    GrFlush(&sContext); 
    // We are finished. Hang around doing nothing.
  

    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOB);
    //
    // Set all GPIOB pins as inputs
    //
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PINS_ALL);
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PINS_ALL);
    GrContextFontSet(&sContext,g_psFontCm16b);
    //Flagi, blokują ciągłe naciskanie przycisku, żeby zarejstrować drugie kliknięcie należy puścić go i ponownie przycisnąć
    bool flaga1 = false; 
    bool flaga2 = false;
    bool flaga3 = false;
    bool flaga4 = false;
    int poziom = 0;
    int pion = 0;
    while(1){

        //pion 
        //pion = 0, stan początkowy wszytkie czerwone
        if(pion == 0)
        {
            GrContextForegroundSet(&sContext, ClrRed); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2, GrContextDpyHeightGet(&sContext) / 2-40, 8);
            GrContextForegroundSet(&sContext, ClrRed); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2, GrContextDpyHeightGet(&sContext) / 2-70, 8);
            GrContextForegroundSet(&sContext, ClrRed); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2, GrContextDpyHeightGet(&sContext) / 2+40, 8);
            GrContextForegroundSet(&sContext, ClrRed); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2, GrContextDpyHeightGet(&sContext) / 2+70, 8);
        }
        //Klikamy przyciski góra/dół zmienamy wartość zmiennej pion od -2 do 2
        if (GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_0) == GPIO_PIN_0  && flaga1 == false && pion < 2) 
        {
            pion+=1;
            flaga1 = true;
        }
        else if(GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_0) != GPIO_PIN_0)
        {
            flaga1 = false; 
        }

        if (GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_5) == GPIO_PIN_5  && flaga2 == false && pion > -2)
        {
            pion-=1;
            flaga2 = true;
        }
        else if(GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_5) != GPIO_PIN_5)
        {
            flaga2 = false; 
        }

        //W zależności od wartości zmiennej rysujemy odpowiednio kółka, dla wartości 0 następuje reset wspomniany wyżej.
        if(pion == 1)
        {
            GrContextForegroundSet(&sContext, ClrYellow); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2, GrContextDpyHeightGet(&sContext) / 2-40, 8);
            GrContextForegroundSet(&sContext, ClrRed); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2, GrContextDpyHeightGet(&sContext) / 2-70, 8);
        }

        if(pion >= 2)
        {
            GrContextForegroundSet(&sContext, ClrGreen); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2, GrContextDpyHeightGet(&sContext) / 2-70, 8);
        }

        if(pion == -1)
        {
            GrContextForegroundSet(&sContext, ClrYellow); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2, GrContextDpyHeightGet(&sContext) / 2+40, 8);
            GrContextForegroundSet(&sContext, ClrRed); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2, GrContextDpyHeightGet(&sContext) / 2+70, 8);
        }

        if(pion <= -2)
        {
            GrContextForegroundSet(&sContext, ClrGreen); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2, GrContextDpyHeightGet(&sContext) / 2+70, 8);
        }

        //Poziom, działa analogicznie jak pion tylko w poziomie, inne porty i zmienamy współrzędną x kółek, y zostawiając.
        if(poziom == 0)
        {
            //1 lewo
            GrContextForegroundSet(&sContext, ClrRed); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2-40, GrContextDpyHeightGet(&sContext) / 2, 8);
            //2 lewo
            GrContextForegroundSet(&sContext, ClrRed); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2-70, GrContextDpyHeightGet(&sContext) / 2, 8);
            //1 prawo
            GrContextForegroundSet(&sContext, ClrRed); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2+40, GrContextDpyHeightGet(&sContext) / 2, 8);
            //2 prawo
            GrContextForegroundSet(&sContext, ClrRed); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2+70, GrContextDpyHeightGet(&sContext) / 2, 8);
        }
        
        if (GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_4) == GPIO_PIN_4  && flaga3 == false && poziom < 2) 
        {
            poziom+=1;
            flaga3 = true;
        }
        else if(GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_4) != GPIO_PIN_4)
        {
            flaga3 = false; 
        }

        if (GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_7) == GPIO_PIN_7  && flaga4 == false && poziom > -2) //TODO zmień na K bo nie zadziałą
        {
            poziom-=1;
            flaga4 = true;
        }
        else if(GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_7) != GPIO_PIN_7)
        {
            flaga4 = false; 
        }

        if(poziom == 1)
        {
            GrContextForegroundSet(&sContext, ClrYellow); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2+40, GrContextDpyHeightGet(&sContext) / 2, 8);
            GrContextForegroundSet(&sContext, ClrRed); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2+70, GrContextDpyHeightGet(&sContext) / 2, 8);
        }

        if(poziom >= 2)
        {
            GrContextForegroundSet(&sContext, ClrGreen); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2+70, GrContextDpyHeightGet(&sContext) / 2, 8);
        }

        if(poziom == -1)
        {
            GrContextForegroundSet(&sContext, ClrYellow); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2-40, GrContextDpyHeightGet(&sContext) / 2, 8);
            GrContextForegroundSet(&sContext, ClrRed); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2-70, GrContextDpyHeightGet(&sContext) / 2, 8);
        }

        if(poziom <= -2)
        {
            GrContextForegroundSet(&sContext, ClrGreen); 
            GrCircleFill(&sContext, GrContextDpyWidthGet(&sContext) / 2-70, GrContextDpyHeightGet(&sContext) / 2, 8);
        }
    }

}

