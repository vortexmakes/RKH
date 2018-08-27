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
 *  \file       rkhfwk_pubsub.h
 *  \ingroup    fwk
 *  \brief      Implements the publish-subscribe interface.
 *  \details    This module addresses the specific issue of how to notify a 
 *              set of interested active objects (clients) in a timely way 
 *              that a value that they care about has nChanged, especially when 
 *              the notification process is to be repeated for a relatively 
 *              long period of time. It does this without requiring the data
 *              server to have any a priori knowledge about its clients. 
 *              The basic solution offered by PubSub module is to have the 
 *              clients "subscribe" to the server to be notified about the 
 *              value in question according to the policy: "when the value 
 *              nChanges", receiving a proper event carrying the value of 
 *              interest.
 *              This means, for example, that sensor data can be easily shared 
 *              to elements that may not even exist when the sensor proxies 
 *              are written.
 *              Also, minimizes computational effort for notification of 
 *              clients and across a communications bus and minimizes the bus 
 *              bandwidth required for notification of the appropriate clients.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.08.06  LeFr  v3.1.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhfwk_pubsub.h"
#include "rkhfwk_rdygrp.h"
#include "rkhsma.h"
#include "rkhassert.h"
#include "rkhevt.h"
#include "rkhfwk_dynevt.h"

RKH_MODULE_NAME(rkhfwk_pubsub)

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
typedef struct PubSub PubSub;
struct PubSub
{
    RKHRdyGrp channels[RKH_CFG_FWK_MAX_SUBS_CHANNELS];
};

typedef struct PubArg PubArg;
struct PubArg
{
    RdyCbArg base;
    RKH_EVT_T *event;
    const void *sender;
};

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static PubSub observer;     /* Singleton */

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
publish(RdyCbArg *arg)
{
    PubArg *realArg;

    RKH_REQUIRE(RKH_GET_SMA(arg->aoRdyPrio) != (const RKH_SMA_T *)0); 
    realArg = (PubArg *)arg;
    RKH_SMA_POST_FIFO(RKH_GET_SMA(arg->aoRdyPrio), 
                      realArg->event, realArg->sender);
}

/* ---------------------------- Global functions --------------------------- */
void 
rkh_pubsub_init(void)
{
    RKHRdyGrp *pCh;
    rui8_t nCh;

    for (pCh = observer.channels, nCh = 0; 
         nCh < RKH_CFG_FWK_MAX_SUBS_CHANNELS; 
         ++nCh, ++pCh)
    {
        rkh_rdygrp_init(pCh);
    }
}

void
rkh_pubsub_subscribe(rui8_t channel, const RKH_SMA_T *ao)
{
    RKH_SR_ALLOC();

    RKH_REQUIRE((ao != (const RKH_SMA_T *)0) && 
                (channel < RKH_CFG_FWK_MAX_SUBS_CHANNELS));
    RKH_ENTER_CRITICAL_();
    rkh_rdygrp_setReady(&observer.channels[channel], RKH_GET_PRIO(ao));
    RKH_EXIT_CRITICAL_();
}

void
rkh_pubsub_unsubscribe(rui8_t channel, const RKH_SMA_T *ao)
{
    RKH_SR_ALLOC();

    RKH_REQUIRE((ao != (const RKH_SMA_T *)0) && 
                (channel < RKH_CFG_FWK_MAX_SUBS_CHANNELS));
    RKH_ENTER_CRITICAL_();
    rkh_rdygrp_setUnready(&observer.channels[channel], RKH_GET_PRIO(ao));
    RKH_EXIT_CRITICAL_();
}

void 
rkh_pubsub_unsubscribeAll(const RKH_SMA_T *ao)
{
    RKHRdyGrp *pCh;
    rui8_t nCh;

    RKH_SR_ALLOC();

    RKH_REQUIRE(ao != (const RKH_SMA_T *)0);
    RKH_ENTER_CRITICAL_();
    for (pCh = observer.channels, nCh = 0; 
         nCh < RKH_CFG_FWK_MAX_SUBS_CHANNELS; 
         ++nCh, ++pCh)
    {
        rkh_rdygrp_setUnready(pCh, RKH_GET_PRIO(ao));
    }
    RKH_EXIT_CRITICAL_();
}

rui8_t 
rkh_pubsub_publish(rui8_t channel, RKH_EVT_T *event, 
                   const void *const sender)
{
    rui8_t nRdyAo;
    PubArg publishArg;
    RKH_SR_ALLOC();

    publishArg.event = event;
    publishArg.sender = sender;
    RKH_ENTER_CRITICAL_();
    RKH_INC_REF(event);
    nRdyAo = rkh_rdygrp_traverse(&observer.channels[channel], 
                                 publish, (RdyCbArg *)&publishArg);
    RKH_EXIT_CRITICAL_();
    RKH_FWK_GC(event, sender);
    return nRdyAo;
}

/* ------------------------------ End of file ------------------------------ */
