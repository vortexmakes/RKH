/*
 *	file: rkh.h
 *	Last updated for version: 1.0.00
 *	Date of the last update:  May 28, 2010
 *
 * 	Copyright (C) 2010 Leandro Francucci. All rights reserved.
 *
 * 	RKH is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License as published by
 * 	the Free Software Foundation, either version 3 of the License, or
 * 	(at your option) any later version.
 *
 *  RKH is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RKH, see copying.txt file.
 *
 * Contact information:
 * RKH web site:	http://
 * e-mail:			francuccilea@gmail.com
 */

/**
 * 	\file rkh.h
 *
 *	\brief
 * 	RKH platform-independent interface.
 *
 * 	This header file must be included in all modules (*.c files) that use RKH.
 */


#ifndef __RKH_H__
#define __RKH_H__


#include <stdlib.h>
#include "rkhitl.h"


/**
 * 	\brief 
 * 	Defines the data structure into which the collected performance 
 * 	information for state machine is stored.
 * 	
 * 	This member is optional, thus it could be declared as NULL or eliminated 
 * 	in compile-time with RKH_EN_SMA_GET_INFO.
 */

typedef struct rkh_smai_t
{
	rkhui16_t ndevt;			/**< # of dispatched events */
	rkhui16_t exectr;			/**< # of executed transitions */
} RKH_SMAI_T;


/**
 * 	\brief
 * 	Constant parameters of state machine.
 *
 *	The constant key parameters of a state machine are allocated within. 
 *	ROMRKH_T is a ROM base structure of RKH_T.
 *
 *	\sa
 *	RKH_T structure definition for more information. Also, \link RKHEVT_T 
 *	single inheritance in C \endlink.
 */

typedef struct romrkh_t
{
	/**
	 * 	\brief
	 * 	SMA priority. 
	 *
	 * 	A unique priority number must be assigned to each SMA from 0 to 
	 * 	RKH_LOWEST_PRIO. The lower the number, the higher the priority. 
	 */

	rkhui8_t prio;

	/**
 	 * 	\brief
	 * 	State machine properties. 
	 *
	 * 	The available properties are enumerated in RKH_HPPTY_T enumeration in 
	 * 	the rkh.h file.
	 */

	rkhui8 ppty;

	/**	
 	 * 	\brief
	 * 	Name of state machine application. 
	 *
	 * 	Represents the top state of state diagram. String terminated in '\\0' 
	 * 	that represents the name of state machine. When a particular user 
	 * 	application requires runtime debugging (native tracing features), 
	 * 	the option RKH_EN_SMA_NAME must be enabled.
	 */

#if RKH_EN_SMA_NAME	== 1
	const char *name;
#endif

	/** 
 	 * 	\brief
	 * 	Points to initial state. 
	 *
	 * 	This state could be defined either composite or basic 
	 * 	(not pseudo-state).
	 */

	rkhrom RKHSREG_T *istate;

	/** 
 	 * 	\brief
	 * 	Points to initializing action (optional). 
	 *
	 * 	The function prototype is defined as RKHINIT_T. This argument is 
	 * 	optional, thus it could be declared as NULL.
	 */

	RKHINIT_T iaction;

	/**
	 * 	\brief
	 *	Pointer to an event that will be passed to state machine application 
	 *	when it starts. Could be used to pass arguments to the state machine 
	 *	like an argc/argv. This argument is optional, thus it could be 
	 *	declared as NULL or eliminated in compile-time with RKH_EN_SMA_IEVENT.
	 */

#if RKH_EN_SMA_IEVENT == 1
	const RKHEVT_T ievent;
#endif
} ROMRKH_T;


/**
 * 	\brief 
 * 	Describes the SMA (active object in UML).
 *
 *	This structure resides in RAM because its members are dinamically updated
 *	by RKH (context of state machine).
 *	The \b #romrkh member points to ROMRKH_T structure, allocated in ROM, 
 *	to reduce the size of RAM consume. The key parameters of a state machine 
 *	are allocated within. Therefore cannot be modified in runtime.
 *
 * 	RKH_T is not intended to be instantiated directly, but rather
 * 	serves as the base structure for derivation of state machines in the
 * 	application code.
 * 	The following example illustrates how to derive an state machine from
 * 	RKH_T. Please note that the RKH_T member sm is defined as the
 * 	FIRST member of the derived struct.
 *
 *	Example:
 *	\code
 *	//	...within state-machine's module
 *
 *	typedef struct
 *	{
 *		RKHSMA_T sm;	// base structure
 *		rkhui8_t x;		// private member
 *		rkhui8_t y;		// private member
 *	} MYSM_T;
 *
 * 	//	static instance of SMA object
 *	RKH_SMA_CREATE( MYSM_T, my, HCAL, &S1, my_iaction, &my_ievent );
 *	\endcode
 *
 *	\sa
 *	RKH_T structure definition for more information. Also, \link RKHEVT_T 
 *	single inheritance in C \endlink.
 */

typedef struct rkhsma_t
{
	/**
 	 * 	\brief
	 * 	Points to state machine object.
	 */
	
	rkhrom ROMRKH_T *romrkh;

	/** 
 	 * 	\brief
	 * 	Points to current state.
	 */

	rkhrom RKHSREG_T *state;

	/**
	 * 	\brief
	 * 	OS-dependent thread of control of the SMA. 
	 * 	This member is optional, thus it could be declared as NULL or 
	 * 	eliminated in compile-time with RKH_EN_SMA_THREAD.
	 */

#if RKH_EN_SMA_THREAD == 1
	RKH_THREAD_TYPE thread;
#endif

	/**
	 * 	\brief
	 *	OS-dependent thread data.
	 * 	This member is optional, thus it could be declared as NULL or 
	 * 	eliminated in compile-time with RKH_EN_SMA_THREAD_DATA.
	 */

#if RKH_EN_SMA_THREAD == 1 && RKH_EN_SMA_THREAD_DATA == 1
	RKH_OSDATA_TYPE osdata;
#endif

	/**
	 * 	\brief
	 * 	Event queue of the SMA.
	 * 	It's OS-dependent.
	 */

	RKH_EQ_TYPE equeue;

	/**
	 * 	\brief
	 * 	The Boolean loop variable determining if the thread routine
	 * 	of the SMA is running.
	 */

	rkhui8_t running;

	/** 
 	 * 	\brief
	 * 	Performance information. This member is optional, thus it could be 
	 * 	declared as NULL or eliminated in compile-time with 
	 * 	RKH_EN_SMA_GET_INFO.
	 */

#if RKH_EN_SMA_GET_INFO == 1
	RKH_SMAI_T sinfo;
#endif	

} RKHSMA_T;


/**
 * 	Each condition connector can have one special branch with a guard 
 *	labeled ELSE, which is taken if all the guards on the other 
 *	branches are false.
 *
 * 	A guard function takes the state machine pointer and the event 
 * 	pointer as arguments. These parameters are optional in compile-time
 * 	according to RKH_EN_GRD_EVT_ARG and RKH_EN_GRD_HSM_ARG.
 */

#define ELSE		rkh_else


/**
 * 	\brief
 *	This macro creates a composite state.
 *
 *	\sa
 *	RKHSREG_T structure definition for more information.
 *
 * 	\param name		state name. Represents a composite state structure.
 * 	\param id		the value of state ID.	
 * 	\param en		pointer to state entry action. This argument is 
 *					optional, thus it could be declared as NULL.
 * 	\param ex		pointer to state exit action. This argument is 
 *					optional, thus it could be declared as NULL.
 * 	\param parent	pointer to parent state.
 * 	\param defchild	pointer to default child state or pseudostate.
 * 	\param history	pointer history pseudostate. This argument is 
 *					optional, thus it could be declared as NULL.
 */

#define RKH_CREATE_COMP_STATE( name,id,en,ex,parent,defchild,history )	\
																		\
								extern rkhrom RKHTR_T name##_trtbl[];	\
																		\
								rkhrom RKHSREG_T name =					\
								{										\
									mkbase(RKH_COMPOSITE,id,name),		\
									mkcomp(en,ex,parent,name,			\
												defchild,history)		\
								}


/**
 * 	\brief
 *	This macro creates a basic state.
 *
 *	\sa
 *	RKHSREG_T structure definition for more information.
 *
 * 	\param name		state name. Represents a basic state structure.
 * 	\param id		the value of state ID.	
 * 	\param en		pointer to state entry action. This argument is 
 *					optional, thus it could be declared as NULL.
 * 	\param ex		pointer to state exit action. This argument is 
 *					optional, thus it could be declared as NULL.
 * 	\param parent	pointer to parent state.
 * 	\param prepro	pointer to input preprocessor function. This argument is 
 *					optional, thus it could be declared as NULL.
 *					Aditionally, by means of single inheritance in C it 
 *					could be used as state's abstract data. 
 *					Aditionally, implementing the single inheritance in C 
 *					is very simply by literally embedding the base type, 
 *					RKHPPRO_T in this case, as the first member of the 
 *					derived structure. See \a prepro member of RKHSREG_T 
 *					structure for more information.
 */

#define RKH_CREATE_BASIC_STATE( name,id,en,ex,parent,prepro )			\
																		\
								extern rkhrom RKHTR_T name##_trtbl[];	\
																		\
								rkhrom RKHSREG_T name =					\
								{										\
									mkbase(RKH_BASIC,id,name),			\
									mkbasic(en,ex,parent,name,prepro)	\
								}

/**
 * 	\brief
 *	This macro creates a conditional pseudostate. 
 *
 *	A condition connector has one incoming transition and can have several 
 *	outgoing transition segments called branches. Branches are labeled with 
 *	guards that determine which one is to be actually taken. 
 *	Since the condition connector is an OR connector, only one of the branches 
 *	can be taken. Each condition connector can have one special branch with 
 *	a guard labeled rkh_else, which is taken if all the guards on the other 
 *	branches are false. 
 *	Branches cannot contain triggers, but in addition to a guard they may 
 *	contain actions. A branch can enter another condition connector, thus 
 *	providing for the nesting of branches.
 *	
 *	\sa
 *	RKHSCOND_T structure definition for more information.
 *
 * 	\param name		pseudostate name. Represents a conditional pseudostate 
 * 					structure.
 * 	\param id		the value of state ID.	
 */

#define RKH_CREATE_COND_STATE( name,id )								\
																		\
								extern rkhrom RKHTR_T name##_trtbl[];	\
																		\
								rkhrom RKHSCOND_T name =				\
								{										\
									mkbase(RKH_CONDITIONAL,id,name),	\
									name##_trtbl 						\
								}


/**
 * 	\brief
 *	This macro creates a junction pseudostate.
 *
 *	Transitions arrows can be joined using junction pseudostate. 
 *	Multiple entrances and exits may be attached to a junction.
 *
 *	\sa
 *	RKHSJUNC_T structure definition for more information.
 *
 * 	\param name		pseudostate name. Represents a junction pseudostate 
 * 					structure.
 * 	\param id		the value of state ID.	
 * 	\param action	pointer to transition action. This argument is optional, 
 * 					thus it could be declared as NULL.
 * 	\param target	pointer to target state.
 */

#define RKH_CREATE_JUNCTION_STATE( name,id,action,target )				\
																		\
								rkhrom RKHSJUNC_T name =				\
								{										\
									mkbase(RKH_JUNCTION,id,name),		\
									action,	target 						\
								}


/**
 * 	\brief
 *	This macro creates a deep history pseudostate. 
 *
 *	Deep history applies downwards to all levels of nesting.
 *
 *	\sa
 *	RKHSHIST_T structure definition for more information.
 *
 *	Arguments:
 *
 * 	\param name		pseudostate name. Represents a deep history 
 * 					pseudostate structure.
 * 	\param id		the value of state ID.	
 * 	\param parent	pointer to parent state.
 */

#define RKH_CREATE_DEEP_HISTORY_STATE( name,id,parent )					\
																		\
								static rkhrom RKHSREG_T *ram##name;		\
																		\
								rkhrom RKHSHIST_T name =				\
								{										\
									mkbase(RKH_DHISTORY,id,name),		\
									parent,&ram##name 					\
								}


/**
 * 	\brief
 *	This macro creates a shallow history pseudostate. 
 *
 *	Shallow history means that history applies to the current nesting context 
 *	only – states nested more deeply are not affected by the 
 *	presence of a history pseudostates in a higher context.
 *	
 *	\sa
 *	RKHSHIST_T structure definition for more information.
 *
 * 	\param name		pseudostate name. Represents a shallow history pseudostate 
 * 					structure.
 * 	\param id		the value of state ID.	
 * 	\param parent	pointer to parent state.
 */

#define RKH_CREATE_SHALLOW_HISTORY_STATE( name,id,parent )				\
																		\
								static rkhrom RKHSREG_T *ram##name;		\
																		\
								rkhrom RKHSHIST_T name =				\
								{										\
									mkbase(RKH_SHISTORY,id,name),		\
									parent,&ram##name 					\
								}


/**
 * 	\brief
 *	This macro creates a state transition table. This table have the general 
 *	structure shown below:
 *	\code
 *	RKH_CREATE_TRANS_TABLE( state_name )		// transition table begin
 *		RKH_TRxx( ... )							// transition
 *		RKH_TRxx( ... )							// transition
 *		...
 *	RKH_END_TRANS_TABLE							// transition table end
 *	\endcode
 *
 * 	Each transition table always begins with the macro RKH_CREATE_TRANS_TABLE() 
 * 	and ends with the macro RKH_END_TRANS_TABLE().
 *	As noted above, sandwiched between these macros are the transitions macros 
 *	that actually represent behavior of state.
 *
 *	\sa
 *	This macro is not terminated with the semicolon.
 *
 * 	\param name		state name.
 */

#define RKH_CREATE_TRANS_TABLE( name )									\
																		\
								static rkhrom RKHTR_T name##_trtbl[]={


/**
 * 	\brief
 *	This macro defines a regular state transition.
 *	The general syntax of an expression labelling a transition in a 
 *	statechart is \e "i[c]/a" where \e i is the input that triggers the 
 *	transition, \e c is a condition that guards the transition from being 
 *	taken unless it is true when \e i occurs, and \e a is an action that 
 *	is carried out if and when the transition is taken. All of these parts 
 *	are optional.
 *
 *	Example:
 *	\code
 *	RKH_TRREG( 	TOUT0, 				// triggering event
 *				is_full, 			// guard function
 *				drop_frame, 		// action function
 *				&WAIT_SYNC )		// next state
 *	\endcode
 *
 *	\sa
 *	RKHTR_T structure definition for more information.
 *
 * 	\param e		triggering event.
 * 	\param g		pointer to guard function. This argument is 
 *					optional, thus it could be declared as NULL.
 * 	\param a		pointer to action function. This argument is 
 *					optional, thus it could be declared as NULL.
 * 	\param t		pointer to target state.
 */

#define RKH_TRREG( e, g, a, t )	{ e, g, a, t }


/**
 * 	\brief
 *	This macro defines an internal state transition.
 *	Internal transitions are simple reactions to events that never lead 
 *	to change of state and consequently never cause execution of exit 
 *	actions, entry actions, or initial transitions.
 *
 *	Example:
 *	\code
 *	RKH_TRINT( 	RCV_DATA, 			// triggering event
 *				is_sync, 			// guard function
 *				store_data ) 		// action function
 *	\endcode
 *	\sa
 *	RKHTR_T structure definition for more information.
 *
 * 	\param e		triggering event.
 * 	\param g		pointer to guard function.	
 * 	\param a		pointer to action function.
 */

#define RKH_TRINT( e, g, a )	{ e, g, a, NULL }


/*
 * 	This macro is internal to RKH and the user application should 
 * 	not call it.
 */

#define RKH_ETRTBL				{ RKH_ANY, NULL, NULL, NULL }


/**
 * 	\brief
 *	This macro is used to terminate a state transition table.
 *	This table have the general structure shown below:
 *	\code
 *	RKH_CREATE_TRANS_TABLE( state_name )		// transition table begin
 *		RKH_TRxx( ... )							// transition
 *		RKH_TRxx( ... )							// transition
 *		...
 *	RKH_END_TRANS_TABLE							// transition table end
 *	\endcode
 *
 * 	Each transition table always begins with the macro RKH_CREATE_TRANS_TABLE() 
 * 	and ends with the macro RKH_END_TRANS_TABLE().
 *	As noted above, sandwiched between these macros are the transitions macros 
 *	that actually represent behavior of state.
 *
 *	\sa
 *	This macro is not terminated with the semicolon.
 */

#define RKH_END_TRANS_TABLE		RKH_ETRTBL};


/**
 *	This macro creates a branch table. This table have the general 
 *	structure shown below:
 *	\code
 *	RKH_CREATE_BRANCH_TABLE( ps_name )			// branch table begin
 *		RKH_BRANCH( ... )						// branch
 *		RKH_BRANCH( ... )						// branch
 *		...
 *	RKH_END_BRANCH_TABLE						// branch table end
 *	\endcode
 *
 * 	Each branch table always begins with the macro RKH_CREATE_BRANCH_TABLE() 
 * 	and ends with the macro RKH_END_BRANCH_TABLE().
 * 	In RKH branches are defined by the macro RKH_BRANCH().
 *
 *	\sa
 *	This macro is not terminated with the semicolon. 
 *	Use rkh_else() when if all the guards on the other branches are false.
 *
 * 	\param name		conditional pseudostate name.
 */

#define RKH_CREATE_BRANCH_TABLE( name )								\
																	\
								RKH_CREATE_TRANS_TABLE( name )


/**
 * 	\brief
 *	This macro defines a branch in the branch table. 
 *
 *	Each condition connector can have one special branch with a guard 
 *	labeled rkh_else, which is taken if all the guards on the other 
 *	branches are false.
 *	The general syntax of an expression labelling a branch in a statechart is
 *	\e "[c]/a" where \e c is a condition that guards the transition from 
 *	being taken unless it is true, and \e a is an action that is carried out 
 *	if and when the transition is taken. All of these parts are optional. 
 *	
 *	Example:
 *	\code
 *	RKH_CREATE_BRANCH_TABLE( C1 )
 *		RKH_BRANCH( power_ok, 	enable_process,	&S22	),
 *		RKH_BRANCH( ELSE, 		abort,			&S4 	),
 *		RKH_END_BRANCH_TABLE
 *	\endcode
 *
 *	\sa
 *	RKHTR_T structure definition for more information.
 *
 * 	\param g		branch guard. Branches are labeled with guards that 
 * 					determine which one is to be actually taken. Use rkh_else
 * 					when if all the guards on the other branches are false.
 * 	\param a		pointer to action function. This argument is 
 *					optional, thus it could be declared as NULL.
 * 	\param t		pointer to target state.
 */

#define RKH_BRANCH( g, a, t )	{ 0, g, a, t }


/*
 * 	This macro is internal to RKH and the user application should 
 * 	not call it.
 */

#define RKH_EBTBL				{ RKH_ANY, NULL, NULL, NULL }


/**
 * 	\brief
 *	This macro is used to terminate a state transition table.
 *	This table have the general structure shown below:
 *	\code
 *	RKH_CREATE_BRANCH_TABLE( ps_name )			// branch table begin
 *		RKH_BRANCH( ... )						// branch
 *		RKH_BRANCH( ... )						// branch
 *		...
 *	RKH_END_BRANCH_TABLE						// branch table end
 *	\endcode
 *
 * 	Each branch table always begins with the macro RKH_CREATE_BRANCH_TABLE() 
 * 	and ends with the macro RKH_END_BRANCH_TABLE().
 *
 *	\sa
 *	This macro is not terminated with the semicolon. 
 */

#define RKH_END_BRANCH_TABLE	RKH_EBTBL};


/**
 * 	\brief
 *	This macro indicates the root state of a state machine.
 */

#define RKH_ROOT				NULL


/**
 * 	\brief
 * 	This macro declares a opaque pointer to previously created state machine 
 * 	to be used as a global object. 
 *
 * 	This global pointer represent the state machine in the application. 
 * 	The state machine pointers are "opaque" because they cannot access the 
 * 	whole state machine structure, but only the part inherited from the 
 * 	RKHSMA_T structure. The power of an "opaque" pointer is that it allows to 
 * 	completely hide the definition of the state machine structure and make 
 * 	it inaccessible to the rest of the application. 
 *	
 *	\note
 * 	Generally, this macro is used in the SMA's header file.
 * 	
 * 	\sa
 * 	RKH_SMA_CREATE().
 * 	
 * 	\param sma		pointer to previously created state machine application.
 */

#define RKH_SMA_DCLR_HSM( sma )		extern RKHSMA_T *const sma


/**@{
 *
 * 	Declares a previously created state/pseudostate to be used 
 * 	as a global object.  
 *
 * 	\note
 * 	Generally, this macro is used in the state-machine's header file.
 */

#define RKH_DCLR_COMP_STATE		extern rkhrom RKHSREG_T
#define RKH_DCLR_BASIC_STATE	extern rkhrom RKHSREG_T
#define RKH_DCLR_COND_STATE		extern rkhrom RKHSCOND_T
#define RKH_DCLR_JUNC_STATE		extern rkhrom RKHSJUNC_T
#define RKH_DCLR_DHIST_STATE	extern rkhrom RKHSHIST_T 
#define RKH_DCLR_SHIST_STATE	extern rkhrom RKHSHIST_T

/*@}*/


/**
 * 	\brief
 * 	Declares a previously created SMA to be used as a global object.  
 *
 *	Example:
 *	\code
 *	//	g_my: global pointer to SMA "my".
 *	RKH_DCLR_SM_GLOBAL( MYSM_T, my, g_my );
 *	\endcode
 *
 *	\sa
 *	RKHSMA_T structure definition for more information. Also, \link RKHEVT_T 
 *	single inheritance in C \endlink.
 *
 * 	\param sma_t		data type of SMA.
 * 	\param sm			name of previously created SMA.
 * 	\param gob			name of global object.
 *
 * 	\note
 * 	Generally, this macro is used in the state-machine's module.
 */

#define RKH_DCLR_SM_GLOBAL( sma_t, sm, gob )				\
															\
							sma_t * const gob = &s_##sm;


/** 	
 *  Return codes from rkh_engine() function.
 */

typedef enum
{
	/**
	 * 	The arrived event was succesfully processed and HSM 
	 * 	resides in a allowed state.
	 */

	RKH_OK,

	/**
	 * 	The arrived event was't founded in the transition table. 
	 */

	RKH_INPUT_NOT_FOUND,

	/**
	 * 	The branch function returned a value not founded 
	 * 	in the branch table.
	 */

	RKH_CONDITION_NOT_FOUND,

	/**
	 * 	The transition was cancelled by guard function.
	 */

	RKH_GUARD_FALSE,

	/**
	 * 	Unknown state. 
	 */

	RKH_UNKNOWN_STATE,

	/**
	 * 	The transition exceeded the allowed hierarchical level.
	 */

	RKH_EXCEED_HCAL_LEVEL,

	/**
	 * 	The transition exceeded the allowed number of segments 
	 * 	within a compound transtion.
	 */

	RKH_EXCEED_TR_SEGS,

	/** Number of returned codes */
	RKH_NUM_CODES
} RKH_RCODE_T;


/** 	
 * 	\brief
 *  State machine properties.
 */

typedef enum
{
	/**
	 * 	Used as state machine property.
	 * 	This macro enables state nesting in a particular state machine.
	 */

	HCAL,


	/**
	 * 	Used as state machine property.
	 * 	This macro disables state nesting in a particular state machine.
	 * 	When FLAT is used in RKH_CREATE_HSM() macro some important features of 
	 * 	RKH are	not included: state nesting, composite state, history 
	 * 	(shallow and deep) pseudostate, entry action, and exit action.
	 */

	FLAT,

	/** Number of state machines properties */
	RKH_NUM_HPPTY
} RKH_HPPTY_T;


/**
 * 	\brief
 * 	This values are retrived by guard functions. 
 *
 * 	A guard is a boolean condition that returns a TRUE or FALSE value that 
 * 	controls whether or not a transition is taken following the receipt of 
 * 	a triggering event.
 */

typedef enum
{
	RKH_GFALSE,	/**< False condition */
	RKH_GTRUE	/**< True condition */
} RKH_GRET_T;


/**
 * 	\brief
 * 	Initializes the RKH framework. 
 * 	A requirement of RKH is that must be called rkh_init() before call any 
 * 	of its other services. This function initializes all of RKH's variables 
 * 	and data structures.
 */

void rkh_init( void );


/**
 * 	\brief
 * 	RKH is started.
 * 	This entry function turns over control to RKH (and does not return!).
 * 	This function runs the highest priority state machine application (SMA) 
 * 	that is ready to run in run-to-completation model. 
 *
 * 	\note 
 * 	The call to this function does not return. Hence, any code after it will 
 * 	never be executed.
 * 	
 * 	\note 
 * 	This function is strongly platform-dependent. All RKH ports must implement 
 * 	rkh_enter().
 */

void rkh_enter( void );


/**
 * 	\brief	
 * 	Exit the RKH framework.
 * 	Function invoked by the application layer to exit the RKH application and 
 * 	return control to the underlying OS/Kernel.
 *
 * 	\note 
 *	This function is strongly platform-dependent. All RKH ports and must be 
 *	defined in the RKH port to a particular platform. 
 *	Some RKH ports might not require implementing this function at all, 
 *	because many embedded applications don't have anything to exit to.
 */

void rkh_exit( void );


/**
 * 	\brief
 * 	Initialize a previously created state machine application.
 *
 * 	A state machine application (SMA) is declared with the RKHSMA_T data type 
 * 	and is defined with the rkh_sma_create() service.
 *
 *	Example:
 *	\code
 *	//	...within state-machine's module
 *
 *	typedef struct
 *	{
 *		RKHSMA_T sm;	// base structure
 *		rkhui8_t x;		// private member
 *		rkhui8_t y;		// private member
 *	} MYSM_T;
 *
 * 	//	static instance of SMA object
 *	RKH_SMA_CREATE( MYSM_T, my, HCAL, &S1, my_iaction, &my_ievent );
 *
 *	void
 *	main( void )
 *	{
 *		// ...
 *		rkh_sma_init( my, 4, qsto, sizeof( RKHEVT_T* ), (void*)0, 0 );
 *		// ...
 *	}
 *	\endcode
 * 	
 *	\note 
 *	This function is strongly platform-dependent. All RKH ports and must be 
 *	defined in the RKH port to a particular platform.
 *
 * 	\param sma			pointer to previously created state machine 
 * 						application.
 * 	\param qs			base address of the event storage area. A message 
 * 						storage area is declared as an array of pointers to 
 * 						voids.
 * 	\param qsize		size of the storage event area [in number of entries].
 * 	\param stks			starting address of the stack's memory area.
 * 	\param stksize		size of stack memory area [in bytes].
 */

void rkh_sma_init(	RKHSMA_T *sma, const void **qs, RKH_RQNE_T qsize, 
					void *stks, rkhui32_t stksize );


/**
 * 	\brief
 * 	Declare and allocate a SMA (active object) derived from RKHSMA_T, 
 * 	initialize and assign a state machine to previously declared SMA.
 *
 * 	In the UML specification, every state machine has a top state 
 * 	(the abstract root of every state machine hierarchy), which contains 
 * 	all the other elements of the entire state machine. RKH provides the 
 * 	top state using the macro RKH_SMA_CREATE().
 *	Frequently, RKH_SMA_CREATE() is used within state-machine's module 
 *	(.c file), thus the structure definition is in fact entirely encapsulated 
 *	in its module and is inaccessible to the rest of the application. 
 *	However, use the RKH_SMA_DCLR_HSM() macro to declare a "opaque" pointer 
 *	to that state machine structure to be used in the rest of the application
 *	but hiding the proper definition.
 * 	RKHSMA_T is not intended to be instantiated directly, but rather
 * 	serves as the base structure for derivation of state machines in the
 * 	application code.
 * 	The following example illustrates how to derive an state machine from
 * 	RKHSMA_T. Please note that the RKHSMA_T member sm is defined as the
 * 	FIRST member of the derived structure.
 *
 *	Example:
 *	\code
 *	//	...within state-machine's module
 *
 *	typedef struct
 *	{
 *		RKHSMA_T sm;	// base structure
 *		rkhui8_t x;		// private member
 *		rkhui8_t y;		// private member
 *	} MYSM_T;
 *
 * 	//	static instance of SMA object
 *	RKH_SMA_CREATE( MYSM_T, my, HCAL, &S1, my_iaction, &my_ievent );
 *	\endcode
 *
 * 	\param sma			pointer to previously created state machine 
 * 						application.
 * 	\param name			name of state machine application. Represents the top 
 * 						state of state diagram. String terminated in '\\0' that 
 * 						represents the name of state machine. When a particular 
 * 						user application requires runtime debugging (native 
 * 						tracing features), the option RKH_EN_SMA_NAME must be 
 * 						enabled.
 * 	\param prio			state machine application priority. A unique priority 
 * 						number must be assigned to each SMA from 0 to 
 * 						RKH_LOWEST_PRIO. The lower the number, the higher the 
 * 						priority. 
 * 	\param ppty			state machine properties. The available properties are
 * 						enumerated in RKH_HPPTY_T enumeration in the rkh.h file.
 * 	\param istate		pointer to initial state. This state could be defined 
 * 						either composite or basic (not pseudo-state).
 * 	\param iaction		pointer to initialization action (optional). The function 
 * 						prototype is defined as RKHINIT_T. This argument is 
 * 						optional, thus it could be declared as NULL.
 * 	\param ievent		pointer to an event that will be passed to state 
 * 						machine application when it starts. Could be used to 
 * 						pass arguments to the state machine like an argc/argv.
 */

#define RKH_SMA_CREATE( sma_t, name, prio, ppty, istate, iaction, ievent )	\
																			\
	static rkhrom ROMRKH_T rs_##name = MKRRKH( 	(prio), (ppty), (name), 	\
												(istate), (iaction), 		\
												(ievent) );					\
	static sma_t s_##name = MKSMA( &rs_##name,(istate) );					\
	RKHSMA_T *const name = ( RKHSMA_T* )&s_##name


/**
 * 	\brief
 * 	Terminate a state machine application. 
 * 	A state machine application may call this service to terminate itself. Once 
 * 	terminated, the state machine application must be re-created in order for 
 * 	it to execute again.
 * 	
 *	\note 
 *	This function is strongly platform-dependent. All RKH ports and must be 
 *	defined in the RKH port to a particular platform.
 *
 * 	\param sma			pointer to previously created state machine 
 * 						application.
 */

void rkh_sma_terminate( RKHSMA_T *sma );


/**
 * 	\brief
 * 	Retrieves performance information for a particular state machine 
 * 	application. 
 *	The user application must allocate an RKH_SMAI_T data structure used to 
 *	receive data. The performance information is available during run-time 
 *	for each of the RKH services. This can be useful in determining whether 
 *	the application is performing properly, as well as helping to optimize the 
 *	application.
 *	This information provides a "snapshot" a particular instant in time, i.e., 
 *	when the service is invoked.
 *
 * 	\note
 * 	See RKH_SMAI_T structure for more information. This function is 
 * 	optional, thus it could be eliminated in compile-time with 
 * 	RKH_EN_SMA_GET_INFO.
 *
 * 	\param sma		pointer to previously created state machine application.
 * 	\param psi		pointer to the buffer into which the performance 
 * 					information will be copied by reference.
 */

void rkh_sma_get_info( RKHSMA_T *sma, RKH_SMAI_T *psi );


/**
 * 	\brief
 * 	Clear performance information for a particular state machine application.
 *
 * 	\note
 * 	This function is optional, thus it could be eliminated in compile-time 
 * 	with RKH_EN_SMA_GET_INFO.
 *
 * 	\param sma		pointer to previously created state machine application.
 */

void rkh_sma_clear_info( RKHSMA_T *sma );


/**
 * 	\brief
 * 	Send an event to a state machine application through a queue using the 
 * 	FIFO policy. 
 * 	A message is a pointer size variable and its use is application specific. 
 *
 * 	\note 
 *	For memory efficiency and best performance the SMA's event queue, 
 *	STORE ONLY POINTERS to events, not the whole event objects.
 *	At this time, this functions are required only when the user 
 *	application is used dynamic event (RKH_EN_DYNAMIC_EVENT == 1).
 *	The assertion inside it guarantee that the pointer is valid, so is not 
 *	necessary to check the pointer returned from rkh_sma_post_fifo().
 *
 *	\note 
 *	This function is strongly platform-dependent. All RKH ports and must be 
 *	defined in the RKH port to a particular platform.
 *
 * 	\param sma		pointer to previously created state machine application.
 * 	\param e		actual event sent to the state machine application.
 */

void rkh_sma_post_fifo( RKHSMA_T *sma, const RKHEVT_T *e );


/**
 * 	\brief
 * 	Send an event to a state machine application through a queue using the 
 * 	LIFO policy. 
 * 	A message is a pointer size variable and its use is application specific. 
 *
 * 	\note
 *	For memory efficiency and best performance the SMA's event queue, 
 *	STORE ONLY POINTERS to events, not the whole event objects.
 *	At this time, this functions are required only when the user 
 *	application is used dynamic event (RKH_EN_DYNAMIC_EVENT == 1).
 *	The assertion inside it guarantee that the pointer is valid, so is not 
 *	necessary to check the pointer returned from rkh_sma_post_lifo().
 *
 *	\note 
 *	This function is strongly platform-dependent. All RKH ports and must be 
 *	defined in the RKH port to a particular platform.
 *
 * 	\param sma		pointer to previously created state machine application.
 * 	\param e		actual event sent to the state machine application.
 */

void rkh_sma_post_lifo( RKHSMA_T *sma, const RKHEVT_T *e );


/**
 * 	\brief
 * 	Get an event from the event queue of an state machine application. 
 * 	The events received are pointer size variables and their use is 
 * 	application specific.
 *
 *	\note 
 *	This function is strongly platform-dependent. All RKH ports and must be 
 *	defined in the RKH port to a particular platform.
 *	Depending on the underlying OS or kernel, if no event is present at the 
 *	queue, the function will block the current thread until an event is 
 *	received.
 *
 *	\return
 * 	'0' if an element was successfully removed from the queue, otherwise 
 * 	error code.
 */

HUInt rkh_sma_get( RKHSMA_T *sma, RKHEVT_T *e );


/**
 * 	\brief
 *	Defer an event to a given separate event queue.
 *
 * 	Event deferral comes in very handy when an event arrives in a 
 * 	particularly inconvenient moment but can be deferred for some later time, 
 * 	when the system is in a much better position to handle the event. RKH 
 * 	supports very efficient event deferring and recalling mechanisms.
 * 	This function is part of the event deferral mechanism. An SMA 
 * 	uses this function to defer an event \a e to the event queue \a q. 
 * 	RKH correctly accounts for another outstanding reference to the event 
 * 	and will not recycle the event at the end of the RTC step. 
 * 	Later, the SMA might recall one event at a time from the 
 * 	event queue by means of rkh_recall() function.
 *	
 *	\note
 *	For memory efficiency and best performance the deferred event queue, 
 *	STORE ONLY POINTERS to events, not the whole event objects.
 *  An SMA can use multiple event queues to defer events of
 *  different kinds.
 *	The assertion inside it guarantee that operation is valid, so is not 
 *	necessary to check the value returned from it.
 *
 * 	\param sma		pointer to previously created state machine application.
 * 	\param q		pointer to previously created queue.
 * 	\param e		pointer to event.
 */

void rkh_defer( RKHSMA_T *sma, RKHRQ_T *q, const RKHEVT_T *e );


/**
 * 	\brief
 * 	Recall a deferred event from a given event queue.
 *
 * 	This function is part of the event deferral support. An SMA 
 * 	uses this function to recall a deferred event from a given event queue. 
 * 	Recalling an event means that it is removed from the deferred event 
 * 	queue \a q and posted (LIFO) to the event queue of the \a sma state 
 * 	machine application.
 *
 * 	\note
 *	For memory efficiency and best performance the destination event queue, 
 *	STORE ONLY POINTERS to events, not the whole event objects.
 *
 * 	\returns 
 * 	The pointer to the recalled event to the caller, or NULL if no 
 * 	event has been recalled.
 */

RKHEVT_T *rkh_recall( RKHSMA_T *sma, RKHRQ_T *q );


/**
 * 	\brief
 *	This macro dynamically creates a new event of type \a et with its signal.
 *
 *	The basic policy is to allocate the event from the first pool that has a 
 *	block size big enough to fit the requested event size. RKH can manage up 
 *	to three event pools (e.g., small, medium, and large events, like shirt 
 *	sizes). It returns a pointer to the event already cast to the event type 
 *	(et*). Here is an example of dynamic event allocation with the macro 
 *	RKH_ALLOC_EVENT():
 *
 *	\code
 *	MYEVT_T *mye = RKH_ALLOC_EVENT( MYEVT_T, DATA );
 *	mye->y = mye->x = 0;
 *	...
 *	\endcode
 *
 * 	\note
 *	The assertions inside rkh_ae() function guarantee that the pointer is 
 *	valid, so you don't need to check the pointer returned from rkh_ae(), 
 *	unlike the value returned from malloc(), which you should check.
 *
 * 	\param et		type of event.
 * 	\param e		event signal.
 */

#define RKH_ALLOC_EVENT( et, e )										\
								(et*)rkh_ae(sizeof(et),(RKHE_T)(e))


/**
 * 	\brief
 * 	Recycle a dynamic event.
 *
 * 	This function implements a simple garbage collector for the dynamic 
 * 	events.	Only dynamic events are candidates for recycling. (A dynamic 
 * 	event is one that is allocated from an event pool, which is determined 
 * 	as non-zero	e->dynamic_ attribute.) Next, the function decrements the 
 * 	reference counter of the event, and recycles the event only if the 
 * 	counter drops to zero (meaning that no more references are outstanding 
 * 	for this event). The dynamic event is recycled by returning it to the 
 * 	pool from which	it was originally allocated. The pool-of-origin 
 * 	information is stored in the e->pool member.
 * 	
 * 	\note 
 * 	The garbage collector must be explicitly invoked at all appropriate 
 * 	contexts, when an event can become garbage (automatic garbage collection).
 *
 * 	\param e		pointer to event to be potentially recycled.
 */

void rkh_gc( RKHEVT_T *e );


/**
 * 	\brief
 *	This macro initialize an event \a e with \a es signal and establishes 
 *	it as one static event.
 *
 *	\sa
 *	RKH_DCLR_STATIC_EVENT() macro.
 *
 *	Example:
 *	\code
 *	...
 *	RKHEVT_T e;
 *
 *	RKH_SET_STATIC_EVENT( &e, TOUT );
 *	\endcode
 *
 * 	\param e		pointer to event structure derived from RKHEVT_T.
 * 	\param es		event signal. The RKH takes this value for triggering 
 * 					a state transition.
 *
 * 	\returns
 */

#define RKH_SET_STATIC_EVENT( e, es )					\
										mksevt( e, es )


/**
 * 	\brief
 *	This macro declares and initializes the event structure \a e with \a es 
 *	signal and establishes it as one static event. The created event object 
 *	is explicitly placed in ROM.
 *
 *	Example:
 *	\code
 *	...
 *	static RKH_DCLR_STATIC_EVENT( etimer, RPC_TIMER_RET );
 *	...
 *	void
 *	offhook( void )
 *	{
 *		...
 *		rkh_put_fifo( qphone, &etimer );
 *	}
 *	\endcode
 *
 * 	\param e		name of event structure (RKHEVT_T).
 * 	\param es		event signal. The RKH takes this value for triggering 
 * 					a state transition.
 */

#define RKH_DCLR_STATIC_EVENT( e, es )					\
										mkievt( e, es )


/**
 * 	\brief
 * 	Inits a previously created state machine calling its initializing action.
 *
 * 	\param sma		pointer to previously created state machine application.
 */

void rkh_init_hsm( RKHSMA_T *sma );


/**
 * 	\brief
 *	Executes a state machine in a non-preemtive model. 
 *
 *	In this model, before the system handles a new event it can store it 
 *	until the previous event has completed processing. This model is 
 *	called run to completion or RTC. Thus, the system processes events in 
 *	discrete, indivisible RTC steps.
 *
 * 	\param sma		pointer to previously created state machine application.
 *	\param e		pointer to arrived event. It's used as state-machine's 
 *					input alphabet.
 *
 *	\return
 *	Result RKH_RCODE_T code.
 */

HUInt rkh_engine( RKHSMA_T *sma, RKHEVT_T *e );


/**
 * 	\brief
 * 	This macro retrieves the state ID of SMA.
 *
 * 	\param sma		pointer to previously created state machine application.
 *
 * 	\return
 * 	Id of current state.
 */

#define rkh_get_cstate_id( sma )									\
								((RKHBASE_T*)((sma)->state))->id	


/**	
 * 	\brief
 * 	This macro retrieves the current state name of SMA.
 *
 * 	\param sma		pointer to previously created state machine application.
 *
 * 	\returns
 * 	Name of current state.
 */

#define rkh_get_cstate_name( sma )									\
								((RKHBASE_T*)((sma)->state))->name	


/**	
 * 	\brief
 * 	This macro retrieves the SMA's name.
 *
 * 	\param sma		pointer to previously created state machine application.
 *
 * 	\returns
 * 	Name of state machine.
 */

#define rkh_get_sm_name( sma )						\
								(sma)->romrkh->name


/**	
 * 	\brief
 * 	This macro retrieves the state's abstract data.
 *
 *	Aditionally, by means of single inheritance in C it could be used 
 *	as state's abstract data. Aditionally, implementing the single 
 *	inheritance in C is very simply by literally embedding the base type, 
 *	#RKHPPRO_T in this case, as the first member of the derived structure. 
 *	See member \a prepro of RKHSREG_T structure for more information.
 *
 * 	\param sma		pointer to previously created state machine application.
 *
 * 	\returns
 * 	Pointer to state's abstract data.
 */

#define rkh_get_sdata( sma )							\
								((sma)->state->sdata)	


/**
 * 	\brief
 * 	Erase the history of a state. It can be a shallow or deep history.
 *
 * 	\param h 		pointer to history pseudostate.
 */

void rkh_clear_history( rkhrom RKHSHIST_T *h );


#endif
