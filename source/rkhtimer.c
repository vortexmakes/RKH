/*
 *	file: rkhtimer.c
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
 * 	rkhtimer.c
 *
 * 	\brief
 * 	Implements a timer services.
 */


#include "rkhtimer.h"
#include "rkh.h"


RKH_THIS_MODULE( 6, rkhtimer );


void 
rkh_timer_handler( void )
{
	RKH_iSR_CRITICAL;
	RKH_iENTER_CRITICAL();
	RKH_iEXIT_CRITICAL();
}


void 
#if RKH_TIMER_EN_HOOK == 0
rkh_itim_init( RKHT_T *t, RKHE_T sig )
#else
rkh_itim_init( RKHT_T *t, RKHE_T sig, RKH_THK_T thk )
#endif
{
	RKH_iSR_CRITICAL;
	RKH_iENTER_CRITICAL();
	RKH_iEXIT_CRITICAL();
}


void 
rkh_timer_start( RKHT_T *t, RKHSMA_T *sma, RKH_TNT_T itick )
{
	RKH_iSR_CRITICAL;
	RKH_iENTER_CRITICAL();
	RKH_iEXIT_CRITICAL();
}


void 
rkh_timer_restart( RKHT_T *t, RKH_TNT_T itick )
{
	RKH_iSR_CRITICAL;
	RKH_iENTER_CRITICAL();
	RKH_iEXIT_CRITICAL();
}


void 
rkh_timer_stop( RKHT_T *t )
{
	RKH_iSR_CRITICAL;
	RKH_iENTER_CRITICAL();
	RKH_iEXIT_CRITICAL();
}


void 
rkh_timer_get_info( RKHT_T *t, RKH_TIMERI_T *pti )
{
	RKH_iSR_CRITICAL;
	RKH_iENTER_CRITICAL();
	RKH_iEXIT_CRITICAL();
}


void 
rkh_timer_clear_info( RKHT_T *t )
{
	RKH_iSR_CRITICAL;
	RKH_iENTER_CRITICAL();
	RKH_iEXIT_CRITICAL();
}
