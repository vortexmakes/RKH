/*
 * fsm.c
 */

#include "mytypes.h"
#include "rksys.h"
#include "fsm.h"
#include "event.h"
#include "rkutils.h"

#include <stdlib.h>


#if RKSYS_FSM


#if RKSYS_FSM_ACT_ARGS
#define call_act( pe )					(*pa)((pe))
#else
#define call_act( pe )					(*pa)()
#endif


#if RKSYS_FSM_GUARD_ARGS
#define call_guard( pe )				(*ptrans->guard)((pe))
#else
#define call_guard( pe )				(*ptrans->guard)()
#endif


#if RKSYS_FSM_PPRO
#define preprocess_input( ps, pe )		ps->ppro != NULL ? 				\
											(*ps->ppro)(pe):pe->param
#else
#define call_guard( ps, pe )			pe->param
#endif


#if RKSYS_FSM_REENTRANT

static ACT_T tacts[ RKSYS_FSM_MAX_COMP_TRANS ];
static ACT_T *ptact;
static uchar tact_counter;

#endif


/*	Maintains the allocated FSM structures */

extern FSM_T fsms[ RKSYS_NUM_FSMS ];


static
FSM_T *
verify_fsm( MUInt fsmd )
{
	return &fsms[ fsmd ];
}


static
const TRANS_T *
find_trans( const TRANS_T *ps, uchar input )
{
	const TRANS_T *s;

	for( s = ps; s->evt != input && s->evt != FSM_ANY; ++s )
		;
	return s;
}


static
void
call_list_action( ACT_T pa, EVT_T *pe )
{
	if( pa != NULL )
		call_act( pe );
}


void
fsm_init( FSMD_T fsmd )
{
    FSM_T *p;
    EVT_T evt;

	rkassert( fsmd < RKSYS_NUM_FSMS, RKSYS_FSM_INIT_FAILED );
    p = verify_fsm( fsmd );
    p->state = p->init_state;

	evt.param = FSM_ANY;
    fsm_engine( fsmd, &evt );
}


void
fsm_engine( FSMD_T fsmd, EVT_T *pevt )
{
#if RKSYS_FSM_REENTRANT == 0
	ACT_T tacts[ RKSYS_FSM_MAX_COMP_TRANS ], *ptact;
	uchar tact_counter;
#endif
	FSM_T *pm;
	const STATE_T *pstate;
	const TRANS_T *ptrans;
	uchar in;

	rkassert( fsmd < RKSYS_NUM_FSMS, RKSYS_FSM_ENG_FAILED );
	pm = verify_fsm( fsmd );
	pstate = pm->state;
	
	in = preprocess_input( pstate, pevt );
	ptrans = find_trans( pstate->trans, in );

	switch( ptrans->next_state->state_type )
	{
		case NORMAL_STATE:
#if RKSYS_FSM_GUARD
			if( ptrans->guard != NULL && call_guard( pevt ) == GUARD_FALSE )
				return;
#endif
			call_list_action( ptrans->action, pevt );
			pm->state = ptrans->next_state;
			break;
#if RKSYS_FSM_COND && RKSYS_FSM_GUARD
		case COND_STATE:
			
			tact_counter = 1;
			ptact = tacts;
			*ptact++ = ptrans->action;

			do
			{
				if( ptrans->guard == NULL || 
						tact_counter >= RKSYS_FSM_MAX_COMP_TRANS )
					return;
				
				ptrans = find_trans( ptrans->next_state->trans, 
										call_guard( pevt ) );
				if( ptrans->evt == ELSE )
					return;

				*ptact++ = ptrans->action;
				++tact_counter;
			}
			while( ptrans->next_state->state_type == COND_STATE );

			for( ptact = tacts; tact_counter--; ++ptact )
				call_list_action( *ptact, pevt );

			pm->state = ptrans->next_state;
			break;
#endif
#if RKSYS_FSM_HISTORY
		case HISTORY_STATE:
			if( pm->srecall != NULL )
			{
				call_list_action( ptrans->action, pevt );
				pm->state = pm->srecall;
			}
			break;
#endif
		default:
			return;
	}
	rktrace_transition( fsmd, pstate->state_id, pm->state->state_id );
}


#if RKSYS_FSM_HISTORY

void
fsm_set_history( FSMD_T fsmd, const STATE_T *ps )
{
	FSM_T *p;

	rkassert( fsmd < RKSYS_NUM_FSMS, RKSYS_FSM_SH_FAILED );
	p = verify_fsm( fsmd );
	p->srecall = ps;
}

#endif


#if RKSYS_FSM_RECALL

void
fsm_set_recall( FSMD_T fsmd, const STATE_T *ps, uchar evt )
{
	FSM_T *p;

	rkassert( fsmd < RKSYS_NUM_FSMS, RKSYS_FSM_SR_FAILED );
	p = verify_fsm( fsmd );
	p->srecall = ps;
	p->erecall = evt;
}

#endif


#if RKSYS_FSM_GET_INFO

FSM_T *
fsm_get_info( FSMD_T fsmd )
{
	FSM_T *p;

	rkassert( fsmd < RKSYS_NUM_FSMS, RKSYS_FSM_GETINFO_FAILED );
	p = verify_fsm( fsmd );
	return p;
}

#endif


#endif
