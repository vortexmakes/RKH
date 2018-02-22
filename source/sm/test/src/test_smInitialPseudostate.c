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
 *  \file       test_smInitialPseudostate.c
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
 *  2018.02.16  LeFr  v1.0.00  ---
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
#include "smInitialPseudoTest.h"
#include "Mock_smInitialPseudoTestAct.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
static RKH_STATIC_EVENT(evA, A);
static RKH_STATIC_EVENT(evB, B);
static RKH_STATIC_EVENT(evC, C);
static RKH_STATIC_EVENT(evD, D);
static RKH_STATIC_EVENT(evE, E);
static RKH_STATIC_EVENT(evF, F);

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(InitPseudostate);

/* ---------------------------- Local variables ---------------------------- */
const RKH_ST_T *targetStates[16], *exitStates[16], *entryStates[16];

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
loadStateMachineSymbols(void)
{
    RKH_TR_FWK_AO(smInitialPseudoTest);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s0);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s1);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s11);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s12);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s2);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s21);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s211);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s3);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s31);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s32);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s33);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s331);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s5);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s51);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s511);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s52);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s6);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s61);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s62);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s1Hist);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s2Hist);
    RKH_TR_FWK_STATE(smInitialPseudoTest, &smIPT_s3Hist);
    RKH_TR_FWK_SIG(A);
    RKH_TR_FWK_SIG(B);
    RKH_TR_FWK_SIG(C);
    RKH_TR_FWK_SIG(D);
}

static void
setRKHTraceFilters(void)
{
    RKH_FILTER_OFF_ALL_SIGNALS();
    RKH_FILTER_OFF_GROUP_ALL_EVENTS(RKH_TG_SM);
    RKH_FILTER_OFF_SMA(smInitialPseudoTest);
    RKH_FILTER_OFF_EVENT(RKH_TE_FWK_ASSERT);
}

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(InitPseudostate)
{
    sm_init();
    sm_ntrnact_ignore();
    rkh_sm_clear_history(&smIPT_s1Hist);

    loadStateMachineSymbols();
    setRKHTraceFilters();
    Mock_smInitialPseudoTestAct_Init();
}

TEST_TEAR_DOWN(InitPseudostate)
{
    sm_verify(); /* Makes sure there are no unused expectations, if */
                 /* there are, this function causes the test to fail. */
    sm_cleanup();
    Mock_smInitialPseudoTestAct_Verify();
    Mock_smInitialPseudoTestAct_Destroy();
}

/**
 *  \addtogroup test_smInitialPseudostate Initial pseudostate test group
 *  @{
 *  \name Test cases of InitPseudostate group
 *  @{ 
 */

TEST(InitPseudostate, firstStateAfterInit)
{
    UtrzProcessOut *p;

    smIPT_init_Expect(smInitialPseudoTest);
    smIPT_nS0_Expect(smInitialPseudoTest);

	sm_init_expect(RKH_STATE_CAST(&smIPT_s0));
	sm_enstate_expect(RKH_STATE_CAST(&smIPT_s0));

    rkh_sm_init((RKH_SM_T *)smInitialPseudoTest);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToEmptyShHistoryToSimpleState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = smInitialPseudoTest;

    stateList_create(targetStates, 2, &smIPT_s1, &smIPT_s11);
    stateList_create(exitStates, 1, &smIPT_s0);
    stateList_create(entryStates, 2, &smIPT_s1, &smIPT_s11);

    smIPT_init_Expect(smInitialPseudoTest);
    smIPT_nS0_Expect(smInitialPseudoTest);
    smIPT_xS0_Expect(smInitialPseudoTest);
    smIPT_tr1_Expect(smInitialPseudoTest, &evA);
    smIPT_nS1_Expect(smInitialPseudoTest);
    smIPT_nS11_Expect(smInitialPseudoTest);

    /*setProfile(smInitialPseudoTest, RKH_STATE_CAST(&smIPT_s0), 
               RKH_STATE_CAST(&smIPT_s0), targetStates, 
               entryStates, exitStates, 
               RKH_STATE_CAST(&smIPT_s11), nTrnActs, TRN_NOT_INTERNAL, 1, &evA,
               RKH_STATE_CAST(&smIPT_s0));*/

#if 0
    sm_init_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    sm_enstate_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    /* Start transition */
	sm_dch_expect(evA.e, RKH_STATE_CAST(&smIPT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smIPT_s0), RKH_STATE_CAST(targetStates[0]));
    /*First step */
    sm_tsState_expect(RKH_STATE_CAST(targetStates[0]));
    sm_exstate_expect(RKH_STATE_CAST(exitStates[0]));
    sm_enstate_expect(RKH_STATE_CAST(entryStates[0]));
    /* Micro step */
    sm_tsState_expect(RKH_STATE_CAST(targetStates[1]));
    sm_enstate_expect(RKH_STATE_CAST(entryStates[1]));
    /* End transition */
    sm_nenex_expect(2, 1);
    sm_state_expect(RKH_STATE_CAST(entryStates[1]));
	sm_evtProc_expect();
#endif

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, 
                  targetStates, entryStates, exitStates, 
                  &evA);

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)smInitialPseudoTest, &evA);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToLoadedShHistory)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = smInitialPseudoTest;

    stateList_create(targetStates, 2, &smIPT_s1, &smIPT_s12);
    stateList_create(exitStates, 1, &smIPT_s0);
    stateList_create(entryStates, 2, &smIPT_s1, &smIPT_s12);

    smIPT_init_Expect(me);
    smIPT_nS0_Expect(me);
    smIPT_xS0_Expect(me);
    smIPT_nS1_Expect(me);
    smIPT_nS12_Expect(me);

    /*setProfile(me, RKH_STATE_CAST(&smIPT_s0), 
               RKH_STATE_CAST(&smIPT_s0), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&smIPT_s12), nTrnActs, TRN_NOT_INTERNAL, 1, &evA,
               RKH_STATE_CAST(&smIPT_s0));*/

    sm_init_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    sm_enstate_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    /* Start transition */
	sm_dch_expect(evA.e, RKH_STATE_CAST(&smIPT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smIPT_s0), RKH_STATE_CAST(targetStates[0]));
    /*First step */
    sm_tsState_expect(RKH_STATE_CAST(targetStates[0]));
    sm_exstate_expect(RKH_STATE_CAST(exitStates[0]));
    sm_enstate_expect(RKH_STATE_CAST(entryStates[0]));
    /* Micro step */
    sm_tsState_expect(RKH_STATE_CAST(targetStates[1]));
    sm_enstate_expect(RKH_STATE_CAST(entryStates[1]));
    /* End transition */
    sm_nenex_expect(2, 1);
    sm_state_expect(RKH_STATE_CAST(entryStates[1]));
	sm_evtProc_expect();

    rkh_sm_init((RKH_SM_T *)me);
    setHistory(&smIPT_s1Hist, RKH_STATE_CAST(&smIPT_s12));
    rkh_sm_dispatch((RKH_SM_T *)me, &evA);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToEmptyShHistoryToCmpState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = smInitialPseudoTest;

    stateList_create(targetStates, 2, &smIPT_s2, &smIPT_s21);
    stateList_create(exitStates, 1, &smIPT_s0);
    stateList_create(entryStates, 3, &smIPT_s2, &smIPT_s21, &smIPT_s211);

    smIPT_init_Expect(smInitialPseudoTest);
    smIPT_nS0_Expect(smInitialPseudoTest);
    smIPT_xS0_Expect(smInitialPseudoTest);
    smIPT_nS2_Expect(smInitialPseudoTest);
    smIPT_nS21_Expect(smInitialPseudoTest);
    smIPT_nS211_Expect(smInitialPseudoTest);

    trnStepExpect(me, &smIPT_s0, &smIPT_s0, 
                  targetStates, entryStates, exitStates, 
                  &evD);

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)smInitialPseudoTest, &evD);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToEmptyDeepHistoryToSimpleState)
{
    UtrzProcessOut *p;
    int nTrnActs;

    nTrnActs = 0;
    stateList_create(targetStates, 2, &smIPT_s3, &smIPT_s31);
    stateList_create(exitStates, 1, &smIPT_s0);
    stateList_create(entryStates, 2, &smIPT_s3, &smIPT_s31);

    smIPT_init_Expect(smInitialPseudoTest);
    smIPT_nS0_Expect(smInitialPseudoTest);
    smIPT_xS0_Expect(smInitialPseudoTest);
    smIPT_nS3_Expect(smInitialPseudoTest);
    smIPT_nS31_Expect(smInitialPseudoTest);

    setProfile(smInitialPseudoTest, RKH_STATE_CAST(&smIPT_s0), 
               RKH_STATE_CAST(&smIPT_s0), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&smIPT_s31), nTrnActs, TRN_NOT_INTERNAL, 1, &evB,
               RKH_STATE_CAST(&smIPT_s0));

    rkh_sm_dispatch((RKH_SM_T *)smInitialPseudoTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToLoadedDeepHistory)
{
    UtrzProcessOut *p;
    int nTrnActs;

    nTrnActs = 0;
    stateList_create(targetStates, 2, &smIPT_s3, &smIPT_s32);
    stateList_create(exitStates, 1, &smIPT_s0);
    stateList_create(entryStates, 2, &smIPT_s3, &smIPT_s32);

    smIPT_init_Expect(smInitialPseudoTest);
    smIPT_nS0_Expect(smInitialPseudoTest);
    smIPT_xS0_Expect(smInitialPseudoTest);
    smIPT_nS3_Expect(smInitialPseudoTest);
    smIPT_nS32_Expect(smInitialPseudoTest);

    setProfile(smInitialPseudoTest, RKH_STATE_CAST(&smIPT_s0), 
               RKH_STATE_CAST(&smIPT_s0), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&smIPT_s32), nTrnActs, TRN_NOT_INTERNAL, 1, &evB,
               RKH_STATE_CAST(&smIPT_s0));

    setHistory(&smIPT_s3Hist, RKH_STATE_CAST(&smIPT_s32));
    rkh_sm_dispatch((RKH_SM_T *)smInitialPseudoTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToLoadedDeepHistoryToNestedState)
{
    UtrzProcessOut *p;
    int nTrnActs;

    nTrnActs = 0;
    stateList_create(targetStates, 2, &smIPT_s3, &smIPT_s331);
    stateList_create(exitStates, 1, &smIPT_s0);
    stateList_create(entryStates, 3, &smIPT_s3, &smIPT_s33, &smIPT_s331);

    smIPT_init_Expect(smInitialPseudoTest);
    smIPT_nS0_Expect(smInitialPseudoTest);
    smIPT_xS0_Expect(smInitialPseudoTest);
    smIPT_nS3_Expect(smInitialPseudoTest);
    smIPT_nS33_Expect(smInitialPseudoTest);
    smIPT_nS331_Expect(smInitialPseudoTest);

    setProfile(smInitialPseudoTest, RKH_STATE_CAST(&smIPT_s0), 
               RKH_STATE_CAST(&smIPT_s0), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&smIPT_s331), nTrnActs, TRN_NOT_INTERNAL, 1, 
               &evB, RKH_STATE_CAST(&smIPT_s0));

    setHistory(&smIPT_s3Hist, RKH_STATE_CAST(&smIPT_s331));
    rkh_sm_dispatch((RKH_SM_T *)smInitialPseudoTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToEmptyShHistoryToNestedSimpleState)
{
    UtrzProcessOut *p;
    int nTrnActs;

    nTrnActs = 0;
    stateList_create(targetStates, 2, &smIPT_s4, &smIPT_s411);
    stateList_create(exitStates, 1, &smIPT_s0);
    stateList_create(entryStates, 3, &smIPT_s4, &smIPT_s41, &smIPT_s411);

    smIPT_init_Expect(smInitialPseudoTest);
    smIPT_nS0_Expect(smInitialPseudoTest);
    smIPT_xS0_Expect(smInitialPseudoTest);
    smIPT_nS4_Expect(smInitialPseudoTest);
    smIPT_nS41_Expect(smInitialPseudoTest);
    smIPT_nS411_Expect(smInitialPseudoTest);

    setProfile(smInitialPseudoTest, RKH_STATE_CAST(&smIPT_s0), 
               RKH_STATE_CAST(&smIPT_s0), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&smIPT_s411), nTrnActs, TRN_NOT_INTERNAL, 1, 
               &evC, RKH_STATE_CAST(&smIPT_s0));

    rkh_sm_dispatch((RKH_SM_T *)smInitialPseudoTest, &evC);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToBranchToSimpleState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = RKH_CAST(SmInitialPseudoTest, 
                                       smInitialPseudoTest);

    /* Expect call actions */
    smIPT_init_Expect(me);
    smIPT_nS0_Expect(me);
    smIPT_isC1_ExpectAndReturn(me, &evE, RKH_TRUE);
    smIPT_xS0_Expect(me);
    smIPT_nS5_Expect(me);
    smIPT_nS52_Expect(me);
    /* Expect init state machine */
    sm_init_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    sm_enstate_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    /* Expect first transition segment */
	sm_dch_expect(evE.e, RKH_STATE_CAST(&smIPT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smIPT_s0), RKH_STATE_CAST(&smIPT_s5));
    sm_tsState_expect(RKH_STATE_CAST(&smIPT_s5));
	sm_ntrnact_expect(0, 1);
    /* Expect target state of last (second) transition */
    sm_tsState_expect(RKH_STATE_CAST(&smIPT_s52));
    /* Expect solve compoused transition */
    sm_exstate_expect(RKH_STATE_CAST(&smIPT_s0));
	sm_ntrnact_expect(0, 2);
    sm_enstate_expect(RKH_STATE_CAST(&smIPT_s5));
    sm_enstate_expect(RKH_STATE_CAST(&smIPT_s52));
    sm_nenex_expect(2, 1);
    /* Expect main target state */
    sm_state_expect(RKH_STATE_CAST(&smIPT_s52));
	sm_evtProc_expect();

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)me, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToBranchToCmpState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = RKH_CAST(SmInitialPseudoTest, 
                                       smInitialPseudoTest);

    /* Expect call actions */
    smIPT_init_Expect(me);
    smIPT_nS0_Expect(me);
    smIPT_isC1_ExpectAndReturn(me, &evE, RKH_FALSE);
    smIPT_isC2_ExpectAndReturn(me, &evE, RKH_FALSE);
    smIPT_xS0_Expect(me);
    smIPT_nS5_Expect(me);
    smIPT_nS51_Expect(me);
    smIPT_nS511_Expect(me);
    /* Expect init state machine */
    sm_init_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    sm_enstate_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    /* Expect first transition segment */
	sm_dch_expect(evE.e, RKH_STATE_CAST(&smIPT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smIPT_s0), RKH_STATE_CAST(&smIPT_s5));
    sm_tsState_expect(RKH_STATE_CAST(&smIPT_s5));
	sm_ntrnact_expect(0, 1);
    /* Expect target state of last (second) transition */
    sm_tsState_expect(RKH_STATE_CAST(&smIPT_s51));
    /* Expect solve compoused transition */
    sm_exstate_expect(RKH_STATE_CAST(&smIPT_s0));
	sm_ntrnact_expect(0, 2);
    sm_enstate_expect(RKH_STATE_CAST(&smIPT_s5));
    sm_enstate_expect(RKH_STATE_CAST(&smIPT_s51));
    sm_enstate_expect(RKH_STATE_CAST(&smIPT_s511));
    sm_nenex_expect(3, 1);
    /* Expect main target state */
    sm_state_expect(RKH_STATE_CAST(&smIPT_s511));
	sm_evtProc_expect();

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)me, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToBranchToNestedSimpleState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = RKH_CAST(SmInitialPseudoTest, 
                                       smInitialPseudoTest);

    /* Expect call actions */
    smIPT_init_Expect(me);
    smIPT_nS0_Expect(me);
    smIPT_isC1_ExpectAndReturn(me, &evE, RKH_FALSE);
    smIPT_isC2_ExpectAndReturn(me, &evE, RKH_TRUE);
    smIPT_xS0_Expect(me);
    smIPT_nS5_Expect(me);
    smIPT_nS51_Expect(me);
    smIPT_nS511_Expect(me);
    /* Expect init state machine */
    sm_init_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    sm_enstate_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    /* Expect first transition segment */
	sm_dch_expect(evE.e, RKH_STATE_CAST(&smIPT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smIPT_s0), RKH_STATE_CAST(&smIPT_s5));
    sm_tsState_expect(RKH_STATE_CAST(&smIPT_s5));
	sm_ntrnact_expect(0, 1);
    /* Expect target state of last (second) transition */
    sm_tsState_expect(RKH_STATE_CAST(&smIPT_s511));
    /* Expect solve compoused transition */
    sm_exstate_expect(RKH_STATE_CAST(&smIPT_s0));
	sm_ntrnact_expect(0, 2);
    sm_enstate_expect(RKH_STATE_CAST(&smIPT_s5));
    sm_enstate_expect(RKH_STATE_CAST(&smIPT_s51));
    sm_enstate_expect(RKH_STATE_CAST(&smIPT_s511));
    sm_nenex_expect(3, 1);
    /* Expect main target state */
    sm_state_expect(RKH_STATE_CAST(&smIPT_s511));
	sm_evtProc_expect();

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)me, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(InitPseudostate, trnToJunctionToSimpleState)
{
    UtrzProcessOut *p;
    SmInitialPseudoTest *me = RKH_CAST(SmInitialPseudoTest, 
                                       smInitialPseudoTest);

    /* Expect call actions */
    smIPT_init_Expect(me);
    smIPT_nS0_Expect(me);
    smIPT_isC1_ExpectAndReturn(me, &evF, RKH_TRUE);
    smIPT_xS0_Expect(me);
    smIPT_nS6_Expect(me);
    smIPT_nS61_Expect(me);
    /* Expect init state machine */
    sm_init_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    sm_enstate_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    /* Expect first transition segment */
	sm_dch_expect(evF.e, RKH_STATE_CAST(&smIPT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smIPT_s0), RKH_STATE_CAST(&smIPT_s6));
    sm_tsState_expect(RKH_STATE_CAST(&smIPT_s6));
    /* Expect target state of last (second) transition */
    sm_tsState_expect(RKH_STATE_CAST(&smIPT_s61));
    /* Expect solve compoused transition */
    sm_exstate_expect(RKH_STATE_CAST(&smIPT_s0));
	sm_ntrnact_expect(0, 2);
    sm_enstate_expect(RKH_STATE_CAST(&smIPT_s6));
    sm_enstate_expect(RKH_STATE_CAST(&smIPT_s61));
    sm_nenex_expect(2, 1);
    /* Expect main target state */
    sm_state_expect(RKH_STATE_CAST(&smIPT_s61));
	sm_evtProc_expect();

    rkh_sm_init((RKH_SM_T *)me);
    rkh_sm_dispatch((RKH_SM_T *)me, &evF);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
