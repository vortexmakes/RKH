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
#include "rkh.h"
#include "common.h"
#include "smTest.h"
#include "smTestAct.h"

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
TEST_GROUP(transition);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(transition)
{
    sm_init();

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
    RKH_TR_FWK_SIG(A);
    RKH_TR_FWK_SIG(B);
    RKH_TR_FWK_SIG(C);
    RKH_TR_FWK_SIG(D);
    RKH_TR_FWK_SIG(E);

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

    rkh_sma_init_hsm(smTest);

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

    setProfile(smTest, RKH_STATE_CAST(&s0), RKH_STATE_CAST(&s0), 
               targetStates,
               entryStates, exitStates, RKH_STATE_CAST(&s1), 1,
               TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evA);

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

    setProfile(smTest, RKH_STATE_CAST(&s0), RKH_STATE_CAST(&s0), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s21), 1, 
               TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evB);

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

    setProfile(smTest, RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s21), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s0), 1, 
               TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evB);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, simpleToCompositeAtEqualLevel)
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

    setProfile(smTest, RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s21), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s0), 1, 
               TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evB);

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

    setProfile(smTest, RKH_STATE_CAST(&s0), RKH_STATE_CAST(&s0), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s2211), 1, 
               TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evD);

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

    setProfile(smTest, RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s21), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s21), 1, 
               TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evC);

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

    setProfile(smTest, RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s2), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s0), 1, 
               TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evA);

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

    setProfile(smTest, RKH_STATE_CAST(&s21), RKH_STATE_CAST(&s2), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s21), 1, 
               TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evD);

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

    setProfile(smTest, RKH_STATE_CAST(&s1), RKH_STATE_CAST(&s1), 
               targetStates, 
               entryStates, exitStates, RKH_STATE_CAST(&s1), 1, 
               TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evA);

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

    setProfile(smTest, RKH_STATE_CAST(&s31), RKH_STATE_CAST(&s31), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s31), 1, TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evD);

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

    setProfile(smTest, RKH_STATE_CAST(&s31), RKH_STATE_CAST(&s3), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s31), 1, TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evA);

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

    setProfile(smTest, RKH_STATE_CAST(&s2211), RKH_STATE_CAST(&s22), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s2211), 1, TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evD);

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

    setProfile(smTest, RKH_STATE_CAST(&s221), RKH_STATE_CAST(&s22), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s0), 1, TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evB);

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

    setProfile(smTest, RKH_STATE_CAST(&s31), RKH_STATE_CAST(&s3), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s21), 1, TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evB);

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

    setProfile(smTest, RKH_STATE_CAST(&s31), RKH_STATE_CAST(&s3), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s2211), 1, TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evC);

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

    setProfile(smTest, RKH_STATE_CAST(&s221), RKH_STATE_CAST(&s22), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s31), 1, TRN_NOT_INTERNAL);

    rkh_sma_dispatch(smTest, &evC);

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

    setProfile(smTest, RKH_STATE_CAST(&s1), RKH_STATE_CAST(&s1), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s1), 1, TRN_INTERNAL);

    rkh_sma_dispatch(smTest, &evB);

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

    setProfile(smTest, RKH_STATE_CAST(&s31), RKH_STATE_CAST(&s3), 
               targetStates, entryStates, exitStates, 
               RKH_STATE_CAST(&s31), 1, TRN_INTERNAL);

    rkh_sma_dispatch(smTest, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, fails_EventNotFound)
{
    UtrzProcessOut *p;

	sm_init_expect(RKH_STATE_CAST(&waiting));
	sm_enstate_expect(RKH_STATE_CAST(&waiting));
	sm_evtNotFound_expect(D);

    rkh_sma_init_hsm(smTest);
    setStateForcesfully(smTest, RKH_STATE_CAST(&s1));
    rkh_sma_dispatch(smTest, &evD);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, fails_GuardFalse)
{
    UtrzProcessOut *p;

	sm_init_expect(RKH_STATE_CAST(&waiting));
	sm_enstate_expect(RKH_STATE_CAST(&waiting));
	sm_trn_expect(RKH_STATE_CAST(&s1), RKH_STATE_CAST(&s1));
	sm_grdFalse_expect();

    rkh_sma_init_hsm(smTest);
    setStateForcesfully(smTest, RKH_STATE_CAST(&s1));
    rkh_sma_dispatch(smTest, &evC);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

TEST(transition, fails_ExceededHierarchicalLevel)
{
    UtrzProcessOut *p;

	sm_init_expect(RKH_STATE_CAST(&waiting));
	sm_enstate_expect(RKH_STATE_CAST(&waiting));
	sm_trn_expect(RKH_STATE_CAST(&s0), RKH_STATE_CAST(&s22211));
    sm_tsState_expect(RKH_STATE_CAST(&s22211));
	sm_exHLevel_expect();

    rkh_sma_init_hsm(smTest);
    setStateForcesfully(smTest, RKH_STATE_CAST(&s0));
    rkh_sma_dispatch(smTest, &evE);

    p = unitrazer_getLastOut();
    TEST_ASSERT_EQUAL(UT_PROC_SUCCESS, p->status);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
