/*
 * main.c
 */


#include "rkh.h"
#include "bsp.h"
#include "my.h"
#include "myact.h"


#define QSTO_SIZE			4

static RKH_EVT_T *qsto[ QSTO_SIZE ];

enum
{
	MY_TRACE = RKH_TE_USER
};


int
main( int argc, char *argv[] )
{
	rui8_t d1 = 255;
	rui16_t d2 = 65535;
	rui32_t d3 = 65535;
	char *str = "hello";

	bsp_init( argc, argv );

	/* set trace filters */
	RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
	RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );
	RKH_FILTER_OFF_EVENT( MY_TRACE );
	RKH_FILTER_OFF_GROUP_ALL_EVENTS( RKH_TG_SM );
	RKH_FILTER_OFF_SMA( my );

	rkh_fwk_init();
	RKH_TRC_OPEN();

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
	RKH_TR_FWK_OBJ( &CH );
	RKH_TR_FWK_OBJ( &DH );
	RKH_TR_FWK_OBJ( &H );

	RKH_TR_FWK_SIG( ZERO );
	RKH_TR_FWK_SIG( ONE	);
	RKH_TR_FWK_SIG( TWO	);
	RKH_TR_FWK_SIG( THREE );
	RKH_TR_FWK_SIG( FOUR );
	RKH_TR_FWK_SIG( FIVE );
	RKH_TR_FWK_SIG( SIX	);
	RKH_TR_FWK_SIG( TERM );

	RKH_TR_FWK_TUSR( MY_TRACE );

	RKH_TRC_USR_BEGIN( MY_TRACE )
		RKH_TUSR_I8( 3, d1 );
		RKH_TUSR_UI8( 3, d1 );
		RKH_TUSR_I16( 4, d2 );
		RKH_TUSR_UI16( 4, d2 );
		RKH_TUSR_I32( 5, d3 );
		RKH_TUSR_UI32( 5, d3 );
		RKH_TUSR_X32( 4, d3 );
		RKH_TUSR_STR( str );
		RKH_TUSR_MEM( (rui8_t*)&d3, sizeof(rui32_t) );
		RKH_TUSR_OBJ( my );
		RKH_TUSR_FUN( main );
		RKH_TUSR_SIG( ZERO );
	RKH_TRC_USR_END();

	RKH_SMA_ACTIVATE( my, qsto, QSTO_SIZE, 0, 0 );
	rkh_fwk_enter();

	RKH_TRC_CLOSE();
	return 0;
}
