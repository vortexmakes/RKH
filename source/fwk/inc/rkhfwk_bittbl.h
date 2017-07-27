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
 *  \file       rkhfwk_bittbl.h
 *  \brief      Specifies the interface of the mapping table manager to deal 
 *              with native priority algorithm.
 *  \ingroup    fwk
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
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHFWK_BITTBL_H__
#define __RKHFWK_BITTBL_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtype.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
#define RKH_INVALID_BITPOS      (rui8_t)0xff

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/**
 *  \brief
 *  Get the bit mask from a bit position (from an 8-bit value).
 *
 *  \param[in] bitPos   bit position.
 *
 *	\return
 *  The bit mask from a bit position (from an 8-bit value) if bitPos is less 
 *  than 8, otherwise RKH_INVALID_BITPOS.
 */
rui8_t rkh_bittbl_getBitMask(rui8_t bitPos);

/**
 *  \brief
 *  Used to return the bit position of the least significant bit set - a 
 *  number between 0 and 7 (from an 8-bit value).
 *
 *  \param[in] value    data value to retrieve the least significant bit set.
 *
 *	\return
 *  The bit position of the least significant bit set - a number between 0 
 *  and 7 (from an 8-bit value).
 */
rui8_t rkh_bittbl_getLeastBitSetPos(rui8_t value);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
