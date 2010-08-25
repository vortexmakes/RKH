/*
 * log.c
 */


#include "mytypes.h"
#include "task.h"
#include "event.h"
#include "evtdata.h"
#include "tdata.h"
#include "rksys.h"
#include "log.h"
#include "rkutils.h"
#include "stimers.h"
#include "eflag.h"
#include "reset.h"
#include "ioports.h"
#include "sigdata.h"

#include <stdlib.h>


#define LOG_LED_EVENT				0x01
#define BUTTON2_LED_EVENT			0x02


static void log_init( void );
static void log_kill_request( void );
static void log_task( SCHDR_MSG_T *pmsg );


CREATE_TCB(	log, log_task, NULL, log_init, 2, 3, LOG, "log", 
				log_kill_request );


static TIM_T logt;
EFD_T logef;


static
void
log_timeout( void )
{
	eflag_set_flags( logef, LOG_LED_EVENT, FLAG_SET );
}


static
void 
log_kill_request( void )
{
	stimer_kill( logt );
}


static
void 
log_init( void )
{
	logt = stimer_assign( RETRIG, log_timeout );
	logef = eflag_assign( log );
	stimer_kick( logt, rktick_ms( 100 ) );
	eflag_set_wait_flags( logef, FLAG_WAIT_SET_ANY, LOG_LED_EVENT |
													BUTTON2_LED_EVENT );
}


static
void
log_task( SCHDR_MSG_T *pmsg )
{
	FLAGS_T flags;
	uchar signo;

	rkwatchdog();
	switch( get_event_type( pmsg ) )
	{
		case EVENT_EFLAG_TYPE:
			flags = get_flags( pmsg );

			if( flags & LOG_LED_EVENT )
				LED1 ^= 1;
			if( flags & BUTTON2_LED_EVENT )
				LED6 ^= 1;
			break;
		case EVENT_SIGNAL_TYPE:
			LED7 ^= 1;
			signo = get_signal( pmsg );
			dprint(( COM1, "log task: catch signal %d\n", signo ) );

			if( signo == SIG1 )
				rkreset();

			break;
	}
}
