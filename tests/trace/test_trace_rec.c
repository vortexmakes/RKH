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
 *  \file       test_trace_rec.c
 *  \ingroup    test_trace
 *  \brief      Unit test for record management of trace module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_trace Trace
 *  @{
 *  \brief      Unit test for record management of trace module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.02.24  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkh.h"
#include "rkhassert_stub.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(trace_stream);
TEST_GROUP(trace_args);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
checkHeader(rui8_t evtId, rui8_t nSeq, rui32_t tStamp)
{
    rui8_t *output;

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(evtId, *output);

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(nSeq, *output);

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL((rui8_t)tStamp, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL_HEX8((rui8_t)(tStamp >> 8), *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL_HEX8((rui8_t)(tStamp >> 16), *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL((rui8_t)(tStamp >> 24), *output);
}

static void
checkTrailer(void)
{
    rui8_t *output;

    output = rkh_trc_get();
    /* get checksum: TEST_ASSERT_EQUAL_HEX8(..., *output); */
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL_HEX8(RKH_FLG, *output);
}

static void
checkObjectAddress(rui8_t *obj)
{
    rui32_t value;
    rui8_t *output;

    value = (rui32_t)obj;

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL_HEX8((rui8_t)value, *output);
    value >>= 8;
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL_HEX8((rui8_t)value, *output);
    value >>= 8;
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL_HEX8((rui8_t)value, *output);
    value >>= 8;
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL_HEX8((rui8_t)value, *output);
}

static void
checkString(const char *str)
{
    rui8_t *output;
    TRCQTY_T len;

    len = strlen(str) + 1;
    output = rkh_trc_get_block(&len);
    TEST_ASSERT_EQUAL_STRING(str, output);
}

static void
checkU8Value(rui8_t value)
{
    rui8_t *output;

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(value, *output);
}

/* ---------------------------- Global functions --------------------------- */
/* =========================== Stream test group =========================== */
TEST_SETUP(trace_stream)
{
    rkh_trc_init();
}

TEST_TEAR_DOWN(trace_stream)
{
}

/**
 *  \addtogroup test_trace_stream Trace record stream test group
 *  @{
 *  \name Test cases of trace record stream group
 *  @{ 
 */
TEST(trace_stream, FlagAfterInit)
{
    rui8_t *output;

    output = rkh_trc_get();
    TEST_ASSERT_NOT_NULL(output);
    TEST_ASSERT_EQUAL(RKH_FLG, *output);
}

TEST(trace_stream, NotFullAfterInit)
{
    TRCQTY_T nData;

    rkh_trc_get_block(&nData);
    TEST_ASSERT_TRUE(RKH_CFG_TRC_SIZEOF_STREAM != nData);
}

TEST(trace_stream, NotEmptyThenEmpty)
{
    TRCQTY_T nData;

    TEST_ASSERT_NOT_NULL(rkh_trc_get());
    rkh_trc_get_block(&nData);
    TEST_ASSERT_EQUAL(0, nData);
}

TEST(trace_stream, GetPutOneValue)
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

TEST(trace_stream, GetPutAFew)
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

TEST(trace_stream, IsFull)
{
    int i;
    TRCQTY_T nData = RKH_CFG_TRC_SIZEOF_STREAM + 1;

    for (i = 0; i < (RKH_CFG_TRC_SIZEOF_STREAM - 1); i++)
        rkh_trc_put((rui8_t)i);

    rkh_trc_get_block(&nData);
    TEST_ASSERT_EQUAL(RKH_CFG_TRC_SIZEOF_STREAM, nData);    
}

TEST(trace_stream, EmptyToFullToEmpty)
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

TEST(trace_stream, WrapAround)
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

TEST(trace_stream, GetFromEmptyReturnsNull)
{
    rkh_trc_get();
    TEST_ASSERT_NULL(rkh_trc_get());
}

TEST(trace_stream, GetContinuousBlock)
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

/* ========================== Arguments test group ========================= */
TEST_SETUP(trace_args)
{
    rkh_trc_init();
    rkh_trc_get();
    RKH_FILTER_OFF_EVENT(RKH_TRC_ALL_EVENTS);
    RKH_FILTER_OFF_ALL_SMA();
    RKH_FILTER_OFF_ALL_SIGNALS();
}

TEST_TEAR_DOWN(trace_args)
{
}

/**
 *  \addtogroup test_trace_rec Trace record arguments test group
 *  @{
 *  \name Test cases of trace record arguments group
 *  @{ 
 */
TEST(trace_args, InsertRecordHeader)
{
    rui8_t *output;

    rkh_trc_begin(8);

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(8, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(0, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(0x67, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(0x45, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(0x23, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(0x01, *output);
}

TEST(trace_args, InsertRecordEnd)
{
    rui8_t *output;
    rui8_t checksum;

    rkh_trc_clear_chk();
    checksum = 0;
    checksum = (rui8_t)(~checksum + 1);

    rkh_trc_end();

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(checksum, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL_HEX8(RKH_FLG, *output);
}

TEST(trace_args, InsertU8Value)
{
    rui8_t *output;

    rkh_trc_u8(9);

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(9, *output);
}

TEST(trace_args, InsertEscapedValues)
{
    rui8_t *output;

    rkh_trc_u8(RKH_FLG);

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(RKH_ESC, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(RKH_FLG ^ RKH_XOR, *output);

    rkh_trc_u8(RKH_ESC);

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(RKH_ESC, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(RKH_ESC ^ RKH_XOR, *output);
}

TEST(trace_args, InsertU16Value)
{
    rui8_t *output;

    rkh_trc_u16(0x1234);

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(0x34, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(0x12, *output);
}

TEST(trace_args, InsertU32Value)
{
    rui8_t *output;

    rkh_trc_u32(0x12345678);

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(0x78, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(0x56, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(0x34, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(0x12, *output);
}

TEST(trace_args, InsertString)
{
    TRCQTY_T len;
    const char *expected = "Hello world!";
    rui8_t *output;

    len = strlen(expected) + 1;
    rkh_trc_str(expected);

    output = rkh_trc_get_block(&len);
    TEST_ASSERT_EQUAL_STRING(expected, output);
}

TEST(trace_args, InsertObject)
{
    rui8_t obj, evtId = 8;
    const char *objName = "obj";

    rkh_trc_obj(evtId, &obj, objName);

    checkHeader(evtId, 0, 0x1234567);
    checkObjectAddress(&obj);
    checkString(objName);

    checkTrailer();
}

TEST(trace_args, InsertSignal)
{
    rui8_t signalId = 8;
    const char *signalName = "buttonPressed";

    rkh_trc_sig(signalId, signalName);

    checkHeader(RKH_TE_FWK_SIG, 0, 0x1234567);
    checkU8Value(signalId);
    checkString(signalName);

    checkTrailer();
}

TEST(trace_args, InsertAO)
{
    RKHROM RKH_ROM_T base = {0, 0, "activeObject"};
    RKH_SMA_T activeObject;
    
    activeObject.sm.romrkh = &base;
    rkh_trc_ao(&activeObject);

    checkHeader(RKH_TE_FWK_AO, 0, 0x1234567);
    checkObjectAddress((rui8_t *)&activeObject);
    checkString("activeObject");
    checkTrailer();
}

TEST(trace_args, InsertState)
{
    RKHROM RKH_ROM_T base = {0, 0, "activeObject"};
    RKH_SMA_T activeObject;
    RKH_ST_T state;
    
    activeObject.sm.romrkh = &base;
    state.base.name = "state";

    rkh_trc_state(&activeObject, (rui8_t *)&state);

    checkHeader(RKH_TE_FWK_STATE, 0, 0x1234567);
    checkObjectAddress((rui8_t *)&activeObject);
    checkObjectAddress((rui8_t *)&state);
    checkString("state");
    checkTrailer();
}

TEST(trace_args, InsertRecord)
{
    RKHROM RKH_ROM_T base = {0, 0, "receiver"};
    RKH_SMA_T receiver;
    RKH_SMA_T sender;
    RKH_EVT_T event;
    rui8_t poolId, refCtr;

    receiver.sm.romrkh = &base;
    event.e = 3;
    poolId = 5;
    refCtr = 7;

    RKH_TR_SMA_FIFO(&receiver, &event, &sender, poolId, refCtr);

    checkHeader(RKH_TE_SMA_FIFO, 0, 0x1234567);
    checkObjectAddress((rui8_t *)&receiver);
    checkU8Value(event.e);
    checkObjectAddress((rui8_t *)&sender);
    checkU8Value(poolId);
    checkU8Value(refCtr);
    checkTrailer();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
