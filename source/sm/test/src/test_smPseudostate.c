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
 *  \file       test_smPseudostate.c
 *  \ingroup    test_sm
 *  \brief      Unit test for state machine module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_sm State Machine
 *  @{
 *  \brief      Unit test for state machine module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.12.15  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */

#include "unity_fixture.h"
#include "unitrazer.h"
#include "rkhfwk_dynevt.h"
#include "common.h"
#include "smPseudoTest.h"
#include "smPseudoTestAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
static RKH_STATIC_EVENT(evA, A);
static RKH_STATIC_EVENT(evB, B);
static RKH_STATIC_EVENT(evC, C);
static RKH_STATIC_EVENT(evD, D);
static RKH_STATIC_EVENT(evE, E);
static RKH_STATIC_EVENT(evF, F);
static RKH_STATIC_EVENT(evG, G);
static RKH_STATIC_EVENT(evH, H);
static RKH_STATIC_EVENT(evI, I);
static RKH_STATIC_EVENT(evTerminate, TERMINATE);

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(pseudostate);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
void
loadStateMachineSymbols(void)
{
    RKH_TR_FWK_AO(smPseudoTest);
    RKH_TR_FWK_STATE(smPseudoTest, &smPT_waiting);
    RKH_TR_FWK_STATE(smPseudoTest, &smPT_s0);
    RKH_TR_FWK_STATE(smPseudoTest, &smPT_s1);
    RKH_TR_FWK_STATE(smPseudoTest, &smPT_s11);
    RKH_TR_FWK_STATE(smPseudoTest, &smPT_s12);
    RKH_TR_FWK_STATE(smPseudoTest, &smPT_s1Hist);
    RKH_TR_FWK_STATE(smPseudoTest, &smPT_s121);
    RKH_TR_FWK_STATE(smPseudoTest, &smPT_s122);
    RKH_TR_FWK_STATE(smPseudoTest, &smPT_s12Hist);
    RKH_TR_FWK_STATE(smPseudoTest, &smPT_s2);
    RKH_TR_FWK_STATE(smPseudoTest, &smPT_s21);
    RKH_TR_FWK_STATE(smPseudoTest, &smPT_s22);
    RKH_TR_FWK_STATE(smPseudoTest, &smPT_s2Hist);
    RKH_TR_FWK_SIG(A);
    RKH_TR_FWK_SIG(B);
    RKH_TR_FWK_SIG(C);
    RKH_TR_FWK_SIG(D);
    RKH_TR_FWK_SIG(E);
}

static
void
setRKHTraceFilters(void)
{
    RKH_FILTER_OFF_ALL_SIGNALS();
    RKH_FILTER_OFF_GROUP_ALL_EVENTS(RKH_TG_SM);
    RKH_FILTER_OFF_SMA(smPseudoTest);
    RKH_FILTER_OFF_EVENT(RKH_TE_FWK_ASSERT);
}

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(pseudostate)
{
    sm_init();
    rkh_sm_clear_history(&smPT_s1Hist);
    rkh_sm_clear_history(&smPT_s12Hist);
    rkh_sm_clear_history(&smPT_s2Hist);

    loadStateMachineSymbols();
    setRKHTraceFilters();
}

TEST_TEAR_DOWN(pseudostate)
{
    sm_verify(); /* Makes sure there are no unused expectations, if */
                 /* there are, this function causes the test to fail. */
    sm_cleanup();
}

/**
 *  \addtogroup test_smPseudostate Pseudostate test group
 *  @{
 *  \name Test cases of pseudostate group
 *  @{ 
 */

TEST(pseudostate, firstStateAfterInit)
{
    UtrzProcessOut *p;

	sm_init_expect(RKH_STATE_CAST(&smPT_waiting));
	sm_enstate_expect(RKH_STATE_CAST(&smPT_waiting));

    rkh_sm_init((RKH_SM_T *)smPseudoTest);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostate, trnToEmptyShallowHistoryWithoutDefaultTrn)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&smPT_s1Hist), RKH_STATE_CAST(&smPT_s1), 
        RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&smPT_s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
       RKH_STATE_CAST(&smPT_s1), RKH_STATE_CAST(&smPT_s11), RKH_STATE_CAST(0)
    };

    setProfile(smPseudoTest, RKH_STATE_CAST(&smPT_s0), 
               RKH_STATE_CAST(&smPT_s0), targetStates, 
               entryStates, exitStates, 
               RKH_STATE_CAST(&smPT_s11), 0, TRN_NOT_INTERNAL, 1, &evB,
               RKH_STATE_CAST(&smPT_s0));

    rkh_sm_dispatch((RKH_SM_T *)smPseudoTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostate, trnToLoadedShallowHistoryWithoutDefaultTrn)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&smPT_s1Hist), RKH_STATE_CAST(&smPT_s12), 
        RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&smPT_s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
       RKH_STATE_CAST(&smPT_s1), RKH_STATE_CAST(&smPT_s12), 
       RKH_STATE_CAST(&smPT_s121), RKH_STATE_CAST(0)
    };

    setProfile(smPseudoTest, RKH_STATE_CAST(&smPT_s0), 
               RKH_STATE_CAST(&smPT_s0), targetStates, 
               entryStates, exitStates, 
               RKH_STATE_CAST(&smPT_s121), 0, TRN_NOT_INTERNAL, 1, &evB,
               RKH_STATE_CAST(&smPT_s0));

    setHistory(&smPT_s1Hist, RKH_STATE_CAST(&smPT_s12));
    rkh_sm_dispatch((RKH_SM_T *)smPseudoTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostate, exitFromCompositeWithLoadedShallowHistory)
{
    UtrzProcessOut *p;
    const RKH_ST_T *state;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&smPT_s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
       RKH_STATE_CAST(&smPT_s121), RKH_STATE_CAST(&smPT_s12), 
       RKH_STATE_CAST(&smPT_s1), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
       RKH_STATE_CAST(&smPT_s0), RKH_STATE_CAST(0)
    };

    setProfile(smPseudoTest, RKH_STATE_CAST(&smPT_s121), 
               RKH_STATE_CAST(&smPT_s1), targetStates, 
               entryStates, exitStates, 
               RKH_STATE_CAST(&smPT_s0), 0, TRN_NOT_INTERNAL, 1, &evA,
               RKH_STATE_CAST(&smPT_s121));

    rkh_sm_dispatch((RKH_SM_T *)smPseudoTest, &evA);
    state = getHistory(&smPT_s1Hist);
    TEST_ASSERT_EQUAL_PTR(RKH_STATE_CAST(&smPT_s12), state);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostate, trnToEmptyDeepHistoryWithoutDefaultTrn)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&smPT_s12Hist), RKH_STATE_CAST(&smPT_s12), 
        RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&smPT_s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
       RKH_STATE_CAST(&smPT_s1), RKH_STATE_CAST(&smPT_s12), 
       RKH_STATE_CAST(&smPT_s121), RKH_STATE_CAST(0)
    };

    setProfile(smPseudoTest, RKH_STATE_CAST(&smPT_s0), 
               RKH_STATE_CAST(&smPT_s0), targetStates, 
               entryStates, exitStates, 
               RKH_STATE_CAST(&smPT_s121), 0, TRN_NOT_INTERNAL, 1, &evC,
               RKH_STATE_CAST(&smPT_s0));

    rkh_sm_dispatch((RKH_SM_T *)smPseudoTest, &evC);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostate, trnToLoadedDeepHistoryWithoutDefaultTrn)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&smPT_s12Hist), RKH_STATE_CAST(&smPT_s122), 
        RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&smPT_s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
       RKH_STATE_CAST(&smPT_s1), RKH_STATE_CAST(&smPT_s12), 
       RKH_STATE_CAST(&smPT_s122), RKH_STATE_CAST(0)
    };

    setProfile(smPseudoTest, RKH_STATE_CAST(&smPT_s0), 
               RKH_STATE_CAST(&smPT_s0), targetStates, 
               entryStates, exitStates, 
               RKH_STATE_CAST(&smPT_s122), 0, TRN_NOT_INTERNAL, 1, &evC,
               RKH_STATE_CAST(&smPT_s0));

    setHistory(&smPT_s12Hist, RKH_STATE_CAST(&smPT_s122));
    rkh_sm_dispatch((RKH_SM_T *)smPseudoTest, &evC);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostate, exitFromCompositeWithLoadedDeepHistory)
{
    UtrzProcessOut *p;
    const RKH_ST_T *state;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&smPT_s122), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
       RKH_STATE_CAST(&smPT_s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
       RKH_STATE_CAST(&smPT_s1), RKH_STATE_CAST(&smPT_s12), 
       RKH_STATE_CAST(&smPT_s122), RKH_STATE_CAST(0)
    };

    setProfile(smPseudoTest, RKH_STATE_CAST(&smPT_s0), 
               RKH_STATE_CAST(&smPT_s0), targetStates, 
               entryStates, exitStates, 
               RKH_STATE_CAST(&smPT_s122), 0, TRN_NOT_INTERNAL, 1, &evD,
               RKH_STATE_CAST(&smPT_s0));

    rkh_sm_dispatch((RKH_SM_T *)smPseudoTest, &evD);
    state = getHistory(&smPT_s12Hist);
    TEST_ASSERT_EQUAL_PTR(RKH_STATE_CAST(&smPT_s122), state);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostate, trnToEmptyShallowHistoryWithDefaultTrn)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&smPT_s2Hist), RKH_STATE_CAST(&smPT_s22), 
        RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&smPT_s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
       RKH_STATE_CAST(&smPT_s2), RKH_STATE_CAST(&smPT_s22), RKH_STATE_CAST(0)
    };

    setProfile(smPseudoTest, RKH_STATE_CAST(&smPT_s0), 
               RKH_STATE_CAST(&smPT_s0), targetStates, 
               entryStates, exitStates, 
               RKH_STATE_CAST(&smPT_s22), 1, TRN_NOT_INTERNAL, 1, &evE,
               RKH_STATE_CAST(&smPT_s0));

    rkh_sm_dispatch((RKH_SM_T *)smPseudoTest, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostate, trnToLoadedShallowHistoryWithDefaultTrn)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&smPT_s2Hist), RKH_STATE_CAST(&smPT_s21), 
        RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&smPT_s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
       RKH_STATE_CAST(&smPT_s2), RKH_STATE_CAST(&smPT_s21), RKH_STATE_CAST(0)
    };

    setProfile(smPseudoTest, RKH_STATE_CAST(&smPT_s0), 
               RKH_STATE_CAST(&smPT_s0), targetStates, 
               entryStates, exitStates, 
               RKH_STATE_CAST(&smPT_s21), 0, TRN_NOT_INTERNAL, 1, &evE,
               RKH_STATE_CAST(&smPT_s0));

    setHistory(&smPT_s2Hist, RKH_STATE_CAST(&smPT_s21));
    rkh_sm_dispatch((RKH_SM_T *)smPseudoTest, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
