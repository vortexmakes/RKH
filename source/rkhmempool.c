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
 *  \file       rkhmempool.c
 *  \ingroup    mp
 *
 *  \brief      Implements a pool of fixed-size memory blocks.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.17.05  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkhitl.h"
#include "rkhmempool.h"
#include "rkhassert.h"
#include "rkhtrc_record.h"
#include "rkhtrc_filter.h"

#if RKH_CFG_MP_EN == RKH_ENABLED

RKH_MODULE_NAME(rkhmempool)

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/*
 *  Structure representing a free block.
 */
typedef struct rkh_free_blk_t
{
    struct rkh_free_blk_t *next;
} RKH_FREE_BLK_T;

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
rkh_memPool_init(RKH_MEMPOOL_T *mp, void *sstart, rui16_t ssize,
            RKH_MPBS_T bsize)
{
    RKH_FREE_BLK_T *fb;
    RKH_MPNB_T nblocks;
    RKH_SR_ALLOC();

    /*
     * The memory block must be valid and the pool size (\a ssize) must fit
     * at least one free block and the block size (\a bsize) must not be too
     * close to the top of the dynamic range.
     */
    RKH_ASSERT(sstart != RKH_NULL &&
               ssize >= sizeof(RKH_FREE_BLK_T) &&
               (RKH_MPBS_T)(bsize + sizeof(RKH_FREE_BLK_T)) > bsize);

    mp->free = (void *)(sstart);

    /*
     * (1) Round up the 'bsize' to fit an integer # free blocks, no division.
     */
    mp->bsize = sizeof(RKH_FREE_BLK_T);               /* start with just one */
    nblocks = 1;               /* # free blocks that fit in one memory block */

    while (mp->bsize < bsize)
    {
        mp->bsize += sizeof(RKH_FREE_BLK_T);
        ++nblocks;
    }

    bsize = mp->bsize;               /* use the rounded-up value from now on */

    /* The pool buffer must fit at least one rounded-up block. */
    RKH_ASSERT(ssize >= (rui16_t)bsize);

    /* Chain all blocks together in a free-list...*/
    ssize -= (rui16_t)bsize;               /* don't count the last block */
    mp->nblocks = 1;                   /* the last block already in the pool */
    fb = (RKH_FREE_BLK_T *)mp->free;    /*start at the head of the free list */

    while (ssize >= (rui16_t)bsize)
    {
        fb->next = &fb[nblocks];    /* point the next link to the next block */
        fb = fb->next;              /* advance to the next block */
        ssize -= (rui16_t)bsize;    /* reduce the available pool size */
        ++mp->nblocks;              /* increment the number of blocks so far */
    }

    fb->next  = (RKH_FREE_BLK_T *)0;         /* the last link points to NULL */
    mp->nfree = mp->nblocks;                          /* all blocks are free */
#if RKH_CFG_MP_GET_LWM_EN == RKH_ENABLED && \
    RKH_CFG_MP_REDUCED_EN == RKH_DISABLED
    mp->nmin  = mp->nblocks;            /* the minimum number of free blocks */
#endif
#if RKH_CFG_MP_REDUCED_EN == RKH_DISABLED
    mp->start = sstart;               /* the original start this pool buffer */
    mp->end   = fb;                           /* the last block in this pool */
#endif
    RKH_TR_MP_INIT(mp, mp->nblocks, mp->bsize);
}

void *
rkh_memPool_get(RKH_MEMPOOL_T *mp)
{
    RKH_FREE_BLK_T *fb;
    RKH_SR_ALLOC();

    RKH_ASSERT(mp != (RKH_MEMPOOL_T *)0 && mp->bsize != 0);

    RKH_ENTER_CRITICAL_();

    fb = (RKH_FREE_BLK_T *)mp->free;            /* get a free block or NULL */
    if (fb != RKH_NULL)                            /* free block available? */
    {
        mp->free = fb->next;     /* adjust list head to the next free block */
        RKH_ASSERT(mp->nfree > (RKH_MPNB_T)0);    /* at least one free block */
        --mp->nfree;                                 /* one less free block */
#if RKH_CFG_MP_GET_LWM_EN == RKH_ENABLED && \
        RKH_CFG_MP_REDUCED_EN == RKH_DISABLED
        if (mp->nmin > mp->nfree)
        {
            mp->nmin = mp->nfree;            /* remember the minimum so far */
        }
#endif
    }

#if RKH_CFG_MP_GET_LWM_EN == RKH_ENABLED && \
        RKH_CFG_MP_REDUCED_EN == RKH_DISABLED
    RKH_TR_MP_GET(mp, mp->nfree, mp->nmin);
#else
    RKH_TR_MP_GET(mp, mp->nfree, mp->nfree);
#endif
    RKH_EXIT_CRITICAL_();
    return fb;            /* return the block or NULL pointer to the caller */
}

void
rkh_memPool_put(RKH_MEMPOOL_T *mp, void *blk)
{
    RKH_SR_ALLOC();

    RKH_ASSERT(mp != (RKH_MEMPOOL_T *)0);
    RKH_ASSERT(mp->bsize != 0);

#if RKH_CFG_MP_REDUCED_EN == RKH_DISABLED
    RKH_ASSERT(mp->start <= blk &&                       /* must be in range */
               blk <= mp->end &&
               mp->nfree < mp->nblocks);    /* # free blocks must be < total */
#else
    RKH_ASSERT(mp->nfree < mp->nblocks);    /* # free blocks must be < total */
#endif

    RKH_ENTER_CRITICAL_();

    /* link into free list */
    ((RKH_FREE_BLK_T *)blk)->next = (RKH_FREE_BLK_T *)mp->free;
    mp->free = blk;                      /* set as new head of the free list */
    ++mp->nfree;                         /* one more free block in this pool */

    RKH_TR_MP_PUT(mp, mp->nfree);
    RKH_EXIT_CRITICAL_();
}

#if RKH_CFG_MP_GET_BSIZE_EN == RKH_ENABLED
RKH_MPBS_T
rkh_memPool_get_bsize(RKH_MEMPOOL_T *mp)
{
    RKH_MPBS_T bs;
    RKH_SR_ALLOC();

    RKH_ASSERT(mp != (RKH_MEMPOOL_T *)0);

    RKH_ENTER_CRITICAL_();
    bs = mp->bsize;
    RKH_EXIT_CRITICAL_();

    return bs;
}
#endif

#if RKH_CFG_MP_GET_NFREE_EN == RKH_ENABLED
RKH_MPNB_T
rkh_memPool_get_nfree(RKH_MEMPOOL_T *mp)
{
    RKH_MPNB_T nfree;
    RKH_SR_ALLOC();

    RKH_ASSERT(mp != (RKH_MEMPOOL_T *)0);

    RKH_ENTER_CRITICAL_();
    nfree = mp->nfree;
    RKH_EXIT_CRITICAL_();

    return nfree;
}
#endif

#if RKH_CFG_MP_GET_LWM_EN == RKH_ENABLED && \
    RKH_CFG_MP_REDUCED_EN == RKH_DISABLED
RKH_MPNB_T
rkh_memPool_get_low_wmark(RKH_MEMPOOL_T *mp)
{
    RKH_MPNB_T nmin;
    RKH_SR_ALLOC();

    RKH_ASSERT(mp != (RKH_MEMPOOL_T *)0);

    RKH_ENTER_CRITICAL_();
    nmin = mp->nmin;
    RKH_EXIT_CRITICAL_();

    return nmin;
}
#endif

#if RKH_CFG_MP_GET_INFO_EN == RKH_ENABLED && \
    RKH_CFG_MP_REDUCED_EN == RKH_DISABLED
void
rkh_memPool_get_info(RKH_MEMPOOL_T *mp, RKH_MPI_T *mpi)
{
    RKH_SR_ALLOC();

    RKH_ASSERT(mp != (RKH_MEMPOOL_T *)0 && mpi != (RKH_MPI_T *)0);

    RKH_ENTER_CRITICAL_();
    *mpi = mp->mpi;
    RKH_EXIT_CRITICAL_();
}

void
rkh_memPool_clear_info(RKH_MEMPOOL_T *mp)
{
    RKH_MPI_T *pmpi;
    RKH_SR_ALLOC();

    RKH_ASSERT(mp != (RKH_MEMPOOL_T *)0);
    pmpi = &mp->mpi;

    RKH_ENTER_CRITICAL_();
    pmpi->inits = pmpi->gets = pmpi->puts = pmpi->free = pmpi->full = 0;
    RKH_EXIT_CRITICAL_();
}
#endif

#endif
/* ------------------------------ End of file ------------------------------ */
