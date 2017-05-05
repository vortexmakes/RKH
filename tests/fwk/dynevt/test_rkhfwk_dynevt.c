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
 *  \file       test_rkhfwk_dynevt.c
 *  \ingroup    test_fwk
 *  \brief      Unit test for dyncamic event of fwk module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_fwk Framework
 *  @{
 *  \brief      Unit test for framework module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.05.04  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkhfwk_dynevt.h"
#include "Mock_rkhassert.h"
#include "Mock_rkhfwk_evtpool.h"
#include "Mock_rkhtrc_record.h"
#include "Mock_rkhtrc_filter.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(dynevt);

/* ---------------------------- Local variables ---------------------------- */
static rui8_t storage[32];

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void 
MockAssertCallback(const char* const file, int line, int cmock_num_calls)
{
    TEST_PASS();
}

/* ---------------------------- Global functions --------------------------- */
/* =========================== Bittbl test group =========================== */
TEST_SETUP(dynevt)
{
    Mock_rkhassert_Init();
    Mock_rkhfwk_evtpool_Init();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_dynEvt_init();
}

TEST_TEAR_DOWN(dynevt)
{
    Mock_rkhassert_Verify();
    Mock_rkhfwk_evtpool_Verify();
    Mock_rkhassert_Destroy();
    Mock_rkhfwk_evtpool_Destroy();
}

/**
 *  \addtogroup test_dynevt for test dynevt group
 *  @{
 *  \name Test cases of dynamic event group
 *  @{ 
 */
TEST(dynevt, RegisterOneEventPool)
{
    rkh_evtPool_init_ExpectAndReturn(storage, sizeof(storage), 4, 
                                     (RKHEvtPool *)1);
    rkh_fwk_registerEvtPool(storage, sizeof(storage), 4);
}

TEST(dynevt, RegisterMultipleEventPool)
{
    int i;

    for (i = 0; i < RKH_CFG_FWK_MAX_EVT_POOL; ++i)
    {
        rkh_evtPool_init_ExpectAndReturn(storage, sizeof(storage), 4, 
                                         (RKHEvtPool *)1);
        rkh_fwk_registerEvtPool(storage, sizeof(storage), 4);
    }
}

TEST(dynevt, Fails_ExceedsNumberOfAllowedEventPools)
{
    int i;

    rkh_assert_Expect("rkhfwk_dynevt", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    for (i = 0; i < RKH_CFG_FWK_MAX_EVT_POOL; ++i)
    {
        rkh_evtPool_init_ExpectAndReturn(storage, sizeof(storage), 4, 
                                         (RKHEvtPool *)1);
    }
    for (i = 0; i < (RKH_CFG_FWK_MAX_EVT_POOL + 1); ++i)
    {
        rkh_fwk_registerEvtPool(storage, sizeof(storage), 4);
    }
}

TEST(dynevt, Fails_NoAssignedPool)
{
    rkh_assert_Expect("rkhfwk_dynevt", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    rkh_evtPool_init_ExpectAndReturn(storage, sizeof(storage), 4, 
                                     (RKHEvtPool *)0);
    rkh_fwk_registerEvtPool(storage, sizeof(storage), 4);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
