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
 *  terms of the GNU General Public License as published by the Recycle Software
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
 *  \file       test_rkhfwk_evtpool.c
 *  \ingroup    test_fwk
 *  \brief      Unit test for event pool of fwk module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_fwk Framework
 *  @{
 *  \brief      Unit test for framework module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.05.09  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkhfwk_evtpool.h"
#include "Mock_rkhtrc_record.h"
#include "Mock_rkhtrc_filter.h"
#include "Mock_rkhport.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(evtpool);

/* ---------------------------- Local variables ---------------------------- */
static rui8_t *stoStart;
static rui32_t stoSize;
static RKH_ES_T evtSize;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void 
MockAssertCallback(const char* const file, int line, int cmock_num_calls)
{
    TEST_PASS();
}

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(evtpool)
{
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_evtPool_init();

    stoStart = (void *)0xdeadbeaf;
    stoSize = 128;
    evtSize = 32;
}

TEST_TEAR_DOWN(evtpool)
{
}

/**
 *  \addtogroup test_evtpool for test event pool group
 *  @{
 *  \name Test cases of event pool group
 *  @{ 
 */
TEST(evtpool, GetOneEvtPool)
{
    RKHEvtPool *ep;

    ep = rkh_evtPool_getPool(stoStart, stoSize, evtSize);
    TEST_ASSERT_NOT_NULL(ep);
}

TEST(evtpool, GetMultipleEvtPool)
{
    RKHEvtPool *ep1, *ep2, *ep3;

    ep1 = rkh_evtPool_getPool(stoStart + (stoSize * 0), stoSize, evtSize * 1);
    TEST_ASSERT_NOT_NULL(ep1);

    ep2 = rkh_evtPool_getPool(stoStart + (stoSize * 1), stoSize, evtSize * 2);
    TEST_ASSERT_NOT_NULL(ep2);

    ep3 = rkh_evtPool_getPool(stoStart + (stoSize * 2), stoSize, evtSize * 4);
    TEST_ASSERT_NOT_NULL(ep3);

    TEST_ASSERT_TRUE((ep1 != ep2) && (ep1 != ep3));
    TEST_ASSERT_TRUE(ep2 != ep3);
}

TEST(evtpool, Fails_ExceedsEvtPoolToAssign)
{
    rint i;
    RKHEvtPool *ep;

    for (i = 0; i < RKH_CFG_FWK_MAX_EVT_POOL; ++i)
    {
        ep = rkh_evtPool_getPool(stoStart, stoSize, evtSize);
        TEST_ASSERT_NOT_NULL(ep);
    }
    ep = rkh_evtPool_getPool(stoStart, stoSize, evtSize);
    TEST_ASSERT_NULL(ep);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
