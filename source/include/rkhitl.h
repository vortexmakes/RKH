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

#ifndef RKH_EN_HCAL
	#error "rkhcfg.h, Missing RKH_EN_HCAL: Enable (1) or Disable (0) state nesting"
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

#ifndef RKH_NUM_STATE_MACHINES
#error "rkhcfg.h, Missing RKH_NUM_STATE_MACHINES: Max. # of state machines"
#else
	#if RKH_NUM_STATE_MACHINES == 0 || RKH_NUM_STATE_MACHINES > 32
	#error  "rkhcfg.h, RKH_NUM_STATE_MACHINES must be > 0 and <= 32"
	#endif
#endif

#ifndef RKH_EN_DYNAMIC_EVENT
	#error "rkhcfg.h, Missing RKH_EN_DYNAMIC_EVENT: Enable (1) or Disable (0) dynamic event support."
#endif

#ifndef RKH_EN_DEFERRED_EVENT
	#error "rkhcfg.h, Missing RKH_EN_DEFERRED_EVENT: Enable (1) or Disable (0) deferred event support. For using this feature the dynamic event support must be set to one."
#else
	#if RKH_EN_DEFERRED_EVENT == 1
		#if RKH_EN_DYNAMIC_EVENT == 0
	    #error  "rkhport.h, For using deferred events support feature the dynamic event support must be set to one (RKH_EN_DYNAMIC_EVENT)."
		#endif
	#endif
#endif

#ifndef RKH_EN_PSEUDOSTATE
	#error "rkhcfg.h, Missing RKH_EN_PSEUDOSTATE: Enable (1) or Disable (0) pseudostates."
#endif

#ifndef RKH_EN_DEEP_HISTORY
	#error "rkhcfg.h, Missing RKH_EN_DEEP_HISTORY: Include deep history. Must be set to one RKH_EN_PSEUDOSTATE."
#endif

#ifndef RKH_EN_SHALLOW_HISTORY
	#error "rkhcfg.h, Missing RKH_EN_SHALLOW_HISTORY: Include shallow history. Must be set to one RKH_EN_PSEUDOSTATE."
#endif

#ifndef RKH_EN_JUNCTION
	#error "rkhcfg.h, Missing RKH_EN_JUNCTION: Include junction. Must be set to one RKH_EN_PSEUDOSTATE."
#endif

#ifndef RKH_EN_CONDITIONAL	
	#error "rkhcfg.h, Missing RKH_EN_CONDITIONAL: Include conditional. Must be set to one RKH_EN_PSEUDOSTATE."
#endif

#ifndef RKH_EN_INIT_HSM_ARG
	#error "rkhcfg.h, Missing RKH_EN_INIT_HSM_ARG: Enable (1) or Disable (0) state machine arg from initialization action."
#endif

#ifndef RKH_EN_ENT_HSM_ARG
	#error "rkhcfg.h, Missing RKH_EN_ENT_HSM_ARG: Enable (1) or Disable (0) state machine arg from entry action."
#endif

#ifndef RKH_EN_EXT_HSM_ARG
	#error "rkhcfg.h, Missing RKH_EN_EXT_HSM_ARG: Enable (1) or Disable (0) state machine arg from exit action."
#endif

#ifndef RKH_EN_ACT_HSM_ARG
	#error "rkhcfg.h, Missing RKH_EN_ACT_HSM_ARG: Enable (1) or Disable (0) state machine arg from transition action."
#endif

#ifndef RKH_EN_ACT_EVT_ARG
	#error "rkhcfg.h, Missing RKH_EN_ACT_EVT_ARG: Enable (1) or Disable (0) event arg from guard function."
#endif

#ifndef RKH_EN_GRD_EVT_ARG
	#error "rkhcfg.h, Missing RKH_EN_GRD_EVT_ARG: Enable (1) or Disable (0) event arg from guard function."
#endif

#ifndef RKH_EN_GRD_HSM_ARG
	#error "rkhcfg.h, Missing RKH_EN_GRD_EVT_ARG: Enable (1) or Disable (0) state machine arg from guard function."
#endif

#ifndef RKH_EN_PPRO_HSM_ARG
	#error "rkhcfg.h, Missing RKH_EN_PPRO_HSM_ARG: Enable (1) or Disable (0) state machine arg from event preprocessor function."
#endif

#ifndef RKH_EN_STATE_NAME
	#error "rkhcfg.h, Missing RKH_EN_STATE_NAME: Include state name as string within state machine object."
#endif

#ifndef RKH_EN_HSM_NAME	
	#error "rkhcfg.h, Missing RKH_EN_HSM_NAME: Include state machine name as string within state machine object."
#endif

#ifndef RKH_EN_HSM_DATA
	#error "rkhcfg.h, Missing RKH_EN_HSM_DATA: Include state machine data within state machine object."
#endif

#ifndef RKH_EN_PPRO	
	#error "rkhcfg.h, Missing RKH_EN_PPRO: Include input preprocessor function within basic state object."
#endif

#ifndef RKH_EN_GET_INFO
	#error "rkhcfg.h, Missing RKH_EN_GET_INFO: Include get information function."
#endif

#ifndef RKH_EN_REENTRANT
	#error "rkhcfg.h, Missing RKH_EN_REENTRANT: Enable (1) or Disable (0) state machine re-entrancy."
#endif

#ifndef RKH_TRACE
	#error "rkhcfg.h, Missing RKH_TRACE: Enable (1) or Disable (0) trace mode."
#endif

#ifndef RKH_TRACE_ALL
	#error "rkhcfg.h, Missing RKH_TRACE_ALL: Include all trace points."
#endif

#ifndef RKH_EN_EVENT
	#error "rkhcfg.h, Missing RKH_EN_EVENT: Enable (1) or Disable (0) trace point - triggering event."
#endif

#ifndef RKH_EN_TRN_SRC
	#error "rkhcfg.h, Missing RKH_EN_TRN_SRC: Enable (1) or Disable (0) trace point - transition source state."
#endif

#ifndef RKH_EN_TRN_TGT	
	#error "rkhcfg.h, Missing RKH_EN_TRN_TGT: Enable (1) or Disable (0) trace point - transition target state."
#endif

#ifndef RKH_EN_NXT_STATE
	#error "rkhcfg.h, Missing RKH_EN_NXT_STATE: Enable (1) or Disable (0) trace point - next state."
#endif

#ifndef RKH_EN_INT_TRAN	
	#error "rkhcfg.h, Missing RKH_EN_INT_TRAN: Enable (1) or Disable (0) trace point - internal transition."
#endif

#ifndef RKH_EN_ENTRY
	#error "rkhcfg.h, Missing RKH_EN_ENTRY: Enable (1) or Disable (0) trace point - entry state."
#endif

#ifndef RKH_EN_EXIT	
	#error "rkhcfg.h, Missing RKH_EN_EXIT: Enable (1) or Disable (0) trace point - exit state."
#endif

#ifndef RKH_EN_INIT_HSM
	#error "rkhcfg.h, Missing RKH_EN_INIT_HSM: Enable (1) or Disable (0) trace point - initializing state machine."
#endif

#ifndef RKH_EN_SGT
	#error "rkhcfg.h, Missing RKH_EN_SGT: Enable (1) or Disable (0) trace point - target state of transition segment."
#endif

#ifndef RKH_EN_RTN_CODE
	#error "rkhcfg.h, Missing RKH_EN_RTN_CODE: Enable (1) or Disable (0) trace point - code returned by rkh_engine() function."
#endif

#ifndef RKH_EN_NUM_ENEX
	#error "rkhcfg.h, Missing RKH_EN_NUM_ENEX: Enable (1) or Disable (0) trace point - # of enter and exited states."
#endif

#ifndef RKH_EN_NUM_ACTSGT
	#error "rkhcfg.h, Missing RKH_EN_NUM_ACTSGT: Enable (1) or Disable (0) trace point - # of transition actions to be executed and number of transition segments."
#endif

#ifndef RKH_EN_TIMESTAMP
	#error "rkhcfg.h, Missing RKH_EN_TIMESTAMP: Enable (1) or Disable (0) trace timestamp."
#endif

#ifndef RKH_SIZEOF_TIMESTAMP
	#error "rkhcfg.h, Missing RKH_SIZEOF_TIMESTAMP: Defines the size of timestamp [in bits]: 8, 16 or 32."
#endif

#ifndef RKH_MAX_NUM_TRACES
	#error "rkhcfg.h, Missing RKH_MAX_NUM_TRACES: Max. number of trace events in the stream."
#else
	#if RKH_MAX_NUM_TRACES == 0 || RKH_MAX_NUM_TRACES > 256
	#error  "rkhcfg.h, RKH_MAX_NUM_TRACES must be > 0 and <= 256"
	#endif
#endif

#ifndef RKH_EN_TRACE_STRING
	#error "rkhcfg.h, Missing RKH_EN_TRACE_STRING: Enable (1) or Disable (0) the string argument of trace event."
#endif

#ifndef RKH_MAX_TRACE_STRING_SIZE
	#error "rkhcfg.h, Missing RKH_MAX_TRACE_STRING_SIZE: Defines the size of string argument of trace event."
#else
	#if RKH_MAX_TRACE_STRING_SIZE == 0 || RKH_MAX_TRACE_STRING_SIZE > 128
	#error  "rkhcfg.h, RKH_MAX_TRACE_STRING_SIZE must be > 0 and <= 32"
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


/**
 * 	\brief 
 * 	The rkhassert() macro is used by RKH to check expressions that ought 
 * 	to be true as long as the program is running correctly. 
 *
 * 	An assert should never have a side effect. If the expression evaluates to 
 * 	FALSE (0), the macro rkh_assert() will be called, typically halting the 
 * 	program in some way. This macro must be defined by the user application.
 * 	The rkh_assert() macro should store or report the error code 
 * 	('event' parameter). Once the rkh_assert() macro has stored or reported 
 * 	the error, it must decide on the system's next action.
 *	One option is:
 *		
 *	-# disable general interrupt
 *	-# stores or send detected error (could be use a trace facility)
 *	-# trigger a software reset
 *
 *	Example:
 *
 *	\code
 *	//	...defining
 *	#define rkh_assert( event )								\
 *															\
 *				printf( "RKHASSERT = [%02d] from %s()", 	\
 *				event, __FUNCTION__ );						\
 *				__debugbreak();
 *
 *	//	...using
    rkhassert( evt != NULL, RKH_AE_NOT_ALLOC );
 *	\endcode
 *	
 *	\note
 *	The policy chooses will be largely determined by the nature of product. 
 *	If the system is running with a source level debugger, place a 
 *	breakpoint within.
 *
 * 	\param exp		expression to be checked.
 * 	\param event	reported code.
 * 	
 * 	\sa rkhallege(), rkhrequire(), rkhensure(), and rkhinvariant() macros.
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

    /** 
 	 * 	\brief 
	 * 	General purpose assertion that ALWAYS evaluates the \a exp
	 * 	argument and calls the rkhassert() macro if the \a exp	evaluates 
	 * 	to FALSE.
	 *
	 * 	\note The \a exp argument IS always evaluated even when assertions 
	 * 	are disabled with the RKH_ASSERT macro. When the RKH_ASSERT macro 
	 * 	is defined, the rkhassert() macro is NOT called, even if the
	 * 	\a exp evaluates to FALSE.
     */

	#define rkhallege( exp, event )			rkhassert( exp, event )

#else
	#define rkhassert( exp, event )			((void)0)
	#define rkhallege( exp, event )			((void)(exp))

	#undef rkh_assert
	#define rkh_assert( event )
#endif


/**
 * 	\brief
 *	This macro checks the precondition. 
 *
 *	This macro is equivalent to rkhassert() macro, except the name provides 
 *	a better documentation of the intention of this assertion.
 */

#define rkhrequire( exp, event )			rkhassert( exp, event )


/**
 * 	\brief
 *	This macro checks the postcondition. 
 *
 *	This macro is equivalent to rkhassert() macro, except the name provides 
 *	a better documentation of the intention of this assertion.
 */

#define rkhensure( exp, event )				rkhassert( exp, event )


/**
 * 	\brief
 *	This macro is used to check a loop invariant. 
 *
 *	This macro is equivalent to rkhassert() macro, except the name provides 
 *	a better documentation of the intention of this assertion.
 */

#define rkhinvariant( exp, event )			rkhassert( exp, event )


#if RKH_EN_DYNAMIC_EVENT == 1
	#define mksevt( evt, es )											\
								((RKHEVT_T*)(evt))->e = (RKHE_T)es;		\
								((RKHEVT_T*)(evt))->dynamic_ = 0;
#else
	#define mksevt( evt, es )											\
								((RKHEVT_T*)(evt))->e = (RKHE_T)es;
#endif


#if RKH_EN_DYNAMIC_EVENT == 1

	#ifndef RKH_DYNE_NUM_POOLS
	    #error  "rkhport.h, Missing RKH_DYNE_NUM_POOLS. RKH can manage up to three (3) event pools."
	#elif RKH_DYNE_NUM_POOLS != 3
	    #error  "rkhport.h, RKH can manage up to three (3) event pools."
	#endif

	#ifndef rkh_dyne_init
	    #error  "rkhport.h, Missing rkh_dyne_init() macro."
	#endif

	#ifndef rkh_dyne_event_size
	    #error  "rkhport.h, Missing rkh_dyne_event_size() macro."
	#endif

	#ifndef rkh_dyne_get
	    #error  "rkhport.h, Missing rkh_dyne_get() macro."
	#endif

	#ifndef rkh_dyne_put
	    #error  "rkhport.h, Missing rkh_dyne_put() macro."
	#endif

	#ifndef rkh_post_fifo
	    #error  "rkhport.h, Missing rkh_post_fifo() macro."
	#endif

	#ifndef rkh_post_lifo
	    #error  "rkhport.h, Missing rkh_post_lifo() macro."
	#endif

	#ifndef rkh_get
	    #error  "rkhport.h, Missing rkh_get() macro."
	#endif

#endif


#ifndef RKH_EN_DOXYGEN
	#define RKH_EN_DOXYGEN	0
#endif


#if RKH_EN_DOXYGEN == 1

/**
 *	Defines dynamic event support.
 *	This definitions are required only when the user application
 *	is used dynamic event (of course, RKH_EN_DYNAMIC_EVENT == 1).
 */

/**
 * 	Number of available memory pools. Default is \b 3.
 *	RKH can manage up to three event pools (e.g., small, medium, and 
 *	large events, like shirt sizes).
 * 	
 * 	\note 
 * 	Typically, must be define it in the specific port file (rkhport.h).
 * 	Example:
 * 	
 * 	\code
 * 	#define RKH_DYNE_NUM_POOLS			RKSYS_MPOOL_NUM_POOLS
 * 	\endcode
 */

#define RKH_DYNE_NUM_POOLS

/**
 * 	\brief 
 * 	Platform-dependent macro defining the event pool initialization.
 *
 * 	\note 
 * 	Typically, must be define it in the specific port file (rkhport.h).
 * 	Example:
 * 	
 * 	\code
 * 	#define rkh_dyne_init( mpd, pm, ps, bs )						\
 * 																	\
 * 				rk_mpool_init( (mpd), (pm), (rkint16)(ps),			\
 *													(RK_MPBS_T)(bs) )
 *	\endcode
 *
 * 	\param mpd		memory pool descriptor.
 * 	\param pm	 	pointer to memory from which memory blocks are allocated.
 * 	\param ps		pool size. Size of the memory pool storage in byte.
 * 	\param bs		block size. This number determines the size of each memory 
 * 					block in the pool.
 *
 * 	\return
 * 	TRUE (0) if the memory pool was successfully initialized, 
 * 	otherwise error code.
 *
 * 	\sa rkh_alloc_event(), rkh_set_static_event() and rkh_gc().
 */

#define rkh_dyne_init( mpd, pm, ps, bs )

/**
 * 	\brief 
 * 	Platform-dependent macro defining how RKH should obtain the
 * 	event pool block size.
 * 	
 * 	\note 
 * 	Typically, must be define it in the specific port file (rkhport.h).
 * 	Example:
 *
 * 	\code
 * 	#define rkh_dyne_event_size( mpd )								\
 * 																	\
 * 				( RK_MPBS_T )rk_mpool_get_blksize( (mpd) )
 * 	\endcode
 *
 * 	\param mpd		memory pool descriptor.
 *
 * 	\return
 * 	The size of memory block in bytes.
 *
 * 	\sa rkh_alloc_event(), rkh_set_static_event() and rkh_gc().
 */

#define rkh_dyne_event_size( mpd )

/**
 * 	\brief 
 * 	Platform-dependent macro defining how RKH should obtain an event
 * 	\a e from the event pool \a mpd.
 * 	
 * 	\note 
 * 	Typically, must be define it in the specific port file (rkhport.h).
 * 	Example:
 *
 * 	\code
 *	#define rkh_dyne_get( mpd, e )									\
 *																	\
 *				((e) = ( RKHEVT_T* )rk_mpool_get( (mpd) ))
 * 	\endcode
 *
 * 	\param mpd		memory pool descriptor.
 * 	\param e 		pointer to the event structure into which the received 
 * 					item will be copied.
 *
 * 	\return
 * 	A pointer to a new memory block or NULL if the pool runs out of blocks.
 *
 * 	\sa rkh_alloc_event(), rkh_set_static_event() and rkh_gc().
 */

#define rkh_dyne_get( mpd, e )

/**
 * 	\brief 
 *  Platform-dependent macro defining how RKH should return an event
 *  \a e to the event pool \a mpd.	
 * 	
 * 	\note 
 * 	Typically, must be define it in the specific port file (rkhport.h).
 * 	Example:
 *
 * 	\code
 *	#define rkh_dyne_put( mpd, e )									\
 *																	\
 *				rk_mpool_put( (mpd), (e) )
 * 	\endcode
 *
 * 	\param mpd		memory pool descriptor.
 * 	\param e 		pointer to the event structure into which the received 
 * 					item will be copied.
 *
 * 	\return
 * 	TRUE (0) if the memory block was succesfully returned to proper 
 * 	memory pool, otherwise error code.
 *
 * 	\sa rkh_alloc_event(), rkh_set_static_event() and rkh_gc().
 */

#define rkh_dyne_put( mpd, e )

/**
 * 	\brief 
 *  Platform-dependent macro defining how RKH should post an event
 *  \a e to the queue \a qd in FIFO policy and retrieves the result of 
 *  that operation, i.e. TRUE (0) if an element was successfully 
 *  inserted to the queue, otherwise error code.
 * 	
 * 	\note 
 * 	Typically, must be define it in the specific port file (rkhport.h).
 * 	Example:
 *
 * 	\code
 *	#define rkh_post_fifo( qd, e )									\
 *																	\
 *				queue_insert( (QD_T)(qd), &(e) )
 * 	\endcode
 *
 * 	\param qd		queue descriptor.
 * 	\param e	 	pointer to the event that is to be placed on the queue.  
 *					The size of the elements the queue will hold was defined when 
 *					the queue was created.
 * 	\return
 * 	TRUE (0) if the element was successfully inserted, 
 *	otherwise error code.
 *
 * 	\sa rkh_alloc_event(), rkh_set_static_event() and rkh_gc().
 */

#define rkh_post_fifo( qd, e )

/**
 * 	\brief 
 *  Platform-dependent macro defining how RKH should post an event
 *  \a e to the queue \a qd in LIFO policy and retrieves the result of 
 *  that operation, i.e. TRUE (0) if an element was successfully 
 *  inserted to the queue, otherwise error code.	
 * 	
 * 	\note 
 * 	Typically, must be define it in the specific port file (rkhport.h).
 * 	Example:
 *
 * 	\code
 *	#define rkh_post_lifo( qd, e )									\
 *																	\
 *				queue_insert_lifo( (QD_T)(qd), &(e) )
 * 	\endcode
 *
 * 	\param qd		queue descriptor.
 * 	\param e	 	pointer to the event that is to be placed on the queue.  
 *					The size of the elements the queue will hold was defined when 
 *					the queue was created.
 * 	\return
 * 	TRUE (0) if the element was successfully inserted, 
 *	otherwise error code.
 *
 * 	\sa rkh_put_fifo(), rkh_put_lifo(), rkh_alloc_event(), 
 * 	rkh_set_static_event() and rkh_gc().
 */

#define rkh_post_lifo( qd, e )

/**
 * 	\brief 
 *  Platform-dependent macro defining how RKH should get an event
 *  \a e from the queue \a qd.
 *
 * 	\param qd		queue descriptor.
 * 	\param e 		pointer to the event structure into which the received 
 * 					item will be copied.
 * 	\return
 * 	TRUE (0) if an event was successfully removed from the queue, otherwise 
 * 	error code.
 * 	
 * 	\note 
 * 	Typically, must be define it in the specific port file (rkhport.h).
 * 	Example:
 *
 * 	\code
 *	#define rkh_get( qd, e )										\
 *																	\
 *				queue_remove( (QD_T)(qd), &(e) )
 * 	\endcode
 *
 * 	\sa rkh_put_fifo(), rkh_put_lifo(), rkh_alloc_event(), 
 * 	rkh_set_static_event() and rkh_gc().
 */

#define rkh_get( qd, e )

/**
 * 	\brief 
 *	Open the tracing session.
 *
 *	This is a platform-dependent function invoked through the macro 
 *	rkh_tropen(). 
 *	The application must implement this function. At a minimum, the 
 *	function must configure the trace stream by calling rkh_trinit().
 *	
 *	Example:
 *
 *	\code
 *	//	...in rkhport.h
 *
 *	#define rkh_tropen			rkh_trace_open
 *
 * 	//	...in some application module
 *
 *	void 
 *	my_rkh_trace_open( void )
 *	{
 *		RKHTRCFG_T *pcfg;
 *		
 *		rkh_trinit();
 *		rkh_trconfig( MY, RKH_TRLOG, RKH_TRPRINT );
 *		rkh_trcontrol( MY, RKH_TRSTART );
 *		
 *		if( ( fdbg = fopen( "../mylog.txt", "w+" ) ) == NULL )
 *		{
 *			perror( "Can't open file\n" );
 *			exit( EXIT_FAILURE );
 *		}
 *		fprintf( fdbg, 
 *			"---- RKH trace log session - "__DATE__" - "__TIME__" ----\n\n" );
 *		pcfg = rkh_trgetcfg( MY );
 *		if( pcfg->print == RKH_TRPRINT )
 *			printf( "---- RKH trace log session - 
 *					"__DATE__" - "__TIME__" ----\n\n" );
 *	}
 *	\endcode
 *
 * 	\note 
 * 	Typically, must be define it in the specific port file (rkhport.h).
 *
 * 	\sa \b rkhtrace.h file.
 */

#define rkh_tropen

/**
 * 	\brief 
 *	Close the tracing session.
 *
 *	This is a platform-dependent function invoked through the macro 
 *	rkh_trclose(). 
 *	The application must implement this function.
 *
 *	Example:
 *
 *	\code
 *	//	...in rkhport.h
 *
 *	#define rkh_trclose			rkh_trace_close
 *
 * 	//	...in some application module
 *
 *	void 
 *	rkh_trace_close( void )
 *	{
 *		fclose( fdbg );
 *	}
 *	\endcode
 *
 * 	\note 
 * 	Typically, must be define it in the specific port file (rkhport.h).
 *
 * 	\sa \b rkhtrace.h file.
 */

#define rkh_trclose

/**
 * 	\brief 
 *	Flush the trace stream.
 *
 *	This is a platform-dependent function invoked through the macro 
 *	rkh_trflush(). 
 * 	When the RKH trace an event, all the information related to it has to 
 * 	be stored somewhere before it can be retrieved, in order to be analyzed. 
 * 	This place is a trace stream. Frequently, events traced are stored in 
 * 	the stream until it is flushed.
 *
 *	Example:
 *
 *	\code
 *	//	...in rkhport.h
 *
 *	#define rkh_trflush				rkh_trace_flush
 *
 * 	//	...in some application module
 *
 * 	void 
 * 	rkh_trace_flush( void )
 * 	{
 * 		RKHTREVT_T te;
 * 		RKHTRCFG_T *pcfg;
 *
 * 		while( rkh_trgetnext( &te ) != RKH_TREMPTY )
 * 		{
 * 			pcfg = rkh_trgetcfg( te.smix );
 * 			if( pcfg->log == RKH_TRLOG )
 * 				fprintf( fdbg, "%05d [ %-16s ] - %s : %s\n",
 *													rkh_trgetts(),
 *													tremap[ te.id ],
 *													smmap[ te.smix ],
 *													format_trevt_args( &te ) );
 *			if( pcfg->print == RKH_TRPRINT )
 *				printf( "%05d [ %-16s ] - %s : %s\n",
 *													rkh_trgetts(),
 *													tremap[ te.id ],
 *													smmap[ te.smix ],
 *													format_trevt_args( &te ) );
 *		}
 *	}
 *	\endcode
 *
 * 	\note 
 * 	Typically, must be define it in the specific port file (rkhport.h).
 *
 * 	\sa \b rkhtrace.h file.
 */

#define rkh_trflush

#endif


#if RKH_TRACE == 1

	#ifndef rkh_tropen
		#error  "rkhport.h, When enabling RKH_TRACE must be defined the platform-dependent function rkh_trace_open() within application level."
	#endif

	#ifndef rkh_trclose
		#error  "rkhport.h, When enabling RKH_TRACE must be defined the platform-dependent function rkh_trace_close() within application level."
	#endif

	#ifndef rkh_trflush
		#error  "rkhport.h, When enabling RKH_TRACE must be defined the platform-dependent function rkh_trace_flush() within application level."
	#endif
#else
	#undef rkh_tropen
	#define rkh_tropen
	#undef rkh_trclose
	#define rkh_trclose
	#undef rkh_trflush
	#define rkh_trflush
#endif


#if RKH_TRACE == 1 && RKH_EN_TIMESTAMP == 1

	#ifndef rkh_trgetts
		#error  "rkhtrace.h, When enabling RKH_TRACE and RKH_EN_TIMESTAMP is set to one (1) must be defined the platform-dependent function rkh_trace_getts() within application level."
	#endif
#else
	#undef rkh_trgetts
	
	/**
	 * 	\brief
	 *	Retrieves a timestamp to be placed in a trace event.
	 * 
	 *	This is a platform-dependent function invoked through the macro 
	 *	rkh_trgetts(). 
	 *	The data returned is defined in compile-time by means of 
	 *	RKH_SIZEOF_TIMESTAMP preprocessor directive.
 	 *
	 *	Example:
	 *
	 *	\code
	 *	//	...in rkhport.h
	 *
	 *	#define rkh_trtrgetts				rkh_trace_getts
	 *
	 * 	//	...in some application module
	 *	
	 *	RKHTS_T 
	 *	rkh_trace_getts( void )
	 *	{
	 *		return ( RKHTS_T )clock();
	 *	}
	 *	\endcode
	 *
	 * 	\returns
	 * 	Timestamp (RKHTS_T data type).
 	 *
	 * 	\sa \b rkhtrace.h file.
	 */

	#define rkh_trgetts

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
 * 	Represents events without parameters.
 * 	
 * 	An event can have associated parameters, allowing the event 
 * 	instance to convey not only the occurrence of some interesting 
 * 	incident but also quantitative information regarding that occurrence.
 *	Implementing the single inheritance in C is very simply by literally
 *	embedding the base structure, RKHEVT_T in this case, as the first 
 *	member of the derived structure.
 * 	For example, the structure MYEVT_T derived from the base structure 
 * 	RKHEVT_T by embedding the RKHEVT_T instance as the first member of 
 *	MYEVT_T.
 *
 * 	\code
 * 	typedef struct
 * 	{
 * 		RKHEVT_T evt;	// base structure
 *		int x;			// parameter 'x'
 *		int y;			// parameter 'y'
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
 * 	\note
 * 	The RKH takes the \a 'e' member of RKHEVT_T structure for triggering a 
 * 	state transition.
 *
 * 	\sa rkh_put_fifo(), rkh_put_lifo(), rkh_alloc_event(), 
 * 	rkh_set_static_event() and rkh_gc().
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
 *
 * 	\sa rkh_put_fifo(), rkh_put_lifo(), rkh_alloc_event(), 
 * 	rkh_set_static_event() and rkh_gc().
 */

RKHEVT_T *rkh_ae( rkhuint8 es, RKHE_T e );


/*
 * 	For GNU compatibility.
 */

struct rkh_t;


/**
 * 	\brief
 * 	Entry action.
 *
 * 	The actions that are always executed when a state is entered 
 * 	should be specified as entry actions.
 * 	An entry function takes the state machine pointer as argument. 
 * 	This parameter is optional in compile-time according to 
 * 	\b RKH_EN_ENT_HSM_ARG macro.
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
 * 	\brief
 * 	Exit action.
 *
 * 	The actions that are always execute when a state is exited should be 
 * 	exit actions.
 * 	An exit function takes the state machine pointer as argument. 
 * 	This parameter is optional in compile-time according to 
 * 	\b RKH_EN_EXT_HSM_ARG.
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
 * 	\brief
 * 	Initialization action.
 *
 * 	The application code must trigger the initial transition explicitly 
 * 	by invoking rkh_init_hsm() function.
 * 	An init function takes the state machine pointer as argument. 
 * 	This parameter is optional in compile-time according to 
 * 	\b RKH_EN_INIT_HSM_ARG macro.
 */

#if RKH_EN_INIT_HSM_ARG == 1

	typedef void ( *RKHINIT_T )( const struct rkh_t *ph );

	#define rkh_exec_init( h )					\
	{											\
		if( (h)->romrkh->init_action != NULL )	\
			(*(h)->romrkh->init_action)( h );	\
	}

#else
	
	typedef void ( *RKHINIT_T )( void );

	#define rkh_exec_init( h )					\
	{											\
		if( (h)->romrkh->init_action != NULL )	\
			(*(h)->romrkh->init_action)();		\
	}

#endif


/**
 * 	\brief
 * 	Event preprocessor.
 *
 * 	Before sending the arrived event to state machine, it can be previously 
 * 	processed using the	event preprocessor function.
 * 	An action function takes the state machine pointer and the event 
 * 	pointer as arguments. The first parameter is optional in compile-time
 * 	according to \b RKH_EN_PPRO_HSM_ARG macro.
 */

#if RKH_EN_PPRO_HSM_ARG == 1

	typedef RKHE_T ( *RKHPPRO_T )( const struct rkh_t *ph, RKHEVT_T *pe );
	#define rkh_call_prepro(s,h,e)		(*(s)->prepro)( h, e )

#else

	typedef RKHE_T ( *RKHPPRO_T )( RKHEVT_T *pe );
	#define rkh_call_prepro(s,h,e)		(*(s)->prepro)( e )

#endif


/**
 * 	\brief
 * 	Actions.
 *
 * 	Actions are small atomic behaviors executed at specified points 
 * 	in a state machine. Actions are assumed to take an insignificant 
 * 	amount of time to execute and are noninterruptible.
 * 	An action function takes the state machine pointer and the event 
 * 	pointer as arguments. These parameters are optional in compile-time
 * 	according to \b RKH_EN_ACT_EVT_ARG and \b RKH_EN_ACT_HSM_ARG.
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
 * 	\brief
 * 	Guard.
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
 * 	according to \b RKH_EN_GRD_EVT_ARG and \b RKH_EN_GRD_HSM_ARG.
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
 * 	Maintains the basic information of a state.
 */

typedef struct rkhbase_t
{
	/**	
	 *	Contains the type of a particular state and can have 
	 *	the following values:
	 *
	 *	- \b RKH_COMPOSITE: 		composite state.
	 *	- \b RKH_BASIC: 			basic state.
	 *	- \b RKH_JUNCTION: 		junction pseudostate.
	 *	- \b RKH_CONDITIONAL: 		conditional pseudostate.
	 *	- \b RKH_SHISTORY: 		shadow history pseudostate.
	 *	- \b RKH_DHISTORY: 		deep history pseudostate.
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
	 *  \code
	 *  static
	 *  RKHE_T
	 *  preprocessor( RKHEVT_T *pe )
	 *  {
	 *  	...
	 *  }
	 *  
	 * 	typedef struct
	 * 	{
	 * 		RKHPPRO_T prepro; 	// extend the RKHPPRO_T class
	 * 		unsigned min:4;
	 * 		unsigned max:4;
	 * 		char *buff;
	 * 	} SDATA_T;
	 *
	 * 	static const SDATA_T option = { preprocessor, 4, 8, token1 };
	 *
	 *  RKH_CREATE_BASIC_STATE( S111, 0, set_x_1, 
	 *  								NULL, &S11, preprocessor ); 
	 * 	RKH_CREATE_BASIC_STATE( S22, 0, set_x_4, 
	 *  								NULL, &S2, (RKHPPRO_T*)&option ); 
	 * \endcode
	 */

	RKHPPRO_T prepro;
} RKHSREG_T;


/**
 * 	\brief 
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
 * 	Describes the state-machine's performance information.
 *
 * 	Defines the data structure into which the performance 
 * 	information for state machine is stored.
 */

typedef struct rkh_info_t
{
	rkhuint16 rcvevt;			/**<	# of received events */
	rkhuint16 exectr;			/**<	# of executed transitions */
} RKH_INFO_T;


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

typedef struct
{
	/**	
	 *	State machine descriptor. It's generally used for 
	 *	debugging and 'rktrace' module.
	 */

	rkhuint8 id;

	/**
	 * 	State machine properties. The available properties are
	 * 	enumerated in RKH_HPPTY_T enumeration in the rkh.h
	 * 	file.
	 */

	rkhuint8 ppty;

	/**	
	 *	State name string. String terminated in '\\0' that 
	 *	represents the name of state. It's generally used for 
	 *	debugging.
	 */
#if RKH_EN_HSM_NAME	== 1
	char *name;
#endif

	/** 
	 * 	Points to initial state. The initial state must be a
	 * 	composite state or basic state.
	 */

	rkhrom RKHSREG_T *init_state;

	/** 
	 * 	Points to initializing action function.
	 */

	RKHINIT_T init_action;

} ROMRKH_T;


/**
 * 	\brief 
 * 	Describes the state machine.
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
 *		RKH_T sm;		// base structure
 *		rkhuint8 x;		// private member
 *		rkhuint8 y;		// private member
 *	} MYSM_T;
 *
 * 	//	static instance of state machine object
 *	RKH_CREATE_HSM( MYSM_T, my, 0, HCAL, &S1, my_init, &mydata );
 *
 *	//	...dispatchig events
 *	rkh_engine( my, ( RKHEVT_T* )myevt );
 *	\endcode
 *
 *	\sa
 *	RKH_T structure definition for more information. Also, \link RKHEVT_T 
 *	single inheritance in C \endlink.
 */

typedef struct rkh_t
{
	/**
	 * 	Points to constant state machine properties
	 */
	
	rkhrom ROMRKH_T *romrkh;

	/** 
	 * 	Points to current state.
	 */

	rkhrom RKHSREG_T *state;

	/** 
	 * 	Points to optional state-machine's data.
	 */

#if RKH_EN_HSM_DATA == 1
	void *hdata;
#endif
	
	/** 
	 * 	Maintains the optional performance information.
	 */

#if RKH_EN_GET_INFO == 1
	RKH_INFO_T hinfo;
#endif	

} RKH_T;


#endif
