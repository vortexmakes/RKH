/*
 *	svr.c
 */


#include "rkh.h"


/*
 *	Include file of HSM definitions.
 */

#include "svr.h"


/*
 *	Include file of action/guard definitions
 */

#include "svract.h"


/*
 *	Defines SMA (a.k.a Active Object) "svr".
 */

RKH_SMA_CREATE( SVR_T, svr, 0, HCAL, &svr_idle, svr_init, NULL );


/*
 *	Defines states and pseudostates.
 */

RKH_CREATE_BASIC_STATE( svr_idle, NULL, NULL,  RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( svr_idle )

	RKH_TRINT( TERM,	NULL,	svr_terminate ),
	RKH_TRREG( REQ,		NULL,	svr_start,	&svr_busy ),
	RKH_TRREG( PAUSE,	NULL,	NULL,		&svr_paused ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE( svr_busy, NULL, NULL,  RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( svr_busy )

	RKH_TRINT( REQ,		NULL,	svr_defer ),
	RKH_TRINT( TERM,	NULL,	svr_terminate ),
	RKH_TRREG( DONE,	NULL,	svr_end,	&svr_idle ),
	RKH_TRREG( PAUSE,	NULL,	NULL,		&svr_paused ),

RKH_END_TRANS_TABLE


RKH_CREATE_BASIC_STATE(	svr_paused, 
						svr_pause, svr_resume, RKH_ROOT, NULL );
RKH_CREATE_TRANS_TABLE( svr_paused )

	RKH_TRINT( REQ,		NULL,	svr_defer ),
	RKH_TRINT( DONE,	NULL,	NULL ),
	RKH_TRINT( TERM,	NULL,	svr_terminate ),
	RKH_TRREG( PAUSE,	NULL,	NULL,		&svr_idle ),

RKH_END_TRANS_TABLE
