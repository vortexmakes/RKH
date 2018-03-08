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
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "unitrazer.h"
#include "rkhfwk_dynevt.h"
#include "common.h"
#include "smTest.h"
#include "smTestAct.h"
#include "Mock_smTestAct.h"
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
static RKH_STATIC_EVENT(evTerminate, TERMINATE);
extern const RKH_EVT_T evCompletion;
extern const RKH_EVT_T evCreation;

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
/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(trnWoutUnitrazer)
{
    Mock_smTestAct_Init();
    sm_ignore();
}

TEST_TEAR_DOWN(trnWoutUnitrazer)
{
    Mock_smTestAct_Verify();
    Mock_smTestAct_Destroy();
}

/**
 *  \addtogroup test_smTransitionWoutUnitrazer Transition test group (wout Ut)
 *  @{
 *  \name Test cases of trnWoutUnitrazer group
 *  @{ 
 */

TEST(trnWoutUnitrazer, firstStateAfterInit)
{
    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    expectedState = RKH_STATE_CAST(&waiting);

    rkh_sm_init((RKH_SM_T *)smTest);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
}

TEST(trnWoutUnitrazer, simpleToSimpleAtEqualLevel)
{
    expectedState = RKH_STATE_CAST(&s1);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr11_Expect(RKH_CAST(SmTest, smTest), &evA);
    smTest_nS1_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s0),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, simpleToSimpleFromHighToLowLevel)
{
    expectedState = RKH_STATE_CAST(&s21);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr12_Expect(RKH_CAST(SmTest, smTest), &evB);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s0),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, simpleToSimpleFromLowToHighLevel)
{
    expectedState = RKH_STATE_CAST(&s0);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr13_Expect(RKH_CAST(SmTest, smTest), &evB);
    smTest_nS0_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s21),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, simpleToCompositeAtEqualLevel)
{
    expectedState = RKH_STATE_CAST(&s21);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr21_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS2_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s0),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, simpleToCompositeFromHighToLowLevel)
{
    expectedState = RKH_STATE_CAST(&s2211);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr22_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS22_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_nS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS221_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_nS2211_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s0),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, simpleToCompositeFromLowToHighLevel)
{
    expectedState = RKH_STATE_CAST(&s21);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr23_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_iS2_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s21),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, compositeToSimpleAtEqualLevel)
{
    expectedState = RKH_STATE_CAST(&s0);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr31_Expect(RKH_CAST(SmTest, smTest), &evA);
    smTest_nS0_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s2),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, compositeToSimpleFromHighToLowLevel)
{
    expectedState = RKH_STATE_CAST(&s21);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr32_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s2),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, loopSimpleStateOnTop)
{
    expectedState = RKH_STATE_CAST(&s1);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS1_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr53_Expect(RKH_CAST(SmTest, smTest), &evA);
    smTest_nS1_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, loopNestedSimpleState)
{
    expectedState = RKH_STATE_CAST(&s31);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS31_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr52_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_nS31_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s31),
                            RKH_STATE_CAST(&s31),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, loopCompositeStateOnTop)
{
    expectedState = RKH_STATE_CAST(&s31);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS31_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr51_Expect(RKH_CAST(SmTest, smTest), &evA);
    smTest_iS3_Expect(RKH_CAST(SmTest, smTest), &evA);
    smTest_nS31_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s31),
                            RKH_STATE_CAST(&s3),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, loopNestedCompositeState)
{
    expectedState = RKH_STATE_CAST(&s2211);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS2211_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr54_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_iS22_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_nS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS221_Expect(RKH_CAST(SmTest, smTest), &evD);
    smTest_nS2211_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s2211),
                            RKH_STATE_CAST(&s22),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, compositeToSimpleFromLowToHighLevel)
{
    expectedState = RKH_STATE_CAST(&s0);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS2211_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr33_Expect(RKH_CAST(SmTest, smTest), &evB);
    smTest_nS0_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s2211),
                            RKH_STATE_CAST(&s22),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, compositeToCompositeAtEqualLevel)
{
    expectedState = RKH_STATE_CAST(&s21);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS31_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr41_Expect(RKH_CAST(SmTest, smTest), &evB);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS2_Expect(RKH_CAST(SmTest, smTest), &evB);
    smTest_nS21_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s31),
                            RKH_STATE_CAST(&s3),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, compositeToCompositeFromHighToLowLevel)
{
    expectedState = RKH_STATE_CAST(&s2211);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS31_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr42_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS22_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS221_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS2211_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s31),
                            RKH_STATE_CAST(&s3),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, compositeToCompositeFromLowToHighLevel)
{
    expectedState = RKH_STATE_CAST(&s31);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS2211_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS221_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS22_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr43_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS3_Expect(RKH_CAST(SmTest, smTest), &evC);
    smTest_nS31_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s2211),
                            RKH_STATE_CAST(&s3),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, internalInSimpleState)
{
    expectedState = RKH_STATE_CAST(&s1);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_tr14_Expect(RKH_CAST(SmTest, smTest), &evB);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, internalInCompositeState)
{
    expectedState = RKH_STATE_CAST(&s31);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_tr15_Expect(RKH_CAST(SmTest, smTest), &evE);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s31),
                            RKH_STATE_CAST(&s3),
                            expectedState,
                            INIT_STATE_MACHINE);

    rkh_sm_dispatch((RKH_SM_T *)smTest, &evE);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
}

TEST(trnWoutUnitrazer, fails_EventNotFound)
{
    expectedState = RKH_STATE_CAST(&s1);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evE);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_NFOUND, result);
}

TEST(trnWoutUnitrazer, fails_GuardFalseOnInternalTrn)
{
    expectedState = RKH_STATE_CAST(&s1);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_falseGuard_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evC, 
                                      RKH_FALSE);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evC);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_NFOUND, result);
}

TEST(trnWoutUnitrazer, fails_GuardFalseOnExternalTrn)
{
    expectedState = RKH_STATE_CAST(&s1);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_falseGuard_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evD, 
                                      RKH_FALSE);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s1),
                            RKH_STATE_CAST(&s1),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evD);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_NFOUND, result);
}

TEST(trnWoutUnitrazer, fails_ExceededHierarchicalLevel)
{
    expectedState = RKH_STATE_CAST(&s0);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s0),
                            expectedState,
                            INIT_STATE_MACHINE);
    rkh_assert_Expect("rkhsm", 0);
    rkh_assert_IgnoreArg_line();

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evE);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EX_HLEVEL, result);
}

TEST(trnWoutUnitrazer, multipleEnabledTrn_FiringFirstTrueGuard)
{
    expectedState = RKH_STATE_CAST(&s4);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_guard4a_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evA, RKH_FALSE);
    smTest_guard4b_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evA, RKH_TRUE);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s4),
                            RKH_STATE_CAST(&s4),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evA);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, multipleEnabledTrn_FiringFirstEmptyGuard)
{
    expectedState = RKH_STATE_CAST(&s4);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_guard4a_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evB, RKH_FALSE);
    smTest_guard4b_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evB, RKH_FALSE);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s4),
                            RKH_STATE_CAST(&s4),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evB);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, defaultTrnWithAssociatedEffect)
{
    expectedState = RKH_STATE_CAST(&s31);

    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS0_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr55_Expect(RKH_CAST(SmTest, smTest), &evF);
    smTest_nS3_Expect(RKH_CAST(SmTest, smTest));
    smTest_iS3_Expect(RKH_CAST(SmTest, smTest), &evF);
    smTest_nS31_Expect(RKH_CAST(SmTest, smTest));
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s0),
                            RKH_STATE_CAST(&s0),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evF);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, generatedCompletionEventBySimpleState)
{
    expectedState = RKH_STATE_CAST(&s4);

    /* Expectations for transition to s5 */
    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_nS5_Expect(RKH_CAST(SmTest, smTest));
    /* Expectations for completion transition */
    smTest_xS5_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr61_Expect(RKH_CAST(SmTest, smTest), &evCompletion);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s2),
                            expectedState,
                            INIT_STATE_MACHINE);

    result = rkh_sm_dispatch((RKH_SM_T *)smTest, &evE);

    TEST_ASSERT_TRUE(expectedState == getState(smTest));
    TEST_ASSERT_EQUAL(RKH_EVT_PROC, result);
}

TEST(trnWoutUnitrazer, generatedCompletionEventByFinalState)
{
    expectedState = RKH_STATE_CAST(&s4);

    /* Expectations for transition to S2's FinalState */
    smTest_init_Expect(RKH_CAST(SmTest, smTest), (RKH_EVT_T *)&evCreation);
    smTest_xS21_Expect(RKH_CAST(SmTest, smTest));
    /* Expectations for completion transition */
    smTest_guardS2_ExpectAndReturn(RKH_CAST(SmTest, smTest), &evCompletion, 
                                   RKH_TRUE);
    smTest_xS2_Expect(RKH_CAST(SmTest, smTest));
    smTest_tr60_Expect(RKH_CAST(SmTest, smTest), &evCompletion);
    setProfileWoutUnitrazer(smTest,
                            RKH_STATE_CAST(&s21),
                            RKH_STATE_CAST(&s21),
                            expectedState,
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
