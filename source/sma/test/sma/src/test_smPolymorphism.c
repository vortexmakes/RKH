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
 *  \file       test_smPolymorphism.c
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
#include "rkhsma.h"
#include "smPolymorphism.h"
#include "Mock_rkhqueue.h"
#include "Mockrkhsm.h"
#include "Mockrkhtrc.h"
#include "Mock_rkhport.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
TEST_GROUP(polymorphism);

/* ---------------------------- Local variables ---------------------------- */
static RKH_EVT_T event = {0, 0, 0};                                       

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
static void
checkVtbl(RKH_SMA_T *me, RKHActivate activate, RKHTask task, 
          RKHPostFifo postFifo, RKHPostLifo postLifo)
{
    TEST_ASSERT_EQUAL_PTR(activate, me->vptr->activate);
    TEST_ASSERT_EQUAL_PTR(task, me->vptr->task);
    TEST_ASSERT_EQUAL_PTR(postFifo, me->vptr->post_fifo);
    TEST_ASSERT_EQUAL_PTR(postLifo, me->vptr->post_lifo);
}

static void
testActivate(RKH_SMA_T *me, const RKH_EVT_T **qSto, RKH_QUENE_T qSize,
             void *stkSto, rui32_t stkSize)
{
    (void)me;
    (void)qSto;
    (void)qSize;
    (void)stkSto;
    (void)stkSize;
}

static void
testTask(RKH_SMA_T *me, void *arg)
{
    (void)me;
    (void)arg;
}

static void
testPostFifo(RKH_SMA_T *me, const RKH_EVT_T *e, const void *const sender)
{
    (void)me;
    (void)e;
    (void)sender;
}

static void
testPostLifo(RKH_SMA_T *me, const RKH_EVT_T *e, const void *const sender)
{
    (void)me;
    (void)e;
    (void)sender;
}
#endif

/* ---------------------------- Global functions --------------------------- */
TEST_SETUP(polymorphism)
{
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    /* Restore the default virtual table of RKH_SMA_T class */
    singleton->vptr = &rkhSmaVtbl;
#endif
    memset(rkh_sptbl, 0, sizeof(rkh_sptbl));
}

TEST_TEAR_DOWN(polymorphism)
{
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
#endif
}

/**
 *  \addtogroup test_smPolymorphism Polymorphism test group
 *  @{
 *  \name Test cases of polimorphism group
 *  @{
 */

TEST(polymorphism, defaultVirtualFunctions)
{
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    checkVtbl(singleton, 
              rkh_sma_activate, NULL, rkh_sma_post_fifo, rkh_sma_post_lifo);

    TEST_ASSERT_EQUAL_PTR(&rkhSmaVtbl, singleton->vptr);
#endif
}

TEST(polymorphism, callVirtualFunction)
{
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    const RKH_EVT_T *qs[1];

    rkh_queue_init_Ignore();   /* for RKH_SMA_ACTIVATE() */
    rkh_enter_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_REG, RKH_FALSE);
    rkh_exit_critical_Expect();
    rkh_sm_init_Ignore();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_ACT, RKH_FALSE);

    rkh_enter_critical_Expect();
    rkh_queue_put_fifo_Ignore();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_FIFO, RKH_FALSE);
    rkh_exit_critical_Expect();

    rkh_enter_critical_Expect();
    rkh_queue_put_lifo_Ignore();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_LIFO, RKH_FALSE);
    rkh_exit_critical_Expect();

    RKH_SMA_ACTIVATE(singleton, qs, 1, 0, 0);
    RKH_SMA_POST_FIFO(singleton, &event, NULL);
    RKH_SMA_POST_LIFO(singleton, &event, NULL);
#endif
}

TEST(polymorphism, setVirtualTable)
{
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    const RKHSmaVtbl *vptr;
    static const RKHSmaVtbl vtbl =
    {
        testActivate, testTask, testPostFifo, testPostLifo
    };

    vptr = singleton->vptr = &vtbl;

    checkVtbl(singleton, 
              testActivate, testTask, testPostFifo, testPostLifo);
#endif
}

TEST(polymorphism, runtimeSingletonAOCtor)
{
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    rkh_sm_ctor_Expect(&singleton->sm);

    Singleton_ctor(8);
    TEST_ASSERT_EQUAL(8, Singleton_getFoo());

    RKH_SMA_ACTIVATE(singleton, NULL, 0, NULL, 0);
    TEST_ASSERT_EQUAL(0, Singleton_getFoo());
#endif
}

TEST(polymorphism, runtimeMultipleAOCtorWithVtblForObj)
{
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    rkh_sm_ctor_Ignore();
    rkh_sm_ctor_Ignore();

    Multiple_ctor(multA, 2, Multiple_postFifoA);
    Multiple_ctor(multB, 4, Multiple_postFifoB);

    checkVtbl((RKH_SMA_T *)multA, 
              rkh_sma_activate, NULL, Multiple_postFifoA, rkh_sma_post_lifo);

    TEST_ASSERT_EQUAL(2, Multiple_getFoobar(multA));
    TEST_ASSERT_EQUAL(4, Multiple_getFoobar(multB));

    RKH_SMA_POST_FIFO((RKH_SMA_T *)multA, NULL, NULL);
    RKH_SMA_POST_FIFO((RKH_SMA_T *)multB, NULL, NULL);

    TEST_ASSERT_EQUAL(0, Multiple_getFoobar(multA));
    TEST_ASSERT_EQUAL(8, Multiple_getFoobar(multB));
#endif
}

TEST(polymorphism, runtimeMultipleAOCtorWithVtblForType)
{
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    Command_ctor(cmdSignal, 128); 
    Command_ctor(cmdRegister, 64); 

    checkVtbl((RKH_SMA_T *)cmdSignal, 
              rkh_sma_activate, Command_task, 
              Command_postFifo, Command_postLifo);

    checkVtbl((RKH_SMA_T *)cmdRegister, 
              rkh_sma_activate, Command_task, 
              Command_postFifo, Command_postLifo);
#endif
}

TEST(polymorphism, runtimeSubObjectCtorOfSMAAndSM)
{
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    CallControl_ctorA(16);

    TEST_ASSERT_EQUAL(16, CallControl_getFoo());
    checkVtbl((RKH_SMA_T *)theCallControl, 
              CallControl_activate, CallControl_task, 
              rkh_sma_post_fifo, rkh_sma_post_lifo);
#endif
}

TEST(polymorphism, runtimeSubObjectCtorOfSMAAndSMWithDefaultVtbl)
{
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    CallControl_ctorB(8);

    TEST_ASSERT_EQUAL(8, CallControl_getFoo());
    checkVtbl((RKH_SMA_T *)theCallControl, 
              rkh_sma_activate, NULL, 
              rkh_sma_post_fifo, rkh_sma_post_lifo);
#endif
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
