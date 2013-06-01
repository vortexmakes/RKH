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
 * RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * e-mail:			lf@vxtsolutions.com.ar
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
#define IS_INTERNAL_TRANSITION(s)		((s) == CST(0))
#define IS_EMPTY_HIST(s)				(*(CH(s))->target==(RKHROM void*)0 )
#define IS_FOUND_TRANS(t)				((t)->event != RKH_ANY)
#define IS_NOT_FOUND_TRANS(t)			((t)->event == RKH_ANY)
#define IS_VALID_GUARD(t)				((t)->guard != CG(0))
#define IS_PSEUDO( s )					((CB((s))->type&RKH_REGULAR)==0)
#define IS_COMPOSITE( s )				(CB((s))->type==RKH_COMPOSITE)
#define IS_SUBMACHINE( s )				(CB((s))->type==RKH_SUBMACHINE)
#define IS_REF_SUBMACHINE( s )			(CB((s))->type==RKH_REF_SUBMACHINE)

#if RKH_EN_NATIVE_SCHEDULER == 1 || RKH_EN_REENTRANT == 0
	#define RKH_RAM		static
#else
			          /* allocate the automatic variables of rkh_dispatch() */
										          /* function on the stack. */
	                                   /* Therefore, the code is reentrant. */
	#define RKH_RAM
#endif


#define FIND_TRANS( t, tbl, sig )							\
	for( 	(t) = (tbl); 									\
			(t)->event != sig && (t)->event != RKH_ANY; 	\
			++(t) )


#if RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_SHALLOW_HISTORY == 1
	#if RKH_SMA_EN_SUBMACHINE == 1
			#define RKH_UPDATE_SHALLOW_HIST( s, h )			\
				if(	CST((s))->parent != CST(0) && 			\
						IS_COMPOSITE( (s)->parent ) &&		\
					((h) = CCMP(CST((s))->parent)->history) != CH(0)&&	\
			 			CB((h))->type == RKH_SHISTORY )					\
					*(h)->target = (s)
	#else
			#define RKH_UPDATE_SHALLOW_HIST( s, h )						\
				if(	CST((s))->parent != CST(0) &&						\
					((h) = CCMP(CST((s))->parent)->history) != CH(0)&&	\
			 			CB((h))->type == RKH_SHISTORY )					\
					*(h)->target = (s)
	#endif
#else
	#define RKH_UPDATE_SHALLOW_HIST( s, h )			((void)0)
#endif


#if RKH_SMA_EN_PPRO == 1
	#define RKH_PROCESS_INPUT( s, h, pe )							\
				(RKHE_T)( ((s)->prepro != CPP(0)) ?					\
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
	#define RKH_CLR_STEP()			(step = 0)
	#define RKH_INC_STEP()			++step
	#define RKH_GET_STEP()			step
#else
	#define RKH_CLR_STEP()			((void)0)
	#define RKH_INC_STEP()			((void)0)
	#define RKH_GET_STEP()			((void)0)
#endif


#if RKH_SMA_EN_GET_INFO == 1
	#define INFO_RCV_EVENTS( p )	++(p)->hinfo.rcvevt
	#define INFO_EXEC_TRS( p )		++(p)->hinfo.exectr
#else
	#define INFO_RCV_EVENTS( p )	((void)0)
	#define INFO_EXEC_TRS( p )		((void)0)
#endif


#if RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_SUBMACHINE == 1
	#define UPDATE_PARENT( s )										\
				(s) = (s)->parent;									\
				if( (s) != CST( 0 ) && IS_REF_SUBMACHINE( (s) ) )	\
					(s) = *CRSM( (s) )->dyp
	#define UPDATE_IN_PARENT( s )									\
				(s) = (s)->parent;									\
				if( (s) != CST( 0 ) && IS_REF_SUBMACHINE( (s) ) )	\
					(s) = *CRSM( (s) )->dyp
#else
	#define UPDATE_PARENT( s )		\
				(s) = (s)->parent
	#define UPDATE_IN_PARENT( s )	\
				(s) = (s)->parent
#endif


#if RKH_SMA_EN_HCAL == 1
	#define RKH_EXEC_EXIT_ACTION( src, tgt, sma, nn )						\
		for( ix_n = 0, ix_x = islca = 0, stx = src; 						\
				stx != CST( 0 ); ++ix_x )									\
		{																	\
			for( ix_n = 0, snl = sentry, stn = tgt; 						\
					stn != CST( 0 ); ++snl, ++ix_n )						\
			{																\
				if( stx == stn )											\
				{															\
					islca = 1;								/* found LCA */ \
					break;													\
				}															\
				else if( ix_n < RKH_SMA_MAX_HCAL_DEPTH )					\
					*snl = stn;		    /* add state in entry state list */ \
				else														\
				{															\
					RKH_TR_SM_EX_HLEVEL( sma );								\
					RKHERROR();												\
					return RKH_EX_TSEG;										\
				}															\
				UPDATE_PARENT( stn );										\
			}																\
			if( islca == 0 )												\
			{																\
						/* perform the exit actions of the exited states */ \
				RKH_EXEC_EXIT( stx, CM( sma ) );							\
									/* update histories of exited states */ \
				RKH_UPDATE_SHALLOW_HIST( stx, h );							\
				RKH_TR_SM_EXSTATE( sma,   /* this state machine object */ 	\
									 stx );              /* exited state */ \
			}																\
			else															\
				break;														\
			UPDATE_PARENT( stx );											\
		}																	\
										 /* save the # of entered states */ \
		nn = ix_n
#else
	#define RKH_EXEC_EXIT_ACTION( src, tgt, sma, nn )						\
		stx = src;															\
		nn = ix_n = ix_x = (rkhui8_t)(stx != tgt)
#endif


#if RKH_SMA_EN_HCAL == 1
	#define RKH_EXEC_ENTRY_ACTION( nen, sma, stn, snl, ix_n )			\
		if( ix_n == ix_x && ix_x == 0 )          /* local transition */ \
		{}																\
		else															\
		{																\
			for( ix_n = nen, snl = &sentry[ ix_n ]; ix_n != 0; --ix_n )	\
			{															\
				--snl;													\
				RKH_EXEC_ENTRY( *snl, CM( sma ) );						\
				RKH_TR_SM_ENSTATE( sma, *snl );						\
			}															\
			stn = *snl;													\
			while( IS_COMPOSITE( stn ) )								\
			{															\
				stn = CCMP(stn)->defchild;								\
				RKH_EXEC_ENTRY( stn, CM( sma ) );						\
				RKH_TR_SM_ENSTATE( sma, stn );						\
				++nen;													\
			}															\
		}
#else
	#define RKH_EXEC_ENTRY_ACTION( nen, sma, stn, snl, ix_n )			\
		if( ix_n == ix_x && ix_x == 0 )									\
		{}																\
		else															\
		{																\
			stn = ets;													\
		}
#endif


static
HUInt
rkh_add_tr_action( RKHACT_T **list, RKHACT_T act, rkhui8_t *num )
{
	if( *num >= RKH_SMA_MAX_TRC_SEGS )
		return 1;

	if( act != CTA( 0 ) )
	{
		**list = act;                      /* store a new transition action */
		++(*list);                    /* increment the pointer to next slot */
		++(*num);           /* increment the counter of actions in the list */
	}
	return 0;
}


#if RKH_SMA_EN_HCAL == 1 && RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_DEEP_HISTORY == 1
	static
	void
	rkh_update_deep_hist( RKHROM RKHST_T *from )
	{
		RKHROM RKHST_T *s;
		RKHROM RKHSHIST_T *h;

		for( s = from->parent; 
				s != (RKHROM RKHST_T *)0; s = s->parent )
		{
#if RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_SUBMACHINE == 1
			if( IS_REF_SUBMACHINE( s ) )
			{
				s = *CRSM( s )->dyp;
				continue;
			}
#endif
			if( ( h = CCMP(s)->history ) != (RKHROM RKHSHIST_T *)0 && 
					CB(h)->type == RKH_DHISTORY )
				*h->target = from;
		}
	}
#else
	#define rkh_update_deep_hist( f )		((void)0)
#endif


void 
rkh_init_hsm( RKHSMA_T *sma )
{
#if RKH_SMA_EN_HCAL == 1
	RKHROM RKHST_T *s;
#endif

    RKHASSERT( 	sma != (RKHSMA_T *)0 && 
				sma->romrkh->istate != (RKHROM RKHST_T *)0 );
	RKH_TR_SM_INIT( sma, sma->romrkh->istate );
	RKH_EXEC_INIT( sma );

#if RKH_SMA_EN_HCAL == 1
	for( s = CST( sma->romrkh->istate );; )
	{
		RKH_EXEC_ENTRY( s, CM( sma ) );
		RKH_TR_SM_ENSTATE( sma, s );

		if( IS_COMPOSITE( s ) )
			s = CST( CCMP( s )->defchild );
		else
			break;
	}
	sma->state = s;
	rkh_update_deep_hist( sma->state );
#endif
}


#if RKH_SMA_EN_HCAL == 1 && RKH_SMA_EN_PSEUDOSTATE == 1 && ( RKH_SMA_EN_SHALLOW_HISTORY == 1 || RKH_SMA_EN_DEEP_HISTORY == 1 )
void
rkh_clear_history( RKHROM RKHSHIST_T *h )
{
	*h->target = (RKHROM void *)0;
}
#endif


HUInt
rkh_dispatch( RKHSMA_T *sma, RKHEVT_T *pe )
{
	RKHROM RKHST_T *cs, *ts;
	RKHROM void *ets;
	RKHROM RKHTR_T *tr;
	HUInt inttr;
	RKHE_T in;
#if RKH_TRC_EN == 1
	rkhui8_t step;
#endif
#if RKH_SMA_EN_HCAL == 1 && RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_SHALLOW_HISTORY == 1
	RKHROM RKHSHIST_T *h;
#endif
#if RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_SUBMACHINE == 1
	RKHROM RKHSSBM_T *dp;
#endif
	                      /* to deal with Statechart's transition sequence */
	RKH_RAM RKHROM RKHST_T *stn, *stx, **snl;
	RKH_RAM rkhui8_t ix_n, ix_x, islca, nn;
                                                   /* set of entered states */
	RKH_RAM RKHROM RKHST_T *sentry[ RKH_SMA_MAX_HCAL_DEPTH ];
                                      /* set of executed transition actions */
	RKH_RAM RKHACT_T al[ RKH_SMA_MAX_TRC_SEGS ];
                                        /* pointer to transition action set */
	RKH_RAM RKHACT_T *pal;
                                        /* # of executed transition actions */
	RKH_RAM rkhui8_t nal;


    RKHASSERT( sma != (RKHSMA_T *)0 && pe != (RKHEVT_T *)0 );

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
	for( stn = cs, tr = CT(0); stn != CST(0); )
	{
		in = RKH_PROCESS_INPUT( stn, sma, pe );	
		FIND_TRANS( tr, CBSC(stn)->trtbl, in );
		if( IS_FOUND_TRANS( tr ) )
			break;
		UPDATE_IN_PARENT( stn );
	}
#else
	stn = cs;
	in = RKH_PROCESS_INPUT( stn, sma, pe );	
	FIND_TRANS( tr, CBSC(stn)->trtbl, in );
#endif

	if( IS_NOT_FOUND_TRANS( tr ) )					   /* transition taken? */
	{
		RKH_TR_SM_EVT_NFOUND( sma );	   				   /* ignored event */
		return RKH_EVT_NFOUND;
	}

	ets = tr->target;	   /* temporarily save the target of the transition */
	ts = CST( ets );

	nn = 0;
	nal = 0;                           /* initialize transition action list */
	pal = al;
	RKH_CLR_STEP();
	RKH_TR_SM_DCH(	sma, 				   /* this state machine object */
						pe );									   /* event */
	RKH_TR_SM_TRN( 	sma, 				   /* this state machine object */
						stn, 					 /* transition source state */
						ts );					 /* transition target state */

	                                                 /* enabled transition? */
	                    /* A CT is enabled if its trigger is the dispatched */
	                             /* event, and the guard evaluates to true. */
	if( IS_VALID_GUARD( tr ) && rkh_call_guard( tr, sma, pe ) == RKH_GFALSE )
	{
		RKH_TR_SM_GRD_FALSE( sma );
		return RKH_GRD_FALSE;
	}
					    /* add action of the transition segment in the list */
	if( rkh_add_tr_action( &pal, tr->action, &nal ) )
	{
		RKH_TR_SM_EX_TSEG( sma );
		RKHERROR();
		return RKH_EX_TSEG;
	}

	RKH_INC_STEP();			  /* increment the number of transition segment */
	inttr = IS_INTERNAL_TRANSITION( ets );    /* is an internal transition? */

	if( IS_NOT_INTERNAL_TRANSITION() )
	{
															/* ---- Stage 3 */
		RKH_TR_SM_CSTATE( 	sma, 		   /* this state machine object */
			   					  /* target state of the transition segment */
								ets );

								/* ... traverses the taken transition until */
   				   		  /* the segment target state (ets) == simple state */
		while( IS_PSEUDO( ets ) || IS_SUBMACHINE( ets ) )
		{
			switch( CB(ets)->type )
			{
#if RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_CONDITIONAL == 1
				case RKH_CONDITIONAL:
					            /* found a conditional (choice) pseudostate */
										      /* in the compound transition */
						/* evaluates the guards of its outgoing transitions */
					FIND_BRANCH( CCD( ets )->trtbl, tr, sma, pe );

					if( IS_NOT_FOUND_TRANS( tr ) )
					{
						RKH_TR_SM_CND_NFOUND( sma );
						return RKH_CND_NFOUND;
					}

					if( rkh_add_tr_action( &pal, tr->action, &nal ) )
					{
						RKH_TR_SM_EX_TSEG( sma );
						RKHERROR();
						return RKH_EX_TSEG;
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
					if( rkh_add_tr_action( &pal, CJ(ets)->action, &nal ) )
					{
						RKH_TR_SM_EX_TSEG( sma );
						RKHERROR();
						return RKH_EX_TSEG;
					}
											  /* another transition segment */
					RKH_INC_STEP();
					ets = CJ(ets)->target;
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
						ets = *(CH(ets))->target;
					break;
#endif
#if RKH_SMA_EN_PSEUDOSTATE == 1 && RKH_SMA_EN_SUBMACHINE == 1
				case RKH_SUBMACHINE:
	                                            /* found a submachine state */
					*CSBM( ets )->sbm->dyp = ets;
					if( rkh_add_tr_action( &pal, CSBM( ets )->sbm->iaction, 
																	&nal ) )
					{
						RKH_TR_SM_EX_TSEG( sma );
						RKHERROR();
						return RKH_EX_TSEG;
					}
					ets = CSBM( ets )->sbm->defchild;
					break;
				case RKH_ENPOINT:
                                        /* found an entry point pseudostate */
										      /* in the compound transition */
					*CSBM(CENP( ets )->parent)->sbm->dyp = CENP( ets )->parent;
					if( rkh_add_tr_action( &pal, CENP( ets )->enpcn->action, 
																	&nal ) )
					{
						RKH_TR_SM_EX_TSEG( sma );
						RKHERROR();
						return RKH_EX_TSEG;
					}
					ets = CENP( ets )->enpcn->target;
					break;
				case RKH_EXPOINT:
	                                     /* found an exit point pseudostate */
										      /* in the compound transition */
					dp = CSBM( *CEXP( ets )->parent->dyp );
					ets = CST( &(dp->exptbl[ CEXP( ets )->ix ]) );
					if( rkh_add_tr_action( &pal, CEXPCN( ets )->action, &nal ) )
					{
						RKH_TR_SM_EX_TSEG( sma );
						RKHERROR();
						return RKH_EX_TSEG;
					}
					ets = CEXPCN( ets )->target;
					break;
#endif
				default:
						                   /* fatal error: unknown state... */
					RKH_TR_SM_UNKN_STATE( sma );
					RKHERROR();
					return RKH_UNKN_STATE;
			}
			RKH_TR_SM_CSTATE( sma, ets );
		}
	}

	if( IS_NOT_INTERNAL_TRANSITION() )
		ts = CST( ets );		      /* finally, set the main target state */

	if( IS_NOT_INTERNAL_TRANSITION() )
	{
															/* ---- Stage 4 */
			                             /* first of all, find the LCA then */
			     /* perform the exit actions of the exited states according */
		   /* to the order states are exited, from low state to high state, */
		 						      /* update histories of exited states, */
			                     /* and, generate the set of entered states */
		RKH_EXEC_EXIT_ACTION( cs, ts, sma, nn );
	}
													        /* ---- Stage 5 */
	                  /* perform the actions on the transition sequentially */
			         /* according to the order in which they are written on */
				       /* the transition, from the action closest to source */
                            /* state to the action closest to target state. */
	RKH_TR_SM_NTRNACT( 	sma,               /* this state machine object */ 
							nal,                      /* # executed actions */
							RKH_GET_STEP() );      /* # transition segments */
	RKH_EXEC_TRANSITION( sma, pe );

	if( IS_NOT_INTERNAL_TRANSITION() )
	{
												 		    /* ---- Stage 6 */
		                 /* perform the entry actions of the entered states */
		                      /* according to the order states are entered, */
		                                   /* from high state to low state. */
				/* For lowest level states that were entered, which are not */
		         /* basic states, perform default transitions (recursively) */
		                      /* until the statechart reaches basic states. */
		                        /* Also, update 'stn' with the target state */
		RKH_EXEC_ENTRY_ACTION( nn, sma, stn, snl, ix_n );
		RKH_TR_SM_NENEX( 	sma,               /* this state machine object */ 
							nn,                         /* # entered states */
							ix_x );                      /* # exited states */

															/* ---- Stage 7 */
		                                             /* update deep history */
		rkh_update_deep_hist( CST( stn ) );
														    /* ---- Stage 8 */
		sma->state = CST( stn );                /* update the current state */
		RKH_TR_SM_STATE( 	sma, 			   /* this state machine object */	
							stn );				           /* current state */
	}

	RKH_TR_SM_EVT_PROC( sma );
	INFO_EXEC_TRS( sma );
	return RKH_EVT_PROC;
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
