/*
 *	file: rkhassert.h
 *	Last updated for version: 1.5.00
 *	Date of the last update:  June 21, 2011
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
 * RKH web site:	http://
 * e-mail:			francuccilea@gmail.com
 */

/**
 * 	\file rkhassert.h
 *	\brief
 *	Assert event definitions.
 */


#ifndef __RKHASSERT_H__
#define __RKHASSERT_H__


/**
 * 	Unique identifiers for assertion error codes.
 */

typedef enum
{
	/**
	 *	Indicates a detected error in rkh_ae() function.
	 */

	RKH_AE_RUNOUT_POOLS,
	RKH_AE_NOT_ALLOC,

	/**
	 *	Indicates a detected error in rkh_gc() function.
	 */

	RKH_GC_RUNOUT_POOLS,

	/**
	 *	Indicates a detected error in rkh_recall() function.
	 */

	RKH_RC_FAIL,

	/**
	 *	Indicates a detected error in rkh_put_fifo() function.
	 */

	RKH_PF_NO_ROOM,

	/**
	 *	Indicates a detected error in rkh_put_lifo() function.
	 */

	RKH_PL_NO_ROOM,

	RKH_ASSERT_NUM_ERRORS
} RKH_ASSERT_T;


#endif
