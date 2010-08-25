/*
 * stat.c
 */


#include "mytypes.h"
#include "task.h"
#include "event.h"
#include "evtdata.h"
#include "qdata.h"
#include "tdata.h"
#include "queue.h"
#include "rksys.h"
#include "stat.h"
#include "eflag.h"
#include "rkutils.h"
#include "stimers.h"
#include "ioports.h"
#include "ffile.h"

#include <stdlib.h>
#include <string.h>


#if RKSYS_TASK_RUNTIME_STATS


static void stat_init( void );
static void stat_kill_request( void );
static void stats_task( SCHDR_MSG_T *pmsg );


CREATE_TCB(	stat, stats_task, NULL, stat_init, 3,
				1, STAT, "stats", stat_kill_request );


static TIM_T statt;
static EFD_T statsef;
uchar runtime_tracing = 0;


static
void
stat_timeout( void )
{
	eflag_set_flags( statsef, 0x01, FLAG_SET );
}


static
void 
stat_kill_request( void )
{
	stimer_kill( statt );
}


static
void 
stat_init( void )
{
	statt = stimer_assign( RETRIG, stat_timeout );
	statsef = eflag_assign( stat );
	stimer_kick( statt, rktick_sec( 2 ) );
	eflag_set_wait_flags( statsef, FLAG_WAIT_SET_ALL, 0x01 );
	runtime_tracing = 1;

	/* Clear resource performance information */

#if RKSYS_TIMER_GET_INFO == 1
	stimer_clear_info( statt );
#endif

#if RKSYS_EFLAG_GET_INFO == 1
	eflag_clear_info( statsef );
#endif

#if RKSYS_QUEUE_GET_INFO == 1
	queue_clear_info( BUTTON_QUEUE );
#endif
}


/*
 * 	print_task_stats:
 *
 * 	RKSYS can optionally collect information on the amount 
 * 	of processing time that has been used by each task. This 
 * 	function can then be used to present this information in
 * 	a tabular format.
 *
 * 	Values are given for each task:
 *
 * 	1. 	Task: 			task name.
 * 	2. 	Counter: 		amount times that the task has actually been 
 * 						executing within interval RKSYS_STATS_TICK_TASK.
 * 	3. 	TotExectime: 	total time that the task has actually been 
 * 						executing within interval RKSYS_STATS_TICK_TASK.
 * 	4.	AvgExectime:	average time that the task has actually been 
 * 						executing within interval RKSYS_STATS_TICK_TASK.
 * 	5. 	Portion:		percentage of the total processing time rather
 * 						than as an absolute time.
 */

static
void
print_task_stats( void )
{
	TASK_T *ptask;
	uchar i, tasktot_exec_time;
	RTCOUNTER_T totexec;

	LED0 ^= 1;
	dprint((COM1,"\n--- Task statistics ---\n\n"));
	dprint((COM1,"Task\tCounter\tTotExectime\t\tAvgExecTime\t\tPortion\n\n"));

	for( totexec = i = 0; i < RKSYS_TASK_NUM_TASKS; ++i )
	{
		rkwatchdog();
		ptask = task_identify( i );

		if( ptask->exec_counter > 0 )
		{
			totexec += ptask->totexec_time;
			tasktot_exec_time = ptask->totexec_time/RKSYS_STATS_TOTAL_TIME;
			dprint(( COM1, "%s\t%d\t\t%u\t\t\t%u\t\t\t%d%%\n",
									ptask->pftask->ns,
									ptask->exec_counter, 
									ptask->totexec_time,
									ptask->totexec_time/ptask->exec_counter,
									tasktot_exec_time ));

			ptask->totexec_time = ptask->exec_counter = 0;
		}
		else
			dprint(( COM1, "%s\t0\t\t0\t\t\t0\t\t\t0%%\n", ptask->pftask->ns ));
	}

	tasktot_exec_time = totexec/RKSYS_STATS_TOTAL_TIME;
	totexec = totexec / (RKSYS_STATS_TICK_HZ/1000);

	dprint((COM1,"\nTotal Execution Time = %u [ms]", totexec ));
	dprint((COM1,"\nTotal Percentage = %d%%\n", tasktot_exec_time ));
}


/*
 *	print_resource_performance_info:
 *
 *	Print run-time performance metrics.
 *
 * 	Information is available during run-time for each of the RKSYS
 * 	resources. This information can be useful in determining whether
 * 	the application is performing properly, as well as helping to
 * 	optimize the application.
 */

static
void
print_resource_performance_info( void )
{
#if RKSYS_TIMER_GET_INFO == 1
	static TIMER_INFO_T ti;
#endif

#if RKSYS_EFLAG_GET_INFO == 1
	static EFLAG_INFO_T efi;
#endif

#if RKSYS_QUEUE_GET_INFO == 1
	static QUEUE_INFO_T qi;
#endif

#if RKSYS_TIMER_GET_INFO == 1 || RKSYS_EFLAG_GET_INFO == 1	\
		|| RKSYS_QUEUE_GET_INFO == 1
	dprint((COM1,"\n--- Resource performance information ---\n\n"));
#endif

#if RKSYS_TIMER_GET_INFO == 1
	stimer_get_info( statt, &ti );

	dprint(( COM1, "'statt' timer:\n\n" ));
	dprint(( COM1, "\texpirations = %d\n", ti.expirations ));
	dprint(( COM1, "\tkicks = %d\n", ti.kicks ));
	dprint(( COM1, "\tkills = %d\n", ti.kills ));
	dprint(( COM1, "\treassigns = %d\n", ti.reassigns ));
#endif

#if RKSYS_EFLAG_GET_INFO == 1
	eflag_get_info( statsef, &efi );

	dprint(( COM1, "'statsef' event flag:\n\n" ));
	dprint(( COM1, "\tsets = %d\n", efi.sets ));
	dprint(( COM1, "\tgets = %d\n", efi.gets ));
#endif

#if RKSYS_QUEUE_GET_INFO == 1
	queue_get_info( BUTTON_QUEUE, &qi );

	dprint(( COM1, "'button' queue:\n\n" ));
	dprint(( COM1, "\tinserts = %d\n", qi.inserts ));
	dprint(( COM1, "\tremoves = %d\n", qi.removes ));
	dprint(( COM1, "\tempty = %d\n", qi.empty ));
	dprint(( COM1, "\tfull = %d\n", qi.full ));
#endif
}


static
void
stats_task( SCHDR_MSG_T *pmsg )
{
	print_task_stats();
	print_resource_performance_info();
}


#endif
