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


int
main( int argc, char *argv[] )
{
	bsp_init( argc, argv );

	/* set trace filters */
	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );
	RKH_FILTER_OFF_GROUP_ALL_EVENTS( RKH_TG_SM );
	RKH_FILTER_OFF_SMA( blinky );

	rkh_init();
	RKH_TRC_OPEN();

	RKH_TR_FWK_OBJ( blinky );
	RKH_TR_FWK_OBJ( &blinky->equeue );
	RKH_TR_FWK_OBJ( &led_on );
	RKH_TR_FWK_OBJ( &led_off );
	RKH_TR_FWK_SIG( TIMEOUT );

	rkh_sma_activate( blinky, (const RKHEVT_T **)qsto, QSTO_SIZE, CV(0), 0 );
	rkh_enter();

	RKH_TRC_CLOSE();
	return 0;
}
