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
 *  \file       rkhport.h
 *  \ingroup    prt
 *
 *  \brief      CIAA Osek multithread port
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  DaBa  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Darío Baliña  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
#ifndef __RKHT_H__
#define __RKHT_H__

/* ----------------------------- Include files ----------------------------- */
#include "os.h"             /* the main Osek include file */
/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/*
 * The RKH uses a set of integer quantities. That maybe machine or
 * compiler dependent.
 */

typedef sint8 ri8_t;
typedef sint16 ri16_t;
typedef sint32 ri32_t;
typedef uint8 rui8_t;
typedef uint16 rui16_t;
typedef uint32 rui32_t;

/*
 * The 'ruint' and 'rint' will normally be the natural size for a
 * particular machine. These types designates an integer type that is
 * usually fastest to operate with among all integer types.
 */

typedef unsigned int ruint;
typedef signed int rint;

/*
 * Boolean data type and constants.
 *
 * \note
 * The true (RKH_TRUE) and false (RKH_FALSE) values as defined as macro
 * definitions in \c rkhdef.h file.
 */

typedef boolean rbool_t;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */

#endif
/* ------------------------------ End of file ------------------------------ */
