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
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
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
    RKH_EVT_T evt;

    rkh_enter_critical_Ignore();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_exit_critical_Ignore();

    RKH_TMR_INIT(&tmr, 
                 RKH_UPCAST(RKH_EVT_T, &evt), 
                 NULL);

    TEST_ASSERT_EQUAL(&evt, tmr.evt);
    TEST_ASSERT_EQUAL(0, tmr.ntick);
    TEST_ASSERT_EQUAL(0, tmr.used);
}

void
test_startTheFirstTimerInTheList(void)
{
    TEST_IGNORE_MESSAGE("To be implemented");
}

void
test_startMultipleTimers(void)
{
    TEST_IGNORE_MESSAGE("To be implemented");
}

void
test_stopTheOnlyOneTimer(void)
{
    TEST_IGNORE_MESSAGE("To be implemented");
}

void
test_stopATimerAtTheBeginningOfTheList(void)
{
    TEST_IGNORE_MESSAGE("To be implemented");
}

void
test_stopATimerAtTheMiddleOfTheList(void)
{
    TEST_IGNORE_MESSAGE("To be implemented");
}

void
test_stopATimerAtTheEndOfTheList(void)
{
    TEST_IGNORE_MESSAGE("To be implemented");
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
