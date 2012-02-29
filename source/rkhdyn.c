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


#include "rkhitl.h"
#include "rkh.h"
#include "rkhassert.h"


#if RKH_EN_DYNAMIC_EVENT == 1


RKH_DYNE_TYPE rkh_epl[ RKH_MAX_EPOOL ];
rkhui8_t rkhnpool;

RKH_THIS_MODULE( 3, rkhdyn );


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
rkh_gc( RKHEVT_T *evt )
{
	RKH_iSR_CRITICAL;
	
    if( evt->dynamic_ != 0 )                      /* is it a dynamic event? */
	{
        RKH_iENTER_CRITICAL();

        if( evt->dynamic_ > 1 )                 /* isn't this the last ref? */
		{
            --evt->dynamic_;             /* decrement the reference counter */
            RKH_iEXIT_CRITICAL();
        }
        else        /* this is the last reference to this event, recycle it */
		{
                                                      /* cannot wrap around */
            rkhui8_t idx = (rkhui8_t)( evt->pool - 1 );
            RKH_iEXIT_CRITICAL();

            RKHASSERT( idx < RKH_MAX_EPOOL );
            RKH_DYNE_PUT( &rkh_epl[ idx ], evt );
        }
    }
}


#if RKH_EN_NATIVE_SCHEDULER == 1 && RKH_EN_NATIVE_PUTFIFO == 1
void 
rkh_sma_put_fifo( HUInt qd, RKHEVT_T *evt )
{
	RKH_iSR_CRITICAL;

    RKH_iENTER_CRITICAL();
    if( evt->dynamic_ != 0 ) 
        ++evt->dynamic_;
    RKH_iEXIT_CRITICAL();

    RKHALLEGE( rkh_post_fifo( qd, evt ) == 0 ); 
}
#endif


#if RKH_EN_NATIVE_SCHEDULER == 1 && RKH_EN_NATIVE_PUTLIFO == 1
void 
rkh_sma_put_lifo( HUInt qd, RKHEVT_T *evt )
{
	RKH_iSR_CRITICAL;

    RKH_iENTER_CRITICAL();
    if( evt->dynamic_ != 0 ) 
        ++evt->dynamic_;
    RKH_iEXIT_CRITICAL();

    RKHALLEGE( rkh_post_fifo( qd, evt ) == 0 ); 
}
#endif


#if RKH_EN_NATIVE_SCHEDULER == 1 && RKH_EN_NATIVE_GET == 1
void
rkh_sma_get( void )
{
}
#endif


#if RKH_EN_DEFERRED_EVENT == 1

void 
void rkh_defer( RKHSMA_T *sma, RKHRQ_T *q, const RKHEVT_T *e )
{ 
	rkh_put_fifo( qd, evt );
}


RKHEVT_T *
rkh_recall( HUInt qdd, HUInt qds )
{
    RKHEVT_T *evt;
	HUInt r;
	RKH_iSR_CRITICAL;
	
										/* get an event from deferred queue */
    if( ( r = rkh_get( qds, evt ) ) == 0 )     			/* event available? */
	{
		/* post it to the front of the AO's queue */
        rkh_put_lifo( qdd, evt );
        RKH_iENTER_CRITICAL();

        if( evt->dynamic_ != 0 )           		  /* is it a dynamic event? */
		{
            /* 
			 * After posting to the AO's queue the event must be referenced
             * at least twice: once in the deferred event queue (eq->get()
             * did NOT decrement the reference counter) and once in the
             * AO's event queue.
             */
            RKHASSERT( evt->dynamic_ > 1 );

            /* 
			 * We need to decrement the reference counter once, to account
             * for removing the event from the deferred event queue.
             */
            --evt->dynamic_;
        }
		RKH_iEXIT_CRITICAL();
    }
    return r != 0 ? NULL : evt;
}
#endif


void 
rkh_dyne_regs( void *sstart, rkhui32_t ssize, RKH_MPBS_T esize )
{
}


#endif
