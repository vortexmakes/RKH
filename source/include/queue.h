/*
 * 	queue.h
 *
 * 	Implements a queue management service. The queue is a buffer-like 
 * 	object through which tasks and ISRs send and receive messages to 
 * 	communicate and synchornize with data. It temporarily holds 
 * 	messages from a sender until the intended receiver is ready to read 
 * 	them.
 */


#ifndef __QUEUE_H__
#define __QUEUE_H__


#include "mytypes.h"
#include "rksys.h"
#include "task.h"


/*
 *	This macro creates the queues register. Must be called from 
 *	'qdata.c' file.
 *
 *	Note:
 *
 *	See 'CREATE_QUEUE' macro declaration for more information.
 */

#define CREATE_QUEUES_REGISTER			QUEUE_T queues[]=


/*
 *	Macro that creates a new queue structure. See 'QUEUE_T' structure for
 *	more information.
 *
 * 	Arguments:
 *
 * 	'qd':	queue descriptor. This field is currently not used and has only 
 * 			been included for future expansion.
 * 	'es': 	element size. Number of bytes each element in the queue will 
 * 			require. Elements are queued by copy, not by reference, so this 
 * 			is the number of bytes that will be copied for each posted 
 * 			element. Each element on the queue must be the same size.
 * 	'ne': 	the maximum number of elements that the queue can contain.
 * 	'pa': 	pointer to elements array. Each element on the queue is stored 
 * 			into storage area.
 *	'td': 	task descriptor that receives every element previously stored on 
 *			the queue. Thus, just one task can waiting for queued elements in 
 *			a particular queue, however other tasks or ISRs can insert item 
 *			to it.
 *	's':	indicates whether the queue is schedulable 
 *			(RKSYS_QUEUE_SCHEDULABLE) or not (RKSYS_QUEUE_NO_SCHEDULABLE). 
 */

#define CREATE_QUEUE( qd, es, ne, pa, td, s ) 						\
					 												\
						{es,ne,0,(uchar*)pa,(uchar*)pa,(uchar*)pa,	\
						(uchar*)(pa+es*ne),&tasks[td],s}


/*
 * 	This macro creates a storage area for a particular created queue.
 *
 * 	Arguments:
 * 		
 * 	'n':	name of storage area that stores elements in a created queue.
 * 	's': 	size of storage area in bytes of a previously created queue. The 
 * 			amount of required memory is calculated as number of elements 
 * 			multiplied by size of element.
 */

#define CREATE_QUEUE_ARRAY( n, s )			uchar n[s]


/*
 * 	This macro declares a previously created storage area for a particular 
 * 	created queue to be used as a global object.
 *
 * 	Arguments:
 * 		
 * 	'n': 	name of array that stores elements in a created queue.
 * 	's': 	size of storage area in bytes of a previously created queue. The 
 * 			amount of required memory is calculated as number of elements 
 * 			multiplied by size of element.
 */

#define DECLARE_QUEUE_ARRAY( n, s )			extern uchar n[s]


/*	Return codes */

enum
{
	QUEUE_OK, QUEUE_EMPTY, QUEUE_FULL
};


typedef MUInt QD_T;


/*	
 *	This data type defines the maximum number of elements that any queue 
 *	can contain.
 */

typedef uchar NUM_ELEM_QUEUE_T;


/*
 * 	Defines the data structure into which the performance information for
 * 	queues is stored.
 */

typedef struct
{
	ushort inserts;				/*	number of insert requests */
	ushort removes;				/*	number of remove requests */
	ushort empty;				/*	number of queue empty retrieves */
	ushort full;				/*	number of queue full retrieves */
} QUEUE_INFO_T;


typedef struct
{
	unsigned elem_size:7;		/* 	element size in bytes */
	NUM_ELEM_QUEUE_T num_elems;	/* 	number of elements */
	NUM_ELEM_QUEUE_T qty;		/* 	number of elements currently in the 
								 *	queue 
								 */
	uchar *pout;				/* 	points to the free next place in the 
								 *	storage area 
								 */
	uchar *pin;					/* 	points to the next place of queued item */
	uchar *parray;				/* 	points to beginning of the queue storage 
								 *	area 
								 */
	uchar *ptail;				/* 	points to the end of the queue storage 
								 *	area 
								 */
	struct task_t *task;		/* 	points to task that receives every element 
								 *	previously stored on the queue
								 */
	unsigned sched:1;			/* indicates whether the queue is schedulable 
								 * (RKSYS_QUEUE_SCHEDULABLE) or not 
								 * (RKSYS_QUEUE_NO_SCHEDULABLE) 
								 */
#if RKSYS_QUEUE_GET_INFO
	QUEUE_INFO_T qinfo;			/* performance information */
#endif
} QUEUE_T;


/*	Maintains the allocated queue structures */

extern QUEUE_T queues[ RKSYS_QUEUE_NUM_QUEUES ];


/*
 * 	queue_is_empty:
 *
 * 	Returns the number of elements currently in the queue.
 *
 * 	Arguments:
 *
 * 	'qd': queue descriptor.
 */

NUM_ELEM_QUEUE_T queue_is_empty( QD_T qd );


/*
 * 	queue_remove:
 *
 * 	Removes an element from a queue. The element is received by copy so a 
 * 	buffer of adequate size must be provided. The number of bytes copied 
 * 	into the buffer was defined when the queue was created.
 *
 * 	Arguments:
 *
 * 	'qd':		queue descriptor.
 * 	'pelem': 	pointer to the buffer into which the received item will be 
 * 				copied.
 *
 * 	Returns:
 *
 * 	QUEUE_OK if an element was successfully removed from the 
 * 	queue, otherwise error code.
 */

MUInt queue_remove( QD_T qd, void *pelem );


/*
 * 	queue_insert:
 *
 *	Inserts an element on a queue. The element is queued by copy, not 
 *	by reference.
 *
 * 	Arguments:
 *
 * 	'qd': 		queue descriptor.
 * 	'pelem': 	pointer to the element that is to be placed on the queue.  
 *				The size of the elements the queue will hold was defined when 
 *				the queue was created.
 *
 * 	Returns:
 *
 * 	QUEUE_OK if the element was successfully inserted, 
 *	otherwise error code.
 */

MUInt queue_insert( QD_T qd, const void *pelem );


/*
 * 	queue_deplete:
 *
 *	Depletes a queue. 
 *		
 *	Arguments:
 *
 * 	'qd': 		queue descriptor.
 */

void queue_deplete( QD_T qd );


/*
 * 	queue_read:
 *
 *	Read an element from a queue without remove it. The element is 
 *	received by copy so a buffer of adequate size must be provided. 
 *	The number of bytes copied into the buffer was defined when the 
 *	queue was created.
 *
 * 	Arguments:
 *
 * 	'qd': 		queue descriptor.
 * 	'pelem':	pointer to the buffer into which the received item will be 
 * 				copied.
 *
 * 	Returns:
 *
 * 	QUEUE_OK if an element was successfully readed from the 
 * 	queue, otherwise error code.
 */

MUInt queue_read( QD_T qd, void *pelem );


/*
 * 	queue_assign_task:
 *
 * 	Assigns a new waiting task to a previously created queue that which 
 * 	receives every posted element on it. Thus, just one task can waiting 
 * 	for queued elements in a particular queue, however other tasks or ISRs 
 * 	can insert item to it.
 *
 * 	Arguments:
 *
 * 	'qd': 		previously defined queue descriptor.
 *	'td': 		new task descriptor that receives every element previously 
 *				stored on the queue.
 *	'es':		new element size in bytes.
 * 	'ne': 		new maximum number of elements that the queue can contain.
 */

void queue_reassign( QD_T qd, MUInt td, uchar es, NUM_ELEM_QUEUE_T ne );


/*
 * 	queue_clear_info:
 *
 * 	Clear performance information for a particular queue.
 *
 * 	Information is available during run-time for each of the RKSYS
 * 	resources. This information can be useful in determining whether
 * 	the application is performing properly, as well as helping to
 * 	optimize the application.
 *
 * 	'qd':		queue descriptor.
 */

void queue_clear_info( QD_T qd );


/*
 * 	queue_get_info:
 *
 * 	Retrieves performance information for a particular queue.
 *
 * 	'qd':		queue descriptor.
 * 	'pqi':		pointer to the buffer into which the performance information
 * 				will be copied by reference.
 */

void queue_get_info( QD_T qd, QUEUE_INFO_T *pqi );


#endif
