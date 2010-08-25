/*
 * 	lowint.h
 * 		Low level routines for
 * 		interrupt management
 */

#include "mytypes.h"

void rkenable_interrupt( void );
void rkdisable_interrupt( void );

/*
 * get_enable_status:
 * Returns	1 if global interrupts ar enabled.
 * 			0 if globla interrupts ar disabled.
 */
MUInt get_enable_status( void );

