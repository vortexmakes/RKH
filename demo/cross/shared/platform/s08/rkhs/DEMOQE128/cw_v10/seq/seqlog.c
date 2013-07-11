/*
 * 	seqlog.c
 * 		Logical implementation of hardware
 * 		routines related to sequences
 * 		Now tones, rings and leds
 */

#include "mytypes.h"
#include "seqlog.h"
#include "ledsctrl.h"

volatile MUInt sem;

void
set_hard_tone( unsigned short minor, MUInt arga, MUInt argb )
{
	set_slic_tone( arga, argb );
}

void
set_hard_ring( unsigned short minor, MUInt arga, MUInt argb )
{
	set_slic_ring( arga, argb );
}

void
set_hard_leds( unsigned short minor, MUInt arga, MUInt argb )
{
	set_led_mask( minor, arga );
}


void
wait_for_semaphore( void )
{
	for( sem = 1; sem; );
}
