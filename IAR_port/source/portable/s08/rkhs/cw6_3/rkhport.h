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
 *  File                     : rkhport.h
 *	Last updated for version : v2.4.04
 *	By                       : DB
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	prt
 *
 * 	\brief 		Freescale S08 MCU's, CodeWarrior v6.3 port
 */


#ifndef __RKHPORT_H__
#define __RKHPORT_H__

#include "derivative.h"
#include <hidef.h>

#include "rkhtype.h"
#include "rkhrq.h"
#include "rkhmp.h"
#include "rkhrdy.h"


const char *rkh_get_port_version( void );
const char *rkh_get_port_desc( void );


/**
 *	If the #RKH_EN_SMA_THREAD is set to 1, each SMA (active object) has its own 
 *	thread of execution.
 */

#define RKH_EN_SMA_THREAD 				0

/**
 *	If the #RKH_EN_SMA_THREAD and #RKH_EN_SMA_THREAD_DATA are set to 1, each 
 *	SMA (active object) has its own thread of execution and its own object 
 *	data.
 */

#define RKH_EN_SMA_THREAD_DATA			0

/**
 * 	If the #RKH_EN_NATIVE_SCHEDULER is set to 1 then RKH will include the 
 * 	simple, cooperative, and nonpreemptive scheduler RKHS.
 * 	When #RKH_EN_NATIVE_SCHEDULER is enabled RKH also will automatically 
 * 	define #RKH_EQ_TYPE, RKH_SMA_BLOCK(), RKH_SMA_READY(), RKH_SMA_UNREADY(), 
 * 	and assume the native priority scheme.
 */

#define RKH_EN_NATIVE_SCHEDULER			1

/**
 * 	If the #RKH_EN_NATIVE_EQUEUE is set to 1 and the native event queue is 
 *	enabled (see #RKH_RQ_EN) then RKH will include its own implementation of 
 *	rkh_sma_post_fifo(), rkh_sma_post_lifo(), and rkh_sma_get() functions.
 */

#define RKH_EN_NATIVE_EQUEUE			1

/**
 * 	If the #RKH_EN_NATIVE_DYN_EVENT is set to 1 and the native fixed-size 
 * 	memory block facility is enabled (see #RKH_MP_EN) then RKH will include 
 * 	its own implementation of dynamic memory management.
 * 	When #RKH_EN_NATIVE_DYN_EVENT is enabled RKH also will automatically 
 * 	define RKH_DYNE_TYPE, RKH_DYNE_INIT(), RKH_DYNE_GET_ESIZE(), 
 * 	RKH_DYNE_GET(), and RKH_DYNE_PUT().
 */

#define RKH_EN_NATIVE_DYN_EVENT			1

/**
 *	If the #RKH_EN_REENTRANT is set to 1, the RKH event dispatch allows to be 
 *	invoked from several threads of executions. Enable this only if the 
 *	application is based on a multi-thread architecture.
 */

#define RKH_EN_REENTRANT				0

/**
 * 	Specify the size of void pointer. The valid values [in bits] are 
 * 	16 or 32. Default is 32. See RKH_TRC_SYM() macro.
 */

#define RKH_TRC_SIZEOF_POINTER			32

/**
 * 	Specify the size of function pointer. The valid values [in bits] are 
 * 	16 or 32. Default is 32. See RKH_TUSR_FUN() and RKH_TRC_FUN() macros.
 */

#define RKH_TRC_SIZEOF_FUN_POINTER		32

/** 
 * 	Specify the number of bytes (size) used by the trace record timestamp. 
 * 	The valid values [in bits] are 8, 16 or 32. Default is 16.
 */

#define RKH_TRC_SIZEOF_TSTAMP			32u


/* 
 * This port use the native, simple, cooperative, and nonpreemptive 
 * scheduler RKHS.
 */

#include "rkhs.h"


/*
 * 	Declaring an object RKHROM announces that its value will
 * 	not be changed and it will be stored in ROM.
 */

#define RKHROM			const	


#define RKH_DIS_INTERRUPT()				DisableInterrupts
#define RKH_ENA_INTERRUPT()				EnableInterrupts
//#define RKH_CPUSR_TYPE

void rkh_enter_critical( void );
void rkh_exit_critical( void );


#define RKH_ENTER_CRITICAL( dummy )		rkh_enter_critical()
#define RKH_EXIT_CRITICAL( dummy )		rkh_exit_critical()

#define RKH_EQ_TYPE              		RKHRQ_T



#endif
