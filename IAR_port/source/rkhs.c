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
 *  File                     : rkhs.c
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	sch
 *
 *	\brief 		Implements a native, simple and cooperative scheduler called 
 *				RKS to deal with multiple event-driven state machines.
 */


#include "rkhassert.h"
#include "rkh.h"


#if RKH_EN_NATIVE_SCHEDULER == RKH_ENABLED


RKH_MODULE_NAME( rkhs )
RKHRG_T rkhrg;				/* ready group of SMAs */


void 
rkh_init( void )
{
}


/**
 * 	\details
 *	The RKS executes one state machine application or active object at a time 
 *	in the infinite loop (similar to the "superloop"). The RKS is engaged 
 *	after each event is processed in the run-to-completion (RTC) fashion to 
 *	choose the next highest-priority active object ready to process the next 
 *	event. The RKS scheduler is cooperative, which means that all active 
 *	objects cooperate to share a single CPU and implicitly yield to each other 
 *	after every RTC step. The kernel is nonpreemptive, meaning that every 
 *	active object must completely process an event before any other active 
 *	object can start processing another event. The ISRs can preempt the 
 *	execution of active objects at any time, but due to the simplistic nature 
 *	of the RKS, every ISR returns to exactly the preemption point. If the ISR 
 *	posts an event to any active object, the processing of this event won't 
 *	start until the current RTC step completes. The maximum time an event for 
 *	the highest-priority active object can be delayed this way is called the 
 *	task-level response. With the nonpreemptive RKS, the task-level response 
 *	is equal to the longest RTC step of all active objects in the system.
 */

void 
rkh_enter( void )
{
	rkhui8_t prio;
	RKHSMA_T *sma;
	RKHEVT_T *e;
	RKH_SR_ALLOC();

	RKH_HK_START();
	RKH_TR_FWK_EN();

    FOREVER
	{
		RKH_DIS_INTERRUPT();
        if( rkh_rdy_isnot_empty( rkhrg ) )
		{
			rkh_rdy_findh( rkhrg, prio );
            sma = rkh_sptbl[ prio ];
			RKH_ENA_INTERRUPT();

            e = rkh_sma_get( sma );
			rkh_dispatch( sma, e );
            RKH_GC( e );
        }
        else 
		/*
		 * rkh_hk_idle() must be called with interrupts DISABLED because the 
		 * determination of the idle condition (no events in the queues) can 
		 * change at any time by an interrupt posting events to a queue. The 
		 * rkh_hk_idle() MUST enable interrups internally, perhaps at the 
		 * same time as putting the CPU into a power-saving mode.
		 */			
            rkh_hk_idle();
    }
}


void 
rkh_exit( void )
{
	RKH_TR_FWK_EX();
}


void 
rkh_sma_activate(	RKHSMA_T *sma, const RKHEVT_T **qs, RKH_RQNE_T qsize, 
						void *stks, rkhui32_t stksize )
{
    ( void )stks;
    ( void )stksize;
	RKH_SR_ALLOC();

	RKHREQUIRE( (qs != (const RKHEVT_T **)0) && (qsize != (RKH_RQNE_T *)0) );

	rkh_rq_init( &sma->equeue, (const void** )qs, qsize, sma );
	rkh_sma_register( sma );
    rkh_init_hsm( sma );
	RKH_TR_SMA_ACT( sma, RKH_GET_PRIO(sma) );
}


void 
rkh_sma_terminate( RKHSMA_T *sma )
{
	RKH_SR_ALLOC();

	rkh_sma_unregister( sma );
	RKH_TR_SMA_TERM( sma, RKH_GET_PRIO(sma) );
}

#endif