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
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/**
 *  \brief
 *  Encapsulates the initialization of publish-subscribe module.
 */
void rkh_pubsub_init(void);

int rkh_pubsub_subscribe(rui8_t channel, const RKH_SMA_T *me);
int rkh_pubsub_unsubcribe(rui8_t channel, const RKH_SMA_T *me);
int rkh_pubsub_unsubscribeAll(const RKH_SMA_T *me);
int rkh_pubsub_publish(rui8_t channel, RKH_EVT_T *event, 
                       const void *const sender);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
