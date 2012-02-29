/*
 *	file: rkhport.c - Visual Studio 2008 port
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 22, 2012
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

/*
 * 	rkhport.c
 */


#include "rkh.h"


CRITICAL_SECTION csection;	/* Win32 critical section */
HANDLE sma_is_ready;          	/* Win32 event to signal when AOs are ready */
RKHRG_T rkhrg;						/* ready set of active objects */



void 
rkh_init( void )
{
}


void rkh_enter( void )
{
}


void rkh_exit( void )
{
}


void rkh_sma_init(	RKHSMA_T *sma, const void **qs, RKH_RQNE_T qsize, 
					void *stks, rkhui32_t stksize )
{
}


void rkh_sma_terminate( RKHSMA_T *sma )
{
}
