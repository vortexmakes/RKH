/*
 *	my.h
 */


#ifndef __MY_H__
#define __MY_H__


#include "rkh.h"


/*
 * 	Signals
 */

enum
{
	ZERO,		/* press the key '0' on the keyboard */
	ONE,		/* press the key '1' on the keyboard */
	TWO,		/* press the key '2' on the keyboard */
	THREE,		/* press the key '3' on the keyboard */
	FOUR,		/* press the key '4' on the keyboard */
	FIVE,		/* press the key '5' on the keyboard */
	SIX,		/* press the key '6' on the keyboard */
	TERM		/* press the key escape on the keyboard */
};


typedef struct
{
	RKH_EVT_T event;
	rkhui16_t ts;
} MYEVT_T;


typedef struct
{
	RKH_SMA_T sma;	/* base structure */
	rkhui8_t x;		/* private member */
	rkhui8_t y;		/* private member */
} MYSM_T;			/* SMA derived from RKH_SMA_T structure */


/*
 *	Declare HSM.
 */

RKH_SMA_DCLR( my );


/*
 *	Declare states and pseudostates.
 */

RKH_DCLR_COMP_STATE		S1;
RKH_DCLR_BASIC_STATE	S11,S13,S3,SB1,SB2;


RKH_DCLR_SUBM_STATE		S12,S2;
RKH_DCLR_REF_SUBM		SB;
RKH_DCLR_REF_EXPNT		EXPNT1,EXPNT2;
RKH_DCLR_REF_ENPNT		ENPNT;
RKH_DCLR_ENPNT			ENS12,ENS2;


#endif
