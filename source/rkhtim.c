/*
 *	file: rkhtim.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 24, 2012
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
 * e-mail:			francuccilea@gmail.com
 */

/**
 * 	rkhtim.c
 *
 * 	\brief
 * 	Implements a timer services.
 */


#include "rkhassert.h"
#include "rkhtim.h"
#include "rkh.h"


#if RKH_TIM_EN == 1

RKH_MODULE_NAME( rkhtim )


#define CPTIM( p )			(( RKHT_T* )(p))

#if RKH_TIM_EN_HOOK == 1
	#define RKH_EXEC_THOOK()							\
					if( t->timhk != ( RKH_THK_T )0 )	\
						(*t->timhk)( t )
	#define RKH_SET_THOOK( t, hk )		\
					(t)->timhk = (hk)
#else
	#define RKH_EXEC_THOOK() \
					(void)0
	#define RKH_SET_THOOK( t, hk ) \
					(void)0
#endif

#define add_to_list( t ) \
			(t)->tnext = thead; \
			thead = (t); \
			(t)->used = 1


static RKHT_T *thead;


static
void
rem_from_list( RKHT_T *t, RKHT_T *tprev )
{
	if( thead == t )			/* is first timer in the list? */
		thead = t->tnext;
	else
		tprev->tnext = t->tnext;
	t->used = 0;
	RKH_TR_TIM_REM( t );
}


void 
rkh_tim_tick( void )
{
	RKHT_T *t, *tprev;
	RKH_SR_CRITICAL_;

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
				RKH_TR_TIM_TOUT( t );
				if( t->period == 0 )
					rem_from_list( t, tprev );
				else
				{
					t->ntick = t->period;
					tprev = t;
				}
				RKH_HK_TIMEOUT( t );
				RKH_EXEC_THOOK();
				rkh_sma_post_fifo( ( RKHSMA_T* )t->sma, t->evt );
			}
			else
				tprev = t;
		}
	RKH_EXIT_CRITICAL_();
}


void 
#if RKH_TIM_EN_HOOK == 0
rkh_tim_init_( RKHT_T *t, RKHEVT_T *e )
#else
rkh_tim_init_( RKHT_T *t, RKHEVT_T *e, RKH_THK_T thk )
#endif
{
	RKH_SR_CRITICAL_;
	RKHREQUIRE( t != CPTIM(0) && e != CE(0) );

	RKH_ENTER_CRITICAL_();
	t->ntick = 0;
	t->used = 0;
	t->evt = e;
	RKH_EXIT_CRITICAL_();

	RKH_SET_THOOK( t, thk );
	RKH_TR_TIM_INIT( t, t->evt->e );
}


void 
rkh_tim_start( RKHT_T *t, const RKHSMA_T *sma, RKH_TNT_T itick )
{
	RKH_SR_CRITICAL_;
	RKHREQUIRE( t != CPTIM(0) && sma != (const RKHSMA_T *)0 && itick != 0 );

	RKH_ENTER_CRITICAL_();
	t->sma = sma;
	t->ntick = itick;
	if( t->used == 0 )
		add_to_list( t );
	RKH_EXIT_CRITICAL_();

	RKH_TR_TIM_START( t, itick, sma );
}


void 
rkh_tim_stop( RKHT_T *t )
{
	RKH_SR_CRITICAL_;
	RKHREQUIRE( t != CPTIM(0) );

	RKH_ENTER_CRITICAL_();
	t->ntick = 0;
	RKH_EXIT_CRITICAL_();

	RKH_TR_TIM_STOP( t );
}


#if RKH_TIM_EN_GET_INFO	== 1
void 
rkh_tim_get_info( RKHT_T *t, RKH_TINFO_T *info )
{
	RKH_SR_CRITICAL_;

	RKH_ENTER_CRITICAL_();
	*info = t->info;
	RKH_EXIT_CRITICAL_();
}


void 
rkh_tim_clear_info( RKHT_T *t )
{
	RKH_TINFO_T *pi;
	RKH_SR_CRITICAL_;

	pi = &t->info;

	RKH_ENTER_CRITICAL_();
	pi->nexp = pi->nstart = pi->nstop = 0;
	RKH_EXIT_CRITICAL_();
}
#endif

#endif
