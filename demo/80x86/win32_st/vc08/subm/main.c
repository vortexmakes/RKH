/*
 * main.c
 */


#include "rkh.h"
#include "rkhtrc.h"
#include "bsp.h"
#include "my.h"
#include "rkhdata.h"


#define QSTO_SIZE			4

static RKH_EVT_T *qsto[ QSTO_SIZE ];


int
main( int argc, char *argv[] )
{
	bsp_init( argc, argv );

	/* set trace filters */
	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );

	RKH_FILTER_OFF_EVENT( RKH_TE_SM_DCH );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_NENEX );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_ENSTATE );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_EXSTATE );

	rkh_fwk_init();
	RKH_TRC_OPEN();

	RKH_TR_FWK_OBJ( &S1 );
	RKH_TR_FWK_OBJ( my );
	RKH_TR_FWK_OBJ( &S11 );
	RKH_TR_FWK_OBJ( &S13 );
	RKH_TR_FWK_OBJ( &S3 );
	RKH_TR_FWK_OBJ( &SB1 );
	RKH_TR_FWK_OBJ( &SB2 );
	RKH_TR_FWK_OBJ( &S12 );
	RKH_TR_FWK_OBJ( &S2 );
	RKH_TR_FWK_OBJ( &SB );
	RKH_TR_FWK_OBJ( &EXPNT1 );
	RKH_TR_FWK_OBJ( &EXPNT2 );
	RKH_TR_FWK_OBJ( &ENPNT );
	RKH_TR_FWK_OBJ( &ENS12 );
	RKH_TR_FWK_OBJ( &ENS2 );

	RKH_TR_FWK_SIG( ZERO );
	RKH_TR_FWK_SIG( ONE	);
	RKH_TR_FWK_SIG( TWO	);
	RKH_TR_FWK_SIG( THREE	);
	RKH_TR_FWK_SIG( FOUR	);
	RKH_TR_FWK_SIG( FIVE	);
	RKH_TR_FWK_SIG( SIX	);
	RKH_TR_FWK_SIG( TERM	);
	
	rkh_sma_activate( my, (const RKH_EVT_T **)qsto, QSTO_SIZE, CV(0), 0 );
	rkh_fwk_enter();

	RKH_TRC_CLOSE();
	return 0;
}
