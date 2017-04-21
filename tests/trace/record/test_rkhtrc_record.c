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
 *  \file       test_rkhtrc_record.c
 *  \ingroup    test_trace
 *  \brief      Unit test for filter module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_trace Trace
 *  @{
 *  \brief      Unit test for filter module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.20.04  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkhtrc_record.h"
#include "rkhtrc_filter.h"
#include "Mock_rkhsm.h"
#include "Mock_rkhsma.h"
#include "Mock_rkh.h"
#include "Mock_rkhport.h"
#include "Mock_rkhassert.h"
#include "Mock_rkhtrc_out.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(record);

/* ---------------------------- Local variables ---------------------------- */
static RKHROM RKH_ROM_T base = {0, 0, "receiver"};
static RKH_SMA_T receiver;
static RKH_SMA_T sender;
static RKH_EVT_T event;
static RKH_ST_T state = {{RKH_BASIC, "state"}};
static RKH_ST_T pseudoState = {{RKH_CHOICE, "pseudoState"}};

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static rui8_t
getData(void)
{
    rui8_t *output, d;

    output = rkh_trc_get();
    d = *output;
    if (d == RKH_ESC)
    {
        output = rkh_trc_get();
        d = (rui8_t)(*output ^ RKH_XOR);
    }
    return d;
}

static void
checkHeader(rui8_t evtId, rui8_t nSeq, rui32_t tStamp)
{
    rui8_t d;

    d = getData();
    TEST_ASSERT_EQUAL(evtId, d);

    d = getData();
    TEST_ASSERT_EQUAL(nSeq, d);

    d = getData();
    TEST_ASSERT_EQUAL((rui8_t)tStamp, d);
    d = getData();
    TEST_ASSERT_EQUAL_HEX8((rui8_t)(tStamp >> 8), d);
    d = getData();
    TEST_ASSERT_EQUAL_HEX8((rui8_t)(tStamp >> 16), d);
    d = getData();
    TEST_ASSERT_EQUAL((rui8_t)(tStamp >> 24), d);
}

static void
checkTrailer(void)
{
    rui8_t *output;

    getData();
    /* get checksum: TEST_ASSERT_EQUAL_HEX8(..., *output); */
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL_HEX8(RKH_FLG, *output);
}

static void
checkObjectAddress(void *obj)
{
    rui32_t value;
    rui8_t d;

    value = (rui32_t)obj;

    d = getData();
    TEST_ASSERT_EQUAL_HEX8((rui8_t)value, d);
    value >>= 8;
    d = getData();
    TEST_ASSERT_EQUAL_HEX8((rui8_t)value, d);
    value >>= 8;
    d = getData();
    TEST_ASSERT_EQUAL_HEX8((rui8_t)value, d);
    value >>= 8;
    d = getData();
    TEST_ASSERT_EQUAL_HEX8((rui8_t)value, d);
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
    rui8_t d;

    d = getData();
    TEST_ASSERT_EQUAL(value, d);
}

static void
checkU16Value(rui16_t value)
{
    rui8_t low;
    rui8_t high;

    low = getData();
    high = getData();
    TEST_ASSERT_EQUAL((rui8_t)value, low);
    TEST_ASSERT_EQUAL(value >> 8, high);
}

static void
checkU32Value(rui32_t value)
{
    rui8_t byte;

    byte = getData();
    TEST_ASSERT_EQUAL((rui8_t)value, byte);

    byte = getData();
    TEST_ASSERT_EQUAL(value >> 8, byte);

    byte = getData();
    TEST_ASSERT_EQUAL(value >> 16, byte);

    byte = getData();
    TEST_ASSERT_EQUAL(value >> 24, byte);
}

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(record)
{
    rkh_trc_init();
    rkh_trc_get();
    RKH_FILTER_OFF_EVENT(RKH_TRC_ALL_EVENTS);
    RKH_FILTER_OFF_ALL_SMA();
    RKH_FILTER_OFF_ALL_SIGNALS();
    Mock_rkh_Init();
    Mock_rkhport_Init();
    Mock_rkhassert_Init();
}

TEST_TEAR_DOWN(record)
{
    receiver.sm.romrkh = &base;
    event.e = 3;
    event.pool = 5;
    event.nref = 7;
    Mock_rkh_Verify();
    Mock_rkhport_Verify();
    Mock_rkhassert_Verify();
    Mock_rkh_Destroy();
    Mock_rkhport_Destroy();
    Mock_rkhassert_Destroy();
}

/**
 *  \addtogroup test_record Trace record stream test group
 *  @{
 *  \name Test cases of trace record record group
 *  @{ 
 */
TEST(record, InsertRecordHeader)
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

TEST(record, InsertRecordEnd)
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

TEST(record, InsertU8Value)
{
    rui8_t *output;

    rkh_trc_u8(9);

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(9, *output);
}

TEST(record, InsertEscapedValues)
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

TEST(record, InsertU16Value)
{
    rui8_t *output;

    rkh_trc_u16(0x1234);

    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(0x34, *output);
    output = rkh_trc_get();
    TEST_ASSERT_EQUAL(0x12, *output);
}

TEST(record, InsertU32Value)
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

TEST(record, InsertString)
{
    TRCQTY_T len;
    const char *expected = "Hello world!";
    rui8_t *output;

    len = strlen(expected) + 1;
    rkh_trc_str(expected);

    output = rkh_trc_get_block(&len);
    TEST_ASSERT_EQUAL_STRING(expected, output);
}

TEST(record, InsertObject)
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

TEST(record, InsertSignal)
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

TEST(record, InsertAO)
{
    rkh_trc_ao(&receiver);

    checkHeader(RKH_TE_FWK_AO, 0, 0x1234567);
    checkObjectAddress(&receiver);
    checkString("receiver");
    checkTrailer();
}

TEST(record, InsertState)
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

TEST(record, InsertRecord)
{
}

TEST(record, InsertFwkEpoolRecord)
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

TEST(record, InsertFwkActorRecord)
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

TEST(record, InsertSmaActivateRecord)
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

TEST(record, InsertSmaGetRecord)
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

TEST(record, InsertSmaPostFifoRecord)
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

TEST(record, InsertSmaPostLifoRecord)
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

TEST(record, InsertFwkAeRecord)
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

TEST(record, InsertFwkGcrRecord)
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

TEST(record, InsertFwkEpregRecord)
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

TEST(record, InsertFwkStateRecord)
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

TEST(record, InsertFwkPseudoStateRecord)
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

TEST(record, InsertDispatchRecordWithInvalidSignal)
{
    event.e = RKH_COMPLETION_EVENT;

    rkh_enter_critical_Expect();
    rkh_trc_getts_ExpectAndReturn(0x1234567);
    rkh_exit_critical_Expect();

    RKH_TR_SM_DCH(&receiver, &event, &state);

    checkHeader(RKH_TE_SM_DCH, 0, 0x1234567);
    checkObjectAddress(&receiver);
    checkU8Value(event.e);
    checkObjectAddress(&state);
    checkTrailer();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
