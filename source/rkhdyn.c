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
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       rkhdyn.c
 *  \ingroup    fwk
 *
 *  \brief      Dynamic event (event with parameters) support.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */

#include "rkhrq.h"
#include "rkhassert.h"
#include "rkh.h"

RKH_MODULE_NAME(rkhdyn)

#if RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */

RKH_DYNE_TYPE rkh_eplist[RKH_CFG_FWK_MAX_EVT_POOL];

/* ---------------------------- Local variables ---------------------------- */

/**
 *  \brief
 *  Number of initialized event pools.
 */
static rui8_t rkhnpool;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

RKH_EVT_T *
rkh_fwk_ae(RKH_ES_T esize, RKH_SIG_T e)
{
    RKH_EVT_T *evt;
    rui8_t idx = 0;
    RKH_DYNE_TYPE *ep = rkh_eplist;
    RKH_SR_ALLOC();

    /* find the pool index that fits the requested event size ... */
    while (esize > RKH_DYNE_GET_ESIZE(ep))
    {
        ++idx;
        ++ep;
        /* cannot run out of registered pools */
        RKH_ASSERT(idx < rkhnpool);
    }

    RKH_DYNE_GET(ep, evt);      /* get e -- platform-dependent */
                                /* pool must not run out of events */
    RKH_ASSERT(evt != RKH_EVT_CAST(0));
    evt->e = e;                 /* set signal for this event */

    /*
     * Store the dynamic attributes of the event: the pool ID and the
     * reference counter = 0
     */
    evt->nref = 0;
    evt->pool = (rui8_t)(idx + (rui8_t)1);

    RKH_TR_FWK_AE(esize, evt, evt->pool - 1, evt->nref);
    return evt;
}

void
rkh_fwk_gc(RKH_EVT_T *e)
{
    RKH_SR_ALLOC();

    if (e->nref != 0)       /* is it a dynamic event? */
    {
        RKH_ENTER_CRITICAL_();

        if (e->nref > 1)    /* isn't this the last ref? */
        {
            --e->nref;      /* decrement the reference counter */
            RKH_TR_FWK_GC(e, e->pool, e->nref);
            RKH_EXIT_CRITICAL_();
        }
        else    /* this is the last reference to this event, recycle it */
        {
            /* cannot wrap around */
            rui8_t idx = (rui8_t)(e->pool - 1);
            RKH_TR_FWK_GCR(e, e->pool, e->nref);
            RKH_EXIT_CRITICAL_();

            RKH_ASSERT(idx < RKH_CFG_FWK_MAX_EVT_POOL);
            RKH_DYNE_PUT(&rkh_eplist[idx], e);
        }
    }
}

void
rkh_fwk_reserve(RKH_EVT_T *e)
{
    RKH_SR_ALLOC();

    RKH_ENTER_CRITICAL_();
    RKH_INC_REF(e);
    RKH_EXIT_CRITICAL_();
}

void
rkh_fwk_epool_register(void *sstart, rui32_t ssize, RKH_ES_T esize)
{
    RKH_SR_ALLOC();

    RKH_ASSERT(((rui8_t)(rkhnpool + (rui8_t)1)) <=
               RKH_CFG_FWK_MAX_EVT_POOL);

    ++rkhnpool;
    RKH_DYNE_INIT(&rkh_eplist[rkhnpool - 1], sstart, ssize, esize);
    RKH_TR_FWK_EPREG(rkhnpool, ssize, esize);
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
    rkh_rq_put_fifo(&sma->equeue, e);
    RKH_TR_SMA_FIFO(sma, e, sender, e->pool, e->nref);

    RKH_EXIT_CRITICAL_();
}
#endif

#if RKH_CFGPORT_NATIVE_EQUEUE_EN == RKH_ENABLED && \
    RKH_CFG_RQ_PUT_LIFO_EN == RKH_ENABLED
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
    rkh_rq_put_lifo(&sma->equeue, e);
    RKH_TR_SMA_LIFO(sma, e, sender, e->pool, e->nref);

    RKH_EXIT_CRITICAL_();
}
#endif

#if RKH_CFGPORT_NATIVE_EQUEUE_EN == RKH_ENABLED
RKH_EVT_T *
rkh_sma_get(RKH_SMA_T *sma)
{
    RKH_EVT_T *e;
    RKH_SR_ALLOC();

    e = rkh_rq_get(&sma->equeue);

    RKH_ASSERT(e != (RKH_EVT_T *)0);
     /* Because the variables are obtained outside critical section could be */
                                                         /* a race condition */
    RKH_TR_SMA_GET(sma, e, e->pool, e->nref, 
                   rkh_rq_get_num(&sma->equeue), rkh_rq_get_lwm(&sma->equeue));
    return e;
}
#endif

#if RKH_CFG_FWK_DEFER_EVT_EN == RKH_ENABLED
void
rkh_fwk_defer(RKH_RQ_T *q, const RKH_EVT_T *e)
{
    RKH_SR_ALLOC();

    RKH_ENTER_CRITICAL_();

    RKH_INC_REF(e);
    rkh_rq_put_fifo(q, e);
    RKH_TR_FWK_DEFER(q, e);

    RKH_EXIT_CRITICAL_();
}

RKH_EVT_T *
rkh_fwk_recall(RKH_SMA_T *sma, RKH_RQ_T *q)
{
    RKH_EVT_T *e;
    RKH_SR_ALLOC();

    e = rkh_rq_get(q);          /* get an event from deferred queue */
    if (e != RKH_EVT_CAST(0))   /* event available? */
    {
        /* post it to the front of the SMA's queue */
        RKH_SMA_POST_LIFO(sma, e, sma);
        RKH_ENTER_CRITICAL_();
        RKH_TR_FWK_RCALL(sma, e);

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
/* ------------------------------ End of file ------------------------------ */
