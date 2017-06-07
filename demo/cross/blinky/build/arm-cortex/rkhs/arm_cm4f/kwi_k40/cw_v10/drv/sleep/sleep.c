/*
 *	sleep.c
 */

#include "sleep.h"

static volatile unsigned short tick;

void sleep_tick( void );

void
sleep_tick( void )			/*	TIMER0 interrupt 1mseg	*/
{	
	if( tick )
		--tick;
}
	

/*
 * 		sleep:
 * 			sleeps during 'msec" with
 * 			a determination of +- 1 msec.
 */

void
sleep( unsigned short msec )
{
	if( msec == 0)
		return;
		
	tick = msec;
	while( tick )
		;
}
