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
 *  \file       test_rkhtrc_stream.c
 *  \ingroup    test_trace
 *  \brief      Unit test for trace stream module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_trace Trace
 *  @{
 *  \brief      Unit test for trace module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.20.04  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkhtrc_stream.h"
#include "Mock_rkhsm.h"
#include "Mock_rkhsma.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(stream);

/* ---------------------------- Local variables ---------------------------- */
static RKHROM RKH_ROM_T base = {0, 0, "receiver"};
static RKH_SMA_T receiver;
static RKH_SMA_T sender;
static RKH_EVT_T event;
static RKH_ST_T state = {{RKH_BASIC, "state"}};
static RKH_ST_T pseudoState = {{RKH_CHOICE, "pseudoState"}};

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(stream)
{
    rkh_trcStream_init();
}

TEST_TEAR_DOWN(stream)
{
}

/**
 *  \addtogroup test_stream Trace stream test group
 *  @{
 *  \name Test cases of trace stream group
 *  @{ 
 */
TEST(stream, FlagAfterInit)
{
    rui8_t *output;

    output = rkh_trc_get();
    TEST_ASSERT_NOT_NULL(output);
    TEST_ASSERT_EQUAL(RKH_FLG, *output);
}

TEST(stream, NotFullAfterInit)
{
    TRCQTY_T nData;

    rkh_trc_get_block(&nData);
    TEST_ASSERT_TRUE(RKH_CFG_TRC_SIZEOF_STREAM != nData);
}

TEST(stream, NotEmptyThenEmpty)
{
    TRCQTY_T nData;

    TEST_ASSERT_NOT_NULL(rkh_trc_get());
    rkh_trc_get_block(&nData);
    TEST_ASSERT_EQUAL(0, nData);
}

TEST(stream, GetPutOneValue)
{
    rui8_t expected;
    rui8_t *output;

    rkh_trc_get();          /* removes the first inserted value RKH_FLG */
    expected = 128;

    rkh_trc_put(expected);

    output = rkh_trc_get();
    TEST_ASSERT_NOT_NULL(output);
    TEST_ASSERT_EQUAL(expected, *output);
}

TEST(stream, GetPutAFew)
{
    rui8_t *output;

    rkh_trc_put(1);
    rkh_trc_put(2);
    rkh_trc_put(3);

    output = rkh_trc_get();
    TEST_ASSERT_NOT_NULL(output);
    TEST_ASSERT_EQUAL(RKH_FLG, *output);
    output = rkh_trc_get();
    TEST_ASSERT_NOT_NULL(output);
    TEST_ASSERT_EQUAL(1, *output);
    output = rkh_trc_get();
    TEST_ASSERT_NOT_NULL(output);
    TEST_ASSERT_EQUAL(2, *output);
    output = rkh_trc_get();
    TEST_ASSERT_NOT_NULL(output);
    TEST_ASSERT_EQUAL(3, *output);
}

TEST(stream, IsFull)
{
    int i;
    TRCQTY_T nData = RKH_CFG_TRC_SIZEOF_STREAM + 1;

    for (i = 0; i < (RKH_CFG_TRC_SIZEOF_STREAM - 1); i++)
        rkh_trc_put((rui8_t)i);

    rkh_trc_get_block(&nData);
    TEST_ASSERT_EQUAL(RKH_CFG_TRC_SIZEOF_STREAM, nData);    
}

TEST(stream, EmptyToFullToEmpty)
{
    int i;
    TRCQTY_T nData = RKH_CFG_TRC_SIZEOF_STREAM + 1;

    for (i = 0; i < (RKH_CFG_TRC_SIZEOF_STREAM - 1); i++)
        rkh_trc_put((rui8_t)i);

    rkh_trc_get_block(&nData);
    TEST_ASSERT_EQUAL(RKH_CFG_TRC_SIZEOF_STREAM, nData);    

    for (i = 0; i < RKH_CFG_TRC_SIZEOF_STREAM; i++)
        rkh_trc_get();

    rkh_trc_get_block(&nData);
    TEST_ASSERT_EQUAL(0, nData);
}

TEST(stream, WrapAround)
{
    int i;
    rui8_t *output;

    for (i = 0; i < (RKH_CFG_TRC_SIZEOF_STREAM - 1); i++)
        rkh_trc_put((rui8_t)i);

    rkh_trc_get();
    rkh_trc_put(128);

    for (i = 0; i < RKH_CFG_TRC_SIZEOF_STREAM; i++)
    {
        output = rkh_trc_get();
        TEST_ASSERT_NOT_NULL(output);
    }

    TEST_ASSERT_EQUAL(128, *output);    
}

TEST(stream, GetFromEmptyReturnsNull)
{
    rkh_trc_get();
    TEST_ASSERT_NULL(rkh_trc_get());
}

TEST(stream, GetContinuousBlock)
{
    int i;
    TRCQTY_T nData;
    rui8_t *output;
    int qty = 16;

    rkh_trc_get();
    for (i = 0; i < qty; i++)
        rkh_trc_put((rui8_t)i);

    nData = qty;
    output = rkh_trc_get_block(&nData);
    TEST_ASSERT_EQUAL(qty, nData);

    for (i = 0; i < nData; i++, output++)
        TEST_ASSERT_EQUAL((rui8_t)i, *output);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
