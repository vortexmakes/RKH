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
#include "rkhsma_prio.h"
#include "rkhitl.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define RKH_CFG_FWK_MAX_SUBS_CHANNELS   32

/* ---------------------------- Local data types --------------------------- */
typedef struct PubSub PubSub;
struct PubSub
{
    RKHRdyGrp channels[RKH_CFG_FWK_MAX_SUBS_CHANNELS];
};

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static PubSub abstractObserver;     /* Singleton */

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void 
rkh_pubsub_init(void)
{
    RKHRdyGrp *pCh;
    rui8_t nCh;

    for (pCh = abstractObserver.channels, nCh = 0; 
         nCh < RKH_CFG_FWK_MAX_SUBS_CHANNELS; 
         ++nCh, ++pCh)
    {
        pCh->grp = 0;
    }
}

/* ------------------------------ End of file ------------------------------ */
