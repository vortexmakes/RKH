/*
 * 	seqlog.h
 * 		Logical implementation of hardware
 * 		routines related to sequences
 * 		Now tones, rings and leds
 */

#ifndef __SEQLOG_H__
#define __SEQLOG_H__

#include "mytypes.h"

extern volatile MUInt sem;

/*
 * 	Sequence generation
 */

#define NO_ARG	0

/*
 * 	Led enumeraction
 */

enum
{
	LED_ON = NO_ARG+1,

	NUM_LED_IX
};


void set_hard_leds( unsigned short minor, MUInt arga, MUInt argb );
void wait_for_semaphore( void );

#endif

