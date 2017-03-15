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
 *  \file       rkhportTest.h
 *  \ingroup    prt
 *
 *  \brief      Only to easily create the mock objecto of rkhport.c module.
 *  \warning    This temporal file is not contained in the official release.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.12.15  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void rkh_sma_activate(RKH_SMA_T *me, const RKH_EVT_T **qSto, RKH_RQNE_T qSize,
                      void *stkSto, rui32_t stkSize);

void rkh_sma_terminate(RKH_SMA_T *me);

#if defined(RKH_USE_TRC_SENDER)
void rkh_sma_post_fifo(RKH_SMA_T *me, const RKH_EVT_T *e,
                       const void *const sender);
#else
void rkh_sma_post_fifo(RKH_SMA_T *me, const RKH_EVT_T *e);
#endif

#if (RKH_CFG_RQ_PUT_LIFO_EN == RKH_ENABLED) && \
    (defined(RKH_USE_TRC_SENDER))
void rkh_sma_post_lifo(RKH_SMA_T *me, const RKH_EVT_T *e,
                       const void *const sender);
#else
void rkh_sma_post_lifo(RKH_SMA_T *me, const RKH_EVT_T *e);
#endif

RKH_EVT_T * rkh_sma_get(RKH_SMA_T *me);

/* ------------------------------ End of file ------------------------------ */
