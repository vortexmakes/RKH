/*
 *	cli.c
 */


#include "rkh.h"


/*
 *	Include file of HSM definitions.
 */

#include "cli.h"


/*
 *	Include file of action/guard definitions
 */

#include "cliact.h"


/*
 *	Defines SMA (a.k.a Active Object) "cli".
 */

RKH_SMA_CREATE( CLI_T, cli0, CLI_PRIO_0, HCAL, &cli_idle, cli_init, NULL );
RKH_SMA_CREATE( CLI_T, cli1, CLI_PRIO_1, HCAL, &cli_idle, cli_init, NULL );
RKH_SMA_CREATE( CLI_T, cli2, CLI_PRIO_2, HCAL, &cli_idle, cli_init, NULL );
RKH_SMA_CREATE( CLI_T, cli3, CLI_PRIO_3, HCAL, &cli_idle, cli_init, NULL );

RKH_ARRAY_SMA_CREATE( clis, NUM_CLIENTS ) 
{
	&cli0, &cli1, &cli2, &cli3
};


/*
 *	Defines states and pseudostates.
 */

RKH_CREATE_BASIC_STATE( cli_idle, 
						cli_delay_req, NULL,  RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( cli_idle )

	RKH_TRREG( TOUT_REQ,	NULL,	cli_req,	&cli_waiting ),
	RKH_TRREG( PAUSE,		NULL,	NULL,		&cli_paused ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( cli_waiting, NULL, NULL,  RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( cli_waiting )

	RKH_TRREG( START,		NULL,	cli_start,	&cli_using ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( cli_using, NULL, NULL,  RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( cli_using )

	RKH_TRREG( TOUT_USING,	NULL,	cli_end,	&cli_idle ),
	RKH_TRREG( PAUSE,		NULL,	NULL,		&cli_paused ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( cli_paused, 
						cli_pause, cli_resume, RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( cli_paused )

	RKH_TRINT( TOUT_USING,	NULL, 	cli_end ),
	RKH_TRREG( PAUSE,		NULL,	NULL,		&cli_idle ),

RKH_END_TRANS_TABLE
