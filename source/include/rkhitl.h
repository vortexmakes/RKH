/*
 *	file: rkhitl.h
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
 * 	\file rkhitl.h
 * 	\brief
 *
 * 	RKH engine interface.
 *
 * 	This header file is directly included in RKH interface 
 * 	file, rkh.h.
 */


#ifndef __RKHITL_H__
#define __RKHITL_H__


/**	
 *  Application specific configuration options.
 */

#include "rkhcfg.h"


/** 
 * 	Specific definitions to the platform being used.
 */

#include "rkhplat.h"


/** 
 * 	Trace facility.
 */

#include "rkhtrace.h"


/**	
 *	Version string of RKH.
 *
 *	Date: 06/24/2011
 */

#define RKH_VERSION					"1.1.5"


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


#ifndef RKH_ASSERT
	#define RKH_ASSERT		0
#endif


/*
 * 	The 'rkhassert' macro is used by RKH to check expressions that ought 
 * 	to be true as long as the program is running correctly. An assert 
 * 	should never have a side effect. If the expression evaluates to 0, the 
 * 	macro 'rkh_assert' will be called, typically halting the program in some 
 * 	way. The 'rkh_assert' macro should store or report the error code 
 * 	('event' parameter). Once the 'rkh_assert' macro has stored 
 *	or reported the error, it must decide on the system's next action.
 *	One option is:
 *		
 *		1.- disable general interrupt
 *		2.- stores or send detected error (could be use a trace facility)
 *		3.- trigger a software reset
 *	
 *	The policy chooses will be largely determined by the nature of product. 
 *	If the system is running with a source level debugger, place a 
 *	breakpoint within.
 */

#if RKH_ASSERT == 1
	#ifdef rkh_assert
		#define rkhassert( exp, event )		\
			if( ( exp ) )					\
			{}								\
			else							\
			{								\
				rkh_assert( event )			\
			}
	#else
	    #error  "rkhcfg.h, Missing rkh_assert macro"
	#endif
#else
	#define rkhassert( exp, event )
	#undef rkh_assert
	#define rkh_assert( event )
#endif


#if RKH_EN_DYNAMIC_EVENT == 1
	#define mksevt( evt, es )											\
								((RKHEVT_T*)(e))->e = (RKHE_T)es;		\
								((RKHEVT_T*)(e))->dynamic_ = 0;
#else
	#define mksevt( evt, es )											\
								((RKHEVT_T*)(evt))->e = (RKHE_T)es;
#endif


/**
 *	Defines dynamic event support.
 *	
 *	This definitions are required only when the user application
 *	is used dynamic event (of course, RKH_EN_DYNAMIC_EVENT == 1).
 */

#if RKH_EN_DYNAMIC_EVENT == 1

	/**
	 * 	\brief 
	 * 	
	 * 	Number of available memory pools. Default is 3.
	 * 	
	 * 	\note 
	 *
	 * 	Typically, must be define it in the specific port file (rkhport.h).
	 * 	Example:
	 * 	
	 * 	\code
	 * 	#define RKH_DYNE_NUM_POOLS			RKSYS_MPOOL_NUM_POOLS
	 * 	\endcode
	 */

	#ifndef RKH_DYNE_NUM_POOLS
		#define RKH_DYNE_NUM_POOLS			3
	#endif

	/**
	 * 	\brief 
	 *
	 * 	Platform-dependent macro defining the event pool initialization.
	 * 	
	 * 	\note 
	 *
	 * 	Typically, must be define it in the specific port file (rkhport.h).
	 * 	Example:
	 * 	
	 * 	\code
	 * 	#define rkh_dyne_init( mpd, pm, ps, bs )						\
	 * 																	\
	 * 				rk_mpool_init( (mpd), (pm), (rkint16)(ps),			\
														(RK_MPBS_T)(bs) )
	 *	\endcode
	 */

	#ifndef rkh_dyne_init
	    #error  "rksyscfg.h, Missing rkh_dyne_init() macro."
	#endif

	/**
	 * 	\brief 
	 *
	 * 	Platform-dependent macro defining how RKH should obtain the
	 * 	event pool block size.
	 * 	
	 * 	\note 
	 *
	 * 	Typically, must be define it in the specific port file (rkhport.h).
	 * 	Example:
	 *
	 * 	\code
	 * 	#define rkh_dyne_event_size( mpd )								\
	 * 																	\
	 * 				( RK_MPBS_T )rk_mpool_get_blksize( (mpd) )
	 * 	\endcode
	 */

	#ifndef rkh_dyne_event_size
	    #error  "rksyscfg.h, Missing rkh_dyne_event_size() macro."
	#endif

	/**
	 * 	\brief 
	 *
	 * 	Platform-dependent macro defining how RKH should obtain an event
	 * 	\a e from the event pool \a mpd.
	 * 	
	 * 	\note 
	 *
	 * 	Typically, must be define it in the specific port file (rkhport.h).
	 * 	Example:
	 *
	 * 	\code
	 *	#define rkh_dyne_get( mpd, e )									\
	 *																	\
	 *				((e) = ( RKHEVT_T* )rk_mpool_get( (mpd) ))
	 * 	\endcode
	 */

	#ifndef rkh_dyne_get
	    #error  "rksyscfg.h, Missing rkh_dyne_get() macro."
	#endif

	/**
	 * 	\brief 
	 *
	 *  Platform-dependent macro defining how RKH should return an event
	 *  \a e to the event pool \a mpd.	
	 * 	
	 * 	\note 
	 *
	 * 	Typically, must be define it in the specific port file (rkhport.h).
	 * 	Example:
	 *
	 * 	\code
	 *	#define rkh_dyne_put( mpd, e )									\
	 *																	\
	 *				rk_mpool_put( (mpd), (e) )
	 * 	\endcode
	 */

	#ifndef rkh_dyne_put
	    #error  "rksyscfg.h, Missing rkh_dyne_put() macro."
	#endif

	/**
	 * 	\brief 
	 *
	 *  Platform-dependent macro defining how RKH should post an event
	 *  \a e to the queue \a qd in FIFO policy.	
	 * 	
	 * 	\note 
	 *
	 * 	Typically, must be define it in the specific port file (rkhport.h).
	 * 	Example:
	 *
	 * 	\code
	 *	#define rkh_post_fifo( qd, e )									\
	 *																	\
	 *				queue_insert( (QD_T)(qd), &(e) )
	 * 	\endcode
	 */

	#ifndef rkh_post_fifo
	    #error  "rksyscfg.h, Missing rkh_post_fifo() macro."
	#endif

	/**
	 * 	\brief 
	 *
	 *  Platform-dependent macro defining how RKH should post an event
	 *  \a e to the queue \a qd in LIFO policy.	
	 * 	
	 * 	\note 
	 *
	 * 	Typically, must be define it in the specific port file (rkhport.h).
	 * 	Example:
	 *
	 * 	\code
	 *	#define rkh_post_lifo( qd, e )									\
	 *																	\
	 *				queue_insert_lifo( (QD_T)(qd), &(e) )
	 * 	\endcode
	 */

	#ifndef rkh_post_lifo
	    #error  "rksyscfg.h, Missing rkh_post_lifo() macro."
	#endif

	/**
	 * 	\brief 
	 *
	 *  Platform-dependent macro defining how RKH should get an event
	 *  \a e from the queue \a qd.
	 * 	
	 * 	\note 
	 *
	 * 	Typically, must be define it in the specific port file (rkhport.h).
	 * 	Example:
	 *
	 * 	\code
	 *	#define rkh_get( qd, e )										\
	 *																	\
	 *				queue_remove( (QD_T)(qd), &(e) )
	 * 	\endcode
	 */

	#ifndef rkh_get
	    #error  "rksyscfg.h, Missing rkh_get() macro."
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
 * 	For example, the structure MYEVT_T derived from the base structure 
 * 	RKHEVT_T by embedding the RKHEVT_T instance as the first member of 
 *	MYEVT_T.
 *
 * 	\code
 * 	typedef struct
 * 	{
 * 		RKHEVT_T evt;
 *		int x;
 *		int y;
 * 	} MYEVT_T;
 * 	\endcode
 *
 *	Such nesting of structures always aligns the data member 'evt' at the 
 *	beginning of every instance of the derived structure. In particular, this 
 *	alignment lets you treat a pointer to the derived MYEVT_T structure as a 
 *	pointer to the RKHEVT_T base structure. Consequently, you can always 
 *	safely pass a pointer to MYEVT_T to any C function that expects a pointer 
 *	to RKHEVT_T. (To be strictly correct in C, you should explicitly cast this 
 *	pointer. In OOP such casting is called upcasting and is always safe.) 
 *	Therefore, all functions designed for the RKHEVT_T structure are 
 *	automatically available to the MYEVT_T structure as well as other 
 *	structures derived from RKHEVT_T.
 *
 * 	The RKH takes the 'e' member of RKHEVT_T structure for triggering a 
 * 	state transition.
 */

typedef struct
{
	/**
	 *	Signal of the event instance.
	 */

	RKHE_T e;

	/**
	 * 	Attributes of dynamic event (0 for static event).
	 */

#if RKH_EN_DYNAMIC_EVENT == 1
	rkhuint8 dynamic_;
#endif
} RKHEVT_T;


/**
 * 	Internal RKH implementation of the dynamic event allocator. 
 *
 * 	\param es		size of event [in bytes].
 * 	\param e		event signal.
 * 	
 * 	\note
 *
 * 	This function is internal to RKH and the user application should 
 * 	not call it. Please use #rkh_alloc_event() macro.
 */

RKHEVT_T *rkh_ae( rkhuint8 es, RKHE_T e );


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
 *
 * 	An action function takes the state machine pointer and the event 
 * 	pointer as arguments. The first parameter is optional in compile-time
 * 	according to RKH_EN_PPRO_HSM_ARG.
 */

#if RKH_EN_PPRO_HSM_ARG == 1

	typedef RKHE_T ( *RKHPPRO_T )( const struct rkh_t *ph, RKHEVT_T *pe );
	#define rkh_call_prepro(s,h,e)		(*(s)->prepro)( h, e )

#else

	typedef RKHE_T ( *RKHPPRO_T )( RKHEVT_T *pe );
	#define rkh_call_prepro(s,h,e)		(*(s)->prepro)( e )

#endif


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
 *	Each condition connector can have one special branch with a guard 
 *	labeled rkh_else, which is taken if all the guards on the other 
 *	branches are false. 
 *
 * 	A guard function takes the state machine pointer and the event 
 * 	pointer as arguments. These parameters are optional in compile-time
 * 	according to RKH_EN_GRD_EVT_ARG and RKH_EN_GRD_HSM_ARG.
 */

#if RKH_EN_GRD_EVT_ARG == 1 && RKH_EN_GRD_HSM_ARG == 1

	typedef HUInt (*RKHGUARD_T)( const struct rkh_t *ph, RKHEVT_T *pe );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)( h, e )
	HUInt rkh_else( const struct rkh_t *ph, RKHEVT_T *pe );

#elif RKH_EN_GRD_EVT_ARG == 1 && RKH_EN_GRD_HSM_ARG == 0
	
	typedef HUInt (*RKHGUARD_T)( RKHEVT_T *pe );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)( e )
	HUInt rkh_else( RKHEVT_T *pe );


#elif RKH_EN_GRD_EVT_ARG == 0 && RKH_EN_GRD_HSM_ARG == 1
	
	typedef HUInt (*RKHGUARD_T)( const struct rkh_t *ph );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)( h )
	HUInt rkh_else( const struct rkh_t *ph );

#else
	
	typedef HUInt (*RKHGUARD_T)( void );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)()
	HUInt rkh_else( void );

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
	 *
	 *	Aditionally, by means of single inheritance in C it could be 
	 *	used as state's abstract data.
	 *	Aditionally, implementing the single inheritance in C is very 
	 *	simply by literally embedding the base type, RKHPPRO_T in 
	 *	this case, as the first member of the derived structure.
	 *	
	 *	This argument is optional, thus it could be declared as NULL.
	 *
	 *	Example:
	 *  
	 *  	\code
	 *  	static
	 *  	RKHE_T
	 *  	preprocessor( RKHEVT_T *pe )
	 *  	{
	 *  		...
	 *  	}
	 *  
	 * 		typedef struct
	 * 		{
	 * 			RKHPPRO_T prepro; 	// extend the RKHPPRO_T class
	 * 			unsigned min:4;
	 * 			unsigned max:4;
	 * 			char *buff;
	 * 		} SDATA_T;
	 *
	 * 		static const SDATA_T option = { preprocessor, 4, 8, token1 };
	 *
	 *  	RKH_CREATE_BASIC_STATE( S111, 0, set_x_1, 
	 *  								NULL, &S11, preprocessor ); 
	 *  	RKH_CREATE_BASIC_STATE( S22, 0, set_x_4, 
	 *  								NULL, &S2, (RKHPPRO_T*)&option ); 
	 *  	\endcode
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
	 * 	State machine properties. The available properties are
	 * 	enumerated in RKH_HPPTY_T enumeration in the rkh.h
	 * 	file.
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
