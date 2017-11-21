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
 *  \file       test_rkhtmr_mgr.c
 *  \ingroup    test_tmr
 *  \brief      Unit test for software timer module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_tmr Software timer module
 *  @{
 *  \brief      Unit test for software timer module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.07.11  LeFr  v3.0.01  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkhtmr_mgr.h"
#include "Mock_rkhassert.h"
#include "Mock_rkhfwk_hook.h"
#include "Mock_rkhport.h"
#include "Mock_rkhsma.h"
#include "Mock_rkhtrc_record.h"
#include "Mock_rkhtrc_filter.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(mgr);

/* ---------------------------- Local variables ---------------------------- */
static rInt nAvailableTmr;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(mgr)
{
    nAvailableTmr = 0;
    nAvailableTmr = rkh_tmrMgr_init();
}

TEST_TEAR_DOWN(mgr)
{
}

/**
 *  \addtogroup test_rkhtimer_mgr Software timer test group
 *  @{
 *  \e Test cases of timer group
 *  @{  */
TEST(mgr, GetAllAvailableTimersAfterInit)
{
    TEST_ASSERT_EQUAL(nAvailableTmr, RKH_CFG_TMR_MAX_TIMERS);
}

TEST(mgr, GetOneTmr)
{
    RKHTmrMgr *tmr;
    RKH_SMA_T ao;

    tmr = rkh_tmrMgr_ctor("myTmr", 0, &ao, 0, 0);
    TEST_ASSERT_NOT_NULL(tmr);
}

TEST(mgr, GetAllTimers)
{
    rInt i;
    RKHTmrMgr *currTmr, *prevTmr;
    RKH_SMA_T ao;

    for (i = 0, currTmr = prevTmr = (RKHTmrMgr *)0; 
         i < RKH_CFG_TMR_MAX_TIMERS; 
         ++i)
    {
        currTmr = rkh_tmrMgr_ctor("myTmr", 0, &ao, 0, 0);
        TEST_ASSERT_NOT_NULL(currTmr);
        TEST_ASSERT_NOT_EQUAL(currTmr, prevTmr);
    }
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
