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
 *  \file       rkhdef.h
 *  \brief      Defines constants and macros.
 *
 *  All constants and macros are prefixed with RKH_ to provide a consistent 
 *  naming convention and to avoid namespace conflicts with other constants 
 *  and macros in your application.
 *
 *  \ingroup apiDef
 *
 *  \addtogroup api
 *  @{
 *  \addtogroup apiDef Definition library
 *  @{@}
 *  @}
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
#ifndef __RKHDEF_H__
#define __RKHDEF_H__

/* ----------------------------- Include files ----------------------------- */
/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* 
 * Bit's macros.
 */

/**
 *  \brief
 *  Create bit mask with single, specified bit set.
 *
 *  \param[in] bit      Bit number of bit to set.
 *
 *  \return
 *  Bit mask with single, specified bit set.
 *
 *  \ingroup apiDef 
 */
#define RKH_BIT(bit)            (1u << (bit))

/**@{
 *  \brief
 *  Create bit mask of specified bit size with single, specified bit set.
 *
 *  \param[in] bit      Bit number of bit to set.
 *
 *  \return
 *  Bit mask with single, specified bit set.
 *
 *  \ingroup apiDef 
 */
#define RKH_BIT08(bit)          ((rui8_t)((rui8_t) 1u << (bit)))
#define RKH_BIT16(bit)          ((rui16_t)((rui16_t) 1u << (bit)))
#define RKH_BIT32(bit)          ((rui32_t)((rui32_t) 1u << (bit)))
/*@}*/

/**
 *  \brief
 *  Shift a bit mask.
 *
 *  \param[in] bit_mask     Bit mask to shift.
 *  \param[in] bit_shift    Number of bit positions to left-shift bit mask.
 *
 *  \return
 *  Shifted bit mask.
 *
 *  \ingroup apiDef 
 */
#define RKH_BIT_MASK(bit_mask, bit_shift) \
    ((bit_mask) << (bit_shift))

/**@{
 *  \brief
 *  Shift a bit mask of specified bit size.
 *
 *  \param[in] bit_mask		Bit mask to shift.
 *  \param[in] bit_shift	Number of bit positions to left-shift bit mask.
 *
 *  \return
 *  Shifted bit mask.
 *
 *  \ingroup apiDef 
 */
#define RKH_BIT_MASK_08(bit_mask, bit_shift) \
    ((rui8_t)((rui8_t)(bit_mask) << (bit_shift)))
#define RKH_BIT_MASK_16(bit_mask, bit_shift) \
    ((rui16_t)((rui16_t)(bit_mask) << (bit_shift)))
#define RKH_BIT_MASK_32(bit_mask, bit_shift) \
    ((rui32_t)((rui32_t)(bit_mask) << (bit_shift)))
/*@}*/

/**@{
 *  \brief
 *  Set specified bit(s) in a value of specified bit size.
 *
 *  \param[in] val		Value to modify by setting specified bit(s).
 *  \param[in] mask		Mask of bits to set.
 *
 *  \return
 *  Modified value with specified bit(s) set.
 *
 *  \ingroup apiDef 
 */
#define RKH_BIT_SET_08(val, mask) \
    ((val) = (rui8_t)(((rui8_t)(val)) | ((rui8_t)(mask))))
#define RKH_BIT_SET_16(val, mask) \
    ((val) = (rui16_t)(((rui16_t)(val)) | ((rui16_t)(mask))))
#define RKH_BIT_SET_32(val, mask) \
    ((val) = (rui32_t)(((rui32_t)(val)) | ((rui32_t)(mask))))
/*@}*/

/**@{
 *  \brief
 *  Clear specified bit(s) in a value of specified bit size.
 *
 *  \param[in] val		Value to modify by clearing specified bit(s).
 *  \param[in] mask		Mask of bits to clear.
 *
 *  \return
 *  Modified value with specified bit(s) clear.
 *
 *  \ingroup apiDef 
 */
#define RKH_BIT_CLR_08(val, mask) \
    ((val) = (rui8_t)(((rui8_t)(val)) & ((rui8_t) ~(mask))))
#define RKH_BIT_CLR_16(val, mask) \
    ((val) = (rui16_t)(((rui16_t)(val)) & ((rui16_t) ~(mask))))
#define RKH_BIT_CLR_32(val, mask) \
    ((val) = (rui32_t)(((rui32_t)(val)) & ((rui32_t) ~(mask))))
/*@}*/

/**
 *  \brief
 *  Determine if specified bit(s) in a value are set.
 *
 *  \param[in] val		Value to check for specified bit(s) set.
 *  \param[in] mask		Mask of bits to check if set.
 *
 *  \return
 *  RKH_YES, if ALL specified bit(s) are set in value.
 *  RKH_NO,  if ALL specified bit(s) are NOT set in value.
 *
 *  \ingroup apiDef 
 */
#define RKH_BIT_IS_SET(val, mask) \
    ((((mask)  !=  0u)  && \
      (((val) & (mask)) == (mask))) ? (RKH_YES) : (RKH_NO))

/**
 *  \brief
 *  Determine if specified bit(s) in a value are clear.
 *
 *  \param[in] val		Value to check for specified bit(s) clear.
 *  \param[in] mask		Mask of bits to check if clear.
 *
 *  \return
 *  RKH_YES, if ALL specified bit(s) are clear in value.
 *  RKH_NO,  if ALL specified bit(s) are NOT clear in value.
 *
 *  \ingroup apiDef 
 */
#define RKH_BIT_IS_CLR(val, mask) \
    ((((mask)  !=  0u)  && \
      (((val) & (mask)) ==  0u)) ? (RKH_YES) : (RKH_NO))

/**
 *  \brief
 *  Determine if any specified bit(s) in a value are set.
 *
 *  \param[in] val		Value to check for specified bit(s) set.
 *  \param[in] mask		Mask of bits to check if set.
 *
 *  \return
 *  RKH_YES, if ALL specified bit(s) are set in value.
 *  RKH_NO,  if ALL specified bit(s) are NOT set in value.
 *
 *  \ingroup apiDef 
 */
#define RKH_BIT_IS_SET_ANY(val, mask) \
    ((((val) & (mask)) ==  0u) ? (RKH_NO) : (RKH_YES))

/**
 *  \brief
 *  Determine if any specified bit(s) in a value are clear.
 *
 *  \param[in] val		Value to check for specified bit(s) clear.
 *  \param[in] mask		Mask of bits to check if clear.
 *
 *  \return
 *  RKH_YES, if ALL specified bit(s) are clear in value.
 *  RKH_NO,  if ALL specified bit(s) are NOT clear in value.
 *
 *  \ingroup apiDef 
 */
#define RKH_BIT_IS_CLR_ANY(val, mask) \
    ((((val) & (mask)) == (mask)) ? (RKH_NO) : (RKH_YES))

/* -------------------------------- Constants ------------------------------ */
#define  RKH_NULL               ((void *) 0)

/**@{
 * \brief
 * Standard define.
 *
 *  \ingroup apiDef 
 */
#define  RKH_FALSE              0u
#define  RKH_TRUE               1u

#define  RKH_NO                 0u
#define  RKH_YES                1u

#define  RKH_DISABLED           0u
#define  RKH_ENABLED            1u

#define  RKH_INACTIVE           0u
#define  RKH_ACTIVE             1u

#define  RKH_INVALID            0u
#define  RKH_VALID              1u

#define  RKH_OFF                0u
#define  RKH_ON                 1u

#define  RKH_CLR                0u
#define  RKH_SET                1u

#define  RKH_FAIL               0u
#define  RKH_OK                 1u
/*@}*/

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
