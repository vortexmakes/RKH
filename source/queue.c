/*
 * 	queue.c
 */


#include "mytypes.h"
#include "queue.h"
#include "qdata.h"
#include "rksys.h"
#include "task.h"
#include "schdr.h"

#include <string.h>


#if RKSYS_QUEUE


#if RKSYS_QUEUE_GET_INFO
	#define info_insert( pq )		++pq->qinfo.inserts
	#define info_remove( pq )		++pq->qinfo.removes
	#define info_empty( pq )		++pq->qinfo.empty
	#define info_full( pq )			++pq->qinfo.full
#else
	#define info_insert( pq )
	#define info_remove( pq )
	#define info_empty( pq )
	#define info_full( pq )
#endif


static
QUEUE_T *
verify_queue( QD_T qd )
{
	return &queues[ qd ];
}


NUM_ELEM_QUEUE_T 
queue_is_empty( QD_T qd )
{
	QUEUE_T *p;
	
	rkassert( qd < RKSYS_QUEUE_NUM_QUEUES, RKSYS_QUEUE_IE_FAILED );
	p = verify_queue( qd );
	
	return p->qty;
}


MUInt 
queue_remove( QD_T qd, void *pelem )
{
	QUEUE_T *p;

	rkassert( 	qd < RKSYS_QUEUE_NUM_QUEUES &&
				pelem != NULL, RKSYS_QUEUE_REM_FAILED );

	p = verify_queue( qd );

	if( p->qty == 0 )
	{
		info_empty( p );
		return QUEUE_EMPTY;
	}

	enter_critical();

	memcpy( pelem, p->pout, p->elem_size );

	if( ( p->pout += p->elem_size ) >= p->ptail )
		p->pout = p->parray;

	--p->qty;
	info_remove( p );

	exit_critical();

	rktrace_remove_queue( qd );
	return QUEUE_OK;
}


MUInt 
queue_insert( QD_T qd, const void *pelem )
{
	QUEUE_T *p;

	rkassert( 	qd < RKSYS_QUEUE_NUM_QUEUES &&
				pelem != NULL, RKSYS_QUEUE_INS_FAILED );

	p = verify_queue( qd );

	enter_critical();

	if( p->qty >= p->num_elems )
	{
		info_full( p );
		exit_critical();
		return QUEUE_FULL;
	}

	if( p->sched == RKSYS_QUEUE_SCHEDULABLE && task_set_task_ready( p->task ) )
	{
		exit_critical();
		return QUEUE_OK;
	}

	set_pend_event();

	memcpy( p->pin, pelem, p->elem_size );

	if( ( p->pin += p->elem_size ) >= p->ptail )
		p->pin = p->parray;

	++p->qty;
	info_insert( p );

	exit_critical();

	rktrace_insert_queue( qd );
	return QUEUE_OK;
}


void 
queue_deplete( QD_T qd )
{
	QUEUE_T *p;

	p = verify_queue( qd );

	enter_critical();

	p->qty = 0;
	p->pin = p->pout = p->parray;
	
	exit_critical();
	rktrace_deplete_queue( qd );
}


#if RKSYS_QUEUE_READ

MUInt 
queue_read( QD_T qd, void *pelem )
{
	QUEUE_T *p;

	rkassert( 	qd < RKSYS_QUEUE_NUM_QUEUES &&
				pelem != NULL, RKSYS_QUEUE_READ_FAILED );

	p = verify_queue( qd );

	if( p->qty == 0 )
		return QUEUE_EMPTY;

	enter_critical();

	memcpy( pelem, p->pout, p->elem_size );

	exit_critical();

	rktrace_read_queue( qd );
	return QUEUE_OK;
}

#endif


#if RKSYS_QUEUE_REASSIGN

void 
queue_reassign( QD_T qd, MUInt td, uchar es, NUM_ELEM_QUEUE_T ne )
{
	QUEUE_T *p;

	rkassert( qd < RKSYS_QUEUE_NUM_QUEUES, RKSYS_QUEUE_REASSIGN_FAILED );
	p = verify_queue( qd );
	
	enter_critical();

	p->task = task_identify( td );
	p->elem_size = es;
	p->num_elems = ne;
	p->qty = 0;

	exit_critical();
	rktrace_reassign_queue( qd, td );
}

#endif


#if RKSYS_QUEUE_GET_INFO

void 
queue_clear_info( QD_T qd )
{
	QUEUE_T *p;
	QUEUE_INFO_T *q;

	p = verify_queue( qd );
	q = &p->qinfo;

	enter_critical();
	q->inserts = q->removes = q->empty = q->full = 0;
	exit_critical();
}


void 
queue_get_info( QD_T qd, QUEUE_INFO_T *pqi )
{
	QUEUE_T *p;

	p = verify_queue( qd );

	enter_critical();
	*pqi = p->qinfo;
	exit_critical();
}

#endif


#endif
