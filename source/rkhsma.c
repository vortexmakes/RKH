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
 *  File                     : rkhsma.c
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	sch
 *
 * 	\brief 		Implements the SMA (active object) registration.
 */


#include "rkhassert.h"
#include "rkh.h"


RKH_MODULE_NAME( rkhsma )


/*
 * 	String describing the RKH version.
 */

RKHROM char rkh_version[] = 
{
	(char)( (rkhui8_t)((RKH_VERSION_CODE >> 12)	& 0x0F) + (rkhui8_t)'0' ),
	(char)'.',
	(char)( (rkhui8_t)((RKH_VERSION_CODE >> 8)	& 0x0F) + (rkhui8_t)'0' ),
	(char)'.',
	(char)( (rkhui8_t)((RKH_VERSION_CODE >> 4)	& 0x0F) + (rkhui8_t)'0' ),
	(char)( (rkhui8_t)(RKH_VERSION_CODE 		& 0x0F) + (rkhui8_t)'0' ),
	(char)'\0',
};


RKHSMA_T *rkh_sptbl[ RKH_MAX_SMA ];			/* registered SMA table */


void 
rkh_sma_register( RKHSMA_T *sma )
{
    rkhui8_t prio = RKH_GET_PRIO(sma);
	RKH_SR_ALLOC();

    RKHREQUIRE(	(prio <= (rkhui8_t)RKH_LOWEST_PRIO) && 
				(rkh_sptbl[ prio ] == (RKHSMA_T *)0));

	RKH_ENTER_CRITICAL_();
    rkh_sptbl[ prio ] = sma;
	RKH_EXIT_CRITICAL_();
	RKH_TR_SMA_REG( sma, prio );
}


void 
rkh_sma_unregister( RKHSMA_T *sma )
{
    rkhui8_t prio = RKH_GET_PRIO(sma);
	RKH_SR_ALLOC();

    RKHREQUIRE(	(prio <= (rkhui8_t)RKH_MAX_SMA) && 
				(rkh_sptbl[ prio ] == sma));

	RKH_ENTER_CRITICAL_();
    rkh_sptbl[ prio ] = ( RKHSMA_T * )0;
	RKH_EXIT_CRITICAL_();
	RKH_TR_SMA_UNREG( sma, prio );
}
