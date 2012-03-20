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
 * RKH web site:	http://
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


RKH_MODULE_NAME( rkhtim );


#define CPT( p )		(( RKHT_T* )(p))
static RKHT_T *thead;


void 
rkh_tim_tick( void )
{
	RKHT_T *t;
	RKH_SR_CRITICAL_;

	if( thead == CPT( 0 ) )	/* is empty list? */
		return;

	RKH_ENTER_CRITICAL_();

	for( t = thead; t->tnext != CPT( 0 ); t = t->tnext )
	{
		if( !--t->ntick )
		{
			if( t->period != 0 )
				t->ntick = t->period;
			else
			{
				if( thead == t )
					thead = t->tnext;
				else
				{
					t->tprev->tnext = t->tnext;
					if( t->tnext != ( RKHT_T* )0 )
						t->tnext->tprev = t->tprev;
				}

			}
			rkh_sma_post_fifo( t->sma, &t->evt );
		}

	}
	RKH_EXIT_CRITICAL_();
}


void 
#if RKH_TIM_EN_HOOK == 0
rkh_tim_init_( RKHT_T *t, RKHE_T sig )
#else
rkh_tim_init_( RKHT_T *t, RKHE_T sig, RKH_THK_T thk )
#endif
{
	t->ntick = 0;
	t->tprev = ( RKHT_T* )0;
	RKH_SET_STATIC_EVENT( &t->evt, sig );
#if RKH_TIM_EN_HOOK == 1
	t->timhk = thk;
#endif
	
	RKH_TRCR_TIM_INIT( t, sig );
}


void 
rkh_tim_start( RKHT_T *t, RKHSMA_T *sma, RKH_TNT_T itick )
{
	RKH_SR_CRITICAL_;
	
	RKHREQUIRE( 	t != ( RKHT_T* )0 && 
					sma != ( RKHSMA_T* )0 && 
					itick != 0 &&
					t->tprev != ( RKHT_T* )0 );

	t->sma = sma;
	t->ntick = itick;

	RKH_ENTER_CRITICAL_();

	if( thead != ( RKHT_T* )0 )
		thead->tprev = t;

	t->tnext = thead;
	thead = t;
	t->tprev = t;

	RKH_EXIT_CRITICAL_();
	RKH_TRCR_TIM_START( t, itick, sma );
}


void 
rkh_tim_restart( RKHT_T *t, RKH_TNT_T itick )
{
	RKH_SR_CRITICAL_;

	RKHREQUIRE( 	t != ( RKHT_T* )0 && 
					t->sma != ( RKHSMA_T* )0 && 
					itick == 0 &&
					t->tprev == ( RKHT_T* )0 );

	RKH_ENTER_CRITICAL_();

	t->ntick = itick;
	if( t->tprev == ( RKHT_T* )0 )
	{
		if( thead != ( RKHT_T* )0 )
			thead->tprev = t;
	
		t->tnext = thead;
		thead = t;
		t->tprev = t;
	}

	RKH_EXIT_CRITICAL_();
	RKH_TRCR_TIM_RESTART( t, itick );
}


void 
rkh_tim_stop( RKHT_T *t )
{
	RKH_SR_CRITICAL_;

	RKHREQUIRE( t != ( RKHT_T* )0 );

	RKH_ENTER_CRITICAL_();
	
	if( t->tprev == ( RKHT_T* )0 )
		return;

	t->ntick = 0;
	if( thead == t )
		thead = t->tnext;				/* first timer in the list */
	else
	{
		t->tprev->tnext = t->tnext;
		if( t->tnext != ( RKHT_T* )0 )
			t->tnext->tprev = t->tprev;	/* last timer in the list */
	}

	RKH_EXIT_CRITICAL_();
	RKH_TRCR_TIM_STOP( t );
}


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
