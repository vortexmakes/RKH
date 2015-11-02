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
 *  \file       rkhrq.h
 *  \ingroup    que
 *
 *  \brief      Platform - independent interface for supporting queue services.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24    LeFr    v2.4.05     Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr        Leandro Francucci (francuccilea@gmail.com)
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */

#ifndef __RKHRQ_H__
#define __RKHRQ_H__

/* ----------------------------- Include files ----------------------------- */

#include "rkhcfg.h"
#include "rkhtype.h"

/* ---------------------- External C language linkage ---------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */

/**
 *  \brief
 *  This macro query the queue.
 *
 *  \param q		pointer to previously created queue.
 *
 *  \return
 *  '1' (RKH_TRUE) if queue is empty, otherwise '0' (RKH_FALSE).
 */
#define RKH_RQ_IS_EMPTY(q) \
    (rbool_t)(rkh_rq_get_num((RKH_RQ_T *)(q)) == 0)

/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */

/**
 *  \brief
 *  This data type defines the maximum number of elements that any queue
 *	can contain.
 *
 *	The valid values [in bits] are 8, 16 or 32. Default is 8. This type is
 *	configurable via the preprocessor switch RKH_CFG_RQ_SIZEOF_NELEM.
 */
#if RKH_CFG_RQ_SIZEOF_NELEM == 8
typedef rui8_t RKH_RQNE_T;
#elif RKH_CFG_RQ_SIZEOF_NELEM == 16
typedef rui16_t RKH_RQNE_T;
#elif RKH_CFG_RQ_SIZEOF_NELEM == 32
typedef rui32_t RKH_RQNE_T;
#else
typedef rui8_t RKH_RQNE_T;
#endif

/**
 *  \brief
 *  Return codes from queue operations.
 */
typedef enum
{
    RKH_RQ_OK, RKH_RQ_EMPTY, RKH_RQ_FULL
} RKH_RQCODE_T;

/**
 *  \brief
 *  Defines the data structure into which the performance information for
 *  queues is stored.
 *
 *	The application must allocate an RKH_RQI_T data structure used to
 *	receive information. The performance information is available during
 *	run-time for each of the RKH services. This can be useful in determining
 *	whether the application is performing properly, as well as helping to
 *	optimize the application.
 */
typedef struct RKH_QINFO_T
{
    rui16_t nputs;      /*	# of put requests */
    rui16_t ngets;      /*	# of get requests */
    rui16_t nreads;     /*	# of queue read requests */
    rui16_t nempty;     /*	# of queue empty retrieves */
    rui16_t nfull;      /*	# of queue full retrieves */
} RKH_RQI_T;

/**
 *  \brief
 *  Defines the data structure used to maintain information about the queue.
 *
 *  The queue is a buffer-like object through which state machine
 *  applications (SMA) and ISRs send and receive messages to communicate and
 *  synchornize with data. It temporarily holds pointer to messages from a
 *  sender until the intended receiver is ready to read them.
 *
 *  The number of messages a queue can hold depends on its message size
 *  (pointer size) and the size of the memory area supplied during creation.
 *  To calculate the total message capacity of the queue, divide the number
 *  of bytes in each message into the total number of bytes in the supplied
 *
 *  The memory area for buffering messages is specified during queue
 *  creation. It can be located anywhere in the target's address space.
 *  This is an important feature because it gives the application
 *  considerable flexibility.
 *
 *  \note
 *  RKH prohibits an application from explicitly modifying the RKH_RQ_T
 *  structure. The RKH's queue structures can be located anywhere in memory,
 *  but it is most common to make it a global structure by defining it
 *  outside the scope of any function.
 *  An RKH queue is created when an queue (copy by reference) is declared
 *  with the RKH_RQ_T data type. The following listing declares "gsmque"
 *  timer:
 *
 *  \code
 *  RKH_RQ_T gsmque;
 *  \endcode
 */
typedef struct RKH_RQ_T
{
    /**
     *  \brief
     *  Number of elements.
     */
    RKH_RQNE_T nelems;

    /**
     *  \brief
     *  Number of elements currently in the queue.
     */
    RKH_RQNE_T qty;

    /**
     *  \brief
     *	Points to the free next place in the storage area.
     */
    void **pout;

    /**
     *  \brief
     *  Points to the next place of queued item.
     */
    void **pin;

    /**
     *  \brief
     *  Points to beginning of the queue storage area.
     */
    const void **pstart;

    /**
     *  \brief
     *  Points to the end of the queue storage area.
     */
    void **pend;

    /**
     *  \brief
     *  Points to the associated SMA (a.k.a Active Object) that receives the
     *  enqueued events.
     *
     *  \note
     *  If \a sma is set to NULL they never block.
     */
    const struct RKH_SMA_T *sma;

    /**
     *  \brief
     *  Minimum number of free elements ever in this queue.
     *	The nmin low-watermark provides valuable empirical data for
     *	proper sizing of the queue.
     */
#if RKH_CFG_RQ_GET_LWMARK_EN == RKH_ENABLED
    RKH_RQNE_T nmin;
#endif

    /**
     *  \brief
     *  Performance information. This member is optional, thus it could be
     *  eliminated in compile-time with RKH_CFG_RQ_GET_INFO_EN.
     */
#if RKH_CFG_RQ_GET_INFO_EN == RKH_ENABLED
    RKH_RQI_T rqi;
#endif
} RKH_RQ_T;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */

/**
 * \brief
 *	Initializes the previously allocated queue data structure RKH_RQ_T.
 *
 *  A queue is declared with the RKH_RQ_T data type and is defined with the
 *  rkh_rq_init() service. The total number of messages is calculated from
 *  the specified message size (pointer size) and the total number of bytes
 *  in the queue. Note that if the total number of bytes specified in the
 *  queue's memory area is not evenly divisible by the specified message
 *  size, the remaining bytes in the memory area are not used.
 *
 *	\sa
 *	RKH_RQ_T structure for more information.
 *
 *  \param q		pointer to previously allocated queue structure.
 *  \param sstart	storage start. Pointer to an array of pointers that holds
 *                  the elements. This array must be declared as an array of
 *                  void pointers.
 *  \param ssize	storage size [in the units of void pointers].
 *  \param sma		pointer to associated SMA that receives the enqueued
 *                  events. If \a sma is set to NULL they never block. When
 *                  using a queue to store deferred events the \a sma
 *                  parameter must be set to NULL.
 */
void rkh_rq_init(RKH_RQ_T *q, const void * *sstart, RKH_RQNE_T ssize,
                 const struct RKH_SMA_T *sma);

/**
 *  \brief
 *  This function query the queue.
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_RQ_IS_FULL_EN.
 *
 *  \param q		pointer to previously created queue.
 *
 *  \return
 *  '1' (RKH_TRUE) if queue is full, otherwise '0' (RKH_FALSE).
 */
rbool_t rkh_rq_is_full(RKH_RQ_T *q);

/**
 *  \brief
 *  Returns the number of elements currently in the queue.
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_RQ_GET_NELEMS_EN.
 *
 *  \param q		pointer to previously created queue.
 */
RKH_RQNE_T rkh_rq_get_num(RKH_RQ_T *q);

/**
 *	\brief
 *  This function returns the lowest number of free elements ever present
 *  in the pool.
 *  This number provides valuable empirical data for proper sizing of the
 *  queue.
 *
 *  \param q		pointer to previously created queue.
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_RQ_GET_LWMARK_EN.
 *
 *  \return
 *  Lowest number of free elements ever present in the queue.
 */
RKH_RQNE_T rkh_rq_get_lwm(RKH_RQ_T *q);

/**
 *  \brief
 *	Get and remove an element from a queue.
 *
 *  \param q		pointer to previously created queue from which the
 *                  elements are received.
 */
void *rkh_rq_get(RKH_RQ_T *q);

/**
 *  \brief
 *	Puts an element on a queue in a FIFO manner. The element is queued by
 *	reference, not by copy.
 *
 *  \note
 *  This function must be invoked within a critical section.
 *  \note
 *  The function raises an assertion if the queue becomes full and cannot
 *  accept the element.
 *
 *  \param q		pointer to previously created queue into which the element
 *                  is deposited.
 *  \param pe		pointer-sized variable and is application specific.
 */
void rkh_rq_put_fifo(RKH_RQ_T *q, const void *pe);

/**
 *  \brief
 *	Puts an element on a queue in a LIFO manner. The element is queued by
 *	reference, not by copy.
 *
 *  \note
 *  This function must be invoked within a critical section.
 *  \note
 *  The function raises an assertion if the queue becomes full and cannot
 *  accept the element.
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_RQ_PUT_LIFO_EN.
 *
 *  \param q		pointer to previously created queue into which the element
 *                  is deposited.
 *  \param pe		pointer-sized variable and is application specific.
 */
void rkh_rq_put_lifo(RKH_RQ_T *q, const void *pe);

/**
 *  \brief
 *	Depletes a queue. Empties the contents of the queue and eliminates all
 *	stored elements.
 *
 *	\note
 *	This function should be used with great care because, when to flush the
 *	queue, the references are LOOSE to what the queue entries are pointing
 *	to and thus, could cause 'memory leaks'. In other words, the data
 *	pointing to that's being referenced by the queue entries should, most
 *	likely, need to be deallocated. To flush a queue that contains entries,
 *	is much safer instead repeateadly use rkh_rq_get().
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_RQ_DEPLETE_EN.
 *
 *  \param q		pointer to previously created queue.
 */
void rkh_rq_deplete(RKH_RQ_T *q);

/**
 *  \brief
 *	Read an element from a queue without remove it.
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_RQ_READ_EN.
 *
 *  \param q		pointer to previously created queue from which the
 *                  elements are received.
 *  \param pe		pointer to the buffer into which the received item will be
 *                  copied.
 *
 *  \return
 *  RKH_RQ_OK if an element was successfully readed from the queue, otherwise
 *  error code.
 */
ruint rkh_rq_read(RKH_RQ_T *q, void *pe);

/**
 *  \brief
 *  Retrieves performance information for a particular queue.
 *
 *	The user application must allocate an RKH_RQI_T data structure used to
 *	receive data. The performance information is available during run-time
 *	for each of the RKH services. This can be useful in determining whether
 *	the application is performing properly, as well as helping to optimize the
 *	application.
 *	This information provides a "snapshot" a particular instant in time, i.e.,
 *	when the service is invoked.
 *
 *  \note
 *  See RKH_RQI_T structure for more information. This function is
 *  optional, thus it could be eliminated in compile-time with
 *  RKH_CFG_RQ_GET_INFO_EN.
 *
 *  \param q		pointer to previously created queue.
 *  \param pqi		pointer to the buffer into which the performance
 *                  information will be copied.
 */
void rkh_rq_get_info(RKH_RQ_T *q, RKH_RQI_T *pqi);

/**
 *  \brief
 *  Clear performance information for a particular queue.
 *
 *  \note
 *  This function is optional, thus it could be eliminated in compile-time
 *  with RKH_CFG_RQ_GET_INFO_EN.
 *
 *  \param q		pointer to previously created queue.
 */
void rkh_rq_clear_info(RKH_RQ_T *q);

/* -------------------- External C language linkage end -------------------- */

#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */

#endif

/* ------------------------------ End of file ------------------------------ */
