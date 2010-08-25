/*
 * sigdata.c
 */


#include "mytypes.h"
#include "rksys.h"
#include "signal.h"
#include "rkutils.h"
#include "task.h"
#include "tdata.h"
#include <stdlib.h>

#include "button.h"


#if RKSYS_SIGNAL


static void sys_catch_sig0( void );
static void sys_catch_sig1( void );


/* 	Defines the system's signals */

SIG_TASK_TABLE( sig0 ) = { task_take( LOG ), END_SIG_TASK_TABLE };
SIG_TASK_TABLE( sig1 ) = { task_take( LOG ), END_SIG_TASK_TABLE };


/*
 *	Register of signals. Any task intending to catch a signal as event 
 *	must first create a signal structure into signals register. Therefore, 
 *	each element of that must be defined by means 'DEFINE_SYSTEM_SIGNAL' 
 *	macro. The signal numbers are defined into 'rksys.h' file.
 */

CREATE_SYSTEM_SIG_REGISTER
{
	DEFINE_SYSTEM_SIGNAL( sig0, sys_catch_sig0 ),
	DEFINE_SYSTEM_SIGNAL( sig1, sys_catch_sig1 )
};


/* 	Defines system's signals handler */

static
void
sys_catch_sig0( void )
{
	dprint(( COM1, "System catch signal 0\n" ) );
}


static
void
sys_catch_sig1( void )
{
	dprint(( COM1, "System catch signal 1\n" ) );
}


#endif
