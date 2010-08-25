/*
 * 	rksyscfg.h
 */


#ifndef __RKSYSCFG_H__
#define __RKSYSCFG_H__


#include "trace.h"


/*	Signal configurations */

#define RKSYS_SIGNAL				1			/* Enable (1) or Disable (0) code generation for system signals */
#define RKSYS_SIGNAL_NUM_SIGNALS	2			/* Number of signals */
#define RKSYS_SIGNAL_QUEUE_SIZE		4			/* Max. number of pending signals */


/*	Task configurations */

#define RKSYS_TASK_NUM_PTY_LEVEL    8			/* Number of priority levels */
#define RKSYS_TASK_NUM_TASKS        4           /* Number of tasks */
#define RKSYS_TASK_QUEUE_LIST 		1			/* Enable (1) or Disable (0) queue list for task */
#define RKSYS_TASK_RESUME			1			/* Include code for task_resume(), task_kill() and task_suspend() */
#define RKSYS_TASK_NAME_STRING		0			/* Include task name within task control block */


/*	Queue configurations */

#define RKSYS_QUEUE					1			/* Enable (1) or Disable (0) code generation for queues */
#define RKSYS_QUEUE_NUM_QUEUES		3			/* Number of queues */
#define RKSYS_QUEUE_READ			0			/* Include code for queue_read() */
#define RKSYS_QUEUE_REASSIGN		0			/* Include code for queue_reassign() */
#define RKSYS_QUEUE_SCHEDULABLE		1			/* Sets a queue as schedulable or not */
#define RKSYS_QUEUE_NO_SCHEDULABLE	0
#define RKSYS_QUEUE_GET_INFO		0			/* Enable (1) or Disable (0) code generation for retrieve performance information */


/*	Event configurations */

#define RKSYS_EVENT_NUM_TARGET		4			/* Max. number of event targets = 2^RKSYS_EVENT_NUM_TARGET */
#define RKSYS_EVENT_NUM_ID			4			/* Max. number of event ids = 2^RKSYS_EVENT_NUM_ID */


/*	Miscellaneous configurations */

#define RKSYS_PRINT_FORMAT			1			/* Enable (1) or Disable (0) code generation for formatted printing */
#define RKSYS_PRINT_FORMAT_SIZE 	128			/* Max. size in character of formatted printing */
#define RKSYS_CRITICAL_METHOD		1			/* Sets a critical section method that the system use */
#define RKSYS_MAX_NESTING_CSECT		8			/* Max. size of nesting critical section */
#define RKSYS_IDLE_TASK				0			/* Enable (1) or Disable (0) code generation for calling to idle task */
#define RKSYS_SIZEOF_TICK_COUNTER	8			/* Defines the size of tick counter in bits: 8, 16 or 32-bits */			
#define RKSYS_TICK_RATE_HZ			10			/* The frequency of the RKSYS tick interrupt */
#define RKSYS_CPU_CLOCK_HZ			24576000UL	/* The frequency in HZ at which the internal processor core will be 
												 * executing. This is needed to configure the several processor modules.
												 */
#define RKSYS_TICK_RATE_MS			((RKTICK_T)(1000/RKSYS_TICK_RATE_HZ)) /* It can be used to convert ticks to milliseconds */


/*	Statistics configurations */

#define RKSYS_TASK_RUNTIME_STATS	1			/* Enable (1) or Disable (0) run-time statistics task */
#define RKSYS_STATS_EXEC_TASKS		1			/* Enable (1) or Disable (0) execution time metrics of schedulable tasks */
#define RKSYS_RUNTIME_COUNTER		1			/* Include timer for metrics and statistics */
#define RKSYS_SO_RUNTIME_COUNTER	16			/* Defines the size of tick counter in bits: 8, 16 or 32-bits */			
#define RKSYS_STATS_TICK_HZ			192000UL	/* Define the # of overflow ocurrences per second of timer statistics */
#define RKSYS_STATS_TICK_TASK		2			/* Define the statistics task rate in unit of time [seconds] */
#define RKSYS_STATS_TOTAL_TIME		((RKSYS_STATS_TICK_HZ*RKSYS_STATS_TICK_TASK)/100)
#define RKSYS_TIME_MEASURE			1			/* Enable (1) or Disable (0) code generation to measure execution time */


/*	Software timer configurations */

#define RKSYS_TIMER		   			1			/* Enable (1) or Disable (0) code generation for timers */
#define RKSYS_TIMER_NUM_TIMERS		4			/* Number of timer control blocks */
#define RKSYS_TIMER_INIT			0			/* Include code for stimer_init() */
#define RKSYS_TIMER_KILL			1			/* Include code for stimer_kill() */
#define RKSYS_TIMER_REASSIGN		0			/* Include code for stimer_reassign() */
#define RKSYS_TIMER_SIMPLE_CB		1			/* Defines the type of callback function for elapsed timer */
#define RKSYS_TIMER_GET_INFO		0			/* Enable (1) or Disable (0) code generation for retrieve performance information */


/*	Event flag register configurations */

#define RKSYS_EFLAG 				1			/* Enable (1) or Disable (0) code generation for event flags */
#define RKSYS_EFLAG_NUM_REGS		2			/* Number of event flag control blocks */
#define RKSYS_EFLAG_NUM_FLAGS		8			/* Define event flag arrangement in groups of 8, 16 or 32 */
#define RKSYS_EFLAG_GET_FLAGS		0			/* Include code for eflag_get_flags() */
#define RKSYS_EFLAG_REASSIGN		0			/* Include code for eflag_reassign() */
#define RKSYS_EFLAG_FREE			0			/* Include code for eflag_free() */
#define RKSYS_EFLAG_GET_INFO		0			/* Enable (1) or Disable (0) code generation for retrieve performance information */


/*	Mutex configurations */

#define RKSYS_MUTEX					1			/* Enable (1) or Disable (0) code generation for mutex */
#define RKSYS_MUTEX_NUM_MUTEX		1			/* Number of mutex control block */
#define RKSYS_MUTEX_CREATE			0			/* Include code for mutex_create() */
#define RKSYS_MUTEX_FREE			0			/* Include code for mutex_free() */
#define RKSYS_MUTEX_UNLINK			1			/* Include code for mutex_unlink() */
#define RKSYS_MUTEX_GET_WAIT_TASK	0			/* Include code for mutex_get_wait_task() */
#define RKSYS_MUTEX_GET_INFO		0			/* Enable (1) or Disable (0) code generation for retrieve performance information */


/*	Finite state machine configurations */

#define RKSYS_FSM					1			/* Enable (1) or Disable (0) code generation for FSM */
#define RKSYS_NUM_FSMS				1			/* Number of finite state machines */
#define RKSYS_FSM_HISTORY			1			/* Include history states */
#define RKSYS_FSM_RECALL			1			/* Include fsm's recall */
#define RKSYS_FSM_COND				1			/* Include conditional states */
#define RKSYS_FSM_GUARD				1			/* Include guard functions */
#define RKSYS_FSM_PPRO				1			/* Include preprocessor function */
#define RKSYS_FSM_ACT_ARGS			1			/* Defines the type of output or action function */
#define RKSYS_FSM_GUARD_ARGS		0			/* Defines the type of guard function */
#define RKSYS_FSM_STATE_ID			1			/* Include state id */
#define RKSYS_FSM_MAX_COMP_TRANS	5			/* Max. number of compound transtions */
#define RKSYS_FSM_REENTRANT			0			/* Enable (1) or Disable (0) fsm engine re-entrancy */
#define RKSYS_FSM_GET_INFO			1			/* Includes get information function */


/*	Trace debug and assert configurations */

#define RKSYS_DEBUG					1			/* Enable (1) or Disable (0) debug facility */
#define RKSYS_TRACE					1			/* Enable (1) or Disable (0) trace facility */
#define RKSYS_ASSERT				0			/* Enable (1) or Disable (0) system's argument checking */

#define rk_assert( event )			rkreset()


/*	Example to use 'rk_assert' macro */

#if 0
	#define rk_assert( event )				\
	{										\
		rkdisable_interrupt();				\
		trace_event0( event, 0, 0, 0 );		\
		trace_flush();						\
		rkreset();							\
	}
#endif
	

#endif
