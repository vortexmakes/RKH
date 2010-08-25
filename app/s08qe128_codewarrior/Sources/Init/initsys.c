/*
 * 	initsys.c
 */


/*---- Hardware module includes ----*/

#include <stdlib.h>
#include "drivers.h"
#include "initsys.h"
#include "rksys.h"


/*---- Software module includes ----*/

#include "task.h"
#include "schdr.h"
#include "button.h"
#include "shell.h"
#include "log.h"
#include "stat.h"
#include "idle.h"


void
init_system( void )
{
	/*---- Hardware initialization ----*/
	
	drivers_init();

	/*---- Software initialization ----*/

	rktrace_init();
	rktrace_sys_start();

	task_create( button, RKSYS_TASK_BLOCKED );
	task_create( shell, RKSYS_TASK_BLOCKED );
	task_create( log, RKSYS_TASK_BLOCKED );

#if RKSYS_TASK_RUNTIME_STATS
{
	task_create( stat, RKSYS_TASK_BLOCKED );
}
#endif

	scheduler_init( idle_task );	
	rkenable_interrupt();
}
