/*
 *	file: rkh.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 28, 2010
 *
 * 	Copyright (C) 2010 Leandro Francucci. All rights reserved.
 *
 * 	RKH is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 *  RKH is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RKH, see copying.txt file.
 *
 * Contact information:
 * RKH web site:	http://
 * e-mail:			francuccilea@gmail.com
 */

/**
 * 	\file rkh.c
 *	\brief
 *
 *	RKH engine source code.
 */


#include <stdlib.h>

#include "rkh.h"
#include "rkhsm.h"
#include "rkhassert.h"


#define EXIT_LIST						0x0
#define ACT_LIST						0x01
#define SN_LIST							0x02
#define SND_LIST						0x04

#define CB( p )							((RKHBASE_T*)p)
#define CR( p )							((RKHSREG_T*)p)
#define CC( p )							((RKHSCOND_T*)p)
#define CJ( p )							((RKHSJUNC_T*)p)
#define CH( p )							((RKHSHIST_T*)p)
#define CA( p )							((RKHACT_T)p)
#define CP( p )							((RKHPPRO_T)p)
#define CV( p )							((void*)p)
#define CM( p )							((const RKH_T*)p)


#define is_not_internal_transition()	(inttr == 0)
#define is_internal_transition(s)		((s) == NULL)
#define is_trtbl_null(s)				((s)->trtbl == NULL)
#define is_empty_hist(s)				(*(CH(s))->target == NULL)
#define is_found_trans(t)				((t)->event != RKH_ANY)
#define is_not_found_trans(t)			((t)->event == RKH_ANY)
#define is_not_valid_guard(t)			((t)->guard == NULL)
#define is_valid_guard(t)				((t)->guard != NULL)
#define is_not_valid_conditional(s)		((s)->cdl == NULL)
#define is_pseudo( s )					((CB(s)->type&RKH_REGULAR)==0)
#define is_composite( s )				(CB(s)->type==RKH_COMPOSITE)
#define is_hcal( ph )					((ph)->ppty==HCAL)


#if RKH_TRACE == 1
	#define clr_step()					(step = 0)
	#define inc_step()					++step
	#define get_step()					step
#else
	#define clr_step()
	#define inc_step()
	#define get_step()
#endif

#if RKH_EN_GET_INFO == 1
	#define info_rcv_events( p )		++p->hinfo.rcvevt
	#define info_exec_trs( p )			++p->hinfo.exectr
#else
	#define info_rcv_events( p )
	#define info_exec_trs( p )
#endif


#if RKH_EN_STATE_NAME == 1
#define stname( s )						CB( (s) )->name
#else
#define stname( s )						NULL	
#endif


#define rkh_update_shallow_hist( s, h )									\
																		\
	CR(s)->parent != NULL && 											\
		( h = CR(s)->parent->history ) != NULL 							\
			&& CB(h)->type == RKH_SHISTORY


#define rkh_define_ex_en_states()										\
																		\
	for( --sn.p, --sx.p; sn.qty != 0 && sx.qty != 0 && *sn.p == *sx.p; 	\
			--sn.qty,--sx.qty, --sn.p, --sx.p )


#if RKH_EN_PPRO == 1

#define rkh_process_input( s, h, pe )									\
																		\
	(s)->prepro != NULL ? rkh_call_prepro(s,h,pe) : (pe->e)

#else

#define rkh_process_input( s, h, pe )									\
																		\
	(pe->e)

#endif


#define find_branch( btbl, t )											\
																		\
	for( tr = btbl; tr->event != RKH_ANY; ++tr )						\
		if( is_valid_guard( tr ) &&										\
				rkh_call_guard( tr, ph, pe ) == RKH_GTRUE )				\
			break;


typedef struct
{
	void *list[ RKH_MAX_HCAL_DEPTH	];
	void **p;
	HUInt qty;
} RKHSLIST_T;


typedef struct
{
	void *list[ RKH_EXCEED_TR_SEGS ];
	void **p;
	HUInt qty;
} RKHALIST_T;


static rkhrom RKHTR_T tr_null = { RKH_ANY, NULL, NULL, NULL };
static RKHALIST_T act_list;
#if RKH_EN_HCAL == 1
static RKHSLIST_T snd, sx, sn;
#endif

static RKHEVT_T *pgevt;
static RKH_T *pgh;

#if RKH_TRACE == 1
static RKHTREVT_T te;
#endif


static
rkhrom
RKHTR_T *
find_trans( rkhrom RKHTR_T *ptr, RKHE_T input )
{
	for( ; ptr->event != input && ptr->event != RKH_ANY; ++ptr )
		;
	return ptr;
}


#if RKH_EN_HCAL == 1
static
HUInt
rkh_make_setxn( RKHSLIST_T *to, rkhrom RKHSREG_T *from )
{
	rkhrom RKHSREG_T *s;

	for( to->qty = 0, s = from, to->p = to->list; 
			s != NULL; s = s->parent, ++to->qty, ++to->p )
	{
		*to->p = CV( s );
		if( to->qty >= RKH_MAX_HCAL_DEPTH )
			return 1;
	}
	return 0;
}
#endif


static
void
rkh_init_list( void *pl )
{
	RKHSLIST_T *p;

	p = ( RKHSLIST_T* )pl;
	p->p = p->list;
	p->qty = 0;
}


static
HUInt
rkh_add_list( void *pl, void *pe, HUInt max )
{
	RKHSLIST_T *p;

	p = ( RKHSLIST_T* )pl;

	if( p->qty >= max )
		return 1;

	if( pe != NULL )
	{
		*p->p++ = pe;
		++p->qty;
	}
	return 0;
}


#if RKH_EN_HCAL == 1 && RKH_EN_PSEUDOSTATE == 1 && RKH_EN_DEEP_HISTORY == 1

static
void
rkh_update_deep_hist( rkhrom RKHSREG_T *from )
{
	rkhrom RKHSREG_T *s;
	rkhrom RKHSHIST_T *h;

	for( s = from->parent; s != NULL; s = s->parent )
		if( ( h = s->history ) != NULL && CB(h)->type == RKH_DHISTORY )
			*h->target = from;
}

#else

#define rkh_update_deep_hist( f )

#endif


static
void
rkh_traverse_list( void *plist, HUInt lname )
{
	void *q;
	RKHSLIST_T *pl;
#if RKH_EN_HCAL == 1 && RKH_EN_PSEUDOSTATE == 1 && RKH_EN_SHALLOW_HISTORY == 1
	rkhrom RKHSHIST_T *h;
#endif

	pl = ( RKHSLIST_T* )plist;
#if RKH_EN_HCAL == 1
	pl->p = lname == SN_LIST ? &pl->list[ pl->qty - 1 ] : pl->list;
#else
	pl->p = pl->list;
#endif
	while( pl->qty )
	{
		q = *pl->p;

		switch( lname )
		{
#if RKH_EN_HCAL == 1
			case EXIT_LIST:
				rkh_exec_exit( CR( q ), CM( pgh ) );
#if RKH_EN_PSEUDOSTATE == 1 && RKH_EN_SHALLOW_HISTORY == 1
				if( rkh_update_shallow_hist( q, h ) )
					*h->target = CR( q );
#endif
				rkh_rec_exit( te, pgh->id, CB( q )->id, stname( q ) );
				break;
#endif
			case ACT_LIST:
				rkh_call_action( CM( pgh ), pgevt );
				break;
#if RKH_EN_HCAL == 1
			case SND_LIST:
			case SN_LIST:
				rkh_exec_entry( CR( q ), CM( pgh ) );
				rkh_rec_entry( te, pgh->id, CB( q )->id, stname( q ) );
				break;
#endif
		}
		
		--pl->qty;

#if RKH_EN_HCAL == 1
		if( lname == SN_LIST )
			--pl->p;
		else
#endif
			++pl->p;
	}
}


void 
rkh_init_hsm( RKH_T *ph )
{
#if RKH_EN_HCAL == 1
	rkhrom RKHSREG_T *s;
#endif

	rkh_rec_init_hsm( te, ph->id, CB( ph->init_state )->id, 
										stname( ph->init_state ) );

	rkh_exec_init( ph );

#if RKH_EN_HCAL == 1
	if( is_hcal( ph ) )
	{
		for( s = ph->init_state; s != NULL; s = s->defchild )
		{
			ph->state = s;
			rkh_exec_entry( s, CM( ph ) );
			rkh_rec_entry( te, ph->id, CB( s )->id, stname( s ) );
		}

		rkh_update_deep_hist( ph->state );
	}
#endif
}


#if RKH_EN_HCAL == 1 && RKH_EN_PSEUDOSTATE == 1 && \
				( RKH_EN_SHALLOW_HISTORY == 1 || RKH_EN_DEEP_HISTORY == 1 )

void
rkh_clear_history( rkhrom RKHSHIST_T *h )
{
	*h->target = NULL;
}

#endif


HUInt
rkh_engine( RKH_T *ph, RKHEVT_T *pe )
{
	rkhrom RKHSREG_T *ss, *s, *ts;
	rkhrom void *ets;
	rkhrom RKHTR_T *tr;
	HUInt first_regular, inttr;
	RKHE_T in;
#if RKH_TRACE == 1
	HUInt step;
#endif

	pgh = ph;
	pgevt = pe;
	inttr = 0;
	info_rcv_events( ph );

	/* Stage 1 */
	ss = ph->state;

	/* Stage 2 */
#if RKH_EN_HCAL == 1
	for( s = ss; s != NULL; s = s->parent )
	{
		in = rkh_process_input( s, ph, pe );	
		tr = find_trans( s->trtbl, in );
		if( is_found_trans( tr ) )
			break;
	}
#else
	s = ss;
	in = rkh_process_input( s, ph, pe );	
	tr = find_trans( s->trtbl, in );
#endif

	if( is_not_found_trans( tr ) )
	{
		rkh_rec_rtn_code( te, ph->id, RKH_INPUT_NOT_FOUND );
		return RKH_INPUT_NOT_FOUND;
	}

	/* Stage 3 */
	ets = tr->target;
	ts = CR( ets );
	rkh_rec_event( 	te, ph->id, in );

	/* Stage 4 */
	first_regular = 1;
	rkh_init_list( &act_list );
	
#if RKH_EN_HCAL == 1
	if( is_hcal( ph ) )
		rkh_init_list( &snd );
#endif

	clr_step();

	if( rkh_add_list( &act_list, tr->action, RKH_MAX_TR_SEGS ) )
	{
		rkh_rec_rtn_code( te, ph->id, RKH_EXCEED_TR_SEGS );
		return RKH_EXCEED_TR_SEGS;
	}

	rkh_rec_src_state( te, ph->id, CB( ss )->id, stname( ss ) );

	if( is_internal_transition( ets ) )
	{
		inttr = 1;
		rkh_rec_int_tran( te, ph->id );
	}
	else
	{
		inttr = 0;
		rkh_rec_tgt_state( te, ph->id, CB( ts )->id, stname( ts ) );
	}

	if( is_not_internal_transition() )
	{
		rkh_rec_sgt( te, ph->id, CB( ets )->id, stname( ets ) );
		inc_step();

		while( is_pseudo( ets ) || is_composite( ets ) )
		{
			switch( CB(ets)->type )
			{
#if RKH_EN_HCAL == 1
				case RKH_COMPOSITE:

					if( first_regular )
					{
						ts = CR( ets );
						first_regular = 0;
					}
					else if( rkh_add_list( &snd, CV( ets ), 
													RKH_MAX_HCAL_DEPTH ) )
					{
						rkh_rec_rtn_code( te, ph->id, RKH_EXCEED_HCAL_LEVEL );
						return RKH_EXCEED_HCAL_LEVEL;
					}

					ets = CR(ets)->defchild;

					break;
#endif
#if RKH_EN_PSEUDOSTATE == 1 && RKH_EN_CONDITIONAL
				case RKH_CONDITIONAL:
					
					if( is_valid_guard( tr ) && 
							rkh_call_guard( tr, ph, pe ) == RKH_GFALSE )
					{
						rkh_rec_rtn_code( te, ph->id, RKH_GUARD_FALSE );
						return RKH_GUARD_FALSE;
					}


					find_branch( CC(ets)->trtbl, tr );

					if( is_not_found_trans( tr ) )
					{
						rkh_rec_rtn_code( te, ph->id, RKH_CONDITION_NOT_FOUND );
						return RKH_CONDITION_NOT_FOUND;
					}

					if( rkh_add_list( &act_list, tr->action, RKH_MAX_TR_SEGS ) )
					{
						rkh_rec_rtn_code( te, ph->id, RKH_EXCEED_TR_SEGS );
						return RKH_EXCEED_TR_SEGS;
					}

					ets = tr->target;

					break;
#endif
#if RKH_EN_PSEUDOSTATE == 1 && RKH_EN_JUNCTION
				case RKH_JUNCTION:

					if( rkh_add_list( &act_list, CJ(ets)->action, 
															RKH_MAX_TR_SEGS ) )
					{
						rkh_rec_rtn_code( te, ph->id, RKH_EXCEED_TR_SEGS );
						return RKH_EXCEED_TR_SEGS;
					}

					ets = CJ(ets)->target;
					tr = &tr_null;

					break;
#endif
#if RKH_EN_HCAL == 1 && RKH_EN_PSEUDOSTATE == 1 && \
					( RKH_EN_SHALLOW_HISTORY == 1 || RKH_EN_DEEP_HISTORY == 1 )
				case RKH_SHISTORY:
				case RKH_DHISTORY:

					if( is_empty_hist( ets ) )
						ets = CH(ets)->parent;
					else
					{
						ets = *(CH(ets))->target;
						tr = &tr_null;
					}
#endif
					break;
				default:
					rkh_rec_rtn_code( te, ph->id, RKH_UNKNOWN_STATE );
					return RKH_UNKNOWN_STATE;
			}

			rkh_rec_sgt( te, ph->id, CB( ets )->id, stname( ets ) );
			inc_step();
		}
	}

	if( is_not_internal_transition() )
	{
		if( first_regular )
			ts = CR( ets );
#if RKH_EN_HCAL == 1
		else if( rkh_add_list( &snd, CV( ets ), RKH_MAX_HCAL_DEPTH ) )
		{
			rkh_rec_rtn_code( te, ph->id, RKH_EXCEED_HCAL_LEVEL );
			return RKH_EXCEED_HCAL_LEVEL;
		}
#endif
	}

	if( is_valid_guard( tr ) && rkh_call_guard( tr, ph, pe ) == RKH_GFALSE )
	{
		rkh_rec_rtn_code( te, ph->id, RKH_GUARD_FALSE );
		return RKH_GUARD_FALSE;
	}

#if RKH_EN_HCAL == 1
	if( is_hcal( ph ) && is_not_internal_transition() )
	{
		/* Stage 5 & 6 */
		if( rkh_make_setxn( &sx, ss ) || rkh_make_setxn( &sn, ts ) )
		{
			rkh_rec_rtn_code( te, ph->id, RKH_EXCEED_HCAL_LEVEL );
			return RKH_EXCEED_HCAL_LEVEL;
		}

		/* Stage 7 */
		rkh_update_deep_hist( CR( ets ) );

		/* Stage 8 */
		rkh_define_ex_en_states();
		rkh_rec_num_enex( te, ph->id, (((sn.qty + snd.qty) << 4) | sx.qty) );

		/* Stage 9 */
		rkh_traverse_list( &sx, EXIT_LIST );
	}
#endif

	/* Stage 10 */
	rkh_rec_num_actsgt( te, ph->id, ((act_list.qty << 4) | get_step()) );
	rkh_traverse_list( &act_list, ACT_LIST );

	if( is_not_internal_transition() )
	{
		/* Stage 11 */
#if RKH_EN_HCAL == 1
		if( is_hcal( ph ) )
		{
			rkh_traverse_list( &sn, SN_LIST );
			rkh_traverse_list( &snd, SND_LIST );
		}
#endif

		/* Stage 12 */
		ph->state = CR( ets );
		rkh_rec_nxt_state( te, ph->id, CB( ets )->id, stname( ets ) );
	}

	info_exec_trs( ph );
	rkh_rec_rtn_code( te, ph->id, RKH_OK );
	return RKH_OK;
}


#if RKH_EN_GET_INFO == 1

void 
rkh_clear_info( RKH_T *ph )
{
	ph->hinfo.rcvevt = ph->hinfo.exectr = 0;
}


RKH_INFO_T *
rkh_get_info( RKH_T *ph )
{
	return &ph->hinfo;
}

#endif


#if RKH_EN_GRD_EVT_ARG == 1 && RKH_EN_GRD_HSM_ARG == 1

HUInt 
rkh_else( const struct rkh_t *ph, RKHEVT_T *pe )
{
	return RKH_GTRUE;
}

#elif RKH_EN_GRD_EVT_ARG == 1 && RKH_EN_GRD_HSM_ARG == 0
	
HUInt 
rkh_else( RKHEVT_T *pe )
{
	return RKH_GTRUE;
}

#elif RKH_EN_GRD_EVT_ARG == 0 && RKH_EN_GRD_HSM_ARG == 1
	
HUInt 
rkh_else( const struct rkh_t *ph )
{
	return RKH_GTRUE;
}

#else
	
HUInt 
rkh_else( void )
{
	return RKH_GTRUE;
}

#endif


#if RKH_EN_DYNAMIC_EVENT == 1

RKHEVT_T *
rkh_ae( rkhuint8 es, RKHE_T e )
{
    RKHEVT_T *evt;

              /* find the pool index that fits the requested event size ... */
    rkhuint8 idx = 0;
    while( es > rkh_dyne_event_size( idx ) ) 
	{
        ++idx;
									  /* cannot run out of registered pools */
        rkhassert( idx < RKH_DYNE_NUM_POOLS, RKH_AE_RUNOUT_POOLS );
    }

    rkh_dyne_get( idx, evt );        		 /* get e -- platform-dependent */
							             /* pool must not run out of events */
    rkhassert( evt != NULL, RKH_AE_NOT_ALLOC );

    evt->e = e;                                /* set signal for this event */

	/* 
	 * Store the dynamic attributes of the event:
	 * the pool ID and the reference counter == 0
	 */
    evt->dynamic_ = (rkhuint8)( ( idx + 1 ) << 6 );
    return e;	
}


void 
rkh_gc( RKHEVT_T *evt )
{
    if( evt->dynamic_ != 0 )                      /* is it a dynamic event? */
	{
        rkh_enter_critical();

        if( ( evt->dynamic_ & 0x3F ) > 1 )      /* isn't this the last ref? */
		{
            --((RKHEVT_T*)e)->dynamic_;   /*decrement the reference counter */
            rkh_exit_critical();
        }
        else        /* this is the last reference to this event, recycle it */
		{
                                                      /* cannot wrap around */
            rkhuint8 idx = (rkhuint8)( ( e->dynamic_ >> 6 ) - 1 );
            rkh_exit_critical();

            rkhassert( idx < RKH_DYNE_NUM_POOLS, RKH_GC_RUNOUT_POOLS );
            rkh_dyne_put( idx, ( RKHEVT_T* )e );
        }
    }
}


HUInt 
rkh_put_fifo( HUInt qd, RKHEVT_T *evt )
{
    rkh_enter_critical();
    if( evt->dynamic_ != 0 ) 
        ++(( RKHEVT_T* )evt)->dynamic_;
    rkh_exit_critical();

    return rkh_post_fifo( qd, evt ); 
}


HUInt 
rkh_put_lifo( HUInt qd, RKHEVT_T *evt )
{
    rkh_enter_critical();
    if( evt->dynamic_ != 0 ) 
        ++(( RKHEVT_T* )evt)->dynamic_;
    rkh_exit_critical();

    return rkh_post_lifo( qd, evt ); 
}


#if RKH_EN_DEFERRED_EVENT == 1

HUInt 
rkh_defer( HUInt qd, RKHEVT_T *evt )
{
	rkh_put_fifo( qd, evt );
}


RKHEVT_T *
rkh_recall( HUInt qdd, HUInt qds )
{
    RKHEVT_T *evt;
	HUInt r;
	
										/* get an event from deferred queue */
    if( ( r = rkh_get( qds, evt ) ) == 0 )     			/* event available? */
	{
		/* post it to the front of the AO's queue */
        rkh_put_lifo( qds, evt );
        rkh_enter_critical();

        if( evt->dynamic_ != 0 )           		  /* is it a dynamic event? */
		{
            /* 
			 * After posting to the AO's queue the event must be referenced
             * at least twice: once in the deferred event queue (eq->get()
             * did NOT decrement the reference counter) and once in the
             * AO's event queue.
             */
            rkhassert(( evt->dynamic_&0x3F ) > 1, RKH_RC_FAIL );

            /* 
			 * We need to decrement the reference counter once, to account
             * for removing the event from the deferred event queue.
             */
            --( ( RKHEVT_T* )evt )->dynamic_;
        }
		rkh_exit_critical();
    }
    return r != 0 ? NULL : evt;
}

#endif

#endif
