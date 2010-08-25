
/*
 * 	maintime.h
 * 		Module to manage
 * 		timer interrupt
 * 		Is independent of application
 */


#include "mytypes.h"

void init_main_timer_interrupt( void );

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

void main_timer_interrupt( void );
