/*
 *	file: rkhport.h - Visual Studio 2008 port
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 27, 2012
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
 * 	rkhport.h
 */


#ifndef __RKHPORT_H__
#define __RKHPORT_H__


#include <windows.h>
#include "rkhcfg.h"
#include "rkhassert.h"
#include "rkhrque.h"
#include "rkhmp.h"
#include "rkhrdy.h"


/*
 * 	Portable data types.
 *
 * 	The RKH uses a set of integer quantities. That maybe 
 * 	machine or compiler	dependent.
 *
 * 	Note:
 *
 * 	The 'HUInt' and 'HInt' will normally be the natural size 
 * 	for a particular machine. These types designates an integer 
 * 	type that is usually fastest to operate with among all integer 
 * 	types.
 */

typedef signed char 	rkhi8_t;
typedef signed short 	rkhi16_t;
typedef signed long		rkhi32_t;
typedef unsigned char 	rkhui8_t;
typedef unsigned short 	rkhui16_t;
typedef unsigned long	rkhui32_t;

typedef unsigned int	HUInt;
typedef signed int		HInt;


/*
 * 	Declaring an object RKHROM announces that its value will
 * 	not be changed and it will be stored in ROM.
 */

#define RKHROM			const	


#define RKH_CPUSR_TYPE
#define RKH_ENTER_CRITICAL( dummy )		EnterCriticalSection( &csection )
#define RKH_EXIT_CRITICAL( dummy )		LeaveCriticalSection( &csection )


/*
 *	Defines trace facility support.
 *
 *	This definitions are required only when the user application
 *	is used trace facility (of course, RKH_TRACE == 1).
 */

#define rkh_tropen						rkh_trace_open
#define rkh_trclose						rkh_trace_close
#define rkh_trflush						rkh_trace_flush
#define rkh_trgetts						rkh_trace_getts


#define RKH_EQ_TYPE              		RKHRQ_T
#define RKH_OSDATA_TYPE          		HANDLE
#define RKH_THREAD_TYPE             	HANDLE


#define RKH_SMA_BLOCK( sma ) 								\
    RKHASSERT( (sma)->eq.qty != 0 )

#define RKH_SMA_READY( sma ) 								\
    QPSet64_insert(&QF_readySet_, (me_)->prio); 			\
    (void)SetEvent(QF_win32Event_)

#define RKH_SMA_UNREADY( sma ) 								\
    QPSet64_remove(&QF_readySet_, (me_)->prio)


#define RKH_DYNE_TYPE					RKHMP_T

#define RKH_DYNE_INIT( mp, sstart, ssize, esize ) 			\
    			rkh_mp_init( &(mp), sstart, ssize, esize )

#define RKH_DYNE_GET_ESIZE( mp )							\
				( (mp).bsize )

#define QF_DYNE_GET( mp, e )								\
				( (e) = (RKHEVT_T*)rk_mpool_get( &(mp) ) )

#define QF_DYNE_PUT( mp, e )								\
				( rkh_mp_put( &(mp), e ) )


extern CRITICAL_SECTION csection;
extern HANDLE  sma_is_ready;
extern RKH_RG64_T rkh_rdygrp;


#endif
