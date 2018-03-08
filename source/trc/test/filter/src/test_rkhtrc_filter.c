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
 *  \file       test_rkhtrc_filter.c
 *  \ingroup    test_trace
 *  \brief      Unit test for runtime filter of trace module.
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
#include "rkhtrc_filter.h"
#include "Mock_rkhassert.h"
#include "Mock_rkhfwk_bittbl.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define SIZEOF_BIT_TBL      RKH_TRC_MAX_EVENTS_IN_BYTES
#define MAX_NUM_BITS        (SIZEOF_BIT_TBL * 8)
#define FILTER_ON_BYTE      0
#define FILTER_OFF_BYTE     0xff

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(toolForTest);
TEST_GROUP(filter);

/* ---------------------------- Local variables ---------------------------- */
static RKH_FilterTbl filStatus;
static rui8_t bitTbl[SIZEOF_BIT_TBL];
static const rui8_t maptbl[] =
{
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
};

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void 
MockAssertCallback(const char* const file, int line, int cmock_num_calls)
{
    TEST_PASS();
}

static void
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
    {
        *(bt + ix) |= maptbl[bitPos];
    }
    else
    {
        *(bt + ix) &= ~maptbl[bitPos];
    }
}

static ruint
getBitTbl(rui8_t *bt, rui16_t bit)
{
    rui8_t bitPos;
    rui16_t ix;
    rui8_t bitVal;

    TEST_ASSERT_TRUE(   (bt != (rui8_t *)0) || 
                        (bit < MAX_NUM_BITS));

    bitPos = (rui8_t)(bit & 0x07);
    ix = (rui16_t)(bit >> 3);

    bitVal = (*(bt + ix) & maptbl[bitPos]) != 0;
    return bitVal;
}

static void
setAllBitTbl(rui8_t *bt, ruint value, ruint size)
{
    TEST_ASSERT_TRUE(bt != (rui8_t *)0);
    memset(bitTbl, value, size);
}

static rbool_t
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

static void
setBlockBit(rui8_t *bt, ruint value, ruint to)
{
    ruint bitPos;

    for (bitPos = 0; bitPos < to; ++bitPos)
    {
        setBitTbl(bt, bitPos, value);
    }
}

/* It could be added to rkhtrc module */
static void
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
TEST_SETUP(toolForTest)
{
}

TEST_TEAR_DOWN(toolForTest)
{
}

/**
 *  \addtogroup test_toolForTest Tool for test filter group
 *  @{
 *  \name Test cases of filter group
 *  @{ 
 */
TEST(toolForTest, getBitIndex0)
{
    setAllBitTbl(bitTbl, 0, SIZEOF_BIT_TBL);
    bitTbl[0] = 0x82;

    TEST_ASSERT_EQUAL(0, getBitTbl(bitTbl, 0)); 
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 1)); 
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 7)); 
}

TEST(toolForTest, getBitIndexX)
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

TEST(toolForTest, setBitIndex0)
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

TEST(toolForTest, resetBitIndex0)
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

TEST(toolForTest, setBitIndexX)
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

TEST(toolForTest, resetBitIndexX)
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
/** @} doxygen end group definition */

/* ============================ Trace test group =========================== */
TEST_SETUP(filter)
{
    rkh_trc_filter_get(&filStatus);
    rkh_trc_filter_init();
    memset(bitTbl, FILTER_ON_BYTE, RKH_TRC_MAX_EVENTS_IN_BYTES);
    Mock_rkhfwk_bittbl_Init();
}

TEST_TEAR_DOWN(filter)
{
    Mock_rkhfwk_bittbl_Verify();
    Mock_rkhfwk_bittbl_Destroy();
}

/**
 *  \addtogroup test_filter Runtime filter test group
 *  @{
 *  \name Test cases of runtime filter group
 *  @{ 
 */
TEST(filter, filEventsAreOnAfterInit)
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

TEST(filter, turnOffOneFilEvent)
{
    RKH_GM_OFFSET_T offset;

    offset = RKH_SM_TTBL_OFFSET;
    bitTbl[offset] = 0x01;
    rkh_bittbl_getBitMask_ExpectAndReturn(GETEVT(RKH_TE_SM_INIT) & 7, 1);
    rkh_bittbl_getBitMask_ExpectAndReturn(GETGRP(RKH_TE_SM_INIT), 8);

    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_SM_INIT);

    TEST_ASSERT_EQUAL(1, getBitTbl(&filStatus.event[offset], 0)); 
    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
    TEST_ASSERT_EQUAL_HEX8(0x01, 
            filStatus.event[offset + GETEVT(RKH_TE_SM_INIT)]);
    TEST_ASSERT_EQUAL_HEX8(0x08, *filStatus.group);
}

TEST(filter, turnOnOneFilEvent)
{
    bitTbl[RKH_SM_TTBL_OFFSET + 0] = 0x02;

    rkh_bittbl_getBitMask_ExpectAndReturn(GETEVT(RKH_TE_SM_INIT) & 7, 1);
    rkh_bittbl_getBitMask_ExpectAndReturn(GETGRP(RKH_TE_SM_INIT), 8);
    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_SM_INIT);

    rkh_bittbl_getBitMask_ExpectAndReturn(GETEVT(RKH_TE_SM_CLRH) & 7, 2);
    rkh_bittbl_getBitMask_ExpectAndReturn(GETGRP(RKH_TE_SM_CLRH), 8);
    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_SM_CLRH);

    rkh_bittbl_getBitMask_ExpectAndReturn(GETEVT(RKH_TE_SM_INIT) & 7, 1);
    rkh_trc_filter_event_(FILTER_ON, RKH_TE_SM_INIT);

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
    TEST_ASSERT_EQUAL_HEX8(0x08, *filStatus.group);
}

TEST(filter, turnOffMultipleFilEvent)
{
    RKH_GM_OFFSET_T offset;

    offset = RKH_SM_TTBL_OFFSET;
    bitTbl[offset] = 0x01;
    bitTbl[offset + 1] = 0x01;

    rkh_bittbl_getBitMask_ExpectAndReturn(GETEVT(RKH_TE_SM_INIT) & 7, 1);
    rkh_bittbl_getBitMask_ExpectAndReturn(GETGRP(RKH_TE_SM_INIT), 8);
    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_SM_INIT);

    rkh_bittbl_getBitMask_ExpectAndReturn(GETEVT(RKH_TE_SM_TS_STATE) & 7, 1);
    rkh_bittbl_getBitMask_ExpectAndReturn(GETGRP(RKH_TE_SM_TS_STATE), 8);
    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_SM_TS_STATE);

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
}

TEST(filter, allOffFilEvent)
{
    memset(bitTbl, FILTER_OFF_BYTE, RKH_TRC_MAX_EVENTS_IN_BYTES);

    rkh_trc_filter_event_(FILTER_OFF, RKH_TRC_ALL_EVENTS);
    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
    TEST_ASSERT_EQUAL_HEX8(0xff, *filStatus.group);
}

TEST(filter, allOnFilEvent)
{
    rkh_trc_filter_event_(FILTER_ON, RKH_TRC_ALL_EVENTS);
    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
    TEST_ASSERT_EQUAL_HEX8(0x00, *filStatus.group);
}

TEST(filter, isOnOffFilEvent)
{
    rkh_bittbl_getBitMask_ExpectAndReturn(GETGRP(RKH_TE_FWK_OBJ), 0x20);
    TEST_ASSERT_TRUE(rkh_trc_isoff_(RKH_TE_FWK_OBJ) == RKH_FALSE);

    setBitTbl(filStatus.event, RKH_TE_MP_INIT, FILTER_OFF);
    setBitTbl(filStatus.group, RKH_TG_MP, FILTER_OFF);
    rkh_bittbl_getBitMask_ExpectAndReturn(GETGRP(RKH_TE_MP_INIT), 0x01);
    rkh_bittbl_getBitMask_ExpectAndReturn(GETEVT(RKH_TE_MP_INIT) & 7, 0x01);
    TEST_ASSERT_TRUE(rkh_trc_isoff_(RKH_TE_MP_INIT) == RKH_TRUE);

    setBitTbl(filStatus.event, RKH_TE_MP_INIT, FILTER_ON);
    rkh_bittbl_getBitMask_ExpectAndReturn(GETGRP(RKH_TE_MP_INIT), 0x01);
    rkh_bittbl_getBitMask_ExpectAndReturn(GETEVT(RKH_TE_MP_INIT) & 7, 0x01);
    TEST_ASSERT_TRUE(rkh_trc_isoff_(RKH_TE_MP_INIT) == RKH_FALSE);
}

TEST(filter, upperAndLowerBoundsFilEvent)
{
    bitTbl[0] = 0x01;
    bitTbl[RKH_TRC_MAX_EVENTS_IN_BYTES - 2] = 0x80;

    rkh_bittbl_getBitMask_ExpectAndReturn(GETGRP(RKH_TE_MP_INIT), 0x01);
    rkh_bittbl_getBitMask_ExpectAndReturn(GETEVT(RKH_TE_MP_INIT) & 7, 0x01);
    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_MP_INIT);

    rkh_bittbl_getBitMask_ExpectAndReturn(GETGRP(RKH_TE_UT_IGNORE_ARG), 0x80);
    rkh_bittbl_getBitMask_ExpectAndReturn(GETEVT(RKH_TE_UT_IGNORE_ARG) & 7, 
                                          0x80);
    rkh_trc_filter_event_(FILTER_OFF, RKH_TE_UT_IGNORE_ARG);

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
}

TEST(filter, setAllEventsFromOneGroup)
{
    RKH_TE_ID_T filter, filterFrom, filterTo, offset;
    rui8_t evt;

    filterFrom = RKH_SM_START;
    filterTo = RKH_SM_END;
    offset = filStatus.grpFilMap[GETGRP(RKH_SM_START)].offset;
    setBlockBit(&bitTbl[offset], 1, filterTo - filterFrom);

    for (filter = filterFrom; filter < filterTo; ++filter)
    {
        evt = GETEVT(filter) & 7;
        rkh_bittbl_getBitMask_ExpectAndReturn(evt, maptbl[evt]);
        rkh_bittbl_getBitMask_ExpectAndReturn(RKH_TG_SM, 8);
        rkh_trc_filter_event_(FILTER_OFF, filter);
    }

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
}

TEST(filter, outOfBoundsProducesRuntimeError)
{
    rkh_assert_Expect("rkhtrc_filter", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    rkh_trc_filter_event_(FILTER_OFF, RKH_TRC_ALL_EVENTS + 1);
}

TEST(filter, turnOffOneGroup)
{
    rkh_bittbl_getBitMask_ExpectAndReturn(RKH_TG_MP, maptbl[RKH_TG_MP]);
    rkh_trc_filter_group_(FILTER_OFF, RKH_TG_MP, EUNCHANGE);
    TEST_ASSERT_EQUAL_HEX8(0x01, *filStatus.group);
}

TEST(filter, turnOnOneGroup)
{
    rkh_bittbl_getBitMask_ExpectAndReturn(RKH_TG_MP, maptbl[RKH_TG_MP]);
    rkh_trc_filter_group_(FILTER_OFF, RKH_TG_MP, EUNCHANGE);

    rkh_bittbl_getBitMask_ExpectAndReturn(RKH_TG_MP, maptbl[RKH_TG_MP]);
    rkh_trc_filter_group_(FILTER_ON, RKH_TG_MP, EUNCHANGE);
    TEST_ASSERT_EQUAL_HEX8(0x00, *filStatus.group);
}

TEST(filter, allOnOffGroup)
{
    rkh_trc_filter_group_(FILTER_OFF, RKH_TRC_ALL_GROUPS, EUNCHANGE);
    TEST_ASSERT_EQUAL_HEX8(0xff, *filStatus.group);
    rkh_trc_filter_group_(FILTER_ON, RKH_TRC_ALL_GROUPS, EUNCHANGE);
    TEST_ASSERT_EQUAL_HEX8(0x00, *filStatus.group);
}

TEST(filter, turnOnOffMultipleGroups)
{
    rkh_bittbl_getBitMask_ExpectAndReturn(RKH_TG_MP, maptbl[RKH_TG_MP]);
    rkh_trc_filter_group_(FILTER_OFF, RKH_TG_MP, EUNCHANGE);

    rkh_bittbl_getBitMask_ExpectAndReturn(RKH_TG_SM, maptbl[RKH_TG_SM]);
    rkh_trc_filter_group_(FILTER_OFF, RKH_TG_SM, EUNCHANGE);

    rkh_bittbl_getBitMask_ExpectAndReturn(RKH_TG_UT, maptbl[RKH_TG_UT]);
    rkh_trc_filter_group_(FILTER_OFF, RKH_TG_UT, EUNCHANGE);

    TEST_ASSERT_EQUAL_HEX8(0x89, *filStatus.group);

    rkh_bittbl_getBitMask_ExpectAndReturn(RKH_TG_MP, maptbl[RKH_TG_MP]);
    rkh_trc_filter_group_(FILTER_ON, RKH_TG_MP, EUNCHANGE);

    rkh_bittbl_getBitMask_ExpectAndReturn(RKH_TG_SM, maptbl[RKH_TG_SM]);
    rkh_trc_filter_group_(FILTER_ON, RKH_TG_SM, EUNCHANGE);

    rkh_bittbl_getBitMask_ExpectAndReturn(RKH_TG_UT, maptbl[RKH_TG_UT]);
    rkh_trc_filter_group_(FILTER_ON, RKH_TG_UT, EUNCHANGE);

    TEST_ASSERT_EQUAL_HEX8(0x00, *filStatus.group);
}

TEST(filter, turnOffOneGroupChangedItsEventFilters)
{
    RKHROM RKH_GMTBL_T *pTrcMap;

    rkh_bittbl_getBitMask_ExpectAndReturn(RKH_TG_UT, maptbl[RKH_TG_UT]);
    rkh_trc_filter_group_(FILTER_OFF, RKH_TG_UT, ECHANGE);
    TEST_ASSERT_EQUAL_HEX8(0x80, *filStatus.group);

    pTrcMap = &filStatus.grpFilMap[RKH_TG_UT];
    memset(&bitTbl[pTrcMap->offset], FILTER_OFF_BYTE, pTrcMap->range);

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.event, 
                             RKH_TRC_MAX_EVENTS_IN_BYTES);
}

TEST(filter, turnOffOneSymFil)
{
    bitTbl[0] = 0x01;

    rkh_bittbl_getBitMask_ExpectAndReturn(0, maptbl[0]);
    rkh_trc_symFil(RKHFilterSma, 0, FILTER_OFF);

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.ao->tbl, RKH_TRC_MAX_SMA);
}

TEST(filter, turnOnOneSymFil)
{
    bitTbl[0] = 0x00;

    rkh_bittbl_getBitMask_ExpectAndReturn(RKH_TRC_MAX_SMA - 1, 
                                          maptbl[RKH_TRC_MAX_SMA - 1]);
    rkh_trc_symFil(RKHFilterSma, RKH_TRC_MAX_SMA - 1, FILTER_OFF);

    rkh_bittbl_getBitMask_ExpectAndReturn(RKH_TRC_MAX_SMA - 1, 
                                          maptbl[RKH_TRC_MAX_SMA - 1]);
    rkh_trc_symFil(RKHFilterSma, RKH_TRC_MAX_SMA - 1, FILTER_ON);

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.ao->tbl, RKH_TRC_MAX_SMA);
}

TEST(filter, turnOnOffMultipleSymFil)
{
    bitTbl[0] = 0x89;

    rkh_bittbl_getBitMask_ExpectAndReturn(0, maptbl[0]);
    rkh_trc_symFil(RKHFilterSma, 0, FILTER_OFF);

    rkh_bittbl_getBitMask_ExpectAndReturn(3, maptbl[3]);
    rkh_trc_symFil(RKHFilterSma, 3, FILTER_OFF);

    rkh_bittbl_getBitMask_ExpectAndReturn(7, maptbl[7]);
    rkh_trc_symFil(RKHFilterSma, 7, FILTER_OFF);

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.ao->tbl, RKH_TRC_MAX_SMA);
}

TEST(filter, allOffOnSymFil)
{
    setAllBitTbl(bitTbl, FILTER_OFF_BYTE, RKH_TRC_MAX_SMA);
    rkh_trc_symFil(RKHFilterSma, 0, RKH_TRC_SET_ALL(FILTER_OFF));
    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.ao->tbl, RKH_TRC_MAX_SMA);

    setAllBitTbl(bitTbl, FILTER_ON_BYTE, RKH_TRC_MAX_SMA);
    rkh_trc_symFil(RKHFilterSma, 0, RKH_TRC_SET_ALL(FILTER_ON));
    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.ao->tbl, RKH_TRC_MAX_SMA);
}

TEST(filter, isOnOffSymFil)
{
    rkh_bittbl_getBitMask_ExpectAndReturn(0, maptbl[0]);
    TEST_ASSERT_TRUE(rkh_trc_symFil_isoff(RKHFilterSma, 0) == RKH_FALSE);

    setBitTbl(filStatus.ao->tbl, 0, FILTER_OFF);
    setBitTbl(filStatus.ao->tbl, 3, FILTER_OFF);
    rkh_bittbl_getBitMask_ExpectAndReturn(0, maptbl[0]);
    TEST_ASSERT_TRUE(rkh_trc_symFil_isoff(RKHFilterSma, 0) == RKH_TRUE);
    rkh_bittbl_getBitMask_ExpectAndReturn(3, maptbl[3]);
    TEST_ASSERT_TRUE(rkh_trc_symFil_isoff(RKHFilterSma, 3) == RKH_TRUE);

    rkh_bittbl_getBitMask_ExpectAndReturn(0, maptbl[0]);
    setBitTbl(filStatus.ao->tbl, 0, FILTER_ON);
    TEST_ASSERT_TRUE(rkh_trc_symFil_isoff(RKHFilterSma, 0) == RKH_FALSE);
}

TEST(filter, upperAndLowerBoundsSymFil)
{
    setBitTbl(bitTbl, 0, FILTER_OFF);
    setBitTbl(bitTbl, RKH_TRC_MAX_SMA * 8, FILTER_OFF);

    rkh_bittbl_getBitMask_ExpectAndReturn(0, maptbl[0]);
    rkh_trc_symFil(RKHFilterSma, 0, FILTER_OFF);

    rkh_bittbl_getBitMask_ExpectAndReturn(0, maptbl[0]);
    rkh_trc_symFil(RKHFilterSma, RKH_TRC_MAX_SMA * 8, FILTER_OFF);

    TEST_ASSERT_EQUAL_MEMORY(bitTbl, filStatus.ao->tbl, RKH_TRC_MAX_SMA);
}

TEST(filter, outOfBoundsProducesRuntimeErrorSymFil)
{
    rkh_assert_Expect("rkhtrc_filter", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    rkh_trc_symFil(RKHFilterSma, (filStatus.ao->size * 8) + 1, FILTER_OFF);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
