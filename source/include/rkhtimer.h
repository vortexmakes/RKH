/*
 *	file: rkhtimer.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 24, 2012
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
 * 	rkhtimer.h
 *
 * 	\brief
 * 	Platform-independent interface for supporting timer services.
 */


#ifndef __RKHTIMER_H__
#define __RKHTIMER_H__


#include "rkh.h"


/** 
 * 	\brief
 * 	This data type defines the dynamic range of the time delays measured in 
 * 	clock ticks (maximum number of ticks).
 *
 *	The valid values [in bits] are 8, 16 or 32. Default is 8. This type is 
 *	configurable via the preprocessor switch RKH_SIZEOF_TNT.
 */

#if RKH_SIZEOF_TNT == 8
	typedef rkhui8_t RKH_TCTR_T;
#elif RKH_SIZEOF_TNT == 16
	typedef rkhui16_t RKH_TCTR_T;
#elif RKH_SIZEOF_TNT == 32
	typedef rkhui32_t RKH_TCTR_T;
#else
	typedef rkhui8_t RKH_TCTR_T;
#endif


/**
 * 	\brief
 * 	Defines the data structure into which the performance information for
 * 	software timers is stored.
 *
 *	The application must allocate an RKH_TIMERI_T data structure used to 
 *	receive information. The performance information is available during 
 *	run-time for each of the RKH services. This can be useful in determining 
 *	whether the application is performing properly, as well as helping to 
 *	optimize the application.
 */

typedef struct rkh_timer_info_t
{
	rkhui16_t nexp;			/** # of expirations */
	rkhui16_t nstart;		/**	# of start requests */
	rkhui16_t nstop;		/**	# of stop requests */
} RKH_TIMERI_T;


/**
 * 	\brief
 * 	Defines the data structure used to maintain information that allows the 
 * 	timer-handling facility to update and expire software timers. 
 */

typedef struct
{
	/**
	 * 	Timer event.
	 */

	RKHEVT_T e;

	/**
	 * 	Points to next timer structure in the doubly linked list.
	 */

	RKHT_T *tnext;

	/**
	 * 	Points to previous timer structure in the doubly linked list.
	 */

	RKHT_T *tprev;

	/**
	 * 	State machine application (SMA) that receives the timer event.
	 */

	RKHSMA_T *sma;

	/**
	 * 	Tick down-counter.
	 */

	RKH_TCTR_T tick;

	/**
	 * 	Number of ticks for all timer expirations after the first (expiration 
	 * 	period). A zero for this parameter makes the timer a one-shot timer, 
	 * 	otherwise, for periodic timers, any value in range.
	 */

	RKH_TCTR_T period;

	/**
	 *	Hook function to call when the timer expires. This member is optional, 
	 *	thus it could be declared as NULL or eliminated in compile-time with 
	 *	RKH_EN_TIMER_HOOK.
	 */

#if RKH_EN_TIMER_HOOK == 1
	RKH_THK_T timhk;
#endif

	/**
	 * 	Performance information. This member is optional, thus it could be 
	 * 	declared as NULL or eliminated in compile-time with 
	 * 	RKSYS_TIMER_GET_INFO.
	 */

#if RKSYS_TIMER_GET_INFO == 1
	RKH_TIMERI_T tinfo;
#endif
} RKHT_T;


/**
 * 	\brief
 * 	Keep tracks and updates the started timers. 
 * 	If one or more timers expires the assigned event is directly posted into 
 * 	the state machine application queue and associated hook function is 
 * 	executed (if it's used). The expiration events of timers that expire at 
 * 	the same time are executed in the order they were started.
 * 	This function must be placed where will be incrementing the system tick. 
 * 	Normally this is placed in a timer ISR routine.
 */

void rkh_timer_handler( void );


/**
 * 	\brief
 *	Initializes the previously allocated timer structure RKHT_T. 
 *	The timer is initialized in a non-active state (stopped). In this case, a 
 *	subsequent start service call is necessary to get the timer actually 
 *	started.
 *
 *	\note 
 *	See RKHT_T structure for more information.
 *		
 *	\param t		pointer to previously allocated timer structure. Any 
 *					software module intending to install a software timer must 
 *					first allocate a timer structure RKHT_T.
 *	\param thk 		hook function to be called at the timer expiration. This 
 *					member is optional, thus it could be declared as NULL or 
 *					eliminated in compile-time with RKH_EN_TIMER_HOOK.
 *	\param sig		signal of the event to be directly posted (using the FIFO 
 *					policy) into the event queue of the target agreed state 
 *					machine application.
 */

#define rkh_timer_init( t, sig, thk )		rkh_mktimer( t, sig, thk )

#if RKH_EN_TIMER_HOOK == 0
	void rkh_itim_init( RKHT_T *t, RKHE_T sig );
#else
	void rkh_itim_init( RKHT_T *t, RKHE_T sig, RKH_THK_T thk );
#endif


/**
 * 	\brief
 * 	Start a timer as one-shot timer.
 * 	This operation installs a previously created timer into	the timer-handling 
 * 	facility. The timer begins running at the completion of this operation. 
 * 	The timer won't be re-started automatically.
 *
 *	\param t		pointer to previously created timer structure.
 *	\param sma		state machine application (SMA) that receives the timer 
 *					event.
 * 	\param tick 	number of ticks for timer expiration.
 */

#define rkh_timer_oneshot( t, sma, tick )						\
				do{												\
					(t)->period = 0;							\
					rkh_timer_start( (t), (sma), (itick) );
				}while(0)


/**
 * 	\brief
 * 	Start a timer as periodic timer.
 * 	This operation installs a previously created timer into	the timer-handling 
 * 	facility. The timer begins running at the completion of this operation.
 * 	Once the timeout will expire the timer will be re-started (re-triggered) 
 * 	again automatically.
 *
 *	\param t		pointer to previously created timer structure.
 *	\param sma		state machine application (SMA) that receives the timer 
 *					event.
 * 	\param itick 	number initial of ticks for timer expiration.
 * 	\param period 	number of ticks for all timer expirations after the first 
 * 					(expiration period). A zero for this parameter makes the 
 * 					timer a one-shot timer, otherwise, for periodic timers, 
 * 					any value in range.
 */

#define rkh_timer_periodic( t, sma, itick, period )				\
				do{												\
					(t)->period = (period);						\
					rkh_timer_start( (t), (sma), (itick) );		\
				}while(0)


/**
 * 	\brief
 * 	Start a timer. 
 * 	This operation installs a previously created timer into	the timer-handling 
 * 	facility. The timer begins running at the completion of this operation.
 *
 *	\param t		pointer to previously created timer structure.
 * 	\param itick 	number of ticks for timer expiration.
 */

void rkh_timer_start( RKHT_T *t, RKHSMA_T *sma, RKH_TCTR_T itick );


/**
 * 	\brief
 * 	Restart a timer with a new number of ticks. 
 * 	The timer begins running at the completion of this operation.
 * 	This function is optional, thus it could be eliminated in compile-time 
 * 	with RKH_EN_TIMER_RESTART.
 *
 *	\param t		pointer to previously created timer structure.
 * 	\param itick 	number of initial ticks for timer expiration.
 */

void rkh_timer_restart( RKHT_T *t, RKH_TCTR_T itick );


/**
 * 	\brief
 *	Stops a running timer. 
 *	This operation stops a timer by removing the currently running timer from 
 *	the timer-handling facility. If the timer is already stopped, this service 
 *	has no effect.
 *
 *	\param t		pointer to previously created timer structure.
 */

void rkh_timer_stop( RKHT_T *t );


/**
 * 	\brief
 * 	Retrieves performance information for a particular queue. 
 *
 *	The user application must allocate an RKH_TIMERI_T data structure used 
 *	to receive data. The performance information is available during run-time 
 *	for each of the RKH services. This can be useful in determining whether 
 *	the application is performing properly, as well as helping to optimize the 
 *	application.
 *	This information provides a "snapshot" a particular instant in time, i.e., 
 *	when the service is invoked.
 *
 * 	\note
 * 	See RKH_TIMERI_T structure for more information. This function is 
 * 	optional, thus it could be eliminated in compile-time with 
 * 	RKSYS_TIMER_GET_INFO.
 *
 *	\param t		pointer to previously created timer structure.
 * 	\param pti		pointer to the buffer into which the performance 
 * 					information will be copied by reference.
 */

void rkh_timer_get_info( RKHT_T *t, RKH_TIMERI_T *pti );


/**
 * 	\brief
 * 	Clear performance information for a particular software timer.
 *
 * 	\note
 * 	See RKH_TIMERI_T structure for more information. This function is 
 * 	optional, thus it could be eliminated in compile-time with 
 * 	RKSYS_TIMER_GET_INFO.
 *
 *	\param t		pointer to previously created timer structure.
 */

void rkh_timer_clear_info( RKHT_T *t );


#endif
