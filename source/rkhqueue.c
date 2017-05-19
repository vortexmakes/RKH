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
 *  \file       rkhqueue.c
 *  \ingroup    apiQueue
 *
 *  \brief      Implements a queue (by reference) services.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.17.05  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhqueue.h"
#include "rkhassert.h"
#include "rkhsma_prio.h"
#include "rkhsma_sync.h"
#include "rkhfwk_module.h"
#include "rkhtrc_record.h"
#include "rkhtrc_filter.h"

#if RKH_CFG_QUE_EN == RKH_ENABLED

RKH_MODULE_NAME(rkhqueue)

/* ----------------------------- Local macros ------------------------------ */
#if RKH_CFG_QUE_GET_INFO_EN == RKH_ENABLED
    #define RKH_IUPDT_PUT(q)          ++ q->rqi.nputs
    #define RKH_IUPDT_GET(q)          ++ q->rqi.ngets
    #define RKH_IUPDT_EMPTY(q)        ++ q->rqi.nempty
    #define RKH_IUPDT_FULL(q)         ++ q->rqi.nfull
    #define RKH_IUPDT_READ(q)         ++ q->rqi.nreads
#else
    #define RKH_IUPDT_PUT(q)
    #define RKH_IUPDT_GET(q)
    #define RKH_IUPDT_EMPTY(q)
    #define RKH_IUPDT_FULL(q)
    #define RKH_IUPDT_READ(q)
#endif

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
rkh_queue_init(RKH_QUEUE_T *q, const void * *sstart, RKH_QUENE_T ssize,
            void *sma)
{
    RKH_SR_ALLOC();

    q->pstart = sstart;
    q->pin = q->pout = (void * *)sstart;
    q->nelems = ssize;
    q->qty = 0;
    q->pend = (void * *)&sstart[ssize];
    q->sma = (const struct RKH_SMA_T *)sma;
#if RKH_CFG_QUE_GET_LWMARK_EN == RKH_ENABLED
    q->nmin = q->nelems;
#endif
#if RKH_CFG_QUE_GET_INFO_EN == RKH_ENABLED
    q->rqi.nputs = q->rqi.ngets = q->rqi.nreads = q->rqi.nempty = 
                                                  q->rqi.nfull = 0;
#endif
    RKH_TR_QUE_INIT(q, (const struct RKH_SMA_T *)sma, ssize);
}

#if RKH_CFG_QUE_IS_FULL_EN == RKH_ENABLED
rbool_t
rkh_queue_is_full(RKH_QUEUE_T *q)
{
    RKH_QUENE_T qty;
    RKH_SR_ALLOC();

    RKH_ASSERT(q != (RKH_QUEUE_T *)0);

    RKH_ENTER_CRITICAL_();
    qty = q->qty;
    RKH_EXIT_CRITICAL_();

    return qty == q->nelems;
}
#endif

#if RKH_CFG_QUE_GET_NELEMS_EN == RKH_ENABLED
RKH_QUENE_T
rkh_queue_get_num(RKH_QUEUE_T *q)
{
    RKH_QUENE_T qty;
    RKH_SR_ALLOC();

    RKH_ASSERT(q != CQ(0));

    RKH_ENTER_CRITICAL_();
    qty = q->qty;
    RKH_EXIT_CRITICAL_();

    return qty;
}
#endif

#if RKH_CFG_QUE_GET_LWMARK_EN == RKH_ENABLED
RKH_QUENE_T
rkh_queue_get_lwm(RKH_QUEUE_T *q)
{
    RKH_QUENE_T nmin;
    RKH_SR_ALLOC();

    RKH_ASSERT(q != CQ(0));

    RKH_ENTER_CRITICAL_();
    nmin = q->nmin;
    RKH_EXIT_CRITICAL_();

    return nmin;
}
#endif

void *
rkh_queue_get(RKH_QUEUE_T *q)
{
    void *e = CV(0);
    RKH_SR_ALLOC();

    RKH_ASSERT(q != CQ(0));
    RKH_ENTER_CRITICAL_();

    if (q->sma != CSMA(0))
    {
        rkh_sma_block((RKH_SMA_T *)(q->sma));
    }
    else if (q->qty == 0)
    {
        RKH_IUPDT_EMPTY(q);
        RKH_EXIT_CRITICAL_();
        return e;
    }

    e = *q->pout++;
    --q->qty;

    if (q->pout == q->pend)
    {
        q->pout = (void * *)q->pstart;
    }

    RKH_IUPDT_GET(q);

    if ((q->sma != CSMA(0)) && (q->qty == 0))
    {
        rkh_sma_setUnready((RKH_SMA_T *)(q->sma));
        RKH_TR_QUE_GET_LAST(q);
        RKH_EXIT_CRITICAL_();
    }
    else
    {
        RKH_TR_QUE_GET(q, q->qty);
        RKH_EXIT_CRITICAL_();
    }
    return e;
}

void
rkh_queue_put_fifo(RKH_QUEUE_T *q, const void *pe)
{
    RKH_SR_ALLOC();

    RKH_ASSERT(q != CQ(0) && pe != (const void *)0);
    /*RKH_ENTER_CRITICAL_();*/
    RKH_ASSERT(q->qty < q->nelems);

    if (q->qty >= q->nelems)
    {
        RKH_IUPDT_FULL(q);
        RKH_TR_QUE_FULL(q);
        /*RKH_EXIT_CRITICAL_();*/
        return;
    }

    *q->pin++ = (char *)pe;
    ++q->qty;

    if (q->pin == q->pend)
    {
        q->pin = (void * *)q->pstart;
    }

    if (q->sma != CSMA(0))
    {
        rkh_sma_setReady((RKH_SMA_T *)(q->sma));
    }

#if RKH_CFG_QUE_GET_LWMARK_EN == RKH_ENABLED
    if (q->nmin > (RKH_QUENE_T)(q->nelems - q->qty))
    {
        q->nmin = (RKH_QUENE_T)(q->nelems - q->qty);
    }
#endif
    RKH_IUPDT_PUT(q);
    /*RKH_EXIT_CRITICAL_();*/
    RKH_TR_QUE_FIFO(q, q->qty, q->nmin);
}

#if RKH_CFG_QUE_PUT_LIFO_EN == RKH_ENABLED
void
rkh_queue_put_lifo(RKH_QUEUE_T *q, const void *pe)
{
    RKH_SR_ALLOC();

    RKH_ASSERT(q != CQ(0) && pe != (const void *)0);
    /*RKH_ENTER_CRITICAL_();*/
    RKH_ASSERT(q->qty < q->nelems);

    if (q->qty >= q->nelems)
    {
        RKH_IUPDT_FULL(q);
        RKH_TR_QUE_FULL(q);
        /*RKH_EXIT_CRITICAL_();*/
        return;
    }

    if (q->pout == (void * *)q->pstart)
    {
        q->pout = q->pend;
    }

    --q->pout;
    *q->pout = CV(pe);
    ++q->qty;

    RKH_IUPDT_PUT(q);

    if (q->sma != CSMA(0))
    {
        rkh_sma_setReady((RKH_SMA_T *)(q->sma));
    }

#if RKH_CFG_QUE_GET_LWMARK_EN == RKH_ENABLED
    if (q->nmin > (RKH_QUENE_T)(q->nelems - q->qty))
    {
        q->nmin = (RKH_QUENE_T)(q->nelems - q->qty);
    }
#endif
    /*RKH_EXIT_CRITICAL_();*/
    RKH_TR_QUE_LIFO(q, q->qty, q->nmin);
}
#endif

#if RKH_CFG_QUE_DEPLETE_EN == RKH_ENABLED
void
rkh_queue_deplete(RKH_QUEUE_T *q)
{
    RKH_SR_ALLOC();

    RKH_ASSERT(q != CQ(0));
    RKH_ENTER_CRITICAL_();
    q->qty = 0;
    q->pin = q->pout = (void * *)q->pstart;
    if (q->sma != CSMA(0))
    {
        rkh_sma_setUnready((RKH_SMA_T *)(q->sma));
    }
    RKH_TR_QUE_DPT(q);
    RKH_EXIT_CRITICAL_();
}
#endif

#if RKH_CFG_QUE_READ_EN == RKH_ENABLED
ruint
rkh_queue_read(RKH_QUEUE_T *q, void *pe)
{
    RKH_SR_ALLOC();

    RKH_ASSERT(q != CQ(0) && pe != (const void *)0);
    RKH_ENTER_CRITICAL_();

    if (q->qty == 0)
    {
        RKH_IUPDT_EMPTY(q);
        RKH_EXIT_CRITICAL_();
        return RKH_QUE_EMPTY;
    }

    pe = *q->pout;

    RKH_IUPDT_READ(q);
    RKH_EXIT_CRITICAL_();
    return RKH_QUE_OK;
}
#endif

#if RKH_CFG_QUE_GET_INFO_EN == RKH_ENABLED
void
rkh_queue_get_info(RKH_QUEUE_T *q, RKH_QUEI_T *pqi)
{
    RKH_SR_ALLOC();

    RKH_ENTER_CRITICAL_();
    *pqi = q->rqi;
    RKH_EXIT_CRITICAL_();
}

void
rkh_queue_clear_info(RKH_QUEUE_T *q)
{
    RKH_QUEI_T *prqi;
    RKH_SR_ALLOC();

    prqi = &q->rqi;

    RKH_ENTER_CRITICAL_();
    prqi->nputs = prqi->ngets = prqi->nreads = prqi->nempty = prqi->nfull = 0;
    RKH_EXIT_CRITICAL_();
}
#endif

#endif
/* ------------------------------ End of file ------------------------------ */
