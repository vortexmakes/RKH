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
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       rkhmempool.h
 *  \brief      Specifies the interface of the fixed-size memory blocks 
 *              facility.
 *  \ingroup    apiMemPool
 *
 *  \addtogroup api
 *  @{
 *  \addtogroup apiMemPool Manager of fixed-sized memory block
 *  @{@}
 *  @}
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHMEMPOOL_H__
#define __RKHMEMPOOL_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtype.h"
#include "rkhcfg.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/**
 *  Defines the size of number of memory block size. The valid values
 *  [in bits] are 8, 16 or 32. Default is 8. This type is configurable via
 *  the preprocessor switch RKH_CFG_MP_SIZEOF_NBLOCK.
 */
#if RKH_CFG_MP_SIZEOF_NBLOCK == 8
typedef rui8_t RKH_MPNB_T;
#elif RKH_CFG_MP_SIZEOF_NBLOCK == 16
typedef rui16_t RKH_MPNB_T;
#elif RKH_CFG_MP_SIZEOF_NBLOCK == 32
typedef rui32_t RKH_MPNB_T;
#else
typedef rui8_t RKH_MPNB_T;
#endif

/**
 *  Defines the size of memory block size. The valid values [in bits] are
 *  8, 16 or 32. Default is 8. This type is configurable via the
 *  preprocessor switch RKH_CFG_MP_SIZEOF_BSIZE.
 */
#if RKH_CFG_MP_SIZEOF_BSIZE == 8
typedef rui8_t RKH_MPBS_T;
#elif RKH_CFG_MP_SIZEOF_BSIZE == 16
typedef rui16_t RKH_MPBS_T;
#elif RKH_CFG_MP_SIZEOF_BSIZE == 32
typedef rui32_t RKH_MPBS_T;
#else
typedef rui8_t RKH_MPBS_T;
#endif

/**
 *  \brief
 *  Defines the data structure into which the performance information for
 *  memory pools is stored.
 */
typedef struct
{
    /**
     *  \brief
     *  Number of pool create requests.
     */
    rui8_t inits;

    /**
     *  \brief
     *	Number of get memory block requests.
     */
    rui8_t gets;

    /**
     *  \brief
     *	Number of put memory block requests.
     */
    rui8_t puts;

    /**
     *  \brief
     *	Number of no free retrieves.
     */
    rui8_t free;

    /**
     *  \brief
     *	Number of full retrieves.
     */
    rui8_t full;
} RKH_MPI_T;

/**
 *  \brief
 *  Defines the data structure used to memory block pool facility.
 *
 *  Since memory block pools consist of fixed-size blocks, there are
 *  never any fragmentation problems. Of course, fragmentation causes
 *  behavior that is inherently un-deterministic. In addition, the time
 *  required to allocate and free a fixed-size memory is comparable to
 *  that of simple linked-list manipulation.
 *  Lack of flexibility is the main drawback of fixed-size memory pools.
 *  The block size of a pool must be large enough to handle the worst
 *  case memory requirements of its users. Of course, memory may be wasted
 *  if many different size memory requests are made to the same pool.
 *  A possible solution is to make several different memory block pools
 *  that contain different sized memory blocks. Each memory block pool
 *  is a public resource.
 *
 *  The memory block pools contain a number of fixed-size blocks. The block
 *  size, in bytes, is specified during creation of the pool. Each memory
 *  block in the pool imposes a small amount of overhead the size of a C
 *  pointer. In addition, RKH may pad the block size in order to keep the
 *  beginning of each memory block on proper alignment.
 *
 *  The number of memory blocks in a pool depends on the block size and the
 *  total number of bytes in the memory area supplied during creation. To
 *  calculate the capacity of a pool (number of blocks that will be
 *  available), divide the block size (including padding and the pointer
 *  overhead bytes) into the total number of bytes in the supplied memory
 *  area.
 *
 *  The memory area for the block pool is specified during creation, and can
 *  be located anywhere in the target's address space. This is an important
 *  feature because of the considerable flexibility it gives the application.
 *
 *	\note
 *  RKH prohibits an application from explicitly modifying the RKH_MEMPOOL_T
 *  structure. The RKH's memory block pool structures can be located anywhere
 *  in memory, but it is most common to make it a global structure by
 *  defining it outside the scope of any function.
 *  An RKH memory pool is created when an memory pool is declared with the
 *  RKH_MEMPOOL_T data type. The following listing declares "my_pool" memory 
 *  pool:
 *
 *  \code
 *  RKH_MEMPOOL_T my_pool;
 *  \endcode
 *
 *  \ingroup apiMemPool
 */
typedef struct RKH_MEMPOOL_T
{
    /**
     *  \brief
     *	The head of the linked list of free blocks.
     *
     *	The only data member strictly required for allocating and freeing
     *	blocks in the pool is the head of the free list 'free'.
     */
    void *free;

    /**
     *  \brief
     *  Number of free blocks remaining.
     */
    RKH_MPNB_T nfree;

    /**
     *  \brief
     *  Total number of blocks in bytes.
     *
     *  The type RKH_MPNB_T is configurable by the macro
     *  RKH_CFG_MP_SIZEOF_NBLOCK.
     *  The valid values [in bits] are 8, 16 or 32. Default is 8. The dynamic
     *  range of the RKH_MPNB_T data type determines the maximum number of
     *  blocks that can be stored in the pool.
     */
    RKH_MPNB_T nblocks;

    /**
     *  \brief
     *  Maximum block size in bytes.
     *
     *  The type RKH_MPBS_T is configurable by the macro
     *  RKH_CFG_MP_SIZEOF_BSIZE. The valid values [in bits] are 8, 16 or 32.
     *  Default is 8. The dynamic range of the RKH_MPBS_T data type
     *  determines the maximum size of blocks that can be managed by the
     *  pool manager.
     */
    RKH_MPBS_T bsize;

#if RKH_CFG_MP_REDUCED_EN == RKH_DISABLED
    /**
     *  \brief
     *  The start of the original pool buffer.
     *
     *  The start and end pointers are used as delimiters of the valid range
     *  of memory blocks managed by this pool.
     */
    void *start;

    /**
     *  \brief
     *  The last block in this pool.
     */
    void *end;

    /**
     *  \brief
     *  Minimum number of free blocks ever in this pool, i.e. holds
     *  the lowest number of free blocks ever present in the pool.
     *
     *	The nmin low-watermark provides valuable empirical data for
     *	proper sizing of the memory pool.
     */
#if RKH_CFG_MP_GET_LWM_EN == RKH_ENABLED
    RKH_MPNB_T nmin;
#endif

#endif

    /**
     *  Performance information. This member is optional, thus it could be
     *  eliminated in compile-time with RKH_CFG_MP_GET_INFO_EN.
     */
#if RKH_CFG_MP_GET_INFO_EN == RKH_ENABLED
    RKH_MPI_T mpi;
#endif
} RKH_MEMPOOL_T;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/**
 *  \brief
 *	Initializes the previously allocated memory pool data strcuture 
 *	RKH_MEMPOOL_T.
 *
 *  A memory block pool is declared with the RKH_MEMPOOL_T data type and is
 *  defined with the rkh_memPool_init() service.
 *
 *  A general challenge in writing this function is portability,
 *  because storage allocation is intrinsically machine-dependent. Perhaps
 *  the trickiest aspect here is the proper and optimal alignment of the
 *  blocks within the contiguous memory buffer. In particular, the alignment
 *  of blocks must be such that every new block can be treated as a pointer
 *  to the next block [MS].
 *	Internally, this function rounds up the block size so that it can fit
 *	an integer number of pointers. This is done to achieve proper alignment
 *	of the blocks within the pool. Due to the rounding of block size the
 *	actual capacity of the pool might be less than (pool_size/blk_size).
 *	[MS]
 *
 *	Check the capacity of the pool by calling the rkh_memPool_get_nfree()
 *	function.
 *
 *  \param[in] mp		pointer to previously allocated memory pool structure.
 *  \param[in] sstart	storage start. Pointer to memory from which memory 
 *                      blocks are allocated.
 *  \param[in] ssize 	storage size. Size of the memory pool storage in bytes.
 *  \param[in] bsize	block size. This number determines the size of each
 *                      memory block in the pool.
 *
 *	\note
 *	See RKH_MEMPOOL_T structure for more information.
 *
 *  \ingroup apiMemPool
 */
void rkh_memPool_init(RKH_MEMPOOL_T *mp, void *sstart, rui16_t ssize,
                 RKH_MPBS_T bsize);

/**
 *  \brief
 *  Get a memory block from one of the previously allocated memory pool.
 *
 *  \param[in] mp		pointer to previously allocated memory pool structure.
 *
 *  \return
 *  A pointer to a new memory block or NULL if the pool runs out of blocks.
 *
 *  \ingroup apiMemPool
 */
void *rkh_memPool_get(RKH_MEMPOOL_T *mp);

/**
 *  \brief
 *  When the application is done with the memory block, it must be returned
 *  to the appropiate memory pool. The block must be allocated from the same
 *  memory pool to which it is returned.
 *
 *  \param[in] mp		pointer to previously allocated memory pool structure.
 *  \param[in] blk		pointer to the returned memory block.
 *
 *  \ingroup apiMemPool
 */
void rkh_memPool_put(RKH_MEMPOOL_T *mp, void *blk);

/**
 *  \brief
 *  Retrieves the size of memory block in bytes.
 *
 *  \param[in] mp		pointer to previously allocated memory pool structure.
 *
 *  \return
 *  The size of memory block in bytes.
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_MP_GET_BSIZE_EN.
 *
 *  \ingroup apiMemPool
 */
RKH_MPBS_T rkh_memPool_get_bsize(RKH_MEMPOOL_T *mp);

/**
 *  \brief
 *  Retrieves the current number of free memory blocks in the pool.
 *
 *  \param[in] mp		pointer to previously allocated memory pool structure.
 *
 *  \return
 *  The number of free memory blocks in the pool.
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_MP_GET_NFREE_EN.
 *
 *  \ingroup apiMemPool
 */
RKH_MPNB_T rkh_memPool_get_nfree(RKH_MEMPOOL_T *mp);

/**
 *  \brief
 *  Retrieves the lowest number of free blocks ever present in the pool.
 *  This number provides valuable empirical data for proper sizing of the
 *  memory pool.
 *
 *  \param[in] mp		pointer to previously allocated memory pool structure.
 *
 *  \return
 *  Lowest number of free blocks ever present in the pool.
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_MP_GET_LWM_EN.
 *
 *  \ingroup apiMemPool
 */
RKH_MPNB_T rkh_memPool_get_low_wmark(RKH_MEMPOOL_T *mp);

/**
 *  \brief
 *  Retrieves performance information for a particular memory pool.
 *
 *  Information is available during run-time for each of the RKSYS
 *  resources. This information can be useful in determining whether
 *  the application is performing properly, as well as helping to
 *  optimize the application.
 *
 *  \param[in] mp		pointer to previously allocated memory pool structure.
 *  \param[in] mpi		pointer to the buffer into which the performance
 *                      information will be copied by reference.
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_MP_GET_INFO_EN.
 *
 *  \ingroup apiMemPool
 */
void rkh_memPool_get_info(RKH_MEMPOOL_T *mp, RKH_MPI_T *mpi);

/**
 *  \brief
 *  Clear performance information for a particular memory pool.
 *
 *  \param[in] mp		pointer to previously allocated memory pool structure.
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_MP_GET_INFO_EN.
 *
 *  \ingroup apiMemPool
 */
void rkh_memPool_clear_info(RKH_MEMPOOL_T *mp);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
