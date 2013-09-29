/*
 * main-old.c
 *
 *  Created on: Sep 27, 2013
 *      Author: bgouveia
 */




#include <inc/hw_types.h>
#include <inc/hw_timer.h>
#include <inc/hw_ints.h>
#include <inc/hw_memmap.h>
#include <inc/hw_gpio.h>
#include <inc/hw_pwm.h>
#include <driverlib/rom.h>
#include <driverlib/rom_map.h>
#include <driverlib/debug.h>
#include <driverlib/sysctl.h>
#include <driverlib/timer.h>
#include <driverlib/interrupt.h>
#include <driverlib/gpio.h>
#include <driverlib/pwm.h>
#include <driverlib/udma.h>
#include <stdint.h>
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"
#include "kakariko-map.h"

#define TILEWIDTH 16
#define TILEHEIGHT 16
#define TILEOFFSET TILEWIDTH*TILEHEIGHT

#define MAPWIDTH 16 //16*16 = 256 pixels
#define MAPHEIGHT 15 //16*15 = 240 pixels


volatile int vLine;
volatile int tileIndex;

#define VPixels 480
#define VBackPorchLines 35


//PWM Gen 0
//void VsyncHandler(){
//	HWREG(PWM_BASE + PWM_GEN_0 + PWM_O_X_ISC) = PWM_INT_CNT_AD; //PWMGenIntClear(PWM_BASE, PWM_GEN_0, PWM_INT_CNT_AD);
//	//PWMGenIntClear(PWM_BASE, PWM_GEN_0, PWM_INT_CNT_AD);
//	vLine = -2;
//}


//PWM Gen 1
void HsyncHandler(){

	HWREG(PWM_BASE +  PWM_GEN_1 + PWM_O_X_ISC) = PWM_INT_CNT_ZERO;  //PWMGenIntClear(PWM_BASE, PWM_GEN_1, PWM_INT_CNT_ZERO);
	//PWMGenIntClear(PWM_BASE, PWM_GEN_1, PWM_INT_CNT_ZERO);

	if (vLine <0){
		vLine++;
		return;
	}

	// if all lines done, do the front porch
	if (vLine >= VPixels){
		HWREG(PWM_BASE +  PWM_GEN_1  + PWM_O_X_INTEN) &= ~(PWM_INT_CNT_ZERO); //PWMGenIntTrigDisable(PWM_BASE, PWM_GEN_1, PWM_INT_CNT_AD);
		//PWMGenIntTrigDisable(PWM_BASE, PWM_GEN_1, PWM_INT_CNT_AD);
		return;
	}

	const uint8_t * tilesrowsadress[MAPWIDTH];

	int indexb=vLine>>1;  //divide 480 /2 to get 240 height resolution
	uint8_t * mapindex= &kakariko_kakarikovillage[(indexb/TILEHEIGHT)*MAPWIDTH]; //get first tile from current row
	int tilerowoffset = indexb%TILEHEIGHT; //get rowoffset in current tile

	for (unsigned int i = 0;i<MAPWIDTH;i+=2){
		int currenttilerow= (*mapindex*TILEOFFSET)+(tilerowoffset*TILEWIDTH);
		tilesrowsadress[i]=&kakariko[currenttilerow];
		mapindex++; //increment mapindex for next tile
		currenttilerow= (*mapindex*TILEOFFSET)+(tilerowoffset*TILEWIDTH);
		tilesrowsadress[i+1]=&kakariko[currenttilerow];
		mapindex++; //increment mapindex for next tile
	}





	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");
	asm volatile("nop");


	const uint8_t * currentbyte =  tilesrowsadress[0];

	//tile 0
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[1];
	asm volatile("nop");

	//tile 1
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[2];
	asm volatile("nop");

	//tile 2
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[3];
	asm volatile("nop");

	//tile 3
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[4];
	asm volatile("nop");

	//tile 4
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[5];
	asm volatile("nop");

	//tile 5
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[6];
	asm volatile("nop");

	//tile 6
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[7];
	asm volatile("nop");

	//tile 7
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[8];
	asm volatile("nop");

	//tile 8
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[9];
	asm volatile("nop");

	//tile 9
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[10];
	asm volatile("nop");

	//tile 10
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[11];
	asm volatile("nop");

	//tile 11
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[12];
	asm volatile("nop");

	//tile 12
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[13];
	asm volatile("nop");

	//tile 13
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[14];
	asm volatile("nop");

	//tile 14
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte =  tilesrowsadress[15];
	asm volatile("nop");

	//tile 15
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	currentbyte++;
	asm volatile("nop");asm volatile("nop");
	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = *currentbyte;
	asm volatile("nop");
	asm volatile("nop");


	HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = 0; // drop back to black

	// this line done
	vLine++;
}

//PWM Gen 2
void FrameHandler(){
	HWREG(PWM_BASE + PWM_GEN_2 + PWM_O_X_ISC) = PWM_INT_CNT_AD;    //PWMGenIntClear(PWM_BASE, PWM_GEN_2, PWM_INT_CNT_AD);
	//PWMGenIntClear(PWM_BASE, PWM_GEN_2, PWM_INT_CNT_AD);
	// do something , prepare tiles, etc...
	vLine = -2;
	//enable hsync interrupt
	HWREG(PWM_BASE + PWM_GEN_1 + PWM_O_X_INTEN) |= PWM_INT_CNT_ZERO; //PWMGenIntTrigEnable(PWM_BASE, PWM_GEN_1, PWM_INT_CNT_AD);
	//PWMGenIntTrigEnable(PWM_BASE, PWM_GEN_1, PWM_INT_CNT_AD);

}


static unsigned long ulClockMS = 0;

int main(void)
{


	//MAP_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_12MHZ);
	MAP_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |SYSCTL_XTAL_12MHZ);

	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);


	ulClockMS = SysCtlClockGet() / (3 * 1000);

	//enable ahb for port B (faster writes)
	MAP_SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOB);

	MAP_GPIOPinTypePWM(GPIO_PORTG_BASE,GPIO_PIN_0);
	MAP_GPIOPinTypePWM(GPIO_PORTH_BASE,GPIO_PIN_0);
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTB_AHB_BASE,0xFF);
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_0);


	//setup pwm for vsync and hsync
	MAP_SysCtlPWMClockSet(SYSCTL_PWMDIV_16);

	MAP_PWMGenConfigure(PWM_BASE,PWM_GEN_0,PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
	MAP_PWMGenConfigure(PWM_BASE,PWM_GEN_1,PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
	MAP_PWMGenConfigure(PWM_BASE,PWM_GEN_2,PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);

	MAP_PWMGenPeriodSet(PWM_BASE, PWM_GEN_0,0xcb6a);
	MAP_PWMGenPeriodSet(PWM_BASE, PWM_GEN_1,0x63);
	MAP_PWMGenPeriodSet(PWM_BASE, PWM_GEN_2,0xcb6a);

	MAP_PWMPulseWidthSet(PWM_BASE, PWM_OUT_0, 199);
	MAP_PWMPulseWidthSet(PWM_BASE, PWM_OUT_2, 12);
	MAP_PWMPulseWidthSet(PWM_BASE, PWM_OUT_4, 3300);

	MAP_PWMOutputState(PWM_BASE, PWM_OUT_0_BIT, true); //Vsync pulse
	MAP_PWMOutputState(PWM_BASE, PWM_OUT_2_BIT, true); //hsync pulse

	MAP_PWMGenEnable(PWM_BASE, PWM_GEN_0);
	MAP_PWMGenEnable(PWM_BASE, PWM_GEN_1);
	MAP_PWMGenEnable(PWM_BASE, PWM_GEN_2);
	MAP_PWMSyncTimeBase(PWM_BASE, PWM_GEN_0 | PWM_GEN_1 | PWM_GEN_2);

	//
	// Enable processor interrupts.
	//
	IntMasterEnable();
	//PWMIntEnable(PWM_BASE, PWM_INT_GEN_0);
	PWMIntEnable(PWM_BASE, PWM_INT_GEN_1);
	PWMIntEnable(PWM_BASE, PWM_INT_GEN_2);

	//trigger when matched counting down
	//PWMGenIntTrigEnable(PWM_BASE, PWM_GEN_0, PWM_INT_CNT_AD);
	//PWMGenIntTrigDisable(PWM_BASE, PWM_GEN_1, PWM_INT_CNT_AD);
	PWMGenIntTrigEnable(PWM_BASE, PWM_GEN_2, PWM_INT_CNT_AD);
	//IntEnable(INT_PWM0);
	IntEnable(INT_PWM1);
	IntEnable(INT_PWM2);
	MAP_PWMSyncTimeBase(PWM_BASE, PWM_GEN_0 | PWM_GEN_1 | PWM_GEN_2);



	//
	// Loop forever.
	//
	while(1)
	{
		/*HWREG(GPIO_PORTE_BASE + GPIO_O_DATA + (GPIO_PIN_0 << 2)) = 0;
		SysCtlDelay(500 * ulClockMS);

		HWREG(GPIO_PORTE_BASE + GPIO_O_DATA + (GPIO_PIN_0 << 2)) = GPIO_PIN_0;
		SysCtlDelay(500 * ulClockMS);*/
	}
}
