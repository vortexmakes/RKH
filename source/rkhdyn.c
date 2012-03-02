/*
 *	file: rkhdyn.c
 *	Last updated for version: 1.0.00
 *	Date of the last update:  Feb 23, 2012
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
 * 	\file rkhdyn.c
 *	\brief
 */


#include "rkhrq.h"
#include "rkhassert.h"
#include "rkh.h"


RKH_THIS_MODULE( 2, rkhdyn );


#if RKH_EN_DYNAMIC_EVENT == 1


RKH_DYNE_TYPE rkh_epl[ RKH_MAX_EPOOL ];
rkhui8_t rkhnpool;


RKHEVT_T *
rkh_ae( RKHES_T esize, RKHE_T e )
{
    RKHEVT_T *evt;

              /* find the pool index that fits the requested event size ... */
    rkhui8_t idx = 0;
	RKH_DYNE_TYPE *ep = rkh_epl;

    while( esize > RKH_DYNE_GET_ESIZE( ep ) ) 
	{
        ++idx;
		++ep;
									  /* cannot run out of registered pools */
        RKHASSERT( idx < rkhnpool );
    }

    RKH_DYNE_GET( ep, evt );                 /* get e -- platform-dependent */
							             /* pool must not run out of events */
    RKHASSERT( evt != NULL );
    evt->e = e;                                /* set signal for this event */

	/* 
	 * Store the dynamic attributes of the event:
	 * the pool ID and the reference counter = 0
	 */
    evt->dynamic_ = 0;
    evt->pool = idx + 1;

    return evt;	
}


void 
rkh_gc( RKHEVT_T *e )
{
	RKH_iSR_CRITICAL;
	
    if( e->dynamic_ != 0 )                      /* is it a dynamic event? */
	{
        RKH_iENTER_CRITICAL();

        if( e->dynamic_ > 1 )                 /* isn't this the last ref? */
		{
            --e->dynamic_;             /* decrement the reference counter */
            RKH_iEXIT_CRITICAL();
        }
        else        /* this is the last reference to this event, recycle it */
		{
                                                      /* cannot wrap around */
            rkhui8_t idx = (rkhui8_t)( e->pool - 1 );
            RKH_iEXIT_CRITICAL();

            RKHASSERT( idx < RKH_MAX_EPOOL );
            RKH_DYNE_PUT( &rkh_epl[ idx ], e );
        }
    }
}


#if RKH_EN_NATIVE_EQUEUE == 1
void 
rkh_sma_post_fifo( RKHSMA_T *sma, const RKHEVT_T *e )
{
	RKH_iSR_CRITICAL;

    RKH_iENTER_CRITICAL();
    if( (( RKHEVT_T *)e )->pool != 0 ) 
        ++(( RKHEVT_T *)e )->dynamic_;

	RKH_SMA_READY( sma );
    rkh_rq_put_fifo( &sma->equeue, e );
    RKH_iEXIT_CRITICAL();
}
#endif


#if RKH_EN_NATIVE_EQUEUE == 1
void 
rkh_sma_post_lifo( RKHSMA_T *sma, const RKHEVT_T *e )
{
	RKH_iSR_CRITICAL;

    RKH_iENTER_CRITICAL();
    if( (( RKHEVT_T *)e )->pool != 0 ) 
        ++(( RKHEVT_T *)e )->dynamic_;

	RKH_SMA_READY( sma );
    rkh_rq_put_lifo( &sma->equeue, e );
    RKH_iEXIT_CRITICAL();
}
#endif


#if RKH_EN_NATIVE_EQUEUE == 1
HUInt 
rkh_sma_get( RKHSMA_T *sma, RKHEVT_T *e )
{
}
#endif


#if RKH_EN_DEFERRED_EVENT == 1
void 
void rkh_defer( RKHRQ_T *q, const RKHEVT_T *e )
{ 
    rkh_rq_put_fifo( q, e );
}


RKHEVT_T *
rkh_recall( RKHSMA_T *sma, RKHRQ_T *q )
{
    RKHEVT_T *e;
	HUInt r;
	RKH_iSR_CRITICAL;
	
										/* get an event from deferred queue */
    if( ( r = rkh_rq_get( q, e ) ) == RKH_RQ_OK )       /* event available? */
	{
		/* post it to the front of the SMA's queue */
		rkh_sma_post_lifo( sma, e );
        RKH_iENTER_CRITICAL();

        if( e->dynamic_ != 0 )           		  /* is it a dynamic event? */
		{
            /* 
			 * After posting to the SMA's queue the event must be referenced
             * at least twice: once in the deferred event queue (eq->get()
             * did NOT decrement the reference counter) and once in the
             * SMA's event queue.
             */
            RKHASSERT( e->dynamic_ > 1 );

            /* 
			 * We need to decrement the reference counter once, to account
             * for removing the event from the deferred event queue.
             */
            --e->dynamic_;
        }
		RKH_iEXIT_CRITICAL();
    }
    return r != 0 ? NULL : e;
}
#endif


void 
rkh_dyne_regs( void *sstart, rkhui32_t ssize, RKHES_T esize )
{
}


#endif
