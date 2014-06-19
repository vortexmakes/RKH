/**
 * \cond
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 * 	          State-machine framework for reactive embedded systems            
 * 	        
 * 	                    Copyright (C) 2010 Leandro Francucci.
 * 	        All rights reserved. Protected by international copyright laws.
 *
 *
 * 	RKH is free software: you can redistribute it and/or modify it under the 
 * 	terms of the GNU General Public License as published by the Free Software 
 * 	Foundation, either version 3 of the License, or (at your option) any 
 * 	later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY 
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for 
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along 
 *  with RKH, see copying.txt file.
 *
 * 	Contact information:
 * 	RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * 	e-mail:			francuccilea@gmail.com
 *
 *  --------------------------------------------------------------------------
 *  File                     : rkhtim.c
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	tmr
 *
 * 	\brief 		Implements the software timer.
 */


#include "rkhassert.h"
#include "rkhtim.h"
#include "rkh.h"


#if RKH_TIM_EN == RKH_ENABLED

RKH_MODULE_NAME( rkhtim )


#define CPTIM( p )			(( RKHT_T* )(p))

#if RKH_TIM_EN_HOOK == RKH_ENABLED
	#define RKH_EXEC_THOOK()							\
					if( t->timhk != ( RKH_THK_T )0 )	\
						(*t->timhk)( t )
	#define RKH_SET_THOOK( t, hk )		\
					(t)->timhk = (hk)
#else
	#define RKH_EXEC_THOOK()			(void)0
	#define RKH_SET_THOOK( t, hk )		(void)0
#endif

#define add_to_list( t ) \
			(t)->tnext = thead; \
			thead = (t); \
			(t)->used = 1


#if defined( RKH_USE_TRC_SENDER )
	#define RKH_TICK_POST( t_, sender_ ) \
				RKH_SMA_POST_FIFO((RKHSMA_T *)t_->sma, t_->evt, \
						sender_ != (const void *)0 ? sender_ : t_)
#else
	#define RKH_TICK_POST( t_, sender_ ) \
					RKH_SMA_POST_FIFO((RKHSMA_T *)t_->sma, t_->evt, sender_ )
#endif


static RKHT_T *thead;


static
void
rem_from_list( RKHT_T *t, RKHT_T *tprev )
{
	RKH_SR_ALLOC();

	if( thead == t )			/* is first timer in the list? */
		thead = t->tnext;
	else
		tprev->tnext = t->tnext;
	t->used = 0;
	RKH_TR_TIM_REM( t );
}
				

void 
#if defined( RKH_USE_TRC_SENDER )
rkh_tim_tick( const void *const sender )
#else
rkh_tim_tick( void )
#endif
{
	RKHT_T *t, *tprev;
	RKH_SR_ALLOC();

	RKH_HK_TIMETICK();			/* call user definable hook */

	RKH_ENTER_CRITICAL_();
	if( thead == CPTIM(0) )		/* is empty list? */
	{
		RKH_EXIT_CRITICAL_();
		return;
	}
	
	for( tprev = CPTIM(0), t = thead; t != CPTIM(0); t = t->tnext )
		if( t->ntick == 0 )
			rem_from_list( t, tprev );
		else
		{
			if( !--t->ntick )
			{
				RKH_TR_TIM_TOUT( t, t->evt->e, t->sma );
				if( t->period == 0 )
					rem_from_list( t, tprev );
				else
				{
					t->ntick = t->period;
					tprev = t;
				}
				RKH_HK_TIMEOUT( t );
				RKH_EXEC_THOOK();
				RKH_TICK_POST( t, sender );
			}
			else
				tprev = t;
		}
	RKH_EXIT_CRITICAL_();
}


void 
#if RKH_TIM_EN_HOOK == RKH_DISABLED
rkh_tim_init_( RKHT_T *t, const RKHEVT_T *e )
#else
rkh_tim_init_( RKHT_T *t, const RKHEVT_T *e, RKH_THK_T thk )
#endif
{
	RKH_SR_ALLOC();
	RKHREQUIRE( t != CPTIM(0) && e != CCE(0) );

	RKH_ENTER_CRITICAL_();
	t->ntick = 0;
	t->used = 0;
	t->evt = CE(e);
	RKH_EXIT_CRITICAL_();

	RKH_SET_THOOK( t, thk );
	RKH_TR_TIM_INIT( t, t->evt->e );
}


void 
rkh_tim_start( RKHT_T *t, const struct rkhsma_t *sma, RKH_TNT_T itick )
{
	RKH_SR_ALLOC();

	RKHREQUIRE( t != CPTIM(0) && sma != (const struct rkhsma_t *)0 && itick != 0 );
	RKH_ENTER_CRITICAL_();

	t->sma = sma;
	t->ntick = itick;
	if( t->used == 0 )
		add_to_list( t );

	RKH_EXIT_CRITICAL_();
	RKH_TR_TIM_START( t, sma, itick, t->period );
}


void 
rkh_tim_stop( RKHT_T *t )
{
	RKH_SR_ALLOC();

	RKHREQUIRE( t != CPTIM(0) );
	RKH_TR_TIM_STOP( t, t->ntick, t->period );

	RKH_ENTER_CRITICAL_();
	t->ntick = 0;
	RKH_EXIT_CRITICAL_();

}


#if RKH_TIM_EN_GET_INFO	== RKH_ENABLED
void 
rkh_tim_get_info( RKHT_T *t, RKH_TINFO_T *info )
{
	RKH_SR_ALLOC();

	RKH_ENTER_CRITICAL_();
	*info = t->info;
	RKH_EXIT_CRITICAL_();
}


void 
rkh_tim_clear_info( RKHT_T *t )
{
	RKH_TINFO_T *pi;
	RKH_SR_ALLOC();

	pi = &t->info;

	RKH_ENTER_CRITICAL_();
	pi->nexp = pi->nstart = pi->nstop = 0;
	RKH_EXIT_CRITICAL_();
}
#endif

#endif
