/**
 * 	\file		oskdep
 * 	\ingroup 	prt
 *
 * 	\brief 		Osek Task - RKH State Machine Apps vinculation
 */

#include "rkh.h"
#include "bky.h"
#include "bsp.h"


const SMA_TASK_TBL_T rkh_sma_task_tbl[] =
{
	{ RKH_SMA(blinky), BlinkyTask },
	{ NULL }
};


TASK( BlinkyTask )
{
	RKH_TASK_FUNCTION( blinky );
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
