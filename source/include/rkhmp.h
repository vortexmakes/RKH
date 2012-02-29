/*
 *	file: rkhmp.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 27, 2012
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
 * 	\file rkhmp.h
 *
 * 	\brief
 * 	Platform-independent interface for supporting fixed-size memory blocks 
 * 	services.
 *
 * 	Since memory block pools consist of fixed-size blocks, there are 
 * 	never any fragmentation problems. Of course, fragmentation causes 
 * 	behavior that is inherently un-deterministic. In addition, the time
 * 	required to allocate and free a fixed-size memory is comparable to 
 * 	that of simple linked-list manipulation.
 * 	Lack of flexibility is the main drawback of fixed-size memory pools. 
 * 	The block size of a pool must be large enough to handle the worst 
 * 	case memory requirements of its users. Of course, memory may be wasted 
 * 	if many different size memory requests are made to the same pool. 
 * 	A possible solution is to make several different memory block pools 
 * 	that contain different sized memory blocks.
 */


#ifndef __RKHMP_H__
#define __RKHMP_H__


#include "rkhtype.h"
#include "rkhcfg.h"


/** 
 * 	Defines the size of number of memory block size. The valid values 
 * 	[in bits] are 8, 16 or 32. Default is 8. This type is configurable via 
 * 	the preprocessor switch RKH_MP_SIZEOF_NBLOCK.
 */

#if RKH_MP_SIZEOF_NBLOCK == 8
	typedef rkhui8_t RKH_MPNB_T;
#elif RKH_MP_SIZEOF_NBLOCK == 16
	typedef rkhui16_t RKH_MPNB_T;
#elif RKH_MP_SIZEOF_NBLOCK == 32
	typedef rkhui32_t RKH_MPNB_T;
#else
	typedef rkhui8_t RKH_MPNB_T;
#endif


/** 
 * 	Defines the size of memory block size. The valid values [in bits] are 
 * 	8, 16 or 32. Default is 8. This type is configurable via the 
 * 	preprocessor switch RKH_MP_SIZEOF_BSIZE.
 */

#if RKH_MP_SIZEOF_BSIZE == 8
	typedef rkhui8_t RKH_MPBS_T;
#elif RKH_MP_SIZEOF_BSIZE == 16
	typedef rkhui16_t RKH_MPBS_T;
#elif RKH_MP_SIZEOF_BSIZE == 32
	typedef rkhui32_t RKH_MPBS_T;
#else
	typedef rkhui8_t RKH_MPBS_T;
#endif


/**
 * 	Defines the data structure into which the performance information for
 * 	memory pools is stored.
 */

typedef struct
{
	/**
	 * 	\brief
	 * 	Number of pool create requests.
	 */

	rkhui8_t inits;

	/**	
	 * 	\brief
	 *	Number of get memory block requests.
	 */

	rkhui16_t gets;
	
	/**	
	 * 	\brief
	 *	Number of put memory block requests.
	 */

	rkhui16_t puts;
	
	/**	
	 * 	\brief
	 *	Number of no free retrieves.
	 */

	rkhui8_t free;

	/**	
	 * 	\brief
	 *	Number of full retrieves.
	 */

	rkhui8_t full;
} RKH_MPI_T;


/**
 * 	Describes the memory pool.
 */

typedef struct
{
	/**
	 * 	\brief
	 *	The head of the linked list of free blocks. 
	 *
	 *	The only data member strictly required for allocating and freeing 
	 *	blocks in the pool is the head of the free list 'free'.
	 */

	void *free;
	
	/**
	 * 	\brief
	 * 	Number of free blocks remaining. 
	 */

	RKH_MPNB_T nfree;

	/**
	 * 	\brief
	 * 	Total number of blocks in bytes. 
	 *
	 * 	The type RKH_MPNB_T is configurable by the macro RKH_MP_SIZEOF_NBLOCK. 
	 * 	The valid values [in bits] are 8, 16 or 32. Default is 8. The dynamic 
	 * 	range of the RKH_MPNB_T data type determines the maximum number of 
	 * 	blocks that can be stored in the pool.
	 */

	RKH_MPNB_T nblocks;

	/**
	 * 	\brief
	 * 	Maximum block size in bytes. 
	 *
	 * 	The type RKH_MPBS_T is configurable by the macro 
	 * 	RKH_MP_SIZEOF_BSIZE. The valid values [in bits] are 8, 16 or 32. 
	 * 	Default is 8. The dynamic range of the RKH_MPBS_T data type determines 
	 * 	the maximum size of blocks that can be managed by the pool manager.
	 */

	RKH_MPBS_T bsize;

#if RKH_MP_REDUCED == 0

	/** 
	 * 	\brief
	 * 	The start of the original pool buffer.
	 *
	 * 	The start and end pointers are used as delimiters of the valid range
	 * 	of memory blocks managed by this pool.
	 */

	void *start;

	/**
	 * 	\brief
	 * 	The last block in this pool.
	 */

	void *end;

	/**
	 * 	\brief
	 * 	Minimum number of free blocks ever in this pool, i.e. holds 
	 * 	the lowest number of free blocks ever present in the pool.
	 *
	 *	The nmin low-watermark provides valuable empirical data for 
	 *	proper sizing of the memory pool.
	 */

#if RKSYS_MPOOL_GET_LWMARK == 1
	RKH_MPNB_T nmin;
#endif

#endif

	/**
	 * 	Performance information. This member is optional, thus it could be 
	 * 	eliminated in compile-time with RKH_MP_EN_GET_INFO.
	 */

#if RKH_MP_EN_GET_INFO == 1
	RKH_MPI_T mpi;
#endif
} RKHMP_T;


/**
 * 	\brief
 *	Initializes the previously allocated memory pool data strcuture RKHMP_T.
 *
 * 	A memory block pool is declared with the RKHMP_T data type and is defined 
 * 	with the rkh_mp_init() service.
 *
 *	\note 
 *	See RKHMP_T structure for more information.
 *
 * 	A general challenge in writing this function is portability, 
 * 	because storage allocation is intrinsically machine-dependent. Perhaps 
 * 	the trickiest aspect here is the proper and optimal alignment of the 
 * 	blocks within the contiguous memory buffer. In particular, the alignment 
 * 	of blocks must be such that every new block can be treated as a pointer 
 * 	to the next block [MS].
 *	Internally, this function rounds up the block size so that it can fit 
 *	an integer number of pointers. This is done to achieve proper alignment 
 *	of the blocks within the pool. Due to the rounding of block size the 
 *	actual capacity of the pool might be less than (pool_size/blk_size). 
 *	[MS]
 *
 *	Check the capacity of the pool by calling the rkh_mp_get_nfree() 
 *	function.
 *
 * 	\param mp		pointer to previously allocated memory pool structure.
 * 	\param sstart	storage start. Pointer to memory from which memory blocks 
 * 					are allocated.
 * 	\param ssize:	storage size. Size of the memory pool storage in bytes.
 * 	\param bsize	block size. This number determines the size of each memory 
 * 					block in the pool.
 */

void rkh_mp_init( 	RKHMP_T *mp, void *sstart, rkhui16_t ssize, 
					RKH_MPBS_T bsize );


/**
 * 	\brief
 * 	This function is used to get a memory block from one of the created
 * 	memory pool.
 * 	
 * 	\param mp		pointer to previously allocated memory pool structure.
 *
 * 	\return
 * 	A pointer to a new memory block or NULL if the pool runs out of blocks.
 */

void *rkh_mp_get( RKHMP_T *mp );


/**
 * 	\brief
 * 	When the application is done with the memory block, it must be returned
 * 	to the appropiate memory pool. The block must be allocated from the same 
 * 	memory pool to which it is returned. 
 * 	
 * 	\param mp		pointer to previously allocated memory pool structure.
 * 	\param blk		pointer to the returned memory block.
 */

void rkh_mp_put( RKHMP_T *mp, void *blk );


/**
 * 	\brief
 * 	This function returns the size of memory block in bytes.
 * 	
 * 	\note
 * 	This function is optional, thus it could be eliminated in compile-time 
 * 	with RKH_MP_EN_GET_BSIZE.
 *
 * 	\param mp		pointer to previously allocated memory pool structure.
 *
 * 	\return
 * 	The size of memory block in bytes.
 */

RKH_MPBS_T rkh_mp_get_blksize( RKHMP_T *mp );


/**
 * 	\brief
 * 	This function returns the current number of free memory blocks in the 
 * 	pool.
 * 	
 * 	\note
 * 	This function is optional, thus it could be eliminated in compile-time 
 * 	with RKH_MP_EN_GET_NFREE.
 * 	
 * 	\param mp		pointer to previously allocated memory pool structure.
 *
 * 	\return
 * 	The number of free memory blocks in the pool.
 */

RKH_MPNB_T rkh_mp_get_nfree( RKHMP_T *mp );


/**
 * 	\brief
 * 	This function returns the lowest number of free blocks ever present in 
 * 	the pool. This number provides valuable empirical data for proper sizing 
 *	of the memory pool.
 * 	
 * 	\note
 * 	This function is optional, thus it could be eliminated in compile-time 
 * 	with RKH_MP_EN_GET_LWM.
 * 	
 * 	\param mp		pointer to previously allocated memory pool structure.
 *
 * 	\return
 * 	Lowest number of free blocks ever present in the pool.
 */

RKH_MPNB_T rkh_mp_get_low_wmark( RKHMP_T *mp );


/**
 * 	\brief
 * 	Retrieves performance information for a particular memory pool.
 *
 * 	Information is available during run-time for each of the RKSYS
 * 	resources. This information can be useful in determining whether
 * 	the application is performing properly, as well as helping to
 * 	optimize the application.
 * 	
 * 	\note
 * 	This function is optional, thus it could be eliminated in compile-time 
 * 	with RKH_MP_EN_GET_INFO.
 *
 * 	\param mp		pointer to previously allocated memory pool structure.
 * 	\param mpi		pointer to the buffer into which the performance information
 * 					will be copied by reference.
 */

void rkh_mp_get_info( RKHMP_T *mp, RKH_MPI_T *mpi );


/**
 * 	\brief
 * 	Clear performance information for a particular memory pool.
 *
 * 	\note
 * 	This function is optional, thus it could be eliminated in compile-time 
 * 	with RKH_MP_EN_GET_INFO.
 *
 * 	\param mp		pointer to previously allocated memory pool structure.
 */

void rkh_mp_clear_info( RKHMP_T *mp );


#endif
