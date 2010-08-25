/*
 *	task.h
 */


#ifndef __TASK_H__
#define __TASK_H__


#include "mytypes.h"
#include "rksys.h"
#include "internal.h"


/*	List of system priorities */

extern RL_NODE_T ready_list[ RKSYS_TASK_NUM_PTY_LEVEL + 1 ];


/*	Maintains task's data structures */

extern TASK_T tasks[ RKSYS_TASK_NUM_TASKS ];


/* 	Used to mark the empty task slot */

#define EMPTY_TASK				RKSYS_TASK_NUM_TASKS


/*
 *	This macro creates a new task control block.
 *
 *	Note:
 *
 *	See TASK_T structure declaration for more information.
 *
 *	Arguments:
 *
 *	't':	task name. Represents a new task structure. 
 *	'pf':	pointer to the task entry function. The function prototype is
 *			defined as 'RCBF_T'.
 *	'plq':	pointer to queue list. Use a 'task_set_que_list' macro to 
 *			retrieve this pointer.
 *	'pi':	pointer to task initializing function. The function prototype is
 *			defined as 'TINIT_T'.
 *	'p':	the value of level priority at which the task should run. 
 *			The allowed levels are specified in 'rksys.h' file.
 *	'q':	task quantum. Not used.
 *	'i':	the value of task ID. The user application defines the 
 *			available ids in 'tdata.h' file.
 *	'tn':	task name. String terminated in '\0' that represents the
 *			name of task. It generally used for debugging.
 *	'pk':	pointer to hook kill function. Called by RKSYS whenever the
 *			task is killed. The function prototype is defined as 'TKREQ_T'.
 */

#define CREATE_TCB( t, pf, plq, pi, p, q, i, tn, pk )					\
				 														\
					const FIXED_TASK_T t##_fxt = 						\
							{pf,plq,pi,p,task_set_pty(p),q,i,tn,pk};	\
																		\
					TASK_T *const t = &tasks[i]


/*
 * 	This macro declares the previously created task structure to be used 
 * 	as a global object. Generally, the tasks are declared in task 
 * 	dependent header file.
 * 	
 * 	Arguments:
 *
 * 	't':	task name. Represents a previously created task structure.
 */

#define DECLARE_TASK( t )			extern const FIXED_TASK_T t##_fxt;	\
									extern TASK_T *const t


/*
 *	This macro creates a event queues list. It's a array of queue structure 
 *	referenced in a task structure.
 *
 *	Arguments:
 *
 *	't':	task name.
 */

#define CREATE_QUEUE_LIST( t )		const MUInt t##_que_list[]


/* 	Used for terminating a queue list */

#define END_QUEUE_LIST			EMPTY_QUEUE_SLOT


/*
 * 	task_take_tcb:
 *
 * 	This macro returns the fixed task control block (FTCB).
 *
 * 	Arguments:
 *
 *	't': 	task name. Represents a previously created task structure.
 */

#define task_take_tcb( t )			&t##_fxt


/*
 * 	task_take:
 *
 * 	This macro retrieves the pointer to previously created task 
 * 	control block.
 *
 * 	Arguments:
 *
 *	'td': 	task descriptor. Represents a previously created task structure.
 */

#define task_take( td )				&tasks[ td ]


/*
 * 	task_set_que_list:
 *
 * 	This macro generates the queue list name according to task name structure.
 *
 * 	Arguments:
 *
 *	't': 	task name. Represents a previously created task structure.
 */

#define task_set_que_list( t )		t##_que_list


/*
 * 	task_suspend:
 *
 * 	This macro suspend a task. An ISR cannot suspend a task.
 * 	A suspended task can only be resumed by calling the 'task_resume' 
 * 	function. A task can suspend either itself or another task.
 * 	The task is removed from the ready list and is changed its state
 * 	to indicate that the task is now suspended. Its pending events 
 * 	are deleted.
 *
 * 	Arguments:
 *
 * 	't': 	task name. Represents a previously created task structure. 
 *
 *	Returns:
 *
 * 	'0' (TRUE) if operation was succesfully done, otherwise 
 * 	'1' (FALSE).
 */

#define task_suspend( t )		task_kill_suspend( t, RKSYS_TASK_SUSPEND )


/*
 *	task_kill:
 *
 * 	This macro kills a task. Killing a task means that the task is 
 * 	returned to the dormant state and does not mean that the code for 
 * 	the task is actually deleted. The task code is simply no longer 
 * 	scheduled by RKSYS.
 * 	If the task is in the ready list, it's removed from that list.
 * 	If the task has pending events to process, that are removed.
 * 	Changes the task state to zombie state and calls the user definable 
 * 	task kill, which allows to release any owned resources.
 *	A task is made available by calling 'task_create' macro.
 * 	 	
 * 	Arguments:
 *
 * 	't': 	task name. Represents a previously created task structure. 
 *
 *	Returns:
 *
 * 	'0' (TRUE) if operation was succesfully done, otherwise 
 * 	'1' (FALSE).
 */

#define task_kill( t )			task_kill_suspend( t, RKSYS_TASK_ZOMBIE )


/*
 * 	task_create:
 *
 * 	This macro initialize a previously created task. According to
 * 	initial state the task maybe available or not. This macro must be 
 * 	called into system initializing.
 *
 * 	Arguments:
 *
 * 	't': 	task name. Represents a previously created task structure.
 * 	's':	indicates the initial task state. The following values are
 * 			allowed:
 *
 * 			RKSYS_TASK_BLOCKED: the task is ready to receive events and
 * 								process it. 
 * 			RKSYS_TASK_ZOMBIE:	the task remains in dormant mode. It can 
 * 								return to blocked state by calling 
 * 								'task_resume' function.
 */

#define task_create( t, s )		task_init( t, task_take_tcb( t ), s )


/*
 *	task_resume:
 *
 * 	Resumes a suspended task.
 *
 * 	'pt': 	pointer to task. Represents a previously created task.
 *
 *	Returns:
 *
 * 	'0' (TRUE) if operation was succesfully done, otherwise 
 * 	'1' (FALSE).
 */

uchar task_resume( TASK_T *pt );


/*
 *	task_deplete_queues:
 *
 *	Depletes each linked queue to a task.
 *
 * 	Arguments:
 *
 * 	'pt': 		pointer to task. Represents a previously created task.
 */

void task_deplete_queues( TASK_T *pt );


/*
 * 	task_identify:
 *
 * 	Retrieves the pointer to previously created task 
 * 	control block (TCB).
 *
 * 	Arguments:
 *
 *	'td': 	task descriptor. Represents a previously created task structure.
 *
 *	Returns:
 *
 *	A pointer to task control block (TCB).
 */

TASK_T *task_identify( TD_T td );


#endif
