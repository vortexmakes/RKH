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
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
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
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkhfwk_dynevt.h"
#include "Mock_rkhassert.h"
#include "Mock_rkhfwk_evtpool.h"
#include "Mock_rkhtrc_record.h"
#include "Mock_rkhtrc_filter.h"
#include "Mock_rkhport.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(dynevt);

/* ---------------------------- Local variables ---------------------------- */
static rui8_t *storage;

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
 *  \addtogroup test_dynevt Test cases of dynamic event group
 *  @{
 *  \name Test cases of dynamic event group
 *  @{ 
 */
TEST(dynevt, RegisterOneEventPool)
{
    rkh_evtPool_getPool_ExpectAndReturn(storage, sizeof(storage), 4, 
                                     (RKHEvtPool *)1);
    rkh_fwk_registerEvtPool(storage, sizeof(storage), 4);
}

TEST(dynevt, RegisterMultipleEventPool)
{
    int i;

    for (i = 0; i < RKH_CFG_FWK_MAX_EVT_POOL; ++i)
    {
        rkh_evtPool_getPool_ExpectAndReturn(storage, sizeof(storage), 4, 
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
        rkh_evtPool_getPool_ExpectAndReturn(storage, sizeof(storage), 4, 
                                         (RKHEvtPool *)1);
    }
    for (i = 0; i < (RKH_CFG_FWK_MAX_EVT_POOL + 1); ++i)
    {
        rkh_fwk_registerEvtPool(storage, sizeof(storage), 4);
    }
}

TEST(dynevt, Fails_UnavailablePool)
{
    rkh_assert_Expect("rkhfwk_dynevt", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    rkh_evtPool_getPool_ExpectAndReturn(storage, sizeof(storage), 4, 
                                     (RKHEvtPool *)0);
    rkh_fwk_registerEvtPool(storage, sizeof(storage), 4);
}

TEST(dynevt, Fails_TriesAllocateOneEvtWithoutAssignedPool)
{
    RKH_EVT_T *evt;

    rkh_assert_Expect("rkhfwk_dynevt", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    evt = rkh_fwk_ae(2, 1, (const void *)0xbeaf);
    TEST_ASSERT_NULL(evt);
}

TEST(dynevt, AllocateOneEvt)
{
    int i, blockSize;
    RKH_EVT_T *pEvt, evt, *expectedEvt;
    int epAddress;
    RKH_SIG_T sig;
    rui8_t pool, nRef;

    sig = 1;
    pool = 3;
    nRef = 0;
    evt.e = 4;
    evt.pool = 0;
    evt.nref = 8;
    expectedEvt = &evt;

    for (i = 0, epAddress = 0xdead0000, blockSize = 4; 
         i < RKH_CFG_FWK_MAX_EVT_POOL; 
         ++i, (blockSize *= 2), ++epAddress)
    {
        rkh_evtPool_getPool_ExpectAndReturn(storage, sizeof(storage), blockSize, 
                                         (RKHEvtPool *)epAddress);
        rkh_fwk_registerEvtPool(storage, sizeof(storage), blockSize);
    }
    rkh_evtPool_getBlockSize_ExpectAndReturn((RKHEvtPool *)0xdead0000, 4);
    rkh_evtPool_getBlockSize_ExpectAndReturn((RKHEvtPool *)0xdead0001, 8);
    rkh_evtPool_getBlockSize_ExpectAndReturn((RKHEvtPool *)0xdead0002, 16);
    rkh_evtPool_get_ExpectAndReturn((RKHEvtPool *)0xdead0002, expectedEvt);

    pEvt = rkh_fwk_ae(9, sig, (const void *)0xbeaf);

    TEST_ASSERT_EQUAL_PTR(expectedEvt, pEvt);
    TEST_ASSERT_EQUAL(sig, pEvt->e);
    TEST_ASSERT_EQUAL(pool, pEvt->pool);
    TEST_ASSERT_EQUAL(nRef, pEvt->nref);
}

TEST(dynevt, Fails_ExceededBlockSize)
{
    int i, blockSize;
    RKH_EVT_T *evt;
    int epAddress;

    rkh_assert_Expect("rkhfwk_dynevt", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    for (i = 0, epAddress = 0xdead0000, blockSize = 4; 
         i < RKH_CFG_FWK_MAX_EVT_POOL; 
         ++i, (blockSize *= 2), ++epAddress)
    {
        rkh_evtPool_getPool_ExpectAndReturn(storage, sizeof(storage), blockSize, 
                                         (RKHEvtPool *)epAddress);
        rkh_fwk_registerEvtPool(storage, sizeof(storage), blockSize);
    }
    rkh_evtPool_getBlockSize_ExpectAndReturn((RKHEvtPool *)0xdead0000, 4);
    rkh_evtPool_getBlockSize_ExpectAndReturn((RKHEvtPool *)0xdead0001, 8);
    rkh_evtPool_getBlockSize_ExpectAndReturn((RKHEvtPool *)0xdead0002, 16);
    rkh_evtPool_getBlockSize_ExpectAndReturn((RKHEvtPool *)0xdead0003, 32);

    evt = rkh_fwk_ae(33, 1, (const void *)0xbeaf);

    TEST_ASSERT_NULL(evt);
}

TEST(dynevt, Fails_UnavailableBlockFromPool)
{
    int i, blockSize;
    RKH_EVT_T *evt;
    int epAddress;

    rkh_assert_Expect("rkhfwk_dynevt", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    for (i = 0, epAddress = 0xdead0000, blockSize = 4; 
         i < RKH_CFG_FWK_MAX_EVT_POOL; 
         ++i, (blockSize *= 2), ++epAddress)
    {
        rkh_evtPool_getPool_ExpectAndReturn(storage, sizeof(storage), blockSize, 
                                         (RKHEvtPool *)epAddress);
        rkh_fwk_registerEvtPool(storage, sizeof(storage), blockSize);
    }
    rkh_evtPool_getBlockSize_ExpectAndReturn((RKHEvtPool *)0xdead0000, 4);
    rkh_evtPool_getBlockSize_ExpectAndReturn((RKHEvtPool *)0xdead0001, 8);
    rkh_evtPool_getBlockSize_ExpectAndReturn((RKHEvtPool *)0xdead0002, 16);
    rkh_evtPool_get_ExpectAndReturn((RKHEvtPool *)0xdead0002, 0);

    evt = rkh_fwk_ae(9, 1, (const void *)0xbeaf);

    TEST_ASSERT_NULL(evt);
}

TEST(dynevt, ReservesOneEvt)
{
    RKH_EVT_T evt;

    evt.e = 8;
    evt.nref = 16;
    evt.pool = 32;
    rkh_enter_critical_Expect();
    rkh_exit_critical_Expect();

    rkh_fwk_reserve(&evt);

    TEST_ASSERT_EQUAL(8, evt.e);
    TEST_ASSERT_EQUAL(16 + 1, evt.nref);
    TEST_ASSERT_EQUAL(32, evt.pool);
}

TEST(dynevt, TriesRecycleNotReferencedEvt)
{
    RKH_EVT_T evt;

    evt.nref = 0;
    rkh_fwk_gc(&evt, (const void *)0xdead);
}

TEST(dynevt, TriesRecycleMultipleReferencedEvt)
{
    RKH_EVT_T evt;

    evt.nref = 4;
    rkh_enter_critical_Expect();
    rkh_exit_critical_Expect();

    rkh_fwk_gc(&evt, (const void *)0xdead);

    TEST_ASSERT_EQUAL(3, evt.nref);
}

TEST(dynevt, RecycleEvt)
{
    RKH_EVT_T evt;

    evt.nref = 1;
    evt.pool = 1;
    rkh_evtPool_getPool_ExpectAndReturn(storage, sizeof(storage), 4, 
                                     (RKHEvtPool *)1);
    rkh_evtPool_put_Expect((RKHEvtPool *)1, &evt);
    rkh_enter_critical_Expect();
    rkh_exit_critical_Expect();

    rkh_fwk_registerEvtPool(storage, sizeof(storage), 4);
    rkh_fwk_gc(&evt, (const void *)0xdead);
}

TEST(dynevt, Fails_OnRecycleEvtNullPool)
{
    RKH_EVT_T evt;

    evt.nref = 1;
    evt.pool = 0;
    rkh_enter_critical_Expect();
    rkh_exit_critical_Expect();
    rkh_assert_Expect("rkhfwk_dynevt", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    rkh_fwk_gc(&evt, (const void *)0xdead);
}

TEST(dynevt, Fails_OnRecycleEvtWrongPool)
{
    RKH_EVT_T evt;

    evt.nref = 1;
    evt.pool = 2;
    rkh_evtPool_getPool_ExpectAndReturn(storage, sizeof(storage), 4, 
                                     (RKHEvtPool *)1);
    rkh_enter_critical_Expect();
    rkh_exit_critical_Expect();
    rkh_assert_Expect("rkhfwk_dynevt", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    rkh_fwk_registerEvtPool(storage, sizeof(storage), 4);
    rkh_fwk_gc(&evt, (const void *)0xdead);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
