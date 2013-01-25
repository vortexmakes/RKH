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
extern RKHT_T tx, ty, tz;


int
main( int argc, char *argv[] )
{
	bsp_init( argc, argv );

	/* set trace filters */
	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );

	/*
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_DCH );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_NENEX );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_ENSTATE );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_EXSTATE );
	RKH_FILTER_OFF_EVENT( RKH_TE_SM_NTRNACT );
	RKH_FILTER_OFF_EVENT( RKH_TE_RQ_FIFO );
	*/

	RKH_FILTER_OFF_GROUP_ALL_EVENTS( RKH_TG_TIM );
	RKH_FILTER_OFF_SMA( my );

	rkh_init();
	RKH_TRC_OPEN();

	RKH_TR_FWK_OBJ( &tx );
	RKH_TR_FWK_OBJ( &ty );
	RKH_TR_FWK_OBJ( &tz );

	RKH_TR_FWK_OBJ( &S1 );
	RKH_TR_FWK_OBJ( my );
	RKH_TR_FWK_OBJ( &my->equeue );
	RKH_TR_FWK_OBJ( &S1 );
	RKH_TR_FWK_OBJ( &S11 );
	RKH_TR_FWK_OBJ( &S111 );
	RKH_TR_FWK_OBJ( &S112 );
	RKH_TR_FWK_OBJ( &S12 );
	RKH_TR_FWK_OBJ( &S2 );
	RKH_TR_FWK_OBJ( &S3 );
	RKH_TR_FWK_OBJ( &S31 );
	RKH_TR_FWK_OBJ( &S32 );
	RKH_TR_FWK_OBJ( &C1 );
	RKH_TR_FWK_OBJ( &C2 );
	RKH_TR_FWK_OBJ( &J );
	RKH_TR_FWK_OBJ( &DH );
	RKH_TR_FWK_OBJ( &H );

	RKH_TR_FWK_SIG( ZERO );
	RKH_TR_FWK_SIG( ONE	);
	RKH_TR_FWK_SIG( TWO	);
	RKH_TR_FWK_SIG( THREE	);
	RKH_TR_FWK_SIG( FOUR	);
	RKH_TR_FWK_SIG( FIVE	);
	RKH_TR_FWK_SIG( SIX	);
	RKH_TR_FWK_SIG( TERM	);

	rkh_sma_activate( my, (const RKHEVT_T **)qsto, QSTO_SIZE, CV(0), 0 );
	rkh_enter();

	RKH_TRC_CLOSE();
	return 0;
}
