/*
 *	file: rkhrqueue.h
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
 * 	\file rkhrqueue.h
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


#ifndef __RKHRQUEUE_H__
#define __RKHRQUEUE_H__


#include "rkh.h"


/**
 * 	\brief
 * 	Queue property.
 * 	When a queue is initialized as RKH_Q_NOSCHED it never block.
 */

enum
{
	RKH_Q_SCHED, RKH_Q_NOSCHED
};


/**
 * 	Return codes from queue operations.
 */

enum
{
	RKH_RQ_OK, RKH_RQ_EMPTY, RKH_RQ_FULL
};


/** 
 * 	\brief
 * 	This data type defines the maximum number of elements that any queue 
 *	can contain. 
 *
 *	The valid values [in bits] are 8, 16 or 32. Default is 8. This type is 
 *	configurable via the preprocessor switch RKH_SIZEOF_QNE.
 */

#if RKH_SIZEOF_QNE == 8
	typedef rkhui8_t RKH_RQNE_T;
#elif RKH_SIZEOF_QNE == 16
	typedef rkhui16_t RKH_RQNE_T;
#elif RKH_SIZEOF_QNE == 32
	typedef rkhui32_t RKH_RQNE_T;
#else
	typedef rkhui8_t RKH_RQNE_T;
#endif


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
	 *	Indicates whether the queue is schedulable (RKH_Q_SCHED) 
	 *	or not (RKH_Q_NOSCHED) 
	 */

	rkhui8_t sched;

	/**
	 * 	Number of elements.
	 */

	RKH_RQNE_T nelem;

	/** 	
	 *  Number of elements currently in the queue.
	 */

	RKH_RQNE_T qty;

	/**
	 *	Points to the free next place in the storage area.
	 */

	void *pout;

	/**
	 * 	Points to the next place of queued item.
	 */

	void *pin;

	/**
	 * 	Points to beginning of the queue storage area.
	 */

	const void **pstart;

	/**
	 * 	Points to the end of the queue storage area.
	 */

	char *pend;

	/**
	 * 	Performance information. This member is optional, thus it could be 
	 * 	declared as NULL or eliminated in compile-time with 
	 * 	RKH_EN_RQUEUE_GET_INFO.
	 */

#if RKH_EN_RQUEUE_GET_INFO == 1
	RKH_RQI_T qinfo;
#endif

	/** 
	 * 	Minimum number of free elements ever in this queue.
	 *	The nmin low-watermark provides valuable empirical data for 
	 *	proper sizing of the queue.
	 */

#if RKH_EN_RQUEUE_GET_LWMARK == 1
	RKH_RQNE_T nmin;	
#endif

} RKHRQ_T;


/**
 * \brief
 *	Initializes the previously allocated queue data strcuture RKHRQ_T.
 *
 *	\note 
 *	See RKHRQ_T structure for more information.
 *
 * 	\param q		pointer to previously allocated queue structure.
 * 	\param ps 		pointer to an array of pointers that holds the elements. 
 * 					This array must be declared as an array of void pointers.
 *	\param sched	indicates whether the queue is schedulable (RKH_Q_SCHED) 
 *					or not (RKH_Q_NOSCHED). 
 */

void rkh_rqueue_init( RKHRQ_T *q, const void **ps, rkhui8_t sched );


/**
 * 	\brief
 * 	This macro query the queue.
 *
 * 	\param q		pointer to previously created queue.
 *
 * 	\return
 * 	'1' (TRUE) if queue is empty, otherwise '0' (FALSE).
 */

#define rkh_rqueue_is_empty( q )								\
				(HUInt)(rkh_rqueue_get_num((RKHRQ_T*)(q))==0)


/**
 * 	\brief
 * 	This function query the queue.
 *
 * 	\param q		pointer to previously created queue.
 *
 * 	\return
 * 	'1' (TRUE) if queue is full, otherwise '0' (FALSE).
 */

HUInt rkh_rqueue_is_full( RKHRQ_T *q );


/**
 * 	\brief
 * 	Returns the number of elements currently in the queue.
 *
 * 	\param q		pointer to previously created queue.
 */

RKH_RQNE_T rkh_rqueue_get_num( RKHRQ_T *q );


/**
 *	\brief
 * 	This function returns the lowest number of free elements ever present 
 * 	in the pool. 
 * 	This number provides valuable empirical data for proper sizing of the 
 * 	queue.
 * 	
 * 	\param q		pointer to previously created queue.
 *
 * 	\return
 * 	Lowest number of free elements ever present in the queue.
 */

RKH_RQNE_T rkh_rqueue_get_lwm( RKHRQ_T *q );


/*
 * 	\brief
 *	Get and remove an element from a queue.
 *
 * 	\param q		pointer to previously created queue from which the 
 * 					elements are received.
 * 	\param pe		pointer to the buffer into which the received item will be 
 * 					copied.
 *
 * 	\return
 * 	RKH_RQ_OK if an element was successfully removed from the queue, otherwise 
 * 	error code.
 */

HUInt rkh_rqueue_get( RKHRQ_T *q, void *pe );


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

void rkh_rqueue_put_fifo( RKHRQ_T *q, const void *pe );


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

void rkh_rqueue_put_lifo( RKHRQ_T *q, const void *pe );


/**
 * 	\brief
 *	Depletes a queue. 
 *
 *	Empties the contents of the queue and eliminates all stored elements.
 *		
 * 	\param q		pointer to previously created queue.
 */

void queue_deplete( RKHRQ_T *q );


/**
 * 	\brief
 *	Read an element from a queue without remove it.
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

HUInt rkh_rqueue_read( RKHRQ_T *q, void *pe ); 


/**
 * 	\brief
 * 	Retrieves performance information for a particular queue. 
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
 * 	RKH_EN_RQUEUE_GET_INFO.
 *
 * 	\param q		pointer to previously created queue.
 * 	\param pqi		pointer to the buffer into which the performance 
 * 					information will be copied by reference.
 */

void rkh_rqueue_get_info( RKHRQ_T *q, RKH_RQI_T *pqi );


/**
 * 	\brief
 * 	Clear performance information for a particular queue.
 *
 * 	\note
 * 	This function is optional, thus it could be eliminated in compile-time 
 * 	with RKH_EN_RQUEUE_GET_INFO.
 *
 * 	\param q		pointer to previously created queue.
 */

void rkh_rqueue_clear_info( RKHRQ_T *q );


#endif
