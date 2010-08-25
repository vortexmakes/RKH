/*
 * 	lowint.c
 * 		Low level routines for
 * 		interrupt management
 */

#include <hidef.h>
#include "derivative.h"
#include "mytypes.h"
#include "lowint.h"

void
enable_interrupt( void )
{
	EnableInterrupts;
}

void
disable_interrupt( void )
{
	DisableInterrupts;
}

/*
 * get_enable_status:
 * Returns	1 if global interrupts ar enabled.
 * 			0 if globla interrupts ar disabled.
 */
MUInt
get_enable_status( void )
{
	MUInt i;
	asm {
            	PSHA
				LDA	#1
				BMC ena 	/* branch if enabled */
				LDA	#0
		ena:	STA i
				PULA
		};

	return i;
}


