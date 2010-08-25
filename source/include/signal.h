/*
 * 	signal.h
 *
 * 	The signal is generated when an event has occurred. Each signal is 
 * 	identified by an integer value, which is the signal number or vector 
 * 	number. A task defines the signals to catch. Thus, when a signal arrives 
 * 	the corresponding system signal handler is invoked and the signal number 
 * 	is passed to corresponding task as event.
 */


#ifndef __SIGNAL_H__
#define __SIGNAL_H__


#include "mytypes.h"


/*
 *	This macro creates the signals register. Must be called from 
 *	'sigdata.c' file.
 *
 *	Note:
 *
 *	See SIG_T structure declaration for more information.
 */

#define CREATE_SYSTEM_SIG_REGISTER	const SIG_T signals[]=


/*
 * 	This macro creates a system signal vector. Generally, every system signal 
 * 	are created in 'sigdata.c' file.
 *
 * 	Arguments:
 *
 * 	's': 	signal name. Represents a newly signal structure.
 * 	'sn': 	signal number. Identifies the integer value of vector number.
 * 	'sh': 	signal handler. Pointer to system signal handler. Optional 
 * 			parameter may be declared as NULL.
 */

#define DEFINE_SYSTEM_SIGNAL( s, sh )		{s##_vect,sh}


/*
 * 	This macro creates a list of task that catchs a signal. This list is a 
 * 	array of pointer to task structures and it must be terminated in 
 * 	'END_SIG_TASK_TABLE'. Every element of array must be defined using 
 * 	'task_take' macro. Generally, every system signal are declared in 
 * 	'sigdata.c' file.
 *
 * 	Arguments:
 *
 *	'sn': 	signal name. Represents a previously created signal structure.
 */

#define SIG_TASK_TABLE( sn )		const struct task_t*const sn##_vect[]


/*	Used to terminate a signal vector table */

#define END_SIG_TASK_TABLE			NULL


typedef void (*DEF_SIG_HDLR_T)( void );


typedef struct
{
	const struct task_t * const *psvect;
	DEF_SIG_HDLR_T pdsh;
} SIG_T;


#endif
