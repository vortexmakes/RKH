/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       rkhsma.c
 *  \ingroup    sch
 *
 *  \brief      Implements the SMA(active object) registration.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhassert.h"
#include "rkhitl.h"
#include "rkhsma.h"
#include "rkhtrc_record.h"
#include "rkhtrc_filter.h"
#include "rkhfwk_hook.h"

RKH_MODULE_NAME(rkhsma)

/* ----------------------------- Local macros ------------------------------ */
#if RKH_CFG_QUE_GET_LWMARK_EN == RKH_ENABLED
    #define RKH_SMA_GET_NMIN(ao)    (ao)->equeue.nmin
#else
    #define RKH_SMA_GET_NMIN(ao)    0
#endif

/* ------------------------------- Constants ------------------------------- */
#if R_TRC_AO_NAME_EN == RKH_DISABLED
RKHROM char noname[] = "null";
#endif

/** Default virtual table for the RKH_SMA_T structure */
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
const RKHSmaVtbl rkhSmaVtbl = 
{
    rkh_sma_activate,
    NULL,
    rkh_sma_post_fifo,
    rkh_sma_post_lifo
};
#endif

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
RKH_SMA_T *rkh_sptbl[RKH_CFG_FWK_MAX_SMA];  /* registered SMA table */

/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
rkh_sma_register(RKH_SMA_T *sma)
{
    rui8_t prio = RKH_GET_PRIO(sma);
    RKH_SR_ALLOC();

    RKH_REQUIRE((prio <= (rui8_t)RKH_LOWEST_PRIO) &&
                (rkh_sptbl[prio] == (RKH_SMA_T *)0));

    RKH_ENTER_CRITICAL_();
    rkh_sptbl[prio] = sma;
    RKH_TR_SMA_REG(sma, prio);
    RKH_EXIT_CRITICAL_();
}

void
rkh_sma_unregister(RKH_SMA_T *sma)
{
    rui8_t prio = RKH_GET_PRIO(sma);
    RKH_SR_ALLOC();

    RKH_REQUIRE((prio <= (rui8_t)RKH_CFG_FWK_MAX_SMA) &&
                (rkh_sptbl[prio] == sma));

    RKH_ENTER_CRITICAL_();
    rkh_sptbl[prio] = (RKH_SMA_T *)0;
    RKH_TR_SMA_UNREG(sma, prio);
    RKH_EXIT_CRITICAL_();
}

#if RKH_CFG_SMA_RT_CTOR_EN == RKH_ENABLED
void 
rkh_sma_ctor(RKH_SMA_T *me, const RKHSmaVtbl *vtbl)
{
    rkh_sm_ctor(&me->sm);   /* Call base object constructor */
                            /* (in fact an initializer operation) */

    /* Link vptr to virtual table of me */
#if RKH_CFG_SMA_VFUNCT_EN == RKH_ENABLED
    me->vptr = (vtbl != (const RKHSmaVtbl *)0) ? vtbl : &rkhSmaVtbl;
#endif
}
#endif

#if RKH_CFGPORT_NATIVE_SCHEDULER_EN == RKH_ENABLED
void
rkh_sma_terminate(RKH_SMA_T *sma)
{
    RKH_SR_ALLOC();

    rkh_sma_unregister(sma);
    RKH_TR_SMA_TERM(sma, RKH_GET_PRIO(sma));
}

void
rkh_sma_activate(RKH_SMA_T *sma, const RKH_EVT_T * *qs, RKH_QUENE_T qsize,
                 void *stks, rui32_t stksize)
{
    (void)stks;
    (void)stksize;
    RKH_SR_ALLOC();

    RKH_REQUIRE((qs != (const RKH_EVT_T * *)0) && (qsize != (RKH_QUENE_T)0));

    rkh_queue_init(&sma->equeue, (const void * *)qs, qsize, sma);
    rkh_sma_register(sma);
    rkh_sm_init((RKH_SM_T *)sma);
    RKH_TR_SMA_ACT(sma, RKH_GET_PRIO(sma), qsize);
}
#endif

#if RKH_CFGPORT_NATIVE_EQUEUE_EN == RKH_ENABLED
void
#if defined(RKH_USE_TRC_SENDER)
rkh_sma_post_fifo(RKH_SMA_T *sma, const RKH_EVT_T *e,
                  const void *const sender)
#else
rkh_sma_post_fifo(RKH_SMA_T * sma, const RKH_EVT_T * e)
#endif
{
    RKH_SR_ALLOC();

    RKH_HOOK_SIGNAL(e);
    RKH_ENTER_CRITICAL_();

    RKH_INC_REF(e);
    rkh_queue_put_fifo(&sma->equeue, e);
    RKH_TR_SMA_FIFO(sma, e, sender, e->pool, e->nref, sma->equeue.qty, 
                    RKH_SMA_GET_NMIN(sma));

    RKH_EXIT_CRITICAL_();
}
#endif

#if RKH_CFGPORT_NATIVE_EQUEUE_EN == RKH_ENABLED && \
    RKH_CFG_QUE_PUT_LIFO_EN == RKH_ENABLED
void
#if defined(RKH_USE_TRC_SENDER)
rkh_sma_post_lifo(RKH_SMA_T *sma, const RKH_EVT_T *e,
                  const void *const sender)
#else
rkh_sma_post_lifo(RKH_SMA_T * sma, const RKH_EVT_T * e)
#endif
{
    RKH_SR_ALLOC();

    RKH_HOOK_SIGNAL(e);
    RKH_ENTER_CRITICAL_();

    RKH_INC_REF(e);
    rkh_queue_put_lifo(&sma->equeue, e);
    RKH_TR_SMA_LIFO(sma, e, sender, e->pool, e->nref, sma->equeue.qty, 
                    RKH_SMA_GET_NMIN(sma));

    RKH_EXIT_CRITICAL_();
}
#endif

#if RKH_CFGPORT_NATIVE_EQUEUE_EN == RKH_ENABLED
RKH_EVT_T *
rkh_sma_get(RKH_SMA_T *sma)
{
    RKH_EVT_T *e;
    RKH_SR_ALLOC();

    e = rkh_queue_get(&sma->equeue);

    RKH_ASSERT(e != (RKH_EVT_T *)0);
    /* Because the variables are obtained outside critical section could be */
    /* a race condition */
    RKH_TR_SMA_GET(sma, e, e->pool, e->nref, 
                   sma->equeue.qty, RKH_SMA_GET_NMIN(sma));
    return e;
}
#endif

#if RKH_CFG_FWK_DEFER_EVT_EN == RKH_ENABLED
void
rkh_sma_defer(RKH_QUEUE_T *q, const RKH_EVT_T *e)
{
    RKH_SR_ALLOC();

    RKH_ENTER_CRITICAL_();

    RKH_INC_REF(e);
    rkh_queue_put_fifo(q, e);
    RKH_TR_SMA_DEFER(q, e);

    RKH_EXIT_CRITICAL_();
}

RKH_EVT_T *
rkh_sma_recall(RKH_SMA_T *sma, RKH_QUEUE_T *q)
{
    RKH_EVT_T *e;
    RKH_SR_ALLOC();

    e = rkh_queue_get(q);          /* get an event from deferred queue */
    if (e != RKH_EVT_CAST(0))   /* event available? */
    {
        /* post it to the front of the SMA's queue */
        RKH_SMA_POST_LIFO(sma, e, sma);
        RKH_ENTER_CRITICAL_();
        RKH_TR_SMA_RCALL(sma, e);

#if RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED
        if (e->nref != 0)   /* is it a dynamic event? */
        {
            /*
             * After posting to the SMA's queue the event must be referenced
             * at least twice: once in the deferred event queue (eq->get()
             * did NOT decrement the reference counter) and once in the
             * SMA's event queue.
             */
            RKH_ASSERT(e->nref > 1);

            /*
             * We need to decrement the reference counter once, to account
             * for removing the event from the deferred event queue.
             */
            --e->nref;
        }
#endif
        RKH_EXIT_CRITICAL_();
    }
    return e;
}
#endif

#if RKH_CFG_SMA_GET_INFO_EN == RKH_ENABLED
void
rkh_sma_clear_info(RKH_SMA_T *sma)
{
    RKH_SMAI_T *psi;
    RKH_SR_ALLOC();

    psi = &sma->sinfo;

    RKH_ENTER_CRITICAL_();
    sma->sinfo.ndevt = sma->sinfo.exectr = 0;
    RKH_EXIT_CRITICAL_();
}

void
rkh_sma_get_info(RKH_SMA_T *sma, RKH_SMAI_T *psi)
{
    RKH_SR_ALLOC();

    RKH_ENTER_CRITICAL_();
    *psi = sma->sinfo;
    RKH_EXIT_CRITICAL_();
}
#endif

/* ------------------------------ End of file ------------------------------ */
