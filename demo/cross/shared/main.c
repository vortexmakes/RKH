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

static RKH_EVT_T *svr_qsto[ QSTO_SIZE ];
static RKH_EVT_T *cli_qsto[ NUM_CLIENTS ][ QSTO_SIZE ];


int
main( int argc, char *argv[] )
{
	HInt cn;

	/* invoke the rkh_fwk_init() function */
	bsp_init( argc, argv );

	/* send objects to trazer */
	RKH_TR_FWK_AO( svr );
	RKH_TR_FWK_AO( CLI0 );
	RKH_TR_FWK_AO( CLI1 );
	RKH_TR_FWK_AO( CLI2 );
	RKH_TR_FWK_AO( CLI3 );
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

	rkh_sma_activate( svr, (const RKH_EVT_T **)svr_qsto, QSTO_SIZE, 
																CV(0), 0 );
	for( cn = 0; cn < NUM_CLIENTS; ++cn )
		rkh_sma_activate( CLI(cn), (const RKH_EVT_T **)cli_qsto[cn], 
												QSTO_SIZE, CV(0), 0 );
	rkh_fwk_enter();

	RKH_TRC_CLOSE();
	return 0;
}
