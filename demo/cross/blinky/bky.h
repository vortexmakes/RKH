/*
 *	bky.h
 */


#ifndef __BKY_H__
#define __BKY_H__


#include "rkh.h"


#define LED_OFF_TIME			200
#define LED_ON_TIME				200


/*
 * 	Signals.
 */

enum
{
	TIMEOUT,		/* 'blktim' timeout */
	BKY_NUM_EVENTS
};


typedef struct
{
	RKHSMA_T sma;	/* base structure */
	rkhui8_t cnt;	/* private member */
} BKYSM_T;			/* SMA derived from RKHSMA_T structure */


/*
 *	Declare HSM.
 */

RKH_SMA_DCLR( blinky );


/*
 *	Declare states and pseudostates.
 */

RKH_DCLR_BASIC_STATE	led_off, led_on;


#endif
