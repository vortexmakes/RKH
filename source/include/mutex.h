/*
 * 	mutex.h
 *
 */


#ifndef __MUTEX_H__
#define __MUTEX_H__


#include "task.h"
#include "mytypes.h"


typedef uchar MTXD_T;


/*	Return codes */

enum
{
	MUTEX_OK, MUTEX_NOT_AVAILABLE, MUTEX_ERROR
};


#define RKSYS_MUTEX_EMPTY			RKSYS_MUTEX_NUM_MUTEX
#define RKSYS_MUTEX_NO_ROOM			RKSYS_MUTEX_EMPTY


/*
 * 	Defines the data structure into which the performance information for
 * 	mutexes is stored.
 */

typedef struct
{
	ushort takes;					/*	number of take requests */
	ushort gives;					/*	number of give requests */
	ushort unlinks;					/*	number of unlink requests */
} MUTEX_INFO_T;


/*
 * 	mutex_take:
 *
 * 	Enables a task to attempt to obtain exclusive ownership of a mutex.
 * 	If no task owns that mutex, then that task acquires ownership of the 
 * 	mutex. If the calling task already owns the mutex, then ignores this
 * 	operation. If another task already owns the mutex, the calling task
 * 	is placed on task-waiting list and waits to receive the 'available mutex'
 * 	event from kernel.
 *
 *	The calling task waiting for an unavailable mutex are placed in the
 *	task-waiting list in highest priority first order.
 *
 * 	Arguments:
 *
 * 	'mtxd':		mutex descriptor.
 * 	'pt':		pointer to calling task.
 *
 * 	Returns:
 *
 *	MUTEX_OK:				successful mutex take operation.
 *	MUTEX_NOT_AVAILABLE:	another task already owns the mutex. 
 *	MUTEX_ERROR:			invalid mutex id or the mutex was aborted or 
 *							deleted by another process.
 */

uchar mutex_take( MTXD_T mtxd, TASK_T *pt );


/*
 * 	mutex_give:
 *
 * 	Enables a task to release ownership of a mutex. Assuming that the task 
 * 	owns the mutex, the mutex becomes available, so the kernel takes the 
 * 	highest priority task in the task-waiting list and moves it to the ready 
 * 	state.
 *
 * 	Arguments:
 *
 * 	'pt':		pointer to calling task.
 */

void mutex_give( TASK_T *pt );


/*
 * 	mutex_unlink:
 *
 * 	Removes the linked mutex to a task. Assuming that calling task required 
 * 	a mutex, if no task owns that mutex or another task already owns the 
 * 	mutex, then that task is deleted from task-waiting list. If the calling 
 * 	task owns the mutex, then the action taken is the same as releasing it.
 *
 * 	Arguments:
 *
 * 	'pt':		pointer to calling task.
 */

void mutex_unlink( TASK_T *pt );


/*
 * 	mutex_create:
 *
 * 	Assigns a mutex. This operation allocates a mutex control block. 
 * 	In order to use a mutex must be first created a mutex control block.
 *
 * 	Returns:
 *
 *	The number of mutex descriptor identifying the newly created mutex.
 */

MTXD_T mutex_create( void );


/*
 * 	mutex_free:
 *
 * 	Frees a mutex. This operation frees a previously created mutex, freeing 
 * 	the memory occupied by the mutex control block. When a mutex is deleted, 
 * 	all tasks in the task-waiting list are deleted.
 * 	Deleting a mutex is not the same as releasing it. When a mutex is deleted
 * 	while it's in use might result in serious problem if the mutex is 
 * 	protected a shared resource or a critical section.
 *
 * 	Arguments:
 *
 * 	'mtxd': 	mutex descriptor identifying a previously created mutex.
 */

void mutex_free( MTXD_T mtxd );


/*
 * 	mutex_check:
 *
 *	Checks mutex availability. Returns a boolean value from this checking. 
 *
 *	Note:
 *
 *	This function is INTERNAL to RKSYS and the user application should not 
 *	call it.
 *
 * 	Arguments:
 *
 * 	'pt':		pointer to current task.
 *
 * 	Returns:
 *
 * 	A true value if current task is waiting for available mutex, otherwise
 * 	false value.
 */

uchar mutex_check( TASK_T *pt );


/*
 * 	mutex_clear_info:
 *
 * 	Clear performance information for a particular mutex.
 *
 * 	Information is available during run-time for each of the RKSYS
 * 	resources. This information can be useful in determining whether
 * 	the application is performing properly, as well as helping to
 * 	optimize the application.
 *
 * 	'mtxd':		mutex descriptor.
 */

void mutex_clear_info( MTXD_T mtxd );


/*
 * 	mutex_get_info:
 *
 * 	Retrieves performance information for a particular mutex.
 *
 * 	'mtxd':		mutex descriptor.
 * 	'pmi':		pointer to the buffer into which the performance information
 * 				will be copied by reference.
 */

void mutex_get_info( MTXD_T mtxd, MUTEX_INFO_T *pmi );


#endif
