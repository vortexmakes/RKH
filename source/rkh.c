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


#define RKH_EXEC_TRANSITION( sma, e )							\
				for( pal = al; nal != 0; ++pal, --nal )			\
					RKH_CALL_ACTION( *pal, (sma), (e) )


#if RKH_TRC_EN == 1
	#define RKH_CLR_STEP()				(step = 0)
	#define RKH_INC_STEP()				++step
	#define RKH_GET_STEP()				step
#else
	#define RKH_CLR_STEP()
	#define RKH_INC_STEP()
	#define RKH_GET_STEP()
#endif


#if RKH_SMA_EN_GET_INFO == 1
	#define INFO_RCV_EVENTS( p )		++(p)->hinfo.rcvevt
	#define INFO_EXEC_TRS( p )			++(p)->hinfo.exectr
#else
	#define INFO_RCV_EVENTS( p )		((void)0)
	#define INFO_EXEC_TRS( p )			((void)0)
#endif

	                                                  /* macros for casting */
#define CB( p )							((RKHBASE_T*)(p))
#define CR( p )							((RKHSREG_T*)(p))
#define CC( p )							((RKHSCOND_T*)(p))
#define CJ( p )							((RKHSJUNC_T*)(p))
#define CH( p )							((RKHSHIST_T*)(p))
#define CM( p )							((RKHROM RKHSMA_T*)(p))
#define CT( p )							((RKHROM RKHTR_T*)(p))


static RKHROM RKHTR_T tr_null = { RKH_ANY, NULL, NULL, NULL };


#define RKH_EXEC_EXIT_ACTION( src, tgt, sma, nn )						\
	for( ix_n = 0, ix_x = islca = 0, stx = src; 						\
			stx != CR( 0 ); stx = stx->parent, ++ix_x )					\
	{																	\
		for( ix_n = 0, snl = sentry, stn = tgt; 						\
				stn != CR( 0 );	stn = stn->parent, ++snl, ++ix_n )		\
			if( stx == stn )											\
			{															\
				islca = 1;								/* found LCA */ \
				break;													\
			}															\
			else if( ix_n < RKH_SMA_MAX_HCAL_DEPTH )					\
				*snl = stn;		    /* add state in entry state list */ \
			else														\
			{															\
				RKH_TRCR_SM_DCH_RC( sma, RKH_EXCEED_HCAL_LEVEL );		\
				RKHERROR();												\
				return RKH_EXCEED_TRC_SEGS;								\
			}															\
		if( islca == 0 )												\
		{																\
			        /* perform the exit actions of the exited states */ \
			RKH_EXEC_EXIT( stx, CM( sma ) );							\
			 			        /* update histories of exited states */ \
			RKH_UPDATE_SHALLOW_HIST( stx, h );							\
			RKH_TRCR_SM_EXSTATE( sma,   /* this state machine object */ \
								 stx );              /* exited state */ \
		}																\
		else															\
			break;														\
	}																	\
	                                 /* save the # of entered states */ \
	nn = ix_n


#if RKH_SMA_EN_HCAL == 1
	#define RKH_EXEC_ENTRY_ACTION( nen, sma, stn, snl, ix_n )				\
		for( ix_n = nen, snl = &sentry[ ix_n ]; ix_n != 0; --ix_n )			\
		{																	\
			--snl;															\
			RKH_EXEC_ENTRY( *snl, CM( sma ) );								\
			RKH_TRCR_SM_ENSTATE( sma, *snl );								\
		}																	\
		for( stn = (*snl)->defchild; stn != CR( 0 ); stn = stn->defchild )	\
		{																	\
			RKH_EXEC_ENTRY( stn, CM( sma ) );								\
			RKH_TRCR_SM_ENSTATE( sma, stn );								\
		}
#else
	#define RKH_EXEC_ENTRY_ACTION( nen, sma, stn, snl, ix_n )				\
					((void)0)
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
	RKHROM RKHSREG_T *cs, *ts;
	RKHROM void *ets;
	RKHROM RKHTR_T *tr;
	HUInt first_regular, inttr;
	RKHE_T in;
#if RKH_TRC_EN == 1
	rkhui8_t step, nn;
#endif
	                      /* to deal with Statechart's transition sequence */
	RKHROM RKHSREG_T *stn, *stx, **snl;
	rkhui8_t ix_n, ix_x, islca;
#if RKH_SMA_EN_HCAL == 1 && RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_SHALLOW_HISTORY == 1
	RKHROM RKHSHIST_T *h;
#endif
                                                   /* set of entered states */
	RKHROM RKHSREG_T *sentry[ RKH_SMA_MAX_HCAL_DEPTH ];
                                      /* set of executed transition actions */
	RKHACT_T al[ RKH_SMA_MAX_TRC_SEGS ];
                                        /* pointer to transition action set */
	RKHACT_T *pal;
                                        /* # of executed transition actions */
	rkhui8_t nal;


    RKHASSERT( 	sma != NULL && pe != NULL );

	inttr = 0;
	INFO_RCV_EVENTS( sma );
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
	for( stn = cs, tr = CT(0); stn != CR(0); stn = stn->parent )
	{
		in = RKH_PROCESS_INPUT( stn, sma, pe );	
		FIND_TRANS( tr, stn->trtbl, in );
		if( IS_FOUND_TRANS( tr ) )
			break;
	}
#else
	stn = cs;
	in = rkh_process_input( stn, sma, pe );	
	FIND_TRANS( tr, stn->trtbl, in );
#endif

	if( IS_NOT_FOUND_TRANS( tr ) )					   /* transition taken? */
	{
		RKH_TRCR_SM_DCH_RC( sma, RKH_INPUT_NOT_FOUND );	   /* ignored event */
		return RKH_INPUT_NOT_FOUND;
	}

	ets = tr->target;	   /* temporarily save the target of the transition */
	ts = CR( ets );

	nn = 0;
	first_regular = 1;		   /* set first regular state in the transition */
	nal = 0;                           /* initialize transition action list */
	pal = al;
	RKH_CLR_STEP();
	RKH_TRCR_SM_DCH(	sma, 				   /* this state machine object */
						pe );									   /* event */
	RKH_TRCR_SM_TRN( 	sma, 				   /* this state machine object */
						stn, 					 /* transition source state */
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

	RKH_INC_STEP();			  /* increment the number of transition segment */
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
					RKH_INC_STEP();
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
					RKH_INC_STEP();
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
		RKH_EXEC_EXIT_ACTION( cs, ts, sma, nn );
															/* ---- Stage 5 */
		                                             /* update deep history */
		rkh_update_deep_hist( CR( ets ) );
		RKH_TRCR_SM_NENEX( 	sma,               /* this state machine object */ 
							ix_n,                       /* # entered states */
							ix_x );                      /* # exited states */
	}
#endif
													        /* ---- Stage 6 */
	                  /* perform the actions on the transition sequentially */
			         /* according to the order in which they are written on */
				       /* the transition, from the action closest to source */
                            /* state to the action closest to target state. */
	RKH_TRCR_SM_NTRNACT( 	sma,               /* this state machine object */ 
							nal,                      /* # executed actions */
							RKH_GET_STEP() );      /* # transition segments */
	RKH_EXEC_TRANSITION( sma, pe );

	if( IS_NOT_INTERNAL_TRANSITION() )
	{
												 		    /* ---- Stage 7 */
		                 /* perform the entry actions of the entered states */
		                      /* according to the order states are entered, */
		                                   /* from high state to low state. */
				/* For lowest level states that were entered, which are not */
		         /* basic states, perform default transitions (recursively) */
		                      /* until the statechart reaches basic states. */
		RKH_EXEC_ENTRY_ACTION( nn, sma, stn, snl, ix_n );
														    /* ---- Stage 8 */
		sma->state = CR( ets );                 /* update the current state */
		RKH_TRCR_SM_STATE( 	sma, 			   /* this state machine object */	
							sma->state );				   /* current state */
	}

	RKH_TRCR_SM_DCH_RC( sma, RKH_OK );
	INFO_EXEC_TRS( sma );
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
