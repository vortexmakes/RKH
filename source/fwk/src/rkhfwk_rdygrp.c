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
 *  \file       rkhfwk_rdygrp.h
 *  \ingroup    fwk
 *  \brief      ...
 *  \details    ...
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.08.07  LeFr  v3.1.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhfwk_rdygrp.h"
#include "rkhitl.h"
#include "rkhfwk_bittbl.h"
#include "rkhassert.h"
#include "rkhfwk_module.h"

RKH_MODULE_NAME(rkhfwk_rdygrp)

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void 
rkh_rdygrp_init(RKHRdyGrp *const me)
{
    rui8_t *pTbl, i;

    me->grp = 0;
    for (pTbl = me->tbl, i = 0; i < RKH_NUM_RDYGRP; ++i, ++pTbl)
    {
        *pTbl = 0;
    }
}

rbool_t 
rkh_rdygrp_isReady(RKHRdyGrp *const me)
{
    return me->grp != 0;
}

void 
rkh_rdygrp_setReady(RKHRdyGrp *const me, rui8_t prio)
{
    RKH_REQUIRE(prio < RKH_CFG_FWK_MAX_SMA);
    me->grp |= rkh_bittbl_getBitMask(prio >> 3);
    me->tbl[prio >> 3] |= rkh_bittbl_getBitMask(prio & 0x07);
}

void 
rkh_rdygrp_setUnready(RKHRdyGrp *const me, rui8_t prio)
{
    RKH_REQUIRE(prio < RKH_CFG_FWK_MAX_SMA);
    if ((me->tbl[prio >> 3] &= ~rkh_bittbl_getBitMask(prio & 0x07)) == 0)
    {
        me->grp &= ~rkh_bittbl_getBitMask(prio >> 3);
    }
}

rui8_t 
rkh_rdygrp_findHighest(RKHRdyGrp *const me)
{
    rui8_t prio;

    prio = rkh_bittbl_getLeastBitSetPos(me->grp);
    prio = (rui8_t)((prio << 3) +
                    (rui8_t)rkh_bittbl_getLeastBitSetPos(me->tbl[prio]));
    return prio;
}

rui8_t 
rkh_rdygrp_traverse(RKHRdyGrp *const me, void (*rdyCb)(RdyCbArg *), 
                    RdyCbArg *rdyCbArg)
{
    rui8_t row, column, *pTbl, nBit, nRdyAO;

    nRdyAO = 0;
    if (me->grp != 0)
    {
        for (row = 0, pTbl = me->tbl; row < RKH_NUM_RDYGRP; ++pTbl, ++row)
        {
            for (column = *pTbl, nBit = 0; (column != 0) && (nBit < 8); 
                 ++nBit, column >>= 1)
            {
                if ((column & 1) != 0)
                {
                    ++nRdyAO;
                    rdyCbArg->aoRdyPrio = (row << 3) | nBit;
                    (*rdyCb)(rdyCbArg);
                }
            }
        }
    }
    return nRdyAO;
}

/* ------------------------------ End of file ------------------------------ */
