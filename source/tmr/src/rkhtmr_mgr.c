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
 *  \file       rkhtmr_mgr.c
 *  \ingroup    apiTmr
 *
 *  \brief      Implements the software timer.
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
#include "rkhtmr_mgr.h"
#include "rkhtmr_base.h"
#include "rkhassert.h"
#include "rkhfwk_hook.h"
#include "rkhsma.h"
#include "rkhtrc_record.h"
#include "rkhtrc_filter.h"
#include "rkhtmr.h"

#if RKH_CFG_TMR_EN == RKH_ENABLED
/*#if RKH_CFGPORT_NATIVE_TMR_EN == RKH_ENABLED*/

RKH_MODULE_NAME(rkhtmr_mgr)

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
struct RKHTmrMgr
{

	RKHTmrBase base;
    RKH_TMR_T osTmr;
};

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKHTmrMgr tmrObjs[RKH_CFG_TMR_MAX_TIMERS];

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
rInt 
rkh_tmrMgr_init(void)
{
    rInt i;
    RKHTmrMgr *tmr;

    for (i = 0, tmr = tmrObjs; i < RKH_CFG_TMR_MAX_TIMERS; ++i, ++tmr)
    {
        ((RKHTmrBase *)tmr)->ao = 0;
    }
    return i;
}

RKHTmrMgr *
rkh_tmrMgr_ctor(char *name, RKH_SIG_T signal, RKH_SMA_T *ao, 
                RKHTick nTick, RKHTick period)
{
    rInt i;
    RKHTmrMgr *tmr;

    for (i = 0, tmr = tmrObjs; i < RKH_CFG_TMR_MAX_TIMERS; ++i, ++tmr)
    {
        if (((RKHTmrBase *)tmr)->ao == (RKH_SMA_T *)0)
        {
            ((RKHTmrBase *)tmr)->ao = ao;
            return tmr;
        }
    }
    return (RKHTmrMgr *)0;
}

#endif
/* ------------------------------ End of file ------------------------------ */
