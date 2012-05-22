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

#include "rkhtrc.h"

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

#define RKH_VERSION_CODE			0x2100U


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


	                                                  /* macros for casting */
#define CB( p )						((RKHBASE_T*)(p))
#define CST( p )					((RKHST_T*)(p))
#define CCMP( p )					((RKHSCMP_T*)(p))
#define CBSC( p )					((RKHSBSC_T*)(p))
#define CCD( p )					((RKHSCOND_T*)(p))
#define CJ( p )						((RKHSJUNC_T*)(p))
#define CH( p )						((RKHSHIST_T*)(p))
#define CSBM( p )					((RKHSSBM_T*)(p))
#define CRSM( p )					((RKHRSM_T*)(p))
#define CM( p )						((RKHROM RKHSMA_T*)(p))
#define CT( p )						((RKHROM RKHTR_T*)(p))
#define CPT( p )					((RKHROM struct rkhscmp_t*)(p))
#define CPP( p )					((RKHPPRO_T)(p))
#define CG( p )						((RKHGUARD_T)(p))
#define CA( p )						((RKHACT_T)(p))
#define CENP( p )					((RKHSENP_T*)(p))
#define CEXP( p )					((RKHSEXP_T*)(p))
#define CENPCN( p )					((RKHENPCN_T*)(p))
#define CEXPCN( p )					((RKHEXPCN_T*)(p))
#define CE( p )						((RKHEVT_T*)(p))


/* 	
 *  Verifies configurations from rkhcfg.h include file.
 */

#ifndef RKH_EN_NATIVE_EQUEUE
	#error "rkhcfg.h, Missing RKH_EN_NATIVE_EQUEUE: Enable (1) or Disable (0) native queue"
#else
	#if RKH_EN_NATIVE_EQUEUE == 1 && RKH_RQ_EN != 1
		#error "rkhcfg.h, When using the native event queue for SMAs must be enabled (1) the RKH_RQ_EN to include the (r) queue module"
	#endif
#endif


#ifndef RKH_EN_DYNAMIC_EVENT
	#error "rkhcfg.h, Missing RKH_EN_DYNAMIC_EVENT: Enable (1) or Disable (0) dynamic event support"
#else
	#if RKH_EN_DYNAMIC_EVENT == 0 && RKH_EN_NATIVE_DYN_EVENT != 0
		#error "rkhcfg.h, When disabling the dynamic event support must be disabled (0) the RKH_EN_NATIVE_DYN_EVENT."
	#endif
	#if RKH_EN_DYNAMIC_EVENT == 1 && RKH_MAX_EPOOL == 0
		#error "rkhcfg.h, When enabling the dynamic event support the RKH_MAX_EPOOL must be != 0"
	#endif
#endif


#ifndef RKH_EN_NATIVE_DYN_EVENT
	#error "rkhcfg.h, Missing RKH_EN_NATIVE_DYN_EVENT: Enable (1) or Disable (0) native dynamic event support."
#else
	#if RKH_EN_NATIVE_DYN_EVENT == 1 && RKH_MP_EN != 1
		#error "rkhcfg.h, When using the native dynamic memory management must be enabled (1) the RKH_MP_EN to include the memory pool module."
	#endif
#endif


#ifndef RKH_RQ_SIZEOF_NELEM
	#error "rkhcfg.h, Missing RKH_RQ_SIZEOF_NELEM, expected 8, 16 or 32"
#endif


#ifndef RKH_TIM_SIZEOF_NTIMER
	#error "rkhcfg.h, Missing RKH_TIM_SIZEOF_NTIMER, expected 8, 16 or 32"
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


#ifndef RKH_TIM_EN
	#error "rkhcfg.h, Missing RKH_TIM_EN: Enable (1) or Disable (0) native timer facility"
#endif


#ifndef RKH_TIM_SIZEOF_NTIMER
	#error "rkhcfg.h, Missing RKH_TIM_SIZEOF_NTIMER: expected 8, 16 or 32"
#endif


#if RKH_TIM_EN_HOOK == 0
	#define rkh_mktimer( t,s,th )										\
				rkh_tim_init_( (RKHT_T*)(t), (RKHE_T)(s) )
#else
	#define rkh_mktimer( t,s,th )										\
				rkh_tim_init_( (RKHT_T*)(t), (RKHE_T)(s), (RKH_THK_T)(th) )
#endif


#ifndef RKH_TIM_EN_GET_INFO
	#error "rkhcfg.h, Missing RKH_TIM_EN_GET_INFO: Include (1) get timer information function"
#endif


#ifndef RKH_TIM_EN_RESTART
	#error "rkhcfg.h, Missing RKH_TIM_EN_RESTART: Include (1) restart timer function"
#endif


#if RKH_TRC_EN == 1 && RKH_TRC_EN_SM == 1
	#if RKH_SMA_EN_STATE_ID != 1
		#error  "rkhcfg.h, When enabling RKH_TRC_EN and RKH_TRC_EN_SM must be set to one (1) RKH_SMA_EN_STATE_ID"
	#endif
#endif

#if RKH_TRC_EN == 1 && RKH_TRC_EN_SMA == 1
	#if RKH_SMA_EN_ID != 1
		#error  "rkhcfg.h, When enabling RKH_TRC_EN and RKH_TRC_EN_SMA must be set to one (1) RKH_SMA_EN_ID"
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

#ifndef RKH_SMA_MAX_TRC_SEGS
#error "rkhcfg.h, Missing RKH_SMA_MAX_TRC_SEGS: Max. # of transition segments"
#else
	#if RKH_SMA_MAX_TRC_SEGS == 0 || RKH_SMA_MAX_TRC_SEGS > 8
	#error  "rkhcfg.h, RKH_SMA_MAX_TRC_SEGS must be > 0 and <= 8"
	#endif
#endif

#ifndef RKH_MAX_SMA
#error "rkhcfg.h, Missing RKH_MAX_SMA: Max. # of state machines applications"
#else
	#if RKH_MAX_SMA == 0 || RKH_MAX_SMA > 64
	#error  "rkhcfg.h, RKH_MAX_SMA must be > 0 and <= 64"
	#endif
#endif

#ifndef RKH_EN_DEFERRED_EVENT
	#error "rkhcfg.h, Missing RKH_EN_DEFERRED_EVENT: Enable (1) or Disable (0) deferred event support. For using this feature the dynamic event support must be set to one."
#else
	#if RKH_EN_DEFERRED_EVENT == 1 && RKH_EN_DYNAMIC_EVENT == 0
		#error "rkhcfg.h, When enabling the defer and recall event features the dynamic event support must be enabled (1) too"
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

#ifndef RKH_SMA_EN_SUBMACHINE	
	#error "rkhcfg.h, Missing RKH_SMA_EN_SUBMACHINE: Include submachine state. Must be set to one RKH_SMA_EN_PSEUDOSTATE."
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

#ifndef RKH_TRC_EN
	#error "rkhcfg.h, Missing RKH_TRC_EN: Enable (1) or Disable (0) trace mode."
#endif

#ifndef RKH_TRC_ALL
	#error "rkhcfg.h, Missing RKH_TRC_ALL: Include all trace points."
#endif

#ifndef RKH_TRC_EN_TSTAMP
	#error "rkhcfg.h, Missing RKH_TRC_EN_TSTAMP: Enable (1) or Disable (0) trace timestamp."
#endif

#ifndef RKH_TRC_SIZEOF_TSTAMP
	#error "rkhcfg.h, Missing RKH_TRC_SIZEOF_TSTAMP: Defines the size of timestamp [in bits]: 8, 16 or 32."
#endif

#ifndef RKH_TRC_SIZEOF_STREAM
	#error "rkhcfg.h, Missing RKH_TRC_SIZEOF_STREAM: Max. number of trace events in the stream."
#else
	#if RKH_TRC_SIZEOF_STREAM == 0 || RKH_TRC_SIZEOF_STREAM > 256
	#error  "rkhcfg.h, RKH_TRC_SIZEOF_STREAM must be > 0 and <= 256"
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
#define RKH_SUBMACHINE					RKH_TYPE( RKH_REGULAR, 	0x02 )	
#define RKH_REF_SUBMACHINE				RKH_TYPE( RKH_REGULAR, 	0x04 )	

#define RKH_CONDITIONAL					RKH_TYPE( RKH_PSEUDO, 	0x02 )	
#define RKH_JUNCTION					RKH_TYPE( RKH_PSEUDO, 	0x04 )	
#define RKH_SHISTORY					RKH_TYPE( RKH_PSEUDO, 	0x08 )	
#define RKH_DHISTORY					RKH_TYPE( RKH_PSEUDO, 	0x10 )	
#define RKH_ENPOINT						RKH_TYPE( RKH_PSEUDO, 	0x20 )	
#define RKH_EXPOINT						RKH_TYPE( RKH_PSEUDO, 	0x40 )	


#if RKH_SMA_EN_ID == 1
	#if RKH_SMA_EN_IEVENT == 1
		#define MKRRKH(prio,ppty,id,is,ia,ie)				\
				{(prio),(ppty),(id),(RKHROM struct rkhst_t*)(is),(ia),(ie)}
	#else
		#define MKRRKH(prio,ppty,id,is,ia,ie)				\
				{(prio),(ppty),(id),(RKHROM struct rkhst_t*)(is),(ia)}
	#endif
#else
	#if RKH_SMA_EN_IEVENT == 1
		#define MKRRKH(prio,ppty,id,is,ia,ie)				\
				{(prio),(ppty),(RKHROM struct rkhst_t*)(is),(ia),(ie)}
	#else
		#define MKRRKH(prio,ppty,id,is,ia,ie)				\
				{(prio),(ppty),(RKHROM struct rkhst_t*)(is),(ia)}
	#endif
#endif


#define MKSMA( rr, s )					\
						{ (rr), (RKHROM struct rkhst_t*)(s) }


#if RKH_SMA_EN_STATE_ID == 1
	#define MKBASE(t,id)			t,id
#else
	#define MKBASE(t,id)			t
#endif


#if RKH_SMA_EN_HCAL == 1
	#if RKH_SMA_EN_PPRO == 1
		#define MKBASIC(n,pp)		n##_trtbl,pp
		#define MKCOMP(n,d,h)		n##_trtbl,NULL,d,h
	#else
		#define MKBASIC(n,pp)		n##_trtbl
		#define MKCOMP(n,d,h)		n##_trtbl,d,h
	#endif
	#define MKST(en,ex,p)			en,ex,(RKHROM struct rkhst_t *)p
	#define MKSBM(n,sbm)			n##_trtbl,n##_exptbl,sbm
	#define MKMCH(d,i,n)			d,i,(RKHROM RKHST_T**)&rdyp_##n
	#define MKENP(e,s)				e,(RKHROM struct rkhst_t *)s
#else
	#if RKH_SMA_EN_PPRO == 1
		#define MKBASIC(n,pp)		n##_trtbl,pp
		#define MKCOMP(n,d,h)		n##_trtbl,NULL
	#else
		#define MKBASIC(n,pp)		n##_trtbl
		#define MKCOMP(n,d,h)		n##_trtbl
	#endif
	#define MKST(en,ex,p)
	#define MKSBM(n,sbm)			n##_trtbl,n##_exptbl,sbm
	#define MKMCH(d,i,n)			d,i,(RKHROM RKHST_T*)&rdyp_##n
	#define MKENP(e,s)				e,(RKHROM struct rkhst_t *)s
#endif


#ifndef RKH_ASSERT
	#define RKH_ASSERT		0
#endif


#define mksevt( evt, es )		\
							((RKHEVT_T*)(evt))->e = (RKHE_T)es;		\
							((RKHEVT_T*)(evt))->nref = 0;
#define mkievt( evt, es )		\
							RKHROM RKHEVT_T evt = { es, 0 }

#ifndef RKH_DIS_INTERRUPT
	#error  "rkhport.h, Must be defined the platform-dependent macro RKH_DIS_INTERRUPT"
#endif

#ifndef RKH_ENA_INTERRUPT
	#error  "rkhport.h, Must be defined the platform-dependent macro RKH_ENA_INTERRUPT"
#endif


#ifndef RKH_EN_DOXYGEN
	#define RKH_EN_DOXYGEN	0
#endif


#if RKH_EN_DOXYGEN == 1

	/**
	 * 	Defines the data type of the event queue for active objects. 
	 * 	The event queue can be implemented with a message queue of 
	 * 	the RTOS/OS. But it is also possible to use the native RKH 
	 * 	queue RKHRQ_T type if the underlying RTOS/OS does not provide 
	 * 	an adequate queue.
	 *
	 * 	<EM>Example for using the native queue</EM>
	 * 	\code
	 * 	#define RKH_EQ_TYPE			RKHRQ_T
	 * 	\endcode
	 */

	#define RKH_EQ_TYPE

	/**
	 * 	The data type RKH_THREAD_TYPE holds the thread handle 
	 * 	associated with the active object.
	 *
	 * 	<EM>Example for using the native scheduler</EM>
	 * 	\code
	 * 	#define RKH_THREAD_TYPE		RKHSMA_T
	 * 	\endcode
	 */

	#define RKH_THREAD_TYPE

	/**
	 * 	The RKH_OSDATA_TYPE data member is necessary when the underlying 
	 * 	OS does not provide an adequate queue facility, so the native RKH 
	 * 	queue RKHRQ_T must be used. In this case the RKH_OSDATA_TYPE data 
	 * 	member holds an operating system specific primitive to efficiently 
	 * 	block the native RKH event queue when the queue is empty.
	 */

	#define RKH_OSDATA_TYPE

	/**@{
	 * 	RKH need to disable interrupts in order to access critical sections 
	 * 	of code, and re-enable interrupts when done. This allows RKH to 
	 * 	protect critical code from being entered simultaneously. To hide the 
	 * 	implementation method chosen by the processor, compiler, etc, RKH 
	 * 	defines two macros to unconditionally disable and enable interrupts: 
	 * 	RKH_DIS_INTERRUPT() and RKH_ENA_INTERRUPT() respectively. Obviously, 
	 * 	they resides in \b rkhport.h file, which the user always need to 
	 * 	provide.
	 *
	 * 	<EM>Example for HCS08 CW6.3 from C:</EM>
	 * 	\code
	 * 	#define RKH_DIS_INTERRUPT()			DisableInterrupts
	 * 	#define RKH_ENA_INTERRUPT()			EnableInterrupts
	 * 	\endcode
	 */

	#define RKH_DIS_INTERRUPT()
	#define RKH_ENA_INTERRUPT()
	/*@}*/


	/**@{
	 * 	\brief
	 * 	RKH need to disable interrupts in order to access critical sections of 
	 * 	code, and re-enable interrupts when done. 
	 *
	 * 	This allows RKH to protect 
	 * 	critical code from being entered simultaneously from either multiple 
	 * 	SMAs or ISRs. Every processor generally provide instructions to 
	 * 	disable/enable interrupts and the C compiler must have a mechanism to 
	 * 	perform these operations directly from C. Some compilers will allows 
	 * 	to insert in-line assembly language statements in the C source code. 
	 * 	This makes it quite easy to insert processor instructions to enable and 
	 * 	disable interrupts. Other compilers will actually contain language 
	 * 	extensions to enable and disable interrupts directly from C. To hide 
	 * 	the implementation method chosen by the compiler manufacturer, RKH 
	 * 	defines two macros to disable and enable interrupts: 
	 * 	RKH_ENTER_CRITICAL() and RKH_EXIT_CRITICAL().
	 *
	 * 	The RKH_ENTER_CRITICAL() macro saves the interrupt disable status onto 
	 * 	the stack and then, disable interrupts. 
	 * 	RKH_EXIT_CRITICAL() would simply be implemented by restoring the 
	 * 	interrupt status from the stack. Using this scheme, if it's called a 
	 * 	RKH service with either interrupts enabled or disabled then, the 
	 * 	status would be preserved across the call. If calls a RKH service with 
	 * 	interrupts disabled, is potentially extending the interrupt latency of 
	 * 	application. The application can use RKH_ENTER_CRITICAL() and 
	 * 	RKH_EXIT_CRITICAL() to also protect critical sections of code. As a 
	 * 	general rule, should always call RKH services with interrupts enabled!.
	 * 	
	 * 	\note
	 * 	These macros are internal to RKH and the user application should 
	 * 	not call it.
	 *
	 * 	<EM>Example for x86, VC2008, and win32 single thread:</EM>
	 * 	\code
	 * 	//#define RKH_CPUSR_TYPE
	 * 	#define RKH_ENTER_CRITICAL( dummy )		EnterCriticalSection( &csection )
	 * 	#define RKH_EXIT_CRITICAL( dummy )		LeaveCriticalSection( &csection )
	 * 	\endcode
	 */

	#define RKH_CPUSR_TYPE
	#define RKH_SR_CRITICAL_					RKH_CPUSR_TYPE sr
	#define RKH_ENTER_CRITICAL( dummy )
	#define RKH_EXIT_CRITICAL( dummy )
	/*@}*/


	/**
	 * 	\brief
	 * 	Encapsulates the mechanism of blocking the event queue.
	 *
	 * 	\param sma		pointer to SMA.
	 */

	#define RKH_SMA_BLOCK( sma )

	/**
	 * 	\brief
	 * 	Encapsulates the mechanism of signaling the thread waiting on the 
	 * 	used event queue. Thus, the SMA is inserted in the ready list as 
	 * 	ready-to-dispatch.
	 *
 	 * 	\param rg		ready group.
	 * 	\param sma		pointer to SMA.
	 */

	#define RKH_SMA_READY( rg, sma )

	/**
	 * 	\brief
	 * 	Informs the underlying kernel that the SMA event queue is becoming 
	 * 	empty. Thus, the SMA is removed from the ready list.
	 *
 	 * 	\param rg		ready group.
	 * 	\param sma		pointer to SMA.
	 */

	#define RKH_SMA_UNREADY( rg, sma ) 	


	/**
	 * 	\brief
	 * 	Defines the data type of the fixed-size memory block for 
	 * 	dynamic event support. 
	 *
	 * 	The fixed-size memory block can be implemented with a RTOS/OS 
	 * 	service provided to that. But it's also possible to use the native 
	 * 	RKH fixed-size memory block RKHMP_T type if the underlying RTOS/OS 
	 * 	does not provide an adequate support.
	 */

	#define RKH_DYNE_TYPE

	/**
	 * 	\brief
	 * 	Encapsulates the creation of a event pool. 
	 *
	 * 	Platform-dependent macro. Typically, must be define it in the 
	 * 	specific port file (rkhport.h).
	 *
	 * 	\param mp		pointer to previously allocated memory pool structure.
	 * 	\param sstart	storage start. Pointer to memory from which memory 
	 * 					blocks are allocated.
	 * 	\param ssize:	storage size. Size of the memory pool storage in bytes.
	 * 	\param esize	event size. This number determines the size of each 
	 * 					memory block in the pool.
	 */

	#define RKH_DYNE_INIT( mp, sstart, ssize, esize )

	/**
	 * 	\brief
	 * 	Encapsulates how RKH should obtain the block size of pool.
	 *
	 * 	Platform-dependent macro. Typically, must be define it in the 
	 * 	specific port file (rkhport.h).
	 *
	 * 	\param mp		pointer to previously allocated memory pool structure.
	 */

	#define RKH_DYNE_GET_ESIZE( mp )

	/**
	 * 	\brief
	 *	Encapsulates how RKH should obtain an event \c e from the 
	 *	event pool \c mp.
	 * 
	 * 	Platform-dependent macro. Typically, must be define it in the 
	 * 	specific port file (rkhport.h).
	 *
	 * 	\param mp		pointer to previously allocated memory pool structure.
	 * 	\param e		pointer to a new event or NULL if the pool 
	 * 					runs out of blocks.
	 */

	#define RKH_DYNE_GET( mp, e )

	/**
	 * 	\brief
	 *	Encapsulates how RKH should return an event \c e to the event 
	 *	pool \c mp.
	 *
	 * 	Platform-dependent macro. Typically, must be define it in the 
	 * 	specific port file (rkhport.h).
	 *
	 * 	\param mp		pointer to previously allocated memory pool structure.
	 * 	\param e		pointer to the returned event.
	 */

	#define RKH_DYNE_PUT( mp, e )
#endif


#ifdef RKH_CPUSR_TYPE
	#if RKH_EN_DOXYGEN == 0
		#define RKH_SR_CRITICAL_			RKH_CPUSR_TYPE sr
		#define RKH_ENTER_CRITICAL_()		RKH_ENTER_CRITICAL( sr )
		#define RKH_EXIT_CRITICAL_()		RKH_EXIT_CRITICAL( sr )
	#endif
#else
	#define RKH_SR_CRITICAL_
	#define RKH_ENTER_CRITICAL_()		RKH_ENTER_CRITICAL( dummy )
	#define RKH_EXIT_CRITICAL_()		RKH_EXIT_CRITICAL( dummy )
#endif


#ifndef RKH_HK_EN_DISPATCH
	#error "rkhcfg.h, Missing RKH_HK_EN_DISPATCH: Include (1) or remove (0) the dispatch hook function"
#else
	#if RKH_HK_EN_DISPATCH == 1
		#define RKH_HK_DISPATCH( sma, e )		\
							rkh_hk_dispatch( sma, (RKHEVT_T*)e )
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
		#define RKH_HK_SIGNAL( e )		rkh_hk_signal( (RKHEVT_T*)e )
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


#define CIA( s )	((RKHINIT_T)((s)->romrkh->iaction))

/**
 * 	\brief
 * 	Initialization action.
 *
 * 	Frequently, the state transition originating at the black ball is called 
 * 	the initial transition. Such transition designates the first active state 
 * 	after the state machine object is created. An initial transition can have 
 * 	associated actions, which in the UML notation are enlisted after the 
 * 	forward slash (/). In RKH framework, the application code must trigger 
 * 	the initial transition explicitly by invoking rkh_sma_activate() function.
 */

#if RKH_SMA_EN_INIT_ARG_SMA == 1 && RKH_SMA_EN_IEVENT == 1
	typedef void ( *RKHINIT_T )( const void *sma, 
										const struct rkhevt_t *e );
	#define RKH_EXEC_INIT( h )										\
	{																\
		if( CIA( h ) != NULL )										\
			(*CIA( h ))( (h), CIA(h)->romrkh->ievent );				\
	}
#elif RKH_SMA_EN_INIT_ARG_SMA == 1 && RKH_SMA_EN_IEVENT == 0
	typedef void ( *RKHINIT_T )( const void *sma );
	#define RKH_EXEC_INIT( h )										\
	{																\
		if( CIA( h ) != NULL )										\
			(*CIA( h ))( (h) );										\
	}
#elif RKH_SMA_EN_INIT_ARG_SMA == 0 && RKH_SMA_EN_IEVENT == 1
	typedef void ( *RKHINIT_T )( const struct rkhevt_t *e );
	#define RKH_EXEC_INIT( h )										\
	{																\
		if( CIA( h ) != NULL )										\
			(*CIA( h ))( CIA(h)->romrkh->ievent );					\
	}
#else
	typedef void ( *RKHINIT_T )( void );
	#define RKH_EXEC_INIT( h )										\
	{																\
		if( CIA( h ) != NULL )										\
			(*CIA( h ))();											\
	}
#endif


/**
 * 	\brief 
 * 	Defines the data structure into which the collected performance 
 * 	information for state machine is stored.
 * 	
 * 	This member is optional, thus it could be declared as NULL or eliminated 
 * 	in compile-time with RKH_EN_SMA_GET_INFO = 0.
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
 *	RKHSMA_T structure definition for more information. Also, \link RKHEVT_T 
 *	single inheritance in C \endlink, and \link RKH_CREATE_BASIC_STATE 
 *	another example \endlink.
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

	rkhui8_t ppty;

	/**	
 	 * 	\brief
	 * 	ID of state machine application. 
	 * 	
	 * 	ID of state machine application. This number allows to uniquely 
	 * 	identify a state machine. When a particular application requires 
	 * 	runtime tracing (native tracing features), the option RKH_SMA_EN_ID 
	 * 	must be set to one. 
	 */

#if RKH_SMA_EN_ID == 1
	rkhui8_t id;
#endif

	/** 
 	 * 	\brief
	 * 	Points to initial state. 
	 *
	 * 	This state could be defined either composite or basic 
	 * 	(not pseudo-state).
	 */

	RKHROM struct rkhst_t *istate;

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
	 *	declared as NULL or eliminated in compile-time with 
	 *	RKH_SMA_EN_IEVENT = 0.
	 */

#if RKH_SMA_EN_IEVENT == 1
	const RKHEVT_T *ievent;
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
 * 	RKHSMA_T is not intended to be instantiated directly, but rather
 * 	serves as the base structure for derivation of state machines in the
 * 	application code.
 * 	The following example illustrates how to derive an state machine from
 * 	RKH_T. Please note that the RKHSMA_T member sm is defined as the
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
 *	RKH_SMA_CREATE( MYSM_T, 0, my, HCAL, &S1, my_iaction, &my_ievent );
 *	\endcode
 *
 *	\sa
 *	RKHSMA_T structure definition for more information. Also, \link RKHEVT_T 
 *	single inheritance in C \endlink, and \link RKH_CREATE_BASIC_STATE 
 *	another example \endlink.
 */

typedef struct rkhsma_t
{
	/**
 	 * 	\brief
	 * 	Points to state machine object.
	 */
	
	RKHROM ROMRKH_T *romrkh;

	/** 
 	 * 	\brief
	 * 	Points to current state (basic state).
	 */

	RKHROM struct rkhst_t *state;

	/**
	 * 	\brief
	 * 	OS-dependent thread of control of the SMA.
	 *
     *	This data might be used in various ways, depending on the RKH port.
     * 	In some ports it's used to store the thread handler.
	 *
	 * 	\note
	 * 	This member is optional, thus it could be declared as NULL or 
	 * 	eliminated in compile-time with RKH_EN_SMA_THREAD = 0.
	 */

#if RKH_EN_SMA_THREAD == 1
	RKH_THREAD_TYPE thread;
#endif

	/**
	 * 	\brief
	 *	OS-dependent thread data.
	 *
	 * 	This data might be used in various ways, depending on the RKH port.
	 * 	In some ports it's used to block the calling thread when the native 
	 * 	RKH queue is empty. In other RKH ports the OS-dependent	data object 
	 * 	might be used differently.
	 * 	
	 * 	\note
	 * 	This member is optional, thus it could be eliminated in compile-time 
	 * 	with RKH_EN_SMA_THREAD_DATA = 0.
	 */

#if RKH_EN_SMA_THREAD == 1 && RKH_EN_SMA_THREAD_DATA == 1
	RKH_OSDATA_TYPE osdata;
#endif

	/**
	 * 	\brief
	 * 	Event queue of the SMA.
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
	 * 	RKH_SMA_EN_GET_INFO = 0.
	 */

#if RKH_SMA_EN_GET_INFO == 1
	RKH_SMAI_T sinfo;
#endif	

} RKHSMA_T;


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
 * 	The RKH implementation preserves the transition sequence imposed by 
 * 	Harel's Statechart and UML. Specifically, the implemented transition 
 * 	sequence is as follows:
 *
 * 	- Execute exit actions of the source state.
 * 	- Execute the transition actions.
 * 	- Execute entry actions of the target state.
 * 
 * 	\note
 * 	This callback is referenced from RKH_CREATE_COMP_STATE() and 
 * 	RKH_CREATE_BASIC_STATE() macros.
 * 	\b RKH_SMA_EN_ENT_ARG_SMA macro.
 */


#if RKH_SMA_EN_ENT_ARG_SMA == 1
	typedef void ( *RKHENT_T )( const struct rkhsma_t *sma );
	#define RKH_EXEC_ENTRY( s, h )				\
	{											\
		if( (s)->enter != NULL )				\
			(*(s)->enter)( h ); 				\
	}
#else
	typedef void ( *RKHENT_T )( void );
	#define RKH_EXEC_ENTRY( s, h )				\
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
 * 	The RKH implementation preserves the transition sequence imposed by 
 * 	Harel's Statechart and UML. Specifically, the implemented transition 
 * 	sequence is as follows:
 *
 * 	- Execute exit actions of the source state.
 * 	- Execute the transition actions.
 * 	- Execute entry actions of the target state.
 *
 * 	\note
 * 	This callback is referenced from RKH_CREATE_COMP_STATE() and 
 * 	RKH_CREATE_BASIC_STATE() macros.
 */

#if RKH_SMA_EN_EXT_ARG_SMA == 1
	typedef void ( *RKHEXT_T )( const struct rkhsma_t *sma );
	#define RKH_EXEC_EXIT( s, h )				\
	{											\
		if( (s)->exit != NULL )					\
			(*(s)->exit)( h ); 					\
	}
#else
	typedef void ( *RKHEXT_T )( void );
	#define RKH_EXEC_EXIT( s, h )				\
	{											\
		if( (s)->exit != NULL )					\
			(*(s)->exit)(); 					\
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


#define CTA( ta )	((RKHACT_T)(ta))

/**
 * 	\brief
 * 	Transition action.
 *
 * 	Transition actions are small atomic behaviors executed at specified points 
 * 	in a state machine. This actions are assumed to take an insignificant 
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
 * 	The RKH implementation preserves the transition sequence imposed by 
 * 	Harel's Statechart and UML. Specifically, the implemented transition 
 * 	sequence is as follows:
 *
 * 	- Execute exit actions of the source state.
 * 	- Execute the transition actions.
 * 	- Execute entry actions of the target state.
 *
 * 	\note
 * 	This callback is referenced from RKH_TRREG() and RKH_TRINT()macro. 
 */

#if RKH_SMA_EN_ACT_ARG_EVT == 1 && RKH_SMA_EN_ACT_ARG_SMA == 1
	typedef void (*RKHACT_T)( const struct rkhsma_t *sma, RKHEVT_T *pe );
	#define RKH_CALL_ACTION( a,h,e )	(*CTA( a ))( (h), (e) )
#elif RKH_SMA_EN_ACT_ARG_EVT == 1 && RKH_SMA_EN_ACT_ARG_SMA == 0
	typedef void (*RKHACT_T)( RKHEVT_T *pe );
	#define RKH_CALL_ACTION( a,h,e )	(*CTA( a ))( (e) )
#elif RKH_SMA_EN_ACT_ARG_EVT == 0 && RKH_SMA_EN_ACT_ARG_SMA == 1
	typedef void (*RKHACT_T)( const struct rkhsma_t *sma );
	#define RKH_CALL_ACTION( a,h,e )	(*CTA( a ))( (h) )
#else
	typedef void (*RKHACT_T)( void );
	#define RKH_CALL_ACTION( a,h,e )	(*CTA( a ))()
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
 * 	\brief
 * 	Describes the exit point connection. 
 *
 * 	...
 */

typedef struct rkhexpcn_t
{
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
} RKHEXPCN_T;


/**
 * 	\brief
 * 	Describes the entry point connection. 
 *
 * 	...
 */

typedef struct rkhenpcn_t
{
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
} RKHENPCN_T;


/**
 *	\brief
 * 	Describes the common properties of regular states (basic, composite, 
 * 	and submachine).
 */

typedef struct rkhst_t
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

	RKHROM struct rkhst_t *parent;
#endif

} RKHST_T;


/**
 *	\brief
 * 	Describes a basic state.
 */

typedef struct rkhsbsc_t
{
	RKHST_T st;

	/**	
 	 * 	\brief
	 *	Points to state transition table.
	 */

	RKHROM struct rkhtr_t *trtbl;

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
	 *	static
	 *	RKHE_T
	 *	preprocessor( RKHEVT_T *pe )
	 *	{
	 *		...
	 *	}
	 *  
	 *	typedef struct
	 *	{
	 *		RKHPPRO_T prepro; 	// extend the RKHPPRO_T class
	 *		unsigned min:4;
	 *		unsigned max:4;
	 *		char *buff;
	 *	} SDATA_T;
	 *
	 *	static const SDATA_T option = { preprocessor, 4, 8, token1 };
	 *
	 *	RKH_CREATE_BASIC_STATE( S111, 0, set_x_1, 
	 *					NULL, &S11, preprocessor ); 
	 *	RKH_CREATE_BASIC_STATE( S22, 0, set_x_4, 
	 *					NULL, &S2, (RKHPPRO_T*)&option ); 
	 * \endcode
	 */

#if RKH_SMA_EN_PPRO == 1
	RKHPPRO_T prepro;
#endif

} RKHSBSC_T;


/**
 *	\brief
 * 	Describes a composite state.
 */

typedef struct rkhscmp_t
{
	RKHST_T st;

	/**	
 	 * 	\brief
	 *	Points to state transition table.
	 */

	RKHROM struct rkhtr_t *trtbl;

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
	 *	static
	 *	RKHE_T
	 *	preprocessor( RKHEVT_T *pe )
	 *	{
	 *		...
	 *	}
	 *  
	 *	typedef struct
	 *	{
	 *		RKHPPRO_T prepro; 	// extend the RKHPPRO_T class
	 *		unsigned min:4;
	 *		unsigned max:4;
	 *		char *buff;
	 *	} SDATA_T;
	 *
	 *	static const SDATA_T option = { preprocessor, 4, 8, token1 };
	 *
	 *	RKH_CREATE_BASIC_STATE( S111, 0, set_x_1, 
	 *					NULL, &S11, preprocessor ); 
	 *	RKH_CREATE_BASIC_STATE( S22, 0, set_x_4, 
	 *					NULL, &S2, (RKHPPRO_T*)&option ); 
	 * \endcode
	 */

#if RKH_SMA_EN_PPRO == 1
	RKHPPRO_T prepro;
#endif

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

} RKHSCMP_T;


/**
 *	\brief
 * 	Describes a submachine state.
 *
 * 	A submachine state is a kind of a state that actually refers to 
 * 	another defined state machine.
 * 	A submachine state is logically equivalent to the insertion of the 
 * 	referenced state machine as a composite state in the place of 
 * 	the submachine state. Consequently, every entrance to a submachine 
 * 	state is equivalent to the corresponding entrance to the inserted 
 * 	(referenced) composite state. In particular, it can be entered 
 * 	thruough its initial pseudostate (as any other composite state), or 
 * 	through one of its entry points. 
 *
 * 	Similary, every exit from a submachine state is equivalent to the 
 * 	corresponding exit from the inserted composite state. It can be exited 
 * 	through one of its exit points. When it is exited through its exit point 
 * 	the effect of the transition targeting the exit point is executed first, 
 * 	followed by the exit behavior of the composite state. 
 *
 * 	The entry, exit, and behavior actions and internal transitions are 
 * 	defined as part of the state. Submachine state is a decomposition 
 * 	mechanism that allows factoring of common behaviors and their reuse.
 *
 * 	The purpose od defining submachine states is to decompose and localize 
 * 	repetitive parts because the same state machine can be referenced from 
 * 	more than one submachine state.
 *
 *	The diagram in following figure shows a fragment from a state machine 
 *	diagram in which a submachine state (the \c SB) is referenced.
 *	
 *	\anchor fig_sbm1
 *	\image html sbm1.png "Submachine state"
 *	
 *	In the above example, the transition triggered by event \c TWO will 
 *	terminate on entry point \c ENS12 of the \c SB state machine. 
 *	The \c ONE transition implies taking of the default transition of the 
 *	\c SB and executes the \c act5() action. The transition emanating from 
 *	the \c EX1S12 exit point of the submachine will execute the \c act1() 
 *	behavior in addition to what is executed within the \c SB state machine. 
 *	Idem transition emanating from the \c EX2S12.
 *	This transition must have been triggered within the \c SB state machine. 
 *	Finally, the transition emanating from the edge of the submachine state 
 *	is triggered by event \c THREE.
 *	
 *	The following figure is an example of a state machine \c SB defined with 
 *	two exit points, \c EXPNT1 and \c EXPNT2, and one entry point \c ENPNT.
 *	
 *	\anchor fig_sbm2
 *	\image html sbm2.png "State machine with two exit points and one entry point"
 *	
 *	In the following figure the state machine shown above is referenced twice in 
 *	a submachine state \c S12 and \c S2.
 *	
 *	\anchor fig_sbm3
 *	\image html sbm3.png "Submachine state with usage of exit and entry points"
 */

typedef struct rkhssbm_t
{
	RKHST_T st;

	/**	
 	 * 	\brief
	 *	Points to state transition table.
	 */

	RKHROM struct rkhtr_t *trtbl;

	/**	
 	 * 	\brief
	 *	Points to state transition table.
	 */

	RKHROM struct rkhexpcn_t *exptbl;

	/**	
 	 * 	\brief
	 *	Points to submachine object.
	 */

	RKHROM struct rkhrsm_t *sbm;

} RKHSSBM_T;


/**
 *	\brief
 * 	Describes a (referenced) submachine state machine.
 */

typedef struct rkhrsm_t
{
	/**	
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
 	 * 	\brief
	 *	Points to state's default child.
	 */

	RKHROM void *defchild;

	/** 
 	 * 	\brief
	 * 	Points to initializing action (optional). 
	 *
	 * 	The function prototype is defined as RKHACT_T. This argument is 
	 * 	optional, thus it could be declared as NULL.
	 */

	RKHACT_T iaction;

	/**	
 	 * 	\brief
	 *	Points to RAM memory location which stores
	 *	the dynamic parent.
	 */

	RKHROM struct rkhst_t **dyp;
} RKHRSM_T;


/**
 * 	\brief 
 * 	Describes the entry point pseudostate.
 *
 * 	An entry pseudostate is used to join an external transition terminating 
 * 	on that entry point to an internal transition emanating from that entry 
 * 	point.
 * 	The main purpose of such entry and exit points is to execute the state 
 * 	entry and exit actions respectively in between the actions that are 
 * 	associated with the joined transitions.
 */

typedef struct rkhsenp_t
{
	/**
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
 	 * 	\brief
	 *	Points to entry point connection.
	 */

	RKHROM RKHENPCN_T *enpcn;

	/**	
 	 * 	\brief
	 *	Points to state's parent (submachine state).
	 */

	RKHROM struct rkhst_t *parent;

} RKHSENP_T;


/**
 * 	\brief 
 * 	Describes the exit point pseudostate.
 *
 * 	An exit pseudostate is used to join an internal transition terminating on 
 * 	that exit point to an external transition emanating from that exit point. 
 * 	The main purpose of such entry and exit points is to execute the state 
 * 	entry and exit actions respectively in between the actions that are 
 * 	associated with the joined transitions.
 */

typedef struct rkhsexp_t
{
	/**
 	 * 	\brief
	 *	Maintains the basic information of state.
	 */

	struct rkhbase_t base;

	/**	
 	 * 	\brief
	 *	Index of exit point table.
	 */

	rkhui8_t ix;

	/**	
 	 * 	\brief
	 *	Points to state's parent (referenced submachine).
	 */

	RKHROM RKHRSM_T *parent;
} RKHSEXP_T;


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

	RKHROM RKHST_T *parent;

	/**	
 	 * 	\brief
	 *	Points to RAM memory location which stores
	 *	the state's history.
	 */

	RKHROM RKHST_T **target;
} RKHSHIST_T;


#endif
