/*
 * 	internal.h
 *
 *	Here are defined INTERNAL macros and functions to RKSYS and the user 
 *	application should not call.
 */


#ifndef __INTERNAL_H__
#define __INTERNAL_H__


#include "mytypes.h"
#include "rksys.h"
#include "event.h"


/*
 * 	At any time each task exists in one of a small number of states.
 *
 * 	RKSYS_TASK_BLOCKED:	the task is waiting for events. The task is made 
 * 						ready when the event ocurrs. The ocurrence of an 
 * 						event can be signaling by either another task or 
 * 						ISR. The ISR can make one or more tasks ready to 
 * 						run by signaling one or more events. When all tasks 
 * 						are	either waiting for events RKSYS executes the idle 
 * 						task.
 *
 * 	RKSYS_TASK_READY: 	the task is ready to receive events from system 
 * 						and has	at least one pending event to dispatch.
 *
 * 	RKSYS_TASK_SUSPEND:	the task cannot receives events.
 *
 *	RKSYS_TASK_ZOMBIE: 	corresponds to a task that resides in program 
 *						space but has not been made available to RKSYS. 
 *						A task is made available by calling 'task_create'
 *						macro.
 */

enum
{
	RKSYS_TASK_BLOCKED,	
	RKSYS_TASK_READY, 
	RKSYS_TASK_SUSPEND, 
	RKSYS_TASK_ZOMBIE,

	RKSYS_TASK_NUM_STATES
};


/*
 * 	task_set_pty:
 *
 * 	This macro assigns the priority to a task. A unique priority MUST 
 * 	be assigned to each task and the lower the number, the higher the 
 * 	priority.
 *
 * 	Arguments:
 *
 * 	'pty':	priority number.
 */

#define task_set_pty( pty )			&ready_list[ pty + 1 ]


/*
 *	is_rtor_events:
 *
 *	This macro checks if task is ready to receive events.
 *
 *	Arguments:
 *
 *	'ts': 	task state.
 *
 *	Returns:
 *
 * 	'1' (TRUE) if task is ready to receive events, otherwise '0' (FALSE).
 */

#define is_rtor_events( ts )		( ( (ts) & 0x02 ) == 0 )


/* 	Used to verify the end of the queue list */

#define EMPTY_QUEUE_SLOT		RKSYS_QUEUE_NUM_QUEUES


#if RKSYS_TASK_NUM_TASKS > 0 && RKSYS_TASK_NUM_TASKS <= 16
#define RKSYS_TASK_MAX_TASKS        4
#else
#define RKSYS_TASK_MAX_TASKS        5
#endif

#if RKSYS_TASK_NUM_PTY_LEVEL > 0 && RKSYS_TASK_NUM_PTY_LEVEL <= 16
#define RKSYS_TASK_MAX_PTY        	4
#else
#define RKSYS_TASK_MAX_PTY        	5
#endif

#if RKSYS_EFLAG_NUM_REGS <= 8
#define RKSYS_TASK_MAX_EFD        	3
#else
#define RKSYS_TASK_MAX_EFD        	4
#endif

#if RKSYS_MUTEX_NUM_MUTEX <= 8
#define RKSYS_TASK_MAX_MUTEX        3
#else
#define RKSYS_TASK_MAX_MUTEX        4
#endif


/* Defines the size of runtime tick counter 8, 16 or 32-bits */

#if RKSYS_SO_RUNTIME_COUNTER == 8
typedef uchar RTCOUNTER_T;
#elif RKSYS_SO_RUNTIME_COUNTER == 16
typedef ushort RTCOUNTER_T;
#elif RKSYS_SO_RUNTIME_COUNTER == 32
typedef ulong RTCOUNTER_T;
#else
typedef uchar RTCOUNTER_T;
#endif


/*
 * 	Defines the size of tick counter 8, 16 or 32-bits. 
 * 	Time is measured in 'ticks' - which is the number
 * 	of times the tick interrupt has executed since the 
 * 	kernel was started. Using a 16-bit tick type will 
 * 	greatly improve performance on 8 and 16-bit architectures,
 * 	but limits the maximum specifiable time period to 65535 
 * 	"ticks".
 */

#if RKSYS_SIZEOF_TICK_COUNTER == 8
typedef uchar RKTICK_T;
#elif RKSYS_SIZEOF_TICK_COUNTER == 16
typedef ushort RKTICK_T;
#elif RKSYS_SIZEOF_TICK_COUNTER == 32
typedef ulong RKTICK_T;
#else
typedef uchar RKTICK_T;
#endif


typedef MUInt TD_T;


/*	
 *	Pointer to call-back entry function of a task. The 'pmsg' parameter is 
 *	a pointer to arrived event information.
 */

typedef void ( *RCBF_T )( SCHDR_MSG_T *pmsg );


/*	Pointer to task initializing function */

typedef void ( *TINIT_T )( void );


/*	
 *	Called by RKSYS whenever a task is killed. This call-back function 
 *	resides in task application space. If a task that needs to be killed
 *	has resources that it has allocated, the task cannot be deleted 
 *	otherwise these resources would not be freed. Therefore, the task to 
 *	be killed must be release any owned resources.
 */

typedef void ( *TKREQ_T )( void );


/*	
 *	Task control block. It's a data structure used by RKSYS to maintain
 *	the state of a task and pointer to fixed control block (FTCB). 
 *	This structure resides in RAM because its fields are dinamically 
 *	updated by RKSYS. The FTCB resides in ROM to reduce the size of RAM 
 *	data. The key parameters of a task are allocated into FTCB structure,
 *	therefore cannot be modified in runtime.
 */

typedef struct task_t
{
	const struct fixed_task_t *pftask;	/* pointer to FTCB */
	unsigned task_state: 2;				/* current task state */
	unsigned efd:RKSYS_TASK_MAX_EFD;	/* assigned event flag register 
										 * descriptor 
										 */
	unsigned mtxd:RKSYS_TASK_MAX_MUTEX;	/* assigned mutex descriptor */
#if RKSYS_TASK_RUNTIME_STATS == 1
	RTCOUNTER_T totexec_time;			/* total execution time */
	uchar exec_counter;					/* how many times a task has 
										 * executed 
										 */
#endif
} TASK_T;


/* 	Fixed task control block */

typedef struct fixed_task_t
{
	RCBF_T prcbf;						/* pointer to task function */
	const MUInt *pqlist;				/* pointer to event queues list */
	TINIT_T ptinit;						/* pointer to task initializing 
										 * function 
										 */
	unsigned pty:RKSYS_TASK_MAX_PTY;	/* task priority */
	struct rl_node_t *pty_node;			/* ready list node */
	MUInt quantum;						/* task quantum */
	unsigned id:RKSYS_TASK_MAX_TASKS;	/* task id */
	char *ns;							/* task name string */
	TKREQ_T pk;							/* pointer to task kill function */
} FIXED_TASK_T;


/* 	
 *  Each task is assigned a unique priority level between 0 and 
 *  RKSYS_TASK_NUM_PTY_LEVEL which are specified in 'rksys.h' file.
 *  Note that RKSYS_TASK_NUM_TASKS and RKSYS_TASK_NUM_PTY_LEVEL 
 *  are unrelated.
 *
 *  Each task that is ready to run is placed in the ready list sorted by
 *  ascending order according to task priority value. Therefore, the first
 *  task in the ready list is the higher priority task ready to run.
 */

typedef struct rl_node_t
{
	uchar pty;				/* priority value. It's used to sort the ready 
							 * list 
							 */
	TASK_T *pt;				/* pointer to the TCB that contains the list node.
							 * There is therefore a two way link between the 
							 * TCB and the list node
							 */
	struct rl_node_t *next;	/* pointer to the next node (TCB) in the 
							 * ready list 
							 */
} RL_NODE_T;


/*
 *	task_set_task_ready:
 *
 * 	This function is called by other RKSYS services and is used to ready a 
 * 	task that was waiting for an event to occur. The signaling task is 
 * 	placed in the ready list according to its priority level. 
 *
 * 	Note:
 *
 * 	It's INTERNAL to RKSYS and the user application should not call it.
 *
 * 	Arguments:
 *
 * 	'pt': 		pointer to task. Represents a previously created task.
 *
 *	Returns:
 *
 * 	'0' (TRUE) if task was successfully ready to receive events, otherwise 
 * 	'1' (FALSE).
 */

uchar task_set_task_ready( TASK_T *pt );


/*
 *	task_kill_suspend:
 *
 * 	See 'task_resume' and 'task_kill' macro declaration for more information.
 *
 * 	Note:
 *
 * 	This function is INTERNAL to RKSYS and the user application should 
 * 	not call it. It's indirectly called by macros 'task_suspend' and 
 * 	'task_kill'.
 *
 * 	Arguments:
 *
 * 	'pt': 		pointer to task. Represents a previously created task.
 * 	'tstate': 	task state.
 *
 *	Returns:
 *
 * 	'0' (TRUE) if operation was succesfully done, otherwise 
 * 	'1' (FALSE).
 */

uchar task_kill_suspend( TASK_T *pt, MUInt tstate );


/*
 *	task_init:
 *
 *	Initialize a previously created task. Assigns a fixed task control 
 *	block and initial task state to a desired TCB.
 *
 * 	Note:
 *
 * 	This function is INTERNAL to RKSYS and the user application should 
 * 	not call it. It's indirectly called by 'task_create' macro.
 *
 * 	Arguments:
 *
 * 	'pt': 		pointer to task control block. Represents a previously 
 * 				created task structure by means 'create_tcb' macro.
 * 	'pft': 		pointer to fixed task control block that is in ROM. Use the
 * 				'task_take_tcb' macro to retrieve this pointer.
 * 	'ts': 		initial task state. Generally, a task is initialized
 * 				as blocked task.
 */

void task_init( TASK_T *pt, const FIXED_TASK_T *pft, MUInt ts );


/*	
 *	This macro sets a flag when one or more events have not yet been 
 *	dispatched. 
 *
 * 	Note:
 *
 *	It's INTERNAL to RKSYS and the user application should not call it.
 */

#define set_pend_event()		(pending_events=1)


/*
 * 	This macro is called when not exists events to dispatch. 
 *
 * 	Note:
 *
 * 	It's INTERNAL to RKSYS and the user application should not call it.
 */

#define reset_pend_event()		(pending_events=0)


/*	
 *	When is set one or more events must be dispatched. 
 *
 * 	Note:
 *
 *	It's INTERNAL to RKSYS and the user application should not call it.
 */

extern uchar pending_events;


/*
 * 	ready_list_find:
 *
 * 	Find a TCB into the ready list.
 *
 * 	Note:
 *
 * 	This function is INTERNAL to RKSYS and the user application should not 
 * 	call it.
 *
 * 	Arguments:
 *
 * 	'pt':	the TCB to find.
 *
 * 	Returns:
 * 	
 * 	'1' (TRUE) if TCB currently into the ready list, otherwise '0' (FALSE).
 */

uchar ready_list_find( uchar task_pty );


/*
 * 	Insert a TCB into the ready list.  The TCB will be inserted into the list 
 * 	in a position determined by its priority (ascending order). The TCB has a
 *	pointer to corresponding node of ready list, so effectively creates a 
 *	two way link between the task and its ready list node. Thus only the 
 * 	list node need be passed into the function.
 *
 * 	Note:
 *
 * 	This function is INTERNAL to RKSYS and the user application should not 
 * 	call it.
 *	
 *	Arguments:
 *
 * 	'pn': the ready list node linked to the task.
 */

void ready_list_insert( RL_NODE_T *pn );


/*
 * 	Remove an TCB from the ready list.  The TCB has a pointer to the 
 * 	corresponding node of ready list that it is in, so only the 
 * 	task priority need be passed into the function.
 *
 * 	Note:
 *
 * 	This function is INTERNAL to RKSYS and the user application should not 
 * 	call it.
 *
 *	Arguments:
 *
 * 	'task_pty': the priority of TCB to be removed. 
 */

void ready_list_remove( uchar task_pty );


/*
 * 	rkpend_event:
 *
 * 	This function is INTERNAL to RKSYS and the user application should not 
 * 	call it.
 */

void rkpend_event( uchar set );


#endif
