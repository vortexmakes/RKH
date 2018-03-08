/**
 *  \file       server.c
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
#include "bsp.h"
#include "shared.h"
#include "server.h"

/* ----------------------------- Local macros ------------------------------ */
#define MAX_SIZEOF_QREQ         (2 * NUM_CLIENTS)

/* ......................... Declares active object ........................ */
typedef struct Server Server;

/* ................... Declares states and pseudostates .................... */
RKH_DCLR_BASIC_STATE server_idle, server_busy, server_paused;

/* ........................ Declares initial action ........................ */
static void server_init(Server *const me, RKH_EVT_T *pe);

/* ........................ Declares effect actions ........................ */
static void server_start(Server *const me, RKH_EVT_T *pe);
static void server_end(Server *const me, RKH_EVT_T *pe);
static void server_defer(Server *const me, RKH_EVT_T *pe);
static void server_terminate(Server *const me, RKH_EVT_T *pe);

/* ......................... Declares entry actions ........................ */
static void server_pause(Server *const me);

/* ......................... Declares exit actions ......................... */
static void server_resume(Server *const me);

/* ............................ Declares guards ............................ */
/* ........................ States and pseudostates ........................ */
RKH_CREATE_BASIC_STATE(server_idle, NULL, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(server_idle)
    RKH_TRINT(TERM,    NULL,   server_terminate),
    RKH_TRREG(REQ,     NULL,   server_start,    &server_busy),
    RKH_TRREG(PAUSE,   NULL,   NULL,            &server_paused),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(server_busy, NULL, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(server_busy)
    RKH_TRINT(REQ,     NULL,   server_defer),
    RKH_TRINT(TERM,    NULL,   server_terminate),
    RKH_TRREG(DONE,    NULL,   server_end,      &server_idle),
    RKH_TRREG(PAUSE,   NULL,   NULL,            &server_paused),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(server_paused,
                       server_pause, server_resume, RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(server_paused)
    RKH_TRINT(REQ,     NULL,   server_defer),
    RKH_TRINT(DONE,    NULL,   NULL),
    RKH_TRINT(TERM,    NULL,   server_terminate),
    RKH_TRREG(PAUSE,   NULL,   NULL,            &server_idle),
RKH_END_TRANS_TABLE

/* ............................. Active object ............................. */
struct Server
{
    RKH_SMA_T sma;      /* base structure */
    rui32_t ntot;       /* total number of attended requests */
                        /* number of attended requests of every client */
    rui32_t ncr[NUM_CLIENTS];
};

RKH_SMA_CREATE(Server, server, 0, HCAL, &server_idle, server_init, NULL);
RKH_SMA_DEF_PTR(server);

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_QUEUE_T queueReq;
static RKH_EVT_T *queueReqSto[MAX_SIZEOF_QREQ];

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ............................ Initial action ............................. */
static void
server_init(Server *const me, RKH_EVT_T *pe)
{
    rInt cn;

    RKH_TR_FWK_AO(server);
    RKH_TR_FWK_STATE(server, &server_idle);
    RKH_TR_FWK_STATE(server, &server_busy);
    RKH_TR_FWK_STATE(server, &server_paused);
    RKH_TR_FWK_SIG(REQ);
    RKH_TR_FWK_SIG(START);
    RKH_TR_FWK_SIG(DONE);
    RKH_TR_FWK_SIG(TOUT_USING);
    RKH_TR_FWK_SIG(TOUT_REQ);
    RKH_TR_FWK_SIG(PAUSE);
    RKH_TR_FWK_SIG(TERM);

    rkh_queue_init(&queueReq, (const void **)queueReqSto, MAX_SIZEOF_QREQ, 
                CV(0));

    RKH_CAST(Server, me)->ntot = 0;
    for (cn = 0; cn < NUM_CLIENTS; ++cn)
        RKH_CAST(Server, me)->ncr[cn] = 0;
}

/* ............................ Effect actions ............................. */
static void
server_start(Server *const me, RKH_EVT_T *pe)
{
    StartEvt *e_start;

    e_start = RKH_ALLOC_EVT(StartEvt, START, me);
    e_start->clino = RKH_CAST(ReqEvt, pe)->clino;
    RKH_SMA_POST_FIFO(RKH_GET_SMA(RKH_CAST(ReqEvt, pe)->clino),
                      RKH_EVT_CAST(e_start), me);
    bsp_svr_start(e_start->clino);
    ++RKH_CAST(Server, me)->ntot;
    ++RKH_CAST(Server, me)->ncr[CLI_ID(e_start->clino)];
}

static void
server_end(Server *const me, RKH_EVT_T *pe)
{
    ReqEvt *e;

    (void)pe;
    if ((e = (ReqEvt *)rkh_sma_recall((RKH_SMA_T*)me, &queueReq))
        != (ReqEvt *)0)
    {
        bsp_svr_recall(e->clino);
    }

    bsp_svr_end();
}

static void
server_defer(Server *const me, RKH_EVT_T *pe)
{
    (void)me;
    rkh_sma_defer(&queueReq, pe);
}

static void
server_terminate(Server *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    rkh_fwk_exit();
}

/* ............................. Entry actions ............................. */
static void
server_pause(Server *const me)
{
    bsp_svr_paused(me->ntot, me->ncr);
}

/* ............................. Exit actions .............................. */
static void
server_resume(Server *const me)
{
    ReqEvt *e;

    if ((e = (ReqEvt *)rkh_sma_recall((RKH_SMA_T*)me, &queueReq))
        != (ReqEvt *)0)
    {
        bsp_svr_recall(e->clino);
    }

    bsp_svr_resume();
}

/* ................................ Guards ................................. */
/* ---------------------------- Global functions --------------------------- */
/* ------------------------------ End of file ------------------------------ */
