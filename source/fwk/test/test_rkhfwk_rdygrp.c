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
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       test_rkhfwk_rdygrp.c
 *  \ingroup    test_fwk
 *  \brief      Unit test for AO ready of fwk module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_fwk Framework
 *  @{
 *  \brief      Unit test for framework module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.08.07  LeFr  v3.1.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity.h"
#include "rkhfwk_rdygrp.h"
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
typedef struct DerivedRdyCbArg DerivedRdyCbArg;
struct DerivedRdyCbArg
{
    RdyCbArg base;
    int cnt;
};

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKHRdyGrp rdyTbl;
static DerivedRdyCbArg rdyCbArg;
static rui8_t prio[] = {0, 3, 9, 17, 27, 33, 41, 55, 63};

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void 
MockAssertCallback(const char* const file, int line, int cmock_num_calls)
{
    TEST_PASS();
}

static void
rdyCb(RdyCbArg *arg)
{
    TEST_ASSERT_EQUAL(prio[((DerivedRdyCbArg *)arg)->cnt++], arg->aoRdyPrio);
}

/* ---------------------------- Global functions --------------------------- */
void
setUp(void)
{
    Mock_rkhfwk_bittbl_Init();
    Mock_rkhassert_Init();
    rkh_rdygrp_init(&rdyTbl);
}

void
tearDown(void)
{
    Mock_rkhfwk_bittbl_Verify();
    Mock_rkhfwk_bittbl_Destroy();
    Mock_rkhassert_Verify();
    Mock_rkhassert_Destroy();
}

/**
 *  \addtogroup test_rdygrp Test cases of AO ready group
 *  @{
 *  \name Test cases of AO ready group
 *  @{ 
 */
void
test_ClearAfterInit(void)
{
    rbool_t result;

    result = rkh_rdygrp_isReady(&rdyTbl);
    TEST_ASSERT_EQUAL(0, result);
}

void
test_SetOneActiveObjectReady(void)
{
    rbool_t result;
    rui8_t prio = 1, resultPrio, column, row;

    column = prio >> 3;
    row = prio & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);

    rkh_rdygrp_setReady(&rdyTbl, prio);
    result = rkh_rdygrp_isReady(&rdyTbl);
    TEST_ASSERT_EQUAL(1, result);

    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(1, leastBitSetTbl[1]);
    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(2, leastBitSetTbl[2]);
    resultPrio = rkh_rdygrp_findHighest(&rdyTbl);
    TEST_ASSERT_EQUAL(prio, resultPrio);
}

void
test_SetMultipleActiveObjectsReady(void)
{
    rui8_t prioA = 1, prioC = 0, prioB = 15, resultPrio, column, row;

    column = prioA >> 3;
    row = prioA & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_rdygrp_setReady(&rdyTbl, prioA);

    column = prioB >> 3;
    row = prioB & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_rdygrp_setReady(&rdyTbl, prioB);

    column = prioC >> 3;
    row = prioC & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_rdygrp_setReady(&rdyTbl, prioC);

    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(3, leastBitSetTbl[3]);
    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(3, leastBitSetTbl[3]);
    resultPrio = rkh_rdygrp_findHighest(&rdyTbl);
    TEST_ASSERT_EQUAL(prioC, resultPrio);
}

void
test_SetOneActiveObjectUnready(void)
{
    rbool_t result;
    rui8_t prio = 1, resultPrio, column, row;

    column = prio >> 3;
    row = prio & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);

    rkh_rdygrp_setReady(&rdyTbl, prio);

    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(1, leastBitSetTbl[1]);
    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(2, leastBitSetTbl[2]);
    resultPrio = rkh_rdygrp_findHighest(&rdyTbl);
    TEST_ASSERT_EQUAL(prio, resultPrio);

    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_rdygrp_setUnready(&rdyTbl, prio);
    result = rkh_rdygrp_isReady(&rdyTbl);
    TEST_ASSERT_EQUAL(0, result);
}

void
test_SetMultipleActiveObjectsUnready(void)
{
    rbool_t result;
    rui8_t prioA = 1, prioC = 0, prioB = 15, column, row;

    column = prioA >> 3;
    row = prioA & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_rdygrp_setReady(&rdyTbl, prioA);

    column = prioB >> 3;
    row = prioB & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_rdygrp_setReady(&rdyTbl, prioB);

    column = prioC >> 3;
    row = prioC & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_rdygrp_setReady(&rdyTbl, prioC);

    column = prioA >> 3;
    row = prioA & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_rdygrp_setUnready(&rdyTbl, prioA);

    column = prioB >> 3;
    row = prioB & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_rdygrp_setUnready(&rdyTbl, prioB);

    column = prioC >> 3;
    row = prioC & 7;
    rkh_bittbl_getBitMask_ExpectAndReturn(row, bitMaskTbl[row]);
    rkh_bittbl_getBitMask_ExpectAndReturn(column, bitMaskTbl[column]);
    rkh_rdygrp_setUnready(&rdyTbl, prioC);

    result = rkh_rdygrp_isReady(&rdyTbl);
    TEST_ASSERT_EQUAL(0, result);
}

void
test_Fails_InvalidActiveObjectOnSet(void)
{
    rui8_t prio = RKH_CFG_FWK_MAX_SMA;

    rkh_assert_Expect("rkhfwk_rdygrp", 0);
    rkh_assert_IgnoreArg_file();
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    rkh_rdygrp_setReady(&rdyTbl, prio);
}

void
test_TraverseWithOneReadyActiveObject(void)
{
    rui8_t nRdyAo, resultNRdyAo;

    rkh_bittbl_getBitMask_IgnoreAndReturn(bitMaskTbl[prio[0] >> 3]);
    rkh_bittbl_getBitMask_IgnoreAndReturn(bitMaskTbl[prio[0] & 7]);

    rdyCbArg.cnt = 0;
    nRdyAo = 1;
    rkh_rdygrp_setReady(&rdyTbl, prio[0]);
    resultNRdyAo = rkh_rdygrp_traverse(&rdyTbl, rdyCb, (RdyCbArg *)&rdyCbArg);
    TEST_ASSERT_EQUAL(nRdyAo, resultNRdyAo);
    TEST_ASSERT_EQUAL(nRdyAo, rdyCbArg.cnt);
}

void
test_TraverseWithMultipleReadyActiveObject(void)
{
    rui8_t nRdyAo, resultNRdyAo, ix;

    nRdyAo = 9;
    for (ix = 0; ix < nRdyAo; ++ix)
    {
        rkh_bittbl_getBitMask_IgnoreAndReturn(bitMaskTbl[prio[ix] >> 3]);
        rkh_bittbl_getBitMask_IgnoreAndReturn(bitMaskTbl[prio[ix] & 7]);
        rkh_rdygrp_setReady(&rdyTbl, prio[ix]);
    }

    rdyCbArg.cnt = 0;
    resultNRdyAo = rkh_rdygrp_traverse(&rdyTbl, rdyCb, (RdyCbArg *)&rdyCbArg);
    TEST_ASSERT_EQUAL(nRdyAo, resultNRdyAo);
    TEST_ASSERT_EQUAL(nRdyAo, rdyCbArg.cnt);
}

void
test_TraverseWithWithoutReadyActiveObject(void)
{
    rui8_t nRdyAo, resultNRdyAo;

    rdyCbArg.cnt = 0;
    nRdyAo = 0;
    resultNRdyAo = rkh_rdygrp_traverse(&rdyTbl, rdyCb, (RdyCbArg *)&rdyCbArg);
    TEST_ASSERT_EQUAL(nRdyAo, resultNRdyAo);
    TEST_ASSERT_EQUAL(nRdyAo, rdyCbArg.cnt);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
