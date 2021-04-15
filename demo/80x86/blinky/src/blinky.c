/**
 *  \file       blinky.c
 *  \brief      Example application.
 */

/* -------------------------- Development history -------------------------- */
/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "blinky.h"
#include "priority.h"
#include "signal.h"
#include "event.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
#define LedOffTime      RKH_TIME_SEC(2)
#define LedOnTime       RKH_TIME_SEC(2)

/* ......................... Declares active object ........................ */
typedef struct Blinky Blinky;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE ledOff, ledOn;

/* ........................ Declares effect actions ........................ */
static void init(Blinky *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
static void nLedOn(Blinky *const me);
static void nLedOff(Blinky *const me);

/* ......................... Declares exit actions ......................... */
/* ............................ Declares guards ............................ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(ledOn, nLedOn, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(ledOn)
RKH_TRREG(evTout, NULL, NULL, &ledOff),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(ledOff, nLedOff, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(ledOff)
RKH_TRREG(evTout, NULL, NULL, &ledOn),
RKH_END_TRANS_TABLE

/* ............................. Active object ............................. */
struct Blinky
{
    RKH_SMA_T sma;      /* base structure */
    rui8_t cnt;         /* private member */
    RKHTmEvt timer;     /* it is responsible for toggling the LED */
                        /* posting the evTout signal event to active object */
                        /* 'blinky' */
};

RKH_SMA_CREATE(Blinky, blinky, BlinkyPrio, HCAL, &ledOn, init, NULL);
RKH_SMA_DEF_PTR(blinky);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Effect actions ............................. */
static void
init(Blinky *const me, RKH_EVT_T *pe)
{
    RKH_TR_FWK_AO(me);
    RKH_TR_FWK_QUEUE(&RKH_UPCAST(RKH_SMA_T, me)->equeue);
    RKH_TR_FWK_STATE(me, &ledOn);
    RKH_TR_FWK_STATE(me, &ledOff);
    RKH_TR_FWK_OBJ_NAME(&me->timer.tmr, "Blinky::timer");
    RKH_TR_FWK_SIG(evTout);

    RKH_SET_STATIC_EVENT(&me->timer, evTout);
    RKH_TMR_INIT(&me->timer.tmr, RKH_UPCAST(RKH_EVT_T, &me->timer), NULL);
    me->cnt = 0;
}

/* ............................. Entry actions ............................. */
static void
nLedOn(Blinky *const me)
{
    RKH_TMR_ONESHOT(&me->timer.tmr, RKH_UPCAST(RKH_SMA_T, me), LedOnTime);
    bsp_ledOn();
    ++me->cnt;
}

static void
nLedOff(Blinky *const me)
{
    RKH_TMR_ONESHOT(&me->timer.tmr, RKH_UPCAST(RKH_SMA_T, me), LedOffTime);
    bsp_ledOff();
}

/* ............................. Exit actions .............................. */
/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
