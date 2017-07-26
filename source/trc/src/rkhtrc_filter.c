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
 *  \file       rkhtrc_filter.c
 *  \brief      Runtime trace filter implementation.
 *  \ingroup    aptTrc
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.21.04  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhtrc_filter.h"
#include "rkhfwk_bittbl.h"
#include "rkhassert.h"

#if RKH_CFG_TRC_RTFIL_EN == RKH_ENABLED
/* ----------------------------- Local macros ------------------------------ */
/*
 * This macro is needed only if the module requires to check expressions 
 * that ought to be true as long as the program  is running.
 */
RKH_MODULE_NAME(rkhtrc_filter)

/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/**
 *  \brief
 *  Filter table of trace events.
 *
 *  The trace filter management is similar to the native priority scheme.
 *  In this case, each trace event is assigned a unique number
 *  (See RKH_TE_<group>_<event> definitions). When a event is ready to record 
 *  a trace its corresponding bit in the filter table must be clear. The size 
 *  of trceftbl[] depends on #RKH_TOT_NUM_TRC_EVTS.
 *
 *  Trace event number = | 0 | Y | Y | Y | Y | X | X | X |\n
 *
 *  Y's:	index into trceftbl[ #RKH_TRC_MAX_EVENTS_IN_BYTES ] table.\n
 *  X's:	bit position in trceftbl[ Y's ].\n
 *
 *  The lower 3 bits (X's) of the trace event number are used to determine
 *  the bit position in trceftbl[], while the next four most significant bits
 *  (Y's) are used to determine the index into trceftbl[].
 */
static rui8_t trceftbl[RKH_TRC_MAX_EVENTS_IN_BYTES];

/**
 *  \brief
 *  Filter table of trace groups.
 *
 *  Each bit in #trcgfilter is used to indicate whenever any trace group
 *  is filtered out its events. See RKH_TG_<group> and RKH_TG_T.
 *
 *  \code
 *  bit position =   7   6   5   4   3   2   1   0   -- Groups
 *  trcgfilter   = | Y | Y | Y | Y | Y | Y | Y | Y |
 *                           |		         |   |___ RKH_TG_MP
 *						     |			     |_______ RKH_TG_QUE
 *                           |				          ...
 *                           |_______________________ RKH_TG_FWK
 *	\endcode
 */
static rui8_t trcgfilter;

/**
 *  \brief
 *  Filter table of trace points associated with the SMA (AO).
 *
 *  The trace filter management is similar to the native priority scheme.
 *  In this case, each SMA is assigned a unique priority number. When a SMA
 *  is ready to record a trace its corresponding bit in the filter table
 *  must be clear. The size of #trcsmaftbl[] depends on
 *  #RKH_CFG_FWK_MAX_SMA (see rkhcfg.h).
 *
 *  SMA priority number = | Y | Y | Y | Y | Y | X | X | X |\n
 *
 *  Y's:	index into trcsmaftbl[ #RKH_TRC_MAX_SMA ] table.\n
 *  X's:	bit position in trcsmaftbl[ Y's ].\n
 *
 *  The lower 3 bits (X's) of the SMA priority number are used to determine
 *  the bit position in trcsmaftbl[], while the next five most significant bits
 *  (Y's) are used to determine the index into trcsmaftbl[].
 */
static rui8_t trcsmaftbl[RKH_TRC_MAX_SMA];

/**
 *  \brief
 *  Filter table of trace points associated with the event signals.
 *	Similar to trcsmaftbl[].
 *
 *  Signal number = | Y | ... | Y | Y | Y | X | X | X |\n
 *
 *  Y's:	index into trcsigftbl[ #RKH_TRC_MAX_SIGNALS ] table.\n
 *  X's:	bit position in trcsigftbl[ Y's ].\n
 *
 *  The lower 3 bits (X's) of the event signal are used to determine the bit
 *  position in trcsigftbl[], while the next most significant bits (Y's) are
 *  used to determine the index into trcsigftbl[].
 */
static rui8_t trcsigftbl[RKH_TRC_MAX_SIGNALS];

/** 
 *  \brief
 *  Map a trace event ID to its corresponding filter.
 */
static RKHROM RKH_GMTBL_T trcgmtbl[] =
{
    {RKH_MP_TTBL_OFFSET,    RKH_MP_TTBL_RANGE},
    {RKH_QUE_TTBL_OFFSET,    RKH_QUE_TTBL_RANGE},
    {RKH_SMA_TTBL_OFFSET,   RKH_SMA_TTBL_RANGE},
    {RKH_SM_TTBL_OFFSET,    RKH_SM_TTBL_RANGE},
    {RKH_TIM_TTBL_OFFSET,   RKH_TIM_TTBL_RANGE},
    {RKH_FWK_TTBL_OFFSET,   RKH_FWK_TTBL_RANGE},
    {RKH_USR_TTBL_OFFSET,   RKH_USR_TTBL_RANGE},
    {RKH_UT_TTBL_OFFSET,    RKH_UT_TTBL_RANGE}
};

/**
 *  \brief
 *  The tables to filter trace events related to signal and active objects.
 */
static const RKH_TRC_FIL_T fsig = {RKH_TRC_MAX_SIGNALS,   trcsigftbl};
static const RKH_TRC_FIL_T fsma = {RKH_TRC_MAX_SMA,       trcsmaftbl};

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
setAllFilters(rui8_t *filterTbl, rui8_t value, ruint size)
{
    rui8_t *ft, ix, c;

    for (ft = filterTbl, ix = 0,
         c = (rui8_t)((value == FILTER_OFF) ? 0xFF : 0);
         ix < size; ++ix, ++ft)
    {
        *ft = c;
    }
}

static void
setOneFilter(rui8_t *filterByte, rui8_t value, rui8_t bitPos)
{
    if (value == FILTER_OFF)
    {
        *filterByte |= rkh_bittbl_getBitMask(bitPos);
    }
    else
    {
        *filterByte &= ~rkh_bittbl_getBitMask(bitPos);
    }
}

static rbool_t
isOffFilter(rui8_t *filterTbl, RKH_TE_ID_T filter)
{
    rui8_t x;
    RKH_TE_ID_T y;

    y = filter >> 3;
    x = (rui8_t)(filter & 7);
    return (*(filterTbl + y) & rkh_bittbl_getBitMask(x)) != 0;
}

static const RKH_TRC_FIL_T *
getFilterTable(RKHFilter fd)
{
    RKH_REQUIRE(fd < RKHFilterNums);
    return (fd == RKHFilterSignal) ? &fsig : &fsma;
}

/* ---------------------------- Global functions --------------------------- */
void 
rkh_trc_filter_group_(rui8_t ctrl, RKH_TG_T grp, rui8_t mode)
{
    RKH_GM_OFFSET_T offset;
    RKH_GM_RANGE_T range;

    if (grp == RKH_TRC_ALL_GROUPS)
    {
        trcgfilter = (rui8_t)((ctrl == FILTER_OFF) ? 0xFF : 0);
        return;
    }

    setOneFilter(&trcgfilter, ctrl, grp);

    if (mode == ECHANGE)
    {
        offset = trcgmtbl[grp].offset;
        range = trcgmtbl[grp].range;
        setAllFilters(&trceftbl[offset], ctrl, range);
    }
}

void 
rkh_trc_filter_event_(rui8_t ctrl, RKH_TE_ID_T evt)
{
    RKH_TG_T grp;
    RKH_TE_ID_T e;
    RKH_GM_OFFSET_T offset;

    RKH_ASSERT(evt <= RKH_TRC_ALL_EVENTS);

    if (evt == RKH_TRC_ALL_EVENTS)
    {
        setAllFilters(trceftbl, ctrl, RKH_TRC_MAX_EVENTS_IN_BYTES);
        trcgfilter = (rui8_t)((ctrl == FILTER_OFF) ? 0xFF : 0);
    }
    else
    {
        e = GETEVT(evt);
        grp = GETGRP(evt);
        offset = (RKH_GM_OFFSET_T)(trcgmtbl[grp].offset + (e >> 3));

        setOneFilter(&trceftbl[offset], ctrl, e & 7);
        if (ctrl == FILTER_OFF)
        {
            trcgfilter |= rkh_bittbl_getBitMask(grp);
        }
    }
}

rbool_t 
rkh_trc_isoff_(RKH_TE_ID_T e)
{
    RKH_TE_ID_T evt;
    RKH_TG_T grp;
    RKH_GM_OFFSET_T offset;

    evt = GETEVT(e);
    grp = GETGRP(e);
    offset = trcgmtbl[grp].offset;

    return (((trcgfilter & rkh_bittbl_getBitMask(grp)) != 0) && 
              isOffFilter(&trceftbl[offset], evt));
}

void 
rkh_trc_symFil(RKHFilter fd, RKH_TRC_FSLOT slot, rui8_t mode)
{
    rui8_t x, onoff;
    RKH_TRC_FSLOT y;
    const RKH_TRC_FIL_T *filter;

    filter = getFilterTable(fd);
    RKH_REQUIRE(slot <= (filter->size << 3));
    onoff = (rui8_t)(mode & RKH_FILTER_MODE_MASK);

    if (mode & RKH_TRC_ALL_FILTERS)
    {
        setAllFilters(filter->tbl, onoff, filter->size);
    }
    else
    {
        y = (RKH_TRC_FSLOT)(slot >> 3);
        x = (rui8_t)(slot & 7);
        setOneFilter(filter->tbl + y, onoff, x);
    }
}

rbool_t 
rkh_trc_symFil_isoff(RKHFilter fd, RKH_TRC_FSLOT slot)
{
    const RKH_TRC_FIL_T *filter;

    filter = getFilterTable(fd);
    RKH_REQUIRE(slot <= (filter->size << 3));
    return isOffFilter(filter->tbl, (RKH_TE_ID_T)slot);
}

void 
rkh_trc_filter_get(RKH_FilterTbl *outFilterTbl)
{
    if (outFilterTbl == (RKH_FilterTbl *)0)
        return;
    outFilterTbl->signal = &fsig;
    outFilterTbl->ao = &fsma;
    outFilterTbl->event = trceftbl;
    outFilterTbl->group = &trcgfilter;
    outFilterTbl->grpFilMap = trcgmtbl;
}

#endif

/* ------------------------------ End of file ------------------------------ */
