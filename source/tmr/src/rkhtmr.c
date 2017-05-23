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
 *  \file       rkhtmr.c
 *  \ingroup    apiTmr
 *
 *  \brief      Implements the software timer.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhtmr.h"
#include "rkhassert.h"
#include "rkhfwk_hook.h"
#include "rkhsma.h"
#include "rkhtrc_record.h"
#include "rkhtrc_filter.h"

#if RKH_CFG_TMR_EN == RKH_ENABLED

RKH_MODULE_NAME(rkhtmr)

/* ----------------------------- Local macros ------------------------------ */
#define CPTIM(p)        ((RKH_TMR_T *)(p))

#if RKH_CFG_TMR_HOOK_EN == RKH_ENABLED
    #define RKH_EXEC_THOOK() \
    if (t->timhk != (RKH_THK_T)0) \
        (*t->timhk)(t)
    #define RKH_SET_THOOK(t, hk) \
    (t)->timhk = (hk)
#else
    #define RKH_EXEC_THOOK()          (void)0
    #define RKH_SET_THOOK(t, hk)      (void)0
#endif

#define add_to_list(t) \
    (t)->tnext = thead; \
    thead = (t); \
    (t)->used = 1

#if defined(RKH_USE_TRC_SENDER)
    #define RKH_TICK_POST(t_, sender_) \
    RKH_SMA_POST_FIFO((RKH_SMA_T *)t_->sma, t_->evt, \
                      sender_ != (const void *)0 ? sender_ : t_)
#else
    #define RKH_TICK_POST(t_, sender_) \
    RKH_SMA_POST_FIFO((RKH_SMA_T *)t_->sma, t_->evt, sender_)
#endif

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_TMR_T * thead;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
rem_from_list(RKH_TMR_T *t, RKH_TMR_T *tprev)
{
    if (thead == t)             /* is first timer in the list? */
    {
        thead = t->tnext;
    }
    else
    {
        tprev->tnext = t->tnext;
    }
    t->used = 0;
    RKH_TR_TMR_REM(t);
}

/* ---------------------------- Global functions --------------------------- */
void
#if defined(RKH_USE_TRC_SENDER)
rkh_tmr_tick(const void *const sender)
#else
rkh_tmr_tick(void)
#endif
{
    RKH_TMR_T *t, *tprev;
    RKH_SR_ALLOC();

    RKH_HOOK_TIMETICK();            /* call user definable hook */

    RKH_ENTER_CRITICAL_();
    if (thead == CPTIM(0))      /* is empty list? */
    {
        RKH_EXIT_CRITICAL_();
        return;
    }

    for (tprev = CPTIM(0), t = thead; t != CPTIM(0); t = t->tnext)
        if (t->ntick == 0)
        {
            rem_from_list(t, tprev);
        }
        else
        {
            if (!--t->ntick)
            {
                RKH_TR_TMR_TOUT(t, t->evt->e, t->sma);
                if (t->period == 0)
                {
                    rem_from_list(t, tprev);
                }
                else
                {
                    t->ntick = t->period;
                    tprev = t;
                }
                RKH_HOOK_TIMEOUT(t);
                RKH_EXEC_THOOK();
                RKH_TICK_POST(t, sender);
            }
            else
            {
                tprev = t;
            }
        }
    RKH_EXIT_CRITICAL_();
}

void
#if RKH_CFG_TMR_HOOK_EN == RKH_DISABLED
rkh_tmr_init_(RKH_TMR_T *t, const RKH_EVT_T *e)
#else
rkh_tmr_init_(RKH_TMR_T * t, const RKH_EVT_T * e, RKH_THK_T thk)
#endif
{
    RKH_SR_ALLOC();
    RKH_REQUIRE(t != CPTIM(0) && e != CCE(0));

    RKH_ENTER_CRITICAL_();
    t->ntick = 0;
    t->used = 0;
    t->evt = CE(e);
    RKH_TR_TMR_INIT(t, t->evt->e);
    RKH_EXIT_CRITICAL_();

    RKH_SET_THOOK(t, thk);
}

void
rkh_tmr_start(RKH_TMR_T *t, const struct RKH_SMA_T *sma, RKH_TNT_T itick)
{
    RKH_SR_ALLOC();

    RKH_REQUIRE(t != CPTIM(
                    0) && sma != (const struct RKH_SMA_T *)0 && itick != 0);
    RKH_ENTER_CRITICAL_();

    t->sma = sma;
    t->ntick = itick;
    if (t->used == 0)
    {
        add_to_list(t);
    }

    RKH_TR_TMR_START(t, sma, itick, t->period);
    RKH_EXIT_CRITICAL_();
}

void
rkh_tmr_stop(RKH_TMR_T *t)
{
    RKH_SR_ALLOC();

    RKH_REQUIRE(t != CPTIM(0));

    RKH_ENTER_CRITICAL_();
    t->ntick = 0;
    RKH_TR_TMR_STOP(t, t->ntick, t->period);
    RKH_EXIT_CRITICAL_();

}

#if RKH_CFG_TMR_GET_INFO_EN == RKH_ENABLED
void
rkh_tmr_get_info(RKH_TMR_T *t, RKH_TINFO_T *info)
{
    RKH_SR_ALLOC();

    RKH_ENTER_CRITICAL_();
    *info = t->info;
    RKH_EXIT_CRITICAL_();
}

void
rkh_tmr_clear_info(RKH_TMR_T *t)
{
    RKH_TINFO_T *pi;
    RKH_SR_ALLOC();

    pi = &t->info;

    RKH_ENTER_CRITICAL_();
    pi->nexp = pi->nstart = pi->nstop = 0;
    RKH_EXIT_CRITICAL_();
}
#endif

#endif
/* ------------------------------ End of file ------------------------------ */
