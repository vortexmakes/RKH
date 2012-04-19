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
 *	<b>Run-to-completation execution model</b>
 *	
 *	Event occurrences are detected, dispatched, and then processed by the 
 *	state machine, one at a time. The order of dequeuing is not defined, 
 *	leaving open the possibility of modeling different priority-based schemes.
 *	The semantics of event occurrence processing is based on the 
 *	run-to-completion assumption, interpreted as run-to-completion (RTC) 
 *	processing. Run-to-completion processing means that an event occurrence 
 *	can only be taken from the pool and dispatched if the processing of the 
 *	previous current occurrence is fully completed.
 *	
 *	The processing of a single event occurrence by a state machine is known 
 *	as a run-to-completion step. An RTC step is the period of time in which 
 *	events are accepted and acted upon. Processing an event always completes 
 *	within a single model step, including exiting the source state, executing 
 *	any associated actions, and entering the target state. Before commencing 
 *	on a run-to-completion step, a state machine is in a stable state 
 *	configuration with all entry/exit/internal activities (but not 
 *	necessarily state (do) activities) completed. The same conditions apply 
 *	after the run-to-completion step is completed. Thus, an event occurrence 
 *	will never be processed while the state machine is in some intermediate 
 *	and inconsistent situation. 
 *	The run-to-completion step is the passage between two state 
 *	configurations of the state machine. The run-to-completion assumption 
 *	simplifies the transition function of the state machine, since 
 *	concurrency conflicts are avoided during the processing of event, 
 *	allowing the state machine to safely complete its run-to-completion step.
 *	
 *	When an event occurrence is detected and dispatched, it may result in one 
 *	or more transitions being enabled for firing. If no transition is enabled 
 *	and the event (type) is not in the deferred event list of the current 
 *	state configuration, the event occurrence is discarded and the 
 *	run-to-completion step is completed.
 *	During a transition, a number of actions may be executed. If such an 
 *	action is a synchronous operation invocation on an object executing a 
 *	state machine, then the transition step is not completed until the invoked 
 *	object completes its run-to-completion step.
 *	
 *	The RKH implementation preserves the transition sequence imposed by 
 *	Harel's Statechart and UML. 
 *
 *	Run-to-completion may be implemented in various ways. The most common way 
 *	to do that is by an event-loop running in its own thread, and that reads 
 *	event occurrences from a pool.
 *	
 *	In case of active objects or SMA <EM>(State Machine Application)</EM>, 
 *	where each object has its own thread of execution, 
 *	it is very important to clearly distinguish the notion of 
 *	run-to-completion from the concept of thread pre-emption. Namely, 
 *	run-to-completion event handling is performed by a thread that, in 
 *	principle, can be pre-empted and its execution suspended in favor of 
 *	another thread executing on the same processing node. 
 *	(This is determined by the scheduling policy of the underlying thread 
 *	environment — no assumptions are made about this policy.). When the 
 *	suspended thread is assigned processor time again, it resumes its event 
 *	processing from the point of pre-emption and, eventually, completes its 
 *	event processing.
 *	
 *	<EM>
 *	An active object is an object that, as a direct consequence of its 
 *	creation, commences to execute its behavior, and does not cease until 
 *	either the complete behavior is executed or the object is 
 *	terminated by some external object. (This is sometimes referred to as 
 *	"the object having its own thread of control"). An active object 
 *	encapsulates a thread of control (event loop), a private event queue, 
 *	and a state machine. 
 *	So, Active object = thread of control + event queue + state machine.</EM>
 *	
 *	<b>Preemptive Kernel</b>
*	
*	In the most common and traditional implementations of the active object 
*	computing model, active objects map to threads of a traditional preemptive 
*	RTOS or OS. In this standard configuration the active object computing 
*	model can take full advantage of the underlying RTOS capabilities. In 
*	particular, if the kernel is preemptive, the active object system 
*	achieves exactly the same optimal task-level response as traditional 
*	tasks.
*	
*	In this approach, RTC semantics of state machine execution do not mean 
*	that a state machine has to monopolize the CPU for the duration of the 
*	RTC step. A preemptive kernel can perform a context switch in the middle 
*	of the long RTC step to allow a higher-priority active object to run. 
*	As long as the active objects don't share resources, they can run 
*	concurrently and complete their RTC steps independently.
*	
*	Example:
*
* 	\anchor fig15
* 	\image html rkhex.png "Figure 15 - A multi-automata application"
*
* 	WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW \n
* 	WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW \n
* 	WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW \n
*
* 	\anchor fig16
* 	\image html rkhpreem.png "Figure 16 - RTC execution model on a fixed priority preemptive scheduling"
*
*	\n Explanation:\n
*
*	\li (1)
*	\li (2)
*	\li (3)
*	\li (4)
*
*	<b>Simple cooperative kernel</b>
*	
*	The active object computing model can also work with nonpreemptive 
*	kernels. In fact, one particular cooperative kernel matches the active 
*	object computing model exceptionally well and can be implemented in 
*	an absolutely portable manner.
*	
*	The simple nonpreemptive native kernel executes one active object at a 
*	time in the infinite loop (similar to the "superloop"). 
*	The native kernel is engaged after each event is processed in the 
*	RTC fashion to choose the next highest-priority active 
*	object ready to process the next event. The native scheduler is 
*	cooperative, which means that all active objects cooperate to share a 
*	single CPU and implicitly yield to each other after every RTC step. 
*	The kernel is nonpreemptive, meaning that every active object must 
*	completely process an event before any other active object can start 
*	processing another event.
*	
*	The ISRs can preempt the execution of active objects at any time, but due 
*	to the simplistic nature of the native kernel, every ISR returns to 
*	exactly the preemption point. If the ISR posts an event to any active 
*	object, the processing of this event won't start until the current RTC 
*	step completes. The maximum time an event for the highest-priority active 
*	object can be delayed this way is called the task-level response. With 
*	the nonpreemptive native kernel, the task-level response is equal to the 
*	longest RTC step of all active objects in the system. Note that the 
*	task-level response of the native kernel is still a lot better than the 
*	traditional "superloop" (a.k.a. main+ISRs) architecture.
*	
*	The task-level response of the simple native kernel turns out to be 
*	adequate for surprisingly many applications because state machines by 
*	nature handle events quickly without a need to busy-wait for events. 
*	(A state machine simply runs to completion and becomes dormant until 
*	another event arrives.) Also note that often you can make the task-level 
*	response as fast as you need by breaking up longer RTC steps into shorter 
*	ones.
*	[MS]
*	
* 	\anchor fig17
* 	\image html rkhcoop.png "Figure 17 - RTC execution model on a fixed priority cooperative scheduling"
*
*	\n Explanation:\n
*
*	\li (1)
*	\li (2)
*	\li (3)
*	\li (4)
*
*	<B>Dealing with RTC model in a nonpreemtive manner</B>
*	
*	Here is the basic algorithm for interpreting the native kernel. 
*	The rkh_enter() function implemented in \b \\source\\rkhs.c source 
*	file is self-explanatory.
*	
*	\code
*	infinite loop
*	{
*		disable interrupts;
*		if( is_not_active_object_ready_to_run )
*		{
*			find the active object with highest priority;
*			enable interrupts;
*			e = get the event from the active object's queue;
*			dispatch the 'e' event to the active object's state machine;
*		}
*		else
*			execute the idle processing;
*	}
*	\endcode
*/


#ifndef __RKHS_H__
#define __RKHS_H__


#include "rkhcfg.h"
#include "rkh.h"
#include "rkhevt.h"


#if RKH_EN_NATIVE_SCHEDULER == 1 && RKH_EN_DOXYGEN == 0

	#define RKH_EQ_TYPE				RKHRQ_T

	#define RKH_SMA_BLOCK( sma ) 							\
					RKHASSERT( ((RKHSMA_T*)(sma))->equeue.qty != 0 )

	#define RKH_SMA_READY( rg, sma ) 						\
					rkh_rdy_ins( (rg), ((RKHSMA_T*)(sma))->romrkh->prio )

	#define RKH_SMA_UNREADY( rg, sma ) 						\
					rkh_rdy_rem( (rg), ((RKHSMA_T*)(sma))->romrkh->prio )

	extern RKHRG_T rkhrg;

#endif


#endif
