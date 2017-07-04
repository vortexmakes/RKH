/*
 * cpu.c
 */

#include "rkh.h"
#include "lpc17xx.h"
#include "system_LPC17xx.h"
#include "bsp.h"
#include <NXP/crp.h>



__CRP const unsigned int CRP_WORD = CRP_NO_CRP;


/*
 * Setup systick for the RKH tick call.
 */

void
systick_init(void)
{
	/* Make PendSV, CallSV and SysTick the same priroity as the kernel. */
	*(portNVIC_SYSPRI2) |= ( ( ( unsigned long ) KERNEL_IRQ_PRIO ) << 24 );

	/* Configure SysTick to interrupt at the requested rate. */
	*(portNVIC_SYSTICK_LOAD) = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
	*(portNVIC_SYSTICK_CTRL) = portNVIC_SYSTICK_CLK | portNVIC_SYSTICK_INT | portNVIC_SYSTICK_ENABLE;
}

void
cpu_init( void )
{
	SystemClockUpdate();
	systick_init();
}
