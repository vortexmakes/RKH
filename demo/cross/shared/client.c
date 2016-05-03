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
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "server.h"
#include "client.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
#define CLI_REQ_TIME \
    (RKH_TNT_T)RKH_TIME_SEC((bsp_rand() % 5) + 2)
#define CLI_USING_TIME \
    (RKH_TNT_T)RKH_TIME_SEC((bsp_rand() % 5) + 1)

/* ------------------------------- Constants ------------------------------- */
static RKH_ROM_STATIC_EVENT(evToUse, TOUT_USING);
static RKH_ROM_STATIC_EVENT(evToReq, TOUT_REQ);
static RKH_ROM_STATIC_EVENT(evDone, DONE);

/* ======================== States and pseudostates ======================== */
RKH_CREATE_BASIC_STATE(cli_idle,
                       cli_delay_req, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(cli_idle)
    RKH_TRREG(TOUT_REQ,    NULL,   cli_req,    &cli_waiting),
    RKH_TRREG(PAUSE,       NULL,   NULL,       &cli_paused),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(cli_waiting, NULL, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(cli_waiting)
    RKH_TRREG(START,       NULL,   cli_start,  &cli_using),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(cli_using, NULL, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(cli_using)
    RKH_TRREG(TOUT_USING,  NULL,   cli_end,    &cli_idle),
    RKH_TRREG(PAUSE,       NULL,   NULL,       &cli_paused),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(cli_paused,
                       cli_pause, cli_resume, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(cli_paused)
    RKH_TRINT(TOUT_USING,  NULL,   cli_end),
    RKH_TRREG(PAUSE,       NULL,   NULL,       &cli_idle),
RKH_END_TRANS_TABLE

/* ---------------------------- Local data types --------------------------- */
struct Client
{
    RKH_SMA_T sma;          /* base structure */
    RKH_TMR_T usageTmr;     /* usage time */
    RKH_TMR_T waitReqTmr;   /* waiting request time */
};
/* ---------------------------- Global variables --------------------------- */
/* ============================= Active object ============================= */
RKH_SMA_CREATE(Client, cli0, CLI_PRIO_0, HCAL, &cli_idle, cli_init, NULL);
RKH_SMA_DEF_PTR(cli0);
RKH_SMA_CREATE(Client, cli1, CLI_PRIO_1, HCAL, &cli_idle, cli_init, NULL);
RKH_SMA_DEF_PTR(cli1);
RKH_SMA_CREATE(Client, cli2, CLI_PRIO_2, HCAL, &cli_idle, cli_init, NULL);
RKH_SMA_DEF_PTR(cli2);
RKH_SMA_CREATE(Client, cli3, CLI_PRIO_3, HCAL, &cli_idle, cli_init, NULL);
RKH_SMA_DEF_PTR(cli3);

RKH_ARRAY_SMA_CREATE(clis, NUM_CLIENTS)
{
    &cli0, &cli1, &cli2, &cli3
};

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

/* ============================ Initial action ============================= */
void
cli_init(Client *const me)
{
    RKH_TR_FWK_AO(CLI0);
    RKH_TR_FWK_AO(CLI1);
    RKH_TR_FWK_AO(CLI2);
    RKH_TR_FWK_AO(CLI3);
    RKH_TR_FWK_STATE(CLI0, &cli_idle);
    RKH_TR_FWK_STATE(CLI0, &cli_waiting);
    RKH_TR_FWK_STATE(CLI0, &cli_using);
    RKH_TR_FWK_STATE(CLI0, &cli_paused);

    RKH_TMR_INIT(&me->usageTmr, &evToUse, NULL);
    RKH_TMR_INIT(&me->waitReqTmr, &evToReq, NULL);
}

/* ============================ Effect actions ============================= */
void
cli_req(Client *const me, RKH_EVT_T *pe)
{
    REQ_EVT_T *e_req;

    (void)pe;
    e_req = RKH_ALLOC_EVT(REQ_EVT_T, REQ);
    e_req->clino = RKH_GET_PRIO(me);
    RKH_SMA_POST_FIFO(server, RKH_EVT_CAST(e_req), me);
    bsp_cli_req(e_req->clino);
}

void
cli_start(Client *const me, RKH_EVT_T *pe)
{
    RKH_TNT_T time;

    (void)pe;
    time = CLI_USING_TIME;
    RKH_TMR_ONESHOT(&me->usageTmr, RKH_UPCAST(RKH_SMA_T, me), time);
    bsp_cli_using(RKH_CAST(START_EVT_T, pe)->clino,
                  time / RKH_CFG_FWK_TICK_RATE_HZ);
}

void
cli_end(Client *const me, RKH_EVT_T *pe)
{
    (void)pe;
    (void)me;

	RKH_SMA_POST_FIFO(server, &evDone, me);
    bsp_cli_done(RKH_GET_PRIO(me));
}

/* ============================= Entry actions ============================= */
void
cli_pause(Client *const me)
{
    rkh_tmr_stop(&me->waitReqTmr);
    bsp_cli_paused(RKH_GET_PRIO(me));
}

void
cli_delay_req(Client *const me)
{
    RKH_TNT_T time;

    time = CLI_REQ_TIME;
    RKH_TMR_ONESHOT(&me->waitReqTmr, RKH_UPCAST(RKH_SMA_T, me), time);
    bsp_cli_wait_req(RKH_GET_PRIO(me), time / RKH_CFG_FWK_TICK_RATE_HZ);
}

/* ============================= Exit actions ============================== */
void
cli_resume(Client *const me)
{
    bsp_cli_resumed(RKH_GET_PRIO(me));
}

/* ================================ Guards ================================= */

/* ------------------------------ End of file ------------------------------ */
