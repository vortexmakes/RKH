/*
 * 	eflag.h
 */


#ifndef __EFLAG_H__
#define __EFLAG_H__


#include "mytypes.h"
#include "task.h"


typedef MUInt EFD_T;


/*	Return codes */

enum
{
	EFLAG_OK, EFLAG_NO_ROOM
};


/*
 *	FLAG_WAIT_SET_ANY: wait for ALL the bits specified to be SET (i.e. 1)
 *	FLAG_WAIT_SET_ANY: wait for ANY of the bits specified to be SET (i.e. 1)
 */

enum
{

	FLAG_WAIT_SET_ANY, FLAG_WAIT_SET_ALL
};


/*	Indicates whether the flags will be SET or CLEAR */

enum
{
	FLAG_SET, FLAG_CLEAR
};


#define FLAG_EMPTY_EFREG		RKSYS_EFLAG_NUM_REGS	


/*	Data type for event flag bits (8, 16 or 32 bits) */

#if RKSYS_EFLAG_NUM_FLAGS == 8
typedef uchar FLAGS_T;
#elif RKSYS_EFLAG_NUM_FLAGS == 16
typedef ushort FLAGS_T;
#elif RKSYS_EFLAG_NUM_FLAGS == 32
typedef ulong FLAGS_T;
#else
typedef uchar FLAGS_T;
#endif


/*
 * 	Defines the data structure into which the performance information for
 * 	event flags is stored.
 */

typedef struct
{
	ushort sets;				/*	number of set requests */
	ushort gets;				/*	number of get requests */
} EFLAG_INFO_T;


/*
 * 	eflag_assign:
 *
 * 	Assigns a task to event flag register. Any task intending to install a 
 * 	event flag register must first assign and initialize a event flag register
 * 	structure. In this case, the flags register is cleared.
 *
 *	Arguments:
 *
 *	'ptask': 	pointer to desired waiting task.
 *
 *	Returns:
 *
 *	A integer number that identifies a event flag register or a negative
 *	value if no more registers are available. 
 */

EFD_T eflag_assign( TASK_T *ptask );


/*
 * 	eflag_reassign_task:
 *
 * 	Assigns a new task to previously assigned event flag register. If event 
 * 	flag register is set must be set again. The flags register is cleared.
 *
 *	Arguments:
 *
 *	'efd':		event flag register descriptor. This number is returned when 
 *				the	event flag register is assigned.
 *	'ptask': 	pointer to assigned waiting task.
 */

void eflag_reassign( EFD_T efd, TASK_T *ptask );

/*
 * 	eflag_free:
 *
 * 	Free a event flag register from assigned task, freeing the slot occupied
 * 	by the event flag register descriptor.
 *
 * 	Arguments:
 *
 * 	'efd':		a event flag register descriptor identifying a previously 
 * 				created event flag register.
 */

void eflag_free( EFD_T efd );


/*
 *	eflag_set_wait_flags:
 *
 * 	Sets a combination of bits to be set in an event flag register. A task
 * 	can wait for any condition to be set or for all conditions to be set. When
 * 	a desired conditions are satisfied the pending task is woken and the event
 * 	flag register is passed to that.
 * 	
 * 	Arguments:
 *
 * 	'efd': 			event flag register descriptor.
 * 	'wait_type': 	specifies whether wants ALL bits to be set or ANY of the 
 * 					bits to be set. The desired conditions are satisfied 
 * 					according to following arguments:
 *
 *  				FLAG_WAIT_SET_ALL: waits for ALL bits in 'flags' to be set
 *  				FLAG_WAIT_SET_ANY: waits for ANY bit in 'flags' to be set
 *
 *  'flags': 		bit pattern indicating which bit(s) or flag(s) wish to 
 *  				check.
 */

void eflag_set_wait_flags( EFD_T efd, uchar wait_type, FLAGS_T flags );


/*
 *	eflag_set_flags:
 *
 *	Sets and clear event flag bits. The bits set or cleared are specified 
 *	in a bit mask. When a desired conditions are satisfied the waiting task 
 *	is woken and the event flag register is passed to it.
 *	
 *	Arguments:
 *
 * 	'efd': 		event flag register descriptor.
 * 	'flags': 	if 'opt' (see below) is FLAG_SET, each bit that is set in 
 * 				'flags' will set the corresponding bit in the event flag 
 * 				register. e.g. to set bits 0, 4 and 5 would set 'flags' to:
 * 				0x31 (note, bit 0 is least significant bit).
 *
 *  			If 'opt' (see below) is FLAG_CLR, each bit that is set in 
 *  			'flags' will CLEAR the corresponding bit in the event flag 
 *  			group. e.g. to clear bits 0, 4 and 5 you would specify 
 *  			'flags' as: 0x31 (note, bit 0 is least significant bit).
 *
 *	'opt':		indicates whether the flags will be: set (FLAG_SET) or 
 *				cleared (FLAG_CLEAR).
 *
 *	Returns:
 *
 *	The new value of the event flags.
 */

FLAGS_T eflag_set_flags( EFD_T efd, FLAGS_T flags, uchar opt );


/*
 *	eflag_get_flags:
 *
 *	Returns the status of the flags in the event flag register.
 *
 *	Arguments:
 *
 * 	'efd': 		event flag register descriptor.
 */

FLAGS_T eflag_get_flags( EFD_T efd );


/*
 *	eflag_check_condition:
 *
 *	Checks the desired condition is safisfied. Returns a boolean value from 
 *	this checking and the status of flags in the event flag register.
 *	Always, the readies flags are consumed. 
 *
 *	Note:
 *
 *	This function is INTERNAL to RKSYS and the user application 
 *	should not call it.
 *
 *	Arguments:
 *
 * 	'efd': 		event flag register descriptor.
 * 	'pflags': 	pointer to the buffer into which the current status of the 
 * 				flags in the event flag register will be copied.
 *
 * 	Returns:
 *
 * 	A true value if desired condition is satisfied, otherwise false value.
 */

uchar eflag_check_condition( EFD_T efd, FLAGS_T *pflags );


/*
 * 	eflag_clear_info:
 *
 * 	Clear performance information for a particular event flag.
 *
 * 	Information is available during run-time for each of the RKSYS
 * 	resources. This information can be useful in determining whether
 * 	the application is performing properly, as well as helping to
 * 	optimize the application.
 *
 * 	'efd':		event flag register descriptor.
 */

void eflag_clear_info( EFD_T efd );


/*
 * 	eflag_get_info:
 *
 * 	Retrieves performance information for a particular event flag.
 *
 * 	'efd':		event flag register descriptor.
 * 	'pefi':		pointer to the buffer into which the performance information
 * 				will be copied by reference.
 */

void eflag_get_info( EFD_T efd, EFLAG_INFO_T *pefi );


#endif
