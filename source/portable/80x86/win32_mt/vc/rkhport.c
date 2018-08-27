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
 *  \brief      Visual Studio Multi-Thread port (win32)
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
#include <stdio.h>

#include "rkh.h"
#include "rkhfwk_dynevt.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
RKH_MODULE_NAME(rkhport)
RKH_MODULE_VERSION(rkhport, 1.00)
RKH_MODULE_DESC(rkhport, "Windows 32-bits (multi thread)")

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static CRITICAL_SECTION csection;
static DWORD tick_msec = 10u;
static rui8_t running;
static HANDLE idle_thread;
#if defined(RKH_USE_TRC_SENDER)
static rui8_t l_isr_tick;
#endif
static DWORD WINAPI thread_function(LPVOID arg);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
DWORD WINAPI
idle_thread_function(LPVOID par)
{
    (void)par;

    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_IDLE);

    while (running)
    {
        RKH_TRC_FLUSH();
        rkhport_wait_for_events();                /* yield the CPU until new */
                                                          /* event(s) arrive */
        Sleep(10);
    }
    return 0;
}

static
DWORD
WINAPI
thread_function(LPVOID arg)
{
    RKH_SR_ALLOC();

    do
    {
        RKH_EVT_T *e = rkh_sma_get((RKH_SMA_T *)arg);
        rkh_sm_dispatch((RKH_SM_T *)arg, e);
        RKH_FWK_GC(e, arg);
    }
    while (((RKH_SMA_T *)arg)->thread != (HANDLE)0);

    rkh_sma_unregister((RKH_SMA_T *)arg);
    RKH_TR_SMA_TERM((RKH_SMA_T *)arg,
                    RKH_GET_PRIO((RKH_SMA_T *)arg));
    CloseHandle(((RKH_SMA_T *)arg)->os_signal);
    return 0;
}

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
}

void
rkh_sma_block(RKH_SMA_T *const me)
{
    while (me->equeue.qty == 0)
    {
        rkhport_exit_critical();
        (void)WaitForSingleObject(me->os_signal, (DWORD)INFINITE);
        rkhport_enter_critical();
    }
}

void
rkh_sma_setReady(RKH_SMA_T *const me)
{
    (void)SetEvent(me->os_signal);
}

void
rkh_sma_setUnready(RKH_SMA_T *const me)
{
    (void)me;
}

void
rkh_fwk_init(void)
{
    InitializeCriticalSection(&csection);
}

void
rkh_fwk_enter(void)
{
    tick_msec = 1000UL / RKH_CFG_FWK_TICK_RATE_HZ;
    running = (rui8_t)1;

    /*
     *  For avoiding to have multiple threads (idle and main) sending data on
     *  the same socket, i.e. using the send() function, the idle thread is
     *  created to be run only after the initial process has finished.
     *  Without this trick, the streams are interleaving and the trace stream
     *  is corrupted.
     */
    if ((idle_thread =
             CreateThread(NULL, 1024, &idle_thread_function, (void *)0,
                          CREATE_SUSPENDED, NULL)) == (HANDLE)0)
    {
        fprintf(stderr, "Cannot create the idle thread: [%d] line from %s "
                "file\n", __LINE__, __FILE__);
    }

    ResumeThread(idle_thread);

    RKH_HOOK_START();                       /* start-up callback */
    RKH_TR_FWK_EN();

    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
    RKH_TR_FWK_OBJ(&l_isr_tick);

    while (running)
    {
        Sleep(tick_msec);               /* wait for the tick interval */
        RKH_TIM_TICK(&l_isr_tick);      /* tick handler */
    }
    RKH_HOOK_EXIT();                    /* cleanup callback */
    RKH_TRC_CLOSE();                    /* cleanup the trace session */
    DeleteCriticalSection(&csection);
}

void
rkh_fwk_exit(void)
{
    RKH_TR_FWK_EX();
    RKH_HOOK_EXIT();
    running = (rui8_t)0;
}

void
rkh_sma_activate(RKH_SMA_T *sma, const RKH_EVT_T **qs, RKH_QUENE_T qsize,
                 void *stks, rui32_t stksize)
{
    int priority;

    (void)stks;
    (void)stksize;
    RKH_SR_ALLOC();

    RKH_REQUIRE((qs != (const RKH_EVT_T **)0) && (stks == (void *)0));

    rkh_queue_init(&sma->equeue, (const void **)qs, qsize, sma);
    rkh_sma_register(sma);
    sma->os_signal = CreateEvent(NULL, FALSE, FALSE, NULL);
    rkh_sm_init((RKH_SM_T *)sma);
    sma->thread = CreateThread(NULL, stksize, thread_function, sma, 0, NULL);
    RKH_ASSERT(sma->thread != (HANDLE)0);

    /* map RKH priority to win32 priority */
    switch (RKH_GET_PRIO(sma))
    {
        case 0:
            priority = THREAD_PRIORITY_HIGHEST;
            break;
        case 1:
            priority = THREAD_PRIORITY_ABOVE_NORMAL;
            break;
        case RKH_LOWEST_PRIO:
            priority = THREAD_PRIORITY_IDLE;
            break;
        case RKH_LOWEST_PRIO - 1:
            priority = THREAD_PRIORITY_LOWEST;
            break;
        case RKH_LOWEST_PRIO - 2:
            priority = THREAD_PRIORITY_BELOW_NORMAL;
            break;
        default:
            priority = THREAD_PRIORITY_NORMAL;
            break;
    }

    SetThreadPriority(sma->thread, priority);
    RKH_TR_SMA_ACT(sma, RKH_GET_PRIO(sma), qsize);
}

void
rkh_sma_terminate(RKH_SMA_T *sma)
{
    sma->thread = (HANDLE)0;
}

/* ------------------------------ End of file ------------------------------ */
