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
 * 	Frequency enumeration
 */

enum
{
	FREQ_A = NO_ARG+1, FREQ_B,

	NUM_FREQ_IX
};

/*
 * 	Ring enumeration
 */

enum
{
	RING_ON = NO_ARG+1,

	NUM_RING_IX
};


/*
 * 	Led enumeraction
 */

enum
{
	LED_ON = NO_ARG+1,

	NUM_LED_IX
};


/*
 * 	Tone position in bit pattern
 */

#define TONE0	0x01

/*
 * 	Ring position in bit pattern
 */

#define RING0	0x01

/*
 * Led position in bit pattern
 */

#define LED_BATTON	0x0001		/*	Led of battery and switched on	*/
#define LED_INUSE	0x0002		/*	Led In Use or Off Hook			*/
#define LED_OPMODE	0x0008		/*	Led OPeration MODE				*/
#define LED_VMSG	0x0010		/*	Led of Voice MeSsaGe			*/
#define LED_20		0x4000		/*	Led 20% signal					*/
#define LED_40		0x2000		/*	Led 40% signal					*/
#define LED_60		0x1000		/*	Led 60% signal					*/
#define LED_80		0x0800		/*	Led 80% signal					*/
#define LED_100		0x0400		/*	Led 100% signal					*/

#define ALL_LEDS	0x7C1B		/* All */


void set_hard_tone( unsigned short minor, MUInt arga, MUInt argb );
void set_hard_ring( unsigned short minor, MUInt arga, MUInt argb );
void set_hard_leds( unsigned short minor, MUInt arga, MUInt argb );
void wait_for_semaphore( void );

#endif

