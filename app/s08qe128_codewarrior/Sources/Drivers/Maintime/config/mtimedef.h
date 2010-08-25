/*
 * 	mtimedef.h
 * 		Main timer definitions
 */

#include "mytypes.h"

/*
 * 	Here define the time of interrupt in us
 */

#define MAIN_TIMER_TIME			1000		/* Expressed in us	*/

/*
 * 	Number of slots in table 'timer_chain'
 * 	declared in 'mtimetbl.h' and user defined
 * 	in 'mtimetbl.c'.
 */

#define NUM_TIMER_DIVISORS		3


