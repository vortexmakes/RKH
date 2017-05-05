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
 *  \file       rkhfwk_dynevt.c
 *  \ingroup    fwk
 *
 *  \brief      Dynamic event (event with parameters) support.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.05.04  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhtrc_record.h"
#include "rkhtrc_filter.h"
#include "rkhassert.h"
#include "rkhfwk_dynevt.h"

RKH_MODULE_NAME(rkhfwk_dynevt)

#if RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
static RKHEvtPoolMgr evtPools[RKH_CFG_FWK_MAX_EVT_POOL];

/* ---------------------------- Local variables ---------------------------- */
/**
 *  \brief
 *  Number of registered event pools.
 */
static rui8_t nextFreeEvtPool;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
#if 0
RKH_EVT_T *
rkh_fwk_ae(RKH_ES_T esize, RKH_SIG_T e, const void *const sender)
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

    RKH_TR_FWK_AE(esize, evt, RKH_DYNE_GET_NUSED(ep), RKH_DYNE_GET_NMIN(ep), 
                  sender);
    return evt;
}

void
rkh_fwk_gc(RKH_EVT_T *e, const void *const sender)
{
    RKH_DYNE_TYPE *ep;
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
            ep = &rkh_eplist[idx]; 
            RKH_TR_FWK_GCR(e, RKH_DYNE_GET_NUSED(ep) - 1, 
                           RKH_DYNE_GET_NMIN(ep), sender);
            RKH_EXIT_CRITICAL_();

            RKH_ASSERT(idx < RKH_CFG_FWK_MAX_EVT_POOL);
            RKH_DYNE_PUT(ep, e);
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
#endif
void
rkh_fwk_registerEvtPool(void *sstart, rui32_t ssize, RKH_ES_T esize)
{
    RKHEvtPool *ep;
    RKH_SR_ALLOC();

    RKH_REQUIRE((nextFreeEvtPool + 1) <= RKH_CFG_FWK_MAX_EVT_POOL);
    ep = rkh_evtPool_init(sstart, ssize, esize);
    RKH_ENSURE(ep != (RKHEvtPool *)0);
    evtPools[nextFreeEvtPool].evtPool = ep;
    ++nextFreeEvtPool;
    RKH_TR_FWK_EPREG(nextFreeEvtPool, ssize, esize, 
                     rkh_evtPool_get_nblock(ep));
}

void
rkh_dynEvt_init(void)
{
    rint i;
    RKHEvtPoolMgr *ep;

    nextFreeEvtPool = 0;
    for (i = 0, ep = evtPools; i < RKH_CFG_FWK_MAX_EVT_POOL; ++i)
    {
        ep->evtPool = (RKHEvtPool *)0;
    }
}
#endif

/* ------------------------------ End of file ------------------------------ */
