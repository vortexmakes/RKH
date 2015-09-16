/**
 * 	\file		oskshrd
 * 	\ingroup 	prt
 *
 * 	\brief 		Osek Task - RKH State Machine Apps vinculation
 */

#include "rkh.h"
#include "svr.h"
#include "cli.h"
#include "bsp.h"

const SMA_TASK_TBL_T rkh_sma_task_tbl[] =
{
	{ RKH_SMA(svr),	 ServerTask },
	{ RKH_SMA(cli0), Cli0Task },
	{ RKH_SMA(cli1), Cli1Task },
	{ RKH_SMA(cli2), Cli2Task },
	{ NULL }
};


TASK( ServerTask )
{
	RKH_TASK_FUNCTION( svr );
}


TASK( Cli0Task )
{
	RKH_TASK_FUNCTION( cli0 );
}


TASK( Cli1Task )
{
	RKH_TASK_FUNCTION( cli1 );
}


TASK( Cli2Task )
{
	RKH_TASK_FUNCTION( cli2 );
}



TASK( RkhTraceTask )
{
#if RKH_CFG_TRC_EN == 1	
	while( trace_open )
		RKH_TRC_FLUSH();
#endif

	TerminateTask();
}


/** \brief Error Hook function
 *
 * This fucntion is called from the os if an os interface (API) returns an
 * error. Is for debugging proposes. If called this function triggers a
 * ShutdownOs which ends in a while(1).
 *
 * The values:
 *    OSErrorGetServiceId
 *    OSErrorGetParam1
 *    OSErrorGetParam2
 *    OSErrorGetParam3
 *    OSErrorGetRet
 *
 * will provide you the interface, the input parameters and the returned value.
 * For more details see the OSEK specification:
 * http://portal.osek-vdx.org/files/pdf/specs/os223.pdf
 *
 */
void
ErrorHook( void )
{
   ciaaPOSIX_printf("ErrorHook was called\n");
   ciaaPOSIX_printf("Service: %d, P1: %d, P2: %d, P3: %d, RET: %d\n",
		   OSErrorGetServiceId(), OSErrorGetParam1(), OSErrorGetParam2(), 
		   OSErrorGetParam3(), OSErrorGetRet());
   ShutdownOS(0);
}
