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


#define IS_NOT_INTERNAL_TRANSITION()	(inttr == 0)
#define IS_INTERNAL_TRANSITION(s)		((s) == NULL)
#define IS_EMPTY_HIST(s)				(*(CH(s))->target == NULL)
#define IS_FOUND_TRANS(t)				((t)->event != RKH_ANY)
#define IS_NOT_FOUND_TRANS(t)			((t)->event == RKH_ANY)
#define IS_VALID_GUARD(t)				((t)->guard != NULL)
#define IS_PSEUDO( s )					((CB(s)->type&RKH_REGULAR)==0)
#define IS_COMPOSITE( s )				(CB(s)->type==RKH_COMPOSITE)


#define FIND_TRANS( t, tbl, sig )							\
	for( 	(t) = (tbl); 									\
			(t)->event != sig && (t)->event != RKH_ANY; 	\
			++(t) )


#if RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_SHALLOW_HISTORY == 1
	#define RKH_UPDATE_SHALLOW_HIST( s, h )							\
				if(	CR((s))->parent != NULL && 						\
						((h) = CR((s))->parent->history) != NULL && \
				 			CB((h))->type == RKH_SHISTORY )			\
					*(h)->target = CR( (s) )
#else
	#define RKH_UPDATE_SHALLOW_HIST( s, h )			((void)0)
#endif


#if RKH_SMA_EN_PPRO == 1
	#define RKH_PROCESS_INPUT( s, h, pe )							\
				(RKHE_T)( ((s)->prepro != NULL) ? 					\
						rkh_call_prepro((s),(h),(pe)) : (pe)->e )
#else
	#define RKH_PROCESS_INPUT( s, h, pe )							\
				(RKHE_T)((pe)->e)
#endif


#define FIND_BRANCH( btbl, t, sma, pe )									\
			for( (t) = (btbl); (t)->event != RKH_ANY; ++(t) )			\
				if( IS_VALID_GUARD( (t) ) &&							\
					rkh_call_guard( (t), (sma), (pe) ) == RKH_GTRUE )	\
					break;


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
	#define info_rcv_events( p )		++(p)->hinfo.rcvevt
	#define info_exec_trs( p )			++(p)->hinfo.exectr
#else
	#define info_rcv_events( p )
	#define info_exec_trs( p )
#endif


#define CB( p )							((RKHBASE_T*)(p))
#define CR( p )							((RKHSREG_T*)(p))
#define CC( p )							((RKHSCOND_T*)(p))
#define CJ( p )							((RKHSJUNC_T*)(p))
#define CH( p )							((RKHSHIST_T*)(p))
#define CM( p )							((RKHROM RKHSMA_T*)(p))
#define CT( p )							((RKHROM RKHTR_T*)(p))


static RKHROM RKHTR_T tr_null = { RKH_ANY, NULL, NULL, NULL };

#if RKH_SMA_EN_HCAL == 1
                                                   /* set of entered states */
static RKHROM RKHSREG_T *sentry[ RKH_SMA_MAX_HCAL_DEPTH ];
                                                     /* state nesting depth */
static rkhui8_t depth;
#endif

static RKHEVT_T *pgevt;
static RKHSMA_T *pgh;
                                      /* set of executed transition actions */
static RKHACT_T al[ RKH_SMA_MAX_TRC_SEGS ];
                                        /* pointer to transition action set */
static RKHACT_T *pal;
                                        /* # of executed transition actions */
static rkhui8_t nal;


static
HUInt
rkh_exec_exit_action( RKHROM RKHSREG_T *src, RKHROM RKHSREG_T *tgt, RKHSMA_T *sma, 
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
				islca = 1;								       /* found LCA */
				break;
			}
			else
				*snl = stn;				   /* add state in entry state list */

		if( islca == 0 )
		{
					       /* perform the exit actions of the exited states */
			RKH_EXEC_EXIT( stx, CM( sma ) );
			 						   /* update histories of exited states */
			RKH_UPDATE_SHALLOW_HIST( stx, h );
			RKH_TRCR_SM_EXSTATE( 	sma,       /* this state machine object */ 
									stx );                  /* exited state */
		}
		else
			break;
	}
											             /* save the # of: */
	*pnx = ix_x;                         				  /* exited states */
	*pnn = ix_n;                         			 /* and entered states */
	return 0;
}


#if RKH_SMA_EN_HCAL == 1
	static
	void
	rkh_exec_entry_action( rkhui8_t nen, RKHSMA_T *sma )
	{
		RKHROM RKHSREG_T *stn, **snl;
		rkhui8_t ix_n;

		/* from LCA state to target state */
		for( ix_n = nen, snl = &sentry[ ix_n ]; ix_n != 0; --ix_n )
		{
			--snl;
			RKH_EXEC_ENTRY( *snl, CM( sma ) );
			RKH_TRCR_SM_ENSTATE( sma, *snl );
		}

		/* from target state to "end" target state */
		for( stn = (*snl)->defchild; stn != CR( 0 ); stn = stn->defchild )
		{
			RKH_EXEC_ENTRY( stn, CM( sma ) );
			RKH_TRCR_SM_ENSTATE( sma, stn );
		}
	}
#else
	#define rkh_exec_entry_action( nen, sma )		((void)0)
#endif


static
HUInt
rkh_add_tr_action( RKHACT_T *list, RKHACT_T act, rkhui8_t *num )
{
	if( *num >= RKH_SMA_MAX_TRC_SEGS )
		return 1;

	if( act != CTA( 0 ) )
	{
		*list++ = act;
		++(*num);
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
rkh_exec_transition( RKHSMA_T *sma, RKHEVT_T *e, RKHACT_T *list, rkhui8_t size )
{
	while( size-- != 0 )
		RKH_CALL_ACTION( *list++, sma, e );
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
	cs = sma->state;						           /* get current state */

														    /* ---- Stage 2 */
	             /* determine the (compound) transition (CT) that will fire */
	                    /* in response to the event: traverse the states in */
	        /* the active configuration from lowest states in the hierarchy */
	           /* upwards. A CT is enabled if its trigger is the dispatched */
	                             /* event, and the guard evaluates to true. */
	       /* Once an enabled transition is found with a given source state */
	                     /* stop traversing the states that are higher than */
	                                        /* this state in the hierarchy. */
#if RKH_SMA_EN_HCAL == 1
	for( s = cs, tr = CT(0); s != CR(0); s = s->parent )
	{
		in = RKH_PROCESS_INPUT( s, sma, pe );	
		FIND_TRANS( tr, s->trtbl, in );
		if( IS_FOUND_TRANS( tr ) )
			break;
	}
#else
	s = cs;
	in = rkh_process_input( s, sma, pe );	
	FIND_TRANS( tr, s->trtbl, in );
#endif

	if( IS_NOT_FOUND_TRANS( tr ) )					   /* transition taken? */
	{
		RKH_TRCR_SM_DCH_RC( sma, RKH_INPUT_NOT_FOUND );	   /* ignored event */
		return RKH_INPUT_NOT_FOUND;
	}

	ets = tr->target;	   /* temporarily save the target of the transition */
	ts = CR( ets );

	first_regular = 1;		   /* set first regular state in the transition */
	depth = 0;							     /* and the state nesting depth */
	nal = 0;                           /* initialize transition action list */
	pal = al;
	rkh_clr_step();
#if RKH_TRC_EN == 1
	nn = nx = 0;
#endif

	RKH_TRCR_SM_DCH(	sma, 				   /* this state machine object */
						pe );									   /* event */
	RKH_TRCR_SM_TRN( 	sma, 				   /* this state machine object */
						s, 						 /* transition source state */
						ts );					 /* transition target state */

	                                                 /* enabled transition? */
	                    /* A CT is enabled if its trigger is the dispatched */
	                             /* event, and the guard evaluates to true. */
	if( IS_VALID_GUARD( tr ) && rkh_call_guard( tr, sma, pe ) == RKH_GFALSE )
	{
		RKH_TRCR_SM_DCH_RC( sma, RKH_GUARD_FALSE );
		return RKH_GUARD_FALSE;
	}
					    /* add action of the transition segment in the list */
	if( rkh_add_tr_action( pal, tr->action, &nal ) )
	{
		RKH_TRCR_SM_DCH_RC( sma, RKH_EXCEED_TRC_SEGS );
		RKHERROR();
		return RKH_EXCEED_TRC_SEGS;
	}

	rkh_inc_step();			  /* increment the number of transition segment */
	inttr = IS_INTERNAL_TRANSITION( ets );    /* is an internal transition? */

	if( IS_NOT_INTERNAL_TRANSITION() )
	{
															/* ---- Stage 3 */
		RKH_TRCR_SM_CSTATE( 	sma, 		   /* this state machine object */
			   					  /* target state of the transition segment */
								ets );

								/* ... traverses the taken transition until */
   				   		  /* the segment target state (ets) == simple state */
		while( IS_PSEUDO( ets ) || IS_COMPOSITE( ets ) )
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
					FIND_BRANCH( CC( ets )->trtbl, tr, sma, pe );

					if( IS_NOT_FOUND_TRANS( tr ) )
					{
						RKH_TRCR_SM_DCH_RC( sma, RKH_CONDITION_NOT_FOUND );
						return RKH_CONDITION_NOT_FOUND;
					}

					if( rkh_add_tr_action( pal, tr->action, &nal ) )
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
					if( rkh_add_tr_action( pal, CJ(ets)->action, &nal ) )
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
					if( IS_EMPTY_HIST( ets ) )
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

	if( IS_NOT_INTERNAL_TRANSITION() )
		if( first_regular )
			ts = CR( ets );			  /* finally, set the main target state */

#if RKH_SMA_EN_HCAL == 1
	if( IS_NOT_INTERNAL_TRANSITION() )
	{
															/* ---- Stage 4 */
			                             /* first of all, find the LCA then */
			     /* perform the exit actions of the exited states according */
		   /* to the order states are exited, from low state to high state, */
		 						      /* update histories of exited states, */
			                     /* and, generate the set of entered states */
		rkh_exec_exit_action( cs, ts, sma, &nx, &nn );
															/* ---- Stage 5 */
		                                             /* update deep history */
		rkh_update_deep_hist( CR( ets ) );
		RKH_TRCR_SM_NENEX( 	sma,               /* this state machine object */ 
							nn,                         /* # entered states */
							nx );                        /* # exited states */
	}
#endif
													        /* ---- Stage 6 */
	                  /* perform the actions on the transition sequentially */
			         /* according to the order in which they are written on */
				       /* the transition, from the action closest to source */
                            /* state to the action closest to target state. */
	rkh_exec_transition( sma, pe, al, nal );
	RKH_TRCR_SM_NTRNACT( 	sma,               /* this state machine object */ 
							nal,                      /* # executed actions */
							rkh_get_step() );      /* # transition segments */

	if( IS_NOT_INTERNAL_TRANSITION() )
	{
												 		    /* ---- Stage 7 */
		                 /* perform the entry actions of the entered states */
		                      /* according to the order states are entered, */
		                                   /* from high state to low state. */
				/* For lowest level states that were entered, which are not */
		         /* basic states, perform default transitions (recursively) */
		                      /* until the statechart reaches basic states. */
		rkh_exec_entry_action( nn, sma );
														    /* ---- Stage 8 */
		sma->state = CR( ets );                 /* update the current state */
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
