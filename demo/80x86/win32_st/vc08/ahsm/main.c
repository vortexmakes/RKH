/*
 * main.c
 */


#include "rkh.h"
#include "rkhtrc.h"
#include "bsp.h"
#include "my.h"
#include "myact.h"
#include "rkhdata.h"


#define QSTO_SIZE			4

static RKHEVT_T *qsto[ QSTO_SIZE ];


int
main( int argc, char *argv[] )
{
	bsp_init( argc, argv );

	/* set trace filters */
	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );

	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_SM, RKH_TRCE_SM_DCH );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_SM, RKH_TRCE_SM_NENEX );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_SM, RKH_TRCE_SM_ENSTATE );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_SM, RKH_TRCE_SM_EXSTATE );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_SM, RKH_TRCE_SM_NTRNACT );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_RQ, RKH_TRCE_RQ_FIFO );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_RKH, RKH_TRCE_OBJ );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_RKH, RKH_TRCE_SIG );
	
	RKH_FILTER_OFF_SMA( my );

	rkh_init();
	RKH_TRC_OPEN();

	RKH_TRCR_RKH_OBJ( &S1 );
	RKH_TRCR_RKH_OBJ( my );
	RKH_TRCR_RKH_OBJ( &my->equeue );
	RKH_TRCR_RKH_OBJ( &S1 );
	RKH_TRCR_RKH_OBJ( &S11 );
	RKH_TRCR_RKH_OBJ( &S111 );
	RKH_TRCR_RKH_OBJ( &S112 );
	RKH_TRCR_RKH_OBJ( &S12 );
	RKH_TRCR_RKH_OBJ( &S2 );
	RKH_TRCR_RKH_OBJ( &S3 );
	RKH_TRCR_RKH_OBJ( &S31 );
	RKH_TRCR_RKH_OBJ( &S32 );
	RKH_TRCR_RKH_OBJ( &C1 );
	RKH_TRCR_RKH_OBJ( &C2 );
	RKH_TRCR_RKH_OBJ( &J );
	RKH_TRCR_RKH_OBJ( &DH );
	RKH_TRCR_RKH_OBJ( &H );

	RKH_TRCR_RKH_SIG( ZERO );
	RKH_TRCR_RKH_SIG( ONE	);
	RKH_TRCR_RKH_SIG( TWO	);
	RKH_TRCR_RKH_SIG( THREE	);
	RKH_TRCR_RKH_SIG( FOUR	);
	RKH_TRCR_RKH_SIG( FIVE	);
	RKH_TRCR_RKH_SIG( SIX	);
	RKH_TRCR_RKH_SIG( TERM	);

	rkh_sma_activate( my, (const RKHEVT_T **)qsto, QSTO_SIZE, CV(0), 0 );
	rkh_enter();

	RKH_TRC_CLOSE();
	return 0;
}
