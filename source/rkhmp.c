/**
 * \cond
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 * 	          State-machine framework for reactive embedded systems            
 * 	        
 * 	                    Copyright (C) 2010 Leandro Francucci.
 * 	        All rights reserved. Protected by international copyright laws.
 *
 *
 * 	RKH is free software: you can redistribute it and/or modify it under the 
 * 	terms of the GNU General Public License as published by the Free Software 
 * 	Foundation, either version 3 of the License, or (at your option) any 
 * 	later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY 
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for 
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along 
 *  with RKH, see copying.txt file.
 *
 * 	Contact information:
 * 	RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * 	e-mail:			francuccilea@gmail.com
 *
 *  --------------------------------------------------------------------------
 *  File                     : rkhmp.c
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	mp
 * 	\brief 		Implements a pool of fixed-size memory blocks.
 */


#include "rkhassert.h"
#include "rkhmp.h"
#include "rkh.h"


#if RKH_MP_EN == RKH_ENABLED

RKH_MODULE_NAME( rkhmp )


/*
 * 	Structure representing a free block.
 */

typedef struct rkh_free_blk_t
{
    struct rkh_free_blk_t *next;
} RKH_FREE_BLK_T;


void 
rkh_mp_init( RKH_MP_T *mp, void *sstart, rui16_t ssize, 
												RKH_MPBS_T bsize )
{
    RKH_FREE_BLK_T *fb;
    RKH_MPNB_T nblocks;
	RKH_SR_ALLOC();

    /* 
	 * The memory block must be valid and the pool size (\a ssize) must fit 
	 * at least one free block and the block size (\a bsize) must not be too 
	 * close to the top of the dynamic range.
     */

	RKHASSERT( 	sstart != RKH_NULL && 
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
	
	              /* The pool buffer must fit at least one rounded-up block. */
	RKHASSERT( ssize >= ( rui16_t )bsize );

	                           /* Chain all blocks together in a free-list...*/
    ssize -= ( rui16_t )bsize;	           /* don't count the last block */
    mp->nblocks = 1;				   /* the last block already in the pool */
    fb = ( RKH_FREE_BLK_T* )mp->free;	/*start at the head of the free list */

    while( ssize >= ( rui16_t )bsize ) 
	{
        fb->next = &fb[ nblocks ];	/* point the next link to the next block */
        fb = fb->next;				/* advance to the next block */
        ssize -= (rui16_t)bsize;	/* reduce the available pool size */
        ++mp->nblocks;				/* increment the number of blocks so far */
    }

    fb->next  = ( RKH_FREE_BLK_T* )0;        /* the last link points to NULL */
    mp->nfree = mp->nblocks;                          /* all blocks are free */
#if RKH_MP_EN_GET_LWM == RKH_ENABLED && \
	RKH_MP_REDUCED == RKH_DISABLED
    mp->nmin  = mp->nblocks;            /* the minimum number of free blocks */
#endif
#if RKH_MP_REDUCED == RKH_DISABLED
    mp->start = sstart;               /* the original start this pool buffer */
    mp->end   = fb;                           /* the last block in this pool */
#endif
	RKH_TR_MP_INIT( mp, mp->nblocks, mp->bsize );
}


void *
rkh_mp_get( RKH_MP_T *mp )
{
    RKH_FREE_BLK_T *fb;
	RKH_SR_ALLOC();

	RKHASSERT( mp != ( RKH_MP_T* )0 && mp->bsize != 0 );

	RKH_ENTER_CRITICAL_();

    fb = ( RKH_FREE_BLK_T* )mp->free;           /* get a free block or NULL */
    if( fb != RKH_NULL )					       /* free block available? */
	{
        mp->free = fb->next;     /* adjust list head to the next free block */
        RKHASSERT(mp->nfree > (RKH_MPNB_T)0);    /* at least one free block */
        --mp->nfree;                                 /* one less free block */
#if RKH_MP_EN_GET_LWM == RKH_ENABLED && \
	RKH_MP_REDUCED == RKH_DISABLED
        if( mp->nmin > mp->nfree )
            mp->nmin = mp->nfree;            /* remember the minimum so far */
#endif
    }

	RKH_EXIT_CRITICAL_();
		RKH_TR_MP_GET( mp, mp->nfree, mp->nmin );
    return fb;            /* return the block or NULL pointer to the caller */
}


void 
rkh_mp_put( RKH_MP_T *mp, void *blk )
{
	RKH_SR_ALLOC();

	RKHASSERT( mp != ( RKH_MP_T* )0 );
	RKHASSERT( mp->bsize != 0 );

#if RKH_MP_REDUCED == RKH_DISABLED
    RKHASSERT(	mp->start <= blk && 				     /* must be in range */
				blk <= mp->end && 
				mp->nfree < mp->nblocks  ); /* # free blocks must be < total */
#else
    RKHASSERT(	mp->nfree < mp->nblocks );  /* # free blocks must be < total */
#endif

	RKH_ENTER_CRITICAL_();
	
	/* link into free list */
    ( ( RKH_FREE_BLK_T* )blk )->next = ( RKH_FREE_BLK_T* )mp->free;
    mp->free = blk;                      /* set as new head of the free list */
    ++mp->nfree;                         /* one more free block in this pool */
	
	RKH_EXIT_CRITICAL_();
	RKH_TR_MP_PUT( mp, mp->nfree );
}


#if RKH_MP_EN_GET_BSIZE == RKH_ENABLED
RKH_MPBS_T 
rkh_mp_get_bsize( RKH_MP_T *mp )
{
    RKH_MPBS_T bs;
	RKH_SR_ALLOC();

	RKHASSERT( mp != ( RKH_MP_T* )0 );

	RKH_ENTER_CRITICAL_();
    bs = mp->bsize;
	RKH_EXIT_CRITICAL_();

    return bs;
}
#endif


#if RKH_MP_EN_GET_NFREE == RKH_ENABLED
RKH_MPNB_T 
rkh_mp_get_nfree( RKH_MP_T *mp )
{
    RKH_MPNB_T nfree;
	RKH_SR_ALLOC();

	RKHASSERT( mp != ( RKH_MP_T* )0 );

	RKH_ENTER_CRITICAL_();
    nfree = mp->nfree;
	RKH_EXIT_CRITICAL_();

    return nfree;
}
#endif


#if RKH_MP_EN_GET_LWM == RKH_ENABLED && \
	RKH_MP_REDUCED == RKH_DISABLED
RKH_MPNB_T 
rkh_mp_get_low_wmark( RKH_MP_T *mp )
{
    RKH_MPNB_T nmin;
	RKH_SR_ALLOC();

	RKHASSERT( mp != ( RKH_MP_T* )0 );

	RKH_ENTER_CRITICAL_();
    nmin = mp->nmin;
	RKH_EXIT_CRITICAL_();

    return nmin;
}
#endif


#if RKH_MP_EN_GET_INFO == RKH_ENABLED && \
	RKH_MP_REDUCED == RKH_DISABLED
void 
rkh_mp_get_info( RKH_MP_T *mp, RKH_MPI_T *mpi )
{
	RKH_SR_ALLOC();

	RKHASSERT( mp != ( RKH_MP_T* )0 && mpi != ( RKH_MPI_T* )0 );

	RKH_ENTER_CRITICAL_();
	*mpi = mp->mpi;
	RKH_EXIT_CRITICAL_();
}


void 
rkh_mp_clear_info( RKH_MP_T *mp )
{
	RKH_MPI_T *pmpi;
	RKH_SR_ALLOC();

	RKHASSERT( mp != ( RKH_MP_T* )0 );
	pmpi = &mp->mpi;

	RKH_ENTER_CRITICAL_();
	pmpi->inits = pmpi->gets = pmpi->puts = pmpi->free = pmpi->full = 0;
	RKH_EXIT_CRITICAL_();
}
#endif

#endif
