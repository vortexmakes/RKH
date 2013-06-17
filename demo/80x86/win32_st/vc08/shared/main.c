/*
 * main.c
 */


#include "rkh.h"
#include "rkhtrc.h"
#include "bsp.h"
#include "my.h"
#include "myact.h"


#define QSTO_SIZE			4

static RKHEVT_T *qsto[ QSTO_SIZE ];


int
main( int argc, char *argv[] )
{
	/* invoke the rkh_init() function */
	bsp_init( argc, argv );

	/* set trace filters */
	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );
	RKH_FILTER_OFF_GROUP_ALL_EVENTS( RKH_TG_SM );
	RKH_FILTER_OFF_SMA( my );

	RKH_TRC_OPEN();

	/* send objects to trazer */
	RKH_TR_FWK_AO( my );
	RKH_TR_FWK_QUEUE( &my->equeue );
	RKH_TR_FWK_STATE( my, &S1 );
	RKH_TR_FWK_STATE( my, &S1 );
	RKH_TR_FWK_STATE( my, &S11 );
	RKH_TR_FWK_STATE( my, &S111 );
	RKH_TR_FWK_STATE( my, &S112 );
	RKH_TR_FWK_STATE( my, &S12 );
	RKH_TR_FWK_STATE( my, &S2 );
	RKH_TR_FWK_STATE( my, &S3 );
	RKH_TR_FWK_STATE( my, &S31 );
	RKH_TR_FWK_STATE( my, &S32 );
	RKH_TR_FWK_PSTATE( my, &C1 );
	RKH_TR_FWK_PSTATE( my, &C2 );
	RKH_TR_FWK_PSTATE( my, &CH );
	RKH_TR_FWK_PSTATE( my, &DH );
	RKH_TR_FWK_PSTATE( my, &H );

	/* send signals to trazer */
	RKH_TR_FWK_SIG( ZERO );
	RKH_TR_FWK_SIG( ONE	);
	RKH_TR_FWK_SIG( TWO	);
	RKH_TR_FWK_SIG( THREE );
	RKH_TR_FWK_SIG( FOUR );
	RKH_TR_FWK_SIG( FIVE );
	RKH_TR_FWK_SIG( SIX	);
	RKH_TR_FWK_SIG( TERM );

	rkh_sma_activate( my, (const RKHEVT_T **)qsto, QSTO_SIZE, CV(0), 0 );
	rkh_enter();

	RKH_TRC_CLOSE();
	return 0;
}
