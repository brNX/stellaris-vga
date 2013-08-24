#include <inc/hw_types.h>
#include <inc/hw_timer.h>
#include <inc/hw_ints.h>
#include <inc/hw_memmap.h>
#include <inc/hw_gpio.h>
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

static uint8_t pattern[]={0xF,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x0,
		0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x5,0x0
};

// The control table used by the uDMA controller.  This table must be aligned to a 1024 byte boundary.
uint8_t ui8ControlTable[1024] __attribute__ ((aligned(1024)));

#define verticalPixels  480  // 480 pixels high

volatile int vLine;
volatile int messageLine;
volatile uint8_t backPorchLinesToGo;
volatile int doline;

//PWM Gen 0
void VsyncHandler(){

	PWMGenIntClear(PWM_BASE, PWM_GEN_0, PWM_INT_CNT_AD);

	vLine = 0;
	messageLine = 0;
}


//PWM Gen 1
void HsyncHandler(){
	PWMGenIntClear(PWM_BASE, PWM_GEN_2, PWM_INT_CNT_AD);

	// if all lines done, do the front porch
	if (vLine >= verticalPixels)
		return;

	uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT,
			UDMA_SIZE_8 | UDMA_SRC_INC_8 |
			UDMA_DST_INC_NONE | UDMA_ARB_512);
	uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT,
			UDMA_MODE_AUTO,pattern, (void *)(GPIO_PORTB_AHB_BASE + GPIO_O_DATA + (0xFF<< 2)) , sizeof(pattern));
	uDMAChannelEnable(UDMA_CHANNEL_SW);
	uDMAChannelRequest(UDMA_CHANNEL_SW);

	// this line done
	vLine++;
}


void uDMAErrorHandler(void){}
void Timer0Handler(void){}

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
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);

	ulClockMS = SysCtlClockGet() / (3 * 1000);

	//enable ahb for port B (faster writes)
	MAP_SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOB);

	MAP_GPIOPinTypePWM(GPIO_PORTG_BASE,GPIO_PIN_0);
	MAP_GPIOPinTypePWM(GPIO_PORTH_BASE,GPIO_PIN_0);
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTB_AHB_BASE,0xFF);
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_0);

	uDMAEnable();
	uDMAControlBaseSet(ui8ControlTable);
	uDMAChannelAttributeDisable(UDMA_CHANNEL_SW,UDMA_ATTR_ALL);


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
	MAP_PWMPulseWidthSet(PWM_BASE, PWM_OUT_4, 10);
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
		GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_0,0);
		SysCtlDelay(500 * ulClockMS);

		GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_0,GPIO_PIN_0);
		SysCtlDelay(500 * ulClockMS);
	}
}
