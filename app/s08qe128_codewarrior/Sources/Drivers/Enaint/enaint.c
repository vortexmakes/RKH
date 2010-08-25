/*
 * 		enaint.c
 *
 * 		This module manages the interrupt enabling and reenabling
 */

#include <stdio.h>
#include "derivative.h"

#include "mytypes.h"

#include "enaint.h"
#include "lowint.h"
#include "drverr.h"


/*
 * 	Stack for saving interrupt status
 */

#define MAX_INT_STACK	8

static signed char int_stack[ MAX_INT_STACK ], *pint;

/*
 * 	init_stack:
 * 		Initializes stack to empty
 */

static
void
init_stack( void )
{
	pint = int_stack;
}

/*
 * 	push:
 * 		Pushes an enable_status.
 * 		If no more room, returns negative
 */

static
MInt
push( MUInt enable_status )
{
	if( pint >= int_stack + MAX_INT_STACK )
		return -1;
	*pint++ = enable_status;
	return 0;
}

/*
 * 	pop:
 * 		Gets enable status from stack top
 * 		If stack empty, return negative
 */

static
MInt
pop( void )
{
	if( pint <= int_stack )
		return -1;
	return *--pint;
}

/*
 * 	init_int_handler:
 */

void
init_int_handler( void )
{
	init_stack();
}

/*
 * 	sem_disable
 * 		Disable general interrupts for semaphore like conditions
 * 		Remembers state of interrupt flag for next 'sem_enable'
 */


void
sem_disable( void )
{
	MInt status;

	status = get_enable_status();
	disable_interrupt();
	if( status < 0 )
		fatal_driver( INT_STK_OFLOW );
	
	push( status ); 		
}

/*
 * 	sem_enable
 * 		Conditionally enables general interrupts based on state of
 * 		saved in stack interrupt flag.
 */

void
sem_enable( void )
{
	MInt enable_status;

	if( enable_status = pop(), enable_status < 0 )
		fatal_driver( ENA_WOUT_DISA );
	enable_status ? enable_interrupt() : disable_interrupt();
}


/*
 * 	enable_gral_interrupt
 * 		Enables general interrupt
 * 		The instruction enable interrupt must not be called
 * 		directly
 */

void
enable_gral_interrupt( void )
{
	enable_interrupt();
}

/*
 * 	disable_general_interrupt
 * 		Disables general interrupt
 * 		The instruction disable interrupt must not be called
 * 		directly
 */

void
disable_gral_interrupt( void )
{
	disable_interrupt();
}

