/**
 *  \file       SignalMgr.c
 *  \brief      SignalMgr application. It demonstrates how to write a
 *              periodic non-reactive active object using a state machine
 *              with synchronous inputs.
 */

/* -------------------------- Development history -------------------------- */
/* -------------------------------- Authors -------------------------------- */
/*
     *  LeFr  Leandro Francucci lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "SignalMgr.h"
#include "Sensor.h"
#include "Actuator.h"
#include "priority.h"
#include "events.h"
#include "rkhdef.h"
#include "rkhfwk_cast.h"
#include "rkhtrc_define.h"
#include "rkhtrc_filter.h"
#include "signals.h"
#include "bsp.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

/* ----------------------------- Local macros ------------------------------ */
/* ......................... Declares active object ........................ */
typedef struct SignalMgr SignalMgr;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE idle, active;

/* ........................ Declares effect actions ........................ */
static void init(SignalMgr* const me, RKH_EVT_T* pe);
static void activeProcess(SignalMgr* const me, RKH_EVT_T* pe);

/* ......................... Declares entry actions ........................ */
/* ......................... Declares exit actions ......................... */
/* ............................ Declares guards ............................ */
static rbool_t isGreaterThanLevel1(SignalMgr* const me, RKH_EVT_T *pe);
static rbool_t isLessThanLevel1(SignalMgr* const me, RKH_EVT_T *pe);

/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(idle, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(idle)
    RKH_TRREG(sigDataReady, isGreaterThanLevel1, activeProcess, &active),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(active, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(active)
    RKH_TRREG(sigDataReady, isLessThanLevel1, NULL, &idle),
    RKH_TRINT(sigDataReady, isGreaterThanLevel1, NULL),
RKH_END_TRANS_TABLE

/* ............................. Active object ............................. */
struct SignalMgr
{
    RKH_SMA_T base;        /* Base structure */
    int baz;               /* Attribute */
    RKHTmEvt syncTmr;      /* Periodic time event to regularly signal this AO */
    DataReady signalReady; /* Input for the sync state machine */
};

RKH_SMA_CREATE(SignalMgr, signalMgr, SignalMgrPrio, HCAL, &idle, init, NULL);
RKH_SMA_DEF_PTR(signalMgr);

/* ------------------------------- Constants ------------------------------- */
RKH_MODULE_NAME(SignalMgr)

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
activate(RKH_SMA_T* me, const RKH_EVT_T** qSto, RKH_QUENE_T qSize, void* stkSto,
         rui32_t stkSize)
{
    (void)stkSto;
    (void)stkSize;
    SignalMgr* realMe = RKH_DOWNCAST(SignalMgr, me);
    RKH_SR_ALLOC();

    RKH_REQUIRE((qSto != (const RKH_EVT_T**)0) && (qSize != (RKH_QUENE_T)0));
    rkh_queue_init(&me->equeue, (const void**)qSto, qSize, me);
    rkh_sma_register(me);
    rkh_sm_init((RKH_SM_T *)me);
    RKH_TMR_PERIODIC(&realMe->syncTmr.tmr, me, TIME_PER, TIME_PER);
    RKH_TR_SMA_ACT(me, RKH_GET_PRIO(me), qSize);
}

static void
task(RKH_SMA_T* me, void* arg)
{
    RKH_EVT_T* evt = RKH_EVT_CAST(arg);
    SignalMgr* realMe = RKH_DOWNCAST(SignalMgr, me);
    double intPart, fractPart;

    RKH_REQUIRE((me != RKH_CAST(RKH_SMA_T, 0)) && (evt != RKH_CAST_EVT(0)));
    if (evt->e == sigSync)
    {
        double sensorValue = Sensor_get();
        double actuatorOutput = Sensor_process(sensorValue);

        fractPart = modf(actuatorOutput, &intPart);
        RKH_TRC_USR_BEGIN(USRT_ACTOUT);
            RKH_TUSR_UI8(RKH_UI8_T, (uint8_t)intPart);
            RKH_TUSR_UI8(
                RKH_UI8_T,
                (uint8_t)(fractPart * 100));
        RKH_TRC_USR_END();

        realMe->signalReady.value = actuatorOutput;
        rkh_sm_dispatch(RKH_UPCAST(RKH_SM_T, me),
                        RKH_EVT_CAST(&realMe->signalReady));
    }
}

/* ............................ Effect actions ............................. */
static void
init(SignalMgr* const me, RKH_EVT_T *pe)
{
    RKH_TR_FWK_AO(me);
    RKH_TR_FWK_QUEUE(&RKH_UPCAST(RKH_SMA_T, me)->equeue);
    RKH_TR_FWK_STATE(me, &idle);
    RKH_TR_FWK_STATE(me, &active);
    RKH_TR_FWK_SIG(sigSync);
    RKH_TR_FWK_SIG(sigDataReady);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_GRD_FALSE);
}

static void
activeProcess(SignalMgr* const me, RKH_EVT_T *pe)
{
    Actuator_set(me->signalReady.value);
}

/* ............................. Entry actions ............................. */
/* ............................. Exit actions .............................. */
/* ................................ Guards ................................. */
static rbool_t
isGreaterThanLevel1(SignalMgr* const me, RKH_EVT_T* pe)
{
    return (RKH_DOWNCAST(DataReady, pe)->value > 1.23) ? RKH_TRUE : RKH_FALSE;
}

static rbool_t
isLessThanLevel1(SignalMgr* const me, RKH_EVT_T* pe)
{
    return (RKH_DOWNCAST(DataReady, pe)->value <= 1.23) ? RKH_TRUE : RKH_FALSE;
}

/* ---------------------------- Global functions --------------------------- */
void
SignalMgr_ctor(int baz)
{
    SignalMgr* const me = RKH_DOWNCAST(SignalMgr, signalMgr); 
    static const RKHSmaVtbl vtbl =
    {
        activate,
        task,
        rkh_sma_post_fifo,
        rkh_sma_post_lifo
    };

    RKH_REQUIRE(me != RKH_CAST(SignalMgr, 0));
    rkh_sma_ctor(&me->base, &vtbl);
    RKH_SET_STATIC_EVENT(&me->signalReady, sigDataReady);
    RKH_SET_STATIC_EVENT(&me->syncTmr, sigSync);
    RKH_TMR_INIT(&me->syncTmr.tmr, RKH_UPCAST(RKH_EVT_T, &me->syncTmr), NULL);
    me->baz = baz;
}

int
SignalMgr_getBaz(void)
{
    SignalMgr* const me = RKH_DOWNCAST(SignalMgr, signalMgr); 
    RKH_REQUIRE(me != RKH_CAST(SignalMgr, 0));
    return me->baz;
}

/* ------------------------------ End of file ------------------------------ */
