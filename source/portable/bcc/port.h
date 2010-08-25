/*
 * 	port.h
 */


#ifndef __PORT_H__
#define __PORT_H__


#include "rksys.h"


#define enter_critical()
#define exit_critical()


#if RKSYS_DEBUG

#include <stdio.h>
#include <conio.h>

#define dprint(x)				print_format##x
#define dclrscr()				clrscr()
#define rkput_string(x)			printf("%s",x)
#define rkput_char(x)			putc(x,stdout)

#if RKSYS_TRACE_FSM && RKSYS_FSM_STATE_ID
#define rktrace_fsm(x)			dprint(x)
#else
#define rktrace_fsm(x)
#endif

#if RKSYS_TRACE_SCHEDULER
#define rktrace_scheduler(x)	dprint(x)
#else
#define rktrace_scheduler(x)
#endif

#if RKSYS_TRACE_EFR
#define rktrace_efreg(x)		dprint(x)
#else
#define rktrace_efreg(x)
#endif

#if RKSYS_TRACE_TASK
#define rktrace_task(x)			dprint(x)
#else
#define rktrace_task(x)
#endif

#if RKSYS_TRACE_STIMER
#define rktrace_stimer(x)		dprint(x)
#else
#define rktrace_stimer(x)
#endif

#else

#define dprint(x)		
#define dclrscr()
#define rkput_string(x)
#define rkput_char(x)
#define rktrace_fsm(x)
#define rktrace_scheduler(x)
#define rktrace_efreg(x)
#define rktrace_task(x)
#define rktrace_stimer(x)

#endif


#endif
