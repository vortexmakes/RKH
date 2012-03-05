/*
 *	file: rkhrq.c
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
 * 	\file rkhrq.c
 *
 *	\brief
 * 	Implements a queue (by reference) services.
 *
 * 	The queue is a buffer-like object through which state machine applications 
 * 	(SMA) and ISRs send and receive messages to communicate and synchornize 
 * 	with data. It temporarily holds pointer to messages from a sender until 
 * 	the intended receiver is ready to read them.
 */


#include "rkhassert.h"
#include "rkhrq.h"
#include "rkh.h"


RKH_THIS_MODULE( 4, rkhrq );


#if RKH_RQ_EN_GET_INFO == 1
	#define RKH_IUPDT_INSERT( q )		++q->rqi.nputs
	#define RKH_IUPDT_REMOVE( q )		++q->rqi.ngets
	#define RKH_IUPDT_EMPTY( q )		++q->rqi.nempty
	#define RKH_IUPDT_FULL( q )			++q->rqi.nfull
#else
	#define RKH_IUPDT_INSERT( q )
	#define RKH_IUPDT_REMOVE( q )
	#define RKH_IUPDT_EMPTY( q )
	#define RKH_IUPDT_FULL( q )
#endif


void 
rkh_rq_init( RKHRQ_T *q, const void **sstart, RKH_RQNE_T ssize )
{
	RKH_iSR_CRITICAL;
	RKH_iENTER_CRITICAL();
	RKH_iEXIT_CRITICAL();

	q->pstart = q->pin = q->pout = sstart;
	q->nelem = ssize;
	q->qty = 0;
	q->pend = sstart + ssize;
#if RKH_RQ_EN_GET_LWMARK == 1
	q->nmin = 0;
#endif
#if RKH_RQ_EN_GET_INFO == 1
	q->rqi.nputs = q->rqi.ngets = q->rqi.nempty = q->rqi.nfull = 0;
#endif
}


#if RKH_RQ_EN_IS_FULL == 1
HUInt 
rkh_rq_is_full( RKHRQ_T *q )
{
	RKH_RQNE_T qty;
	RKH_iSR_CRITICAL;
	
	RKHASSERT( q != ( RKHRQ_T* )0 );
	
	RKH_iENTER_CRITICAL();
	qty = q->qty;
	RKH_iEXIT_CRITICAL();

	return qty == q->nelem;
}
#endif


RKH_RQNE_T 
rkh_rq_get_num( RKHRQ_T *q )
{
	RKH_RQNE_T qty;
	RKH_iSR_CRITICAL;
	
	RKHASSERT( q != ( RKHRQ_T* )0 );
	
	RKH_iENTER_CRITICAL();
	qty = q->qty;
	RKH_iEXIT_CRITICAL();

	return qty;
}


#if RKH_RQ_EN_GET_LWM == 1
RKH_RQNE_T 
rkh_rq_get_lwm( RKHRQ_T *q )
{
	RKH_RQNE_T nmin;
	RKH_iSR_CRITICAL;
	
	RKHASSERT( q != ( RKHRQ_T* )0 );
	
	RKH_iENTER_CRITICAL();
	nmin = q->nmin;
	RKH_iEXIT_CRITICAL();

	return nmin;
}
#endif


HUInt 
rkh_rq_get( RKHRQ_T *q, void *pe )
{
	RKH_iSR_CRITICAL;

	RKHASSERT( q != ( RKHRQ_T* )0 && pe != ( const void* )0 );

	if( q->qty == 0 )
	{
		RKH_IUPDT_EMPTY( q );
		return RKH_RQ_EMPTY;
	}

	RKH_iENTER_CRITICAL();

	pe = *q->pout;

	if( ++q->pout >= q->pend )
		q->pout = q->pstart;

	--q->qty;
	RKH_IUPDT_REMOVE( q );

	RKH_iEXIT_CRITICAL();

	//rktrace_remove_queue( qd );
	return RKH_RQ_OK;
}


void 
rkh_rq_put_fifo( RKHRQ_T *q, const void *pe )
{
	RKH_iSR_CRITICAL;

	RKHASSERT( q != ( RKHRQ_T* )0 && pe != ( const void* )0 );
	RKH_iENTER_CRITICAL();

	if( q->qty >= q->nelem )
	{
		RKH_IUPDT_FULL( q );
		RKH_iEXIT_CRITICAL();
		return RKH_RQ_FULL;
	}

	*q->pin = pe;

	if( ++q->pin >= q->pend )
		q->pin = q->pstart;

	++q->qty;
#if RKH_RQ_GET_LWM == 1
	if( q->nmin > ( q->nelem - q->qty ) )
		q->nmin = ( q->nelem - q->qty );
#endif
	RKH_IUPDT_INSERT( q );
	RKH_iEXIT_CRITICAL();

	//rktrace_insert_queue( qd );
	return RKH_RQ_OK;
}


void 
rkh_rq_put_lifo( RKHRQ_T *q, const void *pe )
{
	RKH_iSR_CRITICAL;
	RKH_iENTER_CRITICAL();
	RKH_iEXIT_CRITICAL();
}


void 
queue_deplete( RKHRQ_T *q )
{
	RKH_iSR_CRITICAL;
	RKH_iENTER_CRITICAL();
	RKH_iEXIT_CRITICAL();
}


HUInt 
rkh_rq_read( RKHRQ_T *q, void *pe )
{
	RKH_iSR_CRITICAL;
	RKH_iENTER_CRITICAL();
	RKH_iEXIT_CRITICAL();
}


void 
rkh_rq_get_info( RKHRQ_T *q, RKH_RQI_T *pqi )
{
	RKH_iSR_CRITICAL;
	RKH_iENTER_CRITICAL();
	RKH_iEXIT_CRITICAL();
}


void 
rkh_rq_clear_info( RKHRQ_T *q )
{
	RKH_iSR_CRITICAL;
	RKH_iENTER_CRITICAL();
	RKH_iEXIT_CRITICAL();
}
