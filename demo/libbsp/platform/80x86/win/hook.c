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
 *  \file       hook.c
 *  \brief      RKH hooks functions for 80x86 OS win32
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.14  DaBa  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */
/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include <conio.h>

#include "rkh.h"
#include "bsp_common.h"

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static DWORD tickMsec;

/* ----------------------- Local function prototypes ----------------------- */
static DWORD WINAPI isr_tmr_thread(LPVOID par);
static DWORD WINAPI isr_kbd_thread(LPVOID par);

/* ---------------------------- Local functions ---------------------------- */
static
DWORD WINAPI
isr_tmrThread(LPVOID par)      /* Win32 thread to emulate timer ISR */
{
    (void)par;
    while (rkhport_fwk_is_running())
    {
        RKH_TIM_TICK(0);
        Sleep(tickMsec);
    }
    return 0;
}

static
DWORD WINAPI
isr_kbdThread(LPVOID par)      /* Win32 thread to emulate keyboard ISR */
{
    (void)par;

    while (rkhport_fwk_is_running())
    {
        bsp_keyParser(_getch());
    }
    return 0;
}

/* ---------------------------- Global functions --------------------------- */
void
rkh_hook_start(void)
{
    DWORD thtmrId, thkbdId;
    HANDLE hthTmr, hthKbd;

    /* set the desired tick rate */
    tickMsec = RKH_TICK_RATE_MS;

    /* create the ISR timer thread */
    hthTmr = CreateThread(NULL, 1024, &isr_tmrThread, 0, 0, &thtmrId);
    RKH_ASSERT(hthTmr != (HANDLE)0);
    SetThreadPriority(hthTmr, THREAD_PRIORITY_TIME_CRITICAL);

    /* create the ISR keyboard thread */
    hthKbd = CreateThread(NULL, 1024, &isr_kbdThread, 0, 0, &thkbdId);
    RKH_ASSERT(hthKbd != (HANDLE)0);
    SetThreadPriority(hthKbd, THREAD_PRIORITY_NORMAL);
}

void
rkh_hook_exit(void)
{
    RKH_TRC_FLUSH();
}

void
rkh_hook_timetick(void)
{
    bsp_timeTick();
}

void
rkh_hook_idle(void)             /* called within critical section */
{
    RKH_EXIT_CRITICAL(dummy);
    RKH_TRC_FLUSH();
    rkhport_wait_for_events();  /* yield the CPU until new event(s) arrive */
}

/* ------------------------------ File footer ------------------------------ */
