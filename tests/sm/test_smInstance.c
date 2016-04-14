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

TEST(instance, staticPrivateAOConstructor)
{
    RKHROM RKH_ROM_T *pConstSM = RKH_SM_GET_CONST(single);
    Single_ctor(4);

    TEST_ASSERT_EQUAL_STRING("single", pConstSM->name);
    TEST_ASSERT_EQUAL(4, Single_getFoo());
}

TEST(instance, staticPublicAO)
{
    RKHROM RKH_ROM_T *pConstSM = RKH_SM_GET_CONST(publicSingle);

    publicSingle->foo = 8;
    TEST_ASSERT_EQUAL_STRING("publicSingle", pConstSM->name);
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

TEST(instance, staticMultipleAOConstructor)
{
    RKHROM RKH_ROM_T *pConstSM = RKH_SM_GET_CONST(single0);
    MultiplePublicSingle_ctor(single0, 8);

    TEST_ASSERT_EQUAL_STRING("single0", pConstSM->name);
    TEST_ASSERT_EQUAL(8, single0->foo);
}

TEST(instance, staticArrayOfAO)
{
    PublicSingle *pSingle = RKH_ARRAY_SMA(arrayOfSingles, 2);
    RKHROM RKH_ROM_T *pConstSM = RKH_SM_GET_CONST(pSingle);
    MultiplePublicSingle_ctor(pSingle, 8);

    TEST_ASSERT_EQUAL_STRING("single2", pConstSM->name);
    TEST_ASSERT_EQUAL(8, pSingle->foo);
}

TEST(instance, staticPrivateStateMachine)
{
    RKHROM RKH_ROM_T *pConstSM = RKH_SM_GET_CONST(stateMachine);

    TEST_ASSERT_EQUAL_STRING("stateMachine", pConstSM->name);
    TEST_ASSERT_EQUAL_PTR(NULL, stateMachine->state);
}

TEST(instance, staticPublicStateMachine)
{
    RKHROM RKH_ROM_T *pConstSM = RKH_SM_GET_CONST(publicStateMachine);

    TEST_ASSERT_EQUAL_STRING("publicStateMachine", pConstSM->name);
    TEST_ASSERT_EQUAL(8, publicSingle->foo);
}

TEST(instance, staticCompositeAOPrivateSingletonConstructor)
{
    RKHROM RKH_ROM_T *pConstCompSM, *pConstPartSM; 

    Composite_ctor(16);
    pConstCompSM = RKH_SM_GET_CONST(composite);
    pConstPartSM = RKH_SM_GET_CONST(Composite_getItsReactivePart());

    TEST_ASSERT_EQUAL_STRING("composite", pConstCompSM->name);
    TEST_ASSERT_EQUAL_STRING("region", pConstPartSM->name);
    TEST_ASSERT_EQUAL(16, Composite_getFoo());
}

TEST(instance, staticCompositeAOPublicConstructor)
{
    RKHROM RKH_ROM_T *pConstCompSM, *pConstPartSM; 

    PublicComposite_ctor(publicComposite, 16);
    pConstCompSM = RKH_SM_GET_CONST(publicComposite);
    pConstPartSM = RKH_SM_GET_CONST(&publicComposite->itsReactivePart);

    TEST_ASSERT_EQUAL_STRING("publicComposite", pConstCompSM->name);
    TEST_ASSERT_EQUAL_STRING("publicRegion", pConstPartSM->name);
    TEST_ASSERT_EQUAL(16, publicComposite->foo);
}

TEST(instance, staticCompositeAOWithDerivedSMPublicConstructor)
{
    RKHROM RKH_ROM_T *pConstCompSM, *pConstPartSM; 

    PublicCompositeA_ctor(publicCompositeA, 16, 8);
    pConstCompSM = RKH_SM_GET_CONST(publicCompositeA);
    pConstPartSM = RKH_SM_GET_CONST(&publicCompositeA->itsReactivePart);

    TEST_ASSERT_EQUAL_STRING("publicCompositeA", pConstCompSM->name);
    TEST_ASSERT_EQUAL_STRING("publicRegionA", pConstPartSM->name);
    TEST_ASSERT_EQUAL(16, publicCompositeA->foo);
    TEST_ASSERT_EQUAL(8, publicCompositeA->itsReactivePart.foo);
}

TEST(instance, dynamicInstantiationOfCompositeActiveObject)
{
#if 0
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
#endif
}

TEST(instance, syncDispatchingToStateMachine)
{
#if 0
    RKH_FILTER_OFF_SMA(&composite->itsReactivePart);
	sm_init_expect(RKH_STATE_CAST(&s0));
	sm_enstate_expect(RKH_STATE_CAST(&s0));
    smTest_nS0_Expect(RKH_CAST(RKH_SM_T, &composite->itsReactivePart));

    rkh_sm_init((RKH_SM_T *)&composite->itsReactivePart);
#endif
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
