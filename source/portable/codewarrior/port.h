/*
 * 	port.h
 */


#ifndef __PORT_H__
#define __PORT_H__


#include "rksyscfg.h"
#include <hidef.h>
#include "ioports.h"
#include "serial.h"
#include "watchdog.h"


#define enter_critical				rkenter_critical
#define exit_critical				rkexit_critical


void rkinit_critical( void );
void rkenter_critical( void );
void rkexit_critical( void );


/*	Enable and disable general interrupts 	*/

#define rkenable_interrupt()		EnableInterrupts
#define rkdisable_interrupt()		DisableInterrupts

#define rkput_string(y,x)			put_string(y,x)
#define rkput_char(y,x)				put_char(y,x)

#define rkreset()					asm ("bgnd")
#define rkwatchdog()				kick_watchdog()


/* 	
 *  These macros can be used to calculate real time from the 
 *  tick rate - with the resolution of one tick period.
 */

#define rktick_ms(t)   				((RKTICK_T)((t)/RKSYS_TICK_RATE_MS))
#define rktick_sec(t)    			((RKTICK_T)((t)*(1000/RKSYS_TICK_RATE_MS)))
#define rktick_min(t)  				((RKTICK_T)((t)*60*(1000/RKSYS_TICK_RATE_MS)))


/* 
 * These macros can be used to print a formatted string.
 */

#if RKSYS_DEBUG

#define dprint(x)					print_format##x
#define dclrscr()

#else

#define dprint(x)
#define dclrscr()

#endif


/* 
 * These macros can be used to measure interval time 
 * between two time points.
 */

#if RKSYS_RUNTIME_COUNTER

#define rkinit_exec_time()
#define rkstart_exec_time()			(TPM1CNT=0)
#define rkstop_exec_time()
#define rkget_exec_time()			TPM1CNT

#endif


#endif
