/*
 * main.c
 */


#include "rkh.h"
#include "rkhtrc.h"
#include "bsp.h"
#include "svr.h"
#include "svract.h"
#include "cli.h"
#include "cliact.h"


#define QSTO_SIZE			4


#if RKH_CFGPORT_SMA_QSTO_EN == RKH_ENABLED
	/* Defines the event queue storage for active object 'server' */
	static RKH_EVT_T *svr_qsto[ QSTO_SIZE ];

	/* Defines the event queue storage for active object 'client' */
	static RKH_EVT_T *cli_qsto[ NUM_CLIENTS ][ QSTO_SIZE ];

#else
	#define svr_qsto
	#define cli_qsto
#endif


#if RKH_CFGPORT_SMA_STK_EN == RKH_ENABLED
	/* Defines the task's stack for active object 'server' */
	static RKH_THREAD_STK_TYPE svr_stk[ SVR_STK_SIZE ];

	/* Defines the task's stack for active object 'client' */
	static RKH_THREAD_STK_TYPE cli_stk[ NUM_CLIENTS ][ CLI_STK_SIZE ];

#else
	#define svr_stk
	#define cli_stk
#endif


int
main( int argc, char *argv[] )
{
	rint cn;

	/* invoke the rkh_fwk_init() function */
	bsp_init( argc, argv );

	/* send objects to trazer */
	RKH_TR_FWK_AO( svr );
	RKH_TR_FWK_AO( CLI0 );
	RKH_TR_FWK_AO( CLI1 );
	RKH_TR_FWK_AO( CLI2 );
	RKH_TR_FWK_STATE( svr, &svr_idle );
	RKH_TR_FWK_STATE( svr, &svr_busy );
	RKH_TR_FWK_STATE( svr, &svr_paused );
	RKH_TR_FWK_STATE( CLI0, &cli_idle );
	RKH_TR_FWK_STATE( CLI0, &cli_waiting );
	RKH_TR_FWK_STATE( CLI0, &cli_using );
	RKH_TR_FWK_STATE( CLI0, &cli_paused );

	/* send signals to trazer */
	RKH_TR_FWK_SIG( REQ );
	RKH_TR_FWK_SIG( START );
	RKH_TR_FWK_SIG( DONE );
	RKH_TR_FWK_SIG( TOUT_USING );
	RKH_TR_FWK_SIG( TOUT_REQ );
	RKH_TR_FWK_SIG( PAUSE );
	RKH_TR_FWK_SIG( TERM );

	RKH_SMA_ACTIVATE( svr, svr_qsto, QSTO_SIZE, svr_stk, SVR_STK_SIZE );

	for( cn = 0; cn < NUM_CLIENTS; ++cn )
		RKH_SMA_ACTIVATE( CLI(cn), cli_qsto[cn], QSTO_SIZE,	cli_stk[cn], 
															CLI_STK_SIZE );
	rkh_fwk_enter();

	RKH_TRC_CLOSE();
	return 0;
}
