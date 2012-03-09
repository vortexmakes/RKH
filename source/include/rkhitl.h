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
#include "rkhtype.h"


/** 
 * 	Trace facility.
 */

#include "rkhtrace.h"

/**
 * 	Event data type and related macros.
 */

#include "rkhevt.h"


/**	
 * 	\brief
 *	This macro expands to the binary representation of the RKH version.
 *
 *	The version number is composed as 0xABCC, where:
 *	the number A (1-digit) denoted the major revision, the number B (1-digit)
 *	denoted the minor revision, and the number C (2-digit) indicated the 
 *	release number. For example, the code for 2.2.04 is 0x2204.
 *	
 *	Date: xx/xx/2012
 */

#define RKH_VERSION_CODE			0x2000U


/**
 * 	\brief
 * 	This macro retrieves a pointer to string describing the RKH version. 
 * 	For example, "2.2.04".
 */

#define RKH_RELEASE					rkh_version


/**
 * 	\brief
 * 	This is the macro used to build an integer version code from the 
 * 	individual numbers that build up a version number. 
 *
 * 	For example, RKH_VERSION(2,2,04) expands to 0x2204. This macro is very 
 * 	useful when needs to compare the current version and a known checkpoint.
 *
 * 	\param a		major revision
 * 	\param b		minor revision
 * 	\param c		release number
 */

#define RKH_VERSION( a, b, c )


/**	
 *	This macro is used to indicate the end of a transition table.
 */

#define RKH_ANY						((RKHE_T)(-1))


/* 	
 *  Verifies port file from rkhport.h included in rkhplat.h.
 */

#ifndef RKHROM
#error "rkhport.h, Missing RKHROM: Qualifier for ROM data storage. \
	See Porting chapter in readme file for more information"
#endif


#define FOREVER						for(;;)


/* 	
 *  Verifies configurations from rkhcfg.h include file.
 */

#ifndef RKH_EN_NATIVE_EQUEUE
	#error "rkhcfg.h, Missing RKH_RQ_EN: Enable (1) or Disable (0) native queue"
#else
	#if RKH_EN_NATIVE_EQUEUE == 1
		#if RKH_RQ_EN != 1
			#error "rkhcfg.h, When using the native event queue for SMAs must be enabled (1) the RKH_RQ_EN to include the (r) queue module"
		#endif
	#endif
#endif


#ifndef RKH_RQ_SIZEOF_NELEM
	#error "rkhcfg.h, Missing RKH_RQ_SIZEOF_NELEM, expected 8, 16 or 32"
#endif


#ifndef RKH_TIMER_SIZEOF_NTIMER
	#error "rkhcfg.h, Missing RKH_TIMER_SIZEOF_NTIMER, expected 8, 16 or 32"
#endif


#ifndef RKH_MP_SIZEOF_BSIZE
	#error "rkhcfg.h, Missing RKH_MP_SIZEOF_BSIZE: expected 8, 16 or 32"
#endif


#ifndef RKH_MP_SIZEOF_NBLOCK
	#error "rkhcfg.h, Missing RKH_MP_SIZEOF_NBLOCK: expected 8, 16 or 32"
#endif


#ifndef RKH_MP_EN
	#error "rkhcfg.h, Missing RKH_MP_EN: Enable (1) or Disable (0) native memory pool"
#endif


#ifndef RKH_MP_EN_GET_INFO
	#error "rkhcfg.h, Missing RKH_MP_EN_GET_INFO: Include (1) get information function"
#endif


#ifndef RKH_MP_EN_GET_BSIZE
	#error "rkhcfg.h, Missing RKH_MP_EN_GET_BSIZE: Include (1) get block size function"
#endif


#ifndef RKH_MP_EN_GET_NFREE
	#error "rkhcfg.h, Missing RKH_MP_EN_GET_NFREE: Include (1) get # of free blocks function"
#endif


#ifndef RKH_MP_EN_GET_LWM
	#error "rkhcfg.h, Missing RKH_MP_EN_GET_LWM: Include (1) get lowest # of free blocks function"
#endif


#ifndef RKH_MP_REDUCED
	#error "rkhcfg.h, Missing RKH_MP_REDUCED: Include (0) all memory pool facilities"
#endif


#ifndef RKH_RQ_EN
	#error "rkhcfg.h, Missing RKH_RQ_EN: Enable (1) or Disable (0) native queue"
#endif


#ifndef RKH_RQ_SIZEOF_NELEM
	#error "rkhcfg.h, Missing RKH_RQ_SIZEOF_NELEM: expected o, 16 or 32"
#endif


#ifndef RKH_RQ_EN_GET_LWMARK
	#error "rkhcfg.h, Missing RKH_RQ_EN_GET_LWMARK: Include (1) get queue low watermark function"
#endif


#ifndef RKH_RQ_EN_GET_INFO
	#error "rkhcfg.h, Missing RKH_RQ_EN_GET_INFO: Include (1) get queue information function"
#endif


#ifndef RKH_RQ_EN_READ
	#error "rkhcfg.h, Missing RKH_RQ_EN_READ: Include (1) queue read function"
#endif


#ifndef RKH_RQ_EN_DEPLETE
	#error "rkhcfg.h, Missing RKH_RQ_EN_DEPLETE: Include (1) queue deplete function"
#endif


#ifndef RKH_TIMER_EN
	#error "rkhcfg.h, Missing RKH_TIMER_EN: Enable (1) or Disable (0) native timer facility"
#endif


#ifndef RKH_TIMER_SIZEOF_NTIMER
	#error "rkhcfg.h, Missing RKH_TIMER_SIZEOF_NTIMER: expected 8, 16 or 32"
#endif


#if RKH_TIMER_EN_HOOK == 0
	#define rkh_mktimer( t,s,th )										\
				rkh_itim_init( (RKHT_T*)(t), (RKHE_T)(s), (RKH_THK_T)(th) )
#else
	#define rkh_mktimer( t,s,th )										\
				rkh_itim_init( (RKHT_T*)(t), (RKHE_T)(s) )
#endif


#ifndef RKH_TIMER_EN_GET_INFO
	#error "rkhcfg.h, Missing RKH_TIMER_EN_GET_INFO: Include (1) get timer information function"
#endif


#ifndef RKH_TIMER_EN_RESTART
	#error "rkhcfg.h, Missing RKH_TIMER_EN_RESTART: Include (1) restart timer function"
#endif


#if RKH_TR_EN == 1
	#if RKH_TR_EN_STRING == 1 && ( RKH_SMA_EN_STATE_NAME != 1 || RKH_SMA_EN_STATE_ID != 1 || RKH_SMA_EN_NAME != 1 )
	#error  "rkhcfg.h, when enabling RKH_TR_EN and RKH_TR_EN_STRING is set to one (1), must be set to one (1) both RKH_SMA_EN_STATE_NAME or RKH_SMA_EN_STATE_ID or RKH_SMA_EN_NAME"
	#endif
#endif

#ifndef RKH_SMA_EN_HCAL
	#error "rkhcfg.h, Missing RKH_SMA_EN_HCAL: Enable (1) or Disable (0) state nesting"
#endif

#ifndef RKH_SMA_MAX_HCAL_DEPTH
	#error "rkhcfg.h, Missing RKH_SMA_MAX_HCAL_DEPTH: Max. # of hierarchical levels"
#else
	#if RKH_SMA_MAX_HCAL_DEPTH == 0 || RKH_SMA_MAX_HCAL_DEPTH > 8
	#error  "rkhcfg.h, RKH_SMA_MAX_HCAL_DEPTH must be > 0 and <= 8"
	#endif
#endif

#ifndef RKH_SMA_MAX_TR_SEGS
#error "rkhcfg.h, Missing RKH_SMA_MAX_TR_SEGS: Max. # of transition segments"
#else
	#if RKH_SMA_MAX_TR_SEGS == 0 || RKH_SMA_MAX_TR_SEGS > 8
	#error  "rkhcfg.h, RKH_SMA_MAX_TR_SEGS must be > 0 and <= 8"
	#endif
#endif

#ifndef RKH_MAX_SMA
#error "rkhcfg.h, Missing RKH_MAX_SMA: Max. # of state machines applications"
#else
	#if RKH_MAX_SMA == 0 || RKH_MAX_SMA > 64
	#error  "rkhcfg.h, RKH_MAX_SMA must be > 0 and <= 64"
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

#ifndef RKH_SMA_EN_PSEUDOSTATE
	#error "rkhcfg.h, Missing RKH_SMA_EN_PSEUDOSTATE: Enable (1) or Disable (0) pseudostates."
#endif

#ifndef RKH_SMA_EN_DEEP_HISTORY
	#error "rkhcfg.h, Missing RKH_SMA_EN_DEEP_HISTORY: Include deep history. Must be set to one RKH_SMA_EN_PSEUDOSTATE."
#endif

#ifndef RKH_SMA_EN_SHALLOW_HISTORY
	#error "rkhcfg.h, Missing RKH_SMA_EN_SHALLOW_HISTORY: Include shallow history. Must be set to one RKH_SMA_EN_PSEUDOSTATE."
#endif

#ifndef RKH_SMA_EN_JUNCTION
	#error "rkhcfg.h, Missing RKH_SMA_EN_JUNCTION: Include junction. Must be set to one RKH_SMA_EN_PSEUDOSTATE."
#endif

#ifndef RKH_SMA_EN_CONDITIONAL	
	#error "rkhcfg.h, Missing RKH_SMA_EN_CONDITIONAL: Include conditional. Must be set to one RKH_SMA_EN_PSEUDOSTATE."
#endif

#ifndef RKH_SMA_EN_INIT_ARG_SMA
	#error "rkhcfg.h, Missing RKH_SMA_EN_INIT_ARG_SMA: Enable (1) or Disable (0) state machine arg from initialization action."
#endif

#ifndef RKH_SMA_EN_ENT_ARG_SMA
	#error "rkhcfg.h, Missing RKH_SMA_EN_ENT_ARG_SMA: Enable (1) or Disable (0) state machine arg from entry action."
#endif

#ifndef RKH_SMA_EN_EXT_ARG_SMA
	#error "rkhcfg.h, Missing RKH_SMA_EN_EXT_ARG_SMA: Enable (1) or Disable (0) state machine arg from exit action."
#endif

#ifndef RKH_SMA_EN_ACT_ARG_SMA
	#error "rkhcfg.h, Missing RKH_SMA_EN_ACT_ARG_SMA: Enable (1) or Disable (0) state machine arg from transition action."
#endif

#ifndef RKH_SMA_EN_ACT_ARG_EVT
	#error "rkhcfg.h, Missing RKH_SMA_EN_ACT_ARG_EVT: Enable (1) or Disable (0) event arg from guard function."
#endif

#ifndef RKH_SMA_EN_GRD_ARG_EVT
	#error "rkhcfg.h, Missing RKH_SMA_EN_GRD_ARG_EVT: Enable (1) or Disable (0) event arg from guard function."
#endif

#ifndef RKH_SMA_EN_GRD_ARG_SMA
	#error "rkhcfg.h, Missing RKH_SMA_EN_GRD_ARG_EVT: Enable (1) or Disable (0) state machine arg from guard function."
#endif

#ifndef RKH_SMA_EN_PPRO_ARG_SMA
	#error "rkhcfg.h, Missing RKH_SMA_EN_PPRO_ARG_SMA: Enable (1) or Disable (0) state machine arg from event preprocessor function."
#endif

#ifndef RKH_SMA_EN_STATE_NAME
	#error "rkhcfg.h, Missing RKH_SMA_EN_STATE_NAME: Include state name as string within state machine object."
#endif

#ifndef RKH_SMA_EN_STATE_ID
	#error "rkhcfg.h, Missing RKH_SMA_EN_STATE_ID: Include an ID number (also called descriptor) within state structure."
#endif

#ifndef RKH_SMA_EN_PPRO	
	#error "rkhcfg.h, Missing RKH_SMA_EN_PPRO: Include input preprocessor function within basic state object."
#endif

#ifndef RKH_SMA_EN_GET_INFO
	#error "rkhcfg.h, Missing RKH_SMA_EN_GET_INFO: Include get information function."
#endif

#ifndef RKH_EN_REENTRANT
	#error "rkhcfg.h, Missing RKH_EN_REENTRANT: Enable (1) or Disable (0) state machine re-entrancy."
#endif

#ifndef RKH_TR_EN
	#error "rkhcfg.h, Missing RKH_TR_EN: Enable (1) or Disable (0) trace mode."
#endif

#ifndef RKH_TR_ALL
	#error "rkhcfg.h, Missing RKH_TR_ALL: Include all trace points."
#endif

#ifndef RKH_TR_EN_EVENT
	#error "rkhcfg.h, Missing RKH_TR_EN_EVENT: Enable (1) or Disable (0) trace point - triggering event."
#endif

#ifndef RKH_TR_EN_TRN_SRC
	#error "rkhcfg.h, Missing RKH_TR_EN_TRN_SRC: Enable (1) or Disable (0) trace point - transition source state."
#endif

#ifndef RKH_TR_EN_TRN_TGT	
	#error "rkhcfg.h, Missing RKH_TR_EN_TRN_TGT: Enable (1) or Disable (0) trace point - transition target state."
#endif

#ifndef RKH_TR_EN_NXT_STATE
	#error "rkhcfg.h, Missing RKH_TR_EN_NXT_STATE: Enable (1) or Disable (0) trace point - next state."
#endif

#ifndef RKH_TR_EN_INT_TRAN	
	#error "rkhcfg.h, Missing RKH_TR_EN_INT_TRAN: Enable (1) or Disable (0) trace point - internal transition."
#endif

#ifndef RKH_TR_EN_ENTRY
	#error "rkhcfg.h, Missing RKH_TR_EN_ENTRY: Enable (1) or Disable (0) trace point - entry state."
#endif

#ifndef RKH_TR_EN_EXIT	
	#error "rkhcfg.h, Missing RKH_TR_EN_EXIT: Enable (1) or Disable (0) trace point - exit state."
#endif

#ifndef RKH_TR_EN_INIT_HSM
	#error "rkhcfg.h, Missing RKH_TR_EN_INIT_HSM: Enable (1) or Disable (0) trace point - initializing state machine."
#endif

#ifndef RKH_TR_EN_SGT
	#error "rkhcfg.h, Missing RKH_TR_EN_SGT: Enable (1) or Disable (0) trace point - target state of transition segment."
#endif

#ifndef RKH_TR_EN_RTN_CODE
	#error "rkhcfg.h, Missing RKH_TR_EN_RTN_CODE: Enable (1) or Disable (0) trace point - code returned by rkh_dispatch() function."
#endif

#ifndef RKH_TR_EN_NUM_ENEX
	#error "rkhcfg.h, Missing RKH_TR_EN_NUM_ENEX: Enable (1) or Disable (0) trace point - # of enter and exited states."
#endif

#ifndef RKH_TR_EN_NUM_ACTSGT
	#error "rkhcfg.h, Missing RKH_TR_EN_NUM_ACTSGT: Enable (1) or Disable (0) trace point - # of transition actions to be executed and number of transition segments."
#endif

#ifndef RKH_TR_EN_TIMESTAMP
	#error "rkhcfg.h, Missing RKH_TR_EN_TIMESTAMP: Enable (1) or Disable (0) trace timestamp."
#endif

#ifndef RKH_TR_SIZEOF_TIMESTAMP
	#error "rkhcfg.h, Missing RKH_TR_SIZEOF_TIMESTAMP: Defines the size of timestamp [in bits]: 8, 16 or 32."
#endif

#ifndef RKH_TR_MAX_NUM_TRACES
	#error "rkhcfg.h, Missing RKH_TR_MAX_NUM_TRACES: Max. number of trace events in the stream."
#else
	#if RKH_TR_MAX_NUM_TRACES == 0 || RKH_TR_MAX_NUM_TRACES > 256
	#error  "rkhcfg.h, RKH_TR_MAX_NUM_TRACES must be > 0 and <= 256"
	#endif
#endif

#ifndef RKH_TR_EN_STRING
	#error "rkhcfg.h, Missing RKH_TR_EN_STRING: Enable (1) or Disable (0) the string argument of trace event."
#endif

#ifndef RKH_TR_MAX_STRING_SIZE
	#error "rkhcfg.h, Missing RKH_TR_MAX_STRING_SIZE: Defines the size of string argument of trace event."
#else
	#if RKH_TR_MAX_STRING_SIZE == 0 || RKH_TR_MAX_STRING_SIZE > 128
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


#if RKH_SMA_EN_ID == 1
	#if RKH_SMA_EN_NAME	== 1
		#if RKH_SMA_EN_IEVENT == 1
			#define MKRRKH(prio,ppty,n,id,is,ia,ie)				\
							{(prio),(ppty),#n,(id),(is),(ia),(ie)}
		#else
			#define MKRRKH(prio,ppty,n,id,is,ia,ie)				\
							{(prio),(ppty),#n,(id),(is),(ia)}
		#endif
	#else
		#if RKH_SMA_EN_IEVENT == 1
			#define MKRRKH(prio,ppty,n,id,is,ia,ie)				\
							{(prio),(ppty),(id),(is),(ia),(ie)}
		#else
			#define MKRRKH(prio,ppty,n,id,is,ia,ie)				\
							{(prio),(ppty),(id),(is),(ia)}
		#endif
	#endif
#else
	#if RKH_SMA_EN_NAME	== 1
		#if RKH_SMA_EN_IEVENT == 1
			#define MKRRKH(prio,ppty,n,id,is,ia,ie)				\
							{(prio),(ppty),#n,(is),(ia),(ie)}
		#else
			#define MKRRKH(prio,ppty,n,id,is,ia,ie)				\
							{(prio),(ppty),#n,(is),(ia)}
		#endif
	#else
		#if RKH_SMA_EN_IEVENT == 1
			#define MKRRKH(prio,ppty,n,id,is,ia,ie)				\
							{(prio),(ppty),(is),(ia),(ie)}
		#else
			#define MKRRKH(prio,ppty,n,id,is,ia,ie)				\
							{(prio),(ppty),(is),(ia)}
		#endif
	#endif
#endif


#define MKSMA( rr, s )					\
						{ (rr), (s) }


#if RKH_SMA_EN_STATE_NAME == 1
	#if RKH_SMA_EN_STATE_ID == 1
		#define mkbase(t,id,name)			{t,id,#name}
	#else
		#define mkbase(t,id,name)			{t,#name}
	#endif
#else
	#if RKH_SMA_EN_STATE_ID == 1
		#define mkbase(t,id,name)			{t,id}
	#else
		#define mkbase(t,id,name)			{t}
	#endif
#endif


#if RKH_SMA_EN_HCAL == 1
	#if RKH_SMA_EN_PPRO == 1
		#define mkbasic(en,ex,p,n,pp)		en,ex,p,n##_trtbl,NULL,NULL,pp
		#define mkcomp(en,ex,p,n,d,h)		en,ex,p,n##_trtbl,d,h,NULL
	#else
		#define mkbasic(en,ex,p,n,pp)		en,ex,p,n##_trtbl,NULL,NULL
		#define mkcomp(en,ex,p,n,d,h)		en,ex,p,n##_trtbl,d,h
	#endif
#else
	#if RKH_SMA_EN_PPRO == 1
		#define mkbasic(en,ex,p,n,pp)		n##_trtbl,pp
		#define mkcomp(en,ex,p,n,d,h)		n##_trtbl,NULL
	#else
		#define mkbasic(en,ex,p,n,pp)		n##_trtbl
		#define mkcomp(en,ex,p,n,d,h)		n##_trtbl
	#endif
#endif


#ifndef RKH_ASSERT
	#define RKH_ASSERT		0
#endif


#if RKH_EN_DYNAMIC_EVENT == 1
	#define mksevt( evt, es )											\
								((RKHEVT_T*)(evt))->e = (RKHE_T)es;		\
								((RKHEVT_T*)(evt))->dynamic_ = 0;
	#define mkievt( evt, es )											\
								RKHROM RKHEVT_T evt = { es, 0 }
#else
	#define mksevt( evt, es )											\
								((RKHEVT_T*)(evt))->e = (RKHE_T)es;
	#define mkievt( evt, es )											\
								RKHROM RKHEVT_T evt = { es }
#endif


#ifndef RKH_DIS_INTERRUPT
	#error  "rkhport.h, Must be defined the platform-dependent macro RKH_DIS_INTERRUPT"
#endif

#ifndef RKH_ENA_INTERRUPT
	#error  "rkhport.h, Must be defined the platform-dependent macro RKH_ENA_INTERRUPT"
#endif


#ifndef RKH_CRITICAL_METHOD
	#define RKH_CRITICAL_METHOD		2
#endif

/**
 * 	RKH need to disable interrupts in order to access critical sections of 
 * 	code, and re-enable interrupts when done. This allows RKH to protect 
 * 	critical code from being entered simultaneously from either multiple 
 * 	SMAs or ISRs. Every processor generally provide instructions to 
 * 	disable/enable interrupts and the C compiler must have a mechanism to 
 * 	perform these operations directly from C. Some compilers will allows 
 * 	to insert in-line assembly language statements in the C source code. 
 * 	This makes it quite easy to insert processor instructions to enable and 
 * 	disable interrupts. Other compilers will actually contain language 
 * 	extensions to enable and disable interrupts directly from C. To hide the 
 * 	implementation method chosen by the compiler manufacturer, RKH defines 
 * 	two macros to disable and enable interrupts: 
 * 	RKH_ENTER_CRITICAL() and RKH_EXIT_CRITICAL().
 *
 * 	Method #1:
 *
 * 	The first and simplest way to implement these two macros is to invoke 
 * 	the processor instruction to disable interrupts for RKH_ENTER_CRITICAL() 
 * 	and the enable interrupts instruction for RKH_EXIT_CRITICAL(). There is, 
 * 	however, a little problem with this scenario. If it's called the RKH 
 * 	function with interrupts disabled then, upon return from RKH, interrupts 
 * 	would be enabled!.
 * 	
 * 	Method #2:
 *
 * 	The second way to implement RKH_ENTER_CRITICAL() is to save the interrupt 
 * 	disable status onto the stack and then, disable interrupts. 
 * 	RKH_EXIT_CRITICAL() would simply be implemented by restoring the interrupt 
 * 	status from the stack. Using this scheme, if it's called a RKH service 
 * 	with either interrupts enabled or disabled then, the status would be 
 * 	preserved across the call. If calls a RKH service with interrupts disabled,
 * 	is potentially extending the interrupt latency of application. The 
 * 	application can use RKH_ENTER_CRITICAL() and RKH_EXIT_CRITICAL() to also 
 * 	protect critical sections of code. As a general rule, should always call 
 * 	RKH services with interrupts enabled!.
 */

#if RKH_CRITICAL_METHOD == 1
	#define RKH_iSR_CRITICAL
	#define RKH_iENTER_CRITICAL()		RKH_DIS_INTERRUPT()
	#define RKH_iEXIT_CRITICAL()		RKH_ENA_INTERRUPT()
#elif RKH_CRITICAL_METHOD == 2

	#ifdef RKH_CPUSR_TYPE
		/** 
		 * 	\brief
		 * 	This macro is internal to RKH and the user application should 
		 * 	not call it.
		 */

		#define RKH_iSR_CRITICAL			RKH_CPUSR_TYPE sr

		/** 
		 * 	\brief
		 * 	This macro is internal to RKH and the user application should 
		 * 	not call it.
		 */

		#define RKH_iENTER_CRITICAL()		RKH_ENTER_CRITICAL( sr )

		/** 
		 * 	\brief
		 * 	This macro is internal to RKH and the user application should 
		 * 	not call it.
		 */

		#define RKH_iEXIT_CRITICAL()		RKH_EXIT_CRITICAL( sr )
	#else
		#define RKH_iSR_CRITICAL
		#define RKH_iENTER_CRITICAL()		RKH_ENTER_CRITICAL( dummy )
		#define RKH_iEXIT_CRITICAL()		RKH_EXIT_CRITICAL( dummy )
	#endif
#else
	#error "RKH_CRITICAL_METHOD defined incorrectly, expected 1, or 2"
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

//#define RKH_DYNE_NUM_POOLS

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
 * 				rkh_mp_init( (mpd), (pm), (rkint16)(ps),			\
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

//#define rkh_dyne_init( mpd, pm, ps, bs )

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

//#define rkh_dyne_event_size( mpd )

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

//#define rkh_dyne_get( mpd, e )

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

//#define rkh_dyne_put( mpd, e )

#endif


#ifndef RKH_HK_EN_DISPATCH
	#error "rkhcfg.h, Missing RKH_HK_EN_DISPATCH: Include (1) or remove (0) the dispatch hook function"
#else
	#if RKH_HK_EN_DISPATCH == 1
		#define RKH_HK_DISPATCH( sma, e )		rkh_hk_dispatch( sma, e )
	#elif RKH_HK_EN_DISPATCH == 0
		#define RKH_HK_DISPATCH( sma, e )
	#else
		#define RKH_HK_DISPATCH( sma, e )
		#error "rkhcfg.h, Wrong RKH_HK_EN_DISPATCH definition: expected 0 or 1"
	#endif
#endif


#ifndef RKH_HK_EN_SIGNAL
	#error "rkhcfg.h, Missing RKH_HK_EN_SIGNAL: Include (1) or remove (0) the signal hook function"
#else
	#if RKH_HK_EN_SIGNAL == 1
		#define RKH_HK_SIGNAL( e )		rkh_hk_signal( e )
	#elif RKH_HK_EN_SIGNAL == 0
		#define RKH_HK_SIGNAL( e )
	#else
		#define RKH_HK_SIGNAL( e )
		#error "rkhcfg.h, Wrong RKH_HK_EN_SIGNAL definition: expected 0 or 1"
	#endif
#endif


#ifndef RKH_HK_EN_TIMEOUT
	#error "rkhcfg.h, Missing RKH_HK_EN_TIMEOUT: Include (1) or remove (0) the timeout hook function"
#else
	#if RKH_HK_EN_TIMEOUT == 1
		#define RKH_HK_TIMEOUT( t )		rkh_hk_timeout( t )
	#elif RKH_HK_EN_TIMEOUT == 0
		#define RKH_HK_TIMEOUT( t )
	#else
		#define RKH_HK_TIMEOUT( t )
		#error "rkhcfg.h, Wrong RKH_HK_EN_TIMEOUT definition: expected 0 or 1"
	#endif
#endif


#ifndef RKH_HK_EN_START
	#error "rkhcfg.h, Missing RKH_HK_EN_START: Include (1) or remove (0) the start hook function"
#else
	#if RKH_HK_EN_START == 1
		#define RKH_HK_START()			rkh_hk_start()
	#elif RKH_HK_EN_START == 0
		#define RKH_HK_START()
	#else
		#define RKH_HK_START()
		#error "rkhcfg.h, Wrong RKH_HK_EN_START definition: expected 0 or 1"
	#endif
#endif


#ifndef RKH_HK_EN_EXIT
	#error "rkhcfg.h, Missing RKH_HK_EN_EXIT: Include (1) or remove (0) the exit hook function"
#else
	#if RKH_HK_EN_EXIT == 1
		#define RKH_HK_EXIT()			rkh_hk_exit()
	#elif RKH_HK_EN_EXIT == 0
		#define RKH_HK_EXIT()
	#else
		#define RKH_HK_EXIT()
		#error "rkhcfg.h, Wrong RKH_HK_EN_EXIT definition: expected 0 or 1"
	#endif
#endif


/*
 * 	For GNU compatibility.
 */

struct rkh_t;


/**
 * 	\brief
 * 	Entry action.
 *
 * 	The actions that are always executed when a state is entered 
 * 	should be specified as entry actions. UML statecharts provide optional 
 * 	entry and exit actions, which are associated with states rather than 
 * 	transitions, as in a Moore automaton.
 * 	An entry function takes the state machine pointer as argument. 
 * 	This argument is optional, thus it could be eliminated in 
 * 	compile-time by means of RKH_SMA_EN_ENT_ARG_SMA.
 *
 * 	\note
 * 	This callback is referenced from RKH_CREATE_COMP_STATE() and 
 * 	RKH_CREATE_BASIC_STATE() macros.
 * 	\b RKH_SMA_EN_ENT_ARG_SMA macro.
 */


#if RKH_SMA_EN_ENT_ARG_SMA == 1
	
	typedef void ( *RKHENT_T )( const struct rkhsma_t *sma );

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
 * 	exit actions. UML statecharts provide optional entry and exit actions, 
 * 	which are associated with states rather than transitions, as in a 
 * 	Moore automaton.
 * 	An exit function takes the state machine pointer as argument. 
 * 	This argument is optional, thus it could be eliminated in 
 * 	compile-time by means of RKH_SMA_EN_EXT_ARG_SMA.
 *
 * 	\note
 * 	This callback is referenced from RKH_CREATE_COMP_STATE() and 
 * 	RKH_CREATE_BASIC_STATE() macros.
 */

#if RKH_SMA_EN_EXT_ARG_SMA == 1

	typedef void ( *RKHEXT_T )( const struct rkhsma_t *sma );

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
 * 	Frequently, the state transition originating at the black ball is called 
 * 	the initial transition. Such transition designates the first active state 
 * 	after the state machine object is created. An initial transition can have 
 * 	associated actions, which in the UML notation are enlisted after the forward 
 * 	slash ( / ). In RKH framework, the application code must trigger the initial 
 * 	transition explicitly by invoking rkh_init_hsm() function.
 * 	An init action takes the state machine pointer as argument. 
 * 	This argument is optional, thus it could be eliminated in 
 * 	compile-time by means of RKH_SMA_EN_INIT_ARG_SMA.
 *
 * 	\note
 * 	This callback is referenced from RKH_CREATE_HSM() macro.
 */

#if RKH_SMA_EN_INIT_ARG_SMA == 1 && RKH_SMA_EN_INIT_ARG_IE == 1
	typedef void ( *RKHINIT_T )( const struct rkhsma_t *sma, 
										const struct rkhevt_t *e );
	#define rkh_exec_init( h )										\
	{																\
		if( (h)->romrkh->iaction != NULL )							\
			(*(h)->romrkh->iaction)( (h), (h)->romrkh->ievent );	\
	}
#elif RKH_SMA_EN_INIT_ARG_SMA == 1 && RKH_SMA_EN_INIT_ARG_IE == 0
	typedef void ( *RKHINIT_T )( const struct rkhsma_t *sma );
	#define rkh_exec_init( h )					\
	{											\
		if( (h)->romrkh->iaction != NULL )		\
			(*(h)->romrkh->iaction)( (h) );		\
	}
#elif RKH_SMA_EN_INIT_ARG_SMA == 0 && RKH_SMA_EN_INIT_ARG_IE == 1
	typedef void ( *RKHINIT_T )( const struct rkhevt_t *e );
	#define rkh_exec_init( h )								\
	{														\
		if( (h)->romrkh->iaction != NULL )					\
			(*(h)->romrkh->iaction)( (h)->romrkh->ievent );	\
	}
#else
	typedef void ( *RKHINIT_T )( void );
	#define rkh_exec_init( h )				\
	{										\
		if( (h)->romrkh->iaction != NULL )	\
			(*(h)->romrkh->iaction)();		\
	}
#endif


/**
 * 	\brief
 * 	Event preprocessor.
 *
 * 	Before sending the arrived event to state machine, it can be previously 
 * 	processed using the	event preprocessor function.
 * 	The RKH framework provides optional event preprocessor 
 * 	action, which are associated with states rather than transitions, 
 * 	as in a Moore automaton.
 * 	This action takes the state machine pointer and the event 
 * 	pointer as arguments. 
 * 	This argument is optional, thus it could be eliminated in 
 * 	compile-time by means of RKH_SMA_EN_PPRO_ARG_SMA.
 *
 * 	\note
 * 	This callback is referenced from RKH_CREATE_COMP_STATE() and 
 * 	RKH_CREATE_BASIC_STATE() macros.
 */

#if RKH_SMA_EN_PPRO_ARG_SMA == 1

	typedef RKHE_T ( *RKHPPRO_T )( const struct rkhsma_t *sma, RKHEVT_T *pe );
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
 * 	amount of time to execute and are noninterruptible. UML statecharts 
 * 	are extended state machines with characteristics of both Mealy and 
 * 	Moore automata. In statecharts, actions generally depend on both 
 * 	the state of the system and the triggering event, as in a Mealy 
 * 	automaton. Additionally, UML statecharts provide optional entry and 
 * 	exit actions, which are associated with states rather than transitions, 
 * 	as in a Moore automaton.
 * 	An action function takes the state machine pointer and the event 
 * 	pointer as arguments. 
 * 	These arguments are optional, thus they could be eliminated in 
 * 	compile-time by means of RKH_SMA_EN_ACT_ARG_EVT and \b 
 * 	RKH_SMA_EN_ACT_ARG_SMA.
 *
 * 	\note
 * 	This callback is referenced from RKH_TRREG() and RKH_TRINT()macro. 
 */

#if RKH_SMA_EN_ACT_ARG_EVT == 1 && RKH_SMA_EN_ACT_ARG_SMA == 1

	typedef void (*RKHACT_T)( const struct rkhsma_t *sma, RKHEVT_T *pe );
	#define rkh_call_action(h,e)	(*CA( q ))( h, e )

#elif RKH_SMA_EN_ACT_ARG_EVT == 1 && RKH_SMA_EN_ACT_ARG_SMA == 0
	
	typedef void (*RKHACT_T)( RKHEVT_T *pe );
	#define rkh_call_action(h,e)	(*CA( q ))( e )

#elif RKH_SMA_EN_ACT_ARG_EVT == 0 && RKH_SMA_EN_ACT_ARG_SMA == 1
	
	typedef void (*RKHACT_T)( const struct rkhsma_t *sma );
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
 *	Each condition connector can have one special branch with a guard 
 *	labeled rkh_else, which is taken if all the guards on the other 
 *	branches are false. 
 * 	A guard function takes the state machine pointer and the event 
 * 	pointer as arguments. 
 * 	These arguments are optional, thus they could be eliminated in 
 * 	compile-time by means of \b RKH_SMA_EN_GRD_ARG_EVT and 
 * 	\b RKH_SMA_EN_GRD_ARG_SMA.
 *
 * 	\note
 * 	This callback is referenced from RKH_BRANCH() macro. 
 */

#if RKH_SMA_EN_GRD_ARG_EVT == 1 && RKH_SMA_EN_GRD_ARG_SMA == 1

	typedef HUInt (*RKHGUARD_T)( const struct rkhsma_t *sma, RKHEVT_T *pe );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)( h, e )
	HUInt rkh_else( const struct rkhsma_t *sma, RKHEVT_T *pe );

#elif RKH_SMA_EN_GRD_ARG_EVT == 1 && RKH_SMA_EN_GRD_ARG_SMA == 0
	
	typedef HUInt (*RKHGUARD_T)( RKHEVT_T *pe );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)( e )
	HUInt rkh_else( RKHEVT_T *pe );


#elif RKH_SMA_EN_GRD_ARG_EVT == 0 && RKH_SMA_EN_GRD_ARG_SMA == 1
	
	typedef HUInt (*RKHGUARD_T)( const struct rkhsma_t *sma );
	#define rkh_call_guard(t,h,e)	(*(t)->guard)( h )
	HUInt rkh_else( const struct rkhsma_t *sma );

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
 	 * 	\brief
	 * 	State type.
	 *
	 *	Contains the type of a particular state and can have 
	 *	the following values:
	 *
	 *	- \b RKH_COMPOSITE: 	composite state.
	 *	- \b RKH_BASIC: 		basic state.
	 *	- \b RKH_JUNCTION: 		junction pseudostate.
	 *	- \b RKH_CONDITIONAL: 	conditional pseudostate.
	 *	- \b RKH_SHISTORY: 		shadow history pseudostate.
	 *	- \b RKH_DHISTORY: 		deep history pseudostate.
	 */

	HUInt type;					

	/**	
 	 * 	\brief
	 *	State ID. 
	 *
	 *	This number isn't internally used by RKH framework.
	 */

#if RKH_SMA_EN_STATE_ID == 1
	HUInt id;
#endif

	/**	
 	 * 	\brief
	 *	State name. 
	 *
	 *	String terminated in '\\0' that represents the name 
	 *	of state. It's generally used for debugging.
	 */
#if RKH_SMA_EN_STATE_NAME == 1
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
 	 * 	\brief
	 *  Triggering event.
	 */

	RKHE_T event;
	
	/**	
 	 * 	\brief
	 *	Points to guard function.
	 */

	RKHGUARD_T guard;
	
	/** 	
 	 * 	\brief
	 *  Points to transition action.
	 */

	RKHACT_T action;

	/** 	
 	 * 	\brief
	 *  Points to target state.
	 */

	RKHROM void *target;
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
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

#if RKH_SMA_EN_HCAL == 1
	/**	
 	 * 	\brief
	 *	Points to entry action.
	 */

	RKHENT_T enter;

	/**	
 	 * 	\brief
	 *	Points to exit action.
	 */

	RKHEXT_T exit;

	/**	
 	 * 	\brief
	 *	Points to state's parent.
	 */

	RKHROM struct rkhsreg_t *parent;
#endif

	/**	
 	 * 	\brief
	 *	Points to state transition table.
	 */

	RKHROM struct rkhtr_t *trtbl;

#if RKH_SMA_EN_HCAL == 1
	/**	
 	 * 	\brief
	 *	Points to state's default child.
	 */

	RKHROM void *defchild;

	/**	
 	 * 	\brief
	 *	Points to state's history. 
	 */

	RKHROM struct rkhshist_t *history;
#endif

	/**	
 	 * 	\brief
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
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
 	 * 	\brief
	 *	Points to branch table.
	 */

	RKHROM struct rkhtr_t *trtbl;
} RKHSCOND_T;


/**
 * 	\brief 
 * 	Describes the junction pseudostate.
 */

typedef struct rkhsjunct_t
{
	/**	
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
 	 * 	\brief
	 *	Points to action function.
	 */

	RKHACT_T action;

	/**	
 	 * 	\brief
	 *	Points to target state or pseudostate.
	 */

	RKHROM void *target;
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
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
 	 * 	\brief
	 *	Points to state's parent.
	 */

	RKHROM RKHSREG_T *parent;

	/**	
 	 * 	\brief
	 *	Points to RAM memory location which stores
	 *	the state's history.
	 */

	RKHROM RKHSREG_T **target;
} RKHSHIST_T;


#endif
