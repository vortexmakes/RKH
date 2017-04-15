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
#include "Mockrkh.h"
#include "Mockrkhport.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(trace_stream);
TEST_GROUP(trace_args);

/* ---------------------------- Local variables ---------------------------- */
static RKHROM RKH_ROM_T base = {0, 0, "receiver"};
static RKH_SMA_T receiver;
static RKH_SMA_T sender;
static RKH_EVT_T event;
static RKH_ST_T state = {{RKH_BASIC, "state"}};
static RKH_ST_T pseudoState = {{RKH_CHOICE, "pseudoState"}};


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
checkObjectAddress(void *obj)
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

static void
checkU16Value(rui16_t value)
{
    rui8_t *low;
    rui8_t *high;

    low = rkh_trc_get();
    high = rkh_trc_get();
    TEST_ASSERT_EQUAL((rui8_t)value, *low);
    TEST_ASSERT_EQUAL(value >> 8, *high);
}

static void
checkU32Value(rui32_t value)
{
    rui8_t *byte;

    byte = rkh_trc_get();
    TEST_ASSERT_EQUAL((rui8_t)value, *byte);

    byte = rkh_trc_get();
    TEST_ASSERT_EQUAL(value >> 8, *byte);

    byte = rkh_trc_get();
    TEST_ASSERT_EQUAL(value >> 16, *byte);

    byte = rkh_trc_get();
    TEST_ASSERT_EQUAL(value >> 24, *byte);
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
    receiver.sm.romrkh = &base;
    event.e = 3;
    event.pool = 5;
    event.nref = 7;
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

    rkh_trc_getts_ExpectAndReturn(0x1234567);

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

    rkh_enter_critical_Expect();
    rkh_trc_getts_ExpectAndReturn(0x1234567);
    rkh_exit_critical_Expect();
    rkh_trc_flush_Expect();

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

    rkh_enter_critical_Expect();
    rkh_trc_getts_ExpectAndReturn(0x1234567);
    rkh_exit_critical_Expect();
    rkh_trc_flush_Expect();

    rkh_trc_sig(signalId, signalName);

    checkHeader(RKH_TE_FWK_SIG, 0, 0x1234567);
    checkU8Value(signalId);
    checkString(signalName);

    checkTrailer();
}

TEST(trace_args, InsertAO)
{
    rkh_trc_ao(&receiver);

    checkHeader(RKH_TE_FWK_AO, 0, 0x1234567);
    checkObjectAddress(&receiver);
    checkString("receiver");
    checkTrailer();
}

TEST(trace_args, InsertState)
{
    RKH_ST_T state;
    
    state.base.name = "state";
    rkh_enter_critical_Expect();
    rkh_trc_getts_ExpectAndReturn(0x1234567);
    rkh_exit_critical_Expect();
    rkh_trc_flush_Expect();

    rkh_trc_state(&receiver, (rui8_t *)&state);

    checkHeader(RKH_TE_FWK_STATE, 0, 0x1234567);
    checkObjectAddress(&receiver);
    checkObjectAddress(&state);
    checkString("state");
    checkTrailer();
}

TEST(trace_args, InsertRecord)
{
}

TEST(trace_args, InsertFwkEpoolRecord)
{
    rui8_t poolId = 2;
    const char *poolName = "ep0";

    rkh_enter_critical_Expect();
    rkh_trc_getts_ExpectAndReturn(0x1234567);
    rkh_exit_critical_Expect();
    rkh_trc_flush_Expect();

    RKH_TR_FWK_EPOOL(poolId, poolName);

    checkHeader(RKH_TE_FWK_EPOOL, 0, 0x1234567);
    checkU8Value(poolId);
    checkString(poolName);
    checkTrailer();
}

TEST(trace_args, InsertFwkActorRecord)
{
    rui8_t actor;
    const char *actorName = "Actor";

    rkh_enter_critical_Expect();
    rkh_trc_getts_ExpectAndReturn(0x1234567);
    rkh_exit_critical_Expect();
    rkh_trc_flush_Expect();

    RKH_TR_FWK_ACTOR(&actor, actorName);

    checkHeader(RKH_TE_FWK_ACTOR, 0, 0x1234567);
    checkObjectAddress(&actor);
    checkString(actorName);
    checkTrailer();
}

TEST(trace_args, InsertSmaActivateRecord)
{
    rkh_enter_critical_Expect();
    rkh_trc_getts_ExpectAndReturn(0x1234567);
    rkh_exit_critical_Expect();

	RKH_TR_SMA_ACT(&receiver, RKH_GET_PRIO(&receiver), 16);

    checkHeader(RKH_TE_SMA_ACT, 0, 0x1234567);
    checkObjectAddress(&receiver);
    checkU8Value(0);
    checkU8Value(16);
    checkTrailer();
}

TEST(trace_args, InsertSmaGetRecord)
{
    rui8_t nElem, nMin;

    nElem = 4;
    nMin = 2;
    rkh_enter_critical_Expect();
    rkh_trc_getts_ExpectAndReturn(0x1234567);
    rkh_exit_critical_Expect();

	RKH_TR_SMA_GET(&receiver, &event, event.pool, event.nref, nElem, nMin);

    checkHeader(RKH_TE_SMA_GET, 0, 0x1234567);
    checkObjectAddress(&receiver);
    checkU8Value(event.e);
    checkU8Value(event.pool);
    checkU8Value(event.nref);
    checkU8Value(nElem);
    checkU8Value(nMin);
    checkTrailer();
}

TEST(trace_args, InsertSmaPostFifoRecord)
{
    rui8_t nElem, nMin;

    nElem = 4;
    nMin = 2;

    rkh_trc_getts_ExpectAndReturn(0x1234567);

    RKH_TR_SMA_FIFO(&receiver, &event, &sender, event.pool, event.nref, nElem, 
                    nMin);

    checkHeader(RKH_TE_SMA_FIFO, 0, 0x1234567);
    checkObjectAddress(&receiver);
    checkU8Value(event.e);
    checkObjectAddress(&sender);
    checkU8Value(event.pool);
    checkU8Value(event.nref);
    checkU8Value(nElem);
    checkU8Value(nMin);
    checkTrailer();
}

TEST(trace_args, InsertSmaPostLifoRecord)
{
    rui8_t nElem, nMin;

    nElem = 4;
    nMin = 2;

    rkh_trc_getts_ExpectAndReturn(0x1234567);

    RKH_TR_SMA_LIFO(&receiver, &event, &sender, event.pool, event.nref, nElem, 
                    nMin);

    checkHeader(RKH_TE_SMA_LIFO, 0, 0x1234567);
    checkObjectAddress(&receiver);
    checkU8Value(event.e);
    checkObjectAddress(&sender);
    checkU8Value(event.pool);
    checkU8Value(event.nref);
    checkU8Value(nElem);
    checkU8Value(nMin);
    checkTrailer();
}

TEST(trace_args, InsertFwkAeRecord)
{
    rkh_enter_critical_Expect();
    rkh_trc_getts_ExpectAndReturn(0x1234567);
    rkh_exit_critical_Expect();

    RKH_TR_FWK_AE(16, &event, 5, 2, &receiver);

    checkHeader(RKH_TE_FWK_AE, 0, 0x1234567);
    checkU16Value(16);
    checkU8Value(event.e);
    checkU8Value(event.pool - 1);
    checkU8Value(event.nref);
    checkU8Value(5);
    checkU8Value(2);
    checkObjectAddress(&receiver);
    checkTrailer();
}

TEST(trace_args, InsertFwkGcrRecord)
{
    rkh_trc_getts_ExpectAndReturn(0x1234567);

    RKH_TR_FWK_GCR(&event, 5, 2, &receiver);

    checkHeader(RKH_TE_FWK_GCR, 0, 0x1234567);
    checkU8Value(event.e);
    checkU8Value(event.pool - 1);
    checkU8Value(event.nref);
    checkU8Value(5);
    checkU8Value(2);
    checkObjectAddress(&receiver);
    checkTrailer();
}

TEST(trace_args, InsertFwkEpregRecord)
{
    rkh_enter_critical_Expect();
    rkh_trc_getts_ExpectAndReturn(0x1234567);
    rkh_exit_critical_Expect();

    RKH_TR_FWK_EPREG(1, 128, 32, 4);

    checkHeader(RKH_TE_FWK_EPREG, 0, 0x1234567);
    checkU8Value(1);
    checkU32Value(128);
    checkU16Value(32);
    checkU8Value(4);
    checkTrailer();
}

TEST(trace_args, InsertFwkStateRecord)
{
    rkh_enter_critical_Expect();
    rkh_trc_getts_ExpectAndReturn(0x1234567);
    rkh_exit_critical_Expect();
    rkh_trc_flush_Expect();

    RKH_TR_FWK_STATE(&receiver, &state);

    checkHeader(RKH_TE_FWK_STATE, 0, 0x1234567);
    checkObjectAddress(&receiver);
    checkObjectAddress(&state);
    checkString(state.base.name);
    checkTrailer();
}

TEST(trace_args, InsertFwkPseudoStateRecord)
{
    rkh_enter_critical_Expect();
    rkh_trc_getts_ExpectAndReturn(0x1234567);
    rkh_exit_critical_Expect();
    rkh_trc_flush_Expect();

    RKH_TR_FWK_PSTATE(&receiver, &pseudoState);

    checkHeader(RKH_TE_FWK_PSTATE, 0, 0x1234567);
    checkObjectAddress(&receiver);
    checkObjectAddress(&pseudoState);
    checkString(pseudoState.base.name);
    checkTrailer();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
