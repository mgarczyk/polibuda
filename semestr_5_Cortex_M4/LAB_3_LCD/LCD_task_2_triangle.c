

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

    //Draw circle and triagle inside.
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
	int CentralPointVertically = GrContextDpyWidthGet(&sContext) / 2;
	int CentralPointHorizontally = GrContextDpyHeightGet(&sContext) / 2;
	int CircleRadius = 50;
	GrContextForegroundSet(&sContext, ClrBlue);
	GrCircleFill(&sContext, CentralPointVertically, CentralPointHorizontally, CircleRadius); //draw centred circle
	GrContextForegroundSet(&sContext, ClrYellow);
	for(float i=0; i<CircleRadius*2; i++){
		GrLineDraw(&sContext, CentralPointVertically, CentralPointHorizontally - CircleRadius, CentralPointVertically - CircleRadius + i, CentralPointHorizontally - CircleRadius + 1.5 * CircleRadius);
	}
	GrContextFontSet(&sContext, g_psFontCm14);
	GrContextForegroundSet(&sContext, ClrBlue);
	GrStringDraw(&sContext, "Kolor niebieski: koło", -1, 50, 200, 0);
    GrContextForegroundSet(&sContext, ClrYellow);
    GrStringDraw(&sContext, "Kolor żółty: trójkąt", -1, 200, 200, 0);
    GrFlush(&sContext); //Flush any cached drawing operations.
	

	
	



	//
	// Drawings
	//



  

}

