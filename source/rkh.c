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
#include "rkhassert.h"


RKH_MODULE_NAME( rkh )


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
#define CM( p )							((const RKHSMA_T*)p)
#define CT( p )							((RKHROM RKHTR_T*)(p))


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
#define is_not_conditional( s )			(CB(s)->type!=RKH_CONDITIONAL)


#if RKH_TRC_EN == 1
	#define rkh_clr_step()				(step = 0)
	#define rkh_inc_step()				++step
	#define rkh_get_step()				step
#else
	#define rkh_clr_step()
	#define rkh_inc_step()
	#define rkh_get_step()
#endif

#if RKH_SMA_EN_GET_INFO == 1
	#define info_rcv_events( p )		++p->hinfo.rcvevt
	#define info_exec_trs( p )			++p->hinfo.exectr
#else
	#define info_rcv_events( p )
	#define info_exec_trs( p )
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


#if RKH_SMA_EN_PPRO == 1

#define rkh_process_input( s, h, pe )									\
																		\
	(RKHE_T)(((s)->prepro != NULL)?rkh_call_prepro(s,h,pe):((pe)->e))

#else

#define rkh_process_input( s, h, pe )									\
																		\
	(RKHE_T)((pe)->e)

#endif


#define find_branch( btbl, t )											\
																		\
	for( t = btbl; t->event != RKH_ANY; ++t )							\
		if( is_valid_guard( t ) &&										\
				rkh_call_guard( t, sma, pe ) == RKH_GTRUE )				\
			break;


typedef struct
{
	rkhui8_t qty;
	void **p;
	void *list[ RKH_SMA_MAX_HCAL_DEPTH	];
} RKHSLIST_T;


typedef struct
{
	rkhui8_t qty;
	void **p;
	void *list[ RKH_SMA_MAX_TRC_SEGS ];
} RKHALIST_T;


static RKHROM RKHTR_T tr_null = { RKH_ANY, NULL, NULL, NULL };
static RKHALIST_T act_list;
#if RKH_SMA_EN_HCAL == 1
static RKHSLIST_T sx, sn;
static RKHROM RKHSREG_T *sentry[ RKH_SMA_MAX_HCAL_DEPTH ];
#endif

static RKHEVT_T *pgevt;
static RKHSMA_T *pgh;
static rkhui8_t depth;


static
RKHROM
RKHTR_T *
find_trans( RKHROM RKHTR_T *ptr, RKHE_T input )
{
	for( ; ptr->event != input && ptr->event != RKH_ANY; ++ptr )
		;
	return ptr;
}


#if RKH_SMA_EN_HCAL == 1
static
HUInt
rkh_exit_entry( RKHROM RKHSREG_T *src, RKHROM RKHSREG_T *tgt, RKHSMA_T *sma, 
							rkhui8_t *pnx, rkhui8_t *pnn )
{
	RKHROM RKHSREG_T *stx, *stn, **snl;
	rkhui8_t ix_x, islca, ix_n = 0;
#if RKH_SMA_EN_HCAL == 1 && RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_SHALLOW_HISTORY == 1
	RKHROM RKHSHIST_T *h;
#endif

	for( ix_x = islca = 0, stx = src; 
			stx != CR( 0 ); stx = stx->parent, ++ix_x )
	{
		for( ix_n = 0, snl = sentry, stn = tgt; 
				stn != CR( 0 ); stn = stn->parent, ++snl, ++ix_n )
			if( stx == stn )
			{
				islca = 1	/* found LCA */;
				break;
			}
			else
				*snl = stn;

		if( islca == 0 )
		{
			RKH_EXEC_EXIT( stx, CM( sma ) );
#if RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_SHALLOW_HISTORY == 1
			if( rkh_update_shallow_hist( stx, h ) )
				*h->target = CR( stx );
#endif
			RKH_TRCR_SM_EXSTATE( sma, stx );
		}
		else
			break;
	}

	*pnx = ix_x;
	*pnn = ix_n;

	return 0;
}


static
void
rkh_exec_entry( rkhui8_t nn, RKHSMA_T *sma )
{
	RKHROM RKHSREG_T *stn, **snl;
	rkhui8_t ix_n;

	/* from LCA state to target state */
	for( ix_n = nn, snl = &sentry[ ix_n ]; ix_n != 0; --ix_n )
	{
		--snl;
		RKH_EXEC_ENTRY( *snl, CM( sma ) );
		RKH_TRCR_SM_ENSTATE( sma, *snl );
	}

	/* from target state to least descendant state */
	for( stn = (*snl)->defchild; stn != CR( 0 ); stn = stn->defchild )
	{
		RKH_EXEC_ENTRY( stn, CM( sma ) );
		RKH_TRCR_SM_ENSTATE( sma, stn );
	}
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


#if RKH_SMA_EN_HCAL == 1 && RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_DEEP_HISTORY == 1
static
void
rkh_update_deep_hist( RKHROM RKHSREG_T *from )
{
	RKHROM RKHSREG_T *s;
	RKHROM RKHSHIST_T *h;

	for( s = from->parent; s != NULL; s = s->parent )
		if( ( h = s->history ) != NULL && CB(h)->type == RKH_DHISTORY )
			*h->target = from;
}
#else
#define rkh_update_deep_hist( f )		((void)0)
#endif


static
void
rkh_traverse_list( void *plist, HUInt lname )
{
	void *q;
	RKHSLIST_T *pl;
#if RKH_SMA_EN_HCAL == 1 && RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_SHALLOW_HISTORY == 1
	RKHROM RKHSHIST_T *h;
#endif

	pl = ( RKHSLIST_T* )plist;
#if RKH_SMA_EN_HCAL == 1
	pl->p = lname == SN_LIST ? &pl->list[ pl->qty - 1 ] : pl->list;
#else
	pl->p = pl->list;
#endif
	while( pl->qty )
	{
		q = *pl->p;

		switch( lname )
		{
#if RKH_SMA_EN_HCAL == 1
			case EXIT_LIST:
				RKH_EXEC_EXIT( CR( q ), CM( pgh ) );
#if RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_SHALLOW_HISTORY == 1
				if( rkh_update_shallow_hist( q, h ) )
					*h->target = CR( q );
#endif
				RKH_TRCR_SM_EXSTATE( pgh, q );
				break;
#endif
			case ACT_LIST:
				rkh_call_action( CM( pgh ), pgevt );
				break;
#if RKH_SMA_EN_HCAL == 1
			case SND_LIST:
			case SN_LIST:
				RKH_EXEC_ENTRY( CR( q ), CM( pgh ) );
				RKH_TRCR_SM_ENSTATE( pgh, q );
				break;
#endif
		}
		
		--pl->qty;

#if RKH_SMA_EN_HCAL == 1
		if( lname == SN_LIST )
			--pl->p;
		else
#endif
			++pl->p;
	}
}


void 
rkh_init_hsm( RKHSMA_T *sma )
{
#if RKH_SMA_EN_HCAL == 1
	RKHROM RKHSREG_T *s;
#endif

    RKHASSERT( 	sma != NULL && 
				sma->romrkh->istate != NULL );
	RKH_TRCR_SM_INIT( sma, sma->romrkh->istate );
	RKH_EXEC_INIT( sma );

#if RKH_SMA_EN_HCAL == 1
	for( s = sma->romrkh->istate; s != NULL; s = s->defchild )
	{
		sma->state = s;
		RKH_EXEC_ENTRY( s, CM( sma ) );
		RKH_TRCR_SM_ENSTATE( sma, s );
	}

	rkh_update_deep_hist( sma->state );
#endif
}


#if RKH_SMA_EN_HCAL == 1 && RKH_SMA_EN_PSEUDOSTATE == 1 && ( RKH_SMA_EN_SHALLOW_HISTORY == 1 || RKH_SMA_EN_DEEP_HISTORY == 1 )

void
rkh_clear_history( RKHROM RKHSHIST_T *h )
{
	*h->target = NULL;
}

#endif


HUInt
rkh_dispatch( RKHSMA_T *sma, RKHEVT_T *pe )
{
	RKHROM RKHSREG_T *cs, *s, *ts;
	RKHROM void *ets;
	RKHROM RKHTR_T *tr;
	HUInt first_regular, inttr;
	RKHE_T in;

#if RKH_TRC_EN == 1
	rkhui8_t step, nx, nn;
#endif

    RKHASSERT( 	sma != NULL && pe != NULL );

	pgh = sma;
	pgevt = pe;
	inttr = 0;
	info_rcv_events( sma );
	RKH_HK_DISPATCH( sma, pe );
															/* ---- Stage 1 */
	cs = sma->state;						  /* get and save current state */

														    /* ---- Stage 2 */
#if RKH_SMA_EN_HCAL == 1
										/* find the transition to be taken: */
										                /* s = source state */
										       /* tr = triggered transition */
	for( s = cs, tr = CT(0); s != CR(0); s = s->parent )
	{
		in = rkh_process_input( s, sma, pe );	
		tr = find_trans( s->trtbl, in );
		if( is_found_trans( tr ) )
			break;
	}
#else
	s = cs;
	in = rkh_process_input( s, sma, pe );	
	tr = find_trans( s->trtbl, in );
#endif

	if( is_not_found_trans( tr ) )					   /* transition taken? */
	{
		RKH_TRCR_SM_DCH_RC( sma, RKH_INPUT_NOT_FOUND );	   /* ignored event */
		return RKH_INPUT_NOT_FOUND;
	}
															/* ---- Stage 3 */
	ets = tr->target;	   /* temporarily save the target of the transition */
	ts = CR( ets );		   /* temporarily save the target of the transition */
	first_regular = 1;		   /* set first regular state in the transition */
	depth = 0;							     /* and the state nesting depth */
	rkh_init_list( &act_list );
	rkh_clr_step();
#if RKH_TRC_EN == 1
	nn = nx = 0;
#endif

	RKH_TRCR_SM_DCH(	sma, 				   /* this state machine object */
						pe );									   /* event */
	RKH_TRCR_SM_TRN( 	sma, 				   /* this state machine object */
						s, 						 /* transition source state */
						ts );					 /* transition target state */

															/* ---- Stage 4 */
								  /* store action of the transition segment */
	if( rkh_add_list( 	&act_list, 
						tr->action, 
						RKH_SMA_MAX_TRC_SEGS ) )
	{
		RKH_TRCR_SM_DCH_RC( sma, RKH_EXCEED_TRC_SEGS );
		RKHERROR();
		return RKH_EXCEED_TRC_SEGS;
	}

	rkh_inc_step();			  /* increment the number of transition segment */
	inttr = is_internal_transition( ets );    /* is an internal transition? */

	if( is_not_internal_transition() )
	{
		RKH_TRCR_SM_CSTATE( 	sma, 		   /* this state machine object */
			   					  /* target state of the transition segment */
								ets );

		if( is_valid_guard( tr ) && 				 /* enabled transition? */
				rkh_call_guard( tr, sma, pe ) == RKH_GFALSE )
		{
			RKH_TRCR_SM_DCH_RC( sma, RKH_GUARD_FALSE );
			return RKH_GUARD_FALSE;
		}
								/* ... traverses the taken transition until */
   				   		  /* the segment target state (ets) == simple state */
		while( is_pseudo( ets ) || is_composite( ets ) )
		{
			switch( CB(ets)->type )
			{
#if RKH_SMA_EN_HCAL == 1
				case RKH_COMPOSITE:
										 /* found a composite (super) state */
										      /* in the compound transition */
			         /* take from that its default child and then it is set */
													  /*as new target state */
					if( first_regular )
					{
						ts = CR( ets );
						first_regular = 0;
					}

					ets = CR( ets )->defchild;
					break;
#endif
#if RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_CONDITIONAL == 1
				case RKH_CONDITIONAL:
					            /* found a conditional (choice) pseudostate */
										      /* in the compound transition */
						/* evaluates the guards of its outgoing transitions */
					find_branch( CC( ets )->trtbl, tr );

					if( is_not_found_trans( tr ) )
					{
						RKH_TRCR_SM_DCH_RC( sma, RKH_CONDITION_NOT_FOUND );
						return RKH_CONDITION_NOT_FOUND;
					}

					if( rkh_add_list(	&act_list, 
										tr->action, 
										RKH_SMA_MAX_TRC_SEGS ) )
					{
						RKH_TRCR_SM_DCH_RC( sma, RKH_EXCEED_TRC_SEGS );
						RKHERROR();
						return RKH_EXCEED_TRC_SEGS;
					}
											  /* another transition segment */
					rkh_inc_step();
					ets = tr->target;
					break;
#endif
#if RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_JUNCTION == 1
				case RKH_JUNCTION:
					                        /* found a junction pseudostate */
										      /* in the compound transition */
					  /* Should be added: test transition guard and call it */
																	 /* ... */
					if( rkh_add_list( 	&act_list, 
										CJ(ets)->action, 
										RKH_SMA_MAX_TRC_SEGS ) )
					{
						RKH_TRCR_SM_DCH_RC( sma, RKH_EXCEED_TRC_SEGS );
						RKHERROR();
						return RKH_EXCEED_TRC_SEGS;
					}
											  /* another transition segment */
					rkh_inc_step();
					ets = CJ(ets)->target;
					tr = &tr_null;
					break;
#endif
#if RKH_SMA_EN_HCAL == 1 && RKH_SMA_EN_PSEUDOSTATE == 1 && ( RKH_SMA_EN_SHALLOW_HISTORY == 1 || RKH_SMA_EN_DEEP_HISTORY == 1 )
				case RKH_SHISTORY:
				case RKH_DHISTORY:
	                         /* found a shallow or deep history pseudostate */
										      /* in the compound transition */
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
						                   /* fatal error: unknown state... */
					RKH_TRCR_SM_DCH_RC( sma, RKH_UNKNOWN_STATE );
					RKHERROR();
					return RKH_UNKNOWN_STATE;
			}

			RKH_TRCR_SM_CSTATE( sma, ets );
		}
	}

	if( is_not_internal_transition() )
		if( first_regular )
			ts = CR( ets );			  /* finally, set the main target state */

#if RKH_SMA_EN_HCAL == 1
	if( is_not_internal_transition() )
	{
															/* ---- Stage 5 */
															/* ---- Stage 6 */
															/* ---- Stage 7 */
															/* ---- Stage 8 */
															/* ---- Stage 9 */
		rkh_exit_entry( cs, ts, sma, &nx, &nn );
		rkh_update_deep_hist( CR( ets ) );
		RKH_TRCR_SM_NENEX( sma, nn, nx );
	}
#endif
													       /* ---- Stage 10 */
	RKH_TRCR_SM_NTRNACT( sma, act_list.qty, rkh_get_step() );
	rkh_traverse_list( &act_list, ACT_LIST );

	if( is_not_internal_transition() )
	{
												 		   /* ---- Stage 11 */
#if RKH_SMA_EN_HCAL == 1
		rkh_exec_entry( nn, sma );
#endif
														   /* ---- Stage 12 */
		sma->state = CR( ets );	      /* set current state to next RTC step */
		RKH_TRCR_SM_STATE( 	sma, 			   /* this state machine object */	
							sma->state );				   /* current state */
	}

	RKH_TRCR_SM_DCH_RC( sma, RKH_OK );
	info_exec_trs( sma );
	return RKH_OK;
}


#if RKH_SMA_EN_GET_INFO == 1
void 
rkh_sma_clear_info( RKHSMA_T *sma )
{
	RKH_SMAI_T *psi;
	RKH_SR_CRITICAL_;

	psi = &sma->sinfo;

	RKH_ENTER_CRITICAL_();
	sma->sinfo.ndevt = sma->sinfo.exectr = 0;
	RKH_EXIT_CRITICAL_();
}


void 
rkh_sma_get_info( RKHSMA_T *sma, RKH_SMAI_T *psi )
{
	RKH_SR_CRITICAL_;

	RKH_ENTER_CRITICAL_();
	*psi = sma->sinfo;
	RKH_EXIT_CRITICAL_();
}
#endif


#if RKH_SMA_EN_GRD_ARG_EVT == 1 && RKH_SMA_EN_GRD_ARG_SMA == 1

HUInt 
rkh_else( const struct rkhsma_t *sma, RKHEVT_T *pe )
{
	(void)sma;
	(void)pe;
	return RKH_GTRUE;
}

#elif RKH_SMA_EN_GRD_ARG_EVT == 1 && RKH_SMA_EN_GRD_ARG_SMA == 0
	
HUInt 
rkh_else( RKHEVT_T *pe )
{
	(void)pe;
	return RKH_GTRUE;
}

#elif RKH_SMA_EN_GRD_ARG_EVT == 0 && RKH_SMA_EN_GRD_ARG_SMA == 1
	
HUInt 
rkh_else( const struct rkhsma_t *sma )
{
	(void)sma;
	return RKH_GTRUE;
}

#else
	
HUInt 
rkh_else( void )
{
	return RKH_GTRUE;
}

#endif
