/*
 *	file: rkhtrace.h
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
 * 	\file rkhtrace.h
 * 	\brief
 *	Platform-independent interface for RKH trace facility.
 *
 * 	When a program needs to be traced, it has to generate some information 
 * 	each time it reaches a "significant step" (certain instruction in the 
 * 	program's source code). In the standard terminology, this step is called 
 * 	a trace point, and the tracing information which is generated at that 
 * 	point is called a trace event. A program containing one or more of this 
 * 	trace points is named instrumented application.
 *
 * 	There is one class of trace events: RKH trace events, which are generated 
 * 	by the RKH source code.
 * 	
 * 	The definition of events and the mapping between these and their 
 * 	corresponding names is hard-coded in the RKH implementation. Therefore, 
 * 	these events are common for all the state machine applications and never 
 * 	change (they are always traced). 
 * 	The trace events are associated with a integer value and are explicity 
 * 	listed and defined (enumerated) as shown below in this file.
 * 		
 *	The standard defines that the trace system has to store some information 
 *	for each trace event (also named arguments) being generated, including, 
 *	at least, the following:
 *
 * 	- the trace event identifier (RKHTR_EVENTS enumerated list),
 * 	- instrumented application (state machine),
 * 	- a timestamp (optional),
 * 	- any extra data that the system wants to associate with the event 
 * 	(optional).
 *
 * 	When the RKH reachs a trace point, all the information related to 
 * 	it has to be stored somewhere before it can be retrieved, in order to 
 * 	be analyzed. This place is named trace stream.
 */


#ifndef __RKHTRACE_H__
#define __RKHTRACE_H__


#include "rkhtype.h"
#include <string.h>


/**
 * 	\brief
 * 	Return codes from rkh_trace_getnext() function.
 */

typedef enum
{
	RKH_TROK, RKH_TREMPTY
} RKHTR_RC;


/**
 * 	\brief
 * 	Enable or disable the trace facility for a instrumented state machine.
 * 	It's used as argument of rkh_trace_control() function.
 */

typedef enum
{
	RKH_TRSTOP, RKH_TRSTART
} RKHTR_CTRL;


/**
 * 	\brief
 * 	Defines printable or not the trace events for a instrumented state machine.
 *
 * 	\note
 * 	It's used as argument of rkh_trace_config() function. This number isn't 
 * 	internally used by RKH trace module.
 */

typedef enum
{
	RKH_TR_DIS_PRINT, RKH_TR_EN_PRINT
} RKHTR_CFGPRT;


/**
 * 	\brief
 * 	Defines logged or not the trace events for a instrumented state machine. 
 *
 * 	\note
 * 	It's used as argument of rkh_trace_config() function. This number isn't 
 * 	internally used by RKH trace module.
 */

typedef enum
{
	RKH_TR_DIS_LOG, RKH_TR_EN_LOG
} RKHTR_CFGLOG;


/**
 * 	\brief
 * 	List of event traced.
 *
 *	The list below defines the available trace events. This traces are 
 *	placed within RKH source code, at key points of interest, called 
 *	trace points.
 */

typedef enum
{
	/** 
	 * 	If it's enabled (1) records the triggering event.
	 */

	RKHTR_EVENT,
	
	/**
	 * 	If it's enabled (1) records the source state of transition.
	 */

	RKHTR_TRN_SRC,

	/**
	 * 	If it's enabled (1) records the target state of transition.
	 */

	RKHTR_TRN_TGT,

	/**
	 * 	If it's enabled (1) records the next state of transition.
	 */

	RKHTR_NXT_STATE,

	/**
	 * 	If it's enabled (1) records the internal transition.
	 */

	RKHTR_INT_TRAN,

	/**
	 * 	If it's enabled (1) records the entered state.
	 */

	RKHTR_ENTRY,

	/**
	 * 	If it's enabled (1) records the exited state.
	 */

	RKHTR_EXIT,

	/**
	 * 	If it's enabled (1) records the initialization process 
	 * 	of state machine.
	 */

	RKHTR_INIT_HSM,

	/**
	 * 	If it's enabled (1) records the target state of 
	 * 	transition segment.
	 */

	RKHTR_SGT_TGT,

	/**
	 * 	If it's enabled (1) records the code returned by 
	 * 	rkh_engine() function.
	 */

	RKHTR_RTN_CODE,

	/**
	 * 	If it's enabled (1) records the number of entered 
	 * 	and exited states.
	 */

	RKHTR_NUM_ENEX,

	/**
	 * 	If it's enabled (1) records the number of transition 
	 * 	actions and transition segments.
	 */

	RKHTR_NUM_ACTSGT,

	RKHTR_NUM_EVENTS
} RKHTR_EVENTS;


/** 
 * 	\brief
 * 	Defines the size of trace timestamp. 
 *
 * 	The valid values [in bits] are 8, 16 or 32. Default is 8. This type is 
 * 	configurable via the RKH_TR_SIZEOF_TIMESTAMP preprocessor option.
 */

#if RKH_TR_SIZEOF_TIMESTAMP == 8
	typedef rkhui8_t RKHTS_T;
#elif RKH_TR_SIZEOF_TIMESTAMP == 16
	typedef rkhui16_t RKHTS_T;
#elif RKH_TR_SIZEOF_TIMESTAMP == 32
	typedef rkhui32_t RKHTS_T;
#else
	typedef rkhui8_t RKHTS_T;
#endif


#if RKH_TR_EN == 1
	#if RKH_TR_TRACE_ALL == 1 || RKH_TR_EN_EVENT == 1
		#define RKH_REC_EVENT( e, s, n )				\
					MKTREVT( (e),RKHTR_EVENT,(s),rkh_trace_getts(),(n),NULL )
	#else
		#define RKH_REC_EVENT( e, s, n )
	#endif

	#if RKH_TR_ALL == 1 || RKH_TR_EN_TRN_SRC == 1
		#define RKH_REC_SRC_STATE( e, s, n, str )		\
					MKTREVT( (e),RKHTR_TRN_SRC,(s),rkh_trace_getts(),(n),(str) )
	#else
		#define RKH_REC_SRC_STATE( e, s, n, str )
	#endif

	#if RKH_TR_ALL == 1 || RKH_TR_EN_TRN_TGT == 1
		#define RKH_REC_TGT_STATE( e, s, n, str )		\
					MKTREVT( (e),RKHTR_TRN_TGT,(s),rkh_trace_getts(),(n),(str) )
	#else
		#define RKH_REC_TGT_STATE( e, s, n, str )
	#endif

	#if RKH_TR_ALL == 1 || RKH_TR_EN_NXT_STATE == 1
		#define RKH_REC_NXT_STATE( e, s, n, str )		\
					MKTREVT( (e),RKHTR_NXT_STATE,(s),rkh_trace_getts(),(n),(str) )
	#else
		#define RKH_REC_NXT_STATE( e, s, n, str )
	#endif

	#if RKH_TR_ALL == 1 || RKH_TR_EN_INT_TRAN == 1
		#define RKH_REC_INT_TRAN( e, s )				\
					MKTREVT( (e),RKHTR_INT_TRAN,(s),rkh_trace_getts(),0,NULL )
	#else
		#define RKH_REC_INT_TRAN( e, s )
	#endif

	#if RKH_TR_ALL == 1 || RKH_TR_EN_ENTRY == 1
		#define RKH_REC_ENTRY( e, s, n, str )			\
					MKTREVT( (e),RKHTR_ENTRY,(s),rkh_trace_getts(),(n),(str) )
	#else
		#define RKH_REC_ENTRY( e, s, n, str )
	#endif

	#if RKH_TR_ALL == 1 || RKH_TR_EN_EXIT == 1
		#define RKH_REC_EXIT( e, s, n, str )			\
					MKTREVT( (e),RKHTR_EXIT,(s),rkh_trace_getts(),(n),(str) )
	#else
		#define RKH_REC_EXIT( e, s, n, str )
	#endif

	#if RKH_TR_ALL == 1 || RKH_TR_EN_INIT_HSM == 1
		#define RKH_REC_INIT_HSM( e, s, n, str )		\
				MKTREVT( (e),RKHTR_INIT_HSM,(s),rkh_trace_getts(),(n),(str) )
	#else
		#define RKH_REC_INIT_HSM( e, s, n, str )
	#endif

	#if RKH_TR_ALL == 1 || RKH_TR_EN_SGT == 1
		#define RKH_REC_SGT( e, s, n, str )				\
				MKTREVT( (e),RKHTR_SGT_TGT,(s),rkh_trace_getts(),(n),(str) )
	#else
		#define RKH_REC_SGT( e, s, n, str )
	#endif

	#if RKH_TR_ALL == 1 || RKH_TR_EN_RTN_CODE == 1
		#define RKH_REC_RTN_CODE( e, s, n )				\
				MKTREVT( (e),RKHTR_RTN_CODE,(s),rkh_trace_getts(),(n),NULL )
	#else
		#define RKH_REC_RTN_CODE( e, s, n )
	#endif

	#if RKH_TR_ALL == 1 || RKH_TR_EN_NUM_ENEX == 1
		#define RKH_REC_NUM_ENEX( e, s, n )				\
				MKTREVT( (e),RKHTR_NUM_ENEX,(s),rkh_trace_getts(),(n),NULL )
	#else
		#define RKH_REC_NUM_ENEX( e, s, n )
	#endif

	#if RKH_TR_ALL == 1 || RKH_TR_EN_NUM_ACTSGT == 1
		#define RKH_REC_NUM_ACTSGT( e, s, n )			\
				MKTREVT( (e),RKHTR_NUM_ACTSGT,(s),rkh_trace_getts(),(n),NULL )
	#else
		#define RKH_REC_NUM_ACTSGT( e, s, n )
	#endif

#else
	#define RKH_REC_EVENT( e, s, n )
	#define RKH_REC_SRC_STATE( e, s, n, str )
	#define RKH_REC_TGT_STATE( e, s, n, str )
	#define RKH_REC_NXT_STATE( e, s, n, str )
	#define RKH_REC_INT_TRAN( e, s )
	#define RKH_REC_ENTRY( e, s, n, str )
	#define RKH_REC_EXIT( e, s, n, str )
	#define RKH_REC_INIT_HSM( e, s, n, str )
	#define RKH_REC_SGT( e, s, n, str )
	#define RKH_REC_RTN_CODE( e, s, n )
	#define RKH_REC_NUM_ENEX( e, s, n )
	#define RKH_REC_NUM_ACTSGT( e, s, n )
#endif


#if RKH_TRACE == 1
#if RKH_TR_EN_TIMESTAMP == 1
	#if RKH_TR_EN_STRING == 1
		#define MKTREVT( e, i, s, t, n, str )			\
							(e).id = i;					\
							(e).smix = s;				\
							(e).ts = t;					\
							(e).num = n;				\
							if( str != NULL )			\
								strcpy( (e).sb, str );	\
							rkh_trace_evt( &(e) )
	#else
		#define MKTREVT( e, i, s, t, n, str )			\
							(e).id = i;					\
							(e).smix = s;				\
							(e).ts = t;					\
							(e).num = n;				\
							rkh_trace_evt( &(e) )
	#endif
#else
	#if RKH_TR_EN_STRING == 1
		#define MKTREVT( e, i, s, t, n, str )			\
							(e).id = i;					\
							(e).smix = s;				\
							(e).num = n;				\
							if( str != NULL )			\
								strcpy( (e).sb, str );	\
							rkh_trace_evt( &(e) )
	#else
		#define MKTREVT( e, i, s, t, n, str )			\
							(e).id = i;					\
							(e).smix = s;				\
							(e).num = n;				\
							rkh_trace_evt( &(e) )
	#endif
#endif
#else
	#define MKTREVT( e, i, s, t, n, str )
#endif


/**
 * 	\brief
 * 	Specifies the behavior of the instrumented state machine. 
 *
 * 	Each of instrumented state machine applications has its own tracing 
 * 	facility configuration. The members of this structure can be set through 
 * 	rkh_trace_control() function.
 */

typedef struct
{
	/**
	 * 	\brief
	 * 	When enabling tracing for a state machine, trace module records 
	 * 	the trace events. 
	 */

	unsigned enable	:1;
	
	/**
	 * 	This number isn't internally used by RKH trace module.
	 */

	unsigned print	:1;

	/**
	 * 	This number isn't internally used by RKH trace module.
	 */

	unsigned log	:1;

	/**
	 * 	Reserved for future use.
	 */

	unsigned res	:5;
} RKHTRCFG_T;


/**
 * 	\brief
 * 	Describes a trace event. 
 */

typedef struct
{
	/**
	 *	Trace event identifier. 
	 */

	rkhui8_t id;

	/**
	 *	State machine application ID. 
	 *	It's used as instrumented state machine identifier.
	 */

	rkhui8_t smix;

	/**
	 *	Timestamp. 
	 * 	This member is optional, thus it could be eliminated in compile-time 
	 * 	with RKH_TR_EN_TIMESTAMP = 0.
	 */

	#if RKH_TR_EN_TIMESTAMP == 1
	RKHTS_T ts;
	#endif

	/**
	 *	Trace event argument. 
	 */

	rkhui8_t num;

	/**
	 *	Trace event argument. 
	 * 	This member is optional, thus it could be eliminated in compile-time 
	 * 	with RKH_TR_EN_STRING = 0.
	 */

	#if RKH_TR_EN_STRING == 1
	char sb[ RKH_TR_MAX_STRING_SIZE + 1 ];
	#endif
} RKHTREVT_T;


/**
 * 	\brief
 * 	Inits the trace facility module.
 */

void rkh_trace_init( void );


/**
 * 	\brief
 * 	Each of instrumented state machine applications has its own tracing
 * 	facility configuration.
 *
 * 	\param trix		instrumented state machine ID. This number 
 * 					must be unique. Each of instrumented state machine 
 * 					applications has its own tracing facility configuration.
 * 	\param log		defines logged or not the trace events for a 
 * 					instrumented state machine. Use RKH_TR_EN_LOG or
 * 					RKH_TR_DIS_LOG for that. This number isn't internally 
 * 					used by RKH trace module.
 * 	\param print	defines printable or not the trace events for a 
 * 					instrumented state machine. Use RKH_TR_EN_PRINT or
 * 					RKH_TR_DIS_PRINT for that. This number isn't internally 
 * 					used by RKH trace module.
 */

void rkh_trace_config( HUInt trix, HUInt log, HUInt print );


/**
 * 	\brief
 * 	Starts or stops the tracing session of an instrumented 
 * 	state machine.
 *
 * 	\param trix		instrumented state machine ID. This number 
 * 					must be unique. Each of instrumented state machine 
 * 					applications has its own tracing facility configuration.
 * 	\param opt		control option. Use RKH_TRSTART to start recording
 * 					events.	
 */

void rkh_trace_control( HUInt trix, HUInt opt );


/**
 * 	\brief
 *	Retrieves the tracing configuration that specifies the behavior of 
 *	the session.
 *
 * 	\param trix		instrumented state machine ID. This number 
 * 					must be unique. Each of instrumented state machine 
 * 					applications has its own tracing facility configuration.
 *
 * 	\returns
 * 	Pointer to tracing configuration structure.
 */

RKHTRCFG_T *rkh_trace_getcfg( HUInt trix );


/**
 * 	\brief
 *	Post a trace event in the stream. The event is stored by copy, not by 
 *	reference.
 *
 *	When the RKH trace an event, all the information related to it has to 
 * 	be stored within the trace stream. This function is indirectly called 
 * 	by means of MKTREVT() macro.
 *
 * 	\param ptre		pointer to the trace event that is to be placed in
 * 					the stream.
 */

void rkh_trace_evt( RKHTREVT_T *ptre );


/**
 * 	\brief
 *	Get a trace event from the stream.
 *
 * 	\param ptre		pointer to the buffer into which the event retrieved
 * 					will be copied.
 *
 * 	\returns
 *
 * 	RKH_TROK if the event was successfully removed from the stream, 
 *	otherwise error code.
 */

HUInt rkh_trace_getnext( RKHTREVT_T *ptre );


/**
 * 	\brief
 *	Retrieves the number of trace events stored in the stream.
 *
 * 	\returns
 * 	Number of trace events stored in the stream.
 */

rkhui16_t rkh_trace_getqty( void );


#endif
