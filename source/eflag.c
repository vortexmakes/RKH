/*
 * eflag.c
 */


#include "mytypes.h"
#include "rksys.h"
#include "eflag.h"
#include "task.h"
#include "schdr.h"
#include "rkutils.h"


enum
{
	FREE, USED
};


typedef struct
{
	unsigned used:1;		/* 	free or used event flag register */
	unsigned type:3;		/* 	event flag register type */
	unsigned pend:1;		/* 	indicates a pending satisfied condition */
	FLAGS_T flags;			/* 	series of flags (bits) that holds the current
						 	*	status of events 
						 	*/
	FLAGS_T mask;			/* 	bit pattern indicating which bit(s) or flag(s) 
						 	*	wish to check 
						 	*/
	TASK_T *ptask;			/* points to assigned task */
#if RKSYS_EFLAG_GET_INFO
	EFLAG_INFO_T efinfo;	/* performance information */
#endif
} EFLAG_REG_T;


#if RKSYS_EFLAG && RKSYS_EFLAG_NUM_REGS != 0


static EFLAG_REG_T eflag_regs[ RKSYS_EFLAG_NUM_REGS ];


#define ready_task()				\
{									\
	check = p->pend = 1;			\
	task_set_task_ready( p->ptask );		\
}


#if RKSYS_EFLAG_GET_INFO
	#define info_set( p )			++p->efinfo.sets
	#define info_get( p )			++p->efinfo.gets
#else
	#define info_set( p )
	#define info_get( p )
#endif


static
EFLAG_REG_T *
eflag_verify( EFD_T efd )
{
	return &eflag_regs[ efd ];
}


EFD_T 
eflag_assign( TASK_T *ptask )
{
	EFLAG_REG_T *p;
	MUInt efix;

	rkassert( ptask != NULL, RKSYS_EFLAG_ASSIGN_FAILED );

	for( efix = 0, p = eflag_regs; efix < RKSYS_EFLAG_NUM_REGS; ++p, ++efix )
		if( p->used != USED )
		{
			p->used = USED;
			p->pend = p->flags = 0;
			p->ptask = ptask;
			rktrace_assign_efr( efix, ptask->pftask->id );
			return ptask->efd = efix;
		}

	rkassert( 0, RKSYS_EFLAG_ASSIGN_FAILED );
	return -EFLAG_NO_ROOM;
}


#if RKSYS_EFLAG_REASSIGN

void 
eflag_reassign( EFD_T efd, TASK_T *ptask )
{
	EFLAG_REG_T *p;
	
	rkassert( ptask != NULL, RKSYS_EFLAG_REASSIGN_FAILED );
	rkassert( efd < RKSYS_EFLAG_NUM_REGS, RKSYS_EFLAG_REASSIGN_FAILED );

	p = eflag_verify( efd );
	rkassert( p->used == USED, RKSYS_EFLAG_REASSIGN_FAILED );

	enter_critical();

	p->flags = p->pend = 0;
	p->ptask->efd = FLAG_EMPTY_EFREG;
	p->ptask = ptask;
	ptask->efd = efd;

	exit_critical();
	rktrace_reassign_efer( efd, ptask->pftask->id );
}

#endif


#if RKSYS_EFLAG_FREE

void 
eflag_free( EFD_T efd )
{
	EFLAG_REG_T *p;
	
	rkassert( efd < RKSYS_EFLAG_NUM_REGS, RKSYS_EFLAG_FREE_FAILED );

	p = eflag_verify( efd );
	rkassert( p->used == USED, RKSYS_EFLAG_FREE_FAILED );

	enter_critical();

	p->used = FREE;
	p->ptask->efd = FLAG_EMPTY_EFREG;

	exit_critical();
	rktrace_free_efr( efd );
}

#endif


void 
eflag_set_wait_flags( EFD_T efd, uchar wait_type, FLAGS_T flags )
{
	EFLAG_REG_T *p;
	
	rkassert( 	efd < RKSYS_EFLAG_NUM_REGS 	&&
				wait_type < FLAG_WAIT_SET_ALL + 1, RKSYS_EFLAG_SWT_FAILED );

	p = eflag_verify( efd );
	rkassert( p->used == USED, RKSYS_EFLAG_SWT_FAILED );

	enter_critical();

	p->flags = p->pend = 0;
	p->type = wait_type;
	p->mask = flags;

	exit_critical();
	rktrace_set_wait_flags( efd, wait_type, flags );
}


uchar
eflag_check_condition( EFD_T efd, FLAGS_T *pflags )
{
	EFLAG_REG_T *p;
	uchar r;
	
	if( efd == FLAG_EMPTY_EFREG )
		return 0;

	p = eflag_verify( efd );

	enter_critical();

	*pflags = p->flags;
	if( ( r = p->pend ) == 1 )
		p->pend = p->flags = 0;

	exit_critical();
	
	return r;
}


uchar
eflag_set_flags( EFD_T efd, FLAGS_T flags, uchar opt )
{
	EFLAG_REG_T *p;
	FLAGS_T flags_ready;
	uchar check;
	
	rkassert( efd < RKSYS_EFLAG_NUM_REGS, RKSYS_EFLAG_SETF_FAILED );

	p = eflag_verify( efd );
	rkassert( p->used == USED, RKSYS_EFLAG_SETF_FAILED );
	check = 0;
    
	enter_critical();
	
	if( opt == FLAG_SET )
		p->flags |= flags;
	else
		p->flags &= ~flags;

	flags_ready = p->mask & p->flags;

	exit_critical();

	if( p->type == FLAG_WAIT_SET_ALL )
	{
		if( flags_ready == p->mask )
			ready_task();
	}
	else if( flags_ready != 0 )
		ready_task();

	info_set( p );
	rktrace_set_flags( efd, opt, flags );

	return check;
}


#if RKSYS_EFLAG_GET_FLAGS

FLAGS_T 
eflag_get_flags( EFD_T efd )
{
	EFLAG_REG_T *p;
	FLAGS_T flags;
	
	rkassert( efd < RKSYS_EFLAG_NUM_REGS, RKSYS_EFLAG_GETF_FAILED );

	p = eflag_verify( efd );
	rkassert( p->used == USED, RKSYS_EFLAG_GETF_FAILED );
	
	enter_critical();
	flags = p->flags;
	exit_critical();

	info_get( p );
	return flags;
}

#endif


#if RKSYS_EFLAG_GET_INFO

void 
eflag_clear_info( EFD_T efd )
{
	EFLAG_REG_T *p;
	EFLAG_INFO_T *q;

	p = eflag_verify( efd );
	q = &p->efinfo;

	enter_critical();
	q->sets = q->gets = 0;
	exit_critical();
}


void 
eflag_get_info( EFD_T efd, EFLAG_INFO_T *pefi )
{
	EFLAG_REG_T *p;

	p = eflag_verify( efd );

	enter_critical();
	*pefi = p->efinfo;
	exit_critical();
}

#endif


#endif
