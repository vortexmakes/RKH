/*
 * stimers.c
 */


#include "mytypes.h"
#include "stimers.h"
#include "rksys.h"


enum
{
	FREE, USED
};


#if RKSYS_TIMER && RKSYS_TIMER_NUM_TIMERS != 0


/*
 * 	Timer Control Block.
 */

typedef struct
{
	unsigned used:1;		/* free or used timer */
	unsigned type:1;		/* timer type */
	RKTICK_T tout;			/* tick counter */
	RKTICK_T reload;			/* expiration time in periodic mode */
	STCB_T stcb;			/* callback function */
#if RKSYS_TIMER_SIMPLE_CB == 0
	void *stp;				/* callback function parameter */
#endif
#if RKSYS_TIMER_GET_INFO == 1
	TIMER_INFO_T tinfo;		/* performance information */
#endif
} TIMER_T;


#if RKSYS_TIMER_GET_INFO
	#define info_expirations( p )			++p->tinfo.expirations
	#define info_kicks( p )					++p->tinfo.kicks
	#define info_kills( p )					++p->tinfo.kills
	#define info_reassigns( p )				++p->tinfo.reassigns
#else
	#define info_expirations( p )
	#define info_kicks( p )
	#define info_kills( p )
	#define info_reassigns( p )
#endif


/*	Maintains the allocated timer structures */

static TIMER_T timers[ RKSYS_TIMER_NUM_TIMERS ];


static
TIMER_T *
stimer_verify( TIM_T timd )
{
	return &timers[ timd ];
}


#if RKSYS_TIMER_INIT
void
stimer_init( void )
{
	TIMER_T *p;
	MUInt tix;

	for( tix = 0, p = timers; tix < RKSYS_TIMER_NUM_TIMERS ; ++p, ++tix )
	{
		enter_critical();
		p->used = FREE;
		p->tout = 0;
		exit_critical();
	}
}
#endif


void
stimer_handler( void )
{
	TIMER_T *p;
	MUInt tix;

	rktrace_timer_tick();

	for( tix = 0, p = timers; tix < RKSYS_TIMER_NUM_TIMERS; ++p, ++tix )
		if( p->used == USED && p->tout && !--p->tout )
		{
			p->tout = p->type == ONESHOT ? 0 : p->reload;
#if RKSYS_TIMER_SIMPLE_CB == 0
			(*p->stcb)( tix, p->stp );
#else
			(*p->stcb)();
#endif
			info_expirations( p );
		}
}


#if RKSYS_TIMER_SIMPLE_CB == 0

TIM_T
stimer_assign( uchar type, STCB_T stcb, void *stp )

#else

TIM_T
stimer_assign( uchar type, STCB_T stcb )

#endif
{
	TIMER_T *p;
	MUInt tix;

	rkassert( stcb != NULL, RKSYS_STIMER_ASSIGN_FAILED );

	for( tix = 0, p = timers; tix < RKSYS_TIMER_NUM_TIMERS; ++p, ++tix )
		if( p->used != USED )
		{
			p->used = USED;
			p->type = type;
			p->tout = p->reload = 0;
			p->stcb = stcb;
#if RKSYS_TIMER_SIMPLE_CB == 0
			rkassert( stp != NULL, RKSYS_STIMER_ASSIGN_FAILED );
			p->stp  = stp;
#endif
			rktrace_assign_timer( tix );
			return tix;
		}

	rkassert( tix < RKSYS_TIMER_NUM_TIMERS, RKSYS_STIMER_ASSIGN_FAILED );
	return -TIMER_NO;
}


#if RKSYS_TIMER_REASSIGN

#if RKSYS_TIMER_SIMPLE_CB == 0

void
stimer_reassign( TIM_T timd, STCB_T stcb, void *stp )

#else

void
stimer_reassign( TIM_T timd, STCB_T stcb )

#endif
{
	TIMER_T *p;
	
	rkassert( timd < RKSYS_TIMER_NUM_TIMERS, RKSYS_STIMER_REASSIGN_FAILED );
	rkassert( stcb != NULL, RKSYS_STIMER_REASSIGN_FAILED );

	p = stimer_verify( timd );
	rkassert( p->used != USED, RKSYS_STIMER_REASSIGN_FAILED );

	stimer_kick( timd, 0 );
	p->stcb = stcb;
#if RKSYS_TIMER_SIMPLE_CB == 0
	rkassert( stp != NULL, RKSYS_STIMER_REASSIGN_FAILED );
	p->stp = stp;
#endif
	info_reassigns( p );
	rktrace_reassign_timer( timd );
}

#endif


#if RKSYS_TIMER_KILL

void
stimer_kill( TIM_T timd )
{
	TIMER_T *p;

	rkassert( timd < RKSYS_TIMER_NUM_TIMERS, RKSYS_STIMER_KILL_FAILED );

	p = stimer_verify( timd );
	rkassert( p->used == USED, RKSYS_STIMER_KILL_FAILED );

	enter_critical();
	p->used = FREE;
	exit_critical();

	info_kills( p );
	rktrace_kill_timer( timd );
}

#endif


void
stimer_kick( TIM_T timd, RKTICK_T tout )
{
	TIMER_T *p;
	
	rkassert( timd < RKSYS_TIMER_NUM_TIMERS, RKSYS_STIMER_KICK_FAILED );

	p = stimer_verify( timd );
	rkassert( p->used == USED, RKSYS_STIMER_KICK_FAILED );

	enter_critical();
	p->tout = p->reload = tout;
	exit_critical();

	info_kicks( p );
	rktrace_kick_timer( timd );
}


void
stimer_stop( TIM_T timd )
{
	stimer_kick( timd, 0 );
	rktrace_stop_timer( timd );
}


#if RKSYS_TIMER_GET_INFO == 1

void 
stimer_clear_info( TIM_T timd )
{
	TIMER_T *p;
	TIMER_INFO_T *q;

	p = stimer_verify( timd );
	q = &p->tinfo;

	enter_critical();
	q->expirations = q->kicks = q->kills = q->reassigns = 0;
	exit_critical();
}


void 
stimer_get_info( TIM_T timd, TIMER_INFO_T *pti )
{
	TIMER_T *p;

	p = stimer_verify( timd );

	enter_critical();
	*pti = p->tinfo;
	exit_critical();
}

#endif


#endif
