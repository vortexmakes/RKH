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
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity_fixture.h"
#include "rkhsma.h"
#include "smTest.h"
#include "smInstance.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(instance);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(instance)
{
}

TEST_TEAR_DOWN(instance)
{
}

/**
 *  \addtogroup test_smInstance Instance test group
 *  @{
 *  \name Test cases of instance group
 *  @{ 
 */

TEST(instance, ctorOfStaticPrivateAO)
{
    Single_ctor(4);

    TEST_ASSERT_EQUAL_STRING("single", RKH_SMA_ACCESS_CONST(single, name));
    TEST_ASSERT_EQUAL(4, Single_getFoo());
}

TEST(instance, staticPublicAOWithoutRuntimeCtor)
{
    publicSingle->foo = 8;
    TEST_ASSERT_EQUAL_STRING("publicSingle", 
                             RKH_SMA_ACCESS_CONST(publicSingle, name));
}

TEST(instance, ctorOfStaticPublicAO)
{
    PublicSingle_ctor(8);

    TEST_ASSERT_EQUAL_STRING("publicSingle", 
                             RKH_SMA_ACCESS_CONST(publicSingle, name));
    TEST_ASSERT_EQUAL(8, publicSingle->foo);
}

TEST(instance, ctorOfStaticOpaqueAO)
{
    Opaque_ctor(opaque, 4);

    TEST_ASSERT_EQUAL(4, Opaque_getFoo(opaque));
}

TEST(instance, ctorOfStaticMultipleAO)
{
    MultiplePublicSingle_ctor(single0, 8);

    TEST_ASSERT_EQUAL_STRING("single0", 
                             RKH_SMA_ACCESS_CONST(single0, name));
    TEST_ASSERT_EQUAL(8, single0->foo);
}

TEST(instance, ctorOfStaticArrayOfAO)
{
    PublicSingle *pSingle = RKH_ARRAY_SMA(arrayOfSingles, 2);
    MultiplePublicSingle_ctor(pSingle, 8);

    TEST_ASSERT_EQUAL_STRING("single2", 
                             RKH_SMA_ACCESS_CONST(pSingle, name));
    TEST_ASSERT_EQUAL(8, pSingle->foo);
}

TEST(instance, staticPrivateSMWithoutRuntimeCtor)
{
    TEST_ASSERT_EQUAL_STRING("stateMachine", 
                             RKH_SMA_ACCESS_CONST(stateMachine, name));
    TEST_ASSERT_EQUAL_PTR(NULL, stateMachine->state);
}

TEST(instance, staticPublicSMWithoutRuntimeCtor)
{
    TEST_ASSERT_EQUAL_STRING("publicStateMachine", 
                             RKH_SMA_ACCESS_CONST(publicStateMachine, name));
    TEST_ASSERT_EQUAL(8, publicSingle->foo);
}

TEST(instance, ctorOfStaticCompositePrivateSingletonAO)
{
    Composite_ctor(16);

    TEST_ASSERT_EQUAL_STRING("composite", 
                             RKH_SMA_ACCESS_CONST(composite, name));
    TEST_ASSERT_EQUAL_STRING("region", 
                 RKH_SMA_ACCESS_CONST(Composite_getItsReactivePart(), name));
    TEST_ASSERT_EQUAL(16, Composite_getFoo());
}

TEST(instance, ctorOfStaticCompositePublicAO)
{
    PublicComposite_ctor(publicComposite, 16);

    TEST_ASSERT_EQUAL_STRING("publicComposite", 
                             RKH_SMA_ACCESS_CONST(publicComposite, name));
    TEST_ASSERT_EQUAL_STRING("publicRegion", 
             RKH_SMA_ACCESS_CONST(&publicComposite->itsReactivePart, name));
    TEST_ASSERT_EQUAL(16, publicComposite->foo);
}

TEST(instance, ctorOfStaticCompositeAOWithDerivedPublicSM)
{
    PublicCompositeA_ctor(publicCompositeA, 16, 8);

    TEST_ASSERT_EQUAL_STRING("publicCompositeA", 
                             RKH_SMA_ACCESS_CONST(publicCompositeA, name));
    TEST_ASSERT_EQUAL_STRING("publicRegionA", 
             RKH_SMA_ACCESS_CONST(&publicCompositeA->itsReactivePart, name));
    TEST_ASSERT_EQUAL(16, publicCompositeA->foo);
    TEST_ASSERT_EQUAL(8, publicCompositeA->itsReactivePart.foo);
}

TEST(instance, ctorOfDynamicCompositeAO)
{
    PublicSingle *actObj;

    actObj = PublicSingle_dynCtor(8);
    TEST_ASSERT_NOT_NULL(actObj);
    TEST_ASSERT_EQUAL(8, actObj->foo);

    TEST_ASSERT_EQUAL_STRING("publicSingleDyn", 
                             RKH_SMA_ACCESS_CONST(actObj, name));

    PublicSingle_dynDtor(actObj);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
