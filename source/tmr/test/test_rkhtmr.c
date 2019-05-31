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
 *  \file       test_rkhtmr.c
 *  \ingroup    test_tmr
 *  \brief      Unit test for software timer module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_tmr Timer
 *  @{
 *  \brief      Unit test for software timer module.
 */

/* -------------------------- Development history -------------------------- */
/*
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity.h"
#include "rkhtmr.h"
#include "Mock_rkhtrc_record.h"
#include "Mock_rkhtrc_filter.h"
#include "Mock_rkhport.h"
#include "Mock_rkhassert.h"
#include "Mock_rkhsma.h"
#include "Mock_rkhfwk_hook.h"
#include "Mock_rkhfwk_dynevt.h"
#include "Mock_rkhfwk_cast.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define evSync      10

/* ---------------------------- Local data types --------------------------- */
static RKHTmEvt myTmEvt;

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_TMR_T tmr0, tmr1, tmr2;
static RKH_SMA_T ao;
static RKH_EVT_T evt;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
createMultipleTimers(RKH_TNT_T nTick0, RKH_TNT_T nTick1, RKH_TNT_T nTick2)
{
    rkh_enter_critical_Ignore();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_hook_timetick_Ignore();
    rkh_exit_critical_Ignore();

    rkh_tmr_init();
    RKH_TMR_INIT(&tmr0, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr0, &ao, nTick0);
    RKH_TMR_INIT(&tmr1, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr1, &ao, nTick1);
    RKH_TMR_INIT(&tmr2, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr2, &ao, nTick2);
}

/* ---------------------------- Global functions --------------------------- */
void 
setUp(void)
{
}

void 
tearDown(void)
{
}

void
test_InitializeATimeEvent(void)
{
    rkh_enter_critical_Ignore();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_exit_critical_Ignore();

    RKH_SET_STATIC_EVENT(&myTmEvt, evSync);
    RKH_TMR_INIT(&myTmEvt.tmr, 
                 RKH_UPCAST(RKH_EVT_T, &myTmEvt), 
                 NULL);

    TEST_ASSERT_EQUAL(evSync, myTmEvt.evt.e);
    TEST_ASSERT_EQUAL(&myTmEvt.evt, myTmEvt.tmr.evt);
}

void
test_InitializeATimer(void)
{
    RKH_TMR_T tmr;

    rkh_enter_critical_Ignore();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_exit_critical_Ignore();

    RKH_TMR_INIT(&tmr, RKH_UPCAST(RKH_EVT_T, &evt), NULL);

    TEST_ASSERT_EQUAL(&evt, tmr.evt);
    TEST_ASSERT_EQUAL(0, tmr.ntick);
    TEST_ASSERT_EQUAL(0, tmr.used);
}

void
test_StartTheFirstTimerInTheList(void)
{
    RKH_TMR_T tmr;
    RKH_TNT_T nTicks;

    rkh_enter_critical_Ignore();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_exit_critical_Ignore();
    nTicks = 4;

    rkh_tmr_init();
    RKH_TMR_INIT(&tmr, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr, &ao, nTicks);

    TEST_ASSERT_EQUAL(1, tmr.used);
    TEST_ASSERT_EQUAL(nTicks, tmr.ntick);
    TEST_ASSERT_EQUAL(&ao, tmr.sma);
    TEST_ASSERT_EQUAL(0, tmr.tnext);    /* the first timer in the list */
}

void
test_StartTheSameTimerManyTimes(void)
{
    RKH_TMR_T tmr;

    rkh_enter_critical_Ignore();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_exit_critical_Ignore();

    rkh_tmr_init();
    RKH_TMR_INIT(&tmr, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr, &ao, 1);
    rkh_tmr_start(&tmr, &ao, 2);
    rkh_tmr_start(&tmr, &ao, 4);
    rkh_tmr_start(&tmr, &ao + 1, 8);

    TEST_ASSERT_EQUAL(1, tmr.used);
    TEST_ASSERT_EQUAL(8, tmr.ntick);
    TEST_ASSERT_EQUAL(&ao + 1, tmr.sma);
    TEST_ASSERT_EQUAL(0, tmr.tnext);    /* the first timer in the list */
}

void
test_StartManyTimers(void)
{
    createMultipleTimers(8, 4, 2);
    TEST_ASSERT_EQUAL(&tmr1, tmr2.tnext);
    TEST_ASSERT_EQUAL(&tmr0, tmr1.tnext);
    TEST_ASSERT_EQUAL(0, tmr0.tnext);
}

void
test_StopTheOnlyOneTimer(void)
{
    RKH_TMR_T tmr;

    rkh_enter_critical_Ignore();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_exit_critical_Ignore();

    rkh_tmr_init();
    RKH_TMR_INIT(&tmr, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr, &ao, 1);
    rkh_tmr_stop(&tmr);

    TEST_ASSERT_EQUAL(0, tmr.ntick);
}

void
test_StopAndImmediatelyStartTheSameTimer(void)
{
#if 0
    RKH_TNT_T nTick = 4;

    createMultipleTimers(8, 6, nTick);
    rkh_sma_post_fifo_Expect((RKH_SMA_T *)tmr2.sma, tmr2.evt, &tmr2);

    rkh_tmr_tick(0);
    rkh_tmr_stop(&tmr2);
    RKH_TMR_INIT(&tmr2, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr2, &ao, nTick);
    rkh_tmr_tick(0);
    rkh_tmr_tick(0);

    TEST_ASSERT_EQUAL(5, tmr0.ntick);
    TEST_ASSERT_EQUAL(3, tmr1.ntick);
    TEST_ASSERT_EQUAL(2, tmr2.ntick);
    TEST_ASSERT_EQUAL(1, tmr2.used);
    TEST_ASSERT_EQUAL(&tmr1, tmr2.tnext);
    TEST_ASSERT_EQUAL(&tmr0, tmr1.tnext);
#else
    TEST_ASSERT_IGNORE_MESSAGE("To be implemented");
#endif
}

void
test_StopATimerAtTheBeginningOfTheList(void)
{
    createMultipleTimers(8, 4, 2);

    rkh_tmr_stop(&tmr2);
    rkh_tmr_tick(0);

    TEST_ASSERT_EQUAL(0, tmr2.ntick);
    TEST_ASSERT_EQUAL(0, tmr2.used);
}

void
test_StopATimerAtTheMiddleOfTheList(void)
{
    createMultipleTimers(8, 4, 2);

    rkh_tmr_stop(&tmr1);
    rkh_tmr_tick(0);

    TEST_ASSERT_EQUAL(0, tmr1.ntick);
    TEST_ASSERT_EQUAL(0, tmr1.used);
    TEST_ASSERT_EQUAL(tmr1.tnext, tmr2.tnext);
}

void
test_StopATimerAtTheEndOfTheList(void)
{
    createMultipleTimers(8, 4, 2);

    rkh_tmr_stop(&tmr0);
    rkh_tmr_tick(0);

    TEST_ASSERT_EQUAL(0, tmr0.ntick);
    TEST_ASSERT_EQUAL(0, tmr0.used);
    TEST_ASSERT_EQUAL(0, tmr1.tnext);
}

void
test_ExpireTheFirstTimerInTheList(void)
{
    int i;

    rkh_enter_critical_Ignore();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_hook_timetick_Ignore();
    rkh_sma_post_fifo_Expect((RKH_SMA_T *)tmr2.sma, tmr2.evt, &tmr2);
    rkh_exit_critical_Ignore();

    rkh_tmr_init();
    RKH_TMR_INIT(&tmr0, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr0, &ao, 8);
    RKH_TMR_INIT(&tmr1, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr1, &ao, 4);
    RKH_TMR_INIT(&tmr2, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr2, &ao, 2);

    for (i = 2; i > 0; --i)
    {
        rkh_tmr_tick(0);
    }

    TEST_ASSERT_EQUAL(0, tmr2.ntick);
    TEST_ASSERT_EQUAL(0, tmr2.used);
}

void
test_ExpireOneTimerAtTheMiddleOfTheList(void)
{
    int i;

    rkh_enter_critical_Ignore();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_hook_timetick_Ignore();
    rkh_sma_post_fifo_Expect((RKH_SMA_T *)tmr1.sma, tmr1.evt, &tmr1);
    rkh_exit_critical_Ignore();

    rkh_tmr_init();
    RKH_TMR_INIT(&tmr0, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr0, &ao, 8);
    RKH_TMR_INIT(&tmr1, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr1, &ao, 2);
    RKH_TMR_INIT(&tmr2, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr2, &ao, 4);

    for (i = 2; i > 0; --i)
    {
        rkh_tmr_tick(0);
    }

    TEST_ASSERT_EQUAL(0, tmr1.ntick);
    TEST_ASSERT_EQUAL(0, tmr1.used);
    TEST_ASSERT_EQUAL(&tmr0, tmr2.tnext);
}

void
test_ExpireOneTimerAtTheEndOfTheList(void)
{
    int i;

    rkh_enter_critical_Ignore();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_hook_timetick_Ignore();
    rkh_sma_post_fifo_Expect((RKH_SMA_T *)tmr0.sma, tmr0.evt, &tmr0);
    rkh_exit_critical_Ignore();

    rkh_tmr_init();
    RKH_TMR_INIT(&tmr0, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr0, &ao, 2);
    RKH_TMR_INIT(&tmr1, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr1, &ao, 4);
    RKH_TMR_INIT(&tmr2, RKH_UPCAST(RKH_EVT_T, &evt), NULL);
    rkh_tmr_start(&tmr2, &ao, 8);

    for (i = 2; i > 0; --i)
    {
        rkh_tmr_tick(0);
    }

    TEST_ASSERT_EQUAL(0, tmr0.ntick);
    TEST_ASSERT_EQUAL(0, tmr0.used);
    TEST_ASSERT_EQUAL(0, tmr1.tnext);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
