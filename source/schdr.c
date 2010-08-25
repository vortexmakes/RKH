/*
 * schdr.c
 */



#include "mytypes.h"
#include <stdlib.h>

#include "rksys.h"
#include "queue.h"
#include "qdata.h"
#include "event.h"
#include "fsm.h"
#include "task.h"
#include "tdata.h"
#include "signal.h"
#include "sigdata.h"
#include "eflag.h"
#include "schdr.h"
#include "evtdata.h"
#include "stimers.h"
#include "rkutils.h"
#include "ioports.h"
#include "mutex.h"


#define is_last_queue(x)			((*x)!=EMPTY_QUEUE_SLOT)
#define get_high_pty_task()			rl_head->next->pt
#define is_empty_ready_list()		rl_head->next == NULL
#define READY_LIST_HEADER			&ready_list[ 0 ]
#define forever						while(1)


/*
 * 	Access macro to determine if the ready list contains any TCB. The macro 
 * 	will only have the value true if the list is empty.
 */

#define is_empty_ready_list()		rl_head->next == NULL


enum
{
	DISPATCHED, NOT_DISPATCHED
};


enum
{
	TASK_NOT_AVAILABLE, TASK_READY
};


#if RKSYS_SIGNAL && RKSYS_QUEUE

CREATE_QUEUE_ARRAY( signal_queue, RKSYS_SIGNAL_QUEUE_SIZE * sizeof( uchar ) );
extern const SIG_T signals[ RKSYS_SIGNAL_NUM_SIGNALS ];

#endif


RL_NODE_T ready_list[ RKSYS_TASK_NUM_PTY_LEVEL + 1 ];
static SCHDR_MSG_T msg;
static const FIXED_TASK_T *pft;
static TASK_T *pht;
static RL_NODE_T *rl_head = READY_LIST_HEADER;

#if RKSYS_IDLE_TASK
static void (*pitask)( void );
#endif

#if RKSYS_TASK_RUNTIME_STATS
extern uchar runtime_tracing;
#endif

uchar pending_events;


#if RKSYS_IDLE_TASK

#define to_idle_task() 					\
{										\
	rkwatchdog();						\
	enter_critical();					\
										\
	if( pending_events )				\
	{									\
		exit_critical();				\
	}									\
	else								\
	{									\
		exit_critical();				\
		if( pitask != NULL )			\
			(*pitask)();				\
	}									\
}
#else

#define to_idle_task()					\
{										\
	rkwatchdog();						\
}

#endif


uchar
ready_list_find( uchar task_pty )
{
	RL_NODE_T *p, *q;

	for( p = rl_head; ( q = p->next ) != NULL && q->pty != task_pty; 
			p = q )
		;
	return q != NULL;
}


void
ready_list_insert( RL_NODE_T *pn )
{
	RL_NODE_T *p, *q;
	uchar pty;

	for( p = rl_head; ( q = p->next ) != NULL && 
							( pty = q->pty ) <= pn->pty; p = q )
		if( pty == pn->pty )
			return;

	enter_critical();

	pn->next = q;
	p->next = pn;

	exit_critical();
}


void
ready_list_remove( uchar task_pty )
{
	RL_NODE_T *p, *q;

	for( p = rl_head; ( q = p->next ) != NULL && 
			q->pty != task_pty; p = q )
		;

	if( q != NULL )
	{
		enter_critical();
		p->next = q->next;
		exit_critical();
	}
}


static
void
ready_list_init( void )
{
	RL_NODE_T *p;
	uchar ix;

	for( ix = 0, p = rl_head + 1; ix < RKSYS_TASK_NUM_PTY_LEVEL; ++p, ++ix )
		p->pty = ix;
}


static
void
do_dispatch( void )
{
#if RKSYS_RUNTIME_COUNTER == 1 && RKSYS_STATS_EXEC_TASKS == 1
	static RTCOUNTER_T start_time, end_time, exec_time;
	start_time = rkget_exec_time();
#endif
	
	(*pft->prcbf)( &msg );

#if RKSYS_RUNTIME_COUNTER == 1 && RKSYS_STATS_EXEC_TASKS == 1
	end_time = rkget_exec_time();
#endif

#if RKSYS_RUNTIME_COUNTER == 1 && RKSYS_STATS_EXEC_TASKS == 1
	if( runtime_tracing )
	{
		if( ( exec_time = end_time - start_time ) > 0 )
			pht->totexec_time += exec_time;
		++pht->exec_counter;
	}
#endif

	rktrace_dispatch_task( pft->id, msg.type, msg.evt.info );
}


#if RKSYS_SIGNAL && RKSYS_QUEUE

static
void
dispatch_signal( void )
{
	const TASK_T * const *pt;
	const SIG_T *ps;
	uchar signo;

	while( queue_remove( SIGNAL_QUEUE, &signo ) == QUEUE_OK )
	{
		ps = &signals[ signo ];

		for( pt = ps->psvect; *pt != END_SIG_TASK_TABLE; ++pt )
			if( is_rtor_events( (*pt)->task_state ) )
			{
				pft = (*pt)->pftask;
				msg.evt.signo = signo;
				msg.type = EVENT_SIGNAL_TYPE;
				msg.pt = (TASK_T*)pt;
				do_dispatch();
			}

		if( ps->pdsh != NULL )
			(*ps->pdsh)();
	}
}

#else

#define dispatch_signal()

#endif


static
uchar
dispatch_events( void )
{
	do_dispatch();
	
	/* Checks than current task is ready to process events */
	return is_rtor_events( pht->task_state );
}


static
MUInt
dispatcher( void )
{
	const MUInt *pq;
	uchar remain_events;

	/* Checks than current task is ready to process events */

#if RKSYS_TASK_RESUME
{
	enter_critical();

	if( !is_rtor_events( pht->task_state ) )
	{
		exit_critical();
		return NOT_DISPATCHED;
	}

	exit_critical();
}
#endif

	/* 
	 * Takes assigned task from current slot and deallocates temporarily 
	 * current task from priority list 
	 */

	pft = pht->pftask;
	ready_list_remove( pft->pty );
	msg.pt = pht;

#if RKSYS_EFLAG && RKSYS_EFLAG_NUM_REGS > 0
{
	if( eflag_check_condition( pht->efd, &msg.evt.flags ) )
	{
		msg.type = EVENT_EFLAG_TYPE;
		
		if( dispatch_events() == TASK_NOT_AVAILABLE )
			return DISPATCHED;
	}
}
#endif

#if RKSYS_MUTEX && RKSYS_MUTEX_NUM_MUTEX > 0
{
	if( mutex_check( pht ) )
	{
		msg.type = EVENT_MUTEX_TYPE;
		msg.evt.mtxd = pht->mtxd;
		
		if( dispatch_events() == TASK_NOT_AVAILABLE )
			return DISPATCHED;
	}
}
#endif

	/* Travers task's queues list and dispatchs one event for queue */

#if RKSYS_QUEUE
{
	#if RKSYS_TASK_QUEUE_LIST
		if( ( pq = pft->pqlist ) != NULL )
			for( ; is_last_queue( pq ); ++pq )
	#else
		if( ( pq = pft->pqlist ) != NULL )
	#endif
				if( ( remain_events = queue_is_empty( *pq ) ) != 0 )
				{
					if( remain_events > 1 )
					{
						set_pend_event();
						ready_list_insert( pft->pty_node );
					}

					msg.evt.qd = *pq;
					msg.type = EVENT_QUEUE_TYPE;
	
					if( dispatch_events() == TASK_NOT_AVAILABLE )
						return DISPATCHED;
				}
}
#endif

	/* 
	 * If current task is not assigned in the priority list its 
	 * state is moved to blocked.
	 */

	enter_critical();

	if( ready_list_find( pft->pty ) == 0 )
		pht->task_state = RKSYS_TASK_BLOCKED;

	exit_critical();

	return DISPATCHED; 
}


void
scheduler( void )
{
	forever
	{
		dispatch_signal();
		reset_pend_event();

		do
		{
			if( is_empty_ready_list() )
				break;

			pht = get_high_pty_task();
			dispatch_signal();
			dispatcher();
		}
		forever;
		to_idle_task();
	}
}


void 
scheduler_init( void (*pidle_task)( void ) )
{
#if RKSYS_IDLE_TASK
	pitask = pidle_task;
#endif
	rkinit_exec_time();
	ready_list_init();
}
