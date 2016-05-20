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
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "bsp.h"
#include "scevt.h"
#include "server.h"

/* ----------------------------- Local macros ------------------------------ */
#define MAX_SIZEOF_QREQ         (2 * NUM_CLIENTS)

/* ------------------------------- Constants ------------------------------- */
struct Server
{
    RKH_SMA_T sma;      /* base structure */
    rui32_t ntot;       /* total number of attended requests */
                        /* number of attended requests of every client */
    rui32_t ncr[NUM_CLIENTS];
};

/* ============================= Active object ============================= */
RKH_SMA_CREATE(Server, server, 0, HCAL, &server_idle, server_init, NULL);
RKH_SMA_DEF_PTR(server);

/* ======================== States and pseudostates ======================== */
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

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_RQ_T queueReq;
static RKH_EVT_T *queueReqSto[MAX_SIZEOF_QREQ];

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

/* ============================ Initial action ============================= */
void
server_init(Server *const me)
{
    rint cn;

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

    rkh_rq_init(&queueReq, (const void **)queueReqSto, MAX_SIZEOF_QREQ, 
                CSMA(0));

    RKH_CAST(Server, me)->ntot = 0;
    for (cn = 0; cn < NUM_CLIENTS; ++cn)
        RKH_CAST(Server, me)->ncr[cn] = 0;
}

/* ============================ Effect actions ============================= */
void
server_start(Server *const me, RKH_EVT_T *pe)
{
    START_EVT_T *e_start;

    e_start = RKH_ALLOC_EVT(START_EVT_T, START);
    e_start->clino = RKH_CAST(REQ_EVT_T, pe)->clino;
    RKH_SMA_POST_FIFO(RKH_GET_SMA(RKH_CAST(REQ_EVT_T, pe)->clino),
                      RKH_EVT_CAST(e_start), me);
    bsp_svr_start(e_start->clino);
    ++RKH_CAST(Server, me)->ntot;
    ++RKH_CAST(Server, me)->ncr[CLI_ID(e_start->clino)];
}

void
server_end(Server *const me, RKH_EVT_T *pe)
{
    REQ_EVT_T *e;

    (void)pe;
    if ((e = (REQ_EVT_T *)rkh_fwk_recall((RKH_SMA_T*)me, &queueReq))
        != (REQ_EVT_T *)0)
    {
        bsp_svr_recall(e->clino);
    }

    bsp_svr_end();
}

void
server_defer(Server *const me, RKH_EVT_T *pe)
{
    (void)me;
    rkh_fwk_defer(&queueReq, pe);
}

void
server_terminate(Server *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    rkh_fwk_exit();
}

/* ============================= Entry actions ============================= */
void
server_pause(Server *const me)
{
    bsp_svr_paused(me->ntot, me->ncr);
}

/* ============================= Exit actions ============================== */
void
server_resume(Server *const me)
{
    REQ_EVT_T *e;

    if ((e = (REQ_EVT_T *)rkh_fwk_recall((RKH_SMA_T*)me, &queueReq))
        != (REQ_EVT_T *)0)
    {
        bsp_svr_recall(e->clino);
    }

    bsp_svr_resume();
}

/* ================================ Guards ================================= */

/* ------------------------------ End of file ------------------------------ */
