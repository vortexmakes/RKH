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
 *  \file       test_rkhsma_prio.c
 *  \ingroup    test_sma
 *  \brief      Unit test for priority mechanism of sma module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_sma SMA
 *  @{
 *  \brief      Unit test for sma module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.05.15  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkhsma_prio.h"
#include "Mock_rkhfwk_bittbl.h"
#include "Mock_rkhassert.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
static const rui8_t bitMaskTbl[] =
{
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
};

static const rui8_t leastBitSetTbl[] =
{
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0x00 to 0x0F */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0x10 to 0x1F */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0x20 to 0x2F */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0x30 to 0x3F */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0x40 to 0x4F */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0x50 to 0x5F */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0x60 to 0x6F */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0x70 to 0x7F */
    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0x80 to 0x8F */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0x90 to 0x9F */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0xA0 to 0xAF */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0xB0 to 0xBF */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0xC0 to 0xCF */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0xD0 to 0xDF */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,     /* 0xE0 to 0xEF */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0      /* 0xF0 to 0xFF */
};

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(prio);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void 
MockAssertCallback(const char* const file, int line, int cmock_num_calls)
{
    TEST_PASS();
}

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(prio)
{
    rkh_smaPrio_init();
}

TEST_TEAR_DOWN(prio)
{
}

/**
 *  \addtogroup test_prio Test cases of priority mechanism group
 *  @{
 *  \name Test cases of priority mechanism group
 *  @{ 
 */
TEST(prio, ClearAfterInit)
{
    rbool_t result;

    result = rkh_smaPrio_isReady();
    TEST_ASSERT_EQUAL(0, result);
}

TEST(prio, SetOneActiveObjectReadyToRun)
{
    rbool_t result;
    rui8_t prio = 1, resultPrio, column, row;

    column = prio >> 3;
    row = prio & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);

    rkh_smaPrio_setReady(prio);
    result = rkh_smaPrio_isReady();
    TEST_ASSERT_EQUAL(1, result);

    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(1, leastBitSetTbl[1]);
    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(2, leastBitSetTbl[2]);
    resultPrio = rkh_smaPrio_findHighest();
    TEST_ASSERT_EQUAL(prio, resultPrio);
}

TEST(prio, SetMultipleActiveObjectsReadyToRun)
{
    rui8_t prioA = 1, prioC = 0, prioB = 15, resultPrio, column, row;

    column = prioA >> 3;
    row = prioA & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_smaPrio_setReady(prioA);

    column = prioB >> 3;
    row = prioB & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_smaPrio_setReady(prioB);

    column = prioC >> 3;
    row = prioC & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_smaPrio_setReady(prioC);

    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(3, leastBitSetTbl[3]);
    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(3, leastBitSetTbl[3]);
    resultPrio = rkh_smaPrio_findHighest();
    TEST_ASSERT_EQUAL(prioC, resultPrio);
}

TEST(prio, SetOneActiveObjectUnready)
{
    rbool_t result;
    rui8_t prio = 1, resultPrio, column, row;

    column = prio >> 3;
    row = prio & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);

    rkh_smaPrio_setReady(prio);

    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(1, leastBitSetTbl[1]);
    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(2, leastBitSetTbl[2]);
    resultPrio = rkh_smaPrio_findHighest();
    TEST_ASSERT_EQUAL(prio, resultPrio);

    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_smaPrio_setUnready(prio);
    result = rkh_smaPrio_isReady();
    TEST_ASSERT_EQUAL(0, result);
}

TEST(prio, SetMultipleActiveObjectsUnready)
{
    rbool_t result;
    rui8_t prioA = 1, prioC = 0, prioB = 15, column, row;

    column = prioA >> 3;
    row = prioA & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_smaPrio_setReady(prioA);

    column = prioB >> 3;
    row = prioB & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_smaPrio_setReady(prioB);

    column = prioC >> 3;
    row = prioC & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_smaPrio_setReady(prioC);

    column = prioA >> 3;
    row = prioA & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_smaPrio_setUnready(prioA);

    column = prioB >> 3;
    row = prioB & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_smaPrio_setUnready(prioB);

    column = prioC >> 3;
    row = prioC & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_smaPrio_setUnready(prioC);

    result = rkh_smaPrio_isReady();
    TEST_ASSERT_EQUAL(0, result);
}

TEST(prio, Fails_InvalidActiveObjectOnSet)
{
    rui8_t prio = RKH_CFG_FWK_MAX_SMA;

    rkh_assert_Expect("rkhsma_prio", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    rkh_smaPrio_setReady(prio);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
