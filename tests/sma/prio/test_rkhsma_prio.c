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
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkhsma_prio.h"
#include "Mock_rkhfwk_bittbl.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(prio);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(prio)
{
    rkh_smaPrio_init();
}

TEST_TEAR_DOWN(prio)
{
}

/**
 *  \addtogroup test_prio for test priority group
 *  @{
 *  \name Test cases of priority mechanism group
 *  @{ 
 */
TEST(prio, ClearAfterInit)
{
    rbool_t result;

    result = rkh_smaPrio_isNotReady();
    TEST_ASSERT_EQUAL(1, result);
}

TEST(prio, SetOneActiveObjectReadyToRun)
{
    rbool_t result;
    rui8_t prio = 1, resultPrio;

    rkh_bittbl_getBitMask_ExpectAndReturn(prio >> 3, 1);
    rkh_bittbl_getBitMask_ExpectAndReturn(prio & 7, 2);

    rkh_smaPrio_setReady(prio);
    result = rkh_smaPrio_isNotReady();
    TEST_ASSERT_EQUAL(0, result);

    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(1, 0);
    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(2, 1);
    resultPrio = rkh_smaPrio_findHighest();
    TEST_ASSERT_EQUAL(prio, resultPrio);
}

TEST(prio, SetMultipleActiveObjectReadyToRun)
{
    rbool_t result;
    rui8_t prioA = 1, prioB = 15, resultPrio;

    rkh_bittbl_getBitMask_ExpectAndReturn(prioA >> 3, 1);
    rkh_bittbl_getBitMask_ExpectAndReturn(prioA & 7, 2);
    rkh_smaPrio_setReady(prioA);

    rkh_bittbl_getBitMask_ExpectAndReturn(prioB >> 3, 2);
    rkh_bittbl_getBitMask_ExpectAndReturn(prioB & 7, 0x80);
    rkh_smaPrio_setReady(prioB);

    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(3, 0);
    rkh_bittbl_getLeastBitSetPos_ExpectAndReturn(2, 1);
    resultPrio = rkh_smaPrio_findHighest();
    TEST_ASSERT_EQUAL(prioA, resultPrio);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
