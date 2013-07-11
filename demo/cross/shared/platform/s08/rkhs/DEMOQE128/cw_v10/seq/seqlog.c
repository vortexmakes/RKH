/*
 * 	seqlog.c
 * 		Logical implementation of hardware
 * 		routines related to sequences
 * 		Now tones, rings and leds
 */

#include "mytypes.h"
#include "seqlog.h"
#include "ledsctrl.h"
#include "genled.h"
#include "gpio.h"

volatile MUInt sem;


void
set_hard_leds( unsigned short minor, MUInt arga, MUInt argb )
{
	switch( minor )
	{
		case CLI0_LED:
			set_iopin( LED1, (arga == LED_ON) ? 0 : 1 );
			break;
		case CLI1_LED:
			set_iopin( LED2, (arga == LED_ON) ? 0 : 1 );
		default:
			break;
	}
}


void
wait_for_semaphore( void )
{
	for( sem = 1; sem; );
}
