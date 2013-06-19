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

static RKHEVT_T *svr_qsto[ QSTO_SIZE ], *cli_qsto[ QSTO_SIZE ];


int
main( int argc, char *argv[] )
{
	/* invoke the rkh_init() function */
	bsp_init( argc, argv );

	/* send objects to trazer */
	RKH_TR_FWK_AO( svr );
	RKH_TR_FWK_AO( cli );
	RKH_TR_FWK_QUEUE( &svr->equeue );
	RKH_TR_FWK_QUEUE( &cli->equeue );
	RKH_TR_FWK_STATE( svr, &svr_idle );
	RKH_TR_FWK_STATE( svr, &svr_busy );
	RKH_TR_FWK_STATE( svr, &svr_paused );
	RKH_TR_FWK_STATE( cli, &cli_idle );
	RKH_TR_FWK_STATE( cli, &cli_waiting );
	RKH_TR_FWK_STATE( cli, &cli_using );
	RKH_TR_FWK_STATE( cli, &cli_paused );

	/* send signals to trazer */
	RKH_TR_FWK_SIG( REQ );
	RKH_TR_FWK_SIG( START );
	RKH_TR_FWK_SIG( DONE );
	RKH_TR_FWK_SIG( TOUT );
	RKH_TR_FWK_SIG( PAUSE );
	RKH_TR_FWK_SIG( TERM );

	rkh_sma_activate( svr, (const RKHEVT_T **)svr_qsto, QSTO_SIZE, CV(0), 0 );
	rkh_sma_activate( cli, (const RKHEVT_T **)cli_qsto, QSTO_SIZE, CV(0), 0 );
	rkh_enter();

	RKH_TRC_CLOSE();
	return 0;
}
