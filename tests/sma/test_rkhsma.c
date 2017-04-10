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
 *  \file       test_rkhsma.c
 *  \ingroup    test_sma
 *  \brief      Unit test for sma module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_sma SMA
 *  @{
 *  \brief      Unit test for sma module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.05  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkhsma.h"
#include "Mockrkhport.h"
#include "Mockrkhtrc.h"
#include "Mockrkh.h"
#include "Mockrkhrq.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(sma);

/* ---------------------------- Local variables ---------------------------- */
static RKHROM RKH_ROM_T base = {0, 0, "receiver"};
static RKH_SMA_T receiver;
const RKH_TRC_FIL_T fsma = {0, NULL};   /* Fake global variable of trace */
                                        /* module (using for mocking) */

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ============================= SMA test group ============================ */
TEST_SETUP(sma)
{
    receiver.sm.romrkh = &base;
}

TEST_TEAR_DOWN(sma)
{
}

/**
 *  \addtogroup test_rkhsma Active object (SMA) test group
 *  @{
 *  \name Test cases of active object test group
 *  @{ 
 */
TEST(sma, Register)
{
    rkh_enter_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_REG, RKH_FALSE);
    rkh_exit_critical_Expect();

    rkh_sma_register(&receiver);
    TEST_ASSERT_EQUAL(&receiver, rkh_sptbl[receiver.sm.romrkh->prio]);
}

TEST(sma, UnRegister)
{
    rkh_enter_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_UNREG, RKH_FALSE);
    rkh_exit_critical_Expect();

    rkh_sma_unregister(&receiver);
    TEST_ASSERT_EQUAL((RKH_SMA_T *)0, rkh_sptbl[receiver.sm.romrkh->prio]);
}

TEST(sma, Constructor)
{
    rkh_sm_ctor_Expect(&(receiver.sm));

    rkh_sma_ctor(&receiver, (const RKHSmaVtbl *)0);
}

TEST(sma, TerminateOneRegisteredAO)
{
    rkh_enter_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_REG, RKH_FALSE);
    rkh_exit_critical_Expect();

    rkh_sma_register(&receiver);

    rkh_enter_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_UNREG, RKH_FALSE);
    rkh_exit_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_TERM, RKH_FALSE);

    rkh_sma_terminate(&receiver);

    TEST_ASSERT_EQUAL((RKH_SMA_T *)0, rkh_sptbl[receiver.sm.romrkh->prio]);
}

TEST(sma, ActivateOneAO)
{
    char *buff;

    rkh_rq_init_Expect(&receiver.equeue, &buff, 16, &receiver);

    rkh_enter_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_REG, RKH_FALSE);
    rkh_exit_critical_Expect();

    rkh_sm_init_Expect((RKH_SM_T *)&receiver);

    rkh_enter_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_ACT, RKH_FALSE);
    rkh_exit_critical_Expect();

    rkh_sma_activate(&receiver, (RKH_EVT_T **)&buff, 16, NULL, 0);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
