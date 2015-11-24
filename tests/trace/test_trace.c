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
 *  \file       test_sm.c
 *  \ingroup    Test
 *
 *  \brief      Unit test for RKH's trace module.
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

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */

#define SIZEOF_BIT_TBL      4
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
setBitTbl(rui8_t *bt, rui16_t bit, ruint value)
{
    rui8_t bitPos;
    rui16_t ix;

    TEST_ASSERT_TRUE(   (bt != (rui8_t *)0) || 
                        (bit < MAX_NUM_BITS) ||
                        (value <= 1));

    bitPos = (rui8_t)(bit & 0x07);
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
setAllBitTbl(rui8_t *bt, ruint value)
{
    TEST_ASSERT_TRUE(bt != (rui8_t *)0);
    memset(bitTbl, value, SIZEOF_BIT_TBL);
}

static
rbool_t
checkBitTbl(rui8_t *bt, rui16_t size)
{
    rui16_t i;
    rui8_t *p;
    rbool_t res;

    for (i = 0, p = bt, res = RKH_OK; i < size; ++i)
    {
        if (*p != FILTER_ON_BYTE)
        {
            res = RKH_FAIL;
            break;
        }
    }
    return res;
}

/* ---------------------------- Global functions --------------------------- */

/* =========================== Filter test group =========================== */

TEST_SETUP(trace_filter)
{
}

TEST_TEAR_DOWN(trace_filter)
{
}

TEST(trace_filter, getBitIndex0)
{
    setAllBitTbl(bitTbl, 0);
    bitTbl[0] = 0x82;

    TEST_ASSERT_EQUAL(0, getBitTbl(bitTbl, 0)); 
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 1)); 
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 7)); 
}

TEST(trace_filter, getBitIndexX)
{
    setAllBitTbl(bitTbl, 0);
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

TEST(trace_filter, setBitIndex0)
{
    setAllBitTbl(bitTbl, 0);

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

TEST(trace_filter, resetBitIndex0)
{
    setAllBitTbl(bitTbl, 0xff);

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

TEST(trace_filter, setBitIndexX)
{
    setAllBitTbl(bitTbl, 0);

    setBitTbl(bitTbl, 8, 1);
    TEST_ASSERT_EQUAL_HEX8(0x01, bitTbl[1]);
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 8)); 

    setBitTbl(bitTbl, 17, 1);
    TEST_ASSERT_EQUAL_HEX8(0x02, bitTbl[2]);
    TEST_ASSERT_EQUAL(1, getBitTbl(bitTbl, 17)); 

    TEST_ASSERT_EQUAL_HEX8(0x00, bitTbl[0]);
    TEST_ASSERT_EQUAL_HEX8(0x00, bitTbl[3]);
}

TEST(trace_filter, resetBitIndexX)
{
    setAllBitTbl(bitTbl, 0xff);

    setBitTbl(bitTbl, 8, 0);
    TEST_ASSERT_EQUAL_HEX8(0xfe, bitTbl[1]);
    TEST_ASSERT_EQUAL(0, getBitTbl(bitTbl, 8)); 

    setBitTbl(bitTbl, 17, 0);
    TEST_ASSERT_EQUAL_HEX8(0xfd, bitTbl[2]);
    TEST_ASSERT_EQUAL(0, getBitTbl(bitTbl, 17)); 

    TEST_ASSERT_EQUAL_HEX8(0xff, bitTbl[0]);
    TEST_ASSERT_EQUAL_HEX8(0xff, bitTbl[3]);
}

/* ============================ Trace test group =========================== */

TEST_SETUP(trace)
{
    rkh_trc_filter_get(&filStatus);
}

TEST_TEAR_DOWN(trace)
{
}

TEST(trace, firstStateAfterInit)
{
    TEST_ASSERT_TRUE(checkBitTbl(filStatus.signal->tbl, 
                                 filStatus.signal->size) == RKH_OK);

    TEST_ASSERT_TRUE(checkBitTbl(filStatus.ao->tbl, 
                                 filStatus.ao->size) == RKH_OK);

    TEST_ASSERT_TRUE(checkBitTbl(filStatus.event, 
                                 RKH_TRC_MAX_EVENTS_IN_BYTES) == RKH_OK);

    TEST_ASSERT_TRUE(checkBitTbl(filStatus.group, 
                                 sizeof(RKH_TG_T)) == RKH_OK);
}

/* ------------------------------ End of file ------------------------------ */
