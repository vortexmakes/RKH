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
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       rkhport.c
 *  \brief      Visual Studio Single-Thread port (win32)
 *
 *  \ingroup    port
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "rkhfwk_dynevt.h"

/* ----------------------------- Local macros ------------------------------ */
/* (1) Function macro defines */

/* ------------------------------- Constants ------------------------------- */
RKH_MODULE_NAME(rkhport)
RKH_MODULE_VERSION(rkhport, 1.00)
RKH_MODULE_DESC(rkhport, "Windows 32-bits (single thread)")

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static CRITICAL_SECTION csection;
static HANDLE sma_is_rdy;
static rui8_t running;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
const
char *
rkhport_get_version(void)
{
    return RKH_MODULE_GET_VERSION();
}

const
char *
rkhport_get_desc(void)
{
    return RKH_MODULE_GET_DESC();
}

rui8_t
rkhport_fwk_is_running(void)
{
    return running;
}

void
rkhport_fwk_stop(void)
{
    running = 0;
}

void
rkhport_enter_critical(void)
{
    EnterCriticalSection(&csection);
}

void
rkhport_exit_critical(void)
{
    LeaveCriticalSection(&csection);
}

void
rkhport_wait_for_events(void)
{
    ((void)WaitForSingleObject(sma_is_rdy, (DWORD)INFINITE));
}

void
rkh_sma_block(RKH_SMA_T *const me)
{
    RKH_ASSERT(me->equeue.qty != 0);
}

void
rkh_sma_setReady(RKH_SMA_T *const me)
{
    rkh_smaPrio_setReady(RKH_SMA_ACCESS_CONST(me, prio));
    SetEvent(sma_is_rdy);
}

void
rkh_sma_setUnready(RKH_SMA_T *const me)
{
    rkh_smaPrio_setUnready(RKH_SMA_ACCESS_CONST(me, prio));
}

void
rkh_fwk_init(void)
{
    InitializeCriticalSection(&csection);
    sma_is_rdy = CreateEvent(NULL, FALSE, FALSE, NULL);
}

void
rkh_fwk_enter(void)
{
    rui8_t prio;
    RKH_SMA_T *sma;
    RKH_EVT_T *e;
    RKH_SR_ALLOC();

    RKH_HOOK_START();
    RKH_TR_FWK_EN();
    running = 1;

    while (running)
    {
        RKH_ENTER_CRITICAL(dummy);
        if (rkh_smaPrio_isReady())
        {
            prio = rkh_smaPrio_findHighest();
            RKH_EXIT_CRITICAL(dummy);

            sma = rkh_sptbl[prio];
            e = rkh_sma_get(sma);
            rkh_sm_dispatch((RKH_SM_T *)sma, e);
            RKH_FWK_GC(e, sma);
        }
        else
        {
            rkh_hook_idle();
        }
    }

    RKH_HOOK_EXIT();
    CloseHandle(sma_is_rdy);
    DeleteCriticalSection(&csection);
}

void
rkh_fwk_exit(void)
{
    RKH_HOOK_EXIT();
    RKH_TR_FWK_EX();
    running = 0;
}

void
rkh_sma_activate(RKH_SMA_T *sma, const RKH_EVT_T **qs, RKH_QUENE_T qsize,
                 void *stks, rui32_t stksize)
{
    (void)stks;
    (void)stksize;
    RKH_SR_ALLOC();

    rkh_queue_init(&sma->equeue, (const void **)qs, qsize, sma);
    rkh_sma_register(sma);
    rkh_sm_init((RKH_SM_T *)sma);
    RKH_TR_SMA_ACT(sma, RKH_GET_PRIO(sma), qsize);
}

void
rkh_sma_terminate(RKH_SMA_T *sma)
{
    RKH_SR_ALLOC();

    rkh_sma_unregister(sma);
    RKH_TR_SMA_TERM(sma, RKH_GET_PRIO(sma));
}

/* ------------------------------ File footer ------------------------------ */

