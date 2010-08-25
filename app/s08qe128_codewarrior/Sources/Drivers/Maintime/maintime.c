/*
 * 	maintime.c
 * 		Module to manage
 * 		timer interrupt
 * 		Is independent of application
 */

#include <stdio.h>

#include "mytypes.h"

#include "maintime.h"
#include "mtimetbl.h"
#include "mtimedef.h"
#include "rti.h"

static unsigned short main_timer_counter;

static
void
execute_list( void (* const *p)( void ) )
{
	for(  ; *p != NULL; ++p  )
		(**p)();
}

void
init_main_timer_interrupt( void )
{
	init_timer_hardware( MAIN_TIMER_TIME );
	main_timer_counter = 0;
}

/*
 * 	This is the main timer interrupt
 * 	In abstract form, this interrupt
 * 	is called each MAIN_TIMER_TIME
 * 	expressed in terms of 100 usecs.
 * 	that is, if MAIN_TIMER_TIME is set to
 * 	10, then is called in each milliseconds
 * 	From here, is controlled all of the 
 * 	timing chain for the project
 * 	This timing chain is controlled
 * 	by table 'timer_chain'
 */

void
main_timer_interrupt( void )
{
	const TIMER_CHAIN *p;
	MUInt num;

	for( p = timer_chain, num = NUM_TIMER_DIVISORS; num-- ; ++p )
		if( ( main_timer_counter % p->timer ) == 0 )
			execute_list( p->ptimeact );
	if( ++main_timer_counter >= (p-1)->timer )
		main_timer_counter = 0;
}

