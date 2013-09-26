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

static uint8_t pattern[213]={1, 2, 3, 6, 2, 5, 6, 5, 2, 5, 0, 1, 4, 4, 6, 3, 6, 2, 7, 0, 6, 1, 6, 3, 2, 5, 2, 1,
		5, 5, 1, 1, 1, 4, 6, 5, 1, 2, 0, 0, 0, 6, 3, 1, 6, 2, 4, 7, 7, 5, 4, 1, 1, 7, 3, 6, 4, 2, 1, 0, 0, 4, 1,
		2, 7, 0, 7, 4, 1, 1, 3, 4, 4, 1, 3, 3, 1, 2, 7, 3, 5, 7, 2, 4, 6, 1, 6, 7, 3, 2, 6, 1, 1, 3, 3, 3, 6, 2,
		7, 3, 0, 2, 3, 1, 0, 6, 2, 3, 0, 2, 6, 5, 0, 3, 7, 6, 2, 6, 2, 6, 4, 0, 4, 1, 3, 6, 0, 5, 3, 7, 2, 7, 1,
		7, 4, 7, 0, 3, 1, 2, 1, 7, 4, 7, 6, 3, 7, 1, 5, 1, 4, 4, 3, 3, 1, 4, 5, 4, 4, 2, 0, 3, 1, 0, 6, 3, 7, 5,
		6, 3, 3, 2, 0, 2, 3, 4, 5, 7, 4, 6, 5, 3, 6, 6, 1, 2, 7, 6, 5, 4, 6, 0, 6, 1, 1, 1, 2, 7, 1, 1, 6, 1, 0,
		0, 5, 7, 0, 6, 3, 7, 5, 0, 2
};



volatile int vLine;
volatile int backPorchLinesToGo;

#define VPixels 480
#define VBackPorchLines 35


//PWM Gen 0
void VsyncHandler(){
	HWREG(PWM_BASE +  PWM_GEN_0 + PWM_O_X_ISC) = PWM_INT_CNT_AD; //PWMGenIntClear(PWM_BASE, PWM_GEN_0, PWM_INT_CNT_AD);
	HWREG(PWM_BASE + PWM_GEN_1 + PWM_O_X_INTEN) |= PWM_INT_CNT_AU; //PWMGenIntTrigEnable(PWM_BASE, PWM_GEN_1, PWM_INT_CNT_AU);
	backPorchLinesToGo = VBackPorchLines;
	vLine = 0;
}


//PWM Gen 1
void HsyncHandler(){

	HWREG(PWM_BASE +  PWM_GEN_1 + PWM_O_X_ISC) = PWM_INT_CNT_AU;  //PWMGenIntClear(PWM_BASE, PWM_GEN_2, PWM_INT_CNT_AD);
	//unsigned int indexb=vLine/3;

	asm volatile("nop");

	// after vsync we do the back porch
	if (backPorchLinesToGo)
	{
		backPorchLinesToGo--;
		return;
	}

	asm volatile("nop");

	// if all lines done, do the front porch
	if (vLine >= VPixels){
		HWREG(PWM_BASE +  PWM_GEN_1  + PWM_O_X_INTEN) &= ~(PWM_INT_CNT_AU); //PWMGenIntTrigDisable(PWM_BASE, PWM_GEN_1, PWM_INT_CNT_AU);
		return;
	}

	asm volatile("nop");


	#include "loop.h"

    HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF << 2)) = 0; // drop back to black


	/*uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT,
			UDMA_MODE_AUTO,pattern+(indexb*160), (void *)(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF<< 2)) , 160);
	uDMAChannelEnable(UDMA_CHANNEL_SW);
	uDMAChannelRequest(UDMA_CHANNEL_SW);*/

	// this line done
	vLine++;
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
	MAP_PWMGenPeriodSet(PWM_BASE, PWM_GEN_1, 0x63);
	MAP_PWMGenPeriodSet(PWM_BASE, PWM_GEN_2, 0x63);
	MAP_PWMPulseWidthSet(PWM_BASE, PWM_OUT_0, 199);
	MAP_PWMPulseWidthSet(PWM_BASE, PWM_OUT_2, 12);
	MAP_PWMPulseWidthSet(PWM_BASE, PWM_OUT_4, 16);
	MAP_PWMOutputState(PWM_BASE, PWM_OUT_0_BIT, true);
	MAP_PWMOutputState(PWM_BASE, PWM_OUT_2_BIT, true);
	MAP_PWMGenEnable(PWM_BASE, PWM_GEN_0);
	MAP_PWMGenEnable(PWM_BASE, PWM_GEN_1);
	MAP_PWMGenEnable(PWM_BASE, PWM_GEN_2);
	MAP_PWMSyncTimeBase(PWM_BASE, PWM_GEN_0 | PWM_GEN_1 | PWM_GEN_2);

	//
	// Enable processor interrupts.
	//
	IntMasterEnable();
	PWMIntEnable(PWM_BASE, PWM_INT_GEN_0);
	PWMIntEnable(PWM_BASE, PWM_INT_GEN_2);

	//trigger when matched counting down
	PWMGenIntTrigEnable(PWM_BASE, PWM_GEN_0, PWM_INT_CNT_AD);
	PWMGenIntTrigEnable(PWM_BASE, PWM_GEN_2, PWM_INT_CNT_AD);
	IntEnable(INT_PWM0);
	IntEnable(INT_PWM2);
	MAP_PWMSyncTimeBase(PWM_BASE, PWM_GEN_0 | PWM_GEN_1 | PWM_GEN_2);



	//
	// Loop forever.
	//
	while(1)
	{
		HWREG(GPIO_PORTE_BASE + GPIO_O_DATA + (GPIO_PIN_0 << 2)) = 0;
		SysCtlDelay(500 * ulClockMS);

		HWREG(GPIO_PORTE_BASE + GPIO_O_DATA + (GPIO_PIN_0 << 2)) = GPIO_PIN_0;
		SysCtlDelay(500 * ulClockMS);
	}
}
