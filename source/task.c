/*
 *	task.c
 */


#include "task.h"
#include "tdata.h"
#include "queue.h"
#include "qdata.h"
#include "event.h"
#include "rksys.h"
#include "schdr.h"
#include "sigdata.h"
#include "eflag.h"
#include "mutex.h"
#include "rkutils.h"

#include "mytypes.h"
#include <stdlib.h>


#define is_last_queue(x)		((*x)!=EMPTY_QUEUE_SLOT)


TASK_T tasks[ RKSYS_TASK_NUM_TASKS ];


TASK_T *
task_identify( TD_T td )
{
	rkassert( td < RKSYS_TASK_NUM_TASKS, RKSYS_ASSERT_NUM_ERRORS );
	return &tasks[ td ];
}


uchar
task_set_task_ready( TASK_T *pt )
{
	rkassert( pt != NULL, RKSYS_TASK_STR_FAILED );

	if( is_rtor_events( pt->task_state ) )
	{
		ready_list_insert( pt->pftask->pty_node );
		pt->task_state = RKSYS_TASK_READY;
		set_pend_event();

		rktrace_task_ready( pt->pftask->id );
		return 0;
	}
	return 1;
}


void 
task_init( TASK_T *pt, const FIXED_TASK_T *pft, MUInt ts )
{
	rkassert( 	pt != NULL 	&& 
				pft != NULL && 
				ts < RKSYS_TASK_NUM_STATES, RKSYS_TASK_INIT_FAILED );

	enter_critical();

	pt->pftask = pft;
	pt->task_state = ts;
	pt->efd = FLAG_EMPTY_EFREG;
	pt->mtxd = RKSYS_MUTEX_EMPTY;
	pft->pty_node->pt = pt;

	exit_critical();

	task_deplete_queues( pt );

	if( pft->ptinit != NULL )
		(*pft->ptinit)();
	
	rktrace_create_task( pt->pftask->id );
}


#if RKSYS_TASK_RESUME

uchar
task_resume( TASK_T *pt )
{
	rkassert( pt != NULL, RKSYS_TASK_RESUME_FAILED );

	enter_critical();

	if( pt->task_state == RKSYS_TASK_SUSPEND )
	{
		pt->task_state = RKSYS_TASK_BLOCKED;
		exit_critical();

		if( pt->pftask->ptinit != NULL )
			(*pt->pftask->ptinit)();

		rktrace_resume_task( pt->pftask->id );
		return 0;
	}
	else
		exit_critical();

	return 1;
}

#endif


#if RKSYS_TASK_RESUME

uchar
task_kill_suspend( TASK_T *pt, MUInt tstate )
{
	rkassert( 	pt != NULL &&
				tstate < RKSYS_TASK_NUM_STATES, RKSYS_TASK_KSUSP_FAILED );

	enter_critical();

	if( pt->task_state != tstate )
	{
		pt->task_state = tstate;
		ready_list_remove( pt->pftask->pty );

		if( tstate == RKSYS_TASK_ZOMBIE )
		{
			pt->efd = FLAG_EMPTY_EFREG;
			if( pt->pftask->pk != NULL )
				(*pt->pftask->pk)();
		}

		exit_critical();
		task_deplete_queues( pt );
		rktrace_kill_suspend_task( pt->pftask->id, tstate );
		return 0;
	}
	else
		exit_critical();

	return 1;
}

#endif


void 
task_deplete_queues( TASK_T *pt )
{
	const MUInt *pq;

	rkassert( pt != NULL, RKSYS_TASK_DQUEUES_FAILED );

	if( ( pq = pt->pftask->pqlist ) != NULL )
#if RKSYS_TASK_QUEUE_LIST
		for( ; is_last_queue( pq ); ++pq )
#endif
			queue_deplete( *pq );

	rktrace_deplete_task_queues( pt->pftask->id );
}
