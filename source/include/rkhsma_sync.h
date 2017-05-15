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
 *  \file       rkhsma_sync.h
 *  \brief      ...
 *  \ingroup    sma
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.05.15  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHSMA_SYNC_H__
#define __RKHSMA_SYNC_H__

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
 *  Encapsulates the mechanism of blocking the event queue.
 *
 *  \param[in] me 		pointer to active object
 */
void rkh_sma_block(RKH_SMA_T *const me);

/**
 *  \brief
 *  Encapsulates the mechanism of signaling the thread waiting on the
 *  used event queue. Thus, the SMA is inserted in the ready list as
 *  ready-to-dispatch.
 *
 *  \param[in] me 		pointer to active object
 */
void rkh_sma_setReady(RKH_SMA_T *const me);

/**
 *  \brief
 *  Informs the underlying kernel that the SMA event queue is becoming
 *  empty. Thus, the SMA is removed from the ready list.
 *
 *  \param[in] me 		pointer to active object
 */
void rkh_sma_setUnready(RKH_SMA_T *const me);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
