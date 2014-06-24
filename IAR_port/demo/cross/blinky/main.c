/*
 * main.c
 */


#include "rkh.h"
#include "rkhtrc.h"
#include "bsp.h"
#include "bky.h"
#include "bkyact.h"


#define QSTO_SIZE			4

static RKHEVT_T *qsto[ QSTO_SIZE ];
extern RKHT_T bkytim;


int
main( int argc, char *argv[] )
{
	bsp_init( argc, argv );

	/* set trace run-time filters */
	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );
	RKH_FILTER_OFF_EVENT( RKH_TE_TIM_TOUT );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_STATE );
	RKH_FILTER_OFF_SMA( blinky );
	RKH_FILTER_OFF_ALL_SIGNALS();

	rkh_init();
	RKH_TRC_OPEN();

	RKH_TR_FWK_AO( blinky );
	RKH_TR_FWK_QUEUE( &blinky->equeue );
	RKH_TR_FWK_STATE( blinky, &led_on );
	RKH_TR_FWK_STATE( blinky, &led_off );
	RKH_TR_FWK_TIMER( &bkytim );
	RKH_TR_FWK_SIG( TIMEOUT );

	rkh_sma_activate( blinky, (const RKHEVT_T **)qsto, QSTO_SIZE, CV(0), 0 );
	rkh_enter();

	RKH_TRC_CLOSE();
	return 0;
}
