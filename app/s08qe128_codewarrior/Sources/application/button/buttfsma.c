/*
 * 	buttfsma.c
 */


#include "mytypes.h"
#include "rksys.h"
#include "event.h"
#include "evtdata.h"
#include "fsm.h"
#include "fsmdata.h"
#include "buttfsm.h"
#include "buttfsma.h"
#include "rkutils.h"
#include "queue.h"
#include "qdata.h"
#include "sigdata.h"


void
buttfsm_init( void )
{
}


void 
set_leds( EVT_T *pevt )
{
}


void 
set_leds0( EVT_T *pevt )
{
}


void 
set_leds1( EVT_T *pevt )
{
}


void 
go_back_state1( EVT_T *pevt )
{
	set_leds( pevt );
	fsm_set_history( pevt->tgt, &st1 );
}


void 
go_back_state2( EVT_T *pevt )
{
	set_leds( pevt );
	fsm_set_history( pevt->tgt, &st2 );
}


void
system_crash( EVT_T *pevt )
{
	uchar signo;

	signo = SIG1;
	queue_insert( SIGNAL_QUEUE, &signo );
}


uchar
check_super_state( void )
{
#if 0
	if( fsm_get_current_state_id( BUTTFSM ) == SSTATE0 )
		return SSTATE0_COND;
#endif
	return SSTATE0_COND;
}
