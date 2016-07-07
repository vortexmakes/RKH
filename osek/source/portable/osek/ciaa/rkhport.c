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
 *  \file       rkhport.c
 *  \ingroup    prt
 *
 *	\brief      CIAA Osek multithread port
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  DaBa  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Dario Baliña dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */

#include "rkh.h"
#include "ciaak.h"

RKH_MODULE_NAME(rkhport)
RKH_MODULE_VERSION(rkhport, 1.00)
RKH_MODULE_DESC(rkhport, "CIAA Osek multithread port")

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static void *pdata[TASKS_COUNT];

#if defined(RKH_USE_TRC_SENDER)
static rui8_t l_isr_tick;
#endif

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

const
char *
rkh_get_port_version(void)
{
    return RKH_MODULE_GET_VERSION();
}

const
char *
rkh_get_port_desc(void)
{
    return RKH_MODULE_GET_DESC();
}

void
rkh_fwk_init(void)
{
    unsigned int i;

    /* init CIAA kernel and devices */
    ciaak_start();

    SetRelAlarm(RKH_TickAlarm, RKH_TICK_RATE_MS, RKH_TICK_RATE_MS);

    /*Initialize to NULL the array containing the pointers to AOs.*/
    for (i = 0; i < TASKS_COUNT; i++)
    {
        pdata[i] = NULL;
    }
}

void
rkh_fwk_enter(void)
{
    /* start-up callback */
    RKH_HOOK_START();
    RKH_TR_FWK_EN();
    RKH_TR_FWK_OBJ(&l_isr_tick);

    /* Osek start the multitasking */
    StartOS(RkhApp);

    /* cleanup the trace session */
    RKH_TRC_CLOSE();
}

void
rkh_fwk_exit(void)
{
    RKH_TR_FWK_EX();

    /* clean-up callback */
    RKH_HOOK_EXIT();
}

void
rkh_sma_activate(RKH_SMA_T *sma, const RKH_EVT_T **qs, RKH_RQNE_T qsize,
                 void *stks, rui32_t stksize)
{
    const SMA_TASK_TBL_T *p;

    (void)stks;
    (void)stksize;
    RKH_SR_ALLOC();

    RKH_REQUIRE((qs != (const RKH_EVT_T **)0) && (stks == (void *)0));

    rkh_rq_init(&sma->equeue, (const void **)qs, qsize, sma);
    rkh_sma_register(sma);
    sma->os_signal = RKHEvent;

    rkh_sm_init((RKH_SM_T *)sma);

    for (p = rkh_sma_task_tbl; p->sma != NULL; ++p)
    {
        if (sma == *(RKH_SMA_T **)(p->sma))
        {
            sma->thread = p->tsk;
            sma->running = (rbool_t)1;
            ActivateTask(sma->thread);
        }
    }

    RKH_ASSERT(sma->running == (rbool_t)1);
    RKH_TR_SMA_ACT(sma, RKH_GET_PRIO(sma));
}

void
rkh_sma_terminate(RKH_SMA_T *sma)
{
    sma->running = (rbool_t)0;
}

ALARMCALLBACK(TickHandler)
{
    RKH_TIM_TICK(&l_isr_tick);
}

void
rkh_task_function(struct SMA **arg)
{
    RKH_SMA_T *sma = *(RKH_SMA_T **)arg;

    while (sma->running != (rbool_t)0)
    {
        RKH_EVT_T *e = rkh_sma_get(sma);
        rkh_sm_dispatch((RKH_SM_T *)sma, e);
        RKH_FWK_GC(e);
    }

    rkh_sma_unregister(sma);
    RKH_TR_SMA_TERM(sma, RKH_GET_PRIO(sma));
    TerminateTask();
}

/* ------------------------------ End of file ------------------------------ */

