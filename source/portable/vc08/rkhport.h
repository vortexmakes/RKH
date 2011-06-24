/*
 *	file: rkhport.h - Visual Studio 2008 port
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 28, 2010
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


#include "rkhcfg.h"
#include <stdio.h>


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

typedef signed char 	rkhint8;
typedef signed short 	rkhint16;
typedef signed long		rkhint32;
typedef unsigned char 	rkhuint8;
typedef unsigned short 	rkhuint16;
typedef unsigned long	rkhuint32;

typedef unsigned int	HUInt;
typedef signed int		HInt;


/*
 * 	Declaring an object rkhrom announces that its value will
 * 	not be changed and it will be stored in ROM.
 */

#define rkhrom			const	


/*
 * 	RKH needs to disable interrupts in order to access critical
 * 	sections of code and to reenable interrupts when done.
 * 	
 * 	To hide the actual implementation method available for a
 * 	particular processor, compiler, an OS, RKH defines the 
 * 	following two macros to disable and enable interrupts 
 * 	rkh_enter_critical() and define rkh_exit_critical() respectively.
 * 	
 * 	These macros are always together to wrap critical sections of
 * 	code.
 */

#define rkh_enter_critical()
#define rkh_exit_critical()


/*
 *	Defines trace facility support.
 *
 *	This definitions are required only when the user application
 *	is used trace facility (of course, RKH_TRACE == 1).
 */

#define rkh_tropen							rkh_trace_open
#define rkh_trclose							rkh_trace_close
#define rkh_trflush							rkh_trace_flush
#define rkh_trgetts							rkh_trace_getts


/*
 *	Defines dynamic event support.
 *
 *	This definitions are required only when the user application
 *	is used dynamic event (of course, RKH_EN_DYNAMIC_EVENT == 1).
 */

#define RKH_DYNE_NUM_POOLS					3
#define rkh_dyne_init( mpd, pm, ps, bs )
#define rkh_dyne_event_size( mpd )
#define rkh_dyne_get( mpd, e )
#define rkh_dyne_put( mpd, e )
#define rkh_post_fifo( qd, e )
#define rkh_post_lifo( qd, e )
#define rkh_get( qd, e )


#endif
