/*
 *	sleep.c
 *	
 *	Programmer: Darío S. Baliña.
 *	Date : 26/05/06.
 */

#include "mytypes.h"
#include "sleep.h"
#include "rksys.h"
#include "watchdog.h"

static unsigned short tick;
/*
 * check_sleep: Must be called at MSEQBASE interrupt.
 */
void
check_sleep( void )
{
	if(tick)
		--tick;
}

/*
 * sleep: Performs a delay of msec in the execution
 * 			msec must be especified as a multiplo of 
 * 			RTI cadence MSEQBASE.
 */
void
sleep( unsigned short msec )
{
	enter_critical();
	tick = msec;
	exit_critical();
	
	while( tick )
		kick_watchdog();	
}





