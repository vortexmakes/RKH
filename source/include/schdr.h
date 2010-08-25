/*
 *	schdr.h
 *	
 *	The scheduler, also called the dispatcher, is the part of the kernel 
 *	responsible for determining which task will run next. The RKSYS is 
 *	priority based. Each task is assigned a priority based on its 
 *	importance. The priority for each task is application specific. In a 
 *	priority-based kernel, control of the CPU will always be given to the 
 *	highest priority task ready-to-run.
 */


#ifndef __SCHDR_H__
#define __SCHDR_H__


#include "mytypes.h"
#include "rksys.h"
#include "queue.h"
#include "internal.h"


#if RKSYS_SIGNAL && RKSYS_QUEUE

DECLARE_QUEUE_ARRAY( signal_queue, RKSYS_SIGNAL_QUEUE_SIZE*sizeof(uchar) );

#endif


/*
 * 	scheduler_init:
 *
 * 	Stores a pointer to idle task function. When all tasks are either waiting 
 * 	for events the scheduler executes the idle task.
 *
 * 	Arguments:
 *
 * 	'pidle_task': pointer to idle task function.
 */
 
void scheduler_init( void (*pidle_task)( void ) );


/*
 * 	scheduler:
 *
 * 	When a task is assigned to prioirity list one or more events must be 
 * 	dispatched. In this case, RKSYS always executes the highest priority task 
 * 	ready to run. The determination of which task has the highest priority 
 * 	and thus, which task will be next to run is determined by the scheduler.
 */

void scheduler( void );


#endif
