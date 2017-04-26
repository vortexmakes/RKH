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
 *  \file       rkhrdy.h
 *  \brief      Native priority management.
 *  \ingroup    sch
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
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHRDY_H__
#define __RKHRDY_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhcfg.h"
#include "rkhtype.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/**
 *  \brief
 *	This macro evaluates to true if all SMAs are not ready to run.
 *
 *  \param[in] rg		ready group.
 */
#define RKH_RDY_IS_EMPTY(rg) \
    ((rg).grp == 0)

/**
 *  \brief
 *	This macro evaluates to true if any SMA is ready to run.
 *
 *  \param[in] rg		ready group.
 */
#define RKH_RDY_ISNOT_EMPTY(rg) \
    ((rg).grp != 0)

/**
 *  \brief
 *  Making a SMA ready-to-run inserting it into the ready list.
 *
 *  The lower 3 bits of the SMA's priority are used to determine the bit
 *  position in rkhrg.tbl[], while the next three most significant bits are
 *  used to determine the index into rkhrg.tbl[].
 *
 *  \param[in] rg		ready group.
 *  \param[in] p		number of SMA's priotity.
 */
#define RKH_RDY_INSERT(rg, p) \
    (rg).grp |= rkh_bittbl_getBitMask[(p) >> 3]; \
    (rg).tbl[(p) >> 3] |= rkh_bittbl_getBitMask[(p) & 0x07]

/**
 *  \brief
 *  Removing a SMA from the ready list.
 *
 *  Clears the ready bit of the SMA in rkhrg.tbl[] and clears the bit in
 *  rkhrg.grp only if all SMAs in a group are not ready to run, i.e. all bits
 *  in rkhrg.tbl[prio >> 3] are 0.
 *
 *  \param[in] rg		ready group.
 *  \param[in] p		number of SMA's priotity.
 */
#define RKH_RDY_REM(rg, p) \
    if (((rg).tbl[(p) >> 3] &= ~rkh_bittbl_getBitMask[(p) & 0x07]) == 0) \
        (rg).grp &= ~rkh_bittbl_getBitMask[(p) >> 3]

/**
 *  \brief
 *	Finding the highest priority SMA ready to run.
 *
 *	Another table lookup is performed, rather than scanning through the table
 *	starting with rkhrg.tbl[0] to find the highest priority task ready to
 *	run. Eight bits are used to represent when tasks are ready in a group. The 
 *  least significant bit has the highest priority. Using this byte to index 
 *  the table returns the bit position of the highest priority bit set, a 
 *  number between 0 and 7.
 *
 *  \param[in] rg		ready group.
 *  \param[in] p		the found highest priority is assigned to \a p.
 */
#define RKH_RDY_FIND_HIGHEST(rg, p) \
    (p) = rkh_bittbl_getLeastBitSetPos((rg).grp); \
    (p) = (rui8_t)(((p) << 3) + \
                   (rui8_t)rkh_bittbl_getLeastBitSetPos((rg).tbl[(p)]))

/* -------------------------------- Constants ------------------------------ */
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

/* ------------------------------- Data types ------------------------------ */
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

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
