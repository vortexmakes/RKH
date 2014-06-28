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
 *  File                     : rkhdyn.c
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	fwk
 */


#include "rkhrq.h"
#include "rkhassert.h"
#include "rkh.h"


RKH_MODULE_NAME( rkhdyn )


#if RKH_EN_DYNAMIC_EVENT == RKH_ENABLED
	#define RKH_INC_REF( evt ) \
					if( RCE( evt )->pool != 0 ) \
				        ++RCE( evt )->nref
#else
	#define RKH_INC_REF( evt ) \
					(void)0
#endif


#if RKH_EN_DYNAMIC_EVENT == RKH_ENABLED

RKH_DYNE_TYPE rkh_eplist[ RKH_MAX_EPOOL ];


/**
 * 	\brief
 * 	Number of initialized event pools.
 */

static rkhui8_t rkhnpool;


RKH_EVT_T *
rkh_fwk_ae( RKH_ES_T esize, RKH_SIG_T e )
{
    RKH_EVT_T *evt;
    /* find the pool index that fits the requested event size ... */
    rkhui8_t idx = 0;
	RKH_DYNE_TYPE *ep = rkh_eplist;
	RKH_SR_ALLOC();

    while( esize > RKH_DYNE_GET_ESIZE( ep ) ) 
	{
        ++idx;
		++ep;
		/* cannot run out of registered pools */
        RKHASSERT( idx < rkhnpool );
    }

    RKH_DYNE_GET( ep, evt );	/* get e -- platform-dependent */
							    /* pool must not run out of events */
    RKHASSERT( evt != RKH_EVT_CAST(0) );
    evt->e = e;                 /* set signal for this event */

	/* 
	 * Store the dynamic attributes of the event: the pool ID and the 
	 * reference counter = 0
	 */
    evt->nref = 0;
    evt->pool = (rkhui8_t)( idx + (rkhui8_t)1 );

	RKH_TR_FWK_AE( esize, evt, evt->pool - 1, evt->nref );
    return evt;	
}


void 
rkh_gc( RKH_EVT_T *e )
{
	RKH_SR_ALLOC();
	
    if( e->nref != 0 )		/* is it a dynamic event? */
	{
        RKH_ENTER_CRITICAL_();

        if( e->nref > 1 )	/* isn't this the last ref? */
		{
            --e->nref;		/* decrement the reference counter */
            RKH_EXIT_CRITICAL_();
			RKH_TR_FWK_GC( e, e->pool, e->nref );
        }
        else	/* this is the last reference to this event, recycle it */
		{
			/* cannot wrap around */
            rkhui8_t idx = (rkhui8_t)( e->pool - 1 );
            RKH_EXIT_CRITICAL_();

            RKHASSERT( idx < RKH_MAX_EPOOL );
			RKH_TR_FWK_GCR( e, e->pool, e->nref );
            RKH_DYNE_PUT( &rkh_eplist[ idx ], e );
        }
    }
}


void
rkh_reserve( RKH_EVT_T *e )
{
	RKH_SR_ALLOC();

	RKH_ENTER_CRITICAL_();
	RKH_INC_REF( e );
	RKH_EXIT_CRITICAL_();
}


void 
rkh_fwk_epool_register( void *sstart, rkhui32_t ssize, RKH_ES_T esize )
{
	RKH_SR_ALLOC();

	RKHASSERT( ( (rkhui8_t)(rkhnpool + (rkhui8_t)1) ) <= RKH_MAX_EPOOL );

	++rkhnpool;
	RKH_DYNE_INIT( &rkh_eplist[ rkhnpool - 1 ], sstart, ssize, esize );
	RKH_TR_FWK_EPREG( rkhnpool, ssize, esize );
}
#endif


#if RKH_EN_NATIVE_EQUEUE == RKH_ENABLED
void 
#if defined( RKH_USE_TRC_SENDER )
rkh_sma_post_fifo( RKH_SMA_T *sma, const RKH_EVT_T *e, 
									const void *const sender )
#else
rkh_sma_post_fifo( RKH_SMA_T *sma, const RKH_EVT_T *e )
#endif
{
	RKH_SR_ALLOC();
	
	RKH_HOOK_SIGNAL( e );

	RKH_ENTER_CRITICAL_();
	RKH_INC_REF( e );
	RKH_EXIT_CRITICAL_();

	rkh_rq_put_fifo( &sma->equeue, e );
	RKH_TR_SMA_FIFO( sma, e, sender, e->pool, e->nref );
}
#endif


#if RKH_EN_NATIVE_EQUEUE == RKH_ENABLED && \
	RKH_RQ_EN_PUT_LIFO == RKH_ENABLED
void 
#if defined( RKH_USE_TRC_SENDER )
rkh_sma_post_lifo( RKH_SMA_T *sma, const RKH_EVT_T *e, 
									const void *const sender )
#else
rkh_sma_post_lifo( RKH_SMA_T *sma, const RKH_EVT_T *e )
#endif
{
	RKH_SR_ALLOC();

	RKH_HOOK_SIGNAL( e );

	RKH_ENTER_CRITICAL_();
	RKH_INC_REF( e );
	RKH_EXIT_CRITICAL_();

    rkh_rq_put_lifo( &sma->equeue, e );
	RKH_TR_SMA_LIFO( sma, e, sender, e->pool, e->nref );
}
#endif


#if RKH_EN_NATIVE_EQUEUE == RKH_ENABLED
RKH_EVT_T *
rkh_sma_get( RKH_SMA_T *sma )
{
	RKH_EVT_T *e;
	RKH_SR_ALLOC();

    /*RKH_ENTER_CRITICAL_();*/
	e = rkh_rq_get( &sma->equeue );
    /*RKH_EXIT_CRITICAL_();*/

	RKHASSERT( e != ( RKH_EVT_T * )0 );
	RKH_TR_SMA_GET( sma, e, e->pool, e->nref );
	return e;
}
#endif


#if RKH_EN_DEFERRED_EVENT == RKH_ENABLED
void 
rkh_fwk_defer( RKH_RQ_T *q, const RKH_EVT_T *e )
{ 
	RKH_SR_ALLOC();

	RKH_ENTER_CRITICAL_();
	RKH_INC_REF( e );
	RKH_EXIT_CRITICAL_();
	
    rkh_rq_put_fifo( q, e );
	RKH_TR_FWK_DEFER( q, e );
}


RKH_EVT_T *
rkh_fwk_recall( RKH_SMA_T *sma, RKH_RQ_T *q )
{
    RKH_EVT_T *e;
	RKH_SR_ALLOC();
	
	e = rkh_rq_get( q );		/* get an event from deferred queue */
    if( e != RKH_EVT_CAST(0) )	/* event available? */
	{
		/* post it to the front of the SMA's queue */
		RKH_SMA_POST_LIFO( sma, e, sma );
		RKH_TR_FWK_RCALL( sma, e );
        RKH_ENTER_CRITICAL_();

		#if RKH_EN_DYNAMIC_EVENT == RKH_ENABLED
        if( e->nref != 0 )	/* is it a dynamic event? */
		{
            /* 
			 * After posting to the SMA's queue the event must be referenced
             * at least twice: once in the deferred event queue (eq->get()
             * did NOT decrement the reference counter) and once in the
             * SMA's event queue.
             */
            RKHASSERT( e->nref > 1 );

            /* 
			 * We need to decrement the reference counter once, to account
             * for removing the event from the deferred event queue.
             */
            --e->nref;
        }
		#endif
		RKH_EXIT_CRITICAL_();
    }
    return e;
}
#endif
