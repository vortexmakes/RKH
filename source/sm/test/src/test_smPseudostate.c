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
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
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
static const RKH_ST_T *targetStates[16], *exitStates[16], *entryStates[16];

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
    sm_ntrnact_ignore();
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
    sm_trn_expect(RKH_STATE_CAST(&smPT_waiting), 
                                 RKH_STATE_CAST(&smPT_waiting));
    sm_tsState_expect(RKH_STATE_CAST(&smPT_waiting));
    sm_enstate_expect(RKH_STATE_CAST(&smPT_waiting));
    sm_nenex_expect(1, 0);
    sm_state_expect(RKH_STATE_CAST(&smPT_waiting));
    sm_evtProc_expect();

    rkh_sm_init((RKH_SM_T *)smPseudoTest);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostate, trnToEmptyShallowHistoryWithoutDefaultTrn)
{
    UtrzProcessOut *p;
    int nExSt, nEnSt;
    RKH_EVT_T event;

    nEnSt = 2;
    nExSt = 1;
    event = evB;
    expInitSm((RKH_SM_T *)smPseudoTest, RKH_STATE_CAST(&smPT_waiting));
	sm_dch_expect(event.e, RKH_STATE_CAST(&smPT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smPT_s0), RKH_STATE_CAST(&smPT_s1Hist));
    sm_tsState_expect(RKH_STATE_CAST(&smPT_s1Hist));
    sm_tsState_expect(RKH_STATE_CAST(&smPT_s1));
    sm_exstate_expect(RKH_STATE_CAST(&smPT_s0));
    sm_enstate_expect(RKH_STATE_CAST(&smPT_s1));
    sm_tsState_expect(RKH_STATE_CAST(&smPT_s11));
    sm_enstate_expect(RKH_STATE_CAST(&smPT_s11));
    sm_nenex_expect(nEnSt, nExSt);
    sm_state_expect(RKH_STATE_CAST(&smPT_s11));
	sm_evtProc_expect();

    rkh_sm_init((RKH_SM_T *)smPseudoTest);
    setState((RKH_SM_T *)smPseudoTest, RKH_STATE_CAST(&smPT_s0));
    rkh_sm_dispatch((RKH_SM_T *)smPseudoTest, &event);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostate, trnToLoadedShallowHistoryWithoutDefaultTrn)
{
    UtrzProcessOut *p;
    int nExSt, nEnSt;
    RKH_EVT_T event;

    nEnSt = 3;
    nExSt = 1;
    event = evB;
    expInitSm((RKH_SM_T *)smPseudoTest, RKH_STATE_CAST(&smPT_waiting));
	sm_dch_expect(event.e, RKH_STATE_CAST(&smPT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smPT_s0), RKH_STATE_CAST(&smPT_s1Hist));
    sm_tsState_expect(RKH_STATE_CAST(&smPT_s1Hist));
    sm_tsState_expect(RKH_STATE_CAST(&smPT_s12));
    sm_exstate_expect(RKH_STATE_CAST(&smPT_s0));
    sm_enstate_expect(RKH_STATE_CAST(&smPT_s1));
    sm_enstate_expect(RKH_STATE_CAST(&smPT_s12));
    sm_tsState_expect(RKH_STATE_CAST(&smPT_s121));
    sm_enstate_expect(RKH_STATE_CAST(&smPT_s121));
    sm_nenex_expect(nEnSt, nExSt);
    sm_state_expect(RKH_STATE_CAST(&smPT_s121));
	sm_evtProc_expect();

    rkh_sm_init((RKH_SM_T *)smPseudoTest);
    setState((RKH_SM_T *)smPseudoTest, RKH_STATE_CAST(&smPT_s0));
    setHistory(&smPT_s1Hist, RKH_STATE_CAST(&smPT_s12));
    rkh_sm_dispatch((RKH_SM_T *)smPseudoTest, &event);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostate, exitFromCompositeWithLoadedShallowHistory)
{
    UtrzProcessOut *p;
    const RKH_ST_T *state;

    stateList_create(targetStates, 1, &smPT_s0);
    stateList_create(exitStates, 3, &smPT_s121, &smPT_s12, &smPT_s1);
    stateList_create(entryStates, 1, &smPT_s0);
    setProfile(smPseudoTest, RKH_STATE_CAST(&smPT_waiting), 
               RKH_STATE_CAST(&smPT_s121), 
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
    int nExSt, nEnSt;
    RKH_EVT_T event;

    nEnSt = 3;
    nExSt = 1;
    event = evC;
    expInitSm((RKH_SM_T *)smPseudoTest, RKH_STATE_CAST(&smPT_waiting));
	sm_dch_expect(event.e, RKH_STATE_CAST(&smPT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smPT_s0), RKH_STATE_CAST(&smPT_s12Hist));
    sm_tsState_expect(RKH_STATE_CAST(&smPT_s12Hist));
    sm_tsState_expect(RKH_STATE_CAST(&smPT_s12));
    sm_exstate_expect(RKH_STATE_CAST(&smPT_s0));
    sm_enstate_expect(RKH_STATE_CAST(&smPT_s1));
    sm_enstate_expect(RKH_STATE_CAST(&smPT_s12));
    sm_tsState_expect(RKH_STATE_CAST(&smPT_s121));
    sm_enstate_expect(RKH_STATE_CAST(&smPT_s121));
    sm_nenex_expect(nEnSt, nExSt);
    sm_state_expect(RKH_STATE_CAST(&smPT_s121));
	sm_evtProc_expect();

    rkh_sm_init((RKH_SM_T *)smPseudoTest);
    setState((RKH_SM_T *)smPseudoTest, RKH_STATE_CAST(&smPT_s0));
    rkh_sm_dispatch((RKH_SM_T *)smPseudoTest, &event);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostate, trnToLoadedDeepHistoryWithoutDefaultTrn)
{
    UtrzProcessOut *p;

    stateList_create(targetStates, 2, &smPT_s12Hist, &smPT_s122);
    stateList_create(exitStates, 1, &smPT_s0);
    stateList_create(entryStates, 3, &smPT_s1, &smPT_s12, &smPT_s122);
    setProfile(smPseudoTest, RKH_STATE_CAST(&smPT_waiting), 
               RKH_STATE_CAST(&smPT_s0), 
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

    stateList_create(targetStates, 1, &smPT_s122);
    stateList_create(exitStates, 1, &smPT_s0);
    stateList_create(entryStates, 3, &smPT_s1, &smPT_s12, &smPT_s122);
    setProfile(smPseudoTest, RKH_STATE_CAST(&smPT_waiting), 
               RKH_STATE_CAST(&smPT_s0), 
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

    stateList_create(targetStates, 2, &smPT_s2Hist, &smPT_s22);
    stateList_create(exitStates, 1, &smPT_s0);
    stateList_create(entryStates, 2, &smPT_s2, &smPT_s22);
    setProfile(smPseudoTest, RKH_STATE_CAST(&smPT_waiting), 
               RKH_STATE_CAST(&smPT_s0), 
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

    stateList_create(targetStates, 2, &smPT_s2Hist, &smPT_s21);
    stateList_create(exitStates, 1, &smPT_s0);
    stateList_create(entryStates, 2, &smPT_s2, &smPT_s21);
    setProfile(smPseudoTest, RKH_STATE_CAST(&smPT_waiting), 
               RKH_STATE_CAST(&smPT_s0), 
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
