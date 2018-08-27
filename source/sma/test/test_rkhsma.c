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
 *  \file       test_rkhsma.c
 *  \ingroup    test_sma
 *  \brief      Unit test for sma module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_sma SMA
 *  @{
 *  \brief      Unit test for sma module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.05  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity.h"
#include "rkhsma.h"
#include "smTest.h"
#include "smInstance.h"
#include "Mock_rkhport.h"
#include "Mock_rkhtrc.h"
#include "Mock_rkhtrc_record.h"
#include "Mock_rkhtrc_filter.h"
#include "Mock_rkhsm.h"
#include "Mock_rkhqueue.h"
#include "Mock_rkhassert.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKHROM RKH_ROM_T base = {0, 0, "receiver"};
static RKH_SMA_T receiver;
const RKH_TRC_FIL_T fsma = {0, NULL};   /* Fake global variable of trace */
                                        /* module (using for mocking) */
const RKH_TRC_FIL_T fsig = {0, NULL};
static RKH_EVT_T event = {0, 0, 0};                                       

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ============================= SMA test group ============================ */
void
setUp(void)
{
    receiver.sm.romrkh = &base;
    Mock_rkhtrc_filter_Init();
}

void
tearDown(void)
{
    Mock_rkhtrc_filter_Verify();
    Mock_rkhtrc_filter_Destroy();
}

/**
 *  \addtogroup test_rkhsma Active object (SMA) test group
 *  @{
 *  \name Test cases of active object test group
 *  @{ 
 */
void
test_Register(void)
{
    rkh_enter_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_REG, RKH_FALSE);
    rkh_exit_critical_Expect();

    rkh_sma_register(&receiver);
    TEST_ASSERT_EQUAL(&receiver, rkh_sptbl[receiver.sm.romrkh->prio]);
}

void
test_UnRegister(void)
{
    rkh_enter_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_UNREG, RKH_FALSE);
    rkh_exit_critical_Expect();

    rkh_sma_unregister(&receiver);
    TEST_ASSERT_EQUAL((RKH_SMA_T *)0, rkh_sptbl[receiver.sm.romrkh->prio]);
}

void
test_Constructor(void)
{
    rkh_sm_ctor_Expect(&(receiver.sm));

    rkh_sma_ctor(&receiver, (const RKHSmaVtbl *)0);
}

void
test_TerminateOneRegisteredAO(void)
{
    rkh_enter_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_REG, RKH_FALSE);
    rkh_exit_critical_Expect();

    rkh_sma_register(&receiver);

    rkh_enter_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_UNREG, RKH_FALSE);
    rkh_exit_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_TERM, RKH_FALSE);

    rkh_sma_terminate(&receiver);

    TEST_ASSERT_EQUAL((RKH_SMA_T *)0, rkh_sptbl[receiver.sm.romrkh->prio]);
}

void
test_ActivateOneAO(void)
{
    char *buff;

    rkh_queue_init_Expect(&receiver.equeue, (const void **)&buff, 16, 
                          &receiver);

    rkh_enter_critical_Expect();
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_REG, RKH_FALSE);
    rkh_exit_critical_Expect();

    rkh_sm_init_Expect((RKH_SM_T *)&receiver);

    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_ACT, RKH_FALSE);

    rkh_sma_activate(&receiver, (const RKH_EVT_T **)&buff, 16, NULL, 0);
}

void
test_PostFifo(void)
{
    rkh_enter_critical_Expect();
    rkh_queue_put_fifo_Expect(&receiver.equeue, &event);
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_FIFO, RKH_FALSE);
    rkh_exit_critical_Expect();

    rkh_sma_post_fifo(&receiver, &event, &receiver);
}

void
test_PostLifo(void)
{
    rkh_enter_critical_Expect();
    rkh_queue_put_lifo_Expect(&receiver.equeue, &event);
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_LIFO, RKH_FALSE);
    rkh_exit_critical_Expect();

    rkh_sma_post_lifo(&receiver, &event, &receiver);
}

void
test_Get(void)
{
    RKH_EVT_T *e;

    rkh_queue_get_ExpectAndReturn(&receiver.equeue, &event);
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_GET, RKH_FALSE);

    e = rkh_sma_get(&receiver);
    TEST_ASSERT_EQUAL(&event, e);
}

void
test_Defer(void)
{
    rkh_enter_critical_Expect();
    rkh_queue_put_fifo_Expect(&receiver.equeue, &event);
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_SMA_DEFER, RKH_FALSE);
    rkh_exit_critical_Expect();

    rkh_sma_defer(&receiver.equeue, &event);
}

void
test_Recall(void)
{
    RKH_EVT_T *e;

    rkh_queue_get_ExpectAndReturn(&receiver.equeue, NULL);

    e = rkh_sma_recall(&receiver, &receiver.equeue);
    TEST_ASSERT_EQUAL(NULL, e);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/* ------------------------------ End of file ------------------------------ */
