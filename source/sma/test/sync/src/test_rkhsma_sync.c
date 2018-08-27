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
 *  \file       test_rkhsma_sync.c
 *  \ingroup    test_sma
 *  \brief      Unit test for synchronous mechanism of sma module.
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
#include "rkhsma_sync.h"
#include "Mock_rkhqueue.h"
#include "Mock_rkhassert.h"
#include "Mock_rkhsma_prio.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(sync);

/* ---------------------------- Local variables ---------------------------- */
static RKHROM RKH_ROM_T base = {0, 0, "ao"};
static RKH_SMA_T ao;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void 
MockAssertCallback(const char* const file, int line, int cmock_num_calls)
{
    TEST_PASS();
}

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(sync)
{
    Mock_rkhassert_Init();
    Mock_rkhsma_prio_Init();
    ao.sm.romrkh = &base;
}

TEST_TEAR_DOWN(sync)
{
    Mock_rkhassert_Verify();
    Mock_rkhsma_prio_Verify();
    Mock_rkhassert_Destroy();
    Mock_rkhsma_prio_Destroy();
}

/**
 *  \addtogroup test_sync Test cases of synchronous mechanism group
 *  @{
 *  \name Test cases of synchronous mechanism group
 *  @{ 
 */
TEST(sync, BlockActiveObject)
{
    ao.equeue.qty = 1;
    rkh_sma_block(&ao);
}

TEST(sync, Fails_TriesBlockActiveObjectWithEmptyQueue)
{
    rkh_assert_Expect("rkhsma_sync", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);
    ao.equeue.qty = 0;

    rkh_sma_block(&ao);
}

TEST(sync, SetActiveObjectReady)
{
    rkh_smaPrio_setReady_Expect(ao.sm.romrkh->prio);
    rkh_sma_setReady(&ao);
}

TEST(sync, SetActiveObjectUnready)
{
    rkh_smaPrio_setUnready_Expect(ao.sm.romrkh->prio);
    rkh_sma_setUnready(&ao);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
