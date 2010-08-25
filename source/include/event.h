/*
 * event.h
 */


#ifndef __EVENT_H__
#define __EVENT_H__


#include "mytypes.h"
#include "rksyscfg.h"


/*
 * 	define_event:
 *
 * 	This macro defines a event structure. This macro is called when use 
 * 	a array of events.
 *
 * 	Arguments:
 *
 * 	'p':	event parameter.
 * 	'i':	event id.
 * 	't':	event target.
 */

#define DEFINE_EVENT( p, i,	t ) 		{ p, i, t }


/*
 * 	create_const_event:
 *
 * 	This macro creates a event structure. This structure resides in ROM memory
 * 	space and cannot be modified in runtime.
 *
 * 	Arguments:
 *
 * 	'n':	event name.
 * 	'p':	event parameter.
 * 	'i':	event id.
 * 	't':	event target.
 */

#define DEFINE_CONST_EVENT( n, p, i, t ) 		const EVT_T n = { p, i, t }


/*
 * 	create_ram_event:
 *
 * 	This macro creates a event structure. This structure resides in 
 * 	RAM memory space and may be modified in runtime.
 *
 * 	Arguments:
 *
 * 	'n':	event name.
 * 	'p':	event parameter.
 * 	'i':	event id.
 * 	't':	event target.
 */

#define DEFINE_VAR_EVENT( n, p, i, t ) 			EVT_T n = { p, i, t }


/*
 * 	These macros are used by application task code to obtain the information 
 * 	about of arrived event that made the task ready to run. According to 
 * 	received event type the task uses the proper macro.
 *
 * 	Arguments:
 *
 * 	'ei': 	parameter of entry task function passed by reference. Contains 
 * 			the necessary information to process arrived event. According to 
 * 			arrived event type must be used a proper macro to obtain the 
 * 			queue descriptor, flags	register or signal number.
 */

#define get_event_type(ei)						(ei)->type
#define get_tcb(ei)								(TASK_T*)((ei)->pt)
#define get_queue(ei)							(ei)->evt.qd
#define get_flags(ei)							(ei)->evt.flags
#define get_signal(ei)							(ei)->evt.signo
#define get_mutex(ei)							(ei)->evt.mtxd


typedef struct
{
	uchar param;							/* event parameter */
	unsigned id:RKSYS_EVENT_NUM_ID;			/* event identification */
	unsigned tgt:RKSYS_EVENT_NUM_TARGET;	/* event target */
} EVT_T;


/* 	Indicates the type associated with the arrived event */

enum
{
	EVENT_QUEUE_TYPE,
	EVENT_SIGNAL_TYPE,
	EVENT_EFLAG_TYPE,
	EVENT_MUTEX_TYPE
};


/*
 *	Contains the associated information with the arrived event that made the 
 *	task ready to run. The entry task function receives this information as 
 *	a pointer.
 */

typedef struct
{
	uchar type;			/*	contains the type associated with the arrived
						 *	event and can have the following values: 
						 *	EVENT_QUEUE_TYPE, EVENT_SIGNAL_TYPE,
						 *	EVENT_EFLAG_TYPE, EVENT_MUTEX_TYPE. 
						 *	The event type allows to determine whether the 
						 *	arrived event is a queued event, signal event, 
						 *	flag event or mutex event.
						 */
	void *pt;			/*	points to current task structure */
	union 
	{
		uchar info;		/*	contains extra information associated with 
						 *	the event.
						 */
		uchar qd;		/* 	contains the queue descriptor when arrived 
						 *	a EVENT_QUEUE_TYPE 
						 */
		uchar flags;	/* 	contains the flags of event flags register 
						 *	linked to task when arrived a EVENT_EFLAG_TYPE 
						 */
		uchar signo;	/* 	contains the signal number when arrived 
						 *	a EVENT_SIGNAL_TYPE 
						 */
		uchar mtxd;		/*	contains the mutex descriptor when arrived 
						 *	a EVENT_MUTEX_TYPE 
						 */
	} evt;
} SCHDR_MSG_T;


#endif
