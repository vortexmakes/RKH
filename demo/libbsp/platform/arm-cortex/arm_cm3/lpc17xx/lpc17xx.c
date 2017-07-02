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
systick_init(  )
{
	/* Make PendSV, CallSV and SysTick the same priroity as the kernel. */
	*(portNVIC_SYSPRI2) |= ( ( ( unsigned long ) KERNEL_IRQ_PRIO ) << 24 );

	/* Configure SysTick to interrupt at the requested rate. */
	*(portNVIC_SYSTICK_LOAD) = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
	*(portNVIC_SYSTICK_CTRL) = portNVIC_SYSTICK_CLK | portNVIC_SYSTICK_INT | portNVIC_SYSTICK_ENABLE;

}


/*
 * Systick ISR
 */

void 
SysTick_Handler( void )
{
	RKH_TIM_TICK(0);
}


/*
 * Routines to implement time stamp counter
 */

static uint32_t pclk;


/*
 * Setup RIT module for 1us time stamp resolution
 */

void
init_ts_timer ( void ) 
{
  uint32_t pclkdiv;

	pclkdiv = (LPC_SC->PCLKSEL0 >> 6) & 0x03;
	switch ( pclkdiv )
	{
	  case 0x00:
	  default:
		pclk = SystemFrequency/4;
		break;
	  case 0x01:
		pclk = SystemFrequency;
		break; 
	  case 0x02:
		pclk = SystemFrequency/2;
		break; 
	  case 0x03:
		pclk = SystemFrequency/8;
		break;
	}
	
	pclk /= 1000000;

  LPC_SC->PCONP |= (1 << 16);
  LPC_RIT->RICOMPVAL = 0;
  LPC_RIT->RICTRL |= 0x03;

  *(portIP7) |= ( ( ( unsigned long ) KERNEL_IRQ_PRIO ) << 11 );

  NVIC_EnableIRQ(RIT_IRQn);
  return;
}


/*
 * RIT ISR
 */

void
RIT_IRQHandler (void) 
{  
  LPC_RIT->RICTRL |= 0x1;
  return;
}


/*
 * Time stamp read function
 */

unsigned long
get_ts( void )
{
  return ( LPC_RIT->RICOUNTER / pclk );
}


void
cpu_init( void )
{
	SystemClockUpdate();
	systick_init();
	init_ts_timer();
}
