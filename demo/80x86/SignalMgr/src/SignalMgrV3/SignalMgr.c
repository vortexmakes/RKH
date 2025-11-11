/**
 *  \file       SignalMgr.c
 *  \brief      SignalMgr application. It demonstrates how to write a periodic
 *              reactive active object using orthogonal regions.
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
#include "rkhevt.h"
#include "rkhfwk_cast.h"
#include "rkhitl.h"
#include "rkhsma.h"
#include "rkhtrc_define.h"
#include "rkhtrc_filter.h"
#include "signals.h"
#include <stdbool.h>
#include <stdio.h>

/* ----------------------------- Local macros ------------------------------ */
/* ......................... Declares active object ........................ */
typedef struct SignalMgr SignalMgr;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE idle, active;

/* ........................ Declares effect actions ........................ */
static void init(SignalMgr* const me, RKH_EVT_T* pe);
static void activeProcess(SignalMgr* const me, RKH_EVT_T* pe);
static void propagateEvent(SignalMgr* const me, RKH_EVT_T* pe);

/* ......................... Declares entry actions ........................ */
/* ......................... Declares exit actions ......................... */
/* ............................ Declares guards ............................ */
static rbool_t isGreaterThanLevel1(SignalMgr* const me, RKH_EVT_T *pe);
static rbool_t isLessThanLevel1(SignalMgr* const me, RKH_EVT_T *pe);

/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(sync, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(sync)
    RKH_TRINT(sigSync, NULL, propagateEvent),
RKH_END_TRANS_TABLE

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
    RKHTmEvt syncTmr;      /* Periodic time event to signal
                            * this AO regurlarly */
    DataReady signalReady; /* Input for synchronization */
    RKH_SM_T processing;   /* Orthogonal region */
};

RKH_SMA_CREATE(SignalMgr, 
        signalMgr, 
        SignalMgrPrio, 
        HCAL, &sync, init, NULL);
RKH_SMA_DEF_PTR(signalMgr);
RKH_SM_CONST_CREATE(processing, 1, HCAL, &idle, NULL, NULL);

/* ------------------------------- Constants ------------------------------- */
RKH_MODULE_NAME(SignalMgr)

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
RKH_DCLR_SM_CONST_GLOBAL(processing);

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
activate(RKH_SMA_T* me, const RKH_EVT_T** qSto, RKH_QUENE_T qSize,
         void* stkSto, rui32_t stkSize)
{
    (void)stkSto;
    (void)stkSize;
    RKH_SR_ALLOC();

    RKH_REQUIRE((qSto != (const RKH_EVT_T**)0) && (qSize != (RKH_QUENE_T)0));
    SignalMgr* realMe = RKH_DOWNCAST(SignalMgr, me);

    rkh_queue_init(&me->equeue, (const void**)qSto, qSize, me);
    rkh_sma_register(me);
    rkh_sm_init(RKH_UPCAST(RKH_SM_T, me));
    rkh_sm_init(RKH_UPCAST(RKH_SM_T, &realMe->processing));
    RKH_TR_SMA_ACT(me, RKH_GET_PRIO(me), qSize);
}

static void
dispatch(RKH_SMA_T* me, void* arg)
{
    RKH_SM_T *region;

    /* The default AO state machine (which represents the 'sync' */
    /* region) */
    rkh_sm_dispatch(RKH_UPCAST(RKH_SM_T, me), RKH_EVT_CAST(arg));

    /* The explicitly defined orthogonal region 'processing' */
    region = &(RKH_DOWNCAST(SignalMgr, me)->processing);
    rkh_sm_dispatch(RKH_CAST(RKH_SM_T, region), RKH_EVT_CAST(arg));
}

/* ............................ Effect actions ............................. */
static void
init(SignalMgr* const me, RKH_EVT_T *pe)
{
    RKH_TR_FWK_AO(me);
    RKH_TR_FWK_QUEUE(&RKH_UPCAST(RKH_SMA_T, me)->equeue);
    RKH_TR_FWK_STATE(me, &idle);
    RKH_TR_FWK_STATE(me, &active);
    RKH_TR_FWK_STATE(me, &sync);
    RKH_TR_FWK_SIG(sigSync);
    RKH_TR_FWK_SIG(sigDataReady);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_DCH);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);

    SignalMgr* realMe = RKH_DOWNCAST(SignalMgr, me);
    RKH_TR_FWK_ACTOR(&realMe->processing, "SignalMgr::processing");
    RKH_FILTER_OFF_SMA(&realMe->processing);

    RKH_TMR_PERIODIC(&me->syncTmr.tmr,
                     RKH_UPCAST(RKH_SMA_T, me),
                     TIME_PER,
                     TIME_PER);
}

static void
activeProcess(SignalMgr* const me, RKH_EVT_T *pe)
{
    Actuator_set(me->signalReady.value);
}

static void
propagateEvent(SignalMgr* const me, RKH_EVT_T* pe)
{
    /* Read and Process Data */
    double sensorValue = Sensor_get();
    double actuatorOutput = Sensor_process(sensorValue);
    me->signalReady.value = actuatorOutput;

    /* Propagate event to self (dispatch to all regions) */
    RKH_SMA_POST_LIFO(signalMgr, RKH_CAST_EVT(&me->signalReady), me);
}

/* ............................. Entry actions ............................. */
/* ............................. Exit actions .............................. */
/* ................................ Guards ................................. */
static rbool_t
isGreaterThanLevel1(SignalMgr* const me, RKH_EVT_T* pe)
{
    return (RKH_DOWNCAST(DataReady, pe)->value > 1.23) ? true : false;
}

static rbool_t
isLessThanLevel1(SignalMgr* const me, RKH_EVT_T* pe)
{
    return (RKH_DOWNCAST(DataReady, pe)->value <= 1.23) ? true : false;
}

/* ---------------------------- Global functions --------------------------- */
void
SignalMgr_ctor(int baz)
{
    SignalMgr* const me = RKH_DOWNCAST(SignalMgr, signalMgr); 
    static const RKHSmaVtbl vtbl =
    {
        activate,
        dispatch,
        rkh_sma_post_fifo,
        rkh_sma_post_lifo
    };

    RKH_REQUIRE(me != RKH_CAST(SignalMgr, 0));
    rkh_sma_ctor(&me->base, &vtbl);
    RKH_SET_STATIC_EVENT(&me->signalReady, sigDataReady);
    RKH_SET_STATIC_EVENT(&me->syncTmr, sigSync);
    RKH_TMR_INIT(&me->syncTmr.tmr, RKH_UPCAST(RKH_EVT_T, &me->syncTmr), NULL);
    me->baz = baz;
    RKH_SM_INIT(&me->processing,
                processing, 0, HCAL,
                &idle, NULL, NULL);
}

int
SignalMgr_getBaz(void)
{
    SignalMgr* const me = RKH_DOWNCAST(SignalMgr, signalMgr); 
    RKH_REQUIRE(me != RKH_CAST(SignalMgr, 0));
    return me->baz;
}

/* ------------------------------ End of file ------------------------------ */
