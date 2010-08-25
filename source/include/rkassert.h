/*
 * 	rkassert.h
 * 
 * 	The 'rkassert' macro is used by RKSYS to check expressions that ought 
 * 	to be true as long as the program is running correctly. An assert 
 * 	should never have a side effect. If the expression evaluates to 0, the 
 * 	macro 'rk_assert' will be called, typically halting the program in some 
 * 	way. The 'rk_assert' macro should store or report the error code 
 * 	('event' parameter). Once the 'rk_assert' macro has stored 
 *	or reported the error, it must decide on the system's next action.
 *	One option is:
 *		
 *		1.- disable general interrupt
 *		2.- stores or send detected error (could be use a trace facility)
 *		3.- trigger a software reset
 *	
 *	The policy chooses will be largely determined by the nature of product. 
 *	If the system is running with a source level debugger, place a 
 *	breakpoint within.
 */


#ifndef __RKASSERT_H__
#define __RKASSERT_H__


/* Unique identifiers for assertion error codes */

enum
{
	RKSYS_TASK_INIT_FAILED,
	RKSYS_TASK_STR_FAILED,
	RKSYS_TASK_RESUME_FAILED,
	RKSYS_TASK_KSUSP_FAILED,
	RKSYS_TASK_DQUEUES_FAILED,

	RKSYS_EFLAG_ASSIGN_FAILED,
	RKSYS_EFLAG_REASSIGN_FAILED,
	RKSYS_EFLAG_FREE_FAILED,
	RKSYS_EFLAG_SWT_FAILED,
	RKSYS_EFLAG_SETF_FAILED,
	RKSYS_EFLAG_GETF_FAILED,

	RKSYS_MUTEX_TAKE_FAILED,
	RKSYS_MUTEX_GIVE_FAILED,
	RKSYS_MUTEX_ULINK_FAILED,
	RKSYS_MUTEX_CREATE_FAILED,
	RKSYS_MUTEX_FREE_FAILED, 
	RKSYS_MUTEX_GWAIT_FAILED,

	RKSYS_STIMER_ASSIGN_FAILED,
	RKSYS_STIMER_REASSIGN_FAILED,
	RKSYS_STIMER_KILL_FAILED,
	RKSYS_STIMER_KICK_FAILED,

	RKSYS_QUEUE_IE_FAILED, 
	RKSYS_QUEUE_REM_FAILED, 
	RKSYS_QUEUE_INS_FAILED,
	RKSYS_QUEUE_READ_FAILED, 
	RKSYS_QUEUE_REASSIGN_FAILED,

	RKSYS_FSM_INIT_FAILED, 
	RKSYS_FSM_ENG_FAILED,
	RKSYS_FSM_SH_FAILED, 
	RKSYS_FSM_SR_FAILED, 
	RKSYS_FSM_GETINFO_FAILED,

	RKSYS_ASSERT_NUM_ERRORS
};


#endif
