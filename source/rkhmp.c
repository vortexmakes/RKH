/*
 *	file: rkhmp.c
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
 * RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * e-mail:			francuccilea@gmail.com
 */

/**
 * 	\file rkhmp.c
 *
 * 	\brief
 * 	Implements a pool of fixed-size memory blocks.
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


#include "rkhassert.h"
#include "rkhmp.h"
#include "rkh.h"


#if RKH_MP_EN == 1

RKH_MODULE_NAME( rkhmp )


/*
 * 	Structure representing a free block.
 */

typedef struct rkh_free_blk_t
{
    struct rkh_free_blk_t *next;
} RKH_FREE_BLK_T;


void 
rkh_mp_init( RKHMP_T *mp, void *sstart, rkhui16_t ssize, 
												RKH_MPBS_T bsize )
{
    RKH_FREE_BLK_T *fb;
    RKH_MPNB_T nblocks;

    /* 
	 * The memory block must be valid and the pool size (\a ssize) must fit 
	 * at least one free block and the block size (\a bsize) must not be too 
	 * close to the top of the dynamic range.
     */

	RKHASSERT( 	sstart != NULL && 
				ssize >= sizeof( RKH_FREE_BLK_T ) &&
				(RKH_MPBS_T)( bsize + sizeof( RKH_FREE_BLK_T ) ) > bsize );

    mp->free = ( void* )(sstart);

    /* 
	 * (1) Round up the 'bsize' to fit an integer # free blocks, no division.
	 */

    mp->bsize = sizeof( RKH_FREE_BLK_T );		      /* start with just one */
    nblocks = 1;			   /* # free blocks that fit in one memory block */

    while( mp->bsize < bsize )
	{
        mp->bsize += sizeof( RKH_FREE_BLK_T );
        ++nblocks;
    }
	
    bsize = mp->bsize;		         /* use the rounded-up value from now on */
	
	/* 
	 * The pool buffer must fit at least one rounded-up block.
	 */

	RKHASSERT( ssize >= ( rkhui16_t )bsize );

	/* 
	 * (2) Chain all blocks together in a free-list... 
	 */

    ssize -= ( rkhui16_t )bsize;	           /* don't count the last block */
    mp->nblocks = 1;				   /* the last block already in the pool */
    fb = ( RKH_FREE_BLK_T* )mp->free;	/*start at the head of the free list */

    while( ssize >= ( rkhui16_t )bsize ) 
	{
        fb->next = &fb[ nblocks ];	/* point the next link to the next block */
        fb = fb->next;				/* advance to the next block */
        ssize -= (rkhui16_t)bsize;	/* reduce the available pool size */
        ++mp->nblocks;				/* increment the number of blocks so far */
    }

    fb->next  = ( RKH_FREE_BLK_T* )0;        /* the last link points to NULL */
    mp->nfree = mp->nblocks;                          /* all blocks are free */
#if RKH_MP_EN_GET_LWM == 1 && RKH_MP_REDUCED == 0
    mp->nmin  = mp->nblocks;            /* the minimum number of free blocks */
#endif
#if RKH_MP_REDUCED == 0
    mp->start = sstart;               /* the original start this pool buffer */
    mp->end   = fb;                           /* the last block in this pool */
#endif
	RKH_TR_MP_INIT( mp, mp->nblocks );
}


void *
rkh_mp_get( RKHMP_T *mp )
{
    RKH_FREE_BLK_T *fb;
	RKH_SR_CRITICAL_;

	RKHASSERT( mp != ( RKHMP_T* )0 && mp->bsize != 0 );

	RKH_ENTER_CRITICAL_();

    fb = ( RKH_FREE_BLK_T* )mp->free;           /* get a free block or NULL */
    if( fb != NULL )							   /* free block available? */
	{
        mp->free = fb->next;    /* adjust list head to the next free block */
        --mp->nfree;                                /* one less free block */
#if RKH_MP_EN_GET_LWM == 1 && RKH_MP_REDUCED == 0
        if( mp->nmin > mp->nfree )
            mp->nmin = mp->nfree;          /* remember the minimum so far */
#endif
    }

	RKH_EXIT_CRITICAL_();
	RKH_TR_MP_GET( mp, mp->nfree );
    return fb;            /* return the block or NULL pointer to the caller */
}


void 
rkh_mp_put( RKHMP_T *mp, void *blk )
{
	RKH_SR_CRITICAL_;

	RKHASSERT( mp != ( RKHMP_T* )0 );
	RKHASSERT( mp->bsize != 0 );

#if RKH_MP_REDUCED == 0
    RKHASSERT(	mp->start <= blk && 				    /* must be in range */
				blk <= mp->end && 
				mp->nfree <= mp->nblocks  ); /* # free blocks must be < total */
#else
    RKHASSERT(	mp->nfree <= mp->nblocks ); /* # free blocks must be < total */
#endif

	RKH_ENTER_CRITICAL_();
	
	/* link into free list */
    ( ( RKH_FREE_BLK_T* )blk )->next = ( RKH_FREE_BLK_T* )mp->free;
    mp->free = blk;                    /* set as new head of the free list */
    ++mp->nfree;                       /* one more free block in this pool */
	
	RKH_EXIT_CRITICAL_();
	RKH_TR_MP_PUT( mp, mp->nfree );
}


#if RKH_MP_EN_GET_BSIZE == 1
RKH_MPBS_T 
rkh_mp_get_bsize( RKHMP_T *mp )
{
    RKH_MPBS_T bs;
	RKH_SR_CRITICAL_;

	RKHASSERT( mp != ( RKHMP_T* )0 );

	RKH_ENTER_CRITICAL_();
    bs = mp->bsize;
	RKH_EXIT_CRITICAL_();

    return bs;
}
#endif


#if RKH_MP_EN_GET_NFREE == 1
RKH_MPNB_T 
rkh_mp_get_nfree( RKHMP_T *mp )
{
    RKH_MPNB_T nfree;
	RKH_SR_CRITICAL_;

	RKHASSERT( mp != ( RKHMP_T* )0 );

	RKH_ENTER_CRITICAL_();
    nfree = mp->nfree;
	RKH_EXIT_CRITICAL_();

    return nfree;
}
#endif


#if RKH_MP_EN_GET_LWM == 1 && RKH_MP_REDUCED == 0
RKH_MPNB_T 
rkh_mp_get_low_wmark( RKHMP_T *mp )
{
    RKH_MPNB_T nmin;
	RKH_SR_CRITICAL_;

	RKHASSERT( mp != ( RKHMP_T* )0 );

	RKH_ENTER_CRITICAL_();
    nmin = mp->nmin;
	RKH_EXIT_CRITICAL_();

    return nmin;
}
#endif


#if RKH_MP_EN_GET_INFO == 1 && RKH_MP_REDUCED == 0
void 
rkh_mp_get_info( RKHMP_T *mp, RKH_MPI_T *mpi )
{
	RKH_SR_CRITICAL_;

	RKHASSERT( mp != ( RKHMP_T* )0 && mpi != ( RKH_MPI_T* )0 );

	RKH_ENTER_CRITICAL_();
	*mpi = mp->mpi;
	RKH_EXIT_CRITICAL_();
}


void 
rkh_mp_clear_info( RKHMP_T *mp )
{
	RKH_MPI_T *pmpi;
	RKH_SR_CRITICAL_;

	RKHASSERT( mp != ( RKHMP_T* )0 );
	pmpi = &mp->mpi;

	RKH_ENTER_CRITICAL_();
	pmpi->inits = pmpi->gets = pmpi->puts = pmpi->free = pmpi->full = 0;
	RKH_EXIT_CRITICAL_();
}
#endif

#endif
