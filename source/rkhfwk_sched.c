/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       rkhfwk_sched.c
 *  \brief      Implements a native, simple and cooperative scheduler called 
 *              RKS to deal with multiple event - driven state machines.
 *  \ingroup    fwk
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.17.05 LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhfwk_module.h"
#include "rkhitl.h"
#include "rkhfwk_sched.h"
#include "rkhsma_prio.h"
#include "rkhtrc_record.h"
#include "rkhtrc_filter.h"
#include "rkhsma.h"
#include "rkhfwk_dynevt.h"
#include "rkhfwk_hook.h"
#include "rkhsm.h"

#if (RKH_CFGPORT_NATIVE_SCHEDULER_EN == RKH_ENABLED)

RKH_MODULE_NAME(rkhfwk_sched)

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
void 
rkh_fwk_init(void)
{
}

/**
 *  \brief
 *  This function executes one state machine application or active object 
 *  at a time in the infinite loop (similar to the "superloop").
 *
 *  \details
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
rkh_fwk_enter(void)
{
    rui8_t prio;
    RKH_SMA_T *sma;
    RKH_EVT_T *e;
    RKH_SR_ALLOC();

    RKH_HOOK_START();
    RKH_TR_FWK_EN();

    FOREVER
    {
        RKH_DIS_INTERRUPT();
        if (rkh_smaPrio_isReady())
        {
            prio = rkh_smaPrio_findHighest();
            sma = rkh_sptbl[prio];
            RKH_ENA_INTERRUPT();

            e = rkh_sma_get(sma);
            (void)rkh_sm_dispatch((RKH_SM_T *)sma, e);
            RKH_FWK_GC(e, sma);
        }
        else
        {
            /*
             * rkh_hook_idle() must be called with interrupts DISABLED because
             * the determination of the idle condition (no events in the queues)
             * can change at any time by an interrupt posting events to a queue.
             * The rkh_hook_idle() MUST enable interrups internally, perhaps at
             * the same time as putting the CPU into a power-saving mode.
             */
            rkh_hook_idle();
        }
    }
}

void 
rkh_fwk_exit(void)
{
    RKH_TR_FWK_EX();
}

#endif

/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
