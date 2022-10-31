#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "grlib/grlib.h"
#include "utils/uartstdio.h"
#include "driverlib/gpio.h"
#include "drivers/ili9341_240x320x262K.h"


int main(void)

{
    tContext sContext;
    tRectangle bRect;
    ROM_FPULazyStackingEnable();
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_8MHZ | SYSCTL_OSC_MAIN);
    ILI9341_240x320x262K_Init();
    GrContextInit(&sContext, &g_sILI9341_240x320x262K);
    
    //RECT
    GrFlush(&sContext);
    bRect.i16XMin = 85;
    bRect.i16YMin = 200;
    bRect.i16XMax = 115;
    bRect.i16YMax = 250;
    GrContextForegroundSet(&sContext, ClrBrown);
    GrRectFill(&sContext, &bRect);
    //TRIANGLES
    GrContextForegroundSet(&sContext, ClrGreen);
    int i;
    for(i=0; i<100; i++){
        GrLineDraw(&sContext, 100, 50, 50+i, 100);
    }

    for(i=0; i<100; i++){
           GrLineDraw(&sContext, 100, 100, 50+i, 150);
    }

    for(i=0; i<100; i++){
               GrLineDraw(&sContext, 100, 150, 50+i, 200);
    }
    //CIRCLES
    i = 0;
    while (true){
        i+=1;
        if (i%4 == 0){
            GrContextForegroundSet(&sContext, ClrBlue);
        }else if(i%4 == 1){
            GrContextForegroundSet(&sContext, ClrRed);
        }else if(i%4 == 2){
            GrContextForegroundSet(&sContext, ClrOrange);
        }else{
            GrContextForegroundSet(&sContext, ClrYellow);
        }
        GrCircleFill(&sContext, 100, 75, 10);
        GrCircleFill(&sContext, 100, 130, 10);
        GrCircleFill(&sContext, 100, 180, 10);
        ROM_SysCtlDelay(ROM_SysCtlClockGet() / 2);
    }







}
