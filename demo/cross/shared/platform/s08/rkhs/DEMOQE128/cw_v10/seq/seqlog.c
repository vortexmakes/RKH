/*
 * 	seqlog.c
 * 		Logical implementation of hardware
 * 		routines related to sequences
 * 		Now tones, rings and leds
 */

#include "mytypes.h"
#include "seqlog.h"
#include "genled.h"
#include "gpio.h"

volatile MUInt sem;

#define LEDS_ON_PORTC_MASK (CLI0_LED|CLI1_LED|CLI2_LED|CLI3_LED|CLI4_LED)
#define LEDS_ON_PORTE_MASK (SRV_LED)

void
set_hard_leds( unsigned short minor, MUInt arga, MUInt argb )
{
	(void)argb;
	
	if( arga == LED_ON )
	{
		PTCD &= ~(minor & LEDS_ON_PORTC_MASK);
		PTED &= ~(minor & LEDS_ON_PORTE_MASK);
	}
	else
	{
		PTCD |= (minor & LEDS_ON_PORTC_MASK);
		PTED |= (minor & LEDS_ON_PORTE_MASK);
	}
}


void
wait_for_semaphore( void )
{
	for( sem = 1; sem; );
}
