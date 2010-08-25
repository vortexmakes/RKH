/*
 * 		enaint.h
 * 		
 * 		This module manages the interrupt enabling and reenabling
 */

#include "mytypes.h"

/*
 * 	init_int_handler:
 *		Must be called before any sem_disable
 */

void init_int_handler( void );

/*
 * 	sem_disable
 * 		Disable general interrupts for semaphore like conditions
 * 		Remembers state of interrupt flag for next 'sem_enable'
 * 		Can be nested called
 */


void sem_disable( void );

/*
 * 	sem_enable
 * 		Conditionally enables general interrupts based on state of
 * 		interrupt flag.
 * 		Programmer must be aware that this functions must be used
 * 		in strict order and that interrupts must not be enabled or disabled
 * 		in between the two callings.
 * 		Can be nested called
 */

void sem_enable( void );

/*
 * 	enable_gral_interrupt
 * 		Enables general interrupt
 * 		The instruction enable interrupt must not be called
 * 		directly
 */

void enable_gral_interrupt( void );

/*
 * 	disable_general_interrupt
 * 		Disables general interrupt
 * 		The instruction disable interrupt must not be called
 * 		directly
 */

void disable_gral_interrupt( void );


