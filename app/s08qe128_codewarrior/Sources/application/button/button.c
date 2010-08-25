/*
 * 	button.c
 */


#include "mytypes.h"
#include "task.h"
#include "event.h"
#include "evtdata.h"
#include "qdata.h"
#include "tdata.h"
#include "queue.h"
#include "stimers.h"
#include "rksys.h"
#include "rkutils.h"
#include "signal.h"
#include "fsm.h"
#include "fsmdata.h"
#include "button.h"

#include <stdlib.h>


static void button_init( void );
static void button_task( SCHDR_MSG_T *pmsg );


CREATE_QUEUE_ARRAY( button_queue, BUTTON_QUEUE_BYTE_SIZE );
static CREATE_QUEUE_LIST( button ) = { BUTTON_QUEUE, END_QUEUE_LIST };
CREATE_TCB(	button,	button_task, task_set_que_list( button ), 
				button_init, 0, 2, BUTTON, "butt", NULL );


static
void 
button_init( void )
{
	fsm_init( BUTTFSM );
}


static
void
button_task( SCHDR_MSG_T *pmsg )
{
	EVT_T event;

	rkwatchdog();
	queue_remove( get_queue( pmsg ), &event );
	fsm_engine( BUTTFSM, &event );
}
