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
 *  \file       test_smTransition.c
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
#include "smTest.h"
#include "smTestAct.h"
#include "MocksmTestAct.h"
#include "Mockrkhassert.h"

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
static RKH_STATIC_EVENT(evCompletion, RKH_COMPLETION_EVENT);
static RKH_STATIC_EVENT(evTerminate, TERMINATE);

/* ---------------------------- Local data types --------------------------- */
typedef struct StateMachine
{
    RKH_SM_T sm;
    int foo;
} StateMachine;

typedef struct Composite
{
    RKH_SMA_T ao;
    int foo;
    RKH_SM_T itsReactivePart;
} Composite;

/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(transition);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(transition)
{
    sm_init();
    MocksmTestAct_Init();

    RKH_TR_FWK_AO(smTest);
    RKH_TR_FWK_STATE(smTest, &waiting);
    RKH_TR_FWK_STATE(smTest, &s0);
    RKH_TR_FWK_STATE(smTest, &s1);
    RKH_TR_FWK_STATE(smTest, &s2);
    RKH_TR_FWK_STATE(smTest, &s21);
    RKH_TR_FWK_STATE(smTest, &s22);
    RKH_TR_FWK_STATE(smTest, &s221);
    RKH_TR_FWK_STATE(smTest, &s2211);
    RKH_TR_FWK_STATE(smTest, &s222);
    RKH_TR_FWK_STATE(smTest, &s2221);
    RKH_TR_FWK_STATE(smTest, &s22211);
    RKH_TR_FWK_STATE(smTest, &s3);
    RKH_TR_FWK_STATE(smTest, &s31);
    RKH_TR_FWK_STATE(smTest, &s4);
    RKH_TR_FWK_STATE(smTest, &s5);
    RKH_TR_FWK_STATE(smTest, &s2Final);
    RKH_TR_FWK_SIG(A);
    RKH_TR_FWK_SIG(B);
    RKH_TR_FWK_SIG(C);
    RKH_TR_FWK_SIG(D);
    RKH_TR_FWK_SIG(E);
    RKH_TR_FWK_SIG(F);

    RKH_FILTER_OFF_ALL_SIGNALS();
    RKH_FILTER_OFF_GROUP_ALL_EVENTS(RKH_TG_SM);
    RKH_FILTER_OFF_SMA(smTest);
    RKH_FILTER_OFF_EVENT(RKH_TE_FWK_ASSERT);
}

TEST_TEAR_DOWN(transition)
{
    sm_verify(); /* Makes sure there are no unused expectations, if */
                 /* there are, this function causes the test to fail. */
    sm_cleanup();
    MocksmTestAct_Verify();
    MocksmTestAct_Destroy();
}

/**
 *  \addtogroup test_smTransition Transition test group
 *  @{
 *  \name Test cases of transition group
 *  @{ 
 */

TEST(transition, firstStateAfterInit)
{
    UtrzProcessOut *p;

	sm_init_expect(RKH_STATE_CAST(&waiting));
	sm_enstate_expect(RKH_STATE_CAST(&waiting));
    smTest_init_Expect(RKH_CAST(SmTest, smTest));

    rkh_sm_init((RKH_SM_T *)smTest);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, simpleToSimpleAtEqualLevel)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s1), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s1), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s0), RKH_STATE_CAST(0)
    };

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr11_Expect(RKH_CAST(SmTest, smTest), &evA);
    smTest_nS1_Expect(RKH_CAST(SmTest, smTest));

    setProfile(smTest, RKH_STATE_CAST(&s0), RKH_STATE_CAST(&s0), 
               targetStates,
               entryStates, exitStates, RKH_STATE_CAST(&s1), 1,
               TRN_NOT_INTERNAL, INIT_STATE_MACHINE, &evA, 
               RKH_STATE_CAST(&s0));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, simpleToSimpleFromHighToLowLevel)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s21), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s2), RKH_STATE_CAST(&s21), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s0), RKH_STATE_CAST(0)
    };

    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr12_Expect(RKH_CAST(SmTest, smTest), &evB);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s0), RKH_STATE_CAST(&s0), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s21), 1, 
               TRN_NOT_INTERNAL, INIT_STATE_MACHINE, &evB, 
               RKH_STATE_CAST(&s0));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, simpleToSimpleFromLowToHighLevel)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s2), RKH_STATE_CAST(0)
    };

    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr13_Expect(RKH_CAST(SmTest, smTest), &evB);
    smTest_nS0_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s21), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s0), 1, 
               TRN_NOT_INTERNAL, INIT_STATE_MACHINE, &evB, 
               RKH_STATE_CAST(&s21));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, simpleToCompositeAtEqualLevel)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s2), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s2), RKH_STATE_CAST(&s21), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s0), RKH_STATE_CAST(0)
    };

    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr21_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s0), RKH_STATE_CAST(&s0), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s21), 1, 
               TRN_NOT_INTERNAL, INIT_STATE_MACHINE, &evC, 
               RKH_STATE_CAST(&s0));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, simpleToCompositeFromHighToLowLevel)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s22), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s2), RKH_STATE_CAST(&s22), RKH_STATE_CAST(&s221), 
        RKH_STATE_CAST(&s2211), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s0), RKH_STATE_CAST(0)
    };

    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr22_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS2211_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s0), RKH_STATE_CAST(&s0), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s2211), 1, 
               TRN_NOT_INTERNAL, INIT_STATE_MACHINE, &evD,
               RKH_STATE_CAST(&s0));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, simpleToCompositeFromLowToHighLevel)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s2), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s21), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s21), RKH_STATE_CAST(0)
    };

    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr23_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_iS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s21), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s21), 1, 
               TRN_NOT_INTERNAL, INIT_STATE_MACHINE, &evC,
               RKH_STATE_CAST(&s21));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, compositeToSimpleAtEqualLevel)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s2), RKH_STATE_CAST(0)
    };

    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr31_Expect(RKH_CAST(SmTest, smTest), &evA);
    smTest_nS0_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s2), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s0), 1, 
               TRN_NOT_INTERNAL, INIT_STATE_MACHINE, &evA,
               RKH_STATE_CAST(&s21));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, compositeToSimpleFromHighToLowLevel)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s21), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s21), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s21), RKH_STATE_CAST(0)
    };

    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr32_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s2), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s21), 1, 
               TRN_NOT_INTERNAL, INIT_STATE_MACHINE, &evD,
               RKH_STATE_CAST(&s21));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, loopSimpleStateOnTop)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s1), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s1), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s1), RKH_STATE_CAST(0)
    };

    smTest_xS1_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr53_Expect(RKH_CAST(SmTest, smTest), &evA);
    smTest_nS1_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s1), RKH_STATE_CAST(&s1), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s1), 1, 
               TRN_NOT_INTERNAL, INIT_STATE_MACHINE, &evA,
               RKH_STATE_CAST(&s1));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, loopNestedSimpleState)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s31), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s31), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s31), RKH_STATE_CAST(0)
    };

    smTest_xS31_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr52_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_nS31_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s31), RKH_STATE_CAST(&s31), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s31), 1, TRN_NOT_INTERNAL, INIT_STATE_MACHINE,
               &evD, RKH_STATE_CAST(&s31));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, loopCompositeStateOnTop)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s3), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s31), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s31), RKH_STATE_CAST(0)
    };

    smTest_xS31_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr51_Expect(RKH_CAST(SmTest, smTest), &evA);
    smTest_iS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS31_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s31), RKH_STATE_CAST(&s3), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s31), 1, TRN_NOT_INTERNAL, INIT_STATE_MACHINE,
               &evA, RKH_STATE_CAST(&s31));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, loopNestedCompositeState)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s22), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s221), RKH_STATE_CAST(&s2211), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s2211), RKH_STATE_CAST(&s221), RKH_STATE_CAST(0)
    };

    smTest_xS2211_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr54_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_iS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS2211_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s2211), RKH_STATE_CAST(&s22), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s2211), 1, TRN_NOT_INTERNAL, 
               INIT_STATE_MACHINE, &evD, RKH_STATE_CAST(&s2211));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, compositeToSimpleFromLowToHighLevel)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s0), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s221), RKH_STATE_CAST(&s22), RKH_STATE_CAST(&s2), 
        RKH_STATE_CAST(0)
    };

    smTest_xS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr33_Expect(RKH_CAST(SmTest, smTest), &evB);
    smTest_nS0_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s221), RKH_STATE_CAST(&s22), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s0), 1, TRN_NOT_INTERNAL, INIT_STATE_MACHINE,
               &evB, RKH_STATE_CAST(&s221));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, compositeToCompositeAtEqualLevel)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s2), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s2), RKH_STATE_CAST(&s21), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s31), RKH_STATE_CAST(&s3), RKH_STATE_CAST(0)
    };

    smTest_xS31_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr41_Expect(RKH_CAST(SmTest, smTest), &evB);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s31), RKH_STATE_CAST(&s3), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s21), 1, TRN_NOT_INTERNAL, INIT_STATE_MACHINE,
               &evB, RKH_STATE_CAST(&s31));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, compositeToCompositeFromHighToLowLevel)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s22), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s2), RKH_STATE_CAST(&s22), RKH_STATE_CAST(&s221), 
        RKH_STATE_CAST(&s2211), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s31), RKH_STATE_CAST(&s3), RKH_STATE_CAST(0)
    };

    smTest_xS31_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr42_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS2211_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s31), RKH_STATE_CAST(&s3), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s2211), 1, TRN_NOT_INTERNAL, INIT_STATE_MACHINE,
               &evC, RKH_STATE_CAST(&s31));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, compositeToCompositeFromLowToHighLevel)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s3), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s3), RKH_STATE_CAST(&s31), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s221), RKH_STATE_CAST(&s22), RKH_STATE_CAST(&s2), 
        RKH_STATE_CAST(0)
    };

    smTest_xS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr43_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS31_Expect(RKH_CAST(SmTest, smTest));

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s221), RKH_STATE_CAST(&s22), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s31), 1, TRN_NOT_INTERNAL, INIT_STATE_MACHINE,
               &evC, RKH_STATE_CAST(&s221));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, internalInSimpleState)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s1), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(0)
    };

    smTest_tr14_Expect(RKH_CAST(SmTest, smTest), &evB);

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfile(smTest, RKH_STATE_CAST(&s1), RKH_STATE_CAST(&s1), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s1), 1, TRN_INTERNAL, INIT_STATE_MACHINE, 
               &evB, RKH_STATE_CAST(&s1));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, internalInCompositeState)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s3), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(0)
    };

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr15_Expect(RKH_CAST(SmTest, smTest), &evE);

    setProfile(smTest, RKH_STATE_CAST(&s31), RKH_STATE_CAST(&s3), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s31), 1, TRN_INTERNAL, INIT_STATE_MACHINE,
               &evE, RKH_STATE_CAST(&s31));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, fails_EventNotFound)
{
    UtrzProcessOut *p;

    smTest_init_Expect(RKH_CAST(SmTest, smTest));

	sm_init_expect(RKH_STATE_CAST(&waiting));
	sm_enstate_expect(RKH_STATE_CAST(&waiting));
	sm_dch_expect(evE.e, RKH_STATE_CAST(&s1));
	sm_evtNotFound_expect(E);

    rkh_sm_init((RKH_SM_T *)smTest);
    setState(smTest, RKH_STATE_CAST(&s1));
    rkh_sm_dispatch((RKH_SM_T *)smTest, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, fails_GuardFalse)
{
    UtrzProcessOut *p;

	sm_init_expect(RKH_STATE_CAST(&waiting));
	sm_enstate_expect(RKH_STATE_CAST(&waiting));
	sm_grdFalse_expect();
	sm_dch_expect(evC.e, RKH_STATE_CAST(&s1));
    sm_evtNotFound_expect(C);

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_falseGuard_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evC, 
                                      RKH_FALSE);

    rkh_sm_init((RKH_SM_T *)smTest);
    setState(smTest, RKH_STATE_CAST(&s1));
    rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, fails_ExceededHierarchicalLevel)
{
    UtrzProcessOut *p;

	sm_init_expect(RKH_STATE_CAST(&waiting));
	sm_enstate_expect(RKH_STATE_CAST(&waiting));
	sm_dch_expect(evE.e, RKH_STATE_CAST(&s0));
	sm_trn_expect(RKH_STATE_CAST(&s0), RKH_STATE_CAST(&s22211));
    sm_tsState_expect(RKH_STATE_CAST(&s22211));
	sm_exHLevel_expect();
    rkh_assert_Expect("rkhsm", 0);
    rkh_assert_IgnoreArg_line();

    smTest_init_Expect(RKH_CAST(SmTest, smTest));

    rkh_sm_init((RKH_SM_T *)smTest);
    setState(smTest, RKH_STATE_CAST(&s0));
    rkh_sm_dispatch((RKH_SM_T *)smTest, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, multipleEnabledTrn_FiringFirstTrueGuard)
{
    UtrzProcessOut *p;

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_guard4a_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evA, RKH_FALSE);
    smTest_guard4b_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evA, RKH_TRUE);

    sm_init_ignore();
	sm_enstate_ignore();
	sm_ntrnact_ignore();
	sm_dch_ignore();
	sm_trn_ignore();
	sm_evtProc_ignore();
    sm_grdFalse_expect();

    rkh_sm_init((RKH_SM_T *)smTest);
    setState(smTest, RKH_STATE_CAST(&s4));
    rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, multipleEnabledTrn_FiringFirstEmptyGuard)
{
    UtrzProcessOut *p;

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_guard4a_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evB, RKH_FALSE);
    smTest_guard4b_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evB, RKH_FALSE);

    sm_init_ignore();
	sm_enstate_ignore();
	sm_exstate_ignore();
	sm_ntrnact_ignore();
	sm_evtProc_ignore();
    sm_grdFalse_expect();
    sm_grdFalse_expect();
	sm_trn_ignore();
    sm_nenex_ignore();
    sm_state_ignore();
    sm_dch_ignore();
    sm_tsState_expect(RKH_STATE_CAST(&s4));

    rkh_sm_init((RKH_SM_T *)smTest);
    setState(smTest, RKH_STATE_CAST(&s4));
    rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, defaultTrnWithAssociatedEffect)
{
    UtrzProcessOut *p;
    const RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s3), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s3), RKH_STATE_CAST(&s31), RKH_STATE_CAST(0)
    };
    const RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s0), RKH_STATE_CAST(0)
    };

    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr55_Expect(RKH_CAST(SmTest, smTest), &evF);
    smTest_nS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS31_Expect(RKH_CAST(SmTest, smTest));

    setProfile(smTest, RKH_STATE_CAST(&s0), RKH_STATE_CAST(&s0), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s31), 1, TRN_NOT_INTERNAL, INIT_STATE_MACHINE,
               &evF, RKH_STATE_CAST(&s0));

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evF);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, generatedCompletionEventBySimpleState)
{
    UtrzProcessOut *p;
    RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s5), RKH_STATE_CAST(0)
    };
    RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s5), RKH_STATE_CAST(0)
    };
    RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s2), RKH_STATE_CAST(0)
    };

    /* Expectations for transition to s5 */
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS5_Expect(RKH_CAST(SmTest, smTest));

    setProfile(smTest, RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s2), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s5), 0, TRN_NOT_INTERNAL, INIT_STATE_MACHINE,
               &evE, RKH_STATE_CAST(&s21));

    /* Expectations for completion transition */
    targetStates[0] = RKH_STATE_CAST(&s4);
    targetStates[1] = RKH_STATE_CAST(0);
    entryStates[0] = RKH_STATE_CAST(&s4);
    entryStates[1] = RKH_STATE_CAST(0);
    exitStates[0] = RKH_STATE_CAST(&s5);
    exitStates[1] = RKH_STATE_CAST(0);

    smTest_xS5_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr61_Expect(RKH_CAST(SmTest, smTest), &evCompletion);

    setProfile(smTest, NULL, RKH_STATE_CAST(&s5), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s4), 1, TRN_NOT_INTERNAL, 
               NO_INIT_STATE_MACHINE, &evCompletion, RKH_STATE_CAST(&s5));

    /* Exercices */
    rkh_sm_dispatch((RKH_SM_T *)smTest, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, generatedCompletionEventByFinalState)
{
    UtrzProcessOut *p;
    RKH_ST_T *targetStates[] = 
    {
        RKH_STATE_CAST(&s2Final), RKH_STATE_CAST(0)
    };
    RKH_ST_T *entryStates[] = 
    {
        RKH_STATE_CAST(&s2Final), RKH_STATE_CAST(0)
    };
    RKH_ST_T *exitStates[] = 
    {
        RKH_STATE_CAST(&s21), RKH_STATE_CAST(0), RKH_STATE_CAST(0)
    };

    /* Expectations for transition to S2's FinalState */
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));

    setProfile(smTest, RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s21), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s2Final), 0, TRN_NOT_INTERNAL, 
               INIT_STATE_MACHINE, &evF, RKH_STATE_CAST(&s21));

    /* Expectations for completion transition */
    targetStates[0] = RKH_STATE_CAST(&s4);
    targetStates[1] = RKH_STATE_CAST(0);
    entryStates[0] = RKH_STATE_CAST(&s4);
    entryStates[1] = RKH_STATE_CAST(0);
    exitStates[0] = RKH_STATE_CAST(&s2Final);
    exitStates[1] = RKH_STATE_CAST(&s2);
    exitStates[2] = RKH_STATE_CAST(0);

    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_guardS2_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evCompletion, 
                                   RKH_TRUE);
    smTest_tr60_Expect(RKH_CAST(SmTest, smTest), &evCompletion);

    setProfile(smTest, NULL, RKH_STATE_CAST(&s2), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s4), 1, TRN_NOT_INTERNAL, 
               NO_INIT_STATE_MACHINE, &evCompletion, RKH_STATE_CAST(&s2Final));

    /* Exercices */
    rkh_sm_dispatch((RKH_SM_T *)smTest, &evF);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, syncDispatchingToStateMachine)
{
    TEST_IGNORE();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
