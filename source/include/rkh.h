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
 * 	\brief
 *
 * 	RKH engine interface.
 *
 * 	This header file is directly included in RKH interface 
 * 	file, rkhsm.h.
 */


#ifndef __RKH_H__
#define __RKH_H__


/**	
 *  Application specific configuration options.
 */

#include "rkhcfg.h"


/** 
 * 	Specific definitions to the platform being used.
 */

#include "rkhplat.h"


/** 
 * 	Identification numbers of declared state-machines.
 */

#include "rkhdata.h"


/** 
 * 	Trace facility.
 */

#include "rkhtrace.h"


/**	
 *	Version string of RKH.
 */

#define RKH_VERSION					"0.0.26"


/**	
 *	This macro is used to indicate the end of a transition table.
 */

#define RKH_ANY						((RKHE_T)(-1))


/* 	
 *  Verifies port file from rkhport.h included in rkhplat.h.
 */

#ifndef rkhrom
#error "rkhport.h, Missing rkhrom: Qualifier for ROM data storage. \
	See Porting chapter in readme file for more information"
#endif


/* 	
 *  Verifies configurations from rkhcfg.h include file.
 */

#if RKH_TRACE == 1
	#if RKH_EN_TRACE_STRING == 1 && ( RKH_EN_STATE_NAME != 1 || RKH_EN_HSM_NAME != 1 )
	#error  "rkhcfg.h, When enabling RKH_TRACE and RKH_EN_TRACE_STRING is set to one (1), must be set to one (1) both RKH_EN_STATE_NAME or RKH_EN_HSM_NAME"
	#endif
#endif

#ifndef RKH_MAX_HCAL_DEPTH
#error "rkhcfg.h, Missing RKH_MAX_HCAL_DEPTH: Max. # of hierarchical levels"
#else
	#if RKH_MAX_HCAL_DEPTH == 0 || RKH_MAX_HCAL_DEPTH > 8
	#error  "rkhcfg.h, RKH_MAX_HCAL_DEPTH must be > 0 and <= 8"
	#endif
#endif


#ifndef RKH_MAX_TR_SEGS
#error "rkhcfg.h, Missing RKH_MAX_TR_SEGS: Max. # of transition segments"
#else
	#if RKH_MAX_TR_SEGS == 0 || RKH_MAX_TR_SEGS > 8
	#error  "rkhcfg.h, RKH_MAX_TR_SEGS must be > 0 and <= 8"
	#endif
#endif


/*
 * 	The following macros and constants are internal to RKH and 
 * 	the user application should not call it.
 */

#define RKH_REGULAR						0x80
#define RKH_PSEUDO						0
#define RKH_TYPE(t,i)					(t|i)

#define RKH_BASIC						RKH_TYPE( RKH_REGULAR, 	0	 )
#define RKH_COMPOSITE					RKH_TYPE( RKH_REGULAR, 	0x01 )	
#define RKH_CONDITIONAL					RKH_TYPE( RKH_PSEUDO, 	0x02 )	
#define RKH_JUNCTION					RKH_TYPE( RKH_PSEUDO, 	0x04 )	
#define RKH_SHISTORY					RKH_TYPE( RKH_PSEUDO, 	0x08 )	
#define RKH_DHISTORY					RKH_TYPE( RKH_PSEUDO, 	0x10 )	


#if RKH_EN_STATE_NAME == 1
	#define mkbase(t,id,name)			{t,id,#name}
#else
	#define mkbase(t,id,name)			{t,id}
#endif


#if RKH_EN_HCAL == 1
	#if RKH_EN_PPRO == 1
		#define mkbasic(en,ex,p,n,pp)		en,ex,p,n##_trtbl,NULL,NULL,pp
		#define mkcomp(en,ex,p,n,d,h)		en,ex,p,n##_trtbl,d,h,NULL
	#else
		#define mkbasic(en,ex,p,n,pp)		en,ex,p,n##_trtbl,NULL,NULL
		#define mkcomp(en,ex,p,n,d,h)		en,ex,p,n##_trtbl,d,h
	#endif
#else
	#if RKH_EN_PPRO == 1
		#define mkbasic(en,ex,p,n,pp)		n##_trtbl,pp
		#define mkcomp(en,ex,p,n,d,h)		n##_trtbl,NULL
	#else
		#define mkbasic(en,ex,p,n,pp)		n##_trtbl
		#define mkcomp(en,ex,p,n,d,h)		n##_trtbl
	#endif
#endif


#if RKH_EN_HSM_NAME	== 1
#if RKH_EN_GET_INFO	== 1
	#if RKH_EN_HSM_DATA	== 1
		#define CHSM( id,p,n,is,ia,hd )	{id,p,#n,is,is,ia,hd,{0,0}}
	#else
		#define CHSM( id,p,n,is,ia,hd )	{id,p,#n,is,is,ia,{0,0}}
	#endif
#else
	#if RKH_EN_HSM_DATA	== 1
		#define CHSM( id,p,n,is,ia,hd )	{id,p,#n,is,is,ia,hd}
	#else
		#define CHSM( id,p,n,is,ia,hd )	{id,p,#n,is,is,ia}
	#endif
#endif
#else
#if RKH_EN_GET_INFO	== 1
	#if RKH_EN_HSM_DATA	== 1
		#define CHSM( id,p,n,is,ia,hd )	{id,p,is,is,ia,hd,{0,0}}
	#else
		#define CHSM( id,p,n,is,ia,hd )	{id,p,is,is,ia,{0,0}}
	#endif
#else
	#if RKH_EN_HSM_DATA	== 1
		#define CHSM( id,p,n,is,ia,hd )	{id,p,is,is,ia,hd}
	#else
		#define CHSM( id,p,n,is,ia,hd )	{id,p,is,is,ia}
	#endif
#endif
#endif


/** 
 * 	Defines the size of event. The valid values [in bits] are 
 * 	8, 16 or 32. Default is 8. This type is configurable via the 
 * 	preprocessor switch RKH_SIZEOF_EVENT.
 */

#if RKH_SIZEOF_EVENT == 8
	typedef rkhuint8 RKHE_T;
#elif RKH_SIZEOF_EVENT == 16
	typedef rkhuint16 RKHE_T;
#elif RKH_SIZEOF_EVENT == 32
	typedef rkhuint32 RKHE_T;
#else
	typedef rkhuint8 RKHE_T;
#endif


/**	
 * 	\brief
 *
 * 	Represents events without parameters.
 * 	
 * 	An event can have associated parameters, allowing the event 
 * 	instance to convey not only the occurrence of some interesting 
 * 	incident but also quantitative information regarding that occurrence.
 *	
 *	Implementing the single inheritance in C is very simply by literally
 *	embedding the base structure, RKHEVT_T in this case, as the first 
 *	member of the derived structure.
 *
 * 	The RKH takes the evt member of RKHEVT_T structure for triggering a 
 * 	state transition.
 */

typedef	struct
{
	RKHE_T evt;		/**< Represents a triggering event */
} RKHEVT_T;


/*
 * 	For GNU compatibility.
 */

struct rkh_t;


/**
 * 	Entry action.
 *
 * 	The actions that are always executed when a state is entered 
 * 	should be specified as entry actions.
 *
 * 	An entry function takes the state machine pointer as argument. 
 * 	This parameter is optional in compile-time according to 
 * 	RKH_EN_ENT_HSM_ARG.
 */


#if RKH_EN_ENT_HSM_ARG == 1
	
	typedef void ( *RKHENT_T )( const struct rkh_t *ph );

	#define rkh_exec_entry( s, h )				\
	{											\
		if( (s)->enter != NULL )				\
			(*(s)->enter)( h ); 				\
	}

#else
	
	typedef void ( *RKHENT_T )( void );

	#define rkh_exec_entry( s, h )				\
	{											\
		if( (s)->enter != NULL )				\
			(*(s)->enter)(); 					\
	}

#endif



/**
 * 	Exit action.
 *
 * 	The actions that are always execute when a state is exited should be 
 * 	exit actions.
 *
 * 	An exit function takes the state machine pointer as argument. 
 * 	This parameter is optional in compile-time according to 
 * 	RKH_EN_EXT_HSM_ARG.
 */

#if RKH_EN_EXT_HSM_ARG == 1

	typedef void ( *RKHEXT_T )( const struct rkh_t *ph );

	#define rkh_exec_exit( s, h )				\
	{											\
		if( (s)->exit != NULL )					\
			(*(s)->exit)( h ); 					\
	}

#else
	
	typedef void ( *RKHEXT_T )( void );

	#define rkh_exec_exit( s, h )				\
	{											\
		if( (s)->exit != NULL )					\
			(*(s)->exit)(); 					\
	}

#endif



/**
 * 	Initialization action.
 *
 * 	The application code must trigger the initial transition explicitly 
 * 	by invoking 'rkh_init_hsm'.
 *
 * 	An init function takes the state machine pointer as argument. 
 * 	This parameter is optional in compile-time according to 
 * 	RKH_EN_INIT_HSM_ARG.
 */

#if RKH_EN_INIT_HSM_ARG == 1

	typedef void ( *RKHINIT_T )( const struct rkh_t *ph );

	#define rkh_exec_init( h )					\
	{											\
		if( (h)->init_action != NULL )			\
			(*(h)->init_action)( h );			\
	}

#else
	
	typedef void ( *RKHINIT_T )( void );

	#define rkh_exec_init( h )					\
	{											\
		if( (h)->init_action != NULL )			\
			(*(h)->init_action)();				\
	}

#endif


/**
 * 	Event preprocessor.
 *
 * 	Before sending the arrived event to state machine, it can be previously 
 * 	processed using the	event preprocessor function.
 */

typedef RKHE_T ( *RKHPPRO_T )( RKHEVT_T *pe );


/**
 * 	Action:
 *
 * 	Actions are small atomic behaviors executed at specified points 
 * 	in a state machine. Actions are assumed to take an insignificant 
 * 	amount of time to execute and are noninterruptible.
 *
 * 	An action function takes the state machine pointer and the event 
 * 	pointer as arguments. These parameters are optional in compile-time
 * 	according to RKH_EN_ACT_EVT_ARG' and RKH_EN_ACT_HSM_ARG.
 */

#if RKH_EN_ACT_EVT_ARG == 1 && RKH_EN_ACT_HSM_ARG == 1

	typedef void (*RKHACT_T)( const struct rkh_t *ph, RKHEVT_T *pe );
	#define rkh_call_action(h,e)	(*CA( q ))( h, e )

#elif RKH_EN_ACT_EVT_ARG == 1 && RKH_EN_ACT_HSM_ARG == 0
	
	typedef void (*RKHACT_T)( RKHEVT_T *pe );
	#define rkh_call_action(h,e)	(*CA( q ))( e )

#elif RKH_EN_ACT_EVT_ARG == 0 && RKH_EN_ACT_HSM_ARG == 1
	
	typedef void (*RKHACT_T)( const struct rkh_t *ph );
	#define rkh_call_action(h,e)	(*CA( q ))( h )

#else
	
	typedef void (*RKHACT_T)( void );
	#define rkh_call_action(h,e)	(*CA( q ))()

#endif


/**
 * 	Guard:
 *
 *	A guard is a boolean condition that returns a TRUE (RKH_GTRUE) or 
 *	FALSE (RKH_GFALSE) value that controls whether or not a transition 
 *	is taken following the receipt of a triggering event. A transition 
 *	with a guard is only take if the triggering event occurs and the 
 *	guard evaluates to TRUE. As long as the guard evaluated to FALSE, 
 *	the triggering event would be discarded and the transition would 
 *	not be taken.
 *	
 * 	A guard function takes the state machine pointer and the event 
 * 	pointer as arguments. These parameters are optional in compile-time
 * 	according to RKH_EN_GRD_EVT_ARG and RKH_EN_GRD_HSM_ARG.
 */

#if RKH_EN_GRD_EVT_ARG == 1 && RKH_EN_GRD_HSM_ARG == 1

	typedef HUInt (*RKHGUARD_T)( const struct rkh_t *ph, RKHEVT_T *pe );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)( h, e )

#elif RKH_EN_GRD_EVT_ARG == 1 && RKH_EN_GRD_HSM_ARG == 0
	
	typedef HUInt (*RKHGUARD_T)( RKHEVT_T *pe );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)( e )

#elif RKH_EN_GRD_EVT_ARG == 0 && RKH_EN_GRD_HSM_ARG == 1
	
	typedef HUInt (*RKHGUARD_T)( const struct rkh_t *ph );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)( h )

#else
	
	typedef HUInt (*RKHGUARD_T)( void );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)()

#endif


/**
 * 	Branch:
 *
 * 	A branch function takes the state machine pointer and the event 
 * 	pointer as arguments. These parameters are optional in compile-time
 * 	according to RKH_EN_BCH_EVT_ARG and RKH_EN_BCH_HSM_ARG.
 */

#if RKH_EN_BCH_EVT_ARG == 1 && RKH_EN_BCH_HSM_ARG == 1

	typedef RKHE_T (*RKHBRANCH_T)( const struct rkh_t *ph, RKHEVT_T *pe );
	#define rkh_call_cond(s,h,e)	(*(s)->cdl)( h, e )

#elif RKH_EN_BCH_EVT_ARG == 1 && RKH_EN_BCH_HSM_ARG == 0
	
	typedef RKHE_T (*RKHBRANCH_T)( RKHEVT_T *pe );
	#define rkh_call_cond(s,h,e)	(*(s)->cdl)( e )

#elif RKH_EN_BCH_EVT_ARG == 0 && RKH_EN_BCH_HSM_ARG == 1
	
	typedef RKHE_T (*RKHBRANCH_T)( const struct rkh_t *ph );
	#define rkh_call_cond(s,h,e)	(*(s)->cdl)( h )

#else
	
	typedef RKHE_T (*RKHBRANCH_T)( void );
	#define rkh_call_cond(s,h,e)	(*(s)->cdl)()

#endif


/**
 * 	\brief 
 *
 * 	Maintains the basic information of a state.
 */

typedef struct rkhbase_t
{
	/**	
	 *	Contains the type of a particular state and can have 
	 *	the following values:
	 *
	 *	- RKH_COMPOSITE: 		composite state.
	 *	- RKH_BASIC: 			basic state.
	 *	- RKH_JUNCTION: 		junction pseudostate.
	 *	- RKH_CONDITIONAL: 		conditional pseudostate.
	 *	- RKH_SHISTORY: 		shadow history pseudostate.
	 *	- RKH_DHISTORY: 		deep history pseudostate.
	 */

	HUInt type;					

	/**	
	 *	State ID. 
	 *	This number isn't internally used by RKH framework.
	 */

	HUInt id;

#if RKH_EN_STATE_NAME == 1

	/**	
	 *	State name. 
	 *	String terminated in '\\0' that represents the name 
	 *	of state. It's generally used for debugging.
	 */

	char *name;
#endif
} RKHBASE_T;


/**
 * 	\brief
 *
 * 	Describes the state transition. 
 *
 * 	Transitions represent the response of a state machine to events. 
 * 	Any event that is not explicitly listed as causing an event to occur 
 * 	in a given state is quietly discarded should it occur.
 */

typedef struct rkhtr_t
{
	/** 	
	 *  Triggering event.
	 */

	RKHE_T event;
	
	/**	
	 *	Points to guard function.
	 */

	RKHGUARD_T guard;
	
	/** 	
	 *  Points to transition action.
	 */

	RKHACT_T action;

	/** 	
	 *  Points to target state.
	 */

	rkhrom void *target;
} RKHTR_T;


/**
 *	\brief
 *
 * 	Describes a regular state.
 *
 * 	It can either be a composite or basic state.
 */

typedef struct rkhsreg_t
{
	/**	
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

#if RKH_EN_HCAL == 1
	/**	
	 *	Points to entry action.
	 */

	RKHENT_T enter;

	/**	
	 *	Points to exit action.
	 */

	RKHEXT_T exit;

	/**	
	 *	Points to state's parent.
	 */

	rkhrom struct rkhsreg_t *parent;
#endif

	/**	
	 *	Points to state transition table.
	 */

	rkhrom struct rkhtr_t *trtbl;

#if RKH_EN_HCAL == 1
	/**	
	 *	Points to state's default child.
	 */

	rkhrom void *defchild;

	/**	
	 *	Points to state's history. 
	 */

	rkhrom struct rkhshist_t *history;
#endif

	/**	
	 *	Points to event preprocessor.
	 */

	RKHPPRO_T prepro;
} RKHSREG_T;


/**
 * 	\brief 
 *
 * 	Describes the conditional pseudostate.
 */

typedef struct rkhscond_t
{
	/**
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
	 *	Points to conditional function.
	 */

	RKHBRANCH_T cdl;

	/**	
	 *	Points to branch table.
	 */

	rkhrom struct rkhtr_t *trtbl;
} RKHSCOND_T;


/**
 * 	\brief 
 *
 * 	Describes the junction pseudostate.
 */

typedef struct rkhsjunct_t
{
	/**	
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
	 *	Points to action function.
	 */

	RKHACT_T action;

	/**	
	 *	Points to target state or pseudostate.
	 */

	rkhrom void *target;
} RKHSJUNC_T;


/**
 * 	\brief 
 *
 * 	Describes the history pseudostate
 *
 * 	It can be either be shallow or deep.
 */

typedef struct rkhshist_t
{
	/**	
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
	 *	Points to state's parent.
	 */

	rkhrom RKHSREG_T *parent;

	/**	
	 *	Points to RAM memory location which stores
	 *	the state's history.
	 */

	rkhrom RKHSREG_T **target;
} RKHSHIST_T;


/**
 * 	\brief 
 *
 * 	Describes the HSM's performance information.
 *
 * 	Defines the data structure into which the performance 
 * 	information for HSM is stored.
 */

typedef struct rkh_info_t
{
	rkhuint16 rcvevt;			/**<	# of received events */
	rkhuint16 exectr;			/**<	# of executed transitions */
} RKH_INFO_T;


/**
 * 	\brief 
 *
 * 	Describes the HSM. 
 *
 * 	It maintains the vital information related with a hierarchical 
 * 	state machine.
 */

typedef struct rkh_t
{
	/**	
	 *	HSM descriptor.
	 */

	rkhuint8 id;

	/**
	 * 	State-machine properties.
	 */

	rkhuint8 ppty;

#if RKH_EN_HSM_NAME	== 1
	
	/**	
	 *	State name string. String terminated in '\\0' that 
	 *	represents the name of state. It generally used for 
	 *	debugging.
	 */

	char *name;
#endif
	/** 
	 * 	Points to initial state. The initial state must be a
	 * 	composite state or basic state.
	 */

	rkhrom RKHSREG_T *init_state;

	/** 
	 * 	Points to current state.
	 */

	rkhrom RKHSREG_T *state;

	/** 
	 * 	Points to initializing action function.
	 */

	RKHINIT_T init_action;
#if RKH_EN_HSM_DATA == 1
	
	/** 
	 * 	Points to optional HSM's data.
	 */

	void *hdata;
#endif
#if RKH_EN_GET_INFO == 1

	/** 
	 * 	Maintains the optional performance information.
	 */

	RKH_INFO_T hinfo;
#endif	
} RKH_T;


#endif
