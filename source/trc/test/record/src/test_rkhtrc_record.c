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
 *  \file       test_rkhtrc_record.c
 *  \ingroup    test_trace
 *  \brief      Unit test for record of trace module.
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
#include "rkhtrc_record.h"
#include "rkhtrc_filter.h"
#include "Mock_rkhsm.h"
#include "Mock_rkhsma.h"
#include "Mock_rkh.h"
#include "Mock_rkhport.h"
#include "Mock_rkhassert.h"
#include "Mock_rkhtrc_out.h"
#include "Mock_rkhtrc_stream.h"
#include "Mock_rkhtrc_filter.h"

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
static void
expectU8(rui8_t expectData)
{
    if ((expectData == RKH_ESC) || (expectData == RKH_FLG))
    {
        rkh_trc_put_Expect(RKH_ESC);
        rkh_trc_put_Expect((rui8_t)(expectData ^ RKH_XOR));
    }
    else
    {
        rkh_trc_put_Expect(expectData);
    }
}

static void
expectHeader(rui8_t evtId, rui8_t nSeq, rui32_t tStamp, int isCritical)
{
    if (isCritical)
    {
        rkh_enter_critical_Expect();
    }
    expectU8(evtId);
    expectU8(nSeq);
    rkh_trc_getts_ExpectAndReturn(tStamp);
    expectU8((rui8_t)tStamp);
    expectU8((rui8_t)(tStamp >> 8));
    expectU8((rui8_t)(tStamp >> 16));
    expectU8((rui8_t)(tStamp >> 24));
}

static void
expectObjectAddress(void *obj)
{
    rui32_t value;

    value = (rui32_t)obj;
    expectU8((rui8_t)value);
    expectU8((rui8_t)(value >> 8));
    expectU8((rui8_t)(value >> 16));
    expectU8((rui8_t)(value >> 24));
}

static void
expectString(const char *str)
{
    const char *p;

    for (p = str; *p != '\0'; ++p)
    {
        rkh_trc_put_Expect(*p);
    }
    rkh_trc_put_Expect('\0');
}

static void
expectTrailer(int isCritical)
{
    rkh_trc_put_Expect(0);          /* insert checksum */
    rkh_trc_put_IgnoreArg_b();
    rkh_trc_put_Expect(RKH_FLG);    /* insert record flag */
    if (isCritical)
    {
        rkh_exit_critical_Expect();
    }
}

static void
expectU32(rui32_t value)
{
    expectU8((rui8_t)value);
    expectU8((rui8_t)(value >> 8));
    expectU8((rui8_t)(value >> 16));
    expectU8((rui8_t)(value >> 24));
}

static void
expectU16(rui16_t value)
{
    expectU8((rui8_t)value);
    expectU8((rui8_t)(value >> 8));
}

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(record)
{
    rkh_trcStream_init_Expect();
    rkh_trc_init();

    Mock_rkhsm_Init();
    Mock_rkhsma_Init();
    Mock_rkh_Init();
    Mock_rkhport_Init();
    Mock_rkhassert_Init();
    Mock_rkhtrc_out_Init();
    Mock_rkhtrc_stream_Init();
    Mock_rkhtrc_filter_Init();
}

TEST_TEAR_DOWN(record)
{
    receiver.sm.romrkh = &base;
    event.e = 3;
    event.pool = 5;
    event.nref = 7;

    Mock_rkhsm_Verify();
    Mock_rkhsma_Verify();
    Mock_rkh_Verify();
    Mock_rkhport_Verify();
    Mock_rkhassert_Verify();
    Mock_rkhtrc_out_Verify();
    Mock_rkhtrc_stream_Verify();
    Mock_rkhtrc_filter_Verify();
    Mock_rkhsm_Destroy();
    Mock_rkhsma_Destroy();
    Mock_rkh_Destroy();
    Mock_rkhport_Destroy();
    Mock_rkhassert_Destroy();
    Mock_rkhtrc_out_Destroy();
    Mock_rkhtrc_stream_Destroy();
    Mock_rkhtrc_filter_Destroy();
}

/**
 *  \addtogroup test_record Trace record test group
 *  @{
 *  \name Test cases of trace record group
 *  @{ 
 */
TEST(record, InsertRecordHeader)
{
    rkh_trc_put_Expect(8);  /* insert the event ID */
    rkh_trc_put_Expect(0);  /* insert tne sequence number */
                            /* insert tne time-stamp */
    rkh_trc_getts_ExpectAndReturn(0x01234567);
    rkh_trc_put_Expect(0x67);
    rkh_trc_put_Expect(0x45);
    rkh_trc_put_Expect(0x23);
    rkh_trc_put_Expect(0x01);

    rkh_trc_begin(8);
}

TEST(record, InsertRecordEnd)
{
    rui8_t checksum;

    checksum = 0;
    checksum = (rui8_t)(~checksum + 1);
    rkh_trc_put_Expect(checksum);   /* insert checksum */
    rkh_trc_put_Expect(RKH_FLG);    /* insert record flag */

    rkh_trc_end();
}

TEST(record, InsertU8Value)
{
    rui8_t value = 8;

    rkh_trc_put_Expect(value);
    rkh_trc_u8(value);
}

TEST(record, InsertEscapedValues)
{
    rui8_t value = RKH_FLG;
    rkh_trc_put_Expect(RKH_ESC);
    rkh_trc_put_Expect((rui8_t)(value ^ RKH_XOR));

    rkh_trc_u8(RKH_FLG);

    value = RKH_ESC;
    rkh_trc_put_Expect(RKH_ESC);
    rkh_trc_put_Expect((rui8_t)(value ^ RKH_XOR));

    rkh_trc_u8(RKH_ESC);
}

TEST(record, InsertU16Value)
{
    rui16_t value = 0x1234;

    rkh_trc_put_Expect(0x34);
    rkh_trc_put_Expect(0x12);
    rkh_trc_u16(value);
}

TEST(record, InsertU32Value)
{
    rui32_t value = 0x12345678;

    rkh_trc_put_Expect(0x78);
    rkh_trc_put_Expect(0x56);
    rkh_trc_put_Expect(0x34);
    rkh_trc_put_Expect(0x12);

    rkh_trc_u32(value);

}

TEST(record, InsertString)
{
    const char *expected = "Hello world!";
    const char *p;

    for (p = expected; *p != '\0'; ++p)
    {
        rkh_trc_put_Expect(*p);
    }
    rkh_trc_put_Expect('\0');

    rkh_trc_str(expected);
}

TEST(record, InsertObject)
{
    rui8_t obj, evtId = RKH_TE_FWK_OBJ;
    const char *objName = "obj";

    expectHeader(evtId, 0, 0x1234567, 1);
    expectObjectAddress(&obj);
    expectString(objName);
    expectTrailer(1);
    rkh_trc_flush_Expect();

    rkh_trc_obj(evtId, &obj, objName);
}

TEST(record, InsertSignal)
{
    rui8_t signalId = 8;
    rui8_t evtId = RKH_TE_FWK_SIG;
    const char *signalName = "buttonPressed";

    expectHeader(evtId, 0, 0x1234567, 1);
    expectU8(signalId);
    expectString(signalName);
    expectTrailer(1);
    rkh_trc_flush_Expect();

    rkh_trc_sig(signalId, signalName);
}

TEST(record, InsertAO)
{
    expectHeader(RKH_TE_FWK_AO, 0, 0x1234567, 1);
    expectObjectAddress(&receiver);
    expectString("receiver");
    expectTrailer(1);
    rkh_trc_flush_Expect();

    rkh_trc_ao(&receiver);
}

TEST(record, InsertState)
{
    RKH_ST_T state;
    
    state.base.name = "state";
    expectHeader(RKH_TE_FWK_STATE, 0, 0x1234567, 1);
    expectObjectAddress(&receiver);
    expectObjectAddress(&state);
    expectString("state");
    expectTrailer(1);
    rkh_trc_flush_Expect();

    rkh_trc_state(&receiver, (rui8_t *)&state);
}

TEST(record, InsertRecord)
{
}

TEST(record, InsertFwkEpoolRecord)
{
    rui8_t poolId = 2;
    const char *poolName = "ep0";

    expectHeader(RKH_TE_FWK_EPOOL, 0, 0x1234567, 1);
    expectU8(poolId);
    expectString(poolName);
    expectTrailer(1);
    rkh_trc_flush_Expect();

    RKH_TR_FWK_EPOOL(poolId, poolName);
}

TEST(record, InsertFwkActorRecord)
{
    rui8_t actor;
    const char *actorName = "Actor";

    expectHeader(RKH_TE_FWK_ACTOR, 0, 0x1234567, 1);
    expectObjectAddress(&actor);
    expectString(actorName);
    expectTrailer(1);
    rkh_trc_flush_Expect();

    RKH_TR_FWK_ACTOR(&actor, actorName);
}

TEST(record, InsertSmaActivateRecord)
{
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_ACT, RKH_TRUE);
    rkh_trc_symFil_isoff_ExpectAndReturn(RKHFilterSma, RKH_GET_PRIO(&receiver), 
                                         RKH_TRUE);
    expectHeader(RKH_TE_SMA_ACT, 0, 0x1234567, 1);
    expectObjectAddress(&receiver);
    expectU8(RKH_GET_PRIO(&receiver));
    expectU8(16);
    expectTrailer(1);

	RKH_TR_SMA_ACT(&receiver, RKH_GET_PRIO(&receiver), 16);
}

TEST(record, InsertSmaGetRecord)
{
    rui8_t nElem = 4, nMin = 2;

    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_GET, RKH_TRUE);
    rkh_trc_symFil_isoff_ExpectAndReturn(RKHFilterSma, RKH_GET_PRIO(&receiver), 
                                         RKH_TRUE);
    rkh_trc_symFil_isoff_ExpectAndReturn(RKHFilterSignal, event.e, RKH_TRUE);
    expectHeader(RKH_TE_SMA_GET, 0, 0x1234567, 1);
    expectObjectAddress(&receiver);
    expectU8(event.e);
    expectU8(event.pool);
    expectU8(event.nref);
    expectU8(nElem);
    expectU8(nMin);
    expectTrailer(1);

	RKH_TR_SMA_GET(&receiver, &event, event.pool, event.nref, nElem, nMin);
}

TEST(record, InsertSmaPostFifoRecord)
{
    rui8_t nElem = 4, nMin = 2;

    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_FIFO, RKH_TRUE);
    rkh_trc_symFil_isoff_ExpectAndReturn(RKHFilterSma, RKH_GET_PRIO(&receiver), 
                                         RKH_TRUE);
    rkh_trc_symFil_isoff_ExpectAndReturn(RKHFilterSignal, event.e, RKH_TRUE);
    expectHeader(RKH_TE_SMA_FIFO, 0, 0x1234567, 0);
    expectObjectAddress(&receiver);
    expectU8(event.e);
    expectObjectAddress(&sender);
    expectU8(event.pool);
    expectU8(event.nref);
    expectU8(nElem);
    expectU8(nMin);
    expectTrailer(0);

    RKH_TR_SMA_FIFO(&receiver, &event, &sender, event.pool, event.nref, nElem, 
                    nMin);
}

TEST(record, InsertSmaPostLifoRecord)
{
    rui8_t nElem = 4, nMin = 2;

    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_LIFO, RKH_TRUE);
    rkh_trc_symFil_isoff_ExpectAndReturn(RKHFilterSma, RKH_GET_PRIO(&receiver), 
                                         RKH_TRUE);
    rkh_trc_symFil_isoff_ExpectAndReturn(RKHFilterSignal, event.e, RKH_TRUE);
    expectHeader(RKH_TE_SMA_LIFO, 0, 0x1234567, 0);
    expectObjectAddress(&receiver);
    expectU8(event.e);
    expectObjectAddress(&sender);
    expectU8(event.pool);
    expectU8(event.nref);
    expectU8(nElem);
    expectU8(nMin);
    expectTrailer(0);

    RKH_TR_SMA_LIFO(&receiver, &event, &sender, event.pool, event.nref, nElem, 
                    nMin);
}

TEST(record, InsertFwkAeRecord)
{
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_FWK_AE, RKH_TRUE);
    expectHeader(RKH_TE_FWK_AE, 0, 0x1234567, 1);
    expectU16(16);
    expectU8(event.e);
    expectU8(event.pool - 1);
    expectU8(event.nref);
    expectU8(5);
    expectU8(2);
    expectObjectAddress(&receiver);
    expectTrailer(1);

    RKH_TR_FWK_AE(16, &event, 5, 2, &receiver);
}

TEST(record, InsertFwkGcrRecord)
{
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_FWK_GCR, RKH_TRUE);
    expectHeader(RKH_TE_FWK_GCR, 0, 0x1234567, 0);
    expectU8(event.e);
    expectU8(event.pool - 1);
    expectU8(event.nref);
    expectU8(5);
    expectU8(2);
    expectObjectAddress(&receiver);
    expectTrailer(0);

    RKH_TR_FWK_GCR(&event, 5, 2, &receiver);
}

TEST(record, InsertFwkEpregRecord)
{
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_FWK_EPREG, RKH_TRUE);
    expectHeader(RKH_TE_FWK_EPREG, 0, 0x1234567, 1);
    expectU8(1);
    expectU32(128);
    expectU16(32);
    expectU8(4);
    expectTrailer(1);

    RKH_TR_FWK_EPREG(1, 128, 32, 4);
}

TEST(record, InsertFwkStateRecord)
{
    expectHeader(RKH_TE_FWK_STATE, 0, 0x1234567, 1);
    expectObjectAddress(&receiver);
    expectObjectAddress(&state);
    expectString(state.base.name);
    expectTrailer(1);
    rkh_trc_flush_Expect();

    RKH_TR_FWK_STATE(&receiver, &state);
}

TEST(record, InsertFwkPseudoStateRecord)
{
    expectHeader(RKH_TE_FWK_PSTATE, 0, 0x1234567, 1);
    expectObjectAddress(&receiver);
    expectObjectAddress(&pseudoState);
    expectString(pseudoState.base.name);
    expectTrailer(1);
    rkh_trc_flush_Expect();

    RKH_TR_FWK_PSTATE(&receiver, &pseudoState);
}

TEST(record, InsertDispatchRecordWithInvalidSignal)
{
    event.e = RKH_COMPLETION_EVENT;

    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SM_DCH, RKH_TRUE);
    rkh_trc_symFil_isoff_ExpectAndReturn(RKHFilterSma, RKH_GET_PRIO(&receiver), 
                                         RKH_TRUE);
    expectHeader(RKH_TE_SM_DCH, 0, 0x1234567, 1);
    expectObjectAddress(&receiver);
    expectU8(event.e);
    expectObjectAddress(&state);
    expectTrailer(1);

    RKH_TR_SM_DCH(&receiver, &event, &state);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
