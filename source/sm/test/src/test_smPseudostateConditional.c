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
 *  \file       test_smPseudostateConditional.c
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
 *  2017.06.05  LeFr  v1.0.00  Initial version
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
#include "smPseudoConditionalTest.h"
#include "MocksmPseudoConditionalTestAct.h"

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
TEST_GROUP(pseudostateConditional);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static
void
loadStateMachineSymbols(void)
{
    RKH_TR_FWK_AO(smPseudoConditionalTest);
    RKH_TR_FWK_STATE(smPseudoConditionalTest, &smPCT_waiting);
    RKH_TR_FWK_STATE(smPseudoConditionalTest, &smPCT_choice1);
    RKH_TR_FWK_STATE(smPseudoConditionalTest, &smPCT_choice2);
    RKH_TR_FWK_STATE(smPseudoConditionalTest, &smPCT_choice3);
    RKH_TR_FWK_STATE(smPseudoConditionalTest, &smPCT_choice4);
    RKH_TR_FWK_STATE(smPseudoConditionalTest, &smPCT_choice5);
    RKH_TR_FWK_STATE(smPseudoConditionalTest, &smPCT_choice6);
    RKH_TR_FWK_STATE(smPseudoConditionalTest, &smPCT_s0);
    RKH_TR_FWK_STATE(smPseudoConditionalTest, &smPCT_s1);
    RKH_TR_FWK_STATE(smPseudoConditionalTest, &smPCT_s11);
    RKH_TR_FWK_STATE(smPseudoConditionalTest, &smPCT_s12);
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
    RKH_FILTER_OFF_SMA(smPseudoConditionalTest);
    RKH_FILTER_OFF_EVENT(RKH_TE_FWK_ASSERT);
}

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(pseudostateConditional)
{
    sm_init();
    MocksmPseudoConditionalTestAct_Init();
    loadStateMachineSymbols();
    setRKHTraceFilters();
}

TEST_TEAR_DOWN(pseudostateConditional)
{
    sm_verify(); /* Makes sure there are no unused expectations, if */
                 /* there are, this function causes the test to fail. */
    sm_cleanup();
    MocksmPseudoConditionalTestAct_Verify();
    MocksmPseudoConditionalTestAct_Destroy();
}

/**
 *  \addtogroup test_smPseudostate Pseudostate test group
 *  @{
 *  \name Test cases of pseudostateConditional group
 *  @{ 
 */
TEST(pseudostateConditional, firstStateAfterInit)
{
    UtrzProcessOut *p;

	sm_init_expect(RKH_STATE_CAST(&smPCT_waiting));
	sm_enstate_expect(RKH_STATE_CAST(&smPCT_waiting));

    rkh_sm_init((RKH_SM_T *)smPseudoConditionalTest);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostateConditional, trnToChoiceWithTrueCondition)
{
    UtrzProcessOut *p;
    SmPseudoConditionalTest *me = RKH_CAST(SmPseudoConditionalTest, 
                                           smPseudoConditionalTest);

    /* Expect call actions */
    smPCT_setCondition_Expect(
        RKH_CAST(SmPseudoConditionalTest, me), &evA);
    smPCT_onEventA_ExpectAndReturn(
        RKH_CAST(SmPseudoConditionalTest, me), 
        &evA, RKH_TRUE);
    smPCT_tr1_Expect(
        RKH_CAST(SmPseudoConditionalTest, me), &evA);
    /* Expect init state machine */
    sm_init_expect(RKH_STATE_CAST(
        RKH_SMA_ACCESS_CONST(me, istate)));
    sm_enstate_expect(RKH_STATE_CAST(
        RKH_SMA_ACCESS_CONST(me, istate)));
    /* Expect first transition segment */
	sm_dch_expect(evA.e, RKH_STATE_CAST(&smPCT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smPCT_s0), RKH_STATE_CAST(&smPCT_choice1));
    sm_tsState_expect(RKH_STATE_CAST(&smPCT_choice1));
	sm_ntrnact_expect(1, 1);
    /* Expect target state of last (second) transition */
    sm_tsState_expect(RKH_STATE_CAST(&smPCT_s1));
    /* Expect solve compoused transition */
    sm_exstate_expect(RKH_STATE_CAST(&smPCT_s0));
	sm_ntrnact_expect(1, 2);
    sm_enstate_expect(RKH_STATE_CAST(&smPCT_s1));
    sm_enstate_expect(RKH_STATE_CAST(&smPCT_s11));
    sm_nenex_expect(2, 1);
    /* Expect main target state */
    sm_state_expect(RKH_STATE_CAST(&smPCT_s11));
	sm_evtProc_expect();
    /* Initialize and set state */
    rkh_sm_init((RKH_SM_T *)me);
    setState((RKH_SMA_T *)me, RKH_STATE_CAST(&smPCT_s0));

    rkh_sm_dispatch((RKH_SM_T *)me, &evA);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostateConditional, trnToChoiceWithFalseCondition)
{
    UtrzProcessOut *p;
    SmPseudoConditionalTest *me = RKH_CAST(SmPseudoConditionalTest, 
                                           smPseudoConditionalTest);

    /* Expect call actions */
    smPCT_setCondition_Expect(
        RKH_CAST(SmPseudoConditionalTest, me), &evB);
    smPCT_onEventA_ExpectAndReturn(
        RKH_CAST(SmPseudoConditionalTest, me), 
        &evB, RKH_FALSE);
    smPCT_onEventD_ExpectAndReturn(
        RKH_CAST(SmPseudoConditionalTest, me), 
        &evB, RKH_FALSE);
    smPCT_tr2_Expect(
        RKH_CAST(SmPseudoConditionalTest, me), &evB);
    /* Expect init state machine */
    sm_init_expect(RKH_STATE_CAST(
        RKH_SMA_ACCESS_CONST(me, istate)));
    sm_enstate_expect(RKH_STATE_CAST(
        RKH_SMA_ACCESS_CONST(me, istate)));
    /* Expect first transition segment */
	sm_dch_expect(evB.e, RKH_STATE_CAST(&smPCT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smPCT_s0), RKH_STATE_CAST(&smPCT_choice1));
    sm_tsState_expect(RKH_STATE_CAST(&smPCT_choice1));
	sm_ntrnact_expect(1, 1);
    /* Expect target state of last (second) transition */
    sm_tsState_expect(RKH_STATE_CAST(&smPCT_s12));
    /* Expect solve compoused transition */
    sm_exstate_expect(RKH_STATE_CAST(&smPCT_s0));
	sm_ntrnact_expect(1, 2);
    sm_enstate_expect(RKH_STATE_CAST(&smPCT_s1));
    sm_enstate_expect(RKH_STATE_CAST(&smPCT_s12));
    sm_nenex_expect(2, 1);
    /* Expect main target state */
    sm_state_expect(RKH_STATE_CAST(&smPCT_s12));
	sm_evtProc_expect();
    /* Initialize and set state */
    rkh_sm_init((RKH_SM_T *)me);
    setState((RKH_SMA_T *)me, RKH_STATE_CAST(&smPCT_s0));

    rkh_sm_dispatch((RKH_SM_T *)me, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostateConditional, trnToChoiceWithoutElse)
{
    UtrzProcessOut *p;
    SmPseudoConditionalTest *me = RKH_CAST(SmPseudoConditionalTest, 
                                           smPseudoConditionalTest);

    /* Expect call actions */
    smPCT_onEventA_ExpectAndReturn(
        RKH_CAST(SmPseudoConditionalTest, me), 
        &evC, RKH_FALSE);
    /* Expect init state machine */
    sm_init_expect(RKH_STATE_CAST(
        RKH_SMA_ACCESS_CONST(me, istate)));
    sm_enstate_expect(RKH_STATE_CAST(
        RKH_SMA_ACCESS_CONST(me, istate)));
    /* Expect first transition segment */
	sm_dch_expect(evC.e, RKH_STATE_CAST(&smPCT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smPCT_s0), RKH_STATE_CAST(&smPCT_choice2));
    sm_tsState_expect(RKH_STATE_CAST(&smPCT_choice2));
	sm_ntrnact_expect(0, 1);
	sm_cndNotFound_expect();
    /* Initialize and set state */
    rkh_sm_init((RKH_SM_T *)me);
    setState((RKH_SMA_T *)me, RKH_STATE_CAST(&smPCT_s0));

    rkh_sm_dispatch((RKH_SM_T *)me, &evC);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostateConditional, trnToChoiceReturnToSource)
{
    UtrzProcessOut *p;
    SmPseudoConditionalTest *me = RKH_CAST(SmPseudoConditionalTest, 
                                           smPseudoConditionalTest);

    /* Expect call actions */
    smPCT_onEventA_ExpectAndReturn(RKH_CAST(SmPseudoConditionalTest, me), 
                                   &evD, RKH_FALSE);
    smPCT_onEventD_ExpectAndReturn(RKH_CAST(SmPseudoConditionalTest, me), 
                                   &evD, RKH_TRUE);
    smPCT_tr4_Expect(RKH_CAST(SmPseudoConditionalTest, me), &evD);
    /* Expect init state machine */
    sm_init_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    sm_enstate_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    /* Expect first transition segment */
	sm_dch_expect(evD.e, RKH_STATE_CAST(&smPCT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smPCT_s0), RKH_STATE_CAST(&smPCT_choice1));
    sm_tsState_expect(RKH_STATE_CAST(&smPCT_choice1));
	sm_ntrnact_expect(0, 1);
    /* Expect target state of last (second) transition */
    sm_tsState_expect(RKH_STATE_CAST(&smPCT_s0));
    /* Expect solve compoused transition */
    sm_exstate_expect(RKH_STATE_CAST(&smPCT_s0));
	sm_ntrnact_expect(1, 2);
    sm_enstate_expect(RKH_STATE_CAST(&smPCT_s0));
    sm_nenex_expect(1, 1);
    /* Expect main target state */
    sm_state_expect(RKH_STATE_CAST(&smPCT_s0));
	sm_evtProc_expect();
    /* Initialize and set state */
    rkh_sm_init((RKH_SM_T *)me);
    setState((RKH_SMA_T *)me, RKH_STATE_CAST(&smPCT_s0));

    rkh_sm_dispatch((RKH_SM_T *)me, &evD);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(pseudostateConditional, failsTrnSegmentsExceeded)
{
    UtrzProcessOut *p;
    SmPseudoConditionalTest *me = RKH_CAST(SmPseudoConditionalTest, 
                                           smPseudoConditionalTest);

    /* Expect call actions */
    smPCT_tr1_Expect(RKH_CAST(SmPseudoConditionalTest, me), &evE);
    smPCT_guardTrue_ExpectAndReturn(RKH_CAST(SmPseudoConditionalTest, me), 
                                    &evE, RKH_TRUE);
    smPCT_tr1_Expect(RKH_CAST(SmPseudoConditionalTest, me), &evE);
    smPCT_guardTrue_ExpectAndReturn(RKH_CAST(SmPseudoConditionalTest, me), 
                                    &evE, RKH_TRUE);
    smPCT_tr1_Expect(RKH_CAST(SmPseudoConditionalTest, me), &evE);
    smPCT_guardTrue_ExpectAndReturn(RKH_CAST(SmPseudoConditionalTest, me), 
                                    &evE, RKH_TRUE);
    smPCT_tr1_Expect(RKH_CAST(SmPseudoConditionalTest, me), &evE);
    smPCT_guardTrue_ExpectAndReturn(RKH_CAST(SmPseudoConditionalTest, me), 
                                    &evE, RKH_TRUE);
    smPCT_tr1_Expect(RKH_CAST(SmPseudoConditionalTest, me), &evE);
    /* Expect init state machine */
    sm_init_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    sm_enstate_expect(RKH_STATE_CAST(RKH_SMA_ACCESS_CONST(me, istate)));
    /* Expect first transition segment */
	sm_dch_expect(evE.e, RKH_STATE_CAST(&smPCT_s0));
	sm_trn_expect(RKH_STATE_CAST(&smPCT_s0), RKH_STATE_CAST(&smPCT_choice3));
    sm_tsState_expect(RKH_STATE_CAST(&smPCT_choice3));
	sm_ntrnact_expect(1, 1);
    /* Expect target state of next transition */
    sm_tsState_expect(RKH_STATE_CAST(&smPCT_choice4));
	sm_ntrnact_expect(1, 2);
    sm_tsState_expect(RKH_STATE_CAST(&smPCT_choice5));
	sm_ntrnact_expect(1, 3);
    sm_tsState_expect(RKH_STATE_CAST(&smPCT_choice6));
	sm_ntrnact_expect(1, 4);
    sm_tsState_expect(RKH_STATE_CAST(&smPCT_s1));
    /* Expect solve compoused transition */
    sm_exstate_expect(RKH_STATE_CAST(&smPCT_s0));
	sm_ntrnact_expect(1, 5);
    sm_enstate_expect(RKH_STATE_CAST(&smPCT_s1));
    sm_enstate_expect(RKH_STATE_CAST(&smPCT_s11));
    sm_nenex_expect(2, 1);
    /* Expect main target state */
    sm_state_expect(RKH_STATE_CAST(&smPCT_s11));
	sm_evtProc_expect();
    /* Initialize and set state */
    rkh_sm_init((RKH_SM_T *)me);
    setState((RKH_SMA_T *)me, RKH_STATE_CAST(&smPCT_s0));

    rkh_sm_dispatch((RKH_SM_T *)me, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
