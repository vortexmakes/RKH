/*
 * 	rkhtim.h
 *
 *	Implements a software timer facility.
 */

#ifndef __RKHTIM_H__
#define __RKHTIM_H__


#include "mytypes.h"
#include "rksys.h"
#include "task.h"


/*
 * 	Timer mode.
 *
 *	ONESHOT:	the started soft timer will run in oneshot mode. Once the 
 *				timeout will expire and the callback function will be 
 *				executed. The timer won't be re-started automatically.
 *
 *	RETRIG: 	the started soft timer will run in periodic mode. Once the 
 *				timeout will expire and the callback function will be 
 *				executed the timer will be re-started (re-triggered) again 
 *				automatically.
 */

enum
{
	ONESHOT, RETRIG
};


/*	Return codes */

enum
{
	TIMER_OK, TIMER_NO
};


typedef MInt TIM_T;


#if RKSYS_TIMER_SIMPLE_CB == 0

typedef void (*STCB_T)( TIM_T timd, void *stp );

#else

typedef void (*STCB_T)( void );

#endif


/*
 * 	Defines the data structure into which the performance information for
 * 	software timers is stored.
 */

typedef struct
{
	ushort expirations;			/*	number of expirations */
	ushort kicks;				/*	number of kick requests */
	ushort kills;				/*	number of kill requests */
	ushort reassigns;			/*	number of reassign requests */
} TIMER_INFO_T;


/*
 * 	stimer_init:
 *
 * 	Initializes the available timer slots.
 */

void stimer_init( void );


/*
 * 	stimer_handler:
 *
 * 	Keep tracks and updates the started timers. If one or more timers 
 * 	expires the associated callback function is executed. This function 
 * 	must be placed where will be incrementing the system tick. Normally 
 * 	this is placed in a timer ISR routine.
 */

void stimer_handler( void );


/*
 * 	stimer_assign:
 *
 *	Assigns a timer. This operation allocates a soft-timer structure. 
 *	Any software module intending to install a soft timer must first 
 *	create a timer structure. The timer structure contains control 
 *	information that allows the timer-handling facility to update and 
 *	expire soft timers. 
 *
 * 	Arguments:
 *		
 *	'type': 	timer type.
 *	'stcb': 	callback function to be called at the timer expiration.
 *	'stp': 		parameter of callback function. 
 *
 *	Returns: 
 *
 *	The number of timer descriptor identifying the newly created timer.
 */

#if RKSYS_TIMER_SIMPLE_CB == 0

TIM_T stimer_assign( uchar type, STCB_T stcb, void *stp );

#else

TIM_T stimer_assign( uchar type, STCB_T stcb );

#endif


/*
 * 	stimer_reassign:
 *
 * 	Reassigns the callback function and its parameter to previously created
 * 	timer. If timer is running must be restarted.
 *
 * 	Arguments:
 *
 * 	'timd': 	a timer descriptor identifying a previously created timer.
 *	'stcb': 	callback function to be called at the timer expiration.
 *	'stp': 		parameter of callback function. 
 */

#if RKSYS_TIMER_SIMPLE_CB == 0

void stimer_reassign( TIM_T timd, STCB_T stcb, void *stp );

#else

void stimer_reassign( TIM_T timd, STCB_T stcb );

#endif


/*
 * 	stimer_kill:
 *
 * 	Kills a timer. This operation kills a previously created timer, 
 * 	freeing the memory occupied by the timer structure.
 *
 * 	Arguments:
 *
 * 	'timd': 	a timer descriptor identifying a previously created timer.
 */

void stimer_kill( TIM_T timd );


/*
 * 	stimer_kick:
 *
 * 	Kicks a timer. This operation installs a previously created timer into
 * 	the timer-handling facility. The timer begins running at the completion 
 * 	of this operation.
 *
 * 	Arguments:
 *
 * 	'timd': 	a timer descriptor identifying a previously created timer.
 * 	'tout': 	timeout or expiration time in ticks.
 */

void stimer_kick( TIM_T timd, RKTICK_T tout );


/*
 * 	stimer_stop:
 *
 *	Stops a currently running timer. This operation stops a timer by 
 * 	removing the currently running timer from the timer-handling facility.
 *
 * 	Arguments:
 *
 * 	'timd': 	a timer descriptor identifying a previously created timer.
 */

void stimer_stop( TIM_T timd );


/*
 * 	stimer_clear_info:
 *
 * 	Clear performance information for a particular software timer.
 *
 * 	Information is available during run-time for each of the RKSYS
 * 	resources. This information can be useful in determining whether
 * 	the application is performing properly, as well as helping to
 * 	optimize the application.
 *
 * 	'timd':		timer descriptor.
 */

void stimer_clear_info( TIM_T timd );


/*
 * 	stimer_get_info:
 *
 * 	Retrieves performance information for a particular software timer.
 *
 * 	'timd':		timer descriptor.
 * 	'pti':		pointer to the buffer into which the performance information
 * 				will be copied by reference.
 */

void stimer_get_info( TIM_T timd, TIMER_INFO_T *pti );


#endif
