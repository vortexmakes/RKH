/*
 *	cli.h
 */


#ifndef __CLI_H__
#define __CLI_H__


#include "rkh.h"
#include "scevt.h"


#define CLI( _clino )			RKH_ARRAY_SMA( clis, _clino )
#define CLI0					CLI(0)
#define CLI1					CLI(1)
#define CLI2					CLI(2)
#define CLI3					CLI(3)
#define CLI_STK_SIZE			1024


typedef enum cli_prio
{
	CLI_PRIO_0 = 1, CLI_PRIO_1, CLI_PRIO_2, CLI_PRIO_3,
	MAX_CLI_PRIO,
	NUM_CLIENTS = MAX_CLI_PRIO - 1,
}CLI_PRIO;


typedef struct
{
	RKH_SMA_T sma;		/* base structure */
	RKH_TMR_T cli_utmr; /* usage time */
	RKH_TMR_T cli_rtmr;	/* waiting request time */
} CLI_T;				/* Active Object derived from RKH_SMA_T structure */


/*
 *	Declare HSM.
 */

RKH_ARRAY_SMA_DCLR( clis, NUM_CLIENTS );


/*
 *	Declare states and pseudostates.
 */

RKH_DCLR_BASIC_STATE	cli_idle, cli_waiting, cli_using, cli_paused;


#endif
