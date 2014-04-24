/*
 *	file: rkhdef.h
 *	Last updated for version: 2.4.00
 *	Date of the last update:  April 15, 2014
 *
 * 	Copyright (C) 2010 Leandro Francucci. All rights reserved.
 *
 * 	RKH is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 *  RKH is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RKH, see copying.txt file.
 *
 * Contact information:
 * RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * e-mail:			lf@vxtsolutions.com.ar
 */

/**
 * 	\file rkhdef.h
 *	\brief
 *	This platform-independent file contains many standard constants and 
 *	macros.
 *
 *	All constants and macros are prefixed with RKH_DEF_ to provide a 
 *	consistent naming convention and to avoid namespace conflicts with other 
 *	constants and macros in your application.
 */


#ifndef __RKHDEF_H__
#define __RKHDEF_H__


#define  RKH_DEF_NULL               ((void *)0)


/* --- Standard defines  -------------------------------------------------- */

#define  RKH_DEF_FALSE				0u
#define  RKH_DEF_TRUE               1u

#define  RKH_DEF_NO                 0u
#define  RKH_DEF_YES                1u

#define  RKH_DEF_DISABLED           0u
#define  RKH_DEF_ENABLED			1u

#define  RKH_DEF_INACTIVE           0u
#define  RKH_DEF_ACTIVE             1u

#define  RKH_DEF_INVALID            0u
#define  RKH_DEF_VALID              1u

#define  RKH_DEF_OFF                0u
#define  RKH_DEF_ON                 1u

#define  RKH_DEF_CLR                0u
#define  RKH_DEF_SET                1u

#define  RKH_DEF_FAIL               0u
#define  RKH_DEF_OK                 1u


/* --- Bit's macros ------------------------------------------------------- */

/**
 * 	\brief
 * 	Create bit mask with single, specified bit set.
 *
 * 	\param bit				Bit number of bit to set.
 *
 * 	\return
 * 	Bit mask with single, specified bit set.
 */

#define RKH_DEF_BIT(bit)			(1u << (bit))


/**@{
 * 	\brief
 * 	Create bit mask of specified bit size with single, specified bit set.
 *
 * 	\param bit				Bit number of bit to set.
 *
 * 	\return
 * 	Bit mask with single, specified bit set.
 */

#define RKH_DEF_BIT08(bit)			(( rkhui8_t)(( rkhui8_t)1u  << (bit)))
#define RKH_DEF_BIT16(bit)        	((rkhui16_t)((rkhui16_t)1u  << (bit)))
#define RKH_DEF_BIT32(bit)        	((rkhui32_t)((rkhui32_t)1u  << (bit)))
/*@}*/


/**
 * 	\brief
 * 	Shift a bit mask.
 *
 * 	\param bit_mask			Bit mask to shift.
 * 	\param bit_shift		Number of bit positions to left-shift bit mask.
 *
 * 	\return
 * 	Shifted bit mask.
 */

#define	RKH_DEF_BIT_MASK(bit_mask, bit_shift) \
									((bit_mask) << (bit_shift))


/**@{
 * 	\brief
 * 	Shift a bit mask of specified bit size.
 *
 * 	\param bit_mask			Bit mask to shift.
 * 	\param bit_shift		Number of bit positions to left-shift bit mask.
 *
 * 	\return
 * 	Shifted bit mask.
 */

#define RKH_DEF_BIT_MASK_08(bit_mask, bit_shift) \
						((rkhui8_t)((rkhui8_t)(bit_mask) << (bit_shift)))
#define RKH_DEF_BIT_MASK_16(bit_mask, bit_shift) \
						((rkhui8_t)((rkhui8_t)(bit_mask) << (bit_shift)))
#define RKH_DEF_BIT_MASK_32(bit_mask, bit_shift) \
						((rkhui8_t)((rkhui8_t)(bit_mask) << (bit_shift)))
/*@}*/


/**@{
 * 	\brief
 * 	Set specified bit(s) in a value of specified bit size.
 *
 * 	\param val				Value to modify by setting specified bit(s).
 * 	\param mask				Mask of bits to set.
 *
 * 	\return
 * 	Modified value with specified bit(s) set.
 */

#define RKH_DEF_BIT_SET_08(val, mask) \
				((val) = (rkhui8_t)(((rkhui8_t)(val)) | ((rkhui8_t)(mask))))
#define RKH_DEF_BIT_SET_16(val, mask) \
				((val) = (rkhui16_t)(((rkhui16_t)(val)) | ((rkhui16_t)(mask))))
#define RKH_DEF_BIT_SET_32(val, mask) \
				((val) = (rkhui32_t)(((rkhui32_t)(val)) | ((rkhui32_t)(mask))))
/*@}*/


/**@{
 * 	\brief
 * 	Clear specified bit(s) in a value of specified bit size.
 *
 * 	\param val				Value to modify by clearing specified bit(s).
 * 	\param mask				Mask of bits to clear.
 *
 * 	\return
 * 	Modified value with specified bit(s) clear.
 */

#define RKH_DEF_BIT_CLR_08(val, mask) \
				((val) = (rkhui8_t)(((rkhui8_t)(val)) & ((rkhui8_t)~(mask))))
#define RKH_DEF_BIT_CLR_16(val, mask) \
				((val) = (rkhui16_t)(((rkhui16_t)(val)) & ((rkhui16_t)~(mask))))
#define RKH_DEF_BIT_CLR_08(val, mask) \
				((val) = (rkhui32_t)(((rkhui32_t)(val)) & ((rkhui32_t)~(mask))))
/*@}*/


/**
 * 	\brief
 * 	Determine if specified bit(s) in a value are set.
 *
 * 	\param val				Value to check for specified bit(s) set.
 * 	\param mask				Mask of bits to check if set.
 *
 * 	\return
 * 	RKH_DEF_YES, if ALL specified bit(s) are set in value.
 * 	RKH_DEF_NO,  if ALL specified bit(s) are NOT set in value.
 */

#define RKH_DEF_BIT_IS_SET(val, mask) \
				((((mask)  !=  0u)  && \
				(((val) & (mask)) == (mask))) ? (RKH_DEF_YES) : (RKH_DEF_NO))


/**
 * 	\brief
 * 	Determine if specified bit(s) in a value are clear.
 *
 * 	\param val				Value to check for specified bit(s) clear.
 * 	\param mask				Mask of bits to check if clear.
 *
 * 	\return
 * 	RKH_DEF_YES, if ALL specified bit(s) are clear in value.
 * 	RKH_DEF_NO,  if ALL specified bit(s) are NOT clear in value.
 */

#define RKH_DEF_BIT_IS_CLR(val, mask) \
				((((mask)  !=  0u)  && \
				(((val) & (mask)) ==  0u)) ? (RKH_DEF_YES) : (RKH_DEF_NO))


/**
 * 	\brief
 * 	Determine if any specified bit(s) in a value are set.
 *
 * 	\param val				Value to check for specified bit(s) set.
 * 	\param mask				Mask of bits to check if set.
 *
 * 	\return
 * 	RKH_DEF_YES, if ALL specified bit(s) are set in value.
 * 	RKH_DEF_NO,  if ALL specified bit(s) are NOT set in value.
 */

#define RKH_DEF_BIT_IS_SET_ANY(val, mask) \
				((((val) & (mask)) ==  0u) ? (RKH_DEF_NO) : (RKH_DEF_YES))


/**
 * 	\brief
 * 	Determine if any specified bit(s) in a value are clear.
 *
 * 	\param val				Value to check for specified bit(s) clear.
 * 	\param mask				Mask of bits to check if clear.
 *
 * 	\return
 * 	RKH_DEF_YES, if ALL specified bit(s) are clear in value.
 * 	RKH_DEF_NO,  if ALL specified bit(s) are NOT clear in value.
 */

#define RKH_DEF_BIT_IS_CLR_ANY(val, mask) \
				((((val) & (mask)) == (mask)) ? (RKH_DEF_NO) : (RKH_DEF_YES))


#endif
