/*
 *	file: rkhrq.h
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
 * 	\file rkhrq.h
 *
 *	\brief
 * 	Platform-independent interface for supporting queue (by reference) 
 * 	services.
 *
 * 	The queue is a buffer-like object through which state machine applications 
 * 	(SMA) and ISRs send and receive messages to communicate and synchornize 
 * 	with data. It temporarily holds pointer to messages from a sender until 
 * 	the intended receiver is ready to read them.
 */


#ifndef __RKHRQ_H__
#define __RKHRQ_H__


#include "rkhcfg.h"
#include "rkhtype.h"


/** 
 * 	\brief
 * 	This data type defines the maximum number of elements that any queue 
 *	can contain. 
 *
 *	The valid values [in bits] are 8, 16 or 32. Default is 8. This type is 
 *	configurable via the preprocessor switch RKH_RQ_SIZEOF_NELEM.
 */

#if RKH_RQ_SIZEOF_NELEM == 8
	typedef rkhui8_t RKH_RQNE_T;
#elif RKH_RQ_SIZEOF_NELEM == 16
	typedef rkhui16_t RKH_RQNE_T;
#elif RKH_RQ_SIZEOF_NELEM == 32
	typedef rkhui32_t RKH_RQNE_T;
#else
	typedef rkhui8_t RKH_RQNE_T;
#endif


/**
 * 	Return codes from queue operations.
 */

typedef enum
{
	RKH_RQ_OK, RKH_RQ_EMPTY, RKH_RQ_FULL
} RKH_RQCODE_T;


/**
 * 	\brief
 * 	Defines the data structure into which the performance information for
 * 	queues is stored.
 *
 *	The application must allocate an RKH_RQI_T data structure used to 
 *	receive information. The performance information is available during 
 *	run-time for each of the RKH services. This can be useful in determining 
 *	whether the application is performing properly, as well as helping to 
 *	optimize the application.
 */

typedef struct rkh_qinfo_t
{
	rkhui16_t nputs;		/*	# of put requests */
	rkhui16_t ngets;		/*	# of get requests */
	rkhui16_t nreads;		/*	# of queue read requests */
	rkhui16_t nempty;		/*	# of queue empty retrieves */
	rkhui16_t nfull;		/*	# of queue full retrieves */
} RKH_RQI_T;


/**
 * 	\brief
 * 	Defines the data structure used to maintain information about the queue. 
 */

typedef struct
{
	/**
	 * 	Number of elements.
	 */

	RKH_RQNE_T nelems;

	/** 	
	 *  Number of elements currently in the queue.
	 */

	RKH_RQNE_T qty;

	/**
	 *	Points to the free next place in the storage area.
	 */

	void **pout;

	/**
	 * 	Points to the next place of queued item.
	 */

	void **pin;

	/**
	 * 	Points to beginning of the queue storage area.
	 */

	const void **pstart;

	/**
	 * 	Points to the end of the queue storage area.
	 */

	void **pend;

	/**
	 * 	Points to the associated SMA that receives the enqueued events.
	 * 	If \a sma is set to NULL they never block.
	 */

	void *sma;

	/** 
	 * 	Minimum number of free elements ever in this queue.
	 *	The nmin low-watermark provides valuable empirical data for 
	 *	proper sizing of the queue.
	 */

#if RKH_RQ_EN_GET_LWMARK == 1
	RKH_RQNE_T nmin;	
#endif

	/**
	 * 	Performance information. This member is optional, thus it could be 
	 * 	eliminated in compile-time with RKH_RQ_EN_GET_INFO.
	 */

#if RKH_RQ_EN_GET_INFO == 1
	RKH_RQI_T rqi;
#endif

} RKHRQ_T;


/**
 * \brief
 *	Initializes the previously allocated queue data strcuture RKHRQ_T.
 *
 * 	A queue is declared with the RKHRQ_T data type and is defined with the 
 * 	rkh_rq_init() service.
 *
 *	\note 
 *	See RKHRQ_T structure for more information.
 *
 * 	\param q		pointer to previously allocated queue structure.
 * 	\param sstart	storage start. Pointer to an array of pointers that holds 
 * 					the elements. This array must be declared as an array of 
 * 					void pointers.
 * 	\param ssize	storage size [in the units of void pointers].
 * 	\param sma		pointer to associated SMA that receives the enqueued 
 * 					events. If \a sma is set to NULL they never block.
 */

void rkh_rq_init( 	RKHRQ_T *q, const void **sstart, RKH_RQNE_T ssize, 
					void *sma );


/**
 * 	\brief
 * 	This macro query the queue.
 *
 * 	\param q		pointer to previously created queue.
 *
 * 	\return
 * 	'1' (TRUE) if queue is empty, otherwise '0' (FALSE).
 */

#define rkh_rq_is_empty( q )								\
				(HUInt)(rkh_rq_get_num((RKHRQ_T*)(q))==0)


/**
 * 	\brief
 * 	This function query the queue.
 *
 * 	\param q		pointer to previously created queue.
 *
 * 	\return
 * 	'1' (TRUE) if queue is full, otherwise '0' (FALSE).
 */

HUInt rkh_rq_is_full( RKHRQ_T *q );


/**
 * 	\brief
 * 	Returns the number of elements currently in the queue.
 *
 * 	\param q		pointer to previously created queue.
 */

RKH_RQNE_T rkh_rq_get_num( RKHRQ_T *q );


/**
 *	\brief
 * 	This function returns the lowest number of free elements ever present 
 * 	in the pool. 
 * 	This number provides valuable empirical data for proper sizing of the 
 * 	queue.
 * 	
 * 	\param q		pointer to previously created queue.
 *
 * 	\note
 * 	This function is optional, thus it could be eliminated in compile-time 
 * 	with RKH_RQ_EN_GET_LWMARK.
 *
 * 	\return
 * 	Lowest number of free elements ever present in the queue.
 */

RKH_RQNE_T rkh_rq_get_lwm( RKHRQ_T *q );


/**
 * 	\brief
 *	Get and remove an element from a queue.
 *
 * 	\param q		pointer to previously created queue from which the 
 * 					elements are received.
 */

void *rkh_rq_get( RKHRQ_T *q );


/**
 * 	\brief
 *	Puts an element on a queue in a FIFO manner. The element is queued by 
 *	reference, not by copy.
 * 	
 * 	\note 
 * 	The function raises an assertion if the queue becomes full and cannot 
 * 	accept the element.
 *
 * 	\param q		pointer to previously created queue into which the element 
 * 					is deposited.
 * 	\param pe		pointer-sized variable and is application specific.
 */

void rkh_rq_put_fifo( RKHRQ_T *q, const void *pe );


/**
 * 	\brief
 *	Puts an element on a queue in a LIFO manner. The element is queued by 
 *	reference, not by copy.
 *
 * 	\note 
 * 	The function raises an assertion if the queue becomes full and cannot 
 * 	accept the element.
 *
 * 	\param q		pointer to previously created queue into which the element 
 * 					is deposited.
 * 	\param pe		pointer-sized variable and is application specific.
 */

void rkh_rq_put_lifo( RKHRQ_T *q, const void *pe );


/**
 * 	\brief
 *	Depletes a queue. Empties the contents of the queue and eliminates all 
 *	stored elements.
 *	
 *	\note
 *	This function should be used with great care because, when to flush the 
 *	queue, the references are LOOSE to what the queue entries are pointing 
 *	to and thus, could cause 'memory leaks'. In other words, the data 
 *	pointing to that's being referenced by the queue entries should, most 
 *	likely, need to be deallocated. To flush a queue that contains entries, 
 *	is much safer instead repeateadly use rkh_rq_get();
 * 
 * 	\note
 * 	This function is optional, thus it could be eliminated in compile-time 
 * 	with RKH_RQ_EN_DEPLETE.
 *
 * 	\param q		pointer to previously created queue.
 */

void rkh_rq_deplete( RKHRQ_T *q );


/**
 * 	\brief
 *	Read an element from a queue without remove it.
 *
 * 	\note
 * 	This function is optional, thus it could be eliminated in compile-time 
 * 	with RKH_RQ_EN_READ.
 *
 * 	\param q		pointer to previously created queue from which the 
 * 					elements are received.
 * 	\param pe		pointer to the buffer into which the received item will be 
 * 					copied.
 *
 * 	\return
 * 	RKH_RQ_OK if an element was successfully readed from the queue, otherwise 
 * 	error code.
 */

HUInt rkh_rq_read( RKHRQ_T *q, void *pe ); 


/**
 * 	\brief
 * 	Retrieves performance information for a particular queue. 
 *
 *	The user application must allocate an RKH_RQI_T data structure used to 
 *	receive data. The performance information is available during run-time 
 *	for each of the RKH services. This can be useful in determining whether 
 *	the application is performing properly, as well as helping to optimize the 
 *	application.
 *	This information provides a "snapshot" a particular instant in time, i.e., 
 *	when the service is invoked.
 *
 * 	\note
 * 	See RKH_RQI_T structure for more information. This function is 
 * 	optional, thus it could be eliminated in compile-time with 
 * 	RKH_RQ_EN_GET_INFO.
 *
 * 	\param q		pointer to previously created queue.
 * 	\param pqi		pointer to the buffer into which the performance 
 * 					information will be copied.
 */

void rkh_rq_get_info( RKHRQ_T *q, RKH_RQI_T *pqi );


/**
 * 	\brief
 * 	Clear performance information for a particular queue.
 *
 * 	\note
 * 	This function is optional, thus it could be eliminated in compile-time 
 * 	with RKH_RQ_EN_GET_INFO.
 *
 * 	\param q		pointer to previously created queue.
 */

void rkh_rq_clear_info( RKHRQ_T *q );


#endif
