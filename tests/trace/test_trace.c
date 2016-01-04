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
 *  \file       test_trace.c
 *  \brief      Unit test for RKH's trace module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_trace Trace
 *  @{
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.11.19  LeFr  v2.4.05  ---
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

#define SIZEOF_BIT_TBL      RKH_TRC_MAX_EVENTS_IN_BYTES
#define MAX_NUM_BITS        (SIZEOF_BIT_TBL * 8)
#define FILTER_ON_BYTE      0
#define FILTER_OFF_BYTE     0xff

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */

TEST_GROUP(trace_filter);
TEST_GROUP(trace);

/* ---------------------------- Local variables ---------------------------- */

static RKH_FilterTbl filStatus;
static rui8_t bitTbl[SIZEOF_BIT_TBL];

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */

static
void
setBitTbl(rui8_t *bt, rui16_t bit, rui8_t value)
{
    rui8_t bitPos;
    rui16_t ix;

    TEST_ASSERT_TRUE(   (bt != (rui8_t *)0) || 
                        (bit < MAX_NUM_BITS) ||
                        (value <= 1));

    bitPos = (rui8_t)(bit & 7);
    ix = (rui16_t)(bit >> 3);

    if (value == 1)
        *(bt + ix) |= rkh_maptbl[bitPos];
    else
        *(bt + ix) &= ~rkh_maptbl[bitPos];
}

static
ruint
getBitTbl(rui8_t *bt, rui16_t bit)
{
    rui8_t bitPos;
    rui16_t ix;
    rui8_t bitVal;

    TEST_ASSERT_TRUE(   (bt != (rui8_t *)0) || 
                        (bit < MAX_NUM_BITS));

    bitPos = (rui8_t)(bit & 0x07);
    ix = (rui16_t)(bit >> 3);

    bitVal = (*(bt + ix) & rkh_maptbl[bitPos]) != 0;
    return bitVal;
}

static
void
setAllBitTbl(rui8_t *bt, ruint value, ruint size)
{
    TEST_ASSERT_TRUE(bt != (rui8_t *)0);
    memset(bitTbl, value, size);
}

static
rbool_t
checkBitTblAreOn(rui8_t *bt, rui16_t size)
{
    rui16_t i;
    rui8_t *p;
    rbool_t res;

    for (i = 0, p = bt, res = RKH_OK; i < size; ++i, ++p)
    {
        if (*p != FILTER_ON_BYTE)
        {
            res = RKH_FAIL;
            break;
        }
    }
    return res;
}

static
void
setBlockBit(rui8_t *bt, ruint value, ruint to)
{
    ruint bitPos;

    for (bitPos = 0; bitPos < to; ++bitPos)
    {
        setBitTbl(bt, bitPos, value);
    }
}

/* It could be added to rkhtrc module */
static
void
rkh_trc_filterAllOn(rui8_t *ft, RKH_TE_ID_T ftSize)
{
    RKH_TE_ID_T cnt;
    rui8_t *p;

    for (cnt = 0, p = ft; cnt < ftSize; ++cnt, ++p)
    {
        *p = FILTER_ON_BYTE;
    }
}

/* It could be added to rkhtrc module */
void
rkh_trc_filter_init(void)
{
    rkh_trc_filterAllOn(filStatus.signal->tbl, 
                        (RKH_TE_ID_T)(filStatus.signal->size));
    rkh_trc_filterAllOn(filStatus.ao->tbl, 
                        (RKH_TE_ID_T)(filStatus.ao->size));
    rkh_trc_filterAllOn(filStatus.event, 
                        (RKH_TE_ID_T)(RKH_TRC_MAX_EVENTS_IN_BYTES));
    rkh_trc_filterAllOn(filStatus.group, 
                        (RKH_TE_ID_T)(sizeof(RKH_TG_T)));
}

/* ---------------------------- Global functions --------------------------- */

/* =========================== Filter test group =========================== */

/**
 *  \name Filter Group
 *  Description
 *  @{
 */

TEST_SETUP(trace_filter)
{
}

TEST_TEAR_DOWN(trace_filter)
{
}

/**
 *  \brief Bla bla
 */
TEST(trace_filter, getBitIndex0)
{
    setAllBitTbl(bitTbl, 0, SIZEOF_BIT_TBL);
    bitTbl[0] = 0x82;

    TEST_ASSERT_EQUAL(0, getBitTbl(bitTbl, 0)); 
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 1)); 
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 7)); 
}

/**
 *  \brief Bla bla
 */
TEST(trace_filter, getBitIndexX)
{
    setAllBitTbl(bitTbl, 0, SIZEOF_BIT_TBL);
    bitTbl[0] = 0x80;
    bitTbl[1] = 0x03;
    bitTbl[2] = 0xc0;

    TEST_ASSERT_EQUAL(0, getBitTbl(bitTbl, 0)); 
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 7)); 
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 8)); 
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 9)); 
    TEST_ASSERT_EQUAL(0, getBitTbl(bitTbl, 10)); 
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 22)); 
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 23)); 
}

/**
 *  \brief Bla bla
 */
TEST(trace_filter, setBitIndex0)
{
    setAllBitTbl(bitTbl, 0, SIZEOF_BIT_TBL);

    setBitTbl(bitTbl, 0, 1);
    TEST_ASSERT_EQUAL_HEX8(0x01, bitTbl[0]);
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 0)); 

    setBitTbl(bitTbl, 7, 1);
    TEST_ASSERT_EQUAL_HEX8(0x81, bitTbl[0]);
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 7)); 

    TEST_ASSERT_EQUAL_HEX8(0x00, bitTbl[1]);
    TEST_ASSERT_EQUAL_HEX8(0x00, bitTbl[2]);
    TEST_ASSERT_EQUAL_HEX8(0x00, bitTbl[3]);
}

/**
 *  \brief Bla bla
 */
TEST(trace_filter, resetBitIndex0)
{
    setAllBitTbl(bitTbl, 0xff, SIZEOF_BIT_TBL);

    setBitTbl(bitTbl, 0, 0);
    TEST_ASSERT_EQUAL_HEX8(0xfe, bitTbl[0]);
    TEST_ASSERT_EQUAL(0, getBitTbl(bitTbl, 0)); 

    setBitTbl(bitTbl, 7, 0);
    TEST_ASSERT_EQUAL_HEX8(0x7e, bitTbl[0]);
    TEST_ASSERT_EQUAL(0, getBitTbl(bitTbl, 7)); 

    TEST_ASSERT_EQUAL_HEX8(0xff, bitTbl[1]);
    TEST_ASSERT_EQUAL_HEX8(0xff, bitTbl[2]);
    TEST_ASSERT_EQUAL_HEX8(0xff, bitTbl[3]);
}

/**
 *  \brief Bla bla
 */
TEST(trace_filter, setBitIndexX)
{
    setAllBitTbl(bitTbl, 0, SIZEOF_BIT_TBL);

    setBitTbl(bitTbl, 8, 1);
    TEST_ASSERT_EQUAL_HEX8(0x01, bitTbl[1]);
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 8)); 

    setBitTbl(bitTbl, 17, 1);
    TEST_ASSERT_EQUAL_HEX8(0x02, bitTbl[2]);
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 17)); 

    TEST_ASSERT_EQUAL_HEX8(0x00, bitTbl[0]);
    TEST_ASSERT_EQUAL_HEX8(0x00, bitTbl[3]);
}

/**
 *  \brief Bla bla
 */
TEST(trace_filter, resetBitIndexX)
{
    setAllBitTbl(bitTbl, 0xff, SIZEOF_BIT_TBL);

    setBitTbl(bitTbl, 8, 0);
    TEST_ASSERT_EQUAL_HEX8(0xfe, bitTbl[1]);
    TEST_ASSERT_EQUAL(0, getBitTbl(bitTbl, 8)); 

    setBitTbl(bitTbl, 17, 0);
    TEST_ASSERT_EQUAL_HEX8(0xfd, bitTbl[2]);
    TEST_ASSERT_EQUAL(0, getBitTbl(bitTbl, 17)); 

    TEST_ASSERT_EQUAL_HEX8(0xff, bitTbl[0]);
    TEST_ASSERT_EQUAL_HEX8(0xff, bitTbl[3]);
}

/** @} doxygen end group definition */
/* ============================ Trace test group =========================== */

/**
 *  \addtogroup test_trace_rec Records group
 *  @{
 */

TEST_SETUP(trace)
{
    rkh_trc_filter_get(&filStatus);
    rkh_trc_filter_init();
    memset(bitTbl, FILTER_ON_BYTE, RKH_TRC_MAX_EVENTS_IN_BYTES);
    rkh_assertStub_reset();
}

TEST_TEAR_DOWN(trace)
{
}

TEST(trace, filEventsAreOnAfterInit)
{
    TEST_ASSERT_TRUE(checkBitTblAreOn(filStatus.signal->tbl, 
                                      filStatus.signal->size) == RKH_OK);

    TEST_ASSERT_TRUE(checkBitTblAreOn(filStatus.ao->tbl, 
                                      filStatus.ao->size) == RKH_OK);

    TEST_ASSERT_TRUE(checkBitTblAreOn(filStatus.event, 
                                      RKH_TRC_MAX_EVENTS_IN_BYTES) == RKH_OK);

    TEST_ASSERT_TRUE(checkBitTblAreOn(filStatus.group, 
                                      sizeof(RKH_TG_T)) == RKH_OK);
}

TEST(trace, turnOffOneFilEvent)
{
    RKH_GM_OFFSET_T offset;

    offset = RKH_SM_TTBL_OFFSET;
    bitTbl[offset] = 0x01;

    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_SM_INIT);

    TEST_ASSERT_EQUAL(1, getBitTbl(&filStatus.event[offset], 0)); 
    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
    TEST_ASSERT_EQUAL_HEX8(0x01, 
            filStatus.event[offset + GETEVT(RKH_TE_SM_INIT)]);
    TEST_ASSERT_EQUAL_HEX8(0x08, *filStatus.group);
}

TEST(trace, turnOnOneFilEvent)
{
    bitTbl[RKH_SM_TTBL_OFFSET + 0] = 0x02;

    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_SM_INIT);
    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_SM_CLRH);
    rkh_trc_filter_event_(FILTER_ON, RKH_TE_SM_INIT);

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
    TEST_ASSERT_EQUAL_HEX8(0x08, *filStatus.group);
}

TEST(trace, turnOffMultipleFilEvent)
{
    RKH_GM_OFFSET_T offset;

    offset = RKH_SM_TTBL_OFFSET;
    bitTbl[offset] = 0x01;
    bitTbl[offset + 1] = 0x01;

    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_SM_INIT);
    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_SM_TS_STATE);

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
}

TEST(trace, allOffFilEvent)
{
    memset(bitTbl, FILTER_OFF_BYTE, RKH_TRC_MAX_EVENTS_IN_BYTES);

    rkh_trc_filter_event_(FILTER_OFF, RKH_TRC_ALL_EVENTS);
    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
    TEST_ASSERT_EQUAL_HEX8(0xff, *filStatus.group);
}

TEST(trace, allOnFilEvent)
{
    rkh_trc_filter_event_(FILTER_ON, RKH_TRC_ALL_EVENTS);
    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
    TEST_ASSERT_EQUAL_HEX8(0x00, *filStatus.group);
}

TEST(trace, isOnOffFilEvent)
{
    TEST_ASSERT_TRUE(rkh_trc_isoff_(RKH_TE_FWK_OBJ) == RKH_FALSE);

    setBitTbl(filStatus.event, RKH_TE_MP_INIT, FILTER_OFF);
    setBitTbl(filStatus.group, RKH_TG_MP, FILTER_OFF);
    TEST_ASSERT_TRUE(rkh_trc_isoff_(RKH_TE_MP_INIT) == RKH_TRUE);

    setBitTbl(filStatus.event, RKH_TE_MP_INIT, FILTER_ON);
    TEST_ASSERT_TRUE(rkh_trc_isoff_(RKH_TE_MP_INIT) == RKH_FALSE);
}

TEST(trace, upperAndLowerBoundsFilEvent)
{
    bitTbl[0] = 0x01;
    bitTbl[RKH_TRC_MAX_EVENTS_IN_BYTES - 2] = 0x80;

    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_MP_INIT);
    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_UT_IGNORE_ARG);

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
}

TEST(trace, setAllEventsFromOneGroup)
{
    RKH_TE_ID_T filter, filterFrom, filterTo, offset;

    filterFrom = RKH_SM_START;
    filterTo = RKH_SM_END;
    offset = filStatus.grpFilMap[GETGRP(RKH_SM_START)].offset;
    setBlockBit(&bitTbl[offset], 1, filterTo - filterFrom);

    for (filter = filterFrom; filter < filterTo; ++filter)
    {
        rkh_trc_filter_event_(FILTER_OFF, filter);
    }

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
}

TEST(trace, outOfBoundsProducesRuntimeError)
{
    rkh_trc_filter_event_(FILTER_OFF, RKH_TRC_ALL_EVENTS + 1);
    TEST_ASSERT_EQUAL_STRING("RKH assertion", rkh_assertStub_getLastError());
}

TEST(trace, turnOffOneGroup)
{
    rkh_trc_filter_group_(FILTER_OFF, RKH_TG_MP, EUNCHANGE);
    TEST_ASSERT_EQUAL_HEX8(0x01, *filStatus.group);
}

TEST(trace, turnOnOneGroup)
{
    rkh_trc_filter_group_(FILTER_OFF, RKH_TG_MP, EUNCHANGE);
    rkh_trc_filter_group_(FILTER_ON, RKH_TG_MP, EUNCHANGE);
    TEST_ASSERT_EQUAL_HEX8(0x00, *filStatus.group);
}

TEST(trace, allOnOffGroup)
{
    rkh_trc_filter_group_(FILTER_OFF, RKH_TRC_ALL_GROUPS, EUNCHANGE);
    TEST_ASSERT_EQUAL_HEX8(0xff, *filStatus.group);
    rkh_trc_filter_group_(FILTER_ON, RKH_TRC_ALL_GROUPS, EUNCHANGE);
    TEST_ASSERT_EQUAL_HEX8(0x00, *filStatus.group);
}

TEST(trace, turnOnOffMultipleGroups)
{
    rkh_trc_filter_group_(FILTER_OFF, RKH_TG_MP, EUNCHANGE);
    rkh_trc_filter_group_(FILTER_OFF, RKH_TG_SM, EUNCHANGE);
    rkh_trc_filter_group_(FILTER_OFF, RKH_TG_UT, EUNCHANGE);
    TEST_ASSERT_EQUAL_HEX8(0x89, *filStatus.group);

    rkh_trc_filter_group_(FILTER_ON, RKH_TG_MP, EUNCHANGE);
    rkh_trc_filter_group_(FILTER_ON, RKH_TG_SM, EUNCHANGE);
    rkh_trc_filter_group_(FILTER_ON, RKH_TG_UT, EUNCHANGE);
    TEST_ASSERT_EQUAL_HEX8(0x00, *filStatus.group);
}

TEST(trace, turnOffOneGroupChangedItsEventFilters)
{
    RKHROM RKH_GMTBL_T *pTrcMap;

    rkh_trc_filter_group_(FILTER_OFF, RKH_TG_UT, ECHANGE);
    TEST_ASSERT_EQUAL_HEX8(0x80, *filStatus.group);

    pTrcMap = &filStatus.grpFilMap[RKH_TG_UT];
    memset(&bitTbl[pTrcMap->offset], FILTER_OFF_BYTE, pTrcMap->range);

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
}

TEST(trace, turnOffOneSymFil)
{
    bitTbl[0] = 0x01;
    rkh_trc_symFil(filStatus.ao, 0, FILTER_OFF);
    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.ao->tbl, RKH_TRC_MAX_SMA);
}

TEST(trace, turnOnOneSymFil)
{
    bitTbl[0] = 0x00;
    rkh_trc_symFil(filStatus.ao, RKH_TRC_MAX_SMA - 1, FILTER_OFF);
    rkh_trc_symFil(filStatus.ao, RKH_TRC_MAX_SMA - 1, FILTER_ON);
    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.ao->tbl, RKH_TRC_MAX_SMA);
}

TEST(trace, turnOnOffMultipleSymFil)
{
    bitTbl[0] = 0x89;
    rkh_trc_symFil(filStatus.ao, 0, FILTER_OFF);
    rkh_trc_symFil(filStatus.ao, 3, FILTER_OFF);
    rkh_trc_symFil(filStatus.ao, 7, FILTER_OFF);
    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.ao->tbl, RKH_TRC_MAX_SMA);
}

TEST(trace, allOffOnSymFil)
{
    setAllBitTbl(bitTbl, FILTER_OFF_BYTE, RKH_TRC_MAX_SMA);
    rkh_trc_symFil(filStatus.ao, 0, RKH_TRC_SET_ALL(FILTER_OFF));
    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.ao->tbl, RKH_TRC_MAX_SMA);

    setAllBitTbl(bitTbl, FILTER_ON_BYTE, RKH_TRC_MAX_SMA);
    rkh_trc_symFil(filStatus.ao, 0, RKH_TRC_SET_ALL(FILTER_ON));
    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.ao->tbl, RKH_TRC_MAX_SMA);
}

TEST(trace, isOnOffSymFil)
{
    TEST_ASSERT_TRUE(rkh_trc_symFil_isoff(filStatus.ao, 0) == RKH_FALSE);

    setBitTbl(filStatus.ao->tbl, 0, FILTER_OFF);
    setBitTbl(filStatus.ao->tbl, 3, FILTER_OFF);
    TEST_ASSERT_TRUE(rkh_trc_symFil_isoff(filStatus.ao, 0) == RKH_TRUE);
    TEST_ASSERT_TRUE(rkh_trc_symFil_isoff(filStatus.ao, 3) == RKH_TRUE);

    setBitTbl(filStatus.ao->tbl, 0, FILTER_ON);
    TEST_ASSERT_TRUE(rkh_trc_symFil_isoff(filStatus.ao, 0) == RKH_FALSE);
}

TEST(trace, upperAndLowerBoundsSymFil)
{
    setBitTbl(bitTbl, 0, FILTER_OFF);
    setBitTbl(bitTbl, RKH_TRC_MAX_SMA * 8, FILTER_OFF);

    rkh_trc_symFil(filStatus.ao, 0, FILTER_OFF);
    rkh_trc_symFil(filStatus.ao, RKH_TRC_MAX_SMA * 8, FILTER_OFF);

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.ao->tbl, RKH_TRC_MAX_SMA);
}

TEST(trace, outOfBoundsProducesRuntimeErrorSymFil)
{
    rkh_trc_symFil(filStatus.ao, (filStatus.ao->size * 8) + 1, FILTER_OFF);
    TEST_ASSERT_EQUAL_STRING("RKH assertion", rkh_assertStub_getLastError());

    rkh_trc_symFil(0, 0, FILTER_OFF);
    TEST_ASSERT_EQUAL_STRING("RKH assertion", rkh_assertStub_getLastError());
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
