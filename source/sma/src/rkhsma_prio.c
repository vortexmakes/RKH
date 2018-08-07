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
 *  \file       rkhsma_prio.c
 *  \brief      Native priority mechanism for active object scheduling
 *  \ingroup    sma
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.05.15  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhsma_prio.h"
#include "rkhfwk_bittbl.h"
#include "rkhassert.h"
#include "rkhfwk_module.h"
#include "rkhitl.h"

RKH_MODULE_NAME(rkhsma_prio)

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKHRdyGrp readyGroup;  /* ready group of active objects */

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void 
rkh_smaPrio_init(void)
{
    rui8_t *pTbl, i;

    readyGroup.grp = 0;
    for (pTbl = readyGroup.tbl, i = 0; i < RKH_NUM_RDYGRP; ++i, ++pTbl)
    {
        *pTbl = 0;
    }
}

rbool_t 
rkh_smaPrio_isNotReady(void)
{
    return readyGroup.grp == 0;
}

rbool_t 
rkh_smaPrio_isReady(void)
{
    return readyGroup.grp != 0;
}

void 
rkh_smaPrio_setReady(rui8_t prio)
{
    RKH_REQUIRE(prio < RKH_CFG_FWK_MAX_SMA);
    readyGroup.grp |= rkh_bittbl_getBitMask(prio >> 3);
    readyGroup.tbl[prio >> 3] |= rkh_bittbl_getBitMask(prio & 0x07);
}

void 
rkh_smaPrio_setUnready(rui8_t prio)
{
    RKH_REQUIRE(prio < RKH_CFG_FWK_MAX_SMA);
    if ((readyGroup.tbl[prio >> 3] &= ~rkh_bittbl_getBitMask(prio & 0x07)) == 0)
    {
        readyGroup.grp &= ~rkh_bittbl_getBitMask(prio >> 3);
    }
}

rui8_t 
rkh_smaPrio_findHighest(void)
{
    rui8_t prio;

    prio = rkh_bittbl_getLeastBitSetPos(readyGroup.grp);
    prio = (rui8_t)((prio << 3) +
                    (rui8_t)rkh_bittbl_getLeastBitSetPos(readyGroup.tbl[prio]));
    return prio;
}

/* ------------------------------ End of file ------------------------------ */
