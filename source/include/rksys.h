/*
 * 	rksys.h
 */


#ifndef __RKSYS_H__
#define __RKSYS_H__


/* Application specific configuration options */

#include "rksyscfg.h"


/* Definitions specific to the port being used */

#include "rkport.h"


/* Version of RKSYS */

#define RKSYS_VERSION			"2.55.0"


/*	Signal configurations */

#ifndef RKSYS_SIGNAL
#error  "rksyscfg.h, Missing RKSYS_SIGNAL: Enable (1) or Disable (0) code generation for system signals"
#else
	#ifndef RKSYS_SIGNAL_NUM_SIGNALS
	#error "rksyscfg.h, Missing RKSYS_SIGNAL_NUM_SIGNALS: Max. number of signals"
	#else
		#if RKSYS_SIGNAL_NUM_SIGNALS == 0 || RKSYS_SIGNAL_NUM_SIGNALS > 16
		#error  "rksyscfg.h, RKSYS_SIGNAL_NUM_SIGNALS must be > 0 and <= 16"
		#endif
	#endif

    #ifndef RKSYS_SIGNAL_QUEUE_SIZE
    #error  "rksyscfg.h,  Max. number of pending signals"
    #else
        #if RKSYS_SIGNAL_QUEUE_SIZE == 0 || RKSYS_SIGNAL_QUEUE_SIZE > 16
        #error  "rksyscfg.h, RKSYS_SIGNAL_QUEUE_SIZE must be > 0 and <= 16"
        #endif
	#endif

#endif


/*	Task configurations */

#ifndef RKSYS_TASK_QUEUE_LIST
#error 	"rksyscfg.h, Missing RKSYS_TASK_QUEUE_LIST: Enable (1) or Disable (0) queue list for task"
#endif

#ifndef RKSYS_TASK_RESUME
#error 	"rksyscfg.h, Missing RKSYS_TASK_RESUME: Include code for task_resume(), task_kill() and task_suspend()"
#endif

#ifndef RKSYS_TASK_NAME_STRING
#error 	"rksyscfg.h, Missing RKSYS_TASK_NAME_STRING: Include task name within task control block"
#endif

#ifndef RKSYS_TASK_RUNTIME_STATS
#error	"rksyscfg.h, Missing RKSYS_TASK_RUNTIME_STATS: Enable (1) or Disable (0) statistics task"
#endif

#ifndef RKSYS_STATS_EXEC_TASKS
#error	"rksyscfg.h, Missing RKSYS_STATS_EXEC_TASKS: Enable (1) or Disable (0) executing time metrics of schedulable tasks"
#else
    #if RKSYS_STATS_EXEC_TASKS == 1 && RKSYS_RUNTIME_COUNTER != 1
    #error  "rksyscfg.h, For metrics and statistics must be enabled the RKSYS_RUNTIME_COUNTER"
    #else
		#ifndef RKSYS_STATS_TICK_HZ 
	    #error  "rksyscfg.h,  Define the # of overflow ocurrences per second of timer statistics"
		#endif

		#ifndef RKSYS_STATS_TICK_TASK 
	    #error  "rksyscfg.h,  Define the statistics task rate in unit of time [seconds]"
		#endif

		#ifndef RKSYS_STATS_TOTAL_TIME 
	    #error  "rksyscfg.h,  Define RKSYS_STATS_TOTAL_TIME macro for metrics and statistics"
		#endif
	#endif
#endif

#ifndef RKSYS_TIME_MEASURE 
#error  "rksyscfg.h,  Missing RKSYS_TIME_MEASURE: Enable (1) or Disable (0) code generation to measure execution time"
#endif

#ifndef rkinit_exec_time
	#define rkinit_exec_time()
#endif

#ifndef rkstart_exec_time
	#define rkstart_exec_time()
#endif

#ifndef rkstop_exec_time
	#define rkstop_exec_time()
#endif

#ifndef rkget_exec_time
	#define rkget_exec_time()
#endif

#ifndef RKSYS_TASK_NUM_TASKS
#error  "rksyscfg.h,  Missing RKSYS_TASK_NUM_TASKS: Max. number of tasks"
#else
    #if RKSYS_TASK_NUM_TASKS == 0 || RKSYS_TASK_NUM_TASKS > 32
    #error  "rksyscfg.h, RKSYS_TASK_NUM_TASKS must be > 0 and <= 32"
    #endif
#endif

#ifndef RKSYS_TASK_NUM_PTY_LEVEL
#error  "rksyscfg.h,  Missing RKSYS_TASK_NUM_PTY_LEVEL: Max. number of priority levels"
#else
    #if RKSYS_TASK_NUM_PTY_LEVEL == 0 || RKSYS_TASK_NUM_PTY_LEVEL > 32
    #error  "rksyscfg.h, RKSYS_TASK_NUM_PTY_LEVEL must be > 0 and <= 32"
    #endif
#endif


/*	Queue configurations */

#ifndef RKSYS_QUEUE
#error	"rksyscfg.h, Missing RKSYS_QUEUE: Enable (1) or Disable (0) code generation for queues"
#else
    #ifndef RKSYS_QUEUE_NUM_QUEUES
    #error "rksyscfg.h, Missing RKSYS_QUEUE_NUM_QUEUES: Max. number of queues"
    #else
        #if RKSYS_QUEUE_NUM_QUEUES == 0 || RKSYS_QUEUE_NUM_QUEUES > 16
        #error "rksyscfg.h, RKSYS_QUEUE_NUM_QUEUES must be > 0 and <= 16"
        #endif
    #endif

	#ifndef RKSYS_QUEUE_READ
	#error	"rksyscfg.h, Missing RKSYS_QUEUE_READ: Include code for queue_read()"
	#endif

	#ifndef RKSYS_QUEUE_REASSIGN
	#error	"rksyscfg.h, Missing RKSYS_QUEUE_REASSIGN: Include code for queue_reassign()"
	#endif

	#ifndef RKSYS_QUEUE_GET_INFO
	#error	"rksyscfg.h, Missing RKSYS_QUEUE_GET_INFO: Include code for queue_get_info()"
	#endif

#endif


/*	Event configurations */

#ifndef RKSYS_EVENT_NUM_TARGET
#error	"rksyscfg.h, Missing RKSYS_EVENT_NUM_TARGET: Max. number of event targets = 2^RKSYS_EVENT_NUM_TARGET"
#endif

#ifndef RKSYS_EVENT_NUM_ID
#error	"rksyscfg.h, Missing RKSYS_EVENT_NUM_ID: Max. number of event IDs = 2^RKSYS_EVENT_NUM_ID"
#endif

#if (RKSYS_EVENT_NUM_TARGET + RKSYS_EVENT_NUM_ID) != 8
#error	"rksyscfg.h, RKSYS_EVENT_NUM_TARGET + RKSYS_EVENT_NUM_ID must be equal to 8"
#endif

#if RKSYS_EVENT_NUM_TARGET == 0
#error	"rksyscfg.h, RKSYS_EVENT_NUM_TARGET must be > 0"
#endif

#if RKSYS_EVENT_NUM_ID == 0
#error	"rksyscfg.h, RKSYS_EVENT_NUM_ID must be > 0"
#endif


/*	Mutex configurations */

#ifndef RKSYS_MUTEX                   
#error     "rksyscfg.h, Missing RKSYS_MUTEX: Enable (1) or Disable (0) code generation for mutex"
#else
    #ifndef RKSYS_MUTEX_NUM_MUTEX
    #error    "rksyscfg.h, Missing RKSYS_MUTEX_NUM_MUTEX: Max. number of mutex"
    #else
        #if RKSYS_MUTEX_NUM_MUTEX == 0 || RKSYS_MUTEX_NUM_MUTEX > 16
        #error    "rksyscfg.h, RKSYS_MUTEX_NUM_MUTEX must be <= 16"
        #endif
    #endif
   
    #ifndef RKSYS_MUTEX_CREATE   
    #error     "rksyscfg.h, Missing RKSYS_MUTEX_CREATE: Include code for mutex_create()"
    #endif

    #ifndef RKSYS_MUTEX_FREE   
    #error     "rksyscfg.h, Missing RKSYS_MUTEX_FREE: Include code for mutex_free()"
    #endif

    #ifndef RKSYS_MUTEX_UNLINK   
    #error     "rksyscfg.h, Missing RKSYS_MUTEX_UNLINK: Include code for mutex_unlink()"
    #endif

	#ifndef RKSYS_MUTEX_GET_INFO
	#error	"rksyscfg.h, Missing RKSYS_MUTEX_GET_INFO: Include code for mutex_get_info()"
	#endif

#endif


/*	Miscellaneous configurations */

#ifndef RKSYS_PRINT_FORMAT
#error 	"rksyscfg.h, Missing RKSYS_PRINT_FORMAT: Enable (1) or Disable (0) code generation for formatted printing"
#endif

#ifndef RKSYS_PRINT_FORMAT_SIZE
#error 	"rksyscfg.h, Missing RKSYS_PRINT_FORMAT_SIZE: Max. size in character of formatted printing"
#endif

#ifndef RKSYS_CRITICAL_METHOD
#error 	"rksyscfg.h, Missing RKSYS_CRITICAL_METHOD: Sets a critical section method that the system use"
#endif

#ifndef RKSYS_MAX_NESTING_CSECT
#error 	"rksyscfg.h, Missing RKSYS_MAX_NESTING_CSECT: Max. size of nesting critical section"
#else
	#if RKSYS_MAX_NESTING_CSECT == 0
	#error	"rksyscfg.h, RKSYS_MAX_NESTING_CSECT must be > 0"
	#endif
#endif

#ifndef RKSYS_IDLE_TASK
#error 	"rksyscfg.h, Missing RKSYS_IDLE_TASK: Enable (1) or Disable (0) code generation for calling to idle task"
#endif

#ifndef RKSYS_SIZEOF_TICK_COUNTER
#error	"rksyscfg.h, Missing RKSYS_SIZEOF_TICK_COUNTER: Size of tick counter 8, 16 or 32-bits"
#endif

#ifndef RKSYS_TICK_RATE_HZ
#error "rksyscfg.h, Missing RKSYS_TICK_RATE_HZ: The frequency of the RKSYS tick interrupt"
#endif

#ifndef RKSYS_CPU_CLOCK_HZ
#error "rksyscfg.h, Missing RKSYS_CPU_CLOCK_HZ: The frequency in HZ at which the internal processor core"
#endif

#ifndef RKSYS_TICK_RATE_MS
#error "rksyscfg.h, Missing RKSYS_TICK_RATE_MS: Converts ticks to milliseconds"
#endif


/*	Software timer configurations */

#define RKSYS_TIMER_MAX_NUM_TIMERS		16		/* Max. number of timer control blocks */

#ifndef RKSYS_TIMER
#error	"rksyscfg.h, Missing RKSYS_TIMER: Enable (1) or Disable (0) code generation for timers"
#else
	#ifndef RKSYS_TIMER_NUM_TIMERS
	#error	"rksyscfg.h, Missing RKSYS_TIMER_NUM_TIMERS: Max. number of timer control blocks"
	#else
		#if RKSYS_TIMER_NUM_TIMERS == 0 || RKSYS_TIMER_NUM_TIMERS > RKSYS_TIMER_MAX_NUM_TIMERS
		#error	"rksyscfg.h, RKSYS_TIMER_MAX_NUM_TIMERS must be > RKSYS_TIMER_NUM_TIMERS"
		#endif
	#endif
 
	#ifndef RKSYS_SIZEOF_TICK_COUNTER
	#error	"rksyscfg.h, Missing RKSYS_SIZEOF_TICK_COUNTER"
	#endif

	#ifndef RKSYS_TIMER_INIT
	#error	"rksyscfg.h, Missing RKSYS_TIMER_INIT"
	#endif

	#ifndef RKSYS_TIMER_KILL 
	#error	"rksyscfg.h, Missing RKSYS_TIMER_KILL"
	#endif

	#ifndef RKSYS_TIMER_REASSIGN 
	#error	"rksyscfg.h, Missing RKSYS_TIMER_REASSIGN"
	#endif

	#ifndef RKSYS_TIMER_SIMPLE_CB
	#error	"rksyscfg.h, Missing RKSYS_TIMER_SIMPLE_CB"
	#endif

	#ifndef RKSYS_TIMER_GET_INFO
	#error	"rksyscfg.h, Missing RKSYS_TIMER_GET_INFO: Include code for stimer_get_info()"
	#endif

#endif


/*    Event flag register configurations */

#ifndef RKSYS_EFLAG
#error     "rksyscfg.h, Missing RKSYS_EFLAG: Enable (1) or Disable (0) code generation for event flags"
#else
    #ifndef RKSYS_EFLAG_NUM_REGS
    #error    "rksyscfg.h, Missing RKSYS_EFLAG_NUM_REGS: Max. number of event flag control blocks"
    #else
        #if RKSYS_EFLAG_NUM_REGS == 0 || RKSYS_EFLAG_NUM_REGS > 16
        #error  "rksyscfg.h, RKSYS_EFLAG_NUM_REGS must be <= 16"
        #endif
    #endif

    #ifndef RKSYS_EFLAG_GET_FLAGS
    #error    "rksyscfg.h, Missing RKSYS_EFLAG_GET_FLAGS: Include code for eflag_get_flags()"
    #endif

    #ifndef RKSYS_EFLAG_REASSIGN
    #error    "rksyscfg.h, Missing RKSYS_EFLAG_REASSIGN: Include code for eflag_reassign()"
    #endif

    #ifndef RKSYS_EFLAG_FREE
    #error    "rksyscfg.h, Missing RKSYS_EFLAG_FREE: Include code for eflag_free()"
    #endif

	#ifndef RKSYS_EFLAG_GET_INFO
	#error	"rksyscfg.h, Missing RKSYS_EFLAG_GET_INFO: Include code for eflag_get_info()"
	#endif

#endif


/*	Finite state machine configurations */

#ifndef RKSYS_FSM
#error "rksyscfg.h, Missing Enable (1) or Disable (0) code generation for FSM"
#else
    #ifndef RKSYS_NUM_FSMS
    #error "rksyscfg.h, Missing RKSYS_NUM_FSMS: Max. number of FSMs"
    #else
        #if RKSYS_NUM_FSMS == 0 || RKSYS_NUM_FSMS > 16
        #error  "rksyscfg.h, RKSYS_EFLAG_NUM_REGS must be > 0 and <= 16"
        #endif
    #endif

	#ifndef RKSYS_FSM_HISTORY
	#error 	"rksyscfg.h, Missing RKSYS_FSM_HISTORY: Include history states"
	#endif

	#ifndef RKSYS_FSM_RECALL
	#error 	"rksyscfg.h, Missing RKSYS_FSM_RECALL: Include recall"
	#endif

	#ifndef RKSYS_FSM_COND
	#error 	"rksyscfg.h, Missing RKSYS_FSM_COND: Include conditional states"
	#endif

	#ifndef RKSYS_FSM_GUARD
	#error 	"rksyscfg.h, Missing RKSYS_FSM_GUARD: Include guard functions"
	#else
		#if RKSYS_FSM_COND != 1
		#error 	"Missing RKSYS_FSM_GUARD: Enable (1) or Disable (0) guard function to pseudo-state facility"
		#endif
	#endif

	#ifndef RKSYS_FSM_PPRO
	#error 	"rksyscfg.h, Missing RKSYS_FSM_PPRO: Include preprocessor function"
	#endif

	#ifndef RKSYS_FSM_ACT_ARGS
	#error 	"rksyscfg.h, Missing RKSYS_FSM_ACT_ARGS: Defines the type of output or action function"
	#endif

	#ifndef RKSYS_FSM_GUARD_ARGS
	#error 	"rksyscfg.h, Missing RKSYS_FSM_GUARD_ARGS: Defines the type of guard function"
	#endif

	#ifndef RKSYS_FSM_STATE_ID
	#error 	"rksyscfg.h, Missing RKSYS_FSM_STATE_ID: Include state id"
	#endif

	#ifndef RKSYS_FSM_REENTRANT
	#error 	"rksyscfg.h, Missing RKSYS_FSM_REENTRANT: Enable (1) or Disable (0) fsm engine re-entrancy"
	#endif

	#ifndef RKSYS_FSM_MAX_COMP_TRANS
	#error 	"rksyscfg.h, Missing RKSYS_FSM_MAX_COMP_TRANS: Max. number of compound transtions"
	#else
		#if RKSYS_FSM_MAX_COMP_TRANS > 8 || RKSYS_FSM_MAX_COMP_TRANS == 0
	    #error  "rksyscfg.h, RKSYS_FSM_MAX_COMP_TRANS must be > 0 and <= 8"
    	#endif
	#endif
#endif


/*	Trace, debug and assert configurations */


#ifndef RKSYS_DEBUG
	#define RKSYS_DEBUG			0
#endif


#ifndef RKSYS_ASSERT
	#define RKSYS_ASSERT		0
#endif


/*
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

#if RKSYS_ASSERT == 1
	#ifdef rk_assert
		#define rkassert( exp, event )		\
			if( ( exp ) )					\
			{}								\
			else							\
				rk_assert( event )
	#else
	    #error  "rksyscfg.h, Missing rk_assert macro"
	#endif
#else
	#define rkassert( exp, event )
	#undef rk_assert
	#define rk_assert( event )
#endif


/*
 *	The list below defines the available trace system events. The system 
 *	generates each event by using a previously declared macro. Thus, each
 *	event is associated a macro. These macros are placed within RKSYS 
 *	source code, at key points of interest, called trace points. The macro 
 *	parameters are used to indicate which task, queue, mutex, timer or 
 *	event flag register was associated with the event being recorded.
 *
 * 	Key points of interest within the RKSYS source code contain 
 * 	empty macros that an application can re-define for the purpose of 
 * 	proving application specific trace facilities. The application need 
 * 	only implement those macros of particular interest - with unused 
 * 	macros remaining empty and therefore not impacting the application 
 * 	timing. 
 */

#ifndef RKSYS_TRACE
	#define RKSYS_TRACE			0
#endif

#if RKSYS_TRACE == 1

	/* ----- Trace tool macros ----- */

	#ifndef rktrace_init
		#define rktrace_init()
	#endif

	#ifndef rktrace_sys_start
		#define rktrace_sys_start()
	#endif

	#ifndef rktrace_sys_stop
		#define rktrace_sys_stop()
	#endif

	#ifndef rktrace_set_ts
		#define rktrace_set_ts()
	#endif

	/* ----- Scheduler trace ----- */

	#ifndef rktrace_dispatch_task
		#define rktrace_dispatch_task( td, mt, mi )
	#endif

	/* ----- Task trace ----- */

	#ifndef rktrace_kill_suspend_task
		#define rktrace_kill_suspend_task( td, tst )
	#endif

	#ifndef rktrace_resume_task
		#define rktrace_resume_task( td )
	#endif

	#ifndef rktrace_create_task
		#define rktrace_create_task( td )
	#endif

	#ifndef rktrace_deplete_task_queues
		#define rktrace_deplete_task_queues( td )
	#endif

	#ifndef rktrace_task_ready
		#define rktrace_task_ready( td )
	#endif

	/* ----- Event flag register trace ----- */

	#ifndef rktrace_assign_efr
		#define rktrace_assign_efr( efrd, td )
	#endif

	#ifndef rktrace_reassign_efr
		#define rktrace_reassign_efr( efrd, td )
	#endif

	#ifndef rktrace_free_efr
		#define	rktrace_free_efr( efrd )
	#endif

	#ifndef rktrace_set_wait_flags
		#define rktrace_set_wait_flags( efrd, wt, flags )
	#endif

	#ifndef rktrace_set_flags
		#define rktrace_set_flags( efrd, opt, flags )
	#endif

	/* ----- Mutex trace ----- */

	#ifndef rktrace_take_mutex
		#define rktrace_take_mutex( mtxd, td, mtxs )
	#endif

	#ifndef rktrace_give_mutex
		#define rktrace_give_mutex( mtxd, td, mtxs )
	#endif

	#ifndef rktrace_unlink_mutex
		#define	rktrace_unlink_mutex( mtxd, td, mtxs )
	#endif

	#ifndef rktrace_create_mutex
		#define	rktrace_create_mutex( mtxd )
	#endif

	#ifndef rktrace_free_mutex
		#define	rktrace_free_mutex( mtxd )
	#endif

	/* ----- Queue trace ----- */

	#ifndef rktrace_remove_queue
		#define rktrace_remove_queue( qd )
	#endif

	#ifndef rktrace_insert_queue
		#define rktrace_insert_queue( qd )
	#endif

	#ifndef rktrace_read_queue
		#define rktrace_read_queue( qd )
	#endif

	#ifndef rktrace_deplete_queue
		#define rktrace_deplete_queue( qd )
	#endif

	#ifndef rktrace_reassign_queue
		#define rktrace_reassign_queue( qd, td )
	#endif

	/* ----- Stimer trace ----- */

	#ifndef rktrace_assign_timer
		#define rktrace_assign_timer( timd )
	#endif

	#ifndef rktrace_reassign_timer
		#define rktrace_reassign_timer( timd )
	#endif

	#ifndef rktrace_kill_timer
		#define rktrace_kill_timer( timd )
	#endif

	#ifndef rktrace_kick_timer
		#define rktrace_kick_timer( timd )
	#endif

	#ifndef rktrace_stop_timer
		#define rktrace_stop_timer( timd )
	#endif

	#ifndef rktrace_timer_tick
		#define rktrace_timer_tick()
	#endif

	/* ----- FSM trace ----- */

	#ifndef rktrace_transition
		#define rktrace_transition( fsmd, cst, nst )
	#endif

	/* ----- Interrupt trace ----- */

	#ifndef rktrace_interrupt_in
		#define rktrace_interrupt_in( in )
	#endif

	#ifndef rktrace_interrupt_out
		#define rktrace_interrupt_out( in )
	#endif

#else

	/* ----- Trace tool macros ----- */

	#undef trace_init
	#define trace_init()

	#undef trace_start_stop
	#define trace_start_stop(trtype,opt)
	
	#undef trace_config
	#define trace_config(trtype,log,print)

	#undef trace_event0
	#define trace_event0(event,d0,d1,d2)
	
	#undef trace_event1
	#define trace_event1(event,d01,d2)

	#undef trace_getnext_event
	#define trace_getnext_event(p)
	
	#undef trace_get_status
	#define trace_get_status()
	
	#undef trace_flush
	#define trace_flush()

	#undef rktrace_init
	#define rktrace_init()

	#undef rktrace_sys_start
	#define rktrace_sys_start()

	#undef rktrace_sys_stop
	#define rktrace_sys_stop()

	#undef rktrace_set_ts
	#define rktrace_set_ts()

	/* ----- Scheduler trace ----- */

	#undef rktrace_dispatch_task
	#define rktrace_dispatch_task( td, mt, mi )

	/* ----- Task trace ----- */

	#undef rktrace_kill_suspend_task
	#define rktrace_kill_suspend_task( td, tst )

	#undef rktrace_resume_task
	#define rktrace_resume_task( td )

	#undef rktrace_create_task
	#define rktrace_create_task( td )

	#undef rktrace_deplete_task_queues
	#define rktrace_deplete_task_queues( td )

	#undef rktrace_task_ready
	#define rktrace_task_ready( td )

	/* ----- Event flag register trace ----- */

	#undef rktrace_assign_efr
	#define rktrace_assign_efr( efrd, td )

	#undef rktrace_reassign_efr
	#define rktrace_reassign_efr( efrd, td )

	#undef rktrace_free_efr
	#define	rktrace_free_efr( efrd )

	#undef rktrace_set_wait_flags
	#define rktrace_set_wait_flags( efrd, wt, flags )

	#undef rktrace_set_flags
	#define rktrace_set_flags( efrd, opt, flags )

	/* ----- Mutex trace ----- */

	#undef rktrace_take_mutex
	#define rktrace_take_mutex( mtxd, td, mtxs )

	#undef rktrace_give_mutex
	#define rktrace_give_mutex( mtxd, td, mtxs )

	#undef rktrace_unlink_mutex
	#define	rktrace_unlink_mutex( mtxd, td, mtxs )

	#undef rktrace_create_mutex
	#define	rktrace_create_mutex( mtxd )

	#undef rktrace_free_mutex
	#define	rktrace_free_mutex( mtxd )

	/* ----- Queue trace ----- */

	#undef rktrace_remove_queue
	#define rktrace_remove_queue( qd )

	#undef rktrace_insert_queue
	#define rktrace_insert_queue( qd )

	#undef rktrace_read_queue
	#define rktrace_read_queue( qd )

	#undef rktrace_deplete_queue
	#define rktrace_deplete_queue( qd )

	#undef rktrace_reassign_queue
	#define rktrace_reassign_queue( qd, td )

	/* ----- Stimer trace ----- */

	#undef rktrace_assign_timer
	#define rktrace_assign_timer( timd )

	#undef rktrace_reassign_timer
	#define rktrace_reassign_timer( timd )

	#undef rktrace_kill_timer
	#define rktrace_kill_timer( timd )

	#undef rktrace_kick_timer
	#define rktrace_kick_timer( timd )

	#undef rktrace_stop_timer
	#define rktrace_stop_timer( timd )

	#undef rktrace_timer_tick
	#define rktrace_timer_tick()

	/* ----- FSM trace ----- */

	#undef rktrace_transition
	#define rktrace_transition( fsmd, cst, nst )

	/* ----- Interrupt trace ----- */

	#undef rktrace_interrupt_in
	#define rktrace_interrupt_in( in )

	#undef rktrace_interrupt_out
	#define rktrace_interrupt_out( in )

#endif

#endif
