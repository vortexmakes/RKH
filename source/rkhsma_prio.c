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
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
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
#if RKH_CFG_FWK_MAX_SMA <= 8
    #define RKH_NUM_RDYGRP      1
#elif RKH_CFG_FWK_MAX_SMA > 8 && RKH_CFG_FWK_MAX_SMA <= 16
    #define RKH_NUM_RDYGRP      2
#elif RKH_CFG_FWK_MAX_SMA > 16 && RKH_CFG_FWK_MAX_SMA <= 24
    #define RKH_NUM_RDYGRP      3
#elif RKH_CFG_FWK_MAX_SMA > 24 && RKH_CFG_FWK_MAX_SMA <= 32
    #define RKH_NUM_RDYGRP      4
#elif RKH_CFG_FWK_MAX_SMA > 32 && RKH_CFG_FWK_MAX_SMA <= 40
    #define RKH_NUM_RDYGRP      5
#elif RKH_CFG_FWK_MAX_SMA > 40 && RKH_CFG_FWK_MAX_SMA <= 48
    #define RKH_NUM_RDYGRP      6
#elif RKH_CFG_FWK_MAX_SMA > 48 && RKH_CFG_FWK_MAX_SMA <= 56
    #define RKH_NUM_RDYGRP      7
#elif RKH_CFG_FWK_MAX_SMA > 56 && RKH_CFG_FWK_MAX_SMA <= 64
    #define RKH_NUM_RDYGRP      8
#endif

/* ---------------------------- Local data types --------------------------- */
/**
 *  \brief
 *	SMA ready table.
 *
 *  Each SMA is assigned a unique priority level between 0 and
 *  RKH_LOWEST_PRIO.
 *  Each SMA that is ready to run is placed in a ready list consisting of two
 *  variables, rkhrg.grp and rkhrg.tbl[]. SMA priorities are grouped
 *  (8 SMA per group) in rkhrg.grp. Each bit in rkhrg.grp is used to
 *  indicate whenever any SMA in a group is ready to run. When a task
 *  is ready to run it also sets its corresponding bit in the ready table,
 *  rkhrg.tbl[]. The size of rkhrg.tbl[] depends on RKH_LOWEST_PRIO
 *  (see rkhcfg.h).
 *
 *  SMA's priority = | 0 | 0 | Y | Y | Y | X | X | X |
 *
 *  Y's:	bit position in rkhrg.grp and
 *          index into rkhrg.tbl[RKH_LOWEST_PRIO / 8 + 1]\n
 *  X's:	bit position in rkhrg.tbl[RKH_LOWEST_PRIO / 8 + 1]
 *
 *  The lower 3 bits (X's) of the SMA's priority are used to determine the
 *  bit position in rkhrg.tbl[], while the next three most significant bits
 *  (Y's) are used to determine the index into rkhrg.tbl[].
 *
 *  To determine which priority (and thus which SMA) will run next, the
 *  scheduler determines the lowest priority number that has its bit set in
 *  rkhrg.tbl[]. The relationship between rkhrg.grp and rkhrg.tbl[] is
 *  given by the following rules:
 *
 *  Bit 0 in rkhrg.grp is 1 when any bit in rkhrg.tbl[0] is 1.\n
 *  Bit 1 in rkhrg.grp is 1 when any bit in rkhrg.tbl[1] is 1.\n
 *  Bit 2 in rkhrg.grp is 1 when any bit in rkhrg.tbl[2] is 1.\n
 *  Bit 3 in rkhrg.grp is 1 when any bit in rkhrg.tbl[3] is 1.\n
 *  Bit 4 in rkhrg.grp is 1 when any bit in rkhrg.tbl[4] is 1.\n
 *  Bit 5 in rkhrg.grp is 1 when any bit in rkhrg.tbl[5] is 1.\n
 *  Bit 6 in rkhrg.grp is 1 when any bit in rkhrg.tbl[6] is 1.\n
 *  Bit 7 in rkhrg.grp is 1 when any bit in rkhrg.tbl[7] is 1.
 *
 *  [JL]
 */
typedef struct
{
    /**
     *  \brief
     *  Each bit in rkhrg.grp is used to indicate whenever any SMA in a group
     *  is ready to run.
     */
    rui8_t grp;

    /**
     *  \brief
     *  When a task is ready to run it also sets its corresponding bit in the
     *  ready table, rkhrg.tbl[].
     */
    unsigned char tbl[RKH_NUM_RDYGRP];
} RKH_RG_T;

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_RG_T readyGroup;  /* ready group of active objects */

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void 
rkh_smaPrio_init(void)
{
    unsigned char *pTbl, i;

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
