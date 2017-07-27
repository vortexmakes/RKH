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
 *  \file       rkhfwk_cast.h
 *  \brief      Defines casting operations which are internally used by RKH
 *  \ingroup    fwk
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.17.05  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHFWK_CAST_H__
#define __RKHFWK_CAST_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtype.h"
#include "rkhcfg.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/**
 *  \brief
 *  Convert a pointer to a base-class. 
 *
 *  In other words, upcasting allows us to treat a derived type as though 
 *  it were its base type.
 *
 *  \ingroup apiAO
 */
#define RKH_UPCAST(BaseType_, me_)          ((BaseType_ *)me_)

/**
 *  \brief
 *  Converts a base-class pointer to a derived-class pointer.
 *
 *  \ingroup apiAO
 */
#define RKH_DOWNCAST(DerivedType_, me_)     ((DerivedType_ *)me_)

/**
 *  \brief
 *  Perform downcast of a reference of a base class to one of its derived
 *  classes.
 *
 *	\sa
 *	\link RKH_EVT_T single inheritance in C \endlink, and
 *	\link RKH_CREATE_BASIC_STATE another example \endlink.
 *
 *  \usage
 *  \code
 *  void
 *  svr_start( const struct RKH_SMA_T *me, RKH_EVT_T *pe )
 *  {
 *      START_EVT_T *e_start;
 *
 *      e_start = RKH_ALLOC_EVT( START_EVT_T, START, me );
 *      e_start->clino = RKH_CAST(REQ_EVT_T, pe)->clino;
 *      RKH_SMA_POST_FIFO( RKH_GET_SMA( RKH_CAST(REQ_EVT_T, pe)->clino ),
 *												RKH_EVT_CAST(e_start), me );
 *  }
 *  \endcode
 */
#define RKH_CAST(_type, _obj)     ((_type *)(_obj))

/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
