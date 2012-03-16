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

#include "rkhtype.h"
#include "rkhrq.h"
#include "rkhmp.h"
#include "rkhrdy.h"


extern CRITICAL_SECTION csection;
extern HANDLE sma_is_rdy;
extern RKHRG_T rkhrg;


const char *rkh_get_port_version( void );
const char *rkh_get_port_desc( void );


/*
 * 	Declaring an object RKHROM announces that its value will
 * 	not be changed and it will be stored in ROM.
 */

#define RKHROM			const	


#define RKH_DIS_INTERRUPT()
#define RKH_ENA_INTERRUPT()
//#define RKH_CPUSR_TYPE
#define RKH_ENTER_CRITICAL( dummy )		EnterCriticalSection( &csection )
#define RKH_EXIT_CRITICAL( dummy )		LeaveCriticalSection( &csection )


#define RKH_EQ_TYPE              		RKHRQ_T
#define RKH_OSDATA_TYPE          		HANDLE
#define RKH_THREAD_TYPE             	HANDLE


#define RKH_SMA_BLOCK( sma ) 								\
			    RKHASSERT( (sma)->eq.qty != 0 )

#define RKH_SMA_READY( rg, sma ) 							\
			    rkh_rdy_ins( (rg), (sma)->romrkh->prio ); 	\
			    (void)SetEvent( sma_is_rdy )

#define RKH_SMA_UNREADY( rg, sma ) 							\
			    rkh_rdy_rem( (rg), (sma)->romrkh->prio )

#define RKH_WAIT_FOR_EVENTS() 								\
    ((void)WaitForSingleObject( sma_is_rdy, (DWORD)INFINITE))


#define RKH_DYNE_TYPE					RKHMP_T

#define RKH_DYNE_INIT( mp, sstart, ssize, esize ) 			\
    			rkh_mp_init( (mp), sstart, ssize, esize )

#define RKH_DYNE_GET_ESIZE( mp )							\
				( (mp)->bsize )

#define RKH_DYNE_GET( mp, e )								\
				( (e) = (RKHEVT_T*)rkh_mp_get( (mp) ) )

#define RKH_DYNE_PUT( mp, e )								\
				( rkh_mp_put( (mp), e ) )


#endif
