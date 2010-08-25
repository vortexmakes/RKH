/*
 * 	fsm.h
 *
 * 	FSM consists of three primary things – states, transitions, and 
 * 	actions. States are distinguishable conditions of existence that 
 * 	persist for a significant period of time. Transitions are the means 
 * 	by which objects change states in respond to events. State machines 
 * 	also execute actions – atomic behaviors – at various points in a 
 * 	state machine, such as when an event triggers a transition.
 */

#ifndef __FSM_H__
#define __FSM_H__


#include "mytypes.h"
#include "event.h"
#include "rksys.h"


/*
 *	This macro creates the FSMs register. Must be called from 
 *	'fsmdata.c' file.
 *
 *	Note:
 *
 *	See 'CREATE_FSM' macro declaration for more information.
 */

#define CREATE_FSMS_REGISTER			FSM_T fsms[]=


/*
 *	This macro creates a state. See STATE_T structure definition.
 *
 *	Arguments:
 *
 *	's': 	state name. Represents a state structure.
 *	'tr': 	pointer to state transition table.
 *	'p': 	pointer to preprocessor function of arrived event. Optional 
 *			parameter may be declared as NULL.
 *	'st': 	state type.
 *	'sid': 	state id. Optional parameter may be declared as 0.
 */

#if RKSYS_FSM_PPRO && RKSYS_FSM_STATE_ID

#define CREATE_STATE( s, tr, p, st, sid ) 					\
					const STATE_T s = { tr, p, st, sid }

#elif RKSYS_FSM_PPRO && RKSYS_FSM_STATE_ID == 0

#define CREATE_STATE( s, tr, p, st ) 						\
					const STATE_T s = { tr, p, st }

#elif RKSYS_FSM_PPRO == 0 && RKSYS_FSM_STATE_ID

#define CREATE_STATE( s, tr, st, sid ) 						\
					const STATE_T s = { tr, st, sid }

#else

#define CREATE_STATE( s, tr, st, sid ) 						\
					const STATE_T s = { tr, st }

#endif


/*	
 *	This macro creates a state transition table. See TRANS_T structure 
 *	definition.
 *	
 *	Arguments:
 *
 *	't': array of allowed transitions for a state.
 */

#define CREATE_TRANSITION(t)			const TRANS_T t[]=


/*
 *	This macro creates a finite state machine structure. See FSM_T structure 
 *	definition.
 *
 *	Arguments:
 *
 *	'is': 	initial or default state.
 */

#if RKSYS_FSM_HISTORY

#define CREATE_FSM(	is )			{ is, is, is, 0 }

#else

#define CREATE_FSM(	is )			{ is, is }

#endif


#define FSM_ANY							0xFF
#define ELSE							FSM_ANY


/*
 * 	State types:
 *
 * 	NORMAL_STATE: 
 *
 * 	It's a distinguishable condition of existence that persist for a 
 * 	significant period of time.
 *
 * 	INITIAL_STATE: 
 *
 * 	The initial pseudostate shows the default state assumed upon creating 
 * 	a fsm. This indicates that when the fsm is created, it enters initial 
 * 	state initially before processing any events.
 *
 * 	COND_STATE: 
 *
 * 	Represents multiple transitions which share a common source state and 
 * 	triggering event. Different exiting transition segments are selected on 
 * 	the basis of guarding conditions. The conditional pseudostate is not a 
 * 	real state – if the transition is not taken, the triggering event 
 * 	is discarded and the original source state continues to be active. 
 * 	Conditional pseudostates are a notational shorthand for multiple exiting 
 * 	transitions all triggered by the same event but each having different 
 * 	guards. The resulting state differs depending on the evaluation of the 
 * 	guards. The "else" guard handles all other conditions and transitions to 
 * 	the target state.
 *
 * 	HISTORY_STATE: 
 *
 * 	Used to store one state of fsm. This action is performed through 
 * 	'set_histoy' function. If a transition to the indicator fires, the 
 * 	current state is moved to history state. If it not exists that 
 * 	transition is ignored.
 */

enum
{
	NORMAL_STATE, INITIAL_STATE, COND_STATE, HISTORY_STATE
};


enum
{
	GUARD_TRUE, GUARD_FALSE
};


#if RKSYS_FSM_ACT_ARGS

/* This declaration pass by reference the triggering event */

typedef void (*ACT_T)( EVT_T *in );

#else

typedef void (*ACT_T)( void );

#endif


#if RKSYS_FSM_GUARD_ARGS

/*	This declaration pass by reference the triggering event  */

typedef uchar (*GUARD_T)( EVT_T *in );

#else

typedef uchar (*GUARD_T)( void );

#endif

typedef uchar (*PREPRO_T)( EVT_T *in );
typedef MUInt FSMD_T;


/*
 *	Transition:
 *
 * 	Indicates that the state machine responds to an event while in certain 
 * 	states. Transitions are modeled as taking approximately zero time to 
 * 	execute. State machine execution itself is said to proceed in discrete 
 * 	time units called run-to-completion (RTC) model steps. An RTC step is 
 * 	the period of time in which events are accepted and acted upon. 
 * 	Processing an event always completes within a single model step.
 *
 * 	Any event that is not explicitly listed as causing an event to occur in
 * 	a given state is quietly discarded should it occur. The general 
 * 	transition for a transition is:
 *
 * 		event[guard or condition]/action-list ^ event-list
 *
 * 	Some of these fields are optional.
 *		
 *	event:
 *
 *	The event triggers the transition. It may include a condition too, 
 *	enclosed in square brackets. Thus, if a transition is labeled 
 *	E = event[ C = guard or condition ], the condition C is tested at the 
 *	instant the event E occurs, guarding the transition from being taken 
 *	if it is not true at that time. The 'guard or conditional' field 
 *	is detailed below.
 *	
 *	guard or condition:
 *
 *	A guard is a boolean condition that returns a GUARD_TRUE or 
 *	GUARD_FALSE value that controls whether or not a transition is taken 
 *	following the receipt of a triggering event. A transition with a guard 
 *	is only take if the triggering event occurs and the guard evaluates to 
 *	GUARD_TRUE. As long as the guard evaluated to GUARD_FALSE, the 
 *	triggering event would be discarded and the transition would not be 
 *	taken.
 *
 *	Another way of using conditions to guard transitions is to employ the 
 *	condition pseudo-state. An arrow enters the conditional state, labeled 
 *	with the triggering event, and the pseudo-state may have several exit 
 *	arrows, each labeled with a condition enclosed in square brackets and 
 *	optionally also with an action.
 *
 *	action-list:
 *
 *	Action lists consist of zero or more actions. The actions are small 
 *	atomic behaviors executed at specified points in a state machine. 
 *	Actions are assumed to take an insignificant amount of time to execute 
 *	and are noninterruptible by another fsm. The listed actions are 
 *	separated by comma ','.
 *
 *	event-list:
 *	
 *	The transition label can also include an event-list. Event-lists are 
 *	always preceded with a carat '^', and have a list of events that are 
 *	generated as a result of taking the transition. Events generated in this 
 *	way are called propagated events.
 */

typedef struct trans_t
{
	uchar evt;								/* input event */
	const struct state_t *const next_state;	/* points to next state */
	ACT_T action;							/* points to action function */
#if RKSYS_FSM_GUARD
	GUARD_T guard; 							/* points to guard function */
#endif
} TRANS_T;


typedef struct state_t
{
	const TRANS_T *const trans;	/* points to transition table state */
#if RKSYS_FSM_PPRO
	PREPRO_T ppro; 				/* points to preprocessor function */
#endif
	uchar state_type;			/* state type */
#if RKSYS_FSM_STATE_ID
	uchar state_id;				/* state id */
#endif
} STATE_T;


/*
 * 	FSM Control Block
 */

typedef struct
{
	const STATE_T *const init_state; 	/* points to initial state */
	const STATE_T *state;				/* points to current state */
#if RKSYS_FSM_HISTORY || RKSYS_FSM_RECALL
	const STATE_T *srecall;			/* points to previously stored state */
	uchar erecall;					/* stores the previously stored event */
#endif
} FSM_T;


/*
 * 	fsm_init:
 *
 * 	Inits a fsm calling its initializing function.
 *
 * 	Arguments:
 *
 * 	'fsmd': fsm descriptor.
 */

void fsm_init( FSMD_T fsmd );


/*
 *	fsm_engine:
 *
 *	Executes a fsm in a non-preemtive model. In this model, before the 
 *	system handles a new event it can store it until the previous event 
 *	has completed processing. This model is called run to completion or 
 *	RTC. Thus, the system processes events in discrete, indivisible RTC 
 *	steps.
 *
 *	Arguments:
 *
 *	'fsmd': fsm descriptor.
 *	'pevt': pointer to arrived event. The field event.param is used as 
 *			input alphabet.
 */

void fsm_engine( FSMD_T fsmd, EVT_T *pevt );


/*
 * 	fsm_set_history:
 *
 * 	Stores a desired state. A transition coming into history state is 
 * 	equivalent to a transition coming into the previously stored state.
 *
 * 	Arguments:
 *
 * 	'fsmd': fsm descriptor.
 *	'ps': 	pointer to state to be stored.
 *	'evt': 	triggering event to be stored.	
 */

void fsm_set_history( FSMD_T fsmd, const STATE_T *ps );


/*
 * 	This macro clears the history state.
 *
 * 	Arguments:
 *
 * 	'fsmd': fsm descriptor.
 */

#define fsm_clear_history( fsmd )		fsm_set_history(fsmd,NULL)


/*
 * 	fsm_set_recall:
 *
 * 	Stores "recalls" a desired state and transition of a fsm.
 *
 * 	Arguments:
 *
 * 	'fsmd': fsm descriptor.
 *	'ps': 	pointer to state to be stored.
 */

void fsm_set_recall( FSMD_T fsmd, const STATE_T *ps, uchar evt );


/*
 * 	This macro clears the recall of a fsm.
 *
 * 	Arguments:
 *
 * 	'fsmd': fsm descriptor.
 */

#define fsm_clear_recall( fsmd )		fsm_set_recall(fsmd,NULL,0)


/*
 * 	fsm_get_info:
 *
 * 	Retrieves a pointer to FSM control block. This information provides 
 * 	a "snapshot" at a particular instant in time.
 *
 * 	Arguments:
 *
 * 	'fsmd': fsm descriptor.
 *
 * 	Returns:
 *
 * 	A pointer to FSM control block.
 */

FSM_T *fsm_get_info( FSMD_T fsmd );


/*
 * 	This macro retrieves the state id field of previously requested 
 * 	FSM control block. Thus, prior to use this macro the 'fsm_get_info' 
 * 	function must be called.
 *
 * 	Arguments:
 *
 * 	'pfsmd': pointer to FSM control block.
 *
 * 	Returns:
 *
 * 	Current state ID field.
 */

#define fsm_get_current_state_id( pfsm )		pfsm->state->state_id	


/*
 * 	This macro retrieves the stored state of previously requested FSM 
 * 	control block. Thus, prior to use this macro the 'fsm_get_info' 
 * 	function must be called.
 *
 * 	Arguments:
 *
 * 	'pfsmd': pointer to FSM control block.
 *
 * 	Returns:
 *
 * 	A pointer to current stored state.
 */

#define fsm_get_stored_state( pfsm )			pfsm->srecall	


/*
 * 	This macro retrieves the stored triggering event of previously requested 
 * 	FSM control block. Thus, prior to use this macro the 'fsm_get_info' 
 * 	function must be called.
 *
 * 	Arguments:
 *
 * 	'pfsmd': pointer to FSM control block.
 *
 * 	Returns:
 *
 * 	Current stored triggering event.
 */

#define fsm_get_stored_event( pfsm )			pfsm->erecall


#endif
