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
 *  \file       rkhfwk_evtpool.c
 *  \ingroup    fwk
 *  \brief      Implements the event pool manager for supporting dynamic 
 *              events based on native memory pool module (rkhmp).
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.05.09  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhassert.h"
#include "rkhfwk_dynevt.h"
#include "rkhmp.h"

RKH_MODULE_NAME(rkhfwk_evtpool)

#if ((RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED) && \
     (RKH_CFGPORT_NATIVE_DYN_EVT_EN == RKH_ENABLED))
/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
struct RKHEvtPool
{
    RKH_MP_T memPool;
};

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKHEvtPool evtPools[RKH_CFG_FWK_MAX_EVT_POOL];

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
rkh_evtPool_init(void)
{
    rint i;
    RKHEvtPool *ep;

    for (i = 0, ep = evtPools; i < RKH_CFG_FWK_MAX_EVT_POOL; ++i, ++ep)
    {
        ((RKH_MP_T *)ep)->free = (void *)0;
    }
}

RKHEvtPool *
rkh_evtPool_getPool(void *stoStart, rui32_t stoSize, RKH_ES_T evtSize)
{
    rint i;
    RKHEvtPool *ep;

    for (i = 0, ep = evtPools; i < RKH_CFG_FWK_MAX_EVT_POOL; ++i, ++ep)
    {
        if (((RKH_MP_T *)ep)->free == (void *)0)
        {
            ((RKH_MP_T *)ep)->free = ep; /* rkh_mp_init(...); */
            return ep;
        }
    }
    return (RKHEvtPool *)0;
}

rui8_t 
rkh_evtPool_getBlockSize(RKHEvtPool *const me)
{
    return 0;
}

RKH_EVT_T *
rkh_evtPool_get(RKHEvtPool *const me)
{
    return (RKH_EVT_T *)0;
}

void 
rkh_evtPool_put(RKHEvtPool *const me, RKH_EVT_T *evt)
{
}

rui8_t 
rkh_evtPool_getNumUsed(RKHEvtPool *const me)
{
    return 0;
}

rui8_t 
rkh_evtPool_getNumMin(RKHEvtPool *const me)
{
    return 0;
}

rui8_t 
rkh_evtPool_getNumBlock(RKHEvtPool *const me)
{
    return 0;
}
#endif

/* ------------------------------ End of file ------------------------------ */
