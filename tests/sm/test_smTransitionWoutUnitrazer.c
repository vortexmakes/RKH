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
 *  \file       test_smTransitionWoutUnitrazer.c
 *  \ingroup    test_sm
 *  \brief      Test runner of state machine module without unitrazer facility
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
#include "rkh.h"
#include "common.h"
#include "smTest.h"
#include "smTestAct.h"
#include "MocksmTestAct.h"

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
TEST_GROUP(trnWoutUnitrazer);
static RKH_ST_T *expectedState;
static RKH_RCODE_T result;

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
setProfileWoutUnitrazer(RKH_SMA_T *const me, 
                        const RKH_ST_T *currentState, 
                        const RKH_ST_T *sourceState, 
                        const RKH_ST_T *mainTargetState, 
                        int initStateMachine)
{
    if (initStateMachine)
    {
        rkh_sm_init((RKH_SM_T *)me);
    }
    if (currentState && (currentState != ((RKH_SM_T *)smTest)->state))
    {
        setStateForcesfully(me, RKH_STATE_CAST(currentState));
    }
    expectedState = RKH_STATE_CAST(mainTargetState);
}

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(trnWoutUnitrazer)
{
    MocksmTestAct_Init();
    sm_ignore();
}

TEST_TEAR_DOWN(trnWoutUnitrazer)
{
    MocksmTestAct_Verify();
    MocksmTestAct_Destroy();
}

/**
 *  \addtogroup test_smTransitionWoutUnitrazer Transition test group (wout Ut)
 *  @{
 *  \name Test cases of trnWoutUnitrazer group
 *  @{ 
 */

TEST(trnWoutUnitrazer, firstStateAfterInit)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    expectedState = RKH_STATE_CAST(&waiting);

    rkh_sm_init((RKH_SM_T *)smTest);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
}

TEST(trnWoutUnitrazer, simpleToSimpleAtEqualLevel)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr11_Expect(RKH_CAST(SmTest, smTest), &evA);
    smTest_nS1_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s1),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, simpleToSimpleFromHighToLowLevel)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr12_Expect(RKH_CAST(SmTest, smTest), &evB);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s21),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, simpleToSimpleFromLowToHighLevel)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr13_Expect(RKH_CAST(SmTest, smTest), &evB);
    smTest_nS0_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s0),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, simpleToCompositeAtEqualLevel)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr21_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s21),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, simpleToCompositeFromHighToLowLevel)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr22_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS2211_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s2211),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, simpleToCompositeFromLowToHighLevel)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr23_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_iS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s21),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, compositeToSimpleAtEqualLevel)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr31_Expect(RKH_CAST(SmTest, smTest), &evA);
    smTest_nS0_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s2),
                            RKH_STATE_CAST(&s0),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, compositeToSimpleFromHighToLowLevel)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr32_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s2),
                            RKH_STATE_CAST(&s21),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, loopSimpleStateOnTop)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS1_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr53_Expect(RKH_CAST(SmTest, smTest), &evA);
    smTest_nS1_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, loopNestedSimpleState)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS31_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr52_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_nS31_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s31),
                            RKH_STATE_CAST(&s31),
                            RKH_STATE_CAST(&s31),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, loopCompositeStateOnTop)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS31_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr51_Expect(RKH_CAST(SmTest, smTest), &evA);
    smTest_iS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS31_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s31),
                            RKH_STATE_CAST(&s3),
                            RKH_STATE_CAST(&s31),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, loopNestedCompositeState)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2211_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr54_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_iS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS2211_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s2211),
                            RKH_STATE_CAST(&s22),
                            RKH_STATE_CAST(&s2211),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, compositeToSimpleFromLowToHighLevel)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2211_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr33_Expect(RKH_CAST(SmTest, smTest), &evB);
    smTest_nS0_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s2211),
                            RKH_STATE_CAST(&s22),
                            RKH_STATE_CAST(&s0),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, compositeToCompositeAtEqualLevel)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS31_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr41_Expect(RKH_CAST(SmTest, smTest), &evB);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s31),
                            RKH_STATE_CAST(&s3),
                            RKH_STATE_CAST(&s21),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, compositeToCompositeFromHighToLowLevel)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS31_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr42_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS2211_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s31),
                            RKH_STATE_CAST(&s3),
                            RKH_STATE_CAST(&s2211),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, compositeToCompositeFromLowToHighLevel)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2211_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr43_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS31_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s2211),
                            RKH_STATE_CAST(&s3),
                            RKH_STATE_CAST(&s31),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, internalInSimpleState)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr14_Expect(RKH_CAST(SmTest, smTest), &evB);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, internalInCompositeState)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr15_Expect(RKH_CAST(SmTest, smTest), &evE);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s31),
                            RKH_STATE_CAST(&s3),
                            RKH_STATE_CAST(&s31),
                            INIT_STATE_MACHINE);

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evE);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
}

TEST(trnWoutUnitrazer, fails_EventNotFound)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evE);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_NFOUND, result);
}

TEST(trnWoutUnitrazer, fails_GuardFalseOnInternalTrn)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_falseGuard_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evC, 
                                      RKH_FALSE);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_NFOUND, result);
}

TEST(trnWoutUnitrazer, fails_GuardFalseOnExternalTrn)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_falseGuard_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evD, 
                                      RKH_FALSE);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_NFOUND, result);
}

TEST(trnWoutUnitrazer, fails_ExceededHierarchicalLevel)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s0),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evE);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EX_HLEVEL, result);
}

TEST(trnWoutUnitrazer, multipleEnabledTrn_FiringFirstTrueGuard)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_guard4a_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evA, RKH_FALSE);
    smTest_guard4b_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evA, RKH_TRUE);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s4),
                            RKH_STATE_CAST(&s4),
                            RKH_STATE_CAST(&s4),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, multipleEnabledTrn_FiringFirstEmptyGuard)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_guard4a_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evB, RKH_FALSE);
    smTest_guard4b_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evB, RKH_FALSE);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s4),
                            RKH_STATE_CAST(&s4),
                            RKH_STATE_CAST(&s4),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, defaultTrnWithAssociatedEffect)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr55_Expect(RKH_CAST(SmTest, smTest), &evF);
    smTest_nS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS31_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s31),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evF);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, generatedCompletionEventBySimpleState)
{
    /* Expectations for transition to s5 */
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS5_Expect(RKH_CAST(SmTest, smTest));
    /* Expectations for completion transition */
    smTest_xS5_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr61_Expect(RKH_CAST(SmTest, smTest), &evCompletion);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s2),
                            RKH_STATE_CAST(&s4),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evE);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, generatedCompletionEventByFinalState)
{
    /* Expectations for transition to S2's FinalState */
    smTest_init_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    /* Expectations for completion transition */
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_guardS2_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evCompletion, 
                                   RKH_TRUE);
    smTest_tr60_Expect(RKH_CAST(SmTest, smTest), &evCompletion);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s4),
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evF);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, syncDispatchingToStateMachine)
{
    TEST_IGNORE();
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
