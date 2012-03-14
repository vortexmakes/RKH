/*
 *	file: rkhtrc.h
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
 * 	\file rkhtrc.h
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


#ifndef __RKHTRC_H__
#define __RKHTRC_H__


#include "rkhtype.h"
#include "rkhcfg.h"
#include <string.h>


/**
 * 	\brief
 * 	Return codes from rkh_trc_getnext() function.
 */

typedef enum
{
	RKH_TRC_OK, RKH_TRC_EMPTY
} RKHTR_RC;


/**
 * 	\brief
 * 	Enable or disable the trace facility for a instrumented state machine.
 * 	It's used as argument of rkh_trc_control() function.
 */

typedef enum
{
	RKH_TRC_STOP, RKH_TRC_START
} RKHTR_CTRL;


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
	 * 	rkh_dispatch() function.
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

	RKHTR_NUM_SMA_EVENTS
	 
} RKHTR_EVENTS;


/** 
 * 	\brief
 * 	Defines the size of trace timestamp. 
 *
 * 	The valid values [in bits] are 8, 16 or 32. Default is 8. This type is 
 * 	configurable via the RKH_TRC_SIZEOF_TSTAMP preprocessor option.
 */

#if RKH_TRC_SIZEOF_TSTAMP == 8
	typedef rkhui8_t RKHTS_T;
	#define RKH_TRCE_TSTAMP()					\
				RKH_TRCE_UI8( rkh_trc_getts() )
#elif RKH_TRC_SIZEOF_TSTAMP == 16
	typedef rkhui16_t RKHTS_T;
	#define RKH_TRCE_TSTAMP()					\
				RKH_TRCE_UI8( rkh_trc_getts() )
#elif RKH_TRC_SIZEOF_TSTAMP == 32
	typedef rkhui32_t RKHTS_T;
	#define RKH_TRCE_TSTAMP()					\
				RKH_TRCE_UI8( rkh_trc_getts() )
#else
	typedef rkhui8_t RKHTS_T;
	#define RKH_TRCE_TSTAMP()					\
				RKH_TRCE_UI8( rkh_trc_getts() )
#endif


#define RKH_TRCE_BEGIN()
#define RKH_TRCE_END()

#define RKH_TRCE_UI8( d )	\
			rkh_trc_ui8( d )

#define RKH_TRCE_UI16( d )	\
			rkh_trc_ui16( d )

#define RKH_TRCE_UI32( d )	\
			rkh_trc_ui32( d )


#if RKH_TRC_EN_TSTAMP == 1
	#define RKH_TRCE_HDR( teid ) 		\
				RKH_TRCE_UI8( teid );	\
				RKH_TRCE_TSTAMP()
#else
	#define RKH_TRCE_HDR( teid ) 		\
				RKH_TRCE_UI8( teid )
#endif


#if RKH_TRC_SIZEOF_POINTER == 16
	#define RKH_TRCE_OBJ_( obj )	\
				RKH_TRCE_UI16( obj )
#elif RKH_TRC_SIZEOF_POINTER == 32
	#define RKH_TRCE_OBJ_( obj )	\
				RKH_TRCE_UI32( obj )
#else
	#define RKH_TRCE_OBJ_( obj )	\
				RKH_TRCE_UI32( obj )
#endif


#if RKH_TIMER_SIZEOF_NTIMER == 8
	#define RKH_TRCE_NTICK_( nt )	\
				RKH_TRCE_UI8( nt )
#elif RKH_TIMER_SIZEOF_NTIMER == 16
	#define RKH_TRCE_NTICK_( nt )	\
				RKH_TRCE_UI16( nt )
#elif RKH_TIMER_SIZEOF_NTIMER == 32
	#define RKH_TRCE_NTICK_( nt )	\
				RKH_TRCE_UI32( nt )
#else
	#define RKH_TRCE_NTICK_( nt )	\
				RKH_TRCE_UI8( nt )
#endif


#if RKH_TRC_EN == 1

	/* --- Memory Pool (MP) --- */
	/* --- Queue (RQ) --- */
	/* --- State Machine Application (SMA) --- */
	/* --- State machine (SM) --- */

	/* --- Timer (TIM) --- */

	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_TIM == 1
		#define RKH_TRCREC_TIM_START( t, nt, sma ) 			\
					RKH_TRCE_BEGIN(); 						\
						RKH_TRCE_HDR( RKH_TRC_TIM_START );	\
						RKH_TRCE_OBJ( t ); 					\
						RKH_TRCE_NTICK_( nt ); 				\
						RKH_TRCE_OBJ( sma ); 				\
					RKH_TRCE_END()
	#else
		#define RKH_TRCREC_TIM_START( t, nt, sma )
	#endif

	
	/* --- OLD --- */
	#if RKH_TRC_TRACE_ALL == 1 || RKH_TRC_EN_EVENT == 1
		#define RKH_REC_EVENT( e, s, n )
	#else
		#define RKH_REC_EVENT( e, s, n )
	#endif

	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_TRN_SRC == 1
		#define RKH_REC_SRC_STATE( e, s, n, str )
	#else
		#define RKH_REC_SRC_STATE( e, s, n, str )
	#endif

	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_TRN_TGT == 1
		#define RKH_REC_TGT_STATE( e, s, n, str )
	#else
		#define RKH_REC_TGT_STATE( e, s, n, str )
	#endif

	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_NXT_STATE == 1
		#define RKH_REC_NXT_STATE( e, s, n, str )
	#else
		#define RKH_REC_NXT_STATE( e, s, n, str )
	#endif

	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_INT_TRAN == 1
		#define RKH_REC_INT_TRAN( e, s )
	#else
		#define RKH_REC_INT_TRAN( e, s )
	#endif

	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_ENTRY == 1
		#define RKH_REC_ENTRY( e, s, n, str )
	#else
		#define RKH_REC_ENTRY( e, s, n, str )
	#endif

	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_EXIT == 1
		#define RKH_REC_EXIT( e, s, n, str )
	#else
		#define RKH_REC_EXIT( e, s, n, str )
	#endif

	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_INIT_HSM == 1
		#define RKH_REC_INIT_HSM( e, s, n, str )
	#else
		#define RKH_REC_INIT_HSM( e, s, n, str )
	#endif

	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_SGT == 1
		#define RKH_REC_SGT( e, s, n, str )
	#else
		#define RKH_REC_SGT( e, s, n, str )
	#endif

	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_RTN_CODE == 1
		#define RKH_REC_RTN_CODE( e, s, n )
	#else
		#define RKH_REC_RTN_CODE( e, s, n )
	#endif

	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_NUM_ENEX == 1
		#define RKH_REC_NUM_ENEX( e, s, n )
	#else
		#define RKH_REC_NUM_ENEX( e, s, n )
	#endif

	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_NUM_ACTSGT == 1
		#define RKH_REC_NUM_ACTSGT( e, s, n )
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


/**
 * 	\brief
 * 	Describes a trace event. 
 * 
 * 	Trace events are binary data consisting of a trace header and its 
 * 	associated event data. Every trace header is made up of a 1-byte ID and a 
 * 	timestamp. The number of bytes used by the timestamp is configurable by 
 * 	RKH_TRC_SIZEOF_TS (1, 2 or 4 bytes). After the timestamp follows the event 
 * 	data. The content and size of the data portion of a trace event is 
 * 	determined by the event ID. 
 *	All types of events are stored in a single ring buffer, called trace 
 *	stream, using a fixed event size of RKH_TRC_SIZEOF_EVENT bytes. In this 
 *	manner the recorder always holds the most recent history.
 *	On the other hand, all data are stored in little-endian order (least 
 *	significant byte first). Also, they are stored into the trace stream 1 
 *	byte at a time, thus avoiding any potential data misalignment problems.
 *	
 *	\note
 *	The timestamp is optional, thus it could be eliminated from the trace 
 *	event in compile-time with RKH_TRC_TSTAMP_EN = 0.
 */

typedef rkhui8_t RKH_TRCEVT_T[ RKH_TRC_SIZEOF_EVENT ];


/**
 * 	\brief
 * 	Inits the trace facility module.
 */

void rkh_trc_init( void );


/**
 * 	\brief
 * 	Starts or stops the tracing session.
 *
 * 	\param opt		control option. Use RKH_TRC_START to start recording
 * 					events.	
 */

void rkh_trc_control( HUInt opt );


/**
 * 	\brief
 *	Retrieves a pointer to oldest trace event in trace stream.
 *
 * 	\param ptrce		pointer to the buffer into which the event retrieved
 * 						will be copied.
 *
 * 	\returns
 * 	RKH_TRC_OK if trace stream was not empty, otherwise RKH_TRC_EMPTY.
 */

HUInt rkh_trc_get( RKH_TRCEVT_T *ptrce );


void rkh_trc_ui8( rkhui8_t d );
void rkh_trc_ui16( rkhui16_t d );
void rkh_trc_ui32( rkhui32_t d );


#endif
