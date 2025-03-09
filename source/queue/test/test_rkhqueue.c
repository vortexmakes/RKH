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
 *  \file       test_rkhqueue.c
 *  \ingroup    test_queue
 *  \brief      Unit test for software timer module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_queue Timer
 *  @{
 *  \brief      Unit test for event queue module.
 */

/* -------------------------- Development history -------------------------- */
/*
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhdef.h"
#include "rkhevt.h"
#include "rkhtrc_define.h"
#include "unity.h"
#include "rkhqueue.h"
#include "Mock_rkhtrc_record.h"
#include "Mock_rkhtrc_filter.h"
#include "Mock_rkhport.h"
#include "Mock_rkhassert.h"
#include "Mock_rkhsma.h"
#include "Mock_rkhfwk_hook.h"
#include "Mock_rkhfwk_dynevt.h"
#include "Mock_rkhfwk_cast.h"
#include "Mock_rkhsma_sync.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define STORAGE_SIZE    4

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_SMA_T ao;
static RKH_STATIC_EVENT(evt, 0xdc);
static RKH_STATIC_EVENT(evtL, 1);
static RKH_STATIC_EVENT(evtM, 2);
static RKH_STATIC_EVENT(evtH, 3);
static RKH_STATIC_EVENT(evtH1, 4);
static RKH_STATIC_EVENT(evtH2, 5);
static RKH_EVT_T* storage[STORAGE_SIZE];

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void 
MockAssertCallback(const char* const file, int line, int cmock_num_calls)
{
    TEST_PASS();
}

static void
priorityQueueOrderSetup(RKH_QUEUE_T *queue)
{
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_QUE_INIT, RKH_FALSE);

    rkh_enter_critical_Expect();
    rkh_exit_critical_Expect();

    rkh_sma_setReady_Expect(&ao);
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_QUE_FIFO, RKH_FALSE);

    rkh_sma_setReady_Expect(&ao);
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_QUE_FIFO, RKH_FALSE);

    rkh_sma_setReady_Expect(&ao);
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_QUE_FIFO, RKH_FALSE);

    rkh_enter_critical_Expect();
    rkh_sma_block_Expect(&ao);
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_QUE_GET, RKH_FALSE);
    rkh_exit_critical_Expect();

    evtL.priority = 2;
    evtM.priority = 1;
    evtH.priority = 0;
    rkh_queue_init(queue, RKH_CAST(const void*, storage), STORAGE_SIZE, &ao);
    rkh_queue_setType(queue, PriorityQueType);
}

static void
priorityQueueOrderTeardown(RKH_QUEUE_T *queue, RKH_EVT_T* event)
{
    TEST_ASSERT_EQUAL(0, event->priority);
    TEST_ASSERT_EQUAL(2, queue->qty);
    TEST_ASSERT_EQUAL(queue->pstart + 2, queue->pin);
}

/* ---------------------------- Global functions --------------------------- */
void 
setUp(void)
{
    Mock_rkhtrc_record_Init();
    Mock_rkhtrc_filter_Init();
    Mock_rkhport_Init();
    Mock_rkhassert_Init();
    Mock_rkhsma_Init();
    Mock_rkhfwk_hook_Init();
    Mock_rkhfwk_dynevt_Init();
    Mock_rkhfwk_cast_Init();
    Mock_rkhsma_sync_Init();
}

void 
tearDown(void)
{
    Mock_rkhtrc_record_Verify();
    Mock_rkhtrc_filter_Verify();
    Mock_rkhport_Verify();
    Mock_rkhassert_Verify();
    Mock_rkhsma_Verify();
    Mock_rkhfwk_hook_Verify();
    Mock_rkhfwk_dynevt_Verify();
    Mock_rkhfwk_cast_Verify();
    Mock_rkhsma_sync_Verify();
}

void
test_defaultValueOfTypeIsRegular(void)
{
    RKH_QUEUE_T queue;

    rkh_enter_critical_Ignore();
    rkh_trc_isoff__ExpectAndReturn(0, RKH_FALSE);
    rkh_trc_isoff__IgnoreArg_e();
    rkh_exit_critical_Ignore();

    rkh_queue_init(&queue, RKH_CAST(const void*, storage), STORAGE_SIZE, &ao);
    TEST_ASSERT_EQUAL(RegularQueType, queue.type);
}

void
test_setQueueType(void)
{
    RKH_QUEUE_T queue;

    rkh_enter_critical_Ignore();
    rkh_exit_critical_Ignore();

    rkh_queue_setType(&queue, PriorityQueType);
    TEST_ASSERT_EQUAL(PriorityQueType, queue.type);
}

void
test_avoidUsingPostLIFOForAPriorityQueue(void)
{
    RKH_QUEUE_T queue;

    rkh_enter_critical_Ignore();
    rkh_trc_isoff__ExpectAndReturn(0, RKH_FALSE);
    rkh_trc_isoff__IgnoreArg_e();
    rkh_exit_critical_Ignore();
    rkh_assert_Expect("rkhqueue", 0);
    rkh_assert_IgnoreArg_file();
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);

    rkh_queue_init(&queue, RKH_CAST(const void*, storage), STORAGE_SIZE, &ao);
    rkh_queue_setType(&queue, PriorityQueType);
    rkh_queue_put_lifo(&queue, &evt);
}

void
test_getAnElementFromARegularQueue(void)
{
    RKH_QUENE_T nElems;
    RKH_QUEUE_T queue;
    RKH_EVT_T* event;

    rkh_enter_critical_Ignore();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_exit_critical_Ignore();
    rkh_enter_critical_Ignore();
    rkh_exit_critical_Ignore();
    rkh_sma_setReady_Expect(&ao);
    rkh_enter_critical_Ignore();
    rkh_trc_isoff__IgnoreAndReturn(RKH_FALSE);
    rkh_exit_critical_Ignore();
    rkh_enter_critical_Ignore();
    rkh_exit_critical_Ignore();
    rkh_enter_critical_Ignore();
    rkh_sma_block_Expect(&ao);
    rkh_sma_setUnready_Expect(&ao);

    rkh_queue_init(&queue, RKH_CAST(const void*, storage), STORAGE_SIZE, &ao);
    nElems = rkh_queue_get_num(&queue);
    TEST_ASSERT_EQUAL(0, nElems);

    rkh_queue_put_fifo(&queue, &evt);
    nElems = rkh_queue_get_num(&queue);
    TEST_ASSERT_EQUAL(1, nElems);

    event = rkh_queue_get(&queue);
    TEST_ASSERT_EQUAL_PTR(&evt, event);
}



void
test_getAnElementFromAPriorityQueueTop(void)
{
    RKH_QUEUE_T queue;
    RKH_EVT_T* event;

    priorityQueueOrderSetup(&queue);
    rkh_queue_put_fifo(&queue, &evtH);
    rkh_queue_put_fifo(&queue, &evtL);
    rkh_queue_put_fifo(&queue, &evtM);

    event = rkh_queue_get(&queue);
    TEST_ASSERT_EQUAL_PTR(&evtH, event);
    TEST_ASSERT_EQUAL(&evtL, (RKH_QUEUE_T*)(*queue.pstart));
    TEST_ASSERT_EQUAL(&evtM, (RKH_QUEUE_T*)(*(queue.pstart + 1)));
    priorityQueueOrderTeardown(&queue, event);
}

void
test_getAnElementFromAPriorityQueueMiddle(void)
{
    RKH_QUEUE_T queue;
    RKH_EVT_T* event;

    priorityQueueOrderSetup(&queue);
    rkh_queue_put_fifo(&queue, &evtL);
    rkh_queue_put_fifo(&queue, &evtH);
    rkh_queue_put_fifo(&queue, &evtM);

    event = rkh_queue_get(&queue);
    TEST_ASSERT_EQUAL_PTR(&evtH, event);
    TEST_ASSERT_EQUAL(&evtL, (RKH_QUEUE_T*)(*queue.pstart));
    TEST_ASSERT_EQUAL(&evtM, (RKH_QUEUE_T*)(*(queue.pstart + 1)));
    priorityQueueOrderTeardown(&queue, event);
}

void
test_getAnElementFromAPriorityQueueBottom(void)
{
    RKH_QUEUE_T queue;
    RKH_EVT_T* event;

    priorityQueueOrderSetup(&queue);
    rkh_queue_put_fifo(&queue, &evtL);
    rkh_queue_put_fifo(&queue, &evtM);
    rkh_queue_put_fifo(&queue, &evtH);

    event = rkh_queue_get(&queue);
    TEST_ASSERT_EQUAL_PTR(&evtH, event);
    TEST_ASSERT_EQUAL(&evtL, (RKH_QUEUE_T*)(*queue.pstart));
    TEST_ASSERT_EQUAL(&evtM, (RKH_QUEUE_T*)(*(queue.pstart + 1)));
    priorityQueueOrderTeardown(&queue, event);
}


void
test_getAnElementFromAPriorityQueueOneElement(void)
{
    RKH_QUEUE_T queue;
    RKH_EVT_T* event;

    rkh_trc_isoff__ExpectAndReturn(RKH_TE_QUE_INIT, RKH_FALSE);

    rkh_enter_critical_Expect();
    rkh_exit_critical_Expect();

    rkh_sma_setReady_Expect(&ao);
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_QUE_FIFO, RKH_FALSE);

    rkh_enter_critical_Expect();
    rkh_sma_block_Expect(&ao);
    rkh_sma_setUnready_Expect(&ao);
    rkh_trc_isoff__ExpectAndReturn(RKH_TE_QUE_GET_LAST, RKH_FALSE);
    rkh_exit_critical_Expect();

    evtL.priority = 2;
    evtM.priority = 1;
    evtH.priority = 0;
    rkh_queue_init(&queue, RKH_CAST(const void*, storage), STORAGE_SIZE, &ao);
    rkh_queue_setType(&queue, PriorityQueType);
    rkh_queue_put_fifo(&queue, &evtH);

    event = rkh_queue_get(&queue);
    TEST_ASSERT_EQUAL_PTR(&evtH, event);
    TEST_ASSERT_EQUAL(0, event->priority);
    TEST_ASSERT_EQUAL(0, queue.qty);
    TEST_ASSERT_EQUAL(queue.pstart, queue.pin);
}

void
test_getAnElementFromAPriorityQueueFirstHighestElement(void)
{
    RKH_QUEUE_T queue;
    RKH_EVT_T* event;

    priorityQueueOrderSetup(&queue);

    evtL.priority = 2;
    evtH1.priority = 0;
    evtH2.priority = 0;

    rkh_queue_put_fifo(&queue, &evtH1);
    rkh_queue_put_fifo(&queue, &evtL);
    rkh_queue_put_fifo(&queue, &evtH2);

    event = rkh_queue_get(&queue);
    TEST_ASSERT_EQUAL_PTR(&evtH1, event);
    TEST_ASSERT_EQUAL(&evtL, (RKH_QUEUE_T*)(*queue.pstart));
    TEST_ASSERT_EQUAL(&evtH2, (RKH_QUEUE_T*)(*(queue.pstart + 1)));

    priorityQueueOrderTeardown(&queue, event);
}

void
test_getAnElementFromAPriorityQueueEmpty(void)
{
    RKH_QUEUE_T queue;
    RKH_EVT_T* event;

    rkh_trc_isoff__ExpectAndReturn(RKH_TE_QUE_INIT, RKH_FALSE);
    rkh_enter_critical_Expect();
    rkh_exit_critical_Expect();
    rkh_enter_critical_Expect();
    rkh_exit_critical_Expect();

    rkh_queue_init(&queue, RKH_CAST(const void*, storage), STORAGE_SIZE, NULL);
    rkh_queue_setType(&queue, PriorityQueType);
    event = rkh_queue_get(&queue);
    TEST_ASSERT_EQUAL_PTR(NULL, event);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
