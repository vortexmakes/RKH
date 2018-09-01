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
 *  terms of the GNU General Public License as published by the Recycle Software
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
 *  \file       test_rkhfwk_pubsub.c
 *  \ingroup    test_fwk
 *  \brief      Unit test for publish/subscribe mechanism of fwk module.
 *
 *  \addtogroup test
 *  @{
 *  \addtogroup test_fwk Framework
 *  @{
 *  \brief      Unit test for framework module.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.08.06  LeFr  v3.1.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "unity.h"
#include "rkhfwk_pubsub.h"
#include "rkhfwk_pubsubSpy.h"
#include "Mock_rkhfwk_rdygrp.h"
#include "Mock_rkhsma.h"
#include "Mock_rkhassert.h"
#include "Mock_rkhport.h"
#include "Mock_rkhfwk_dynevt.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
typedef struct PubArg PubArg;
struct PubArg
{
    RdyCbArg base;
    RKH_EVT_T *event;
    const void *sender;
};

/* ---------------------------- Global variables --------------------------- */
int GlobalExpectCount;
int GlobalVerifyOrder;
char *GlobalOrderError;
RKH_SMA_T *rkh_sptbl[RKH_CFG_FWK_MAX_SMA];  /* Just for compiling */
static RKH_EVT_T event;

/* ---------------------------- Local variables ---------------------------- */
RKH_SMA_CREATE(RKH_SMA_T, ao, 0, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR(ao);
RKH_SMA_CREATE(RKH_SMA_T, aoSender, 1, HCAL, NULL, NULL, NULL);
RKH_SMA_DEF_PTR(aoSender);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void 
MockAssertCallback(const char* const file, int line, int cmock_num_calls)
{
    TEST_PASS();
}

/* ---------------------------- Global functions --------------------------- */
void
setUp(void)
{
    Mock_rkhfwk_rdygrp_Init();
    Mock_rkhsma_Init();
    Mock_rkhassert_Init();
    Mock_rkhport_Init();
}

void
tearDown(void)
{
    Mock_rkhfwk_rdygrp_Verify();
    Mock_rkhsma_Verify();
    Mock_rkhassert_Verify();
    Mock_rkhport_Verify();
    Mock_rkhfwk_rdygrp_Destroy();
    Mock_rkhsma_Destroy();
    Mock_rkhassert_Destroy();
    Mock_rkhport_Destroy();
}

/**
 *  \addtogroup test_pubsub Test cases of publish/subscribe group
 *  @{
 *  \name Test cases of publish/subscribe group
 *  @{ 
 */
void
test_AfterInitAllChannelsAreAvailable(void)
{
    rui8_t nCh;

    for (nCh = 0; nCh < RKH_CFG_FWK_MAX_SUBS_CHANNELS; ++nCh)
    {
        rkh_rdygrp_init_Expect(0);
        rkh_rdygrp_init_IgnoreArg_me();
    }

    rkh_pubsub_init();
}

void
test_SubscribeOneActiveObject(void)
{
    rkh_rdygrp_init_Ignore();
    rkh_enter_critical_Expect();
    rkh_rdygrp_setReady_Expect(0, RKH_GET_PRIO(ao));
    rkh_rdygrp_setReady_IgnoreArg_me();
    rkh_exit_critical_Expect();

    rkh_pubsub_init();
    rkh_pubsub_subscribe(0, ao);
}

void
test_UnsubscribeOneActiveObject(void)
{
    rkh_rdygrp_init_Ignore();
    rkh_enter_critical_Expect();
    rkh_rdygrp_setUnready_Expect(0, RKH_GET_PRIO(ao));
    rkh_rdygrp_setUnready_IgnoreArg_me();
    rkh_exit_critical_Expect();

    rkh_pubsub_init();
    rkh_pubsub_unsubscribe(0, ao);
}

void
test_UnsubscribeAllActiveObjects(void)
{
    rui8_t nCh;

    rkh_rdygrp_init_Ignore();
    rkh_pubsub_init();

    for (nCh = 0; nCh < RKH_CFG_FWK_MAX_SUBS_CHANNELS; ++nCh)
    {
        rkh_enter_critical_Expect();
        rkh_rdygrp_setReady_Expect(0, RKH_GET_PRIO(ao));
        rkh_exit_critical_Expect();
        rkh_rdygrp_setReady_IgnoreArg_me();
        rkh_pubsub_subscribe(nCh, ao);
    }

    rkh_enter_critical_Expect();
    for (nCh = 0; nCh < RKH_CFG_FWK_MAX_SUBS_CHANNELS; ++nCh)
    {
        rkh_rdygrp_setUnready_Expect(0, RKH_GET_PRIO(ao));
        rkh_rdygrp_setUnready_IgnoreArg_me();
    }
    rkh_exit_critical_Expect();

    rkh_pubsub_unsubscribeAll(ao);
}

void
test_PublishOneActiveObject(void)
{
    int me;
    RKH_EVT_T evt;
    rui8_t nRdyAo;

    rkh_rdygrp_init_Ignore();
    rkh_enter_critical_Expect();
    rkh_rdygrp_traverse_ExpectAndReturn(0, 0, 0, 1);
    rkh_exit_critical_Expect();
    rkh_fwk_gc_Expect(&evt, &me);
    rkh_rdygrp_traverse_IgnoreArg_me();
    rkh_rdygrp_traverse_IgnoreArg_rdyCb();
    rkh_rdygrp_traverse_IgnoreArg_rdyCbArg();

    rkh_pubsub_init();
    nRdyAo = rkh_pubsub_publish(0, &evt, &me);
    TEST_ASSERT_EQUAL(1, nRdyAo);
}

void
test_InvokePublishCallbackOnPublish(void)
{
    rui8_t nRdyAo;
    PubArg publishArg;

    rkh_sptbl[RKH_GET_PRIO(ao)] = ao;
    rkh_sptbl[RKH_GET_PRIO(aoSender)] = aoSender;
    publishArg.base.aoRdyPrio = RKH_GET_PRIO(ao);   /* subscriber */
    publishArg.event = &event;
    publishArg.sender = aoSender;
    rkh_sma_post_fifo_Expect(ao, &event, aoSender);

    publish((RdyCbArg *)&publishArg);
}

void
test_IgnoreSelfPublishing(void)
{
    rui8_t nRdyAo;
    PubArg publishArg;

    rkh_sptbl[RKH_GET_PRIO(ao)] = ao;
    publishArg.base.aoRdyPrio = RKH_GET_PRIO(ao);   /* subscriber */
    publishArg.event = &event;
    publishArg.sender = ao;

    publish((RdyCbArg *)&publishArg);
}

void
test_Fails_SubscribeWithWrongArgs(void)
{
    rui8_t prio = RKH_CFG_FWK_MAX_SMA;

    rkh_assert_Expect("rkhfwk_pubsub", 0);
    rkh_assert_IgnoreArg_file();
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);
    rkh_pubsub_subscribe(RKH_CFG_FWK_MAX_SUBS_CHANNELS, ao);

    rkh_assert_Expect("rkhfwk_pubsub", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);
    rkh_pubsub_subscribe(0, NULL);
}

void
test_Fails_UnsubscribeWithWrongArgs(void)
{
    rui8_t prio = RKH_CFG_FWK_MAX_SMA;

    rkh_assert_Expect("rkhfwk_pubsub", 0);
    rkh_assert_IgnoreArg_file();
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);
    rkh_pubsub_unsubscribe(RKH_CFG_FWK_MAX_SUBS_CHANNELS, ao);

    rkh_assert_Expect("rkhfwk_pubsub", 0);
    rkh_assert_IgnoreArg_line();
    rkh_assert_StubWithCallback(MockAssertCallback);
    rkh_pubsub_unsubscribe(0, NULL);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */

/* ------------------------------ End of file ------------------------------ */
