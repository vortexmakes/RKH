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
 *	
 *	The active object computing model can work with nonpreemptive kernels. 
 *	In fact, one particular cooperative kernel matches the active object 
 *	computing model exceptionally well and can be implemented in an 
 *	absolutely portable manner. A very powerful yet simple solution is 
 *	exaplained below, the simple RKHS kernel.
 *
 *	The simple nonpreemptive kernel executes one active object at a time in 
 *	the infinite loop (similar to the "superloop"). 
 *	The RKHS kernel is engaged after each event is processed in the 
 *	run-to-completion (RTC) fashion to choose the next highest-priority 
 *	active object ready to process the next event. The RKHS scheduler is 
 *	cooperative, which means that all active objects cooperate to share a 
 *	single CPU and implicitly yield to each other after every RTC step. The 
 *	kernel is nonpreemptive, meaning that every active object must completely 
 *	process an event before any other active object can start processing 
 *	another event.
 *
 *	The ISRs can preempt the execution of active objects at any time, but due 
 *	to the simplistic nature of the RKHS kernel, every ISR returns to exactly 
 *	the preemption point. If the ISR posts an event to any active object, the 
 *	processing of this event won't start until the current RTC step completes. 
 *	The maximum time an event for the highest-priority active object can be 
 *	delayed this way is called the task-level response. With the 
 *	nonpreemptive RKHS kernel, the task-level response is equal to the longest 
 *	RTC step of all active objects in the system. Note that the task-level 
 *	response of the RKHS kernel is still a lot better than the traditional 
 *	"superloop" (a.k.a. main+ISRs) architecture.
 *
 *	The task-level response of the simple RKHS kernel turns out to be 
 *	adequate for surprisingly many applications because state machines by 
 *	nature handle events quickly without a need to busy-wait for events. 
 *	(A state machine simply runs to completion and becomes dormant until 
 *	another event arrives.) Also note that often you can make the task-level 
 *	response as fast as you need by breaking up longer RTC steps into shorter 
 *	ones.
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
