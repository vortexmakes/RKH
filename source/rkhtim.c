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


RKH_THIS_MODULE( 6, rkhtim );


void 
rkh_tim_tick( void )
{
	RKH_SR_CRITICAL_;
	RKH_ENTER_CRITICAL_();
	RKH_EXIT_CRITICAL_();
}


void 
#if RKH_TIM_EN_HOOK == 0
rkh_tim_init_( RKHT_T *t, RKHE_T sig )
#else
rkh_tim_init_( RKHT_T *t, RKHE_T sig, RKH_THK_T thk )
#endif
{
	RKH_SR_CRITICAL_;
	RKH_ENTER_CRITICAL_();
	RKH_EXIT_CRITICAL_();
}


void 
rkh_tim_start( RKHT_T *t, RKHSMA_T *sma, RKH_TNT_T itick )
{
	RKH_SR_CRITICAL_;
	RKH_ENTER_CRITICAL_();
	RKH_EXIT_CRITICAL_();
}


void 
rkh_tim_restart( RKHT_T *t, RKH_TNT_T itick )
{
	RKH_SR_CRITICAL_;
	RKH_ENTER_CRITICAL_();
	RKH_EXIT_CRITICAL_();
}


void 
rkh_tim_stop( RKHT_T *t )
{
	RKH_SR_CRITICAL_;
	RKH_ENTER_CRITICAL_();
	RKH_EXIT_CRITICAL_();
}


void 
rkh_tim_get_info( RKHT_T *t, RKH_TIMERI_T *pti )
{
	RKH_SR_CRITICAL_;
	RKH_ENTER_CRITICAL_();
	RKH_EXIT_CRITICAL_();
}


void 
rkh_tim_clear_info( RKHT_T *t )
{
	RKH_SR_CRITICAL_;
	RKH_ENTER_CRITICAL_();
	RKH_EXIT_CRITICAL_();
}
