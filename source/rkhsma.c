/*
 *	file: rkhsma.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 23, 2012
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
 * 	\file rkhsma.c
 *	\brief
 */


#include "rkhassert.h"
#include "rkh.h"


RKH_THIS_MODULE( 8, rkhsma );


RKHSMA_T *rkh_sptbl[ RKH_MAX_SMA ];			/* registered SMA table */


void 
rkh_sma_register( RKHSMA_T *sma )
{
    rkhui8_t prio = sma->romrkh->prio;
	RKH_iSR_CRITICAL;

    RKHREQUIRE( ( 0 < prio ) && ( prio <= (rkhui8_t)RKH_MAX_SMA )
              && ( rkh_sptbl[ prio ] == ( RKHSMA_T * )0 ) );

	RKH_iENTER_CRITICAL();
    rkh_sptbl[ prio ] = sma;
	RKH_iEXIT_CRITICAL();
}


void 
rkh_sma_unregister( RKHSMA_T *sma )
{
    rkhui8_t prio = sma->romrkh->prio;
	RKH_iSR_CRITICAL;

    RKHREQUIRE( ( 0 < prio ) && ( prio <= (rkhui8_t)RKH_MAX_SMA )
              && ( rkh_sptbl[ prio ] == sma ) );

	RKH_iENTER_CRITICAL();
    rkh_sptbl[ prio ] = ( RKHSMA_T * )0;
	RKH_iEXIT_CRITICAL();
}
