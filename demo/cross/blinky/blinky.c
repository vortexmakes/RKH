/**
 *  \file       blinky.c
 *  \brief      Example application.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.03.17  LeFr  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "blinky.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
#define LED_OFF_TIME            RKH_TIME_SEC(2)
#define LED_ON_TIME             RKH_TIME_SEC(2)

/* ......................... Declares active object ........................ */
typedef struct Blinky Blinky;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE ledOff, ledOn;

/* ........................ Declares initial action ........................ */
static void blinky_init(Blinky *const me, RKH_EVT_T *pe);

/* ........................ Declares effect actions ........................ */
static void blinky_ledOn(Blinky *const me, RKH_EVT_T *pe);
static void blinky_ledOff(Blinky *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
/* ......................... Declares exit actions ......................... */
/* ............................ Declares guards ............................ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(ledOn, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(ledOn)
    RKH_TRREG(TIMEOUT, NULL, blinky_ledOff, &ledOff),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(ledOff, NULL, NULL, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(ledOff)
    RKH_TRREG(TIMEOUT, NULL, blinky_ledOn, &ledOn),
RKH_END_TRANS_TABLE

/* ............................. Active object ............................. */
struct Blinky
{
    RKH_SMA_T sma;      /* base structure */
    rui8_t cnt;         /* private member */
    RKH_TMR_T timer;    /* which is responsible for toggling the LED */
                        /* posting the TIMEOUT signal event to active object */
                        /* 'blinky' */
};

RKH_SMA_CREATE(Blinky, blinky, 0, HCAL, &ledOn, blinky_init, NULL);
RKH_SMA_DEF_PTR(blinky);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/*
 *  Declare and allocate the 'e_tout' event.
 *  The 'e_tout' event with TIMEOUT signal never changes, so it can be
 *  statically allocated just once by means of RKH_ROM_STATIC_EVENT() macro.
 */
static RKH_ROM_STATIC_EVENT(e_tout, TIMEOUT);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Initial action ............................. */
static void
blinky_init(Blinky *const me, RKH_EVT_T *pe)
{
    RKH_TR_FWK_AO(me);
    RKH_TR_FWK_QUEUE(&RKH_UPCAST(RKH_SMA_T, me)->equeue);
    RKH_TR_FWK_STATE(me, &ledOn);
    RKH_TR_FWK_STATE(me, &ledOff);
    RKH_TR_FWK_TIMER(&me->timer);
    RKH_TR_FWK_SIG(TIMEOUT);

    RKH_TMR_INIT(&me->timer, &e_tout, NULL);
    blinky_ledOn(me, NULL);
}

/* ............................ Effect actions ............................. */
static void
blinky_ledOn(Blinky *const me, RKH_EVT_T *pe)
{
    (void)pe;

    RKH_TMR_ONESHOT(&me->timer, RKH_UPCAST(RKH_SMA_T, me), LED_ON_TIME);
    bsp_ledOn();
    ++me->cnt;
}

static void
blinky_ledOff(Blinky *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    RKH_TMR_ONESHOT(&me->timer, RKH_UPCAST(RKH_SMA_T, me), LED_OFF_TIME);
    bsp_ledOff();
}

/* ............................. Entry actions ............................. */
/* ............................. Exit actions .............................. */
/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
