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
 *  File                     : rkhrq.c
 *	Last updated for version : v2.4.04
 *	By                       : LF
 *  --------------------------------------------------------------------------
 *  \endcond
 *
 * 	\file
 * 	\ingroup 	que
 *	\brief 		Implements a queue (by reference) services.
 */


#include "rkhassert.h"
#include "rkhrq.h"
#include "rkhrdy.h"
#include "rkh.h"


#if RKH_CFG_RQ_EN == RKH_ENABLED

RKH_MODULE_NAME( rkhrq )


#if RKH_CFG_RQ_GET_INFO_EN == RKH_ENABLED
	#define RKH_IUPDT_PUT( q )			++q->rqi.nputs
	#define RKH_IUPDT_GET( q )			++q->rqi.ngets
	#define RKH_IUPDT_EMPTY( q )		++q->rqi.nempty
	#define RKH_IUPDT_FULL( q )			++q->rqi.nfull
	#define RKH_IUPDT_READ( q )			++q->rqi.nreads
#else
	#define RKH_IUPDT_PUT( q )
	#define RKH_IUPDT_GET( q )
	#define RKH_IUPDT_EMPTY( q )
	#define RKH_IUPDT_FULL( q )
	#define RKH_IUPDT_READ( q )
#endif


void rkh_rq_init( 	RKH_RQ_T *q, const void **sstart, RKH_RQNE_T ssize, 
					const struct RKH_SMA_T *sma )
{
	RKH_SR_ALLOC();

	q->pstart = sstart;
	q->pin = q->pout = (void **)sstart;
	q->nelems = ssize;
	q->qty = 0;
	q->pend = (void **)&sstart[ ssize ];
	q->sma = sma;	
#if RKH_CFG_RQ_GET_LWMARK_EN == RKH_ENABLED
	q->nmin = q->nelems;
#endif
#if RKH_CFG_RQ_GET_INFO_EN == RKH_ENABLED
	q->rqi.nputs = q->rqi.ngets = q->rqi.nreads = q->rqi.nempty = 
		q->rqi.nfull = 0;
#endif
	RKH_TR_RQ_INIT( q, sma, ssize );
}


#if RKH_CFG_RQ_IS_FULL_EN == RKH_ENABLED
rbool_t 
rkh_rq_is_full( RKH_RQ_T *q )
{
	RKH_RQNE_T qty;
	RKH_SR_ALLOC();
	
	RKH_ASSERT( q != (RKH_RQ_T *)0 );
	
	RKH_ENTER_CRITICAL_();
	qty = q->qty;
	RKH_EXIT_CRITICAL_();

	return qty == q->nelems;
}
#endif


#if RKH_CFG_RQ_GET_NELEMS_EN == RKH_ENABLED
RKH_RQNE_T 
rkh_rq_get_num( RKH_RQ_T *q )
{
	RKH_RQNE_T qty;
	RKH_SR_ALLOC();
	
	RKH_ASSERT( q != CQ(0) );
	
	RKH_ENTER_CRITICAL_();
	qty = q->qty;
	RKH_EXIT_CRITICAL_();

	return qty;
}
#endif


#if RKH_CFG_RQ_GET_LWMARK_EN == RKH_ENABLED
RKH_RQNE_T 
rkh_rq_get_lwm( RKH_RQ_T *q )
{
	RKH_RQNE_T nmin;
	RKH_SR_ALLOC();
	
	RKH_ASSERT( q != CQ(0) );
	
	RKH_ENTER_CRITICAL_();
	nmin = q->nmin;
	RKH_EXIT_CRITICAL_();

	return nmin;
}
#endif


void *
rkh_rq_get( RKH_RQ_T *q  )
{
	void *e = CV(0);
	RKH_SR_ALLOC();

	RKH_ASSERT( q != CQ(0) );
	RKH_ENTER_CRITICAL_();

	if( q->sma != CSMA(0) )
	{
		RKH_SMA_BLOCK( q->sma );
	}
	else if( q->qty == 0 )
	{
		RKH_IUPDT_EMPTY( q );
		RKH_EXIT_CRITICAL_();
		return e;
	}

	e = *q->pout++;
	--q->qty;

	if( q->pout == q->pend )
		q->pout = ( void ** )q->pstart;

	RKH_IUPDT_GET( q );

	if( q->sma != CSMA(0) && q->qty == 0 )
	{
		RKH_SMA_UNREADY( rkhrg, (RKH_SMA_T *)( q->sma ) );
		RKH_TR_RQ_GET_LAST( q );
		RKH_EXIT_CRITICAL_();
	}
	else
	{
		RKH_TR_RQ_GET( q, q->qty );
		RKH_EXIT_CRITICAL_();
	}
	return e;
}


void 
rkh_rq_put_fifo( RKH_RQ_T *q, const void *pe )
{
	RKH_SR_ALLOC();

	RKH_ASSERT( q != CQ(0) && pe != ( const void* )0 );
	/*RKH_ENTER_CRITICAL_();*/
	RKH_ASSERT( q->qty < q->nelems );

	if( q->qty >= q->nelems )
	{
		RKH_IUPDT_FULL( q );
		RKH_TR_RQ_FULL( q );
		/*RKH_EXIT_CRITICAL_();*/
		return;
	}

	*q->pin++ = ( char* )pe;
	++q->qty;

	if( q->pin == q->pend )
		q->pin = ( void ** )q->pstart;

	if( q->sma != CSMA(0) )
	{
		RKH_SMA_READY( rkhrg, (RKH_SMA_T *)( q->sma ) );
	}

#if RKH_CFG_RQ_GET_LWMARK_EN == RKH_ENABLED
	if( q->nmin > (RKH_RQNE_T)( q->nelems - q->qty ) )
		q->nmin = (RKH_RQNE_T)( q->nelems - q->qty );
#endif
	RKH_IUPDT_PUT( q );
	/*RKH_EXIT_CRITICAL_();*/
	RKH_TR_RQ_FIFO( q, q->qty, q->nmin );
}


#if RKH_CFG_RQ_PUT_LIFO_EN == RKH_ENABLED
void 
rkh_rq_put_lifo( RKH_RQ_T *q, const void *pe )
{
	RKH_SR_ALLOC();

	RKH_ASSERT( q != CQ(0) && pe != ( const void* )0 );
	/*RKH_ENTER_CRITICAL_();*/
	RKH_ASSERT( q->qty < q->nelems );

	if( q->qty >= q->nelems )
	{
		RKH_IUPDT_FULL( q );
		RKH_TR_RQ_FULL( q );
		/*RKH_EXIT_CRITICAL_();*/
		return;
	}

	if( q->pout == (void **)q->pstart )
		q->pout = q->pend;

	--q->pout;
	*q->pout = CV( pe );
	++q->qty;

	RKH_IUPDT_PUT( q );

	if( q->sma != CSMA(0) )
	{
		RKH_SMA_READY( rkhrg, (RKH_SMA_T *)( q->sma ) );
	}

#if RKH_CFG_RQ_GET_LWMARK_EN == RKH_ENABLED
	if( q->nmin > (RKH_RQNE_T)( q->nelems - q->qty ) )
		q->nmin = (RKH_RQNE_T)( q->nelems - q->qty );
#endif
	/*RKH_EXIT_CRITICAL_();*/
	RKH_TR_RQ_LIFO( q, q->qty, q->nmin );
}
#endif


#if RKH_CFG_RQ_DEPLETE_EN == RKH_ENABLED
void 
rkh_rq_deplete( RKH_RQ_T *q )
{
	RKH_SR_ALLOC();

	RKH_ASSERT( q != CQ(0) );
	RKH_ENTER_CRITICAL_();
	q->qty = 0;
	q->pin = q->pout = ( void ** )q->pstart;
	if( q->sma != CSMA(0) )
		RKH_SMA_UNREADY( rkhrg, (RKH_SMA_T *)( q->sma ) );
	RKH_TR_RQ_DPT( q );
	RKH_EXIT_CRITICAL_();
}
#endif


#if RKH_CFG_RQ_READ_EN == RKH_ENABLED
ruint 
rkh_rq_read( RKH_RQ_T *q, void *pe )
{
	RKH_SR_ALLOC();

	RKH_ASSERT( q != CQ(0) && pe != ( const void* )0 );
	RKH_ENTER_CRITICAL_();

	if( q->qty == 0 )
	{
		RKH_IUPDT_EMPTY( q );
		RKH_EXIT_CRITICAL_();
		return RKH_RQ_EMPTY;
	}

	pe = *q->pout;

	RKH_IUPDT_READ( q );
	RKH_EXIT_CRITICAL_();
	return RKH_RQ_OK;
}
#endif


#if RKH_CFG_RQ_GET_INFO_EN == RKH_ENABLED
void 
rkh_rq_get_info( RKH_RQ_T *q, RKH_RQI_T *pqi )
{
	RKH_SR_ALLOC();

	RKH_ENTER_CRITICAL_();
	*pqi = q->rqi;
	RKH_EXIT_CRITICAL_();
}


void 
rkh_rq_clear_info( RKH_RQ_T *q )
{
	RKH_RQI_T *prqi;
	RKH_SR_ALLOC();

	prqi = &q->rqi;

	RKH_ENTER_CRITICAL_();
	prqi->nputs = prqi->ngets = prqi->nreads = prqi->nempty = prqi->nfull = 0;
	RKH_EXIT_CRITICAL_();
}
#endif

#endif
