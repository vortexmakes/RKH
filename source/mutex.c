/*
 * 	mutex.c
 */


#include "mytypes.h"
#include "rksys.h"
#include "mutex.h"
#include "task.h"
#include <stdlib.h>


#if RKSYS_MUTEX

/* 
 * 	Max. number of task per mutex 
 */

#define RKSYS_MUTEX_TASK_PER_MUTEX		RKSYS_TASK_NUM_TASKS

#define mutex_delete_task( pm, pty )				\
													\
								mutex_insert_task((pm),(pty),NULL)


enum
{
	RKSYS_MUTEX_UNLOCKED, RKSYS_MUTEX_LOCKED
};


enum
{
	MUTEX_USED, MUTEX_FREE
};


#if RKSYS_MUTEX_GET_INFO
	#define info_take( pm )			++pm->minfo.takes
	#define info_give( pm )			++pm->minfo.gives
	#define info_unlink( pm )		++pm->minfo.unlinks
#else
	#define info_take( pm )
	#define info_give( pm )
	#define info_unlink( pm )
#endif


typedef struct
{
	unsigned state:1;	/*	the states of a mutex are locked or unlocked */
	unsigned used:1;	/* 	free or used mutex task control block */
	TASK_T *owner;		/*	points to owning task's pointer */
	TASK_T *waitlist[ RKSYS_MUTEX_TASK_PER_MUTEX ];	/* the tasks that waiting
													 * for an unavailable 
													 * mutex are placed in 
													 * this list in highest 
													 * priority first order
													 */
#if RKSYS_MUTEX_GET_INFO
	MUTEX_INFO_T minfo;			/* performance information */
#endif
} MUTEX_T;


static MUTEX_T mutexs[ RKSYS_MUTEX_NUM_MUTEX ];


static
MUTEX_T *
mutex_verify( MTXD_T mtxd )
{
	MUTEX_T *pm;

	if( mtxd == RKSYS_MUTEX_EMPTY )		/* mutex not assigned */
		return NULL;
	
	pm = &mutexs[ mtxd ];

	if( pm->used != MUTEX_USED )		/* mutex not created */
		return NULL;

	return pm;
}


static
void
mutex_insert_task( MUTEX_T *pm, uchar pty, TASK_T *pt )
{
	pm->waitlist[ pty ] = pt;
}


static
TASK_T *
mutex_find_waiting_task( MUTEX_T *pm )
{
	uchar mix;
	TASK_T **pt, *t;

	for( pt = pm->waitlist, mix = 0; 
			mix < RKSYS_MUTEX_TASK_PER_MUTEX && ( t = *pt ) == NULL; 
			++mix, ++pt )
		;

	return t;
}


uchar
mutex_take( MTXD_T mtxd, TASK_T *pt )
{
	MUTEX_T *pm;

	rkassert( mtxd < RKSYS_MUTEX_NUM_MUTEX, RKSYS_MUTEX_TAKE_FAILED );

	if( ( pm = mutex_verify( mtxd ) ) == NULL )
		return MUTEX_ERROR;

	if( pm->state == RKSYS_MUTEX_LOCKED )
	{
		if( pm->owner != pt )
		{
			mutex_insert_task( pm, pt->pftask->pty, pt );
			pt->mtxd = mtxd;
		}
		rktrace_take_mutex( mtxd, pt->pftask->id, pm->state );
		return MUTEX_NOT_AVAILABLE;
	}

	pm->state = RKSYS_MUTEX_LOCKED;
	pm->owner = pt;
	mutex_delete_task( pm, pt->pftask->pty );
	pt->mtxd = mtxd;

	info_take( pm );
	rktrace_take_mutex( mtxd, pt->pftask->id, pm->state );

	return MUTEX_OK;
}


void
mutex_give( TASK_T *pt )
{
	MUTEX_T *pm;
	TASK_T *pwt;

	rkassert( 	pt != NULL	&&
				pt->mtxd < RKSYS_MUTEX_NUM_MUTEX, RKSYS_MUTEX_GIVE_FAILED );

	if( ( pm = mutex_verify( pt->mtxd ) ) == NULL )
		return;

	if( pm->owner == pt )
	{
		pm->state = RKSYS_MUTEX_UNLOCKED;
		pm->owner = NULL;
		pt->mtxd = RKSYS_MUTEX_EMPTY;
		if( ( pwt = mutex_find_waiting_task( pm ) ) != NULL )
			task_set_task_ready( pwt );

		info_give( pm );
		rktrace_give_mutex( pm->mtxd, pt->pftask->id, pm->state );
	}
}


uchar
mutex_check( TASK_T *pt )
{	
	MUTEX_T *pm;

	if( ( pm = mutex_verify( pt->mtxd ) ) == NULL )
		return 0;
	
	return pm->state == RKSYS_MUTEX_UNLOCKED;
}


#if RKSYS_MUTEX_UNLINK

void
mutex_unlink( TASK_T *pt )
{
	MUTEX_T *pm;

	rkassert( 	pt != NULL	&&
				pt->mtxd < RKSYS_MUTEX_NUM_MUTEX, RKSYS_MUTEX_ULINK_FAILED );

	if( ( pm = mutex_verify( pt->mtxd ) ) == NULL )
		return;

	mutex_give( pt );
	pt->mtxd = RKSYS_MUTEX_EMPTY;
	mutex_delete_task( pm, pt->pftask->pty );

	info_unlink( pm );
	rktrace_unlink_mutex( pm->mtxd, pt->pftask->id, pm->state );
}

#endif


#if RKSYS_MUTEX_CREATE

MTXD_T
mutex_create( void )
{
	MUTEX_T *p;
	uchar mix;

	for( mix = 0, p = sems; mix < RKSYS_MUTEX_NUM_MUTEX; ++mix, ++p )
		if( p->used != MUTEX_USED )
		{
			p->used = MUTEX_USED;
			p->owner = NULL;
			p->state = RKSYS_MUTEX_UNLOCKED;
			rktrace_create_mutex( mtxd );
			return mix;
		}

	rkassert( mix < RKSYS_MUTEX_NUM_MUTEX, RKSYS_MUTEX_CREATE_FAILED );

	return RKSYS_MUTEX_NO_ROOM;
}

#endif


#if RKSYS_MUTEX_FREE

void
mutex_free( MTXD_T mtxd )
{
	MUTEX_T *pm;

	rkassert( mtxd < RKSYS_MUTEX_NUM_MUTEX, RKSYS_MUTEX_FREE_FAILED );

	if( ( pm = mutex_verify( mtxd ) ) == NULL )
		return;

	pm->used = MUTEX_FREE;
	rktrace_free_mutex( mtxd );
}

#endif


#if RKSYS_MUTEX_GET_WAIT_TASK

TASK_T **
mutex_get_wait_task( MTXD_T mtxd )
{
	MUTEX_T *pm;

	rkassert( mtxd < RKSYS_MUTEX_NUM_MUTEX, RKSYS_MUTEX_GWAIT_FAILED );

	if( ( pm = mutex_verify( mtxd ) ) == NULL )
		return NULL;
	
	return pm->waitlist;
}

#endif


#if RKSYS_MUTEX_GET_INFO

void 
mutex_clear_info( MTXD_T mtxd )
{
	MUTEX_T *pm;
	QUEUE_INFO_T *q;

	pm = mutex_verify( mtxd );
	q = &pm->minfo;

	enter_critical();
	q->takes = q->gives = q->unlinks = 0;
	exit_critical();
}


void 
mutex_get_info( MTXD_T mtxd, MUTEX_INFO_T *pmi )
{
	MUTEX_T *pm;

	pm = mutex_verify( mtxd );

	enter_critical();
	*pmi = pm->minfo;
	exit_critical();
}

#endif


#endif
