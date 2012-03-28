/*
 * main.c
 */


#include "rkh.h"
#include "rkhtrc.h"
#include "bsp.h"
#include "my.h"
#include "myevt.h"
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

	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_MP, RKH_TRCE_MP_INIT );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_SM, RKH_TRCE_SM_DCH );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_RKH, RKH_TRCE_OBJ );
	RKH_FILTER_OFF_GROUP_EVENT( RKH_TRCG_RKH, RKH_TRCE_SIG );

	rkh_trc_open();
	rkh_init();

	RKH_TRCR_RKH_OBJ( &rkheplist[0] );
	RKH_TRCR_RKH_OBJ( &rkheplist[1] );
	RKH_TRCR_RKH_SIG( ONE );

	rkh_sma_activate( my, qsto, QSTO_SIZE, ( void * )0, 0 );
	rkh_enter();

	rkh_trc_close();
	return 0;
}
