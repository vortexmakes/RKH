/*
 * 	rkhmp.h
 *
 * 	Implements a pool of fixed-size memory blocks.
 * 	Since memory block pools consist of fixed-size blocks, there are 
 * 	never any fragmentation problems. Of course, fragmentation causes 
 * 	behavior that is inherently un-deterministic. In addition, the time
 * 	required to allocate and free a fixed-size memory is comparable to 
 * 	that of simple linked-list manipulation.
 *
 * 	Lack of flexibility is the main drawback of fixed-size memory pools. 
 * 	The block size of a pool must be large enough to handle the worst 
 * 	case memory requirements of its users. Of course, memory may be wasted 
 * 	if many different size memory requests are made to the same pool. 
 * 	A possible solution is to make several different memory block pools 
 * 	that contain different sized memory blocks.
 */


#ifndef __RKMP_H__
#define __RKMP_H__


#include "rkh.h"


/*
 * 	Return codes.
 */

enum
{
	RKMPOOL_OK, 
	RKMPOOL_NO_FREE_BLKS, 
	RKMPOOL_FULL, 
	RKMPOOL_NO_POOL
};


/*
 * 	Memory pool descriptor type.
 */

typedef KUInt RK_MPD_T;


/*
 * 	Defines the data structure into which the information about the memory
 * 	pool is stored.
 */

typedef struct
{
	/*
	 * 	Size (in bytes) of each memory block.
	 */

	RK_MPBS_T blk_size;

	/*
	 * 	Total number of memory blocks in the pool.
	 */

	RK_MPCTR_T nblocks;

	/*
	 * 	Number of memory blocks free.
	 */

	RK_MPCTR_T nfree;

	/*
	 * 	Number of memory blocks used.
	 */

	RK_MPCTR_T nused;
} RK_MPOOL_DATA_T;


/*
 * 	Defines the data structure into which the performance information for
 * 	memory pools is stored.
 */

typedef struct
{
	/*
	 * 	Number of pool create requests.
	 */

	rkint8 inits;

	/*	
	 *	Number of get memory block requests.
	 */

	rkint16 gets;
	
	/*	
	 *	Number of put memory block requests.
	 */

	rkint16 puts;
	
	/*	
	 *	Number of RKMPOOL_NO_FREE_BLKS retrieves.
	 */

	rkint8 free;

	/*	
	 *	Number of RKMPOOL_FULL retrieves.
	 */

	rkint8 full;
} RK_MPOOL_INFO_T;


/*
 * 	rk_mpool_init:
 *
 * 	Initialize a previously defined memory pool.
 *
 * 	A general challenge in writing this function is portability, 
 * 	because storage allocation is intrinsically machine-dependent. Perhaps 
 * 	the trickiest aspect here is the proper and optimal alignment of the 
 * 	blocks within the contiguous memory buffer. In particular, the alignment 
 * 	of blocks must be such that every new block can be treated as a pointer 
 * 	to the next block [Miro Samek].
 *	
 *	Internally, this function rounds up the block size so that it can fit 
 *	an integer number of pointers. This is done to achieve proper alignment 
 *	of the blocks within the pool. Due to the rounding of block size the 
 *	actual capacity of the pool might be less than (pool_size/blk_size). 
 *	[Miro Samek]
 *
 *	Check the capacity of the pool by calling the rk_mpool_get_nfree() 
 *	function.
 *
 * 	Arguments:
 *
 * 	'mpd':			memory pool descriptor.
 * 	'pmem': 		pointer to memory from which memory blocks are allocated.
 * 	'pool_size':	pool size. Size of the memory pool storage in byte.
 * 	'blk_size':		block size. This number determines the size of each memory 
 * 					block in the pool.
 *
 * 	Returns:
 *
 * 	RKMPOOL_OK if the memory pool was successfully initialized, 
 * 	otherwise error code.
 */

KUInt rk_mpool_init( RK_MPD_T mpd, void *pmem, rkint16 pool_size, 
														RK_MPBS_T blk_size );


/*
 * 	rk_mpool_get:
 *
 * 	This function is used to get a memory block from one of the created
 * 	memory pool.
 * 	
 * 	Arguments:
 *
 * 	'mpd':		memory pool descriptor.
 *
 * 	Returns:
 *
 * 	A pointer to a new memory block or NULL if the pool runs out of blocks.
 */

void *rk_mpool_get( RK_MPD_T mpd );


/*
 * 	rk_mpool_put:
 *
 * 	When the application is done with the memory block, it must be returned
 * 	to the appropiate memory pool.
 * 	The block must be allocated from the same memory pool to which it 
 * 	is returned. 
 * 	
 * 	Arguments:
 *
 * 	'mpd':		memory pool descriptor.
 * 	'blk':		pointer to the returned memory block.
 *
 * 	Returns:
 *
 * 	RKMPOOL_OK if the memory block was succesfully returned to proper 
 * 	memory pool, otherwise error code.
 */

KUInt rk_mpool_put( RK_MPD_T mpd, void *blk );


/*
 * 	rk_mpool_get_blksize:
 *
 * 	This function returns the size of memory block in bytes.
 * 	
 * 	Arguments:
 *
 * 	'mpd':		memory pool descriptor.
 *
 * 	Returns:
 *
 * 	The size of memory block in bytes.
 */

RK_MPBS_T rk_mpool_get_blksize( RK_MPD_T mpd );


/*
 * 	rk_mpool_get_nfree:
 *
 * 	This function returns the current number of free memory blocks 
 * 	in the pool.
 * 	
 * 	Arguments:
 *
 * 	'mpd':		memory pool descriptor.
 *
 * 	Returns:
 *
 * 	The number of free memory blocks in the pool.
 */

RK_MPCTR_T rk_mpool_get_nfree( RK_MPD_T mpd );


/*
 * 	rk_mpool_get_low_wmark:
 *
 * 	This function returns the lowest number of free blocks ever 
 * 	present in the pool.
 *	This number provides valuable empirical data for proper sizing 
 *	of the memory pool.
 * 	
 * 	Arguments:
 *
 * 	'mpd':		memory pool descriptor.
 *
 * 	Returns:
 *
 * 	Lowest number of free blocks ever present in the pool.
 */

RK_MPCTR_T rk_mpool_get_low_wmark( RK_MPD_T mpd );


/*
 * 	rk_mpool_query:
 *
 * 	This function is used to obtain information about the memory pool.
 * 	
 * 	Arguments:
 *
 * 	'mpd':		memory pool descriptor.
 * 	'data':		pointer to the buffer into which the information about the
 * 				memory pool will be copied by reference.
 */

void rk_mpool_query( RK_MPD_T mpd, RK_MPOOL_DATA_T *data );


/*
 * 	rk_mpool_clear_info:
 *
 * 	Clear performance information for a particular memory pool.
 *
 * 	Information is available during run-time for each of the RKSYS
 * 	resources. This information can be useful in determining whether
 * 	the application is performing properly, as well as helping to
 * 	optimize the application.
 *
 * 	'mpd':		memory pool descriptor.
 */

void rk_mpool_clear_info( RK_MPD_T qd );


/*
 * 	rk_mpool_get_info:
 *
 * 	Retrieves performance information for a particular memory pool.
 *
 * 	'mpd':		memory pool descriptor.
 * 	'pmpi':		pointer to the buffer into which the performance information
 * 				will be copied by reference.
 */

void rk_mpool_get_info( RK_MPD_T mpd, RK_MPOOL_INFO_T *pmpi );


#endif
