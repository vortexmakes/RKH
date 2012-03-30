/*
 *	file: rkhs.h
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

/**
 * 	\file rkhs.h
 *	\brief
 *	Platform-independent interface to the RKS scheduler.
 */


#ifndef __RKHS_H__
#define __RKHS_H__


#include "rkhcfg.h"
#include "rkh.h"
#include "rkhevt.h"


#if RKH_EN_NATIVE_SCHEDULER == 1

	/**
	 * 	\brief
	 * 	Data type of the event queue for SMA (active object).
	 */

	#define RKH_EQ_TYPE				RKHRQ_T

	/**
	 * 	\brief
	 * 	Encapsulates the mechanism of blocking the used event queue.
	 */

	#define RKH_SMA_BLOCK( sma ) 							\
					RKHASSERT( ((RKHSMA_T*)(sma))->equeue.qty != 0 )

	/**
	 * 	\brief
	 * 	Encapsulates the mechanism of signaling the thread waiting on the 
	 * 	used event queue. Thus, the SMA is inserted in the ready list as 
	 * 	ready-to-dispatch.
	 */

	#define RKH_SMA_READY( rg, sma ) 						\
					rkh_rdy_ins( (rg), ((RKHSMA_T*)(sma))->romrkh->prio )

	/**
	 * 	\brief
	 * 	Informs the underlying kernel that the SMA event queue is becoming 
	 * 	empty. Thus, the SMA is removed from the ready list.
	 */

	#define RKH_SMA_UNREADY( rg, sma ) 						\
					rkh_rdy_rem( (rg), ((RKHSMA_T*)(sma))->romrkh->prio )

	/**
	 * 	\brief
	 * 	List of ready active objects.
	 */

	extern RKHRG_T rkhrg;

#endif
#endif
