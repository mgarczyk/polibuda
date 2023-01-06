//*****************************************************************************
//
// hello.c - Simple hello world example.
//
// Maciej Kucia July 2013
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 1.0 of the EK-LM4F232 Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inc/hw_memmap.h" //Memory mapping of the used device (maps all the pins ports etc. to specific numbers)
#include "driverlib/fpu.h" //Routines for manipulating the floating-point unit in the Cortex-M processor.
#include "driverlib/sysctl.h" //Driver for the system controller
#include "driverlib/rom.h"		//Macros to facilitate calling functions in the ROM
#include "driverlib/pin_map.h" //Mapping of peripherals to pins for all parts
#include "driverlib/uart.h" 	// Driver for the UART
#include "grlib/grlib.h"	//Prototypes for the low level primitives provided by the graphics library
#include "drivers/ili9341_240x320x262K.h" //Display driver for the MULTI-INNO TECHNOLOGY
										// MI0283QT-9 TFT display with an ILI9341 controller.
#include "utils/uartstdio.h"		//Prototypes for the UART console functions.
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"
#include "drivers/touch.h"



#define GPIO_PINS_ALL GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7



//*****************************************************************************
//
// Global system tick counter holds elapsed time since the application started
// expressed in 100ths of a second.
//
//*****************************************************************************
volatile uint32_t g_ui32SysTickCount;



int_fast32_t i32CenterX, i32CenterY;
//int i32CenterX_temp = 100;
//int i32CenterY_temp = 100;
tContext sContext;
tRectangle sRect;

//*****************************************************************************
//
// This is the interrupt handler for the SysTick interrupt.  It is used to
// update our local tick count which, in turn, is used to check for transmit
// timeouts.
//
//*****************************************************************************
void
SysTickIntHandler(void)
{
    g_ui32SysTickCount++;
}


//*****************************************************************************
//
//! Callback for calibration process
//!
//! \param X - x coordinate of point to check
//! \param Y - y coordinate of point to check
//! \param cX - x coordinate of circle center
//! \param cY - y coordinate of circle center
//! \param radius - circle radius
//!
//! \return boolean true if coordinates are within circle
//
//*****************************************************************************
inline bool IsInCircle(int32_t X,int32_t Y,int32_t cX,int32_t cY,int32_t radius)
{
	return ( (X-cX)*(X-cX) + (Y-cY)*(Y-cY) < (radius*radius) );
}
int color;
//color=0;
int size=3;
int c;
//c=0;
int s;
//s=0;
int colors[]={0x00000000,0x000000FF,0x00008000,0x00800080,0x00FFFF00};
//colors[0]=0x00000000;
//colors[1]=0x000000FF;
//colors[2]=0x00008000;
//colors[3]=0x00800080;
//colors[4]=0x00FFFF00;


//*****************************************************************************
//
//! Callback for calibration process
//!
//! \param ulMessage is type of event
//! \param lX is a x location of touch
//! \param lY is a y location of cross center
//!
//! \return None.
//
//*****************************************************************************

int32_t TouchCallback(uint32_t ulMessage, int32_t lX, int32_t lY)
{
	i32CenterX = lX;
	i32CenterY = lY;

//	char fullText[30];
//	GrContextForegroundSet(&sContext, ClrWhite);
//	sprintf(fullText,"Pressed %d %d",i32CenterX, i32CenterY);


//	GrStringDrawCentered(&sContext, fullText, -1, i32CenterX , i32CenterY, 0);
//		unsigned long color;
//		color=0;
//	  int size=3;
//	  int c;
//		c=0;
//		int s;
//		s=0;
//		int colors[5];
//		colors[0]=0x00000000;
//		colors[1]=0x000000FF;
//		colors[2]=0x00008000;
//		colors[3]=0x00800080;
////		colors[4]=0x00FFFF00;
//	c=GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_2);
//	    	if(c==4){
//	    		color++;
//	    		if(color>4){
//	    			color=0;
//	    		};
//	    GrContextForegroundSet(&sContext, colors[color]);
//	    GrRectFill(&sContext, &sRect);
//	    GrCircleFill(&sContext, 240, 10, size);
//	    	};
//	  s=GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_0);
//	    if(s==1){
//	    	if(size>0){
//	    		size--;}
//	    GrContextForegroundSet(&sContext, colors[color]);
//	    GrRectFill(&sContext, &sRect);
//	    GrCircleFill(&sContext, 240, 10, size);
//	    	}
//	    	s=GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_1);
//	  if(s==2){
//		  if(size<6){
//			  size++;}
//	   GrContextForegroundSet(&sContext, colors[color]);
//	   GrRectFill(&sContext, &sRect);
//	   GrCircleFill(&sContext, 240, 10, size);
//	  };
	GrContextForegroundSet(&sContext, colors[color]);
//	sprintf(fullText,"Pressed %d %d",lX, lY);
	if(i32CenterY-size>20){
	GrCircleFill(&sContext, lX, lY, size);
	};
//	i32CenterX = lX;
//	i32CenterY = lY;

//	GrStringDrawCentered(&sContext, fullText, -1, i32CenterX, i32CenterY, 0);
	return 0;

}



int
main(void)
{
	SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PINS_ALL);
    //
    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    ROM_FPULazyStackingEnable();

    //
    // Set the clocking to run directly from the crystal.
    //
//    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
//                       SYSCTL_OSC_MAIN);

    ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_8MHZ);

    //
    // Initialize the display driver.
    //
    ILI9341_240x320x262K_Init();

    //
    // Initialize the graphics context.
    //
    GrContextInit(&sContext, &g_sILI9341_240x320x262K);

    //
    // Initialize touchscreen driver
    //
    TouchScreenInit();
//    TouchScreenCalibrate(&sContext);
    TouchScreenCallbackSet(TouchCallback);
//	unsigned long color;
	color=0;
	size=3;
//  int c;
	c=0;
//	int s;
	s=0;
    GrContextFontSet(&sContext, g_psFontCm12);
	GrContextForegroundSet(&sContext, ClrBlack);
	GrLineDraw(&sContext,0,20,320,20);
	GrLineDraw(&sContext,160,0,160,20);
	sRect.i16XMin = 0;
	sRect.i16YMin = 0;
	sRect.i16XMax = 159;
	sRect.i16YMax = 19;
	GrContextForegroundSet(&sContext, ClrBlack);
	GrRectFill(&sContext, &sRect);
	GrCircleFill(&sContext, 240, 10, size);
//	int colors[5];
//	colors[0]=0x00000000;
//	colors[1]=0x000000FF;
//	colors[2]=0x00008000;
//	colors[3]=0x00800080;
//	colors[4]=0x00FFFF00;
    while(1)
    {
    	GrContextForegroundSet(&sContext, ClrBlack);
    	GrLineDraw(&sContext,0,20,320,20);
    	GrLineDraw(&sContext,160,0,160,20);
    	sRect.i16XMin = 0;
    	sRect.i16YMin = 0;
    	sRect.i16XMax = 159;
    	sRect.i16YMax = 19;
    	GrContextForegroundSet(&sContext, colors[color]);
//    	GrRectFill(&sContext, &sRect);
//    	sRect.i16XMin = 161;
//    	sRect.i16YMin = 0;
//    	sRect.i16XMax = 320;
//    	sRect.i16YMax = 19;
//    	GrContextForegroundSet(&sContext, ClrWhite);
//    	GrRectFill(&sContext, &sRect);
    	GrContextForegroundSet(&sContext, colors[color]);
    	GrCircleFill(&sContext, 240, 10, size);
    	c=GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_2);
    	if(c==4){
    		color++;
    		if(color>4){
    			color=0;
    		};
    		GrContextForegroundSet(&sContext, colors[color]);
    		GrRectFill(&sContext, &sRect);
    		GrCircleFill(&sContext, 240, 10, size);
    	};
    	s=GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_0);
    	if(s==1){
    		if(size>1){
    		size--;}
    	   	GrContextForegroundSet(&sContext, ClrWhite);
    		GrCircleDraw(&sContext, 240, 10, size+1);
    		GrContextForegroundSet(&sContext, colors[color]);
    		GrRectFill(&sContext, &sRect);
    		GrCircleFill(&sContext, 240, 10, size);
    	}
    	s=GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_1);
    	if(s==2){
    		if(size<6){
    		size++;}
    		GrContextForegroundSet(&sContext, colors[color]);
    		GrRectFill(&sContext, &sRect);
    		GrCircleFill(&sContext, 240, 10, size);
    	};
    	ROM_SysCtlDelay(ROM_SysCtlClockGet()/10);
    }

}
