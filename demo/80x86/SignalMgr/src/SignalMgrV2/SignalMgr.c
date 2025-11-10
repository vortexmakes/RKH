/**
 *  \file       SignalMgr.c
 *  \brief      SignalMgr application. It demonstrates how to write a periodic
 *              reactive active object propagating an event.
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
#include "rkhsm.h"
#include "signals.h"
#include <stdbool.h>
#include <time.h>

/* ----------------------------- Local macros ------------------------------ */
/* ......................... Declares active object ........................ */
typedef struct SignalMgr SignalMgr;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE idle, active;
RKH_DCLR_COMP_STATE processing;

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
RKH_CREATE_COMP_REGION_STATE(processing, NULL, NULL, RKH_ROOT, &idle,
                             init, RKH_NO_HISTORY, NULL, NULL, NULL, NULL);
RKH_CREATE_TRANS_TABLE(processing)
    RKH_TRINT(sigSync, NULL, propagateEvent),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(idle, NULL, NULL, &processing, NULL);
RKH_CREATE_TRANS_TABLE(idle)
    RKH_TRREG(sigDataReady, isGreaterThanLevel1, activeProcess, &active),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(active, NULL, NULL, &processing, NULL);
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
                            * this active object regurlarly */
    DataReady signalReady; /* Input for synchronization */
};

RKH_SMA_CREATE(SignalMgr, 
        signalMgr, 
        SignalMgrPrio, 
        HCAL, &processing, NULL, NULL);
RKH_SMA_DEF_PTR(signalMgr);

/* ------------------------------- Constants ------------------------------- */
RKH_MODULE_NAME(SignalMgr)

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
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
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_DCH);

    RKH_SET_STATIC_EVENT(&me->syncTmr, sigSync);
    RKH_TMR_INIT(&me->syncTmr.tmr, 
            RKH_UPCAST(RKH_EVT_T, &me->syncTmr), 
            NULL);
    RKH_TMR_PERIODIC(&me->syncTmr.tmr,
                     RKH_UPCAST(RKH_SMA_T, me),
                     TIME_PER,
                     TIME_PER);
    RKH_SET_STATIC_EVENT(&me->signalReady, sigDataReady);
}

static void
activeProcess(SignalMgr* const me, RKH_EVT_T *pe)
{
    Actuator_set(me->signalReady.value);
}

static void
propagateEvent(SignalMgr* const me, RKH_EVT_T* pe)
{
    /* Synchronous Data Acquisition and Processing */
    double sensorValue = Sensor_get();
    double actuatorOutput = Sensor_process(sensorValue);
    me->signalReady.value = actuatorOutput;

    /* Propagate the data event to self */
    rkh_sm_propagate(RKH_UPCAST(RKH_SM_T, me), RKH_EVT_CAST(&me->signalReady));
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
    RKH_REQUIRE(me != RKH_CAST(SignalMgr, 0));
    rkh_sma_ctor(&me->base, NULL);
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
