/*
 * main.c
 */


#include "rkh.h"
#include "bsp.h"
#include "my.h"
#include "myevt.h"
#include "rkhdata.h"


#define QSTO_SIZE			16

static RKHEVT_T *qsto[ QSTO_SIZE ];


int
main( int argc, char *argv[] )
{
	bsp_init( argc, argv );
	rkh_init();
	
	rkh_sma_activate( my, qsto, QSTO_SIZE, ( void * )0, 0 );
	rkh_enter();

	rkh_trc_close();
	return 0;
}
