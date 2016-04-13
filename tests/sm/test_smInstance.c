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
 *  \file       test_smInstance.c
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
#include "MocksmTestAct.h"
#include "smInstance.h"

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
typedef struct Composite
{
    RKH_SMA_T ao;
    int foo;
    RKH_SM_T itsReactivePart;
} Composite;

/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(instance);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(instance)
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

TEST_TEAR_DOWN(instance)
{
    sm_verify(); /* Makes sure there are no unused expectations, if */
                 /* there are, this function causes the test to fail. */
    sm_cleanup();
    MocksmTestAct_Verify();
    MocksmTestAct_Destroy();
}

/**
 *  \addtogroup test_smInstance Instance test group
 *  @{
 *  \name Test cases of instance group
 *  @{ 
 */

TEST(instance, accessingToStateMachineInternals)
{
    RKHROM RKH_ROM_T *pConstSM = RKH_SM_GET_CONST(smTest);

    TEST_ASSERT_EQUAL_PTR(smTest->sm.romrkh, pConstSM);
    TEST_ASSERT_EQUAL(0, pConstSM->prio);
    TEST_ASSERT_EQUAL(HCAL, pConstSM->ppty);
    TEST_ASSERT_EQUAL_STRING("smTest", pConstSM->name);
    TEST_ASSERT_EQUAL_PTR(&waiting, pConstSM->istate);
    TEST_ASSERT_EQUAL_PTR(smTest_init, pConstSM->iaction);
}

TEST(instance, hidingActiveObjectInternals)
{
    RKH_SMA_CREATE(SmTest, smTestA, 0, HCAL, &waiting, smTest_init, NULL);
    RKH_SMA_DEF_PTR(smTestA);

    TEST_ASSERT_EQUAL(0, ((SmTest *)smTestA)->foo);
}

TEST(instance, publishingActiveObjectInternals)
{
    RKH_SMA_CREATE(SmTest, smTestA, 0, HCAL, &waiting, smTest_init, NULL);
    RKH_SMA_DEF_PTR_TYPE(SmTest, smTestA);

    TEST_ASSERT_EQUAL(0, smTestA->foo);
}

TEST(instance, staticInstantiationOfCompositeActiveObject)
{
    RKH_SMA_CREATE(Composite, composite, 0, HCAL, &waiting, NULL, NULL);
    RKH_SMA_DEF_PTR_TYPE(Composite, composite);
    RKH_SM_CONST_CREATE(itsReactivePart, 2, HCAL, &s0, NULL, NULL);
    RKH_SM_INIT(&composite->itsReactivePart, itsReactivePart);

    RKH_FILTER_OFF_SMA(&composite->itsReactivePart);
	sm_init_expect(RKH_STATE_CAST(&s0));
	sm_enstate_expect(RKH_STATE_CAST(&s0));
    smTest_nS0_Expect(RKH_CAST(RKH_SM_T, &composite->itsReactivePart));

    rkh_sm_init((RKH_SM_T *)&composite->itsReactivePart);
}

TEST(instance, dynamicInstantiationOfCompositeActiveObject)
{
    RKH_SM_CONST_CREATE(itsReactivePart, 2, HCAL, &s0, NULL, NULL);
    RKH_SM_CONST_CREATE(composite, 0, HCAL, &waiting, NULL, NULL);

    /* ----------------------- Composite constructor ----------------------- */
    Composite *pCmp = (Composite *)malloc(sizeof(Composite));
    TEST_ASSERT_NOT_NULL(pCmp);

    /* Initialize its state machine object */
    RKH_SM_INIT(pCmp, composite);

    TEST_ASSERT_EQUAL_PTR(RKH_SM_GET_CONST_OBJ(composite), 
                          pCmp->ao.sm.romrkh);
    TEST_ASSERT_EQUAL_PTR(&waiting, pCmp->ao.sm.state);

    /* and its (reactive) part */
    RKH_SM_INIT(&pCmp->itsReactivePart, itsReactivePart);

    TEST_ASSERT_EQUAL_PTR(RKH_SM_GET_CONST_OBJ(itsReactivePart), 
                          pCmp->itsReactivePart.romrkh);
    TEST_ASSERT_EQUAL_PTR(&s0, pCmp->itsReactivePart.state);

    free(pCmp);
}

TEST(instance, staticPrivateAOConstructor)
{
    RKHROM RKH_ROM_T *pConstSM = RKH_SM_GET_CONST(single);
    Single_ctor(4);

    TEST_ASSERT_EQUAL_STRING("single", pConstSM->name);
    TEST_ASSERT_EQUAL(4, Single_getFoo());
}

TEST(instance, staticPublicAOConstructor)
{
    RKHROM RKH_ROM_T *pConstSM = RKH_SM_GET_CONST(publicSingle);
    PublicSingle_ctor(8);

    TEST_ASSERT_EQUAL_STRING("publicSingle", pConstSM->name);
    TEST_ASSERT_EQUAL(8, publicSingle->foo);
}

TEST(instance, staticOpaqueAOConstructor)
{
    Opaque_ctor(opaque, 4);

    TEST_ASSERT_EQUAL(4, Opaque_getFoo(opaque));
}

TEST(instance, multipleStaticAOConstructor)
{
    RKHROM RKH_ROM_T *pConstSM = RKH_SM_GET_CONST(single0);
    MultiplePublicSingle_ctor(single0, 8);

    TEST_ASSERT_EQUAL_STRING("single0", pConstSM->name);
    TEST_ASSERT_EQUAL(8, single0->foo);
}

TEST(instance, arrayOfStaticAO)
{
    PublicSingle *pSingle = RKH_ARRAY_SMA(arrayOfSingles, 2);
    RKHROM RKH_ROM_T *pConstSM = RKH_SM_GET_CONST(pSingle);
    MultiplePublicSingle_ctor(pSingle, 8);

    TEST_ASSERT_EQUAL_STRING("single2", pConstSM->name);
    TEST_ASSERT_EQUAL(8, pSingle->foo);
}

TEST(instance, stateMachineRegardlessOfAO)
{
#if 0
    RKH_SM_CREATE(StateMachine, stateMachineA, 4, HCAL, &waiting, 
                  smTest_init, NULL);
    RKH_SM_DEF_PTR(stateMachineA);
    RKHROM RKH_ROM_T *pConstSMA = RKH_SM_GET_CONST(stateMachineA);

    TEST_ASSERT_EQUAL(4, pConstSMA->prio);
    TEST_ASSERT_EQUAL(HCAL, pConstSMA->ppty);
    TEST_ASSERT_EQUAL_STRING("stateMachineA", pConstSMA->name);
    TEST_ASSERT_EQUAL_PTR(&waiting, pConstSMA->istate);
    TEST_ASSERT_EQUAL_PTR(smTest_init, pConstSMA->iaction);
    TEST_ASSERT_EQUAL_PTR(&waiting, stateMachineA->state);
    TEST_ASSERT_EQUAL(0, ((StateMachine *)stateMachineA)->foo);
#endif
}

TEST(instance, hidingStateMachineInternals)
{
    RKHROM RKH_ROM_T *pConstSM = RKH_SM_GET_CONST(stateMachine);

    TEST_ASSERT_EQUAL_STRING("stateMachine", pConstSM->name);
    TEST_ASSERT_EQUAL_PTR(NULL, stateMachine->state);
}

TEST(instance, publishingStateMachineInternals)
{
#if 0
    RKH_SM_CREATE(StateMachine, stateMachineA, 4, HCAL, NULL, NULL, NULL);
    RKH_SM_DEF_PTR_TYPE(StateMachine, stateMachineA);
    RKHROM RKH_ROM_T *pConstSMA = ((RKH_SM_T *)stateMachineA)->romrkh;

    TEST_ASSERT_EQUAL_STRING("stateMachineA", pConstSMA->name);
    TEST_ASSERT_EQUAL_PTR(&waiting, ((RKH_SM_T *)stateMachineA)->state);
    TEST_ASSERT_EQUAL(0, stateMachineA->foo);
#endif
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
