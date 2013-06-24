/*
 *	svr.h
 */


#ifndef __SVR_H__
#define __SVR_H__


#include "rkh.h"
#include "scevt.h"


typedef struct
{
	RKHSMA_T sma;	/* base structure */
	rkhui8_t x;		/* private member */
} SVR_T;			/* Active Object derived from RKHSMA_T structure */


/*
 *	Declare HSM.
 */

RKH_SMA_DCLR( svr );


/*
 *	Declare states and pseudostates.
 */

RKH_DCLR_BASIC_STATE	svr_idle, svr_busy, svr_paused;


#endif
