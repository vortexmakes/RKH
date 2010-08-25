/*
 * qdata.c
 */


#include "queue.h"
#include "event.h"
#include "rksys.h"
#include "signal.h"
#include "sigdata.h"
#include "task.h"
#include "tdata.h"


/*	Include files of software modules that uses queues */

#include "schdr.h"
#include "button.h"
#include "shell.h"
#include "log.h"


/*
 *	Register of queues. Any software module intending to use a queue
 *	must first create a queue structure into queues register. When a queue 
 *	is first created, it's assigned an associated unique descriptor, 
 *	memory buffer, a queue length, a maximum element length, and one 
 *	waiting-task. Therefore, each element of that must be defined by means 
 *	'CREATE_QUEUE' macro. The queue descriptor are defined in 'qdata.h' file.
 */

CREATE_QUEUES_REGISTER
{
#if RKSYS_SIGNAL

	CREATE_QUEUE( 
					SIGNAL_QUEUE,
					sizeof( uchar ), 
					RKSYS_SIGNAL_QUEUE_SIZE, 
					signal_queue, 
					EMPTY_TASK, 
					RKSYS_QUEUE_NO_SCHEDULABLE 
				),

#endif
	CREATE_QUEUE( 
					BUTTON_QUEUE,
					sizeof( EVT_T ), 
					BUTTON_QUEUE_SIZE, 
					button_queue,
					BUTTON, 
					RKSYS_QUEUE_SCHEDULABLE 
				),
	CREATE_QUEUE( 
					SHELL_QUEUE,
					sizeof( char ), 
					SHELL_QUEUE_SIZE, 
					shell_queue, 
					SHELL, 
					RKSYS_QUEUE_SCHEDULABLE 
				)
};
