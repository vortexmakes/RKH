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
 *  \file       rkhfwk_evtpool.h
 *  \brief      
 *  \ingroup    fwk
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.05.04  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHFWK_EVTPOOL_H__
#define __RKHFWK_EVTPOOL_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhitl.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
typedef struct RKHEvtPool RKHEvtPool;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/**
 *  \brief
 *  Encapsulates the creation of an event pool.
 *
 *  \param[in] me	    pointer to previously allocated memory pool 
 *                      structure.
 *  \param[in] stoStart	storage start. Pointer to memory from which 
 *                      memory blocks are allocated.
 *  \param[in] stoSize:	storage size. Size of the memory pool storage in 
 *                      bytes.
 *  \param[in] evtSize	event size. This number determines the size of each
 *                      memory block in the pool.
 */
void rkh_evtPool_init(RKHEvtPool *me, void *stoStart, rui32_t stoSize, 
                      RKH_ES_T evtSize);

/**
 *  \brief
 *  Encapsulates how RKH should obtain the block size of an event pool.
 *
 * \param[in] me		pointer to previously allocated memory pool 
 *                      structure.
 */
rui8_t rkh_evtPool_get_esize(RKHEvtPool *const me);

/**
 *  \brief
 *	Encapsulates how RKH should obtain an event \c evt from the
 *	event pool \c me.
 *
 *  \param[in] me		pointer to previously allocated memory pool 
 *                      structure.
 *  \param[in] evt      inter to a new event or NULL if the pool runs 
 *                      out of blocks.
 */
RKH_EVT_T *rkh_evtPool_get(RKHEvtPool *const me, RKH_EVT_T *evt);

/**
 *  \brief
 *	Encapsulates how RKH should return an event \c evt to the event
 *	pool \c me.
 *
 *  \param[in] me		pointer to previously allocated memory pool 
 *                      structure.
 *  \param[in] evt      pointer to the returned event.
 */
void rkh_evtPool_put(RKHEvtPool *const me, RKH_EVT_T *evt);

/**
 *  \brief
 *	Encapsulates how RKH should return the current number of memory 
 *	blocks used in the pool \c me.
 *
 *  \param[in] me		pointer to previously allocated memory pool 
 *                      structure.
 */
rui8_t rkh_evtPool_get_nused(RKHEvtPool *const me);

/**
 *  \brief
 *	Encapsulates how RKH should return the lowest number of free 
 *	blocks ever present in the pool \c me.
 *  This number provides valuable empirical data for proper sizing of the
 *  memory pool.
 *
 *  \param[in] me		pointer to previously allocated memory pool 
 *                      structure.
 */
rui8_t rkh_evtPool_get_nmin(RKHEvtPool *const me);

/**
 *  \brief
 *	Encapsulates how RKH should return the total number of blocks in the 
 *	pool \c me.
 *
 *  \param[in] me		pointer to previously allocated memory pool 
 *                      structure.
 */
void rkh_evtPool_get_nblock(RKHEvtPool *const me);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
