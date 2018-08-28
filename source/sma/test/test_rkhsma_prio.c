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
#include "unity.h"
#include "rkhsma_prio.h"
#include "Mock_rkhfwk_rdygrp.h"
#include "Mock_rkhassert.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
int GlobalExpectCount;
int GlobalVerifyOrder;
char *GlobalOrderError;

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void 
MockAssertCallback(const char* const file, int line, int cmock_num_calls)
{
    TEST_PASS();
}

/* ---------------------------- Global functions --------------------------- */
void
setUp(void)
{
    Mock_rkhfwk_rdygrp_Init();
}

void
tearDown(void)
{
    Mock_rkhfwk_rdygrp_Verify();
    Mock_rkhfwk_rdygrp_Destroy();
}

/**
 *  \addtogroup test_prio Test cases of priority mechanism group
 *  @{
 *  \name Test cases of priority mechanism group
 *  @{ 
 */
void
test_ClearAfterInit(void)
{
    rbool_t result;

    rkh_rdygrp_init_Expect(0);
    rkh_rdygrp_init_IgnoreArg_me();
    rkh_rdygrp_isReady_ExpectAndReturn(0, 0);
    rkh_rdygrp_isReady_IgnoreArg_me();
    rkh_rdygrp_isReady_ExpectAndReturn(0, 0);
    rkh_rdygrp_isReady_IgnoreArg_me();

    rkh_smaPrio_init();
    result = rkh_smaPrio_isReady();
    TEST_ASSERT_EQUAL(0, result);
    result = rkh_smaPrio_isNotReady();
    TEST_ASSERT_EQUAL(1, result);
}

void
test_SetOneActiveObjectReadyToRun(void)
{
    rbool_t result;
    rui8_t prio = 1, resultPrio;

    rkh_rdygrp_init_Expect(0);
    rkh_rdygrp_init_IgnoreArg_me();
    rkh_rdygrp_setReady_Expect(0, prio);
    rkh_rdygrp_setReady_IgnoreArg_me();
    rkh_rdygrp_isReady_ExpectAndReturn(0, 1);
    rkh_rdygrp_isReady_IgnoreArg_me();
    rkh_rdygrp_findHighest_ExpectAndReturn(0, prio);
    rkh_rdygrp_findHighest_IgnoreArg_me();

    rkh_smaPrio_init();
    rkh_smaPrio_setReady(prio);
    result = rkh_smaPrio_isReady();
    TEST_ASSERT_EQUAL(1, result);

    resultPrio = rkh_smaPrio_findHighest();
    TEST_ASSERT_EQUAL(prio, resultPrio);
}

void
test_SetMultipleActiveObjectsReadyToRun(void)
{
    rui8_t prioA = 1, prioC = 0, prioB = 15, resultPrio;

    rkh_rdygrp_init_Expect(0);
    rkh_rdygrp_init_IgnoreArg_me();
    rkh_rdygrp_setReady_Expect(0, prioA);
    rkh_rdygrp_setReady_IgnoreArg_me();
    rkh_rdygrp_setReady_Expect(0, prioB);
    rkh_rdygrp_setReady_IgnoreArg_me();
    rkh_rdygrp_setReady_Expect(0, prioC);
    rkh_rdygrp_setReady_IgnoreArg_me();
    rkh_rdygrp_findHighest_ExpectAndReturn(0, prioC);
    rkh_rdygrp_findHighest_IgnoreArg_me();

    rkh_smaPrio_init();
    rkh_smaPrio_setReady(prioA);
    rkh_smaPrio_setReady(prioB);
    rkh_smaPrio_setReady(prioC);
    resultPrio = rkh_smaPrio_findHighest();

    TEST_ASSERT_EQUAL(prioC, resultPrio);
}

void
test_SetOneActiveObjectUnready(void)
{
    rbool_t result;
    rui8_t prio = 1, resultPrio;

    rkh_rdygrp_init_Expect(0);
    rkh_rdygrp_init_IgnoreArg_me();
    rkh_rdygrp_setReady_Expect(0, prio);
    rkh_rdygrp_setReady_IgnoreArg_me();
    rkh_rdygrp_findHighest_ExpectAndReturn(0, prio);
    rkh_rdygrp_findHighest_IgnoreArg_me();
    rkh_rdygrp_setUnready_Expect(0, prio);
    rkh_rdygrp_setUnready_IgnoreArg_me();
    rkh_rdygrp_isReady_ExpectAndReturn(0, 0);
    rkh_rdygrp_isReady_IgnoreArg_me();

    rkh_smaPrio_init();
    rkh_smaPrio_setReady(prio);
    resultPrio = rkh_smaPrio_findHighest();
    TEST_ASSERT_EQUAL(prio, resultPrio);

    rkh_smaPrio_setUnready(prio);
    result = rkh_smaPrio_isReady();
    TEST_ASSERT_EQUAL(0, result);
}

void
test_SetMultipleActiveObjectsUnready(void)
{
    rbool_t result;
    rui8_t prioA = 1, prioC = 0, prioB = 15;

    rkh_rdygrp_init_Expect(0);
    rkh_rdygrp_init_IgnoreArg_me();
    rkh_rdygrp_setReady_Expect(0, prioA);
    rkh_rdygrp_setReady_IgnoreArg_me();
    rkh_rdygrp_setReady_Expect(0, prioB);
    rkh_rdygrp_setReady_IgnoreArg_me();
    rkh_rdygrp_setReady_Expect(0, prioC);
    rkh_rdygrp_setReady_IgnoreArg_me();
    rkh_rdygrp_setUnready_Expect(0, prioA);
    rkh_rdygrp_setUnready_IgnoreArg_me();
    rkh_rdygrp_setUnready_Expect(0, prioB);
    rkh_rdygrp_setUnready_IgnoreArg_me();
    rkh_rdygrp_setUnready_Expect(0, prioC);
    rkh_rdygrp_setUnready_IgnoreArg_me();
    rkh_rdygrp_isReady_ExpectAndReturn(0, 0);
    rkh_rdygrp_isReady_IgnoreArg_me();

    rkh_smaPrio_init();
    rkh_smaPrio_setReady(prioA);
    rkh_smaPrio_setReady(prioB);
    rkh_smaPrio_setReady(prioC);
    rkh_smaPrio_setUnready(prioA);
    rkh_smaPrio_setUnready(prioB);
    rkh_smaPrio_setUnready(prioC);
    result = rkh_smaPrio_isReady();

    TEST_ASSERT_EQUAL(0, result);
}

void
test_Fails_InvalidActiveObjectOnSet(void)
{
    rui8_t prio = RKH_CFG_FWK_MAX_SMA;

    rkh_rdygrp_init_Expect(0);
    rkh_rdygrp_init_IgnoreArg_me();

    rkh_assert_Expect("rkhsma_prio", 0);
    rkh_assert_IgnoreArg_file();
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    rkh_smaPrio_init();
    rkh_smaPrio_setReady(prio);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
