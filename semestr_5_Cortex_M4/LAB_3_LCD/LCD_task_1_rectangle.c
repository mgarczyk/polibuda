

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

    //Function that draws rectangles 
	void draw_rectangle(int i16XMin, int i16YMin, int i16XMax, int i16YMax, int Clr, tContext sContext, tRectangle sRect){
        sRect.i16XMin = i16XMin;
	    sRect.i16YMin = i16YMin;
	    sRect.i16XMax = i16XMax;
	    sRect.i16YMax = i16YMax;
        GrContextForegroundSet(&sContext, Clr);
	    GrRectFill(&sContext, &sRect);

    }

    void setup_LCD(){

    }
    
	int main(void)
	{
    //SETUP LCD
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
	// Draw some rectangles
	//
    draw_rectangle(10, 10, 100, 100, ClrRed, sContext, sRect);
    draw_rectangle(120, 10, 220, 100, ClrGreen, sContext, sRect);
    draw_rectangle(10, 120, 100, 220, ClrBlue, sContext, sRect);
    draw_rectangle(120, 120, 220, 220, ClrYellow, sContext, sRect);
    //Set information about text (color and font_type)
	GrContextFontSet(&sContext, g_psFontCm14);
    //Draw text
    GrContextForegroundSet(&sContext, ClrWhite);
    GrStringDraw(&sContext, "Witaj", -1, 40, 50, 0);
    GrContextForegroundSet(&sContext, ClrBlack);
    GrStringDraw(&sContext, "w", -1, 160, 50, 0);
    GrContextForegroundSet(&sContext, ClrWhite);
    GrStringDraw(&sContext, "wielkim", -1, 30, 160, 0);
    GrContextForegroundSet(&sContext, ClrGreen);
    GrStringDraw(&sContext, "świecie", -1, 150, 160, 0);
    GrFlush(&sContext); //Flush any cached drawing operations.

}

