/**
 *  \file       client.c
 *  \brief      Example application
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
#include "shared.h"
#include "server.h"
#include "client.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
#define CLI_REQ_TIME \
    (RKH_TNT_T)RKH_TIME_SEC((bsp_rand() % 5) + 2)
#define CLI_USING_TIME \
    (RKH_TNT_T)RKH_TIME_SEC((bsp_rand() % 5) + 1)

/* ......................... Declares active object ........................ */
typedef struct Client Client;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE client_idle, client_waiting, client_using, client_paused;

/* ........................ Declares initial action ........................ */
static void client_init(Client *const me, RKH_EVT_T *pe);

/* ........................ Declares effect actions ........................ */
static void client_req(Client *const me, RKH_EVT_T *pe);
static void client_start(Client *const me, RKH_EVT_T *pe);
static void client_end(Client *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
static void client_delay_req(Client *const me);
static void client_pause(Client *const me);

/* ......................... Declares exit actions ......................... */
static void client_resume(Client *const me);

/* ............................ Declares guards ............................ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(client_idle,
                       client_delay_req, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(client_idle)
    RKH_TRREG(TOUT_REQ,    NULL,   client_req,      &client_waiting),
    RKH_TRREG(PAUSE,       NULL,   NULL,            &client_paused),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(client_waiting, NULL, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(client_waiting)
    RKH_TRREG(START,       NULL,   client_start,    &client_using),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(client_using, NULL, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(client_using)
    RKH_TRREG(TOUT_USING,  NULL,   client_end,      &client_idle),
    RKH_TRREG(PAUSE,       NULL,   NULL,            &client_paused),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(client_paused,
                       client_pause, client_resume, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(client_paused)
    RKH_TRINT(TOUT_USING,  NULL,   client_end),
    RKH_TRREG(PAUSE,       NULL,   NULL,            &client_idle),
RKH_END_TRANS_TABLE

/* ............................. Active object ............................. */
struct Client
{
    RKH_SMA_T sma;          /* base structure */
    RKH_TMR_T usageTmr;     /* usage time */
    RKH_TMR_T waitReqTmr;   /* waiting request time */
};

RKH_SMA_CREATE(Client, cli0, CLI_PRIO_0, HCAL, &client_idle, client_init, NULL);
RKH_SMA_DEF_PTR(cli0);
RKH_SMA_CREATE(Client, cli1, CLI_PRIO_1, HCAL, &client_idle, client_init, NULL);
RKH_SMA_DEF_PTR(cli1);
RKH_SMA_CREATE(Client, cli2, CLI_PRIO_2, HCAL, &client_idle, client_init, NULL);
RKH_SMA_DEF_PTR(cli2);
RKH_SMA_CREATE(Client, cli3, CLI_PRIO_3, HCAL, &client_idle, client_init, NULL);
RKH_SMA_DEF_PTR(cli3);

RKH_ARRAY_SMA_CREATE(clis, NUM_CLIENTS)
{
    &cli0, &cli1, &cli2, &cli3
};

/* ------------------------------- Constants ------------------------------- */
static RKH_ROM_STATIC_EVENT(evToUse, TOUT_USING);
static RKH_ROM_STATIC_EVENT(evToReq, TOUT_REQ);
static RKH_ROM_STATIC_EVENT(evDone, DONE);

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Initial action ............................. */
static void
client_init(Client *const me, RKH_EVT_T *pe)
{
    RKH_TR_FWK_AO(CLI0);
    RKH_TR_FWK_AO(CLI1);
    RKH_TR_FWK_AO(CLI2);
    RKH_TR_FWK_AO(CLI3);
    RKH_TR_FWK_STATE(CLI0, &client_idle);
    RKH_TR_FWK_STATE(CLI0, &client_waiting);
    RKH_TR_FWK_STATE(CLI0, &client_using);
    RKH_TR_FWK_STATE(CLI0, &client_paused);

    RKH_TMR_INIT(&me->usageTmr, &evToUse, NULL);
    RKH_TMR_INIT(&me->waitReqTmr, &evToReq, NULL);
}

/* ............................ Effect actions ............................. */
static void
client_req(Client *const me, RKH_EVT_T *pe)
{
    ReqEvt *e_req;

    (void)pe;
    e_req = RKH_ALLOC_EVT(ReqEvt, REQ, me);
    e_req->clino = RKH_GET_PRIO(me);
    RKH_SMA_POST_FIFO(server, RKH_EVT_CAST(e_req), me);
    bsp_cli_req(e_req->clino);
}

static void
client_start(Client *const me, RKH_EVT_T *pe)
{
    RKH_TNT_T time;

    time = CLI_USING_TIME;
    RKH_TMR_ONESHOT(&me->usageTmr, RKH_UPCAST(RKH_SMA_T, me), time);
    bsp_cli_using(RKH_CAST(StartEvt, pe)->clino,
                  time / RKH_CFG_FWK_TICK_RATE_HZ);
}

static void
client_end(Client *const me, RKH_EVT_T *pe)
{
    (void)pe;

	RKH_SMA_POST_FIFO(server, &evDone, me);
    bsp_cli_done(RKH_GET_PRIO(me));
}

/* ............................. Entry actions ............................. */
static void
client_pause(Client *const me)
{
    rkh_tmr_stop(&me->waitReqTmr);
    bsp_cli_paused(RKH_GET_PRIO(me));
}

static void
client_delay_req(Client *const me)
{
    RKH_TNT_T time;

    time = CLI_REQ_TIME;
    RKH_TMR_ONESHOT(&me->waitReqTmr, RKH_UPCAST(RKH_SMA_T, me), time);
    bsp_cli_wait_req(RKH_GET_PRIO(me), time / RKH_CFG_FWK_TICK_RATE_HZ);
}

/* ............................. Exit actions .............................. */
static void
client_resume(Client *const me)
{
    bsp_cli_resumed(RKH_GET_PRIO(me));
}

/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
