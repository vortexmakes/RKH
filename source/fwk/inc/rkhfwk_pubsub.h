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
 *  \brief      Specifies the publish-subscribe interface.
 *  \details    This module addresses the specific issue of how to notify a 
 *              set of interested active objects (clients) in a timely way 
 *              that a value that they care about has changed, especially when 
 *              the notification process is to be repeated for a relatively 
 *              long period of time. It does this without requiring the data
 *              server to have any a priori knowledge about its clients. 
 *              The basic solution offered by PubSub module is to have the 
 *              clients "subscribe" to the server to be notified about the 
 *              value in question according to the policy: "when the value 
 *              changes", receiving a proper event carrying the value of 
 *              interest.
 *              This means, for example, that sensor data can be easily shared 
 *              to elements that may not even exist when the sensor proxies 
 *              are written.
 *              Also, minimizes computational effort for notification of 
 *              clients and across a communications bus and minimizes the bus 
 *              bandwidth required for notification of the appropriate clients.
 *
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
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHFWK_PUBSUB_H__
#define __RKHFWK_PUBSUB_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhitl.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
#define RKH_CFG_FWK_MAX_SUBS_CHANNELS   16

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/**
 *  \brief
 *  Encapsulates the initialization of publish-subscribe module.
 */
void rkh_pubsub_init(void);

/**
 *  \brief
 *  Adds an active object to the notification list of an event channel.
 *  Each subscription registers a client’s interest in one event channel 
 *  (topic). This module posts published events to the registered clients in 
 *  order to forward events that were published to channel that match this 
 *  subscription.
 *
 *  \param[in] channel  indicates the topic to which the active object 
 *                      (client) wants to subscribe.
 *  \param[in] ao       pointer to previously created active object to
 *                      subscribe.
 */
void rkh_pubsub_subscribe(rui8_t channel, const RKH_SMA_T *ao);

/**
 *  \brief
 *  Unsubscribes an active object from topic.
 *
 *  \param[in] channel  indicates the topic that the active object wishes
 *                      to unsubscribe from.
 *  \param[in] ao       pointer to previously created active object to 
 *                      unsubscribe.
 */
void rkh_pubsub_unsubscribe(rui8_t channel, const RKH_SMA_T *ao);

/**
 *  \brief
 *  Unsubscribes an active object from all topics.
 *
 *  \param[in] ao       pointer to previously created active object to 
 *                      unsubscribe.
 */
void rkh_pubsub_unsubscribeAll(const RKH_SMA_T *ao);

/**
 *  \brief
 *
 *  \param[in] channel  identifies the information channel to which event is
 *                      published.
 *  \param[in] event    pointer to event to publish
 *  \param[in] sender	pointer to the sender object. It is not necessarily a 
 *                      pointer to an active object. In fact, if 
 *                      rkh_pubsub_publish() is called from an interrupt or 
 *                      other context, it can create a unique object just to 
 *                      unambiguously identify the publisher of the event.
 *
 *  \return
 *  The number of found ready active objects.
 */
rui8_t rkh_pubsub_publish(rui8_t channel, RKH_EVT_T *event, 
                          const void *const sender);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
