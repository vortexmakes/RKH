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
#include "Mock_rkhmempool.h"
#include "Mock_rkhassert.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(evtpool);

/* ---------------------------- Local variables ---------------------------- */
static rui8_t *stoStart;
static rui16_t stoSize;
static RKH_ES_T evtSize;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void 
MockAssertCallback(const char* const file, int line, int cmock_num_calls)
{
    TEST_PASS();
}

static void 
MockMemPoolInitCallback(RKH_MEMPOOL_T *mp, void* sstart, rui16_t ssize, 
                        RKH_MPBS_T bsize, int cmock_num_calls)
{
    mp->nblocks = 1;    /* this value is only used just for testing */
}

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(evtpool)
{
    Mock_rkhmempool_Init();
    Mock_rkhassert_Init();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_evtPool_init();
    rkh_assert_StubWithCallback(MockAssertCallback);
    rkh_memPool_init_StubWithCallback(MockMemPoolInitCallback);

    stoStart = (void *)0xdeadbeaf;
    stoSize = 128;
    evtSize = 32;
}

TEST_TEAR_DOWN(evtpool)
{
    Mock_rkhmempool_Verify();
    Mock_rkhmempool_Destroy();
    Mock_rkhassert_Verify();
    Mock_rkhassert_Destroy();
}

/**
 *  \addtogroup test_evtpool Test cases of event pool group
 *  @{
 *  \name Test cases of event pool group
 *  @{ 
 */
TEST(evtpool, AfterInitAllEvtPoolAvailable)
{
    RKHEvtPool *ep;
    int i;

    for (i = 0; i < RKH_CFG_FWK_MAX_EVT_POOL; ++i)
    {
        rkh_memPool_init_Expect(0, stoStart, stoSize, (RKH_MPBS_T)evtSize);
        rkh_memPool_init_IgnoreArg_mp();

        ep = rkh_evtPool_getPool(stoStart, stoSize, evtSize);
        TEST_ASSERT_NOT_NULL(ep);
    } 
    TEST_ASSERT_EQUAL(RKH_CFG_FWK_MAX_EVT_POOL, i);
}

TEST(evtpool, GetOneEvtPool)
{
    RKHEvtPool *ep;

    rkh_memPool_init_Expect(0, stoStart, stoSize, (RKH_MPBS_T)evtSize);
    rkh_memPool_init_IgnoreArg_mp();

    ep = rkh_evtPool_getPool(stoStart, stoSize, evtSize);
    TEST_ASSERT_NOT_NULL(ep);
}

TEST(evtpool, GetMultipleEvtPool)
{
    rInt i;
    RKHEvtPool *ep[RKH_CFG_FWK_MAX_EVT_POOL];

    for (i = 0; i < RKH_CFG_FWK_MAX_EVT_POOL; ++i)
    {
        rkh_memPool_init_Expect(0, stoStart + (stoSize * i), 
                           stoSize, (RKH_MPBS_T)evtSize * (2 * (i + 1)));
        rkh_memPool_init_IgnoreArg_mp();
        ep[i] = rkh_evtPool_getPool(stoStart + (stoSize * i), stoSize, 
                                  evtSize * (2 * (i + 1)));
        TEST_ASSERT_NOT_NULL(ep[i]);
    }

    TEST_ASSERT_TRUE((ep[0] != ep[1]) && (ep[0] != ep[2]));
    TEST_ASSERT_TRUE(ep[1] != ep[2]);
}

TEST(evtpool, Fails_ExceedsMaxAvailableEvtPool)
{
    rInt i;
    RKHEvtPool *ep;

    for (i = 0; i < RKH_CFG_FWK_MAX_EVT_POOL; ++i)
    {
        rkh_memPool_init_Expect(0, stoStart, stoSize, (RKH_MPBS_T)evtSize);
        rkh_memPool_init_IgnoreArg_mp();
        ep = rkh_evtPool_getPool(stoStart, stoSize, evtSize);
        TEST_ASSERT_NOT_NULL(ep);
    }
    ep = rkh_evtPool_getPool(stoStart, stoSize, evtSize);
    TEST_ASSERT_NULL(ep);
}

TEST(evtpool, GetBlockSize)
{
    RKHEvtPool *ep;

    rkh_memPool_init_Expect(0, stoStart, stoSize, (RKH_MPBS_T)evtSize);
    rkh_memPool_init_IgnoreArg_mp();

    ep = rkh_evtPool_getPool(stoStart, stoSize, evtSize);
    rkh_evtPool_getBlockSize(ep);
}

TEST(evtpool, Fails_GetBlockSizeInvalidInstance)
{
    rkh_assert_Expect("rkhfwk_evtpool", 0);
    rkh_assert_IgnoreArg_line();

    rkh_evtPool_getBlockSize((RKHEvtPool *)0);
}

TEST(evtpool, GetBlock)
{
    RKHEvtPool *ep;
    RKH_EVT_T *evt;

    rkh_memPool_init_Expect(0, stoStart, stoSize, (RKH_MPBS_T)evtSize);
    rkh_memPool_init_IgnoreArg_mp();
    rkh_memPool_get_ExpectAndReturn(0, (void *)0xdead);
    rkh_memPool_get_IgnoreArg_mp();

    ep = rkh_evtPool_getPool(stoStart, stoSize, evtSize);
    evt = rkh_evtPool_get(ep);

    TEST_ASSERT_EQUAL_PTR((RKH_EVT_T *)0xdead, evt);
}

TEST(evtpool, Fails_GetBlockInvalidInstance)
{
    rkh_assert_Expect("rkhfwk_evtpool", 0);
    rkh_assert_IgnoreArg_line();

    rkh_evtPool_get((RKHEvtPool *)0);
}

TEST(evtpool, PutBlock)
{
    RKHEvtPool *ep;
    RKH_EVT_T *evt = (RKH_EVT_T *)0xdead;

    rkh_memPool_init_Expect(0, stoStart, stoSize, (RKH_MPBS_T)evtSize);
    rkh_memPool_init_IgnoreArg_mp();
    rkh_memPool_put_Expect(0, evt);
    rkh_memPool_put_IgnoreArg_mp();

    ep = rkh_evtPool_getPool(stoStart, stoSize, evtSize);
    rkh_evtPool_put(ep, evt);
}

TEST(evtpool, Fails_PutBlockInvalidInstance)
{
    RKH_EVT_T *evt = (RKH_EVT_T *)0xdead;

    rkh_assert_Expect("rkhfwk_evtpool", 0);
    rkh_assert_IgnoreArg_line();

    rkh_evtPool_put((RKHEvtPool *)0, evt);
}

TEST(evtpool, GetNumUsed)
{
    RKHEvtPool *ep;

    rkh_memPool_init_Expect(0, stoStart, stoSize, (RKH_MPBS_T)evtSize);
    rkh_memPool_init_IgnoreArg_mp();

    ep = rkh_evtPool_getPool(stoStart, stoSize, evtSize);
    rkh_evtPool_getNumUsed(ep);
}

TEST(evtpool, Fails_GetNumUsedInvalidInstance)
{
    rkh_assert_Expect("rkhfwk_evtpool", 0);
    rkh_assert_IgnoreArg_line();

    rkh_evtPool_getNumUsed((RKHEvtPool *)0);
}

TEST(evtpool, GetNumMin)
{
    RKHEvtPool *ep;

    rkh_memPool_init_Expect(0, stoStart, stoSize, (RKH_MPBS_T)evtSize);
    rkh_memPool_init_IgnoreArg_mp();

    ep = rkh_evtPool_getPool(stoStart, stoSize, evtSize);
    rkh_evtPool_getNumMin(ep);
}

TEST(evtpool, Fails_GetNumMinInvalidInstance)
{
    rkh_assert_Expect("rkhfwk_evtpool", 0);
    rkh_assert_IgnoreArg_line();

    rkh_evtPool_getNumMin((RKHEvtPool *)0);
}

TEST(evtpool, GetNumBlock)
{
    RKHEvtPool *ep;

    rkh_memPool_init_Expect(0, stoStart, stoSize, (RKH_MPBS_T)evtSize);
    rkh_memPool_init_IgnoreArg_mp();

    ep = rkh_evtPool_getPool(stoStart, stoSize, evtSize);
    rkh_evtPool_getNumBlock(ep);
}

TEST(evtpool, Fails_GetNumBlockInvalidInstance)
{
    rkh_assert_Expect("rkhfwk_evtpool", 0);
    rkh_assert_IgnoreArg_line();

    rkh_evtPool_getNumBlock((RKHEvtPool *)0);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
