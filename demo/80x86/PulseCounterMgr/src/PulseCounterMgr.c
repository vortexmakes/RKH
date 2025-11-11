/**
 *  \file       PulseCounterMgr.c
 *  \brief      PulseCounterMgr application. It demonstrates how to implement
 *              a pulseCounterMgr reactive Active Object.
 */

/* -------------------------- Development history -------------------------- */
/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "PulseCounterMgr.h"
#include "priority.h"
#include "events.h"
#include "rkhfwk_cast.h"
#include "rkhtrc_filter.h"
#include "rkhtrc_record.h"
#include "signals.h"
#include <stdbool.h>
#include <stdint.h>

/* ----------------------------- Local macros ------------------------------ */
/* ......................... Declares SM component ......................... */
typedef struct PulseCounter PulseCounter;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE idle, setup, active, waitInactive, inactive;

/* ........................ Declares effect actions ........................ */
static void init(PulseCounter* const me, RKH_EVT_T* pe);
static void reset(PulseCounter* const me, RKH_EVT_T* pe);
static void inc(PulseCounter* const me, RKH_EVT_T* pe);
static void notify(PulseCounter* const me, RKH_EVT_T* pe);

/* ......................... Declares entry actions ........................ */
static void enSetup(PulseCounter* const me);
static void exSetup(PulseCounter* const me);
static void enActive(PulseCounter* const me);
static void exActive(PulseCounter* const me);
static void enInactive(PulseCounter* const me);
static void exInactive(PulseCounter* const me);

/* ......................... Declares exit actions ......................... */
/* ............................ Declares guards ............................ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(idle, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(idle)
    RKH_TRREG(sigActive, NULL, reset, &setup),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(setup, enSetup, exSetup, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(setup)
    RKH_TRREG(sigTactMinTout, NULL, NULL, &active),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(active, enActive, exActive, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(active)
    RKH_TRREG(sigInactive, NULL, inc, &inactive),
    RKH_TRREG(sigTactMaxTout, NULL, NULL, &waitInactive),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(inactive, enInactive, exInactive, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(inactive)
    RKH_TRREG(sigActive, NULL, NULL, &setup),
    RKH_TRREG(sigTinactMaxTout, NULL, notify, &idle),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(waitInactive, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(waitInactive)
    RKH_TRREG(sigInactive, NULL, NULL, &idle),
RKH_END_TRANS_TABLE

/* ............................. Active object ............................. */
typedef struct PulseCounterMgr PulseCounterMgr;
struct PulseCounter
{
    RKH_SM_T sm;                         /* base class */
    TimeEvt tactMin;                     /* timer tactMin */
    TimeEvt tactMax;                     /* timer tactMax */
    TimeEvt tinactMax;                   /* timer tinactMax */
    uint32_t nPulses;                    /* amount of detected pulses */
    int id;                              /* identification */
    const char* name;                    /* name */
    PulseCounterMgr* thePulseCounterMgr; /* reference to its own container */
};

struct PulseCounterMgr
{
    RKH_SMA_T base;
    int baz;
    PulseCounter pulseCounters[NUM_PULSE_COUNTERS]; /* SM components */
};

RKH_SMA_CREATE(PulseCounterMgr, pulseCounterMgr, PulseCounterMgrPrio, 0, NULL,
               NULL, NULL);
RKH_SMA_DEF_PTR(pulseCounterMgr);
RKH_SM_CONST_CREATE(pulseCounter, /* name of parameterized SM */
                    1, HCAL,      /* it is a hierarchical SM */
                    &idle,        /* default state */
                    init,         /* topmost initial action */
                    NULL);

/* ------------------------------- Constants ------------------------------- */
RKH_MODULE_NAME(PulseCounterMgr)

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static const char* const pulseCtrNames[NUM_PULSE_COUNTERS] =
{
    "pc0", "pc1", "pc2", "pc3"
};

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
activate(RKH_SMA_T* me, const RKH_EVT_T** qSto, RKH_QUENE_T qSize, void* stkSto,
         rui32_t stkSize)
{
    (void)stkSto;
    (void)stkSize;
    PulseCounterMgr* realMe = RKH_DOWNCAST(PulseCounterMgr, me);
    PulseCounter *pulseCtr;
    int i;
    RKH_SR_ALLOC();

    RKH_REQUIRE((qSto != (const RKH_EVT_T**)0) && (qSize != (RKH_QUENE_T)0));
    rkh_queue_init(&me->equeue, (const void**)qSto, qSize, me);
    rkh_sma_register(me);
    for (pulseCtr = &realMe->pulseCounters[0], i = 0;
         i < NUM_PULSE_COUNTERS;
         ++i, ++pulseCtr)
    {
        rkh_sm_init(RKH_UPCAST(RKH_SM_T, pulseCtr));
    }
    RKH_TR_SMA_ACT(me, RKH_GET_PRIO(me), qSize);
}

static void
task(RKH_SMA_T* me, void* arg)
{
    RKH_EVT_T* evt = RKH_EVT_CAST(arg);
    PulseCounterMgr* realMe = RKH_DOWNCAST(PulseCounterMgr, me);
    int ix;

    RKH_REQUIRE((me != RKH_CAST(RKH_SMA_T, 0)) && (evt != RKH_CAST_EVT(0)));
    RKH_TR_SM_DCH(me, evt, RKH_CAST(RKH_ST_T, 0));
    switch (evt->e)
    {
        case sigActive:
        case sigInactive:
            ix = RKH_DOWNCAST(StatusEvt, evt)->id;
            RKH_REQUIRE(ix <= NUM_PULSE_COUNTERS);
            rkh_sm_dispatch(RKH_DOWNCAST(RKH_SM_T, &realMe->pulseCounters[ix]),
                            evt);
            break;
        case sigTactMinTout:
        case sigTactMaxTout:
        case sigTinactMaxTout:
            ix = RKH_DOWNCAST(TimeEvt, evt)->id;
            RKH_REQUIRE(ix <= NUM_PULSE_COUNTERS);
            rkh_sm_dispatch(RKH_DOWNCAST(RKH_SM_T, &realMe->pulseCounters[ix]),
                            evt);
            break;
        default:
            /* Unknown event */
            break;
    }
}

/* ............................ Effect actions ............................. */
static void
init(PulseCounter* const me, RKH_EVT_T* pe)
{
    RKH_SET_STATIC_EVENT(&me->tactMin, sigTactMinTout);
    RKH_SET_STATIC_EVENT(&me->tactMax, sigTactMaxTout);
    RKH_SET_STATIC_EVENT(&me->tinactMax, sigTinactMaxTout);

    RKH_TMR_INIT(&me->tactMin.evt.tmr,
                 RKH_UPCAST(RKH_EVT_T, &me->tactMin),
                 NULL);
    RKH_TMR_INIT(&me->tactMax.evt.tmr,
                 RKH_UPCAST(RKH_EVT_T, &me->tactMax),
                 NULL);
    RKH_TMR_INIT(&me->tinactMax.evt.tmr,
                 RKH_UPCAST(RKH_EVT_T, &me->tinactMax),
                 NULL);
}

static void
reset(PulseCounter* const me, RKH_EVT_T* pe)
{
    me->nPulses = 0;
}

static void
inc(PulseCounter* const me, RKH_EVT_T* pe)
{
    ++me->nPulses;
}

static void
notify(PulseCounter* const me, RKH_EVT_T* pe)
{
}

/* ............................. Entry actions ............................. */
static void
enSetup(PulseCounter* const me)
{
    RKH_TMR_ONESHOT(&me->tactMin.evt.tmr,
                    RKH_UPCAST(RKH_SMA_T, me->thePulseCounterMgr),
                    TACTMIN);
}

static void
exSetup(PulseCounter* const me)
{
      rkh_tmr_stop(&me->tactMin.evt.tmr);
}

static void
enActive(PulseCounter* const me)
{
    RKH_TMR_ONESHOT(&me->tactMax.evt.tmr,
                    RKH_UPCAST(RKH_SMA_T, me->thePulseCounterMgr),
                    TACTMAX);
}

static void
exActive(PulseCounter* const me)
{
      rkh_tmr_stop(&me->tactMax.evt.tmr);
}

static void
enInactive(PulseCounter* const me)
{
    RKH_TMR_ONESHOT(&me->tinactMax.evt.tmr,
                    RKH_UPCAST(RKH_SMA_T, me->thePulseCounterMgr),
                    TINACTMAX);
}

static void
exInactive(PulseCounter* const me)
{
    rkh_tmr_stop(&me->tinactMax.evt.tmr);
}

/* ............................. Exit actions .............................. */
/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
void
PulseCounterMgr_ctor(int baz)
{
    int i;
    PulseCounter *pulseCtr;
    PulseCounterMgr* const me = RKH_DOWNCAST(PulseCounterMgr, pulseCounterMgr);
    static const RKHSmaVtbl vtbl =
    {
        activate,
        task,
        rkh_sma_post_fifo,
        rkh_sma_post_lifo
    };

    RKH_REQUIRE(me != RKH_CAST(PulseCounterMgr, 0));

    RKH_TR_FWK_AO(me);
    RKH_TR_FWK_QUEUE(&RKH_UPCAST(RKH_SMA_T, me)->equeue);
    RKH_TR_FWK_SIG(sigActive);
    RKH_TR_FWK_SIG(sigInactive);
    RKH_TR_FWK_SIG(sigTactMaxTout);
    RKH_TR_FWK_SIG(sigTactMinTout);
    RKH_TR_FWK_SIG(sigTinactMaxTout);
    RKH_TR_FWK_STATE(me, &idle);
    RKH_TR_FWK_STATE(me, &setup);
    RKH_TR_FWK_STATE(me, &active);
    RKH_TR_FWK_STATE(me, &waitInactive);
    RKH_TR_FWK_STATE(me, &inactive);

    rkh_sma_ctor(&me->base, &vtbl);
    for (i = 0; i < NUM_PULSE_COUNTERS; ++i)
    {
        pulseCtr = &me->pulseCounters[i];
        pulseCtr->id = i;
        pulseCtr->nPulses = 0;
        pulseCtr->tactMin.id = i;
        pulseCtr->tactMax.id = i;
        pulseCtr->tinactMax.id = i;
        pulseCtr->thePulseCounterMgr = me;
        pulseCtr->name = pulseCtrNames[i];
        RKH_SM_INIT(pulseCtr,     /* Instance of SM component */
                    pulseCounter, /* Complete next parameters with the */
                    1,            /* same values used in the macro */
                    HCAL,         /* RKH_SM_CONST_CREATE() */
                    &PulseCounter_Idle,
                    PulseCounter_init,
                    NULL);
        RKH_TR_FWK_ACTOR(pulseCtr, pulseCtr->name);
        RKH_FILTER_OFF_SMA(pulseCtr);
    }
    me->baz = baz;
}

int
PulseCounterMgr_getBaz(void)
{
    PulseCounterMgr* const me = RKH_DOWNCAST(PulseCounterMgr, pulseCounterMgr);
    RKH_REQUIRE(me != RKH_CAST(PulseCounterMgr, 0));
    return me->baz;
}

/* ------------------------------ End of file ------------------------------ */
