/*
 *	cli.h
 */


#ifndef __CLI_H__
#define __CLI_H__


#include "rkh.h"
#include "scevt.h"


#define NUM_CLIENTS				4
#define CLI( _clino )			*clis[_clino]

#define CLI0					CLI(0)
#define CLI1					CLI(1)
#define CLI2					CLI(2)
#define CLI3					CLI(3)


typedef struct
{
	RKHSMA_T sma;		/* base structure */
	RKHT_T cli_utmr; 	/* usage time */
	RKHT_T cli_rtmr;	/* waiting request time */
} CLI_T;				/* Active Object derived from RKHSMA_T structure */


/*
 *	Declare HSM.
 */

RKH_ARRAY_SMA_DCLR( clis, NUM_CLIENTS );


/*
 *	Declare states and pseudostates.
 */

RKH_DCLR_BASIC_STATE	cli_idle, cli_waiting, cli_using, cli_paused;


#endif
