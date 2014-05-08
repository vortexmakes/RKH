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
 * RKH web site:	http://sourceforge.net/projects/rkh-reactivesys/
 * e-mail:			lf@vxtsolutions.com.ar
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
 * 	- the trace event identifier (#RKH_TRC_EVENTS enumerated list),
 * 	- a timestamp (optional),
 * 	- any extra data that the system wants to associate with the event 
 * 	(optional).
 *
 * 	When the system or an application trace an event, all the information 
 * 	related to it has to be stored somewhere before it can be retrieved, in 
 * 	order to be analyzed. This place is a trace stream. Formally speaking, a 
 * 	trace stream is defined as a non-persistent, internal (opaque) data 
 * 	object containing a sequence of trace events plus some internal 
 * 	information to interpret those trace events.
 *	
 *	Also, the streams support runtime filtering. The application can define and 
 *	apply a filter to a trace stream. Basically, the filter establishes which 
 *	event types the stream is accepting (and hence storing) and which are not.
 *	Therefore, trace events corresponding to types which are filtered out 
 *	from a certain stream will not be stored in the stream. The stream in the 
 *	system can potentially be applied a different filter. This filter can be 
 *	applied, removed or changed at any time.
 *
 *	\sa RKH_TRC_EVENTS the enumerated list of RKH trace events.
 */


#ifndef __RKHTRC_H__
#define __RKHTRC_H__


#include "rkhcfg.h"
#include "rkhtype.h"
#include "rkhplat.h"
#include "rkhevt.h"


#define RKH_TRC_MAX_GROUPS			7
#define RKH_MAX_NUM_TE_PER_GROUP	32 /* 2^5 = 32 */

/**
 *	Specify the maximum number of trace events, this number is direclty 
 *	related with the #RKH_TRC_EVENTS enumeration. The smaller this number, 
 *	the lower the RAM consumption.
 *	See \c #trceftbl table.
 */

#define RKH_TRC_MAX_EVENTS			RKH_MAX_NUM_TE_PER_GROUP*RKH_TRC_MAX_GROUPS


/**
 * 	\brief
 * 	The size of trcsmaftbl[] (trace SMA filter table) depends on #RKH_MAX_SMA 
 * 	(see rkhcfg.h).
 */

#if ((RKH_MAX_SMA & (8-1)) == 0)
	#define RKH_TRC_MAX_SMA		(RKH_MAX_SMA/8)
#else
	#define RKH_TRC_MAX_SMA		(RKH_MAX_SMA/8 + 1)
#endif

/**
 * 	\brief
 * 	The size of trcsigftbl[] (trace signal filter table) depends on 
 * 	#RKH_MAX_SIGNALS and #RKH_SIZEOF_EVENT (see rkhcfg.h).
 */

#if ((RKH_MAX_SIGNALS & (8-1)) == 0)
	#define RKH_TRC_MAX_SIGNALS	(RKH_MAX_SIGNALS/8)
#else
	#define RKH_TRC_MAX_SIGNALS	(RKH_MAX_SIGNALS/8 + 1)
#endif


/** 
 * 	\brief
 * 	This data type defines the size of filter table for AO and signals.
 */

#if RKH_TRC_MAX_SMA > RKH_TRC_MAX_SIGNALS
	#if (RKH_TRC_MAX_SMA * 8) <= RKH_DEF_BIT(8)
		typedef rkhui8_t TRCFS_T;
	#elif (RKH_TRC_MAX_SMA * 8) <= RKH_DEF_BIT(16)
		typedef rkhui16_t TRCFS_T;
	#elif (RKH_TRC_MAX_SMA * 8) <= RKH_DEF_BIT(32)
		typedef rkhui32_t TRCFS_T;
	#else
		typedef rkhui8_t TRCFS_T;
	#endif
#else
	#if (RKH_TRC_MAX_SIGNALS * 8) <= RKH_DEF_BIT(8)
		typedef rkhui8_t TRCFS_T;
	#elif (RKH_TRC_MAX_SIGNALS * 8) <= RKH_DEF_BIT(16)
		typedef rkhui16_t TRCFS_T;
	#elif (RKH_TRC_MAX_SIGNALS * 8) <= RKH_DEF_BIT(32)
		typedef rkhui32_t TRCFS_T;
	#else
		typedef rkhui8_t TRCFS_T;
	#endif
#endif


/**
 * 	\brief
 *	Represents the filter of signal and active object.
 */

typedef struct FIL_T
{
	TRCFS_T size;			/** Size of filter table in bytes */
	rkhui8_t *const tbl;	/** Points to filter table in RAM */
} FIL_T;


extern const FIL_T fsig;
extern const FIL_T fsma;


#if RKH_TRC_SIZEOF_STREAM < 255u
	typedef rkhui8_t TRCQTY_T;
#else
	typedef rkhui16_t TRCQTY_T;
#endif


/**@{
 *
 * 	\brief
 * 	Trace event offset.
 *
 * 	The trace event ID is arranged as:
 *
 * 	event number = | G | G | G | E | E | E | E | E |\n
 *
 * 	G's:	group number.\n
 * 	E's:	event's group.\n
 *
 * 	The lower 5 bits (E's) of the event ID are used to determine 
 * 	the trace event, while the next three most significant bits 
 * 	(G's) are used to determine the corresponding group.
 * 	Therefore, is able to define 8 groups and 32 events per group.
 */

#define RKH_MP_START				GRPLSH( RKH_TG_MP	)
#define RKH_RQ_START				GRPLSH( RKH_TG_RQ 	)
#define RKH_SMA_START				GRPLSH( RKH_TG_SMA 	)
#define RKH_SM_START				GRPLSH( RKH_TG_SM 	)
#define RKH_TIM_START				GRPLSH( RKH_TG_TIM 	)
#define RKH_FWK_START				GRPLSH( RKH_TG_FWK 	)
#define RKH_USR_START				GRPLSH( RKH_TG_USR 	)
/*@}*/


/**@{
 * 	Max. number of used trace events in a particular group in octets, thus 
 * 	the desired value must be divided by 8 (1 -> 8 events).
 * 	\note 
 * 	Must be less than or equal to RKH_MAX_NUM_TE_PER_GROUP/8.
 */

#define RKH_MP_TTBL_RANGE			1
#define RKH_RQ_TTBL_RANGE			1
#define RKH_SMA_TTBL_RANGE			1
#define RKH_SM_TTBL_RANGE			3
#define RKH_TIM_TTBL_RANGE			1
#define RKH_FWK_TTBL_RANGE			3
#define RKH_USR_TTBL_RANGE			4
/*@}*/


/**
 * 	Defines the total number of trace events.
 */

#define RKH_TOT_NUM_TRC_EVTS		(	RKH_MP_TTBL_RANGE 	+ \
										RKH_RQ_TTBL_RANGE 	+ \
										RKH_SMA_TTBL_RANGE 	+ \
										RKH_SM_TTBL_RANGE 	+ \
										RKH_TIM_TTBL_RANGE 	+ \
										RKH_FWK_TTBL_RANGE 	+ \
										RKH_USR_TTBL_RANGE )

/**
 * 	\brief
 * 	Defines the size of trace filter table according to RKH_TOT_NUM_TRC_EVTS 
 * 	and RKH_TRC_MAX_EVENTS.
 */

#if (RKH_TOT_NUM_TRC_EVTS <= RKH_TOT_NUM_TRC_EVTS)
	#define RKH_TRC_MAX_EVENTS_IN_BYTES		RKH_TOT_NUM_TRC_EVTS
#else
	#error  "rkhtrc.h, the total number of trace events represented"
	#error  "by RKH_TOT_NUM_TRC_EVTS must be <= RKH_TRC_MAX_EVENTS"
#endif


#define RKH_MP_TTBL_OFFSET			0
#define RKH_RQ_TTBL_OFFSET			(RKH_MP_TTBL_OFFSET + RKH_MP_TTBL_RANGE)
#define RKH_SMA_TTBL_OFFSET			(RKH_RQ_TTBL_OFFSET + RKH_RQ_TTBL_RANGE)
#define RKH_SM_TTBL_OFFSET			(RKH_SMA_TTBL_OFFSET + RKH_SMA_TTBL_RANGE)
#define RKH_TIM_TTBL_OFFSET			(RKH_SM_TTBL_OFFSET + RKH_SM_TTBL_RANGE)
#define RKH_FWK_TTBL_OFFSET			(RKH_TIM_TTBL_OFFSET + RKH_TIM_TTBL_RANGE)
#define RKH_USR_TTBL_OFFSET			(RKH_FWK_TTBL_OFFSET + RKH_FWK_TTBL_RANGE)


#if RKH_MAX_NUM_TE_PER_GROUP <= 32
	#define NGSH					5
#else
	#define NGSH					5
#endif

#define GRPLSH( grp )				(rkhui8_t)(((grp) & 7) << NGSH)
#define EXTE( te, grp )				(rkhui8_t)((te) - GRPLSH(grp))


#define ECHANGE						0
#define EUNCHANGE					1


#if ((	(RKH_TRC_EN == 1) && \
		(RKH_SMA_EN_TRC_SENDER == 1)) || \
		(RKH_EN_DOXYGEN == 1))

	/**
	 * 	\brief
	 * 	This macro is used to verify the sender object usage on post an event.
	 *
	 * 	The macros RKH_TIM_TICK(), RKH_SMA_POST_FIFO(), and 
	 * 	RKH_SMA_POST_LIFO() takes an additional argument \a sender, which is a 
	 * 	pointer to the sender object. This argument is actually only used when 
	 * 	software tracing is enabled (macro #RKH_USE_TRC_SENDER is defined). 
	 * 	When software tracing is disabled, the macros RKH_TIM_TICK(), 
	 * 	RKH_SMA_POST_FIFO(), and RKH_SMA_POST_LIFO() calls rkh_tim_tick(), 
	 * 	rkh_sma_post_fifo(), and rkh_sma_post_lifo() respectively without any 
	 * 	arguments, so the overhead of passing this extra argument is entirely 
	 * 	avoided.
	 */

	#define RKH_USE_TRC_SENDER

#endif


/**
 * 	\brief
 * 	Emit or suppress tracing for all groups and events.
 */

#define RKH_TRC_ALL_GROUPS		RKH_TG_NGROUP


/**
 * 	\brief
 * 	Emit or suppress all trace events.
 */

#define RKH_TRC_ALL_EVENTS		RKH_TE_NEVENT

/**
 * 	\brief
 * 	Emit or supress tracing for all signal/active objects.
 */

#define RKH_TRC_SET_ALL( mode_ ) \
				((mode_)|RKH_TRC_ALL_FILTERS)
#define RKH_TRC_ALL_FILTERS		0x80
#define RKH_FILTER_MODE_MASK	~RKH_TRC_ALL_FILTERS


typedef enum
{
	FILTER_ON, FILTER_OFF
} RKH_TRC_FOPT;


typedef enum RKH_FIL_T
{
	RKH_FIL_TRCE, RKH_FIL_SIG, RKH_FIL_SMA
} RKH_FIL_T;


/**
 * 	\brief
 * 	RKH group of trace events
 */

typedef enum rkh_trc_groups
{
	/**
	 * 	\brief
	 * 	Memory Pool group (MP)
	 */
	RKH_TG_MP,

	/**
	 * 	\brief
	 * 	Reference Queue group (RQ)
	 */
	RKH_TG_RQ,

	/**
	 * 	\brief
	 * 	State Machine Application group (SMA)
	 */
	RKH_TG_SMA,

	/**
	 * 	\brief
	 * 	State Machine group (SM)
	 */
	RKH_TG_SM,

	/**
	 * 	\brief
	 * 	Timer group (TIM)
	 */
	RKH_TG_TIM,

	/**
	 * 	\brief
	 * 	Framework RKH group (FWK)
	 */
	RKH_TG_FWK,

	/**
	 * 	\brief
	 * 	User group (USR)
	 */
	RKH_TG_USR,

	RKH_TG_NGROUP
} RKH_TRC_GROUPS;


/**
 * 	\brief
 * 	RKH trace events.
 *
 * 	<EM>RKH trace event structure</EM>
 *
 *	\code
 *	(1) RKH_TRC_BEGIN( trc_evt, ao_prio, signal )	\
 *	(2)		RKH_TRC_ARG0( arg0 ); 					\
 *	(3)		RKH_TRC_ARG1( arg1 ); 					\
 *	(4)		RKH_TRC_....( ... ); 					\
 *	(5)	RKH_TRC_END()
 *	\endcode
 *
 *	\li (1,5)	Each trace event always begins with the macro RKH_TRC_BEGIN() 
 *				and ends with the matching macro RKH_TRC_END().
 *			 	These macros are not terminated with the semicolon.
 *			 	The record-begin macro RKH_TRC_BEGIN() takes three arguments. 
 *			 	The first argument 'trc_evt' is the trace event ID, the second 
 *			 	argument 'ao_prio' is the active object priority, and the 
 *			 	third argument 'signal' is the event signal number. These 
 *			 	arguments are used in the on/off filters. 
 *			 	The runtime filter is optional and could be enabled or 
 *			 	disabled with the #RKH_TRC_RUNTIME_FILTER in the \b rkhcfg.h 
 *			 	file. This pair of macros locks interrupts at the beginning 
 *			 	and unlocks at the end of each record.
 *	\li (2-4) 	Sandwiched between these two macros are the 
 *				argument-generating macros that actually insert individual 
 *				event argument elements into the trace stream.
 *
 * 	Example:
 *	
 *	\code
 *	#define RKH_TR_RQ_INIT( q, ao, nelem  )				\
 *				RKH_TRC_BEGIN_WOAOSIG( RKH_TE_RQ_INITS )\
 *					RKH_TRC_SYM( q ); 					\
 *					RKH_TRC_SYM( ao ); 					\
 *					RKH_TRC_NE( nelem ); 				\
 *				RKH_TRC_END()
 *	
 *	#define RKH_TR_SMA_FIFO( ao, ev, snr, pid, rc )		\
 *				RKH_TRC_BEGIN( 	RKH_TE_SMA_FIFO, 		\
 *								(ao)->romrkh->prio,		\
 *								ev->e )					\
 *					RKH_TRC_SYM( ao ); 					\
 *					RKH_TRC_SIG( ev->e ); 				\
 *					RKH_TRC_SENDER( snr ); 				\
 *					RKH_TRC_UI8( pid ); 				\
 *					RKH_TRC_UI8( rc ); 					\
 *				RKH_TRC_END()
 *	\endcode
 *
 *	Each trace event and its arguments are placed in the trace stream like a 
 *	simple data protocol frame. The protocol has been specifically designed 
 *	to simplify the data management overhead in the target yet allow 
 *	detection of any data dropouts due to the trace buffer overruns. 
 *	The protocol has not only provisions for detecting gaps in the data and 
 *	other errors but allows for instantaneous resynchronization after any 
 *	error, to minimize data loss. [MS]
 *	
 *	\a Frame
 *
 * 	\code
 *      | ...               |
 *  (1) | event ID          | 1-byte
 *  (2) | sequence number   | 1-byte
 *  (3) | timestamp         | 2,4-bytes
 *  (4) | args              | n-byte
 *  (5) | checksum          | 1-byte
 *  (6) | flag              | 1-byte
 *      | ...               |
 *	\endcode
 *
 *	- 	(1) Each frame starts with the <B>trace event ID</B> byte, which is 
 *		one of the predefined RKH records or an application-specific record.
 *	- 	(2) Following the <B>sequence number</B> is the sequence number byte. 
 *		The target component increments this number for every frame inserted 
 *		into the stream. The sequence number allows the trazer tool to detect 
 *		any data discontinuities. If the #RKH_TRC_EN_NSEQ is set to 1 then 
 *		RKH will add to the trace record the sequence number.
 *	-	(3) Following the sequence number is the <B>timestamp</B>. The number 
 *		of bytes used by the timestamp is configurable by the macro 
 *		#RKH_TRC_SIZEOF_TSTAMP.
 *		If the #RKH_TRC_EN_TSTAMP is set to 1 then RKH will add to the 
 *		trace record the timestamp field.
 *	- 	(4) Following the timestamp is zero or more data bytes for <B>args</B>.
 *	- 	(5) Following the data is the <B>checksum</B> byte. The checksum is 
 *		computed over the sequence number, the trace event ID, and all the 
 *		data bytes. 
 *		If the #RKH_TRC_EN_CHK is set to 1 then RKH will add to the trace 
 *		record a checksum byte.
 *	- 	(6) Following the checksum is the <B>flag</B> byte, which delimits 
 *		the frame. The flag is the 0x7E. Only one flag is inserted between 
 *		frames.
 *	
 *	To avoid confusing unintentional flag bytes that can naturally occur in 
 *	the data stream with an intentionally sent flag, the protocol uses a 
 *	technique known as byte stuffing or escaping to make the flag bytes 
 *	transparent during the transmission.
 *	Whenever the transmitter encounters a flag byte in the data, it inserts 
 *	a 2-byte escape sequence to the output stream. The first byte is the 
 *	escape byte, defined as binary 0x7D. The second byte is the original 
 *	byte XOR-ed with 0x20.
 *	The transmitter computes the checksum over the sequence number, the 
 *	trace event ID, and all data bytes before performing any byte stuffing.
 *
 * 	<em>User trace events</em>
 *
 * 	The user application could defined its own trace events to be placed 
 * 	at anywhere in the application level. Allowing to generate tracing 
 * 	information from the application-level code like a "printf" but with 
 * 	much less overhead.
 *
 *	\code
 *	(1) RKH_TRC_USR_BEGIN( MY_TRACE )	\
 *	(2)		RKH_TRC_ARG0( arg0 ); 		\
 *	(3)		RKH_TRC_ARG1( arg1 ); 		\
 *	(4)		RKH_TRC_....( ... ); 		\	
 *	(5)	RKH_TRC_USR_END();
 *	\endcode
 *
 *	\li (1,5)	Each trace event always begins with the macro 
 *				RKH_TRC_USR_BEGIN() and ends with the matching macro 
 *				RKH_TRC_USR_END(). The record-begin macro RKH_TRC_USR_BEGIN() 
 *				takes one argument, 'eid_' is the user trace event ID, from 
 *				the RKH_TE_USER value. This pair of macros locks interrupts 
 *				at the beginning and unlocks at the end of each record.
 *	\li (2-4) 	Sandwiched between these two macros are the 
 *				argument-generating macros that actually insert individual 
 *				event argument elements into the trace stream.
 *
 *	Argument-generating macros for building user trace events:
 *
 *	\li RKH_TUSR_I8() 	\copydoc RKH_TUSR_I8
 *	\li RKH_TUSR_UI8() 	\copydoc RKH_TUSR_UI8
 *	\li RKH_TUSR_I16() 	\copydoc RKH_TUSR_I16
 *	\li RKH_TUSR_UI16() \copydoc RKH_TUSR_UI16
 *	\li RKH_TUSR_I32() 	\copydoc RKH_TUSR_I32
 *	\li RKH_TUSR_UI32() \copydoc RKH_TUSR_UI32
 *	\li RKH_TUSR_X32() 	\copydoc RKH_TUSR_X32
 *	\li RKH_TUSR_STR() 	\copydoc RKH_TUSR_STR
 *	\li RKH_TUSR_MEM() 	\copydoc RKH_TUSR_MEM
 *	\li RKH_TUSR_OBJ() 	\copydoc RKH_TUSR_OBJ
 *	\li RKH_TUSR_FUN() 	\copydoc RKH_TUSR_FUN
 *	\li RKH_TUSR_SIG() 	\copydoc RKH_TUSR_SIG
 *
 * 	Example:
 *	
 *	\code
 *	enum
 *	{
 *		LOWPWR_USR_TRACE = RKH_TE_USER,
 *		DISCONNECTED_USR_TRACE
 *		...
 *	};
*
 *	void
 *	some_function( ... )
 *	{
 *		rkhui8_t d1 = 255;
 *		rkhui16_t d2 = 65535;
 *		rkhui32_t d3 = 65535;
 *		char *str = "hello";
 *
 *		RKH_TRC_USR_BEGIN( LOWPWR_USR_TRACE )
 *			RKH_TUSR_I8( 3, d1 );
 *			RKH_TUSR_UI8( 3, d1 );
 *			RKH_TUSR_I16( 4, d2 );
 *			RKH_TUSR_UI16( 4, d2 );
 *			RKH_TUSR_I32( 5, d3 );
 *			RKH_TUSR_UI32( 5, d3 );
 *			RKH_TUSR_X32( 4, d3 );
 *			RKH_TUSR_STR( str );
 *			RKH_TUSR_MEM( (rkhui8_t*)&d3, sizeof(rkhui32_t) );
 *			RKH_TUSR_OBJ( my );
 *			RKH_TUSR_FUN( main );
 *			RKH_TUSR_SIG( ZERO );
 *		RKH_TRC_USR_END();
 *	}
 *	\endcode
 *
 *	\sa RKH_TRC_HDR(), RKH_TRC_END(), RKH_TRC_CHK().
 */

typedef enum rkh_trc_events
{
	/* --- Memory Pool events (MP group) ------------------ */
	RKH_TE_MP_INIT = RKH_MP_START,	/**< \copydetails RKH_TR_MP_INIT */
	RKH_TE_MP_GET, 					/**< \copydetails RKH_TR_MP_GET */
	RKH_TE_MP_PUT,					/**< \copydetails RKH_TR_MP_PUT */
	
	/* --- Queue events (RQ group) ------------------------ */
	RKH_TE_RQ_INIT = RKH_RQ_START,	/**< \copydetails RKH_TR_RQ_INIT */
	RKH_TE_RQ_GET,					/**< \copydetails RKH_TR_RQ_GET */
	RKH_TE_RQ_FIFO,					/**< \copydetails RKH_TR_RQ_FIFO */
	RKH_TE_RQ_LIFO,					/**< \copydetails RKH_TR_RQ_LIFO */
	RKH_TE_RQ_FULL,					/**< \copydetails RKH_TR_RQ_FULL */
	RKH_TE_RQ_DPT,					/**< \copydetails RKH_TR_RQ_DPT */
	RKH_TE_RQ_GET_LAST,				/**< \copydetails RKH_TR_RQ_GET_LAST */

	/* --- State Machine Application events (SMA group) --- */
	RKH_TE_SMA_ACT = RKH_SMA_START,	/**< \copydetails RKH_TR_SMA_ACT */
	RKH_TE_SMA_TERM,				/**< \copydetails RKH_TR_SMA_TERM */
	RKH_TE_SMA_GET,					/**< \copydetails RKH_TR_SMA_GET */
	RKH_TE_SMA_FIFO,				/**< \copydetails RKH_TR_SMA_FIFO */
	RKH_TE_SMA_LIFO,				/**< \copydetails RKH_TR_SMA_LIFO */
	RKH_TE_SMA_REG,					/**< \copydetails RKH_TR_SMA_REG */
	RKH_TE_SMA_UNREG,				/**< \copydetails RKH_TR_SMA_UNREG */

	/* --- State machine events (SM group) ---------------- */
	RKH_TE_SM_INIT = RKH_SM_START,	/**< \copydetails RKH_TR_SM_INIT */
	RKH_TE_SM_CLRH,					/**< \copydetails RKH_TR_SM_CLRH */
	RKH_TE_SM_DCH,					/**< \copydetails RKH_TR_SM_DCH */
	RKH_TE_SM_TRN,					/**< \copydetails RKH_TR_SM_TRN */
	RKH_TE_SM_STATE,				/**< \copydetails RKH_TR_SM_STATE */
	RKH_TE_SM_ENSTATE,				/**< \copydetails RKH_TR_SM_ENSTATE */
	RKH_TE_SM_EXSTATE,				/**< \copydetails RKH_TR_SM_EXSTATE */
	RKH_TE_SM_NENEX,				/**< \copydetails RKH_TR_SM_NENEX */
	RKH_TE_SM_NTRNACT,				/**< \copydetails RKH_TR_SM_NTRNACT */
	RKH_TE_SM_TS_STATE,				/**< \copydetails RKH_TR_SM_TS_STATE */
	RKH_TE_SM_EVT_PROC,				/**< \copydetails RKH_TR_SM_EVT_PROC */
	RKH_TE_SM_EVT_NFOUND,			/**< \copydetails RKH_TR_SM_EVT_NFOUND */
	RKH_TE_SM_GRD_FALSE,			/**< \copydetails RKH_TR_SM_GRD_FALSE */
	RKH_TE_SM_CND_NFOUND,			/**< \copydetails RKH_TR_SM_CND_NFOUND */
	RKH_TE_SM_UNKN_STATE,			/**< \copydetails RKH_TR_SM_UNKN_STATE */
	RKH_TE_SM_EX_HLEVEL,			/**< \copydetails RKH_TR_SM_EX_HLEVEL */
	RKH_TE_SM_EX_TSEG,				/**< \copydetails RKH_TR_SM_EX_TSEG */

	/* --- Timer events (TIM group) ----------------------- */
	RKH_TE_TIM_INIT = RKH_TIM_START,/**< \copydetails RKH_TR_TIM_INIT */
	RKH_TE_TIM_START,				/**< \copydetails RKH_TR_TIM_START */
	RKH_TE_TIM_STOP,				/**< \copydetails RKH_TR_TIM_STOP */
	RKH_TE_TIM_TOUT,				/**< \copydetails RKH_TR_TIM_TOUT */
	RKH_TE_TIM_REM,					/**< \copydetails RKH_TR_TIM_REM */

	/* --- Framework and misc. events (FWK group) ------------------- */
	RKH_TE_FWK_EN = RKH_FWK_START,	/**< \copydetails RKH_TR_FWK_EN */
	RKH_TE_FWK_EX,					/**< \copydetails RKH_TR_FWK_EX */
	RKH_TE_FWK_EPREG,				/**< \copydetails RKH_TR_FWK_EPREG */
	RKH_TE_FWK_AE,					/**< \copydetails RKH_TR_FWK_AE */
	RKH_TE_FWK_GC,					/**< \copydetails RKH_TR_FWK_GC */
	RKH_TE_FWK_GCR,					/**< \copydetails RKH_TR_FWK_GCR */
	RKH_TE_FWK_DEFER,				/**< \copydetails RKH_TR_FWK_DEFER */
	RKH_TE_FWK_RCALL,				/**< \copydetails RKH_TR_FWK_RCALL */
	RKH_TE_FWK_OBJ,					/**< \copydetails RKH_TR_FWK_OBJ */
	RKH_TE_FWK_SIG,					/**< \copydetails RKH_TR_FWK_SIG */
	RKH_TE_FWK_FUN,					/**< \copydetails RKH_TR_FWK_FUN */
	RKH_TE_FWK_EXE_FUN,				/**< \copydetails RKH_TR_FWK_EXE_FUN */
	RKH_TE_FWK_TUSR,				/**< \copydetails RKH_TR_FWK_TUSR */
	RKH_TE_FWK_TCFG,				/**< \copydetails RKH_TR_FWK_TCFG */
	RKH_TE_FWK_ASSERT,				/**< \copydetails RKH_TR_FWK_ASSERT */
	RKH_TE_FWK_AO,					/**< \copydetails RKH_TR_FWK_AO */
	RKH_TE_FWK_STATE,				/**< \copydetails RKH_TR_FWK_STATE */
	RKH_TE_FWK_PSTATE,				/**< \copydetails RKH_TR_FWK_PSTATE */
	RKH_TE_FWK_TIMER,				/**< \copydetails RKH_TR_FWK_TIMER */
	RKH_TE_FWK_EPOOL,				/**< \copydetails RKH_TR_FWK_EPOOL */
	RKH_TE_FWK_QUEUE,				/**< \copydetails RKH_TR_FWK_QUEUE */

	RKH_TE_USER = RKH_USR_START,

	RKH_TE_NEVENT = 255
} RKH_TRC_EVENTS;


/** x-ored byte for stuffing a single byte */
#define RKH_XOR		0x20
/** flag byte, used as a trace event delimiter */
#define RKH_FLG		0x7E
/** escape byte stuffing a single byte */
#define RKH_ESC		0x7D


/**
 * 	\brief
 * 	Inserts the previously calculated checksum as:
 * 	checksum = 0 - sum mod-256 -> ~(sum mod-256) + 1.
 */

#if RKH_TRC_EN_CHK == RKH_DEF_ENABLED
	#define RKH_TRC_CHK()					\
				chk = (rkhui8_t)(~chk + 1); \
				rkh_trc_u8( chk )
#else
	#define RKH_TRC_CHK()
#endif


/**
 * 	\brief
 * 	Inserts directly into the trace stream the flag byte in a raw (without 
 * 	escaped sequence) manner.
 */

#define RKH_TRC_FLG()						\
				RKH_TRC_U8_RAW( RKH_FLG )


/** 
 * 	\brief
 * 	Defines the size of trace timestamp. 
 *
 * 	The valid values [in bits] are 8, 16 or 32. Default is 16. This type is 
 * 	configurable via the RKH_TRC_SIZEOF_TSTAMP preprocessor option.
 */

#if RKH_TRC_EN_TSTAMP == RKH_DEF_ENABLED
	#if RKH_TRC_SIZEOF_TSTAMP == 8
		typedef rkhui8_t RKHTS_T;
		#define RKH_TRC_TSTAMP()					\
					RKH_TRC_UI8( rkh_trc_getts() )
	#elif RKH_TRC_SIZEOF_TSTAMP == 16
		typedef rkhui16_t RKHTS_T;
		#define RKH_TRC_TSTAMP()					\
					RKH_TRC_UI16( rkh_trc_getts() )
	#elif RKH_TRC_SIZEOF_TSTAMP == 32
		typedef rkhui32_t RKHTS_T;
		#define RKH_TRC_TSTAMP()					\
					RKH_TRC_UI32( rkh_trc_getts() )
	#else
		typedef rkhui16_t RKHTS_T;
		#define RKH_TRC_TSTAMP()					\
					RKH_TRC_UI16( rkh_trc_getts() )
	#endif
#else
	typedef rkhui16_t RKHTS_T;
	#define RKH_TRC_TSTAMP()
#endif


#if RKH_TRC_RUNTIME_FILTER == RKH_DEF_ENABLED
	/**
	 *	Each trace event always begins with the macro RKH_TRC_BEGIN() 
	 *	and ends with the matching macro RKH_TRC_END(). These macros are 
	 *	not terminated with the semicolon.
	 * 	This pair of macros locks interrupts at the beginning and unlocks 
	 * 	at the end of each record.
	 *
	 * 	\note
	 * 	Both arguments are used in the on/off filter. 
	 * 	\note
	 * 	The runtime filter is optional and could be enabled or 
	 * 	disabled with the RKH_TRC_RUNTIME_FILTER in the rkhcfg.h file.
	 * 	\note
	 * 	This macro always invokes the rkh_trc_begin() function.
	 *
	 *	\param eid_		is the trace event ID (RKH_TRC_EVENTS).
	 *	\param prio_	priority of active object.
	 *	\param sig_		signal.
	 */

	#define RKH_TRC_BEGIN( eid_, prio_, sig_ )	\
				if(	rkh_trc_isoff_( eid_ ) 		\
					RKH_TRC_AO_ISOFF( prio_ )   \
					RKH_TRC_SIG_ISOFF( sig_ ) )	\
				{								\
					RKH_ENTER_CRITICAL_();		\
					rkh_trc_begin( eid_ );

	#define RKH_TRC_BEGIN_WOAO( eid_, sig_ )	\
				if(	rkh_trc_isoff_( eid_ )      \
					RKH_TRC_SIG_ISOFF( sig_ ) )	\
				{								\
					RKH_ENTER_CRITICAL_();		\
					rkh_trc_begin( eid_ );

	#define RKH_TRC_BEGIN_WOSIG( eid_, prio_ )	\
				if(	rkh_trc_isoff_( eid_ )      \
					RKH_TRC_AO_ISOFF( prio_ ) ) \
				{								\
					RKH_ENTER_CRITICAL_();		\
					rkh_trc_begin( eid_ );

	#define RKH_TRC_BEGIN_WOAOSIG( eid_ )		\
				if(	rkh_trc_isoff_( eid_ ) )	\
				{								\
					RKH_ENTER_CRITICAL_();		\
					rkh_trc_begin( eid_ );

	/**
	 *	Each trace event always begins with the macro RKH_TRC_BEGIN() 
	 *	and ends with the matching macro RKH_TRC_END(). These macros are 
	 *	not terminated with the semicolon.
	 * 	This pair of macros locks interrupts at the beginning and unlocks 
	 * 	at the end of each record.
	 *
	 * 	\note
	 * 	This macro always invokes the rkh_trc_end() function.
	 */

	#define RKH_TRC_END()						\
					rkh_trc_end();				\
					RKH_EXIT_CRITICAL_();		\
				}

	/**
	 * 	Idem RKH_TRC_BEGIN() macro but without entering critical section.
	 *
	 *	\param eid_		is the trace event ID (RKH_TRC_EVENTS).
	 *	\param prio_	priority of active object.
	 *	\param sig_		signal.
	 */

	#define RKH_TRC_BEGIN_NOCRIT( eid_, prio_, sig_ )	\
				if(	rkh_trc_isoff_( eid_ )    			\
					RKH_TRC_AO_ISOFF( prio_ )   		\
					RKH_TRC_SIG_ISOFF( sig_ ) )			\
				{										\
					rkh_trc_begin( eid_ );

	/**
	 * 	Idem RKH_TRC_BEGIN_WOAO() macro but without entering critical 
	 * 	section.
	 *
	 *	\param eid_		is the trace event ID (RKH_TRC_EVENTS).
	 *	\param sig_		signal.
	 */

	#define RKH_TRC_BEGIN_WOAO_NOCRIT( eid_, sig_ )		\
				if(	rkh_trc_isoff_( eid_ )      		\
					RKH_TRC_SIG_ISOFF( sig_ ) )			\
				{										\
					rkh_trc_begin( eid_ );

	/**
	 * 	Idem RKH_TRC_BEGIN_WOSIG() macro but without entering critical 
	 * 	section.
	 *
	 *	\param eid_		is the trace event ID (RKH_TRC_EVENTS).
	 *	\param prio_	priority of active object.
	 */

	#define RKH_TRC_BEGIN_WOSIG_NOCRIT( eid_, prio_ )	\
				if(	rkh_trc_isoff_( eid_ )      		\
					RKH_TRC_AO_ISOFF( prio_ ) ) 		\
				{										\
					rkh_trc_begin( eid_ );

	/**
	 * 	Idem RKH_TRC_BEGIN_WOAOSIG() macro but without entering critical 
	 * 	section.
	 *
	 *	\param eid_		is the trace event ID (RKH_TRC_EVENTS).
	 *	\param prio_	priority of active object.
	 */

	#define RKH_TRC_BEGIN_WOAOSIG_NOCRIT( eid_ )		\
				if(	rkh_trc_isoff_( eid_ ) )   			\
				{										\
					rkh_trc_begin( eid_ );

	/**
	 * 	Idem RKH_TRC_EXIT() macro but without exiting critical section.
	 */

	#define RKH_TRC_END_NOCRIT()						\
					rkh_trc_end();						\
				}
#else
	#define RKH_TRC_BEGIN( eid_, prio_, sig_ )			\
				RKH_ENTER_CRITICAL_();					\
				rkh_trc_begin( eid_ );

	#define RKH_TRC_BEGIN_WOAO( eid_, sig_ )			\
				RKH_ENTER_CRITICAL_();					\
				rkh_trc_begin( eid_ );

	#define RKH_TRC_BEGIN_WOSIG( eid_, prio_ )			\
				RKH_ENTER_CRITICAL_();					\
				rkh_trc_begin( eid_ );

	#define RKH_TRC_BEGIN_WOAOSIG( eid_ )				\
				RKH_ENTER_CRITICAL_();					\
				rkh_trc_begin( eid_ );

	#define RKH_TRC_END()								\
				rkh_trc_end();							\
				RKH_EXIT_CRITICAL_();

	#define RKH_TRC_BEGIN_NOCRIT( eid_, prio_, sig_ )	\
				rkh_trc_begin( eid_ );

	#define RKH_TRC_BEGIN_WOAO_NOCRIT( eid_, sig_ )		\
				rkh_trc_begin( eid_ );

	#define RKH_TRC_BEGIN_WOSIG_NOCRIT( eid_, prio_ )	\
				rkh_trc_begin( eid_ );

	#define RKH_TRC_BEGIN_WOAOSIG_NOCRIT( eid_ )		\
				rkh_trc_begin( eid_ );

	#define RKH_TRC_END_NOCRIT()						\
				rkh_trc_end();
#endif


/**
 * 	Idem RKH_TRC_BEGIN() macro but use it for trace events that are 
 * 	independent of any runtime filter.
 */

#define RKH_TRC_BEGIN_WOFIL( eid_ )					\
				RKH_SR_ALLOC();						\
				RKH_ENTER_CRITICAL_();				\
				rkh_trc_begin( eid_ );

/**
 * 	Idem RKH_TRC_END() macro but use it for trace events that are 
 * 	independent of any runtime filter.
 */

#define RKH_TRC_END_WOFIL()							\
				rkh_trc_end();						\
				RKH_EXIT_CRITICAL_();

/**
 * 	Idem RKH_TRC_BEGIN_WOFIL() macro but without entering critical section.
 */

#define RKH_TRC_BEGIN_WOFIL_NOCRIT( eid_ )			\
				rkh_trc_begin( eid_ );

/**
 * 	Idem RKH_TRC_END_WOFIL_NOCRIT() macro but without entering critical 
 * 	section.
 */

#define RKH_TRC_END_WOFIL_NOCRIT()					\
				rkh_trc_end();						\


/**
 * 	\brief
 * 	Insert a 1-byte without escaping it.
 */

#define RKH_TRC_U8_RAW( d )	\
			rkh_trc_put( (d) )

/**
 * 	\brief
 * 	Insert a 1-byte data.
 */

#define RKH_TRC_UI8( d )	\
			rkh_trc_u8( (rkhui8_t)(d) )

/**
 * 	\brief
 * 	Insert a 2-byte data.
 */

#define RKH_TRC_UI16( d )	\
			rkh_trc_u16( (d) )

/**
 * 	\brief
 * 	Insert a 4-byte data.
 */

#define RKH_TRC_UI32( d )	\
			rkh_trc_u32( (d) )

/**
 * 	\brief
 * 	Insert a string.
 */

#define RKH_TRC_STR( s )	\
			rkh_trc_str( (s) )


/** 
 * 	\brief 
 * 	Enumerates data formats recognized by Trazer.
 *
 * 	Trazer uses this enumeration is used only internally for the formatted 
 * 	user data elements.
 */

enum rkh_trc_fmt
{
	RKH_I8_T,		/**< signed 8-bit integer format */
	RKH_UI8_T,		/**< unsigned 8-bit integer format */
	RKH_I16_T,		/**< signed 16-bit integer format */
	RKH_UI16_T,		/**< unsigned 16-bit integer format */
	RKH_I32_T,		/**< signed 32-bit integer format */
	RKH_UI32_T,		/**< unsigned 16-bit integer format */
	RKH_X32_T,		/**< signed 16-bit integer in hex format */
	RKH_STR_T,		/**< zero-terminated ASCII string format */
	RKH_MEM_T,		/**< up to 255-bytes memory block format */
	RKH_OBJ_T,		/**< object pointer format */
	RKH_FUN_T,		/**< function pointer format */
	RKH_SIG_T		/**< event signal format */
};


/** 
 * 	Macros for use in the client code.
 */
	
#if RKH_TRC_EN_USER_TRACE == RKH_DEF_ENABLED

	/**
	 * 	Idem RKH_TRC_BEGIN() macro but use it for user trace events.
	 */

	#define RKH_TRC_USR_BEGIN( eid_ ) 				\
					RKH_SR_ALLOC();					\
					if(	rkh_trc_isoff_( eid_ ) )	\
					{								\
						RKH_ENTER_CRITICAL_();		\
						rkh_trc_begin( eid_ );


	/**
	 * 	Idem RKH_TRC_END() macro but use it for user trace events.
	 */

	#define RKH_TRC_USR_END() 						\
						rkh_trc_end();				\
						RKH_EXIT_CRITICAL_();		\
					}

	/**
	 * 	Idem RKH_TRC_USR_BEGIN() macro but without entering critical section.
	 */

	#define RKH_TRC_USR_BEGIN_NOCRIT( eid_ ) 		\
					if(	rkh_trc_isoff_( eid_ ) )	\
					{								\
						rkh_trc_begin( eid_ );


	/**
	 * 	Idem RKH_TRC_USR_END() macro but without exiting critical section.
	 */

	#define RKH_TRC_USR_END_NOCRIT() 				\
						rkh_trc_end();				\
					}

	/**
	 * 	\brief 
	 * 	Output formatted rkhi8_t to the trace record.
	 */

	#define RKH_TUSR_I8( w_, d_ ) \
			rkh_trc_fmt_u8((rkhui8_t)(((w_) << 4)) | (rkhui8_t)RKH_I8_T, \
								(d_))

	/**
	 * 	\brief 
	 * 	Output formatted rkhui8_t to the trace record.
	 */

	#define RKH_TUSR_UI8( w_, d_ ) \
			rkh_trc_fmt_u8((rkhui8_t)(((w_) << 4)) | (rkhui8_t)RKH_UI8_T, \
								(d_))

	/**
	 * 	\brief 
	 * 	Output formatted rkhi16_t to the trace record.
	 */

	#define RKH_TUSR_I16( w_, d_ ) \
			rkh_trc_fmt_u16((rkhui8_t)(((w_) << 4)) | (rkhui8_t)RKH_I16_T, \
								(d_))

	/**
	 * 	\brief 
	 * 	Output formatted rkhui16_t to the trace record.
	 */

	#define RKH_TUSR_UI16( w_, d_ ) \
			rkh_trc_fmt_u16((rkhui8_t)(((w_) << 4)) | (rkhui8_t)RKH_UI16_T, \
								(d_))

	/**
	 * 	\brief 
	 * 	Output formatted rkhi32_t to the trace record.
	 */

	#define RKH_TUSR_I32( w_, d_ ) \
			rkh_trc_fmt_u32((rkhui8_t)(((w_) << 4)) | (rkhui8_t)RKH_I32_T, \
								(d_))

	/**
	 * 	\brief 
	 * 	Output formatted rkhui32_t to the trace record.
	 */

	#define RKH_TUSR_UI32( w_, d_ ) \
			rkh_trc_fmt_u32((rkhui8_t)(((w_) << 4)) | (rkhui8_t)RKH_UI32_T, \
								(d_))

	/**
	 * 	\brief 
	 * 	Output formatted rkhui32_t to the trace record.
	 */

	#define RKH_TUSR_X32( w_, d_ ) \
			rkh_trc_fmt_u32((rkhui8_t)(((w_) << 4)) | (rkhui8_t)RKH_X32_T, \
								(d_))

	/**
	 * 	\brief 
	 * 	Output formatted zero-terminated ASCII string to the trace record.
	 */

	#define RKH_TUSR_STR( s_ ) \
				rkh_trc_fmt_str((s_))

	/**
	 * 	\brief 
	 * 	Output formatted memory block of up to 255 bytes to the trace record.
	 */

	#define RKH_TUSR_MEM( mem_, size_ ) \
				rkh_trc_fmt_mem((mem_), (size_))

	/**
	 * 	\brief 
	 * 	Output formatted object pointer to the trace record.
	 */

	#if RKH_TRC_SIZEOF_POINTER == 16
		#define RKH_TUSR_OBJ( obj_ )	\
				rkh_trc_fmt_u16((rkhui8_t)RKH_OBJ_T, (rkhui16_t)(obj_))
	#elif RKH_TRC_SIZEOF_POINTER == 32
		#define RKH_TUSR_OBJ( obj_ )	\
				rkh_trc_fmt_u32((rkhui8_t)RKH_OBJ_T, (rkhui32_t)(obj_))
	#else
		#define RKH_TUSR_OBJ( obj_ )	\
				rkh_trc_fmt_u32((rkhui8_t)RKH_OBJ_T, (rkhui32_t)(obj_))
	#endif

	/**
	 * 	\brief 
	 * 	Output formatted function pointer to the trace record.
	 */

	#if RKH_TRC_SIZEOF_FUN_POINTER == 16
		#define RKH_TUSR_FUN( fun_ )	\
				rkh_trc_fmt_u16((rkhui8_t)RKH_FUN_T, (rkhui16_t)(fun_))
	#elif RKH_TRC_SIZEOF_FUN_POINTER == 32
		#define RKH_TUSR_FUN( fun_ )	\
				rkh_trc_fmt_u32((rkhui8_t)RKH_FUN_T, (rkhui32_t)(fun_))
	#else
		#define RKH_TUSR_FUN( fun_ )	\
				rkh_trc_fmt_u32((rkhui8_t)RKH_FUN_T, (rkhui32_t)(fun_))
	#endif

	/**
	 * 	\brief 
	 * 	Output formatted event signal to the trace record.
	 */

	#if RKH_SIZEOF_EVENT == 8
		#define RKH_TUSR_SIG( sig_ ) \
					rkh_trc_fmt_u8((rkhui8_t)RKH_SIG_T, (rkhui8_t)(sig_))
	#elif RKH_SIZEOF_EVENT == 16
		#define RKH_TUSR_SIG( sig_ ) \
					rkh_trc_fmt_u16((rkhui8_t)RKH_SIG_T, (rkhui16_t)(sig_))
	#elif RKH_SIZEOF_EVENT == 32
		#define RKH_TUSR_SIG( sig_ ) \
					rkh_trc_fmt_u32((rkhui8_t)RKH_SIG_T, (rkhui32_t)(sig_))
	#else
		#define RKH_TUSR_SIG( sig_ ) \
					rkh_trc_fmt_u8((rkhui8_t)RKH_SIG_T, (rkhui8_t)(sig_))
	#endif
#else
	#define RKH_TRC_USR_BEGIN( eid_ ) 			(void)0;
	#define RKH_TRC_USR_END()					(void)0
	#define RKH_TRC_USR_BEGIN_NOCRIT( eid_ ) 	(void)0
	#define RKH_TRC_USR_END_NOCRIT()			(void)0
	#define RKH_TUSR_I8( w_, d_ )				(void)0
	#define RKH_TUSR_UI8( w_, d_ )				(void)0
	#define RKH_TUSR_I16( w_, d_ )				(void)0
	#define RKH_TUSR_UI16( w_, d_ )				(void)0
	#define RKH_TUSR_I32( w_, d_ )				(void)0
	#define RKH_TUSR_UI32( w_, d_ )				(void)0
	#define RKH_TUSR_X32( w_, d_ )				(void)0
	#define RKH_TUSR_STR( s_ )					(void)0
	#define RKH_TUSR_MEM( mem_, size_ )			(void)0
	#define RKH_TUSR_OBJ( obj_ )				(void)0
	#define RKH_TUSR_FUN( fun_ )				(void)0
	#define RKH_TUSR_SIG( sig_ )				(void)0
#endif


/**
 * 	\brief
 * 	Insert the sequence number byte.
 */

#if RKH_TRC_EN_NSEQ == RKH_DEF_ENABLED
	#define RKH_TRC_NSEQ()				\
				RKH_TRC_UI8( nseq );	\
				++nseq
#else
	#define RKH_TRC_NSEQ()
#endif


/**
 * 	\brief
 *	Insert the trace event header in the stream.
 */

#define RKH_TRC_HDR( eid ) 			\
			chk = 0;				\
			RKH_TRC_UI8( eid );		\
			RKH_TRC_NSEQ();			\
			RKH_TRC_TSTAMP()


/**
 * 	\brief
 * 	Insert a object address as trace record argument.
 */

#if RKH_TRC_SIZEOF_POINTER == 16
	#define RKH_TRC_SYM( sym )	\
				RKH_TRC_UI16( (rkhui16_t)sym )
#elif RKH_TRC_SIZEOF_POINTER == 32
	#define RKH_TRC_SYM( sym )	\
				RKH_TRC_UI32( (rkhui32_t)sym )
#else
	#define RKH_TRC_SYM( sym )	\
				RKH_TRC_UI32( (rkhui32_t)sym )
#endif


/**
 * 	\brief
 * 	Insert a sender object address as trace record argument.
 */

#if defined( RKH_USE_TRC_SENDER )
	#define RKH_TRC_SENDER( sym ) \
				RKH_TRC_SYM( sym )
#else
	#define RKH_TRC_SENDER( sym )
#endif


/**
 * 	\brief
 * 	Insert a function address as trace record argument.
 */

#if RKH_TRC_SIZEOF_FUN_POINTER == 16
	#define RKH_TRC_FUN( sym )	\
				RKH_TRC_UI16( (rkhui16_t)sym )
#elif RKH_TRC_SIZEOF_FUN_POINTER == 32
	#define RKH_TRC_FUN( sym )	\
				RKH_TRC_UI32( (rkhui32_t)sym )
#else
	#define RKH_TRC_FUN( sym )	\
				RKH_TRC_UI32( (rkhui32_t)sym )
#endif


/**
 * 	Insert a ntick value as trace record argument.
 */

#if RKH_TIM_SIZEOF_NTIMER == 8
	#define RKH_TRC_NTICK( nt )	\
				RKH_TRC_UI8( nt )
#elif RKH_TIM_SIZEOF_NTIMER == 16
	#define RKH_TRC_NTICK( nt )	\
				RKH_TRC_UI16( nt )
#elif RKH_TIM_SIZEOF_NTIMER == 32
	#define RKH_TRC_NTICK( nt )	\
				RKH_TRC_UI32( nt )
#else
	#define RKH_TRC_NTICK( nt )	\
				RKH_TRC_UI8( nt )
#endif


/**
 * 	Insert a nblock value as trace record argument.
 */

#if RKH_MP_SIZEOF_NBLOCK == 8
	#define RKH_TRC_NBLK( nb )	\
				RKH_TRC_UI8( nb )
	#if RKH_MP_EN_GET_LWM == RKH_DEF_ENABLED
		#define RKH_TRC_MP_NMIN( nm )	\
					RKH_TRC_UI8( nm )
	#else
		#define RKH_TRC_MP_NMIN( nm )
	#endif
#elif RKH_MP_SIZEOF_NBLOCK == 16
	#define RKH_TRC_NBLK( nb )	\
				RKH_TRC_UI16( nb )
	#if RKH_MP_EN_GET_LWM == RKH_DEF_ENABLED
		#define RKH_TRC_MP_NMIN( nm )	\
					RKH_TRC_UI16( nm )
	#else
		#define RKH_TRC_MP_NMIN( nm )
	#endif
#elif RKH_MP_SIZEOF_NBLOCK == 32
	#define RKH_TRC_NBLK( nb )	\
				RKH_TRC_UI32( nb )
	#if RKH_MP_EN_GET_LWM == RKH_DEF_ENABLED
		#define RKH_TRC_MP_NMIN( nm )	\
					RKH_TRC_UI32( nm )
	#else
		#define RKH_TRC_MP_NMIN( nm )
	#endif
#else
	#define RKH_TRC_NBLK( nb )	\
				RKH_TRC_UI8( nb )
	#if RKH_MP_EN_GET_LWM == RKH_DEF_ENABLED
		#define RKH_TRC_MP_NMIN( nm )	\
					RKH_TRC_UI8( nm )
	#else
		#define RKH_TRC_MP_NMIN( nm )
	#endif
#endif


/**
 * 	Insert the block size value as trace record argument.
 */

#if RKH_MP_SIZEOF_BSIZE == 8
	#define RKH_TRC_BSIZE( bs )	\
				RKH_TRC_UI8( bs )
#elif RKH_MP_SIZEOF_BSIZE == 16
	#define RKH_TRC_BSIZE( bs )	\
				RKH_TRC_UI16( bs )
#elif RKH_MP_SIZEOF_BSIZE == 32
	#define RKH_TRC_BSIZE( bs )	\
				RKH_TRC_UI32( bs )
#else
	#define RKH_TRC_BSIZE( bs )	\
				RKH_TRC_UI8( bs )
#endif


/**
 * 	Insert a nelem value as trace record argument.
 */

#if RKH_RQ_SIZEOF_NELEM == 8
	#define RKH_TRC_NE( ne )	\
				RKH_TRC_UI8( ne )
	#if RKH_RQ_EN_GET_LWMARK == RKH_DEF_ENABLED
		#define RKH_TRC_RQ_NMIN( nm )	\
						RKH_TRC_UI8( nm )
	#else
		#define RKH_TRC_RQ_NMIN( nm )
	#endif
#elif RKH_RQ_SIZEOF_NELEM == 16
	#define RKH_TRC_NE( ne )	\
				RKH_TRC_UI16( ne )
	#if RKH_RQ_EN_GET_LWMARK == RKH_DEF_ENABLED
		#define RKH_TRC_RQ_NMIN( nm )	\
						RKH_TRC_UI16( nm )
	#else
		#define RKH_TRC_RQ_NMIN( nm )
	#endif
#elif RKH_RQ_SIZEOF_NELEM == 32
	#define RKH_TRC_NE( ne )	\
				RKH_TRC_UI32( ne )
	#if RKH_RQ_EN_GET_LWMARK == RKH_DEF_ENABLED
		#define RKH_TRC_RQ_NMIN( nm )	\
						RKH_TRC_UI32( nm )
	#else
		#define RKH_TRC_RQ_NMIN( nm )
	#endif
#else
	#define RKH_TRC_NE( ne )	\
				RKH_TRC_UI8( ne )
	#if RKH_RQ_EN_GET_LWMARK == RKH_DEF_ENABLED
		#define RKH_TRC_RQ_NMIN( nm )	\
						RKH_TRC_UI8( nm )
	#else
		#define RKH_TRC_RQ_NMIN( nm )
	#endif
#endif


/**
 * 	Insert a signal number as trace record argument.
 */

#if RKH_SIZEOF_EVENT == 8
	#define RKH_TRC_SIG( e )	\
				RKH_TRC_UI8( e )
#elif RKH_SIZEOF_EVENT == 16
	#define RKH_TRC_SIG( e )	\
				RKH_TRC_UI16( e )
#elif RKH_SIZEOF_EVENT == 32
	#define RKH_TRC_SIG( e )	\
				RKH_TRC_UI32( e )
#else
	#define RKH_TRC_SIG( e )	\
				RKH_TRC_UI8( e )
#endif


/**
 * 	Insert a event size value as trace record argument.
 */

#if RKH_SIZEOF_ESIZE == 8
	#define RKH_TRC_ES( es )	\
				RKH_TRC_UI8( es )
#elif RKH_SIZEOF_ESIZE == 16
	#define RKH_TRC_ES( es )	\
				RKH_TRC_UI16( es )
#elif RKH_SIZEOF_ESIZE == 32
	#define RKH_TRC_ES( es )	\
				RKH_TRC_UI32( es )
#else
	#define RKH_TRC_ES( es )	\
				RKH_TRC_UI8( es )
#endif


/**
 * 	Used to invalidate the SMA filter in the RKH_TRC_BEGIN() macro.
 */

#define AOINV		RKH_MAX_SMA	
#define SIGINV		RKH_DEF_DISABLE		


#if RKH_TRC_EN == RKH_DEF_ENABLED
	/* --- Memory Pool (MP) ------------------ */
	#if RKH_TRC_ALL == RKH_DEF_ENABLED || RKH_TRC_EN_MP == RKH_DEF_ENABLED

		/**
		 * 	\brief
		 * 	\copybrief rkh_mp_init
		 *
		 * 	Desc	= initialize a memory block pool\n
		 * 	Group 	= RKH_TG_MP\n
		 * 	Id 		= RKH_TE_MP_INIT\n
		 * 	Args	= memory pool, nblock, block size\n
		 */

		#define RKH_TR_MP_INIT( mp, nb, bs )							\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_MP_INIT  )			\
						RKH_TRC_SYM( mp ); 								\
						RKH_TRC_NBLK( nb ); 							\
						RKH_TRC_BSIZE( bs );							\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_mp_get
		 *
		 * 	Desc 	= get a block from the pool\n
		 * 	Group 	= RKH_TG_MP\n
		 * 	Id 		= RKH_TE_MP_GET\n
		 * 	Args	= memory pool, nfree, nmin\n
		 */

		#define RKH_TR_MP_GET( mp, nfree, nmin )						\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_MP_GET )				\
						RKH_TRC_SYM( mp ); 								\
						RKH_TRC_NBLK( nfree ); 							\
				/*NEW*/ RKH_TRC_MP_NMIN( nmin );						\
					RKH_TRC_END()
	
		/**
		 * 	\brief
		 * 	\copybrief rkh_mp_put
		 *
		 * 	Desc 	= put the block to the pool\n
		 * 	Group 	= RKH_TG_MP\n
		 * 	id 		= RKH_TE_MP_PUT\n
		 * 	Args	= memory pool, nfree\n
		 */

		#define RKH_TR_MP_PUT( mp, nfree )								\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_MP_PUT )				\
						RKH_TRC_SYM( mp ); 								\
						RKH_TRC_NBLK( nfree ); 							\
					RKH_TRC_END()
	#else
		#define RKH_TR_MP_INIT( mp, nb, bs )				(void)0
		#define RKH_TR_MP_GET( mp, nfree, nmin )			(void)0
		#define RKH_TR_MP_PUT( mp, nfree )					(void)0
	#endif

	/* --- Queue (RQ) ------------------------ */
	#if RKH_TRC_ALL == RKH_DEF_ENABLED || RKH_TRC_EN_RQ == RKH_DEF_ENABLED

		/**
		 * 	\brief
		 *	\copybrief rkh_rq_init
		 *
		 * 	Desc 	= initialize a queue\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_INIT\n
		 * 	Args	= queue, ao, nelem\n
		 */

		#define RKH_TR_RQ_INIT( q, ao, nelem )							\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_RQ_INIT )				\
						RKH_TRC_SYM( q ); 								\
						RKH_TRC_SYM( ao ); 								\
						RKH_TRC_NE( nelem ); 							\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_rq_get
		 *
		 * 	Desc 	= get a element from the queue\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_GET\n
		 * 	Args	= queue, nelem\n
		 */

		#define RKH_TR_RQ_GET( q, nelem )								\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_RQ_GET )				\
						RKH_TRC_SYM( q ); 								\
						RKH_TRC_NE( nelem );							\
					RKH_TRC_END()
	
		/**
		 * 	\brief
		 * 	\copybrief rkh_rq_put_fifo
		 *
		 * 	Desc 	= put a element to the queue in a FIFO manner\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_FIFO\n
		 * 	Args	= queue, nelem, nmin\n
		 */

		#define RKH_TR_RQ_FIFO( q, nelem, nmin )						\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_RQ_FIFO )				\
						RKH_TRC_SYM( q ); 								\
						RKH_TRC_NE( nelem ); 							\
						RKH_TRC_RQ_NMIN( nmin );						\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_rq_put_lifo
		 *
		 * 	Desc 	= put a element to the queue in a LIFO manner\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_LIFO\n
		 * 	Args	= queue, nelem, nmin\n
		 */

		#define RKH_TR_RQ_LIFO( q, nelem, nmin )						\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_RQ_LIFO )				\
						RKH_TRC_SYM( q ); 								\
						RKH_TRC_NE( nelem ); 							\
						RKH_TRC_RQ_NMIN( nmin );						\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	Queue is full.
		 *
		 * 	Desc 	= query the queue\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_FULL\n
		 * 	Args	= queue\n
		 */

		#define RKH_TR_RQ_FULL( q )										\
					RKH_TRC_BEGIN_WOAOSIG_NOCRIT( RKH_TE_RQ_FULL )		\
						RKH_TRC_SYM( q ); 								\
					RKH_TRC_END_NOCRIT()

		/**
		 * 	\brief
		 * 	\copybrief rkh_rq_deplete
		 *
		 * 	Desc 	= deplete the queue\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_DPT\n
		 * 	Args	= queue\n
		 */

		#define RKH_TR_RQ_DPT( q )										\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_RQ_DPT )				\
						RKH_TRC_SYM( q ); 								\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	Get the last element from the queue
		 *
		 * 	Desc 	= get the last element from the queue\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_GET_LAST\n
		 * 	Args	= queue\n
		 */

		#define RKH_TR_RQ_GET_LAST( q )									\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_RQ_GET_LAST )			\
						RKH_TRC_SYM( q ); 								\
					RKH_TRC_END()
	#else
		#define RKH_TR_RQ_INIT( q, ao, nelem )				(void)0
		#define RKH_TR_RQ_GET( q, nelem )					(void)0
		#define RKH_TR_RQ_FIFO( q, nelem, nmin )			(void)0
		#define RKH_TR_RQ_LIFO( q, nelem, nmin )			(void)0
		#define RKH_TR_RQ_FULL( q )							(void)0
		#define RKH_TR_RQ_DPT( q )							(void)0
		#define RKH_TR_RQ_GET_LAST( q )						(void)0
	#endif

	/* --- State Machine Application (SMA) --- */
	#if RKH_TRC_ALL == RKH_DEF_ENABLED || RKH_TRC_EN_SMA == RKH_DEF_ENABLED

		/**
		 * 	\brief
		 * 	\copybrief rkh_sma_activate
		 *
		 * 	Desc 	= activate a SMA\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_ACT\n
		 * 	Args	= ao, active object priority\n
		 */

		#define RKH_TR_SMA_ACT( ao, p )									\
					RKH_TRC_BEGIN_WOSIG(	RKH_TE_SMA_ACT, 			\
											(ao)->romrkh->prio )		\
						RKH_TRC_SYM( ao ); 								\
						RKH_TRC_UI8( p );								\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_sma_terminate
		 *
		 * 	Desc 	= terminate a SMA\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_ACT\n
		 * 	Args	= ao, active object priority\n
		 */

		#define RKH_TR_SMA_TERM( ao, p )								\
					RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SMA_TERM, 			\
											(ao)->romrkh->prio )		\
						RKH_TRC_SYM( ao ); 								\
						RKH_TRC_UI8( p );								\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	Get an event from the active object's queue.
		 *
		 * 	Desc 	= get a event from the SMA's queue\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_ACT\n
		 * 	Args	= ao, signal, pool id, reference count\n
		 */

		#define RKH_TR_SMA_GET( ao, ev, pid, rc )						\
					RKH_TRC_BEGIN( 	RKH_TE_SMA_GET, 					\
									(ao)->romrkh->prio,					\
									ev->e )								\
						RKH_TRC_SYM( ao ); 								\
						RKH_TRC_SIG( ev->e ); 							\
						RKH_TRC_UI8( pid );								\
						RKH_TRC_UI8( rc );								\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_sma_post_fifo
		 *
		 * 	Desc 	= send a event to SMA's queue in a FIFO manner\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_FIFO\n
		 * 	Args	= ao, signal, sender, pool id, reference count\n
		 */

		#define RKH_TR_SMA_FIFO( ao, ev, snr, pid, rc )					\
					RKH_TRC_BEGIN( 	RKH_TE_SMA_FIFO, 					\
									(ao)->romrkh->prio,					\
									ev->e )								\
						RKH_TRC_SYM( ao ); 								\
						RKH_TRC_SIG( ev->e ); 							\
						RKH_TRC_SENDER( snr ); 							\
						RKH_TRC_UI8( pid );								\
						RKH_TRC_UI8( rc );								\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_sma_post_lifo
		 *
		 * 	Desc 	= send a event to SMA's queue in a LIFO manner\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_LIFO\n
		 * 	Args	= ao, signal, sender, pool id, reference count\n
		 */

		#define RKH_TR_SMA_LIFO( ao, ev, snr, pid, rc )					\
					RKH_TRC_BEGIN(	 RKH_TE_SMA_LIFO, 					\
									(ao)->romrkh->prio,					\
									ev->e )								\
						RKH_TRC_SYM( ao ); 								\
						RKH_TRC_SIG( ev->e ); 							\
						RKH_TRC_SENDER( snr ); 							\
						RKH_TRC_UI8( pid );								\
						RKH_TRC_UI8( rc );								\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_sma_register
		 *
		 * 	Desc 	= register a SMA\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_REG\n
		 * 	Args	= ao, active object priority\n
		 */

		#define RKH_TR_SMA_REG( ao, prio )								\
					RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SMA_REG, 			\
											(ao)->romrkh->prio )		\
						RKH_TRC_SYM( ao ); 								\
						RKH_TRC_UI8( prio ); 							\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_sma_unregister
		 *
		 * 	Desc 	= unregister a SMA\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_UNREG\n
		 * 	Args	= ao, active object priority\n
		 */

		#define RKH_TR_SMA_UNREG( ao, prio )							\
					RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SMA_UNREG, 			\
											(ao)->romrkh->prio )		\
						RKH_TRC_SYM( ao ); 								\
						RKH_TRC_UI8( prio ); 							\
					RKH_TRC_END()
	#else
		#define RKH_TR_SMA_ACT( ao, p )						(void)0
		#define RKH_TR_SMA_TERM( ao, p )					(void)0
		#define RKH_TR_SMA_GET( ao, ev, pid, rc )			(void)0
		#define RKH_TR_SMA_FIFO( ao, ev, snr, pid, rc )		(void)0
		#define RKH_TR_SMA_LIFO( ao, ev, snr, pid, rc )		(void)0
		#define RKH_TR_SMA_REG( ao, prio )					(void)0
		#define RKH_TR_SMA_UNREG( ao, prio )				(void)0
	#endif

	/* --- State machine (SM) ---------------- */
	#if RKH_TRC_ALL == RKH_DEF_ENABLED || RKH_TRC_EN_SM == RKH_DEF_ENABLED

		/**
		 * 	\brief
		 * 	\copybrief rkh_init_hsm
		 *
		 * 	Desc 	= start (initialize) a state machine\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_INIT\n
		 * 	Args	= ao, initial state\n
		 */

		#if RKH_TRC_EN_SM_INIT == RKH_DEF_ENABLED
			#define RKH_TR_SM_INIT( ao, ist )							\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_INIT, 		\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
							RKH_TRC_SYM( ist ); 						\
						RKH_TRC_END()
		#else
			#define RKH_TR_SM_INIT( ao, ist )				(void)0
		#endif

		/**
		 * 	\brief
		 *	\copybrief rkh_clear_history
		 *
		 * 	Desc 	= clear history pseudostate\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_CLRH\n
		 * 	Args	= ao, history pseudostate\n
		 */

		#if RKH_TRC_EN_SM_CLRH == RKH_DEF_ENABLED
			#define RKH_TR_SM_CLRH( ao, h )								\
						RKH_TRC_BEGIN_WOSIG(	RKH_TE_SM_CLRH, 		\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
							RKH_TRC_SYM( h ); 							\
						RKH_TRC_END()
		#else
			#define RKH_TR_SM_CLRH( ao, h )				(void)0
		#endif

		/**
		 * 	\brief
		 * 	\copybrief rkh_dispatch
		 *
		 * 	Desc 	= dispatch an event to a state machine\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_DCH\n
		 * 	Args	= ao, signal\n
		 */

		#if RKH_TRC_EN_SM_DCH == RKH_DEF_ENABLED
			#define RKH_TR_SM_DCH( ao, ev )								\
						RKH_TRC_BEGIN( 	RKH_TE_SM_DCH, 					\
										(ao)->romrkh->prio,				\
										ev->e )							\
							RKH_TRC_SYM( ao ); 							\
							RKH_TRC_SIG( ev->e ); 						\
						RKH_TRC_END()
		#else
			#define RKH_TR_SM_DCH( ao, ev )				(void)0
		#endif

		/**
		 * 	\brief
		 *	Source and target state of the transition. The target could be 
		 *	either basic state, composite state or pseudostate.
		 *
		 * 	Desc 	= source and target state of transition\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_TRN\n
		 * 	Args	= ao, source state, target state\n
		 */

		#if RKH_TRC_EN_SM_TRN == RKH_DEF_ENABLED
			#define RKH_TR_SM_TRN( ao, sst, tst )						\
						RKH_TRC_BEGIN_WOSIG(	RKH_TE_SM_TRN, 			\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
							RKH_TRC_SYM( sst ); 						\
							RKH_TRC_SYM( tst ); 						\
						RKH_TRC_END()
		#else
			#define RKH_TR_SM_TRN( ao, sst, tst )			(void)0
		#endif

		/**
		 * 	\brief
		 *	Legal, stable and final state of the transition.
		 *
		 * 	Desc 	= final state of transition\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_STATE\n
		 * 	Args	= ao, final state\n
		 */

		#if RKH_TRC_EN_SM_STATE == RKH_DEF_ENABLED
			#define RKH_TR_SM_STATE( ao, st )							\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_STATE, 		\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
							RKH_TRC_SYM( st ); 							\
						RKH_TRC_END()
		#else
			#define RKH_TR_SM_STATE( ao, st )				(void)0
		#endif

		/**
		 * 	\brief
		 * 	Entered state.
		 *
		 * 	Desc 	= entered state\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_ENSTATE\n
		 * 	Args	= ao, entry state\n
		 */

		#if RKH_TRC_EN_SM_ENSTATE == RKH_DEF_ENABLED
			#define RKH_TR_SM_ENSTATE( ao, st )							\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_ENSTATE, 		\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
							RKH_TRC_SYM( st ); 							\
						RKH_TRC_END()
		#else
			#define RKH_TR_SM_ENSTATE( ao, st )			(void)0
		#endif

		/**
		 * 	\brief
		 * 	Exited state.
		 *
		 * 	Desc 	= exited state\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_EXSTATE\n
		 * 	Args	= ao, exit state\n
		 */

		#if RKH_TRC_EN_SM_EXSTATE == RKH_DEF_ENABLED
			#define RKH_TR_SM_EXSTATE( ao, st )							\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_EXSTATE, 		\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
							RKH_TRC_SYM( st ); 							\
						RKH_TRC_END()
		#else
			#define RKH_TR_SM_EXSTATE( ao, st )			(void)0	
		#endif

		/**
		 * 	\brief
		 *	Number of entry and exit states in transition.
		 *
		 * 	Desc 	= number of entry and exit states in transition\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_NENEX\n
		 * 	Args	= ao, nen, nex\n
		 */

		#if RKH_TRC_EN_SM_NENEX == RKH_DEF_ENABLED
			#define RKH_TR_SM_NENEX( ao, nen, nex )						\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_NENEX, 		\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
							RKH_TRC_UI8( nen ); 						\
							RKH_TRC_UI8( nex ); 						\
						RKH_TRC_END()
		#else
			#define RKH_TR_SM_NENEX( ao, nen, nex )		(void)0	
		#endif

		/**
		 * 	\brief
		 *	Number of executed actions and segments of the transition.
		 *
		 * 	Desc 	= number of executed actions in transition\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_NTRNACT\n
		 * 	Args	= ao, nta, nts\n
		 */

		#if RKH_TRC_EN_SM_NTRNACT == RKH_DEF_ENABLED
			#define RKH_TR_SM_NTRNACT( ao, nta, nts )					\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_NTRNACT, 		\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
							RKH_TRC_UI8( nta ); 						\
							RKH_TRC_UI8( nts ); 						\
						RKH_TRC_END()
		#else
			#define RKH_TR_SM_NTRNACT( ao, nta, nts )		(void)0	
		#endif

		/**
		 * 	\brief
		 *	Destination state or pseudostate of a transition segment.
		 *
		 * 	Desc 	= next state or pseudostate in a compound transition\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_TS_STATE\n
		 * 	Args	= ao, state/pseudostate\n
		 */

		#if RKH_TRC_EN_SM_TS_STATE == RKH_DEF_ENABLED
			#define RKH_TR_SM_TS_STATE( ao, st )						\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_TS_STATE, 	\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
							RKH_TRC_SYM( st ); 							\
						RKH_TRC_END()
		#else
			#define RKH_TR_SM_TS_STATE( ao, st )				(void)0	
		#endif

		#if RKH_TRC_EN_SM_PROCESS == RKH_DEF_ENABLED

		/**
		 * 	\brief
		 *	The arrived event was succesfully processed and HSM resides in an 
		 *	allowed state
		 *
		 * 	Desc 	= the arrived event was succesfully processed and HSM 
		 * 			  resides in an allowed state.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_EVT_PROC\n
		 * 	Args	= ao\n
		 */

			#define RKH_TR_SM_EVT_PROC( ao )							\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_EVT_PROC, 	\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
						RKH_TRC_END()

		/**
		 * 	\brief
		 *	The arrived event was't founded in the transition table.
		 *
		 * 	Desc 	= the arrived event was't founded in the transition 
		 * 			  table.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_EVT_NFOUND\n
		 * 	Args	= ao\n
		 */

			#define RKH_TR_SM_EVT_NFOUND( ao )							\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_EVT_NFOUND,	\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
						RKH_TRC_END()

		/**
		 * 	\brief
		 *	The transition was cancelled by guard function.
		 *
		 * 	Desc 	= The transition was cancelled by guard function.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_GRD_FALSE\n
		 * 	Args	= ao\n
		 */

			#define RKH_TR_SM_GRD_FALSE( ao )							\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_GRD_FALSE,	\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
						RKH_TRC_END()

		/**
		 * 	\brief
		 *	The branch function returned a value not founded in the branch 
		 *	table.
		 *
		 * 	Desc 	= the branch function returned a value not founded 
		 * 			  in the branch table.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_CND_NFOUND\n
		 * 	Args	= ao\n
		 */

			#define RKH_TR_SM_CND_NFOUND( ao )							\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_CND_NFOUND,	\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
						RKH_TRC_END()

		/**
		 * 	\brief
		 *	Unknown state.
		 *
		 * 	Desc 	= unknown state.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_UNKN_STATE\n
		 * 	Args	= ao\n
		 */

			#define RKH_TR_SM_UNKN_STATE( ao )							\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_UNKN_STATE,	\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
						RKH_TRC_END()

		/**
		 * 	\brief
		 *	The transition exceeded the allowed hierarchical level.
		 *
		 * 	Desc 	= the transition exceeded the allowed hierarchical 
		 * 			  level.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_EX_HLEVEL\n
		 * 	Args	= ao\n
		 */
			#define RKH_TR_SM_EX_HLEVEL( ao )							\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_EX_HLEVEL,	\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
						RKH_TRC_END()

		/**
		 * 	\brief
		 *	The transition exceeded the allowed number of segments within a 
		 *	compound transtion.
		 *
		 * 	Desc 	= the transition exceeded the allowed number of 
		 * 			  segments within a compound transtion.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_EX_TSEG\n
		 * 	Args	= ao\n
		 */
			#define RKH_TR_SM_EX_TSEG( ao )								\
						RKH_TRC_BEGIN_WOSIG( 	RKH_TE_SM_EX_TSEG,		\
												(ao)->romrkh->prio )	\
							RKH_TRC_SYM( ao ); 							\
						RKH_TRC_END()
		#else
			#define RKH_TR_SM_EVT_PROC( ao )				(void)0
			#define RKH_TR_SM_EVT_NFOUND( ao )				(void)0
			#define RKH_TR_SM_CND_NFOUND( ao )				(void)0
			#define RKH_TR_SM_GRD_FALSE( ao )				(void)0
			#define RKH_TR_SM_UNKN_STATE( ao )				(void)0
			#define RKH_TR_SM_EX_HLEVEL( ao )				(void)0
			#define RKH_TR_SM_EX_TSEG( ao )					(void)0
		#endif
	#else
		#define RKH_TR_SM_INIT( ao, ist )				(void)0
		#define RKH_TR_SM_CLRH( ao, h )					(void)0
		#define RKH_TR_SM_DCH( ao, ev )					(void)0
		#define RKH_TR_SM_TRN( ao, sst, tst )			(void)0
		#define RKH_TR_SM_STATE( ao, st )				(void)0
		#define RKH_TR_SM_ENSTATE( ao, st )				(void)0
		#define RKH_TR_SM_EXSTATE( ao, st )				(void)0
		#define RKH_TR_SM_NENEX( ao, nen, nex )			(void)0
		#define RKH_TR_SM_NTRNACT( ao, nta, nts )		(void)0
		#define RKH_TR_SM_TS_STATE( aaost )				(void)0
		#define RKH_TR_SM_EVT_PROC( ao )				(void)0
		#define RKH_TR_SM_EVT_NFOUND( ao )				(void)0
		#define RKH_TR_SM_GRD_FALSE( ao )				(void)0
		#define RKH_TR_SM_CND_NFOUND( ao )				(void)0
		#define RKH_TR_SM_UNKN_STATE( ao )				(void)0
		#define RKH_TR_SM_EX_HLEVEL( ao )				(void)0
		#define RKH_TR_SM_EX_TSEG( ao )					(void)0
	#endif

	/* --- Timer (TIM) ----------------------- */
	#if RKH_TRC_ALL == RKH_DEF_ENABLED || RKH_TRC_EN_TIM == RKH_DEF_ENABLED

		/**
		 * 	\brief
		 * 	\copybrief rkh_tim_init
		 *
		 * 	Desc 	= initialize a timer\n
		 * 	Group 	= RKH_TG_TIM\n
		 * 	Id 		= RKH_TE_TIM_INIT\n
		 * 	Args	= timer, signal\n
		 */

		#define RKH_TR_TIM_INIT( t, sig )								\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_TIM_INIT )			\
						RKH_TRC_SYM( t ); 								\
						RKH_TRC_SIG( sig ); 							\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_tim_start
		 *
		 * 	Desc 	= start a timer\n
		 * 	Group 	= RKH_TG_TIM\n
		 * 	Id 		= RKH_TE_TIM_START\n
		 * 	Args	= timer, ao, nticks, period\n
		 */

		#define RKH_TR_TIM_START( t, ao, nt, per )						\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_TIM_START )			\
						RKH_TRC_SYM( t ); 								\
						RKH_TRC_SYM( ao ); 								\
						RKH_TRC_NTICK( nt ); 							\
						RKH_TRC_NTICK( per );							\
					RKH_TRC_END()
	
		/**
		 * 	\brief
		 * 	\copybrief rkh_tim_stop
		 *
		 * 	Desc 	= stop a timer\n
		 * 	Group 	= RKH_TG_TIM\n
		 * 	Id 		= RKH_TE_TIM_STOP\n
		 * 	Args	= timer, ntick, period\n
		 */

		#define RKH_TR_TIM_STOP( t, nt, per )							\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_TIM_STOP )			\
						RKH_TRC_SYM( t ); 								\
				/*NEW*/ RKH_TRC_NTICK( nt );							\
				/*NEW*/ RKH_TRC_NTICK( per );							\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	Timer expired.
		 *
		 * 	Desc 	= timer expired\n
		 * 	Group 	= RKH_TG_TIM\n
		 * 	Id 		= RKH_TE_TIM_TOUT\n
		 * 	Args	= timer, signal, active object\n
		 */

		#define RKH_TR_TIM_TOUT( t, sig, ao )							\
					RKH_TRC_BEGIN( 	RKH_TE_TIM_TOUT, 					\
									(ao)->romrkh->prio,					\
									sig )								\
						RKH_TRC_SYM( t ); 								\
				/*NEW*/ RKH_TRC_SIG( sig );								\
				/*NEW*/ RKH_TRC_SYM( ao );								\
					RKH_TRC_END()

		/**
		 * 	\brief
		 *	Removes timer from the active timer list.
		 *
		 * 	Desc 	= remove timer from the active timer list\n
		 * 	Group 	= RKH_TG_TIM\n
		 * 	Id 		= RKH_TE_TIM_REM\n
		 * 	Args	= timer\n
		 */

		#define RKH_TR_TIM_REM( t )										\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_TIM_REM )				\
						RKH_TRC_SYM( t ); 								\
					RKH_TRC_END()
	#else
		#define RKH_TR_TIM_INIT( t, sig )					(void)0
		#define RKH_TR_TIM_START( t, ao, nt, per )			(void)0
		#define RKH_TR_TIM_STOP( t, nt, per )				(void)0
		#define RKH_TR_TIM_TOUT( t, sig, ao )				(void)0
		#define RKH_TR_TIM_REM( t )							(void)0
	#endif

	/* --- Framework (RKH) ----------------------- */
	#if RKH_TRC_ALL == RKH_DEF_ENABLED || RKH_TRC_EN_FWK == RKH_DEF_ENABLED

		/**
		 * 	\brief
		 * 	\copybrief rkh_init
		 *
		 * 	Desc 	= initialize the RKH\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_EN\n
		 * 	Args	= \n
		 */

		#define RKH_TR_FWK_EN()										\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_FWK_EN )			\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_exit
		 *
		 * 	Desc 	= exit the RKH\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_EX\n
		 * 	Args	= \n
		 */

		#define RKH_TR_FWK_EX()											\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_FWK_EX )				\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_epool_register
		 *
		 * 	Desc 	= event pool register\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_EPREG\n
		 * 	Args	= event pool index, storage size, event size\n
		 */

		#define RKH_TR_FWK_EPREG( ep, ss, es )							\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_FWK_EPREG )			\
						RKH_TRC_UI8( ep );								\
						RKH_TRC_UI32( ss );								\
						RKH_TRC_ES( es );								\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_ae
		 *
		 * 	Desc 	= allocate an event\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_AE\n
		 * 	Args	= event size, signal, pool id, reference count\n
		 */

		#define RKH_TR_FWK_AE( es, ev, pid, rc )						\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_FWK_AE )				\
						RKH_TRC_ES( es );								\
						RKH_TRC_SIG( ev->e );							\
				/*NEW*/ RKH_TRC_UI8( pid );								\
				/*NEW*/ RKH_TRC_UI8( rc );								\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	Attempt to recycle an event.
		 *
		 * 	Desc 	= attempt to recycle an event\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_GC\n
		 * 	Args	= signal, pool id, reference count\n
		 */

		#define RKH_TR_FWK_GC( ev, pid, rc )							\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_FWK_GC )				\
						RKH_TRC_SIG( ev->e );							\
				/*NEW*/ RKH_TRC_UI8( pid );								\
				/*NEW*/ RKH_TRC_UI8( rc );								\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	Effective recycling event.
		 *
		 * 	Desc 	= effective recycling event\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_GCR\n
		 * 	Args	= signal, pool id, reference count\n
		 */

		#define RKH_TR_FWK_GCR( ev, pid, rc )							\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_FWK_GCR )				\
						RKH_TRC_SIG( ev->e );							\
				/*NEW*/ RKH_TRC_UI8( pid );								\
				/*NEW*/ RKH_TRC_UI8( rc );								\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_defer
		 *
		 * 	Desc 	= defer an event\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_DEFER\n
		 * 	Args	= event queue, signal\n
		 */

		#define RKH_TR_FWK_DEFER( q, ev )								\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_FWK_DEFER )			\
						RKH_TRC_SYM( q );								\
						RKH_TRC_SIG( ev->e );							\
					RKH_TRC_END()

		/**
		 * 	\brief
		 * 	\copybrief rkh_recall
		 *
		 * 	Desc 	= recall an event\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_RCALL\n
		 * 	Args	= ao, signal\n
		 */

		#define RKH_TR_FWK_RCALL( ao, ev )								\
					RKH_TRC_BEGIN_WOAOSIG( RKH_TE_FWK_RCALL )			\
						RKH_TRC_SYM( ao );								\
						RKH_TRC_SIG( ev->e );							\
					RKH_TRC_END()

		/* --- Symbol entry table for objects --------- */

		/**
		 * 	\brief
		 *	Entry symbol table for memory object.
		 *
		 * 	Desc 	= entry symbol table for memory object\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_OBJ\n
		 * 	Args	= object address, symbol\n
		 *
		 * 	e.g.\n
		 * 	Associates the address of the object, in memory 
		 * 	with its symbolic name.
		 *
		 * 	\code
		 * 	...
		 * 	static int g_status; 
		 * 	static RKHT_T tdll; 
		 *
		 * 	RKH_TR_FWK_OBJ( &g_status );
		 * 	RKH_TR_FWK_OBJ( &tdll );
		 * 	\endcode
		 */

		#define RKH_TR_FWK_OBJ( __o )									\
				do{ 													\
					static RKHROM char *const __o_n = #__o;				\
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_OBJ )				\
						RKH_TRC_SYM( __o );								\
						RKH_TRC_STR( __o_n );							\
					RKH_TRC_END_WOFIL()									\
					RKH_TRC_FLUSH();									\
				} while(0)

		/* --- Symbol entry table for objects with name --------- */

		/**
		 * 	\brief
		 *	Entry symbol table for memory object. Very similar to 
		 *	RKH_TR_FWK_OBJ() but the name of object must be explicitely 
		 *	defined.
		 *
		 *	\note
		 *	This macro uses the same trace event that RKH_TR_FWK_OBJ().
		 *
		 * 	Desc 	= entry symbol table for memory object\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_OBJ\n
		 * 	Args	= object address, name of object\n
		 *
		 * 	e.g.\n
		 * 	Associates the address of the object, in memory with a name.
		 *
		 * 	\code
		 * 	...
		 * 	RKH_TR_FWK_OBJ_NAME( &RKH_CAST(CLI_T, sma)->cli_utmr, "cli_utmr" );
		 * 	\endcode
		 */

		#define RKH_TR_FWK_OBJ_NAME( __o, __n )							\
				do{ 													\
					static RKHROM char *const __o_n = __n;				\
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_OBJ )				\
						RKH_TRC_SYM( __o );								\
						RKH_TRC_STR( __o_n );							\
					RKH_TRC_END_WOFIL()									\
					RKH_TRC_FLUSH();									\
				} while(0)

		/* --- Symbol entry table for event signals ---- */

		/**
		 * 	\brief
		 *	Entry symbol table for event signal.
		 *
		 * 	Desc 	= entry symbol table for signal\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_SIG\n
		 * 	Args	= signal number, symbol\n
		 *
		 * 	e.g.\n
		 * 	Associates the numerical value of the event signal to the 
		 * 	symbolic name of the signal.
		 *
		 * 	\code
		 * 	// in the dedicated application header file resides the signal 
		 * 	// enumeration
		 * 	
		 * 	enum
		 * 	{
		 * 		...
		 * 		PWR_FAIL,
		 * 		PRESS_ENTER,
		 * 		...
		 * 	};
		 *
		 * 	// frequently, the macro RKH_TR_FWK_SIG() is used in the 
		 * 	// \b main.c file.
		 *
		 * 	RKH_TR_FWK_SIG( PWR_FAIL );
		 * 	RKH_TR_FWK_SIG( PRESS_ENTER );
		 * 	\endcode
		 */

		#define RKH_TR_FWK_SIG( __s )									\
				do{ 													\
					static RKHROM char *const __s_n = #__s;				\
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_SIG )				\
						RKH_TRC_SIG( __s );								\
						RKH_TRC_STR( __s_n );							\
					RKH_TRC_END_WOFIL()									\
					RKH_TRC_FLUSH();									\
				} while(0)

		/* --- Symbol entry table for functions ---- */

		/**
		 * 	\brief
		 *	Entry symbol table for function object.
		 *
		 * 	Desc 	= entry symbol table for function\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_FUN\n
		 * 	Args	= function address, symbol\n
		 *
		 * 	e.g.\n
		 * 	Associates the address of the function in memory 
		 * 	with its symbolic name.
		 *
		 * 	\code
		 * 	// frequently, the macro RKH_TR_FWK_FUN() is used in the 
		 * 	// \b main.c file.
		 *
		 * 	RKH_TR_FWK_FUN( my_init );
		 * 	RKH_TR_FWK_FUN( set_x_1 );
		 * 	RKH_TR_FWK_FUN( set_x_2 );
		 * 	RKH_TR_FWK_FUN( set_x_3 );
		 * 	RKH_TR_FWK_FUN( set_y_0 );
		 * 	RKH_TR_FWK_FUN( dummy_exit );
		 * 	...
		 * 	\endcode
		 */

		#define RKH_TR_FWK_FUN( __f )									\
				do{ 													\
					static RKHROM char *const __f_n = #__f;				\
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_FUN )				\
						RKH_TRC_FUN( __f );								\
						RKH_TRC_STR( __f_n );							\
					RKH_TRC_END_WOFIL()									\
					RKH_TRC_FLUSH();									\
				} while(0)

		/**
		 * 	\brief
		 * 	The function was executed.
		 *
		 * 	Desc 	= the function was executed\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_FUN\n
		 * 	Args	= function address\n
		 *
		 * 	Example:
		 *
		 * 	\code
		 * 	void 
		 * 	my_init( const void *sma )
		 * 	{
		 * 		CMY( sma )->x = CMY( sma )->y = 0;
		 * 		RKH_TR_FWK_EXE_FUN( my_init );
		 * 	}
		 * 	\endcode
		 */

		#define RKH_TR_FWK_EXE_FUN( fn )								\
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_EXE_FUN )			\
						RKH_TRC_FUN( fn );								\
					RKH_TRC_END_WOFIL()

		/* --- Symbol entry table for user user-defined trace events --------- */

		/**
		 * 	\brief
		 *	Entry symbol table for user-defined trace events.
		 *
		 * 	Desc 	= entry symbol table for user-defined trace events\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_TUSR\n
		 * 	Args	= user trace event number\n
		 *
		 * 	e.g.\n
		 * 	Associates the numerical value of the user-defined trace event to 
		 * 	the symbolic name of that.
		 *
		 * 	\code
		 * 	...
		 * 	// frequently, the macro RKH_TR_FWK_TUSR() is used in the 
		 * 	// \b main.c file.
		 *
		 *	enum // define the user trace events
		 *	{
		 *		LOWPWR_USRT = RKH_TE_USER,
		 *		DISCONNECTED_USRT,
		 *		...
		 *	};
		 *
		 * 	void
		 * 	main( void )
		 * 	{
		 * 		RKH_TR_FWK_TUSR( LOWPWR_USRT );
		 * 		RKH_TR_FWK_TUSR( DISCONNECTED_USRT );
		 * 		...
		 * 	}
		 * 	\endcode
		 */

		#define RKH_TR_FWK_TUSR( __e )									\
				do{ 													\
					static RKHROM char *const __e_n = #__e;				\
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_TUSR )				\
						RKH_TRC_UI8( EXTE( __e, RKH_TG_USR ) );			\
						RKH_TRC_STR( __e_n );							\
					RKH_TRC_END_WOFIL()									\
					RKH_TRC_FLUSH();									\
				} while(0)

		/* --- Trace configuration --------- */

		/**
		 * 	\brief
		 *	Send trace configuration table to Trazer.
		 *
		 * 	Desc 	= send trace configuration table to Trazer\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_TCFG\n
		 * 	Args	= configuration parameters\n
		 *
		 * 	\code
		 * 	void 
		 * 	rkh_trc_config( void )
		 * 	{
		 * 		RKH_TR_FWK_TCFG();
		 * 	}
		 * 	\endcode
		 */

		#define RKH_TR_FWK_TCFG()  										\
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_TCFG )				\
						RKH_TRC_UI16( (rkhui16_t)RKH_VERSION_CODE );	\
						RKH_TRC_UI16( 									\
							(rkhui16_t)(								\
								(RKH_SMA_EN_TRC_SENDER		 ) |		\
								(RKH_TRC_RUNTIME_FILTER	<< 1 ) |		\
								(RKH_TRC_EN_USER_TRACE	<< 2 ) |		\
								(RKH_TRC_ALL			<< 3 ) |		\
								(RKH_TRC_EN_MP			<< 4 ) |		\
								(RKH_TRC_EN_RQ			<< 5 ) |		\
								(RKH_TRC_EN_SMA			<< 6 ) |		\
								(RKH_TRC_EN_TIM			<< 7 ) |		\
								(RKH_TRC_EN_SM			<< 8 ) |		\
								(RKH_TRC_EN_FWK			<< 9 ) |		\
								(RKH_TRC_EN_ASSERT		<< 10) |		\
						/*NEW*/	(RKH_RQ_EN_GET_LWMARK	<< 11) |		\
						/*NEW*/	(RKH_MP_EN_GET_LWM		<< 12)));		\
						RKH_TRC_UI8( 									\
							(rkhui8_t)((RKH_SIZEOF_EVENT/8 << 4) | 		\
							(rkhui8_t)RKH_TRC_SIZEOF_TSTAMP/8));		\
						RKH_TRC_UI8( 									\
							(rkhui8_t)((RKH_TRC_SIZEOF_POINTER/8 << 4) |\
							RKH_TIM_SIZEOF_NTIMER/8));					\
						RKH_TRC_UI8( 									\
							(rkhui8_t)((RKH_MP_SIZEOF_NBLOCK/8 << 4) | 	\
							RKH_RQ_SIZEOF_NELEM/8));					\
						RKH_TRC_UI8( 									\
							(rkhui8_t)((RKH_SIZEOF_ESIZE/8 << 4) |		\
							RKH_TRC_EN_NSEQ));							\
						RKH_TRC_UI8( 									\
							(rkhui8_t)((RKH_TRC_EN_CHK << 4) |			\
							RKH_TRC_EN_TSTAMP));						\
				/*NEW*/	RKH_TRC_UI8( 									\
							(rkhui8_t)((RKH_MP_SIZEOF_BSIZE/8 << 4) |	\
							RKH_MAX_EPOOL));							\
					RKH_TRC_END_WOFIL()									\
					RKH_TRC_FLUSH()

		/* --- Assertion --------- */

		/**
		 * 	\brief
		 *	Assertion expression was evaluated to false.
		 *
		 * 	Desc 	= assertion expression was evaluated to false.\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_ASSERT\n
		 * 	Args	= module name, and line number\n
		 */

		#if RKH_TRC_EN_ASSERT == RKH_DEF_ENABLED
			#define RKH_TR_FWK_ASSERT( mod_, ln_ )							\
						RKH_TRC_BEGIN_WOAOSIG_NOCRIT( RKH_TE_FWK_ASSERT )	\
							RKH_TRC_STR( (RKHROM char *)mod_ );				\
							RKH_TRC_UI16( (rkhui16_t)ln_ );					\
						RKH_TRC_END_NOCRIT()								\
						RKH_TRC_FLUSH()
		#else
			#define RKH_TR_FWK_ASSERT( mod_, ln_ )		(void)0
		#endif

		/* --- Symbol entry table for active objects --------- */

		/**
		 * 	\brief
		 *	Entry symbol table for active object.
		 *
		 * 	Desc 	= entry symbol table for active object\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_OBJ\n
		 * 	Args	= active object address, symbol\n
		 *
		 * 	e.g.\n
		 * 	Associates the address of the active object, in memory 
		 * 	with its symbolic name.
		 *
		 * 	\code
		 * 	...
		 * 	typedef struct
		 * 	{
		 * 		RKHSMA_T ao;
		 * 		rkhui8_t x;
		 * 		rkhui8_t y;
		 * 	} AO_T;
		 * 	
		 * 	RKH_SMA_CREATE( AO_T, 0, ao, 0, HCAL, &S1, ao_init, NULL );
		 * 	RKH_TR_FWK_OBJ( &ao );
		 * 	\endcode
		 */

		#define RKH_TR_FWK_AO( __ao )									\
				do{ 													\
					static RKHROM char *const __ao_n = #__ao;			\
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_AO )				\
						RKH_TRC_SYM( __ao );							\
						RKH_TRC_STR( __ao_n );							\
					RKH_TRC_END_WOFIL()									\
					RKH_TRC_FLUSH();									\
				} while(0)

		/* --- Symbol entry table for state objects --------- */

		/**
		 * 	\brief
		 *	Entry symbol table for state object.
		 *
		 * 	Desc 	= entry symbol table for state objects\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_OBJ\n
		 * 	Args	= state object address, symbol\n
		 *
		 * 	e.g.\n
		 * 	Associates the address of the state object, in memory 
		 * 	with its symbolic name.
		 *
		 * 	\code
		 * 	...
		 * 	RKH_CREATE_COMP_STATE( S1, 0, en, ex, RKH_ROOT, &S11, NULL );
		 * 	RKH_CREATE_TRANS_TABLE( S1 )
		 * 		RKH_TRINT( SIX, 	NULL, 		show_data ),
		 * 		RKH_TRREG( TWO, 	NULL, 		set_y_2,	&S2 ),
		 * 	RKH_END_TRANS_TABLE
		 * 	
		 * 	...
		 * 	RKH_TR_FWK_STATE( my, &S1 );
		 * 	\endcode
		 */

		#define RKH_TR_FWK_STATE( __ao, __so )							\
				do{ 													\
					static RKHROM char *const __so_n = #__so;			\
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_STATE )				\
						RKH_TRC_SYM( __ao );							\
						RKH_TRC_SYM( __so );							\
						RKH_TRC_STR( __so_n );							\
					RKH_TRC_END_WOFIL()									\
					RKH_TRC_FLUSH();									\
				} while(0)

		/* --- Symbol entry table for pseudostate objects --------- */

		/**
		 * 	\brief
		 *	Entry symbol table for pseudostate object.
		 *
		 * 	Desc 	= entry symbol table for pseudostate objects\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_OBJ\n
		 * 	Args	= pseudostate object address, symbol\n
		 *
		 * 	e.g.\n
		 * 	Associates the address of the pseudostate object, in memory 
		 * 	with its symbolic name.
		 *
		 * 	\code
		 * 	...
		 * 	RKH_CREATE_COND_STATE( C1, 12 );
		 * 	RKH_CREATE_BRANCH_TABLE( C1 )
		 * 		RKH_BRANCH( y_1, 	NULL, 			&H ),
		 * 		RKH_BRANCH( y_2, 	dummy_act, 		&DH ),
		 * 		RKH_BRANCH( y_0, 	NULL, 			&S1 ),
		 * 	RKH_END_BRANCH_TABLE
		 * 	
		 * 	...
		 * 	RKH_TR_FWK_PSTATE( my, &C1 );
		 * 	\endcode
		 */

		#define RKH_TR_FWK_PSTATE( __ao, __pso )						\
				do{ 													\
					static RKHROM char *const __pso_n = #__pso;			\
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_PSTATE )			\
						RKH_TRC_SYM( __ao );							\
						RKH_TRC_SYM( __pso );							\
						RKH_TRC_STR( __pso_n );							\
					RKH_TRC_END_WOFIL()									\
					RKH_TRC_FLUSH();									\
				} while(0)

		/* --- Symbol entry table for timer objects --------- */

		/**
		 * 	\brief
		 *	Entry symbol table for timer object.
		 *
		 * 	Desc 	= entry symbol table for timer objects\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_OBJ\n
		 * 	Args	= timer object address, symbol\n
		 *
		 * 	e.g.\n
		 * 	Associates the address of the timer object, in memory 
		 * 	with its symbolic name.
		 *
		 * 	\code
		 * 	...
		 * 	static RKHT_T bky_tmr;
		 *
		 * 	RKH_TR_FWK_TIMER( &bky_tmr );
		 * 	\endcode
		 */

		#define RKH_TR_FWK_TIMER( __to )								\
				do{ 													\
					static RKHROM char *const __to_n = #__to;			\
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_TIMER )				\
						RKH_TRC_SYM( __to );							\
						RKH_TRC_STR( __to_n );							\
					RKH_TRC_END_WOFIL()									\
					RKH_TRC_FLUSH();									\
				} while(0)

		/* --- Symbol entry table for event pool objects --------- */

		/**
		 * 	\brief
		 *	Entry symbol table for event pool object.
		 *
		 * 	Desc 	= entry symbol table for event pool objects\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_OBJ\n
		 * 	Args	= event pool object address, symbol\n
		 *
		 * 	e.g.\n
		 * 	Associates the address of the event pool object, in memory 
		 * 	with its symbolic name.
		 *
		 * 	\code
		 * 	...
		 * 	static rkhui8_t ep0_sto[ SIZEOF_EP0STO ],
		 * 					ep1_sto[ SIZEOF_EP1STO ];
		 *	
		 *	...
		 * 	RKH_TR_FWK_EPOOL( &ep0_sto );
		 * 	RKH_TR_FWK_EPOOL( &ep1_sto );
		 *
		 *	rkh_epool_register( ep0_sto, SIZEOF_EP0STO, SIZEOF_EP0_BLOCK  );
		 *	rkh_epool_register( ep1_sto, SIZEOF_EP1STO, SIZEOF_EP1_BLOCK  );
		 *	...
		 * 	\endcode
		 */

		#define RKH_TR_FWK_EPOOL( __epo )								\
				do{ 													\
					static RKHROM char *const __epo_n = #__epo;			\
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_EPOOL )				\
						RKH_TRC_SYM( __epo );							\
						RKH_TRC_STR( __to_n );							\
					RKH_TRC_END_WOFIL()									\
					RKH_TRC_FLUSH();									\
				} while(0)

		/* --- Symbol entry table for queue objects --------- */

		/**
		 * 	\brief
		 *	Entry symbol table for queue object.
		 *
		 * 	Desc 	= entry symbol table for queue objects\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_OBJ\n
		 * 	Args	= queue object address, symbol\n
		 *
		 * 	e.g.\n
		 * 	Associates the address of the queue object, in memory 
		 * 	with its symbolic name.
		 *
		 * 	\code
		 * 	...
		 * 	#define QSTO_SIZE			4
		 * 	static RKHEVT_T *qsto[ QSTO_SIZE ];
		 *
		 * 	...
		 * 	RKH_TR_FWK_QUEUE( &blinky->equeue );
		 * 	rkh_sma_activate( blinky, (const RKHEVT_T **)qsto, 
		 * 											QSTO_SIZE, CV(0), 0 );
		 *	...
		 * 	\endcode
		 */

		#define RKH_TR_FWK_QUEUE( __qo )								\
				do{ 													\
					static RKHROM char *const __qo_n = #__qo;			\
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_QUEUE )				\
						RKH_TRC_SYM( __qo );							\
						RKH_TRC_STR( __qo_n );							\
					RKH_TRC_END_WOFIL()									\
					RKH_TRC_FLUSH();									\
				} while(0)

	#else
		#define RKH_TR_FWK_EN()							(void)0
		#define RKH_TR_FWK_EX()							(void)0
		#define RKH_TR_FWK_EPREG( ep, ss, es )			(void)0
		#define RKH_TR_FWK_AE( es, ev, pid, rc )		(void)0
		#define RKH_TR_FWK_GC( ev, pid, rc )			(void)0
		#define RKH_TR_FWK_GCR( ev, pid, rc )			(void)0
		#define RKH_TR_FWK_DEFER( q, ev )				(void)0
		#define RKH_TR_FWK_RCALL( ao, ev )				(void)0
		#define RKH_TR_FWK_OBJ( __o )					(void)0
		#define RKH_TR_FWK_OBJ_NAME( __o, __n )			(void)0
		#define RKH_TR_FWK_SIG( __s )					(void)0
		#define RKH_TR_FWK_FUN( __s )					(void)0
		#define RKH_TR_FWK_EXE_FUN( __f )				(void)0
		#define RKH_TR_FWK_TUSR( __e )					(void)0
		#define RKH_TR_FWK_TCFG()						(void)0
		#define RKH_TR_FWK_ASSERT( mod_, ln_ )			(void)0
		#define RKH_TR_FWK_AO( __ao )					(void)0
		#define RKH_TR_FWK_STATE( __ao, __so )			(void)0
		#define RKH_TR_FWK_PSTATE( __ao, __pso )		(void)0
		#define RKH_TR_FWK_TIMER( __to )				(void)0
		#define RKH_TR_FWK_EPOOL( __epo )				(void)0
		#define RKH_TR_FWK_QUEUE( __qo )				(void)0
	#endif
#else
	/* --- Memory Pool (MP) ------------------ */
	#define RKH_TR_MP_INIT( mp, nb, bs )				(void)0
	#define RKH_TR_MP_GET( mp, nfree, nmin )			(void)0
	#define RKH_TR_MP_PUT( mp, nfree )					(void)0

	/* --- Queue (RQ) ------------------------ */
	#define RKH_TR_RQ_INIT( q, ao, nelem )				(void)0
	#define RKH_TR_RQ_GET( q, nelem )					(void)0
	#define RKH_TR_RQ_FIFO( q, nelem, nmin )			(void)0
	#define RKH_TR_RQ_LIFO( q, nelem, nmin )			(void)0
	#define RKH_TR_RQ_FULL( q )							(void)0
	#define RKH_TR_RQ_DPT( q )							(void)0
	#define RKH_TR_RQ_GET_LAST( q )						(void)0

	/* --- State Machine Application (SMA) --- */
	#define RKH_TR_SMA_ACT( ao, p )						(void)0
	#define RKH_TR_SMA_TERM( ao, p )					(void)0
	#define RKH_TR_SMA_GET( ao, ev, pid, rc )			(void)0
	#define RKH_TR_SMA_FIFO( ao, ev, snr, pid, rc )		(void)0
	#define RKH_TR_SMA_LIFO( ao, ev, snr, pid, rc )		(void)0
	#define RKH_TR_SMA_REG( ao, prio )					(void)0
	#define RKH_TR_SMA_UNREG( ao, prio )				(void)0

	/* --- State machine (SM) ---------------- */
	#define RKH_TR_SM_INIT( ao, ist )					(void)0
	#define RKH_TR_SM_CLRH( ao, h )						(void)0
	#define RKH_TR_SM_DCH( ao, ev )						(void)0
	#define RKH_TR_SM_TRN( ao, sst, tst )				(void)0
	#define RKH_TR_SM_STATE( ao, st )					(void)0
	#define RKH_TR_SM_ENSTATE( ao, st )					(void)0
	#define RKH_TR_SM_EXSTATE( ao, st )					(void)0
	#define RKH_TR_SM_NENEX( ao, nen, nex )				(void)0
	#define RKH_TR_SM_NTRNACT( ao, nta, nts )			(void)0
	#define RKH_TR_SM_TS_STATE( ao, st )				(void)0
	#define RKH_TR_SM_EVT_PROC( ao )					(void)0
	#define RKH_TR_SM_EVT_NFOUND( ao )					(void)0
	#define RKH_TR_SM_GRD_FALSE( ao )					(void)0
	#define RKH_TR_SM_CND_NFOUND( ao )					(void)0
	#define RKH_TR_SM_UNKN_STATE( ao )					(void)0
	#define RKH_TR_SM_EX_HLEVEL( ao )					(void)0
	#define RKH_TR_SM_EX_TSEG( ao )						(void)0

	/* --- Timer (TIM) ----------------------- */
	#define RKH_TR_TIM_INIT( t, sig )					(void)0
	#define RKH_TR_TIM_START( t, ao, nt, per )			(void)0
	#define RKH_TR_TIM_STOP( t, nt, per )				(void)0
	#define RKH_TR_TIM_TOUT( t, sig, ao )				(void)0
	#define RKH_TR_TIM_REM( t )							(void)0

	/* --- Framework (RKH) ----------------------- */
	#define RKH_TR_FWK_EN()								(void)0
	#define RKH_TR_FWK_EX()								(void)0
	#define RKH_TR_FWK_EPREG( ep, ss, es )				(void)0
	#define RKH_TR_FWK_AE( es, ev, pid, rc )			(void)0
	#define RKH_TR_FWK_GC( ev, pid, rc )				(void)0
	#define RKH_TR_FWK_GCR( ev, pid, rc )				(void)0
	#define RKH_TR_FWK_DEFER( q, ev )					(void)0
	#define RKH_TR_FWK_RCALL( ao, ev )					(void)0
	#define RKH_TR_FWK_OBJ( __o )						(void)0
	#define RKH_TR_FWK_OBJ_NAME( __o, __n )				(void)0
	#define RKH_TR_FWK_SIG( __s )						(void)0
	#define RKH_TR_FWK_FUN( __f )						(void)0
	#define RKH_TR_FWK_EXE_FUN( __f )					(void)0
	#define RKH_TR_FWK_TUSR( __e )						(void)0
	#define RKH_TR_FWK_TCFG()							(void)0
	#define RKH_TR_FWK_ASSERT( mod_, ln_ )				(void)0
	#define RKH_TR_FWK_AO( __ao )						(void)0
	#define RKH_TR_FWK_STATE( __ao, __so )				(void)0
	#define RKH_TR_FWK_PSTATE( __ao, __pso )			(void)0
	#define RKH_TR_FWK_TIMER( __to )					(void)0
	#define RKH_TR_FWK_EPOOL( __epo )					(void)0
	#define RKH_TR_FWK_QUEUE( __qo )					(void)0
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
 *	stream, using a variable event size. In this manner the recorder always 
 *	holds the most recent history.
 *	On the other hand, all data are stored in little-endian order (least 
 *	significant byte first). Also, they are stored into the trace stream 1 
 *	byte at a time, thus avoiding any potential data misalignment problems.
 *	
 *	\note
 *	The timestamp is optional, thus it could be eliminated from the trace 
 *	event in compile-time with RKH_TRC_EN_TSTAMP = 0.
 */

typedef rkhui8_t RKH_TE_T;


/**
 * 	\brief
 * 	Initializes the RKH's trace record service.
 *
 * 	\note
 *  rkh_trc_init() is NOT protected with a critical section.
 */

void rkh_trc_init( void );


/**
 * 	\brief
 * 	Send the trace facility configuration to host application software Trazer.
 *
 * 	Trazer is designed to work with all possible target CPU, which requires a 
 * 	wide range of configurability. For example, for any given target CPU, 
 * 	Trazer must "know" the size of object pointers, event size, timestamp 
 * 	size and so on. This configurations could be provided through 
 * 	"trazer.cfg" file in the host or invoking rkh_trc_config() function from 
 * 	the application-specific rkh_trc_open() function.
 *
 * 	\sa trtrazer
 */

void rkh_trc_config( void );


/**
 * 	\brief
 *	Retrieves a pointer to oldest stored byte in the trace stream. 
 *	Frequently, this function is used by the called trace analyzer.
 *
 * 	\note
 * 	The data is stored in a single ring buffer, called trace stream. In this 
 *	manner the recorder always holds the most recent history.
 *  rkh_trc_get() is NOT protected with a critical section.
 *
 * 	\returns
 * 	A pointer to the oldest stored byte if trace stream was not empty, 
 * 	otherwise NULL pointer.
 */

rkhui8_t *rkh_trc_get( void );


/**
 * 	\brief
 * 	Retrieves a pointer to a contiguous block of data from the trace stream.
 *
 * 	The function returns the pointer to the beginning of the block, and writes
 * 	the number of bytes in the block to the location pointed to by \a nget.
 * 	The argument \a nget is also used as input to provide the maximum size 
 * 	of the data block that the caller can accept.
 *	Frequently, this function is used by the called trace analyzer.
 *
 * 	\note
 * 	The data is stored in a single ring buffer, called trace stream. In this 
 *	manner the recorder always holds the most recent history.
 *  rkh_trc_get_block() is NOT protected with a critical section.
 *
 * 	\param nget		when this function is invoked \a nget is used as an input 
 * 					to provide the maximum size of the data block to be 
 * 					retrieved. Also, it is used as an output retrieving the 
 * 					size of block.
 *
 * 	\returns
 * 	The pointer to the beginning of the block, and writes the number of bytes 
 * 	in the block to the location pointed to by \a nget. If this number differs 
 * 	from the \a nget parameter, the end-of-stream was reached. If the trace 
 * 	stream is empty, the function returns NULL and the content pointed by 
 * 	\a nget is set to zero.
 */

rkhui8_t *rkh_trc_get_block( TRCQTY_T *nget );


/**
 * 	\brief
 * 	Put a data byte into the trace stream. 
 *
 * 	\param b		data to be written in the trace stream.
 *
 * 	\note
 * 	The data is stored in a single ring buffer, called trace stream. In this 
 *	manner the recorder always holds the most recent history.
 *  rkh_trc_put() is NOT protected with a critical section.
 */

void rkh_trc_put( rkhui8_t b );


#if RKH_TRC_EN == RKH_DEF_ENABLED && RKH_TRC_RUNTIME_FILTER == RKH_DEF_ENABLED
	/**
	 * 	\brief
	 * 	Suppress the enabled trace events from a specific group. 
	 * 	Use the RKH_TRC_ALL_GROUPS to disable all groups.
	 */

	#define RKH_FILTER_ON_GROUP( grp )				\
				rkh_trc_filter_group_( FILTER_ON, (grp), EUNCHANGE )

	/**
	 * 	\brief
	 * 	Emit the enabled trace events from a specific group. 
	 * 	Use the RKH_TRC_ALL_GROUPS to enable all groups.
	 */

	#define RKH_FILTER_OFF_GROUP( grp )				\
				rkh_trc_filter_group_( FILTER_OFF, (grp), EUNCHANGE )

	/**
	 * 	\brief
	 * 	Suppress (disable) one trace event.
	 * 	Use the RKH_TRC_ALL_EVENTS to disable all trace events.
	 */

	#define RKH_FILTER_ON_EVENT( evt )				\
				rkh_trc_filter_event_( FILTER_ON, (evt) )

	/**
	 * 	\brief
	 * 	Emit (enable) one trace event. 
	 * 	Use the RKH_TRC_ALL_EVENTS to enable all trace events.
	 *
	 * 	\note
	 *	The container group is enabled, reglardless of its previous status.
	 */

	#define RKH_FILTER_OFF_EVENT( evt )				\
				rkh_trc_filter_event_( FILTER_OFF, (evt) )

	/**
	 * 	\brief
	 * 	Suppress (disable) all events in a specific group. 
	 */

	#define RKH_FILTER_ON_GROUP_ALL_EVENTS( grp )			\
				rkh_trc_filter_group_( FILTER_ON, (grp), ECHANGE )

	/**
	 * 	\brief
	 * 	Emit (enable) all events in a specific group. 
	 *
	 * 	\note
	 *	The container group is enabled, reglardless of its previous status.
	 */

	#define RKH_FILTER_OFF_GROUP_ALL_EVENTS( grp )			\
				rkh_trc_filter_group_( FILTER_OFF, (grp), ECHANGE )

	#if RKH_TRC_RTFIL_SMA_EN == RKH_DEF_ENABLED

		/**
		 * 	\brief
		 * 	Suppress the enable trace events related to a specified active 
		 * 	object.
		 */

		#define RKH_FILTER_ON_SMA( sma ) \
					rkh_trc_simfil( &fsma, (sma)->romrkh->prio, FILTER_ON )

		/**
		 * 	\brief
		 * 	Suppress all enabled trace events related to specified active 
		 * 	object.
		 */

		#define RKH_FILTER_ON_ALL_SMA() \
					rkh_trc_simfil( &fsma, 0, RKH_TRC_SET_ALL(FILTER_ON) )
	
		/**
		 * 	\brief
		 * 	Emmit the enabled trace events related to a specified active 
		 * 	object.
		 */

		#define RKH_FILTER_OFF_SMA( sma ) \
					rkh_trc_simfil( &fsma, (sma)->romrkh->prio, FILTER_OFF )

		/**
		 * 	\brief
		 * 	Emmit all enabled trace events related to specified active object.
		 */

		#define RKH_FILTER_OFF_ALL_SMA() \
					rkh_trc_simfil( &fsma, 0, RKH_TRC_SET_ALL(FILTER_OFF) )

	#else
		#define RKH_FILTER_ON_SMA( sma )				(void)0
		#define RKH_FILTER_ON_ALL_SMA()					(void)0
		#define RKH_FILTER_OFF_SMA( sma )				(void)0
		#define RKH_FILTER_OFF_ALL_SMA()				(void)0
	#endif

	#if RKH_TRC_RTFIL_SIGNAL_EN == RKH_DEF_ENABLED

		/**
		 * 	\brief
		 * 	Suppress the enabled trace events related to a specified event 
		 * 	signal.
		 */

		#define RKH_FILTER_ON_SIGNAL( sig ) \
					rkh_trc_simfil( &fsig, (sig), FILTER_ON )

		/**
		 * 	\brief
		 * 	Suppress all enabled trace events related to specified event 
		 * 	signal.
		 */

		#define RKH_FILTER_ON_ALL_SIGNALS() \
					rkh_trc_simfil( &fsig, 0, RKH_TRC_SET_ALL(FILTER_ON) )

		/**
		 * 	\brief
		 * 	Emmit the enabled trace events related to a specified event 
		 * 	signal.
		 */

		#define RKH_FILTER_OFF_SIGNAL( sig ) \
					rkh_trc_simfil( &fsig, (sig), FILTER_OFF )

		/**
		 * 	\brief
		 * 	Emmit all enabled trace events related to specified event signal.
		 */

		#define RKH_FILTER_OFF_ALL_SIGNALS() \
					rkh_trc_simfil( &fsig, 0, RKH_TRC_SET_ALL(FILTER_OFF) )
	#else
		#define RKH_FILTER_ON_SIGNAL( sig )			(void)0
		#define RKH_FILTER_ON_ALL_SIGNALS()			(void)0
		#define RKH_FILTER_OFF_SIGNAL( sig )		(void)0
		#define RKH_FILTER_OFF_ALL_SIGNALS()		(void)0
	#endif

#else
	#define RKH_FILTER_ON_GROUP( grp ) 				(void)0
	#define RKH_FILTER_OFF_GROUP( grp )				(void)0
	#define RKH_FILTER_ON_EVENT( evt )				(void)0
	#define RKH_FILTER_OFF_EVENT( evt )				(void)0
	#define RKH_FILTER_ON_GROUP_ALL_EVENTS( grp )	(void)0
	#define RKH_FILTER_OFF_GROUP_ALL_EVENTS( grp )	(void)0
	#define RKH_FILTER_ON_SMA( sma )				(void)0
	#define RKH_FILTER_ON_ALL_SMA()					(void)0
	#define RKH_FILTER_OFF_SMA( sma )				(void)0
	#define RKH_FILTER_OFF_ALL_SMA()				(void)0
	#define RKH_FILTER_ON_SIGNAL( sig )				(void)0
	#define RKH_FILTER_ON_ALL_SIGNALS()				(void)0
	#define RKH_FILTER_OFF_SIGNAL( sig )			(void)0
	#define RKH_FILTER_OFF_ALL_SIGNALS()			(void)0
#endif


/**
 * 	\brief
 * 	Emit or suppress all trace events from a specific group. 
 *
 * 	The stream is initially created with an empty filter (that is, without 
 * 	filtering any event type). If this is not the required behavior, the 
 * 	application can build a set of event types, include the appropriate event 
 * 	types in it, and apply it as a filter to the stream. After that, the 
 * 	stream will reject any event whose type is in the filter set.
 *	
 *	Gathering many events generates a lot of data, which requires memory and 
 *	processor time. It also makes the task of interpreting the data more 
 *	difficult. Because the amount of data that the instrumented framework 
 *	generates can be overwhelming, the RKH supports several types of filters 
 *	that can use it to reduce the amount of data to be processed. The available 
 *	groups are enumerated in #RKH_TRC_GROUPS.
 *
 * 	Example:
 * 	
 * 	\code
 * 	void 
 * 	some_function( ... )
 * 	{
 * 		RKH_FILTER_ON_GROUP( RKH_TRC_ALL_GROUPS );
 * 		RKH_FILTER_ON_EVENT( RKH_TRC_ALL_EVENTS );
 * 		...
 * 	}
 * 	\endcode
 *
 *	\note
 * 	This function is internal to RKH and the user application should not call 
 * 	it. Please use RKH_FILTER_ON_GROUP(), or RKH_FILTER_OFF_GROUP() macros 
 * 	instead.
 * 
 * 	\param ctrl		filter option, the available options are FILTER_ON or 
 * 					FILTER_OFF.
 * 	\param grp		trace group. The available groups are enumerated in 
 * 					RKH_TRC_GROUPS.
 * 	\param mode		filter mode. ECHANGE indicates that the all event's group 
 * 					are accordingly changed as filter option value, otherwise 
 * 					EUNCHANGE.
 */

void rkh_trc_filter_group_( rkhui8_t ctrl, rkhui8_t grp, rkhui8_t mode );


/**
 * 	\brief
 * 	Emit or suppress a specific event.
 *
 * 	The stream is initially created with an empty filter (that is, without 
 * 	filtering any event type). If this is not the required behavior, the 
 * 	application can build a set of event types, include the appropriate event 
 * 	types in it, and apply it as a filter to the stream. After that, the 
 * 	stream will reject any event whose type is in the filter set.
 *	
 *	Gathering many events generates a lot of data, which requires memory and 
 *	processor time. It also makes the task of interpreting the data more 
 *	difficult. Because the amount of data that the instrumented framework 
 *	generates can be overwhelming, the RKH supports several types of filters 
 *	that can use it to reduce the amount of data to be processed. The available 
 *	events are enumerated in #RKH_TRC_EVENTS.
 *
 * 	Example:
 * 	
 * 	\code
 * 	void 
 * 	some_function( ... )
 * 	{
 * 		RKH_FILTER_OFF_EVENT( RKH_TE_MP_INIT );
 * 		RKH_FILTER_OFF_EVENT( RKH_TE_SM_DCH );
 * 		RKH_FILTER_OFF_EVENT( RKH_TE_FWK_OBJ );
 * 		RKH_FILTER_OFF_EVENT( RKH_TE_FWK_SIG );
 * 		RKH_FILTER_OFF_EVENT( RKH_TE_TIM_START );
 * 		RKH_FILTER_OFF_EVENT( RKH_TE_TIM_TOUT );
 * 		...
 *	}
 * 	\endcode
 *
 *	\note
 * 	This function is internal to RKH and the user application should not call 
 * 	it. Please use RKH_FILTER_ON_EVENT(), or RKH_FILTER_OFF_EVENT() macros 
 * 	instead.
 * 
 * 	\param ctrl		filter option, the available options are FILTER_ON or 
 * 					FILTER_OFF.
 * 	\param evt		trace event. The available events are enumerated in 
 * 					RKH_TRC_EVENTS.
 */

void rkh_trc_filter_event_( rkhui8_t ctrl, rkhui8_t evt );


/**
 * 	\brief
 * 	Test the group and event filter condition.
 *
 *	\note
 * 	This function is internal to RKH and the user application should not call 
 * 	it.
 *
 * 	\param e		trace event. The available events are enumerated in 
 * 					RKH_TRC_EVENTS.
 *	
 *	\return
 * 	'1' (TRUE) if the group and event is not filtered, otherwise '0' (FALSE).
 */

HUInt rkh_trc_isoff_( rkhui8_t e );


/**
 * 	\brief
 * 	Emmit or suppresse trace events related to a particular active 
 * 	object or event signal.
 *
 *	\note
 * 	This function is internal to RKH and the user application should not call 
 * 	it. Please use RKH_FILTER_ON_SMA()/RKH_FILTER_ON_SIGNAL(), or 
 * 	RKH_FILTER_OFF_SMA()/RKH_FILTER_OFF_SIGNAL macros instead.
 * 	
 * 	\param filter	filter type.
 * 	\param slot		indicates the filter slot to be applied.
 * 	\param mode		filter option, the available options are FILTER_ON or 
 * 					FILTER_OFF. 
 */

void rkh_trc_simfil( const FIL_T *filter, TRCFS_T slot, rkhui8_t mode );


/**
 * 	\brief
 * 	Test the active objecto or signal filter condition.
 *
 *	\note
 * 	This function is internal to RKH and the user application should not call 
 * 	it.
 *
 * 	\param filter	filter type.
 * 	\param slot		indicates the filter slot to be applied.
 *	
 *	\return
 * 	'1' (TRUE) if the group and event is not filtered, otherwise '0' (FALSE).
 */

HUInt rkh_trc_simfil_isoff( const FIL_T *filter, TRCFS_T slot );


/**
 * 	\brief
 * 	Test the state machine application (SMA) filter condition.
 *
 *	\note
 * 	This macro is internal to RKH and the user application should not call 
 * 	it.
 *
 * 	\param prio		SMA priority.
 *	
 *	\return
 * 	'1' (TRUE) if the SMA is not filtered, otherwise '0' (FALSE).
 */

#if RKH_TRC_RTFIL_SMA_EN == RKH_DEF_ENABLED
		#define RKH_TRC_AO_ISOFF( prio ) \
					&& rkh_trc_simfil_isoff( &fsma, (TRCFS_T)(prio) )
#else
		#define RKH_TRC_AO_ISOFF( prio )
#endif


/**
 * 	\brief
 * 	Test the event signal filter condition.
 *
 *	\note
 * 	This macro is internal to RKH and the user application should not call 
 * 	it.
 *
 * 	\param sig		event signal.
 *	
 *	\return
 * 	'1' (TRUE) if the signal is not filtered, otherwise '0' (FALSE).
 */

#if RKH_TRC_RTFIL_SIGNAL_EN == RKH_DEF_ENABLED
		#define RKH_TRC_SIG_ISOFF( sig ) \
					&& rkh_trc_simfil_isoff( &fsig, (TRCFS_T)(sig) )
#else
		#define RKH_TRC_SIG_ISOFF( sig )
#endif


/**
 * 	\brief
 * 	Store the trace record header in the stream.
 *	
 *	By means of RKH_TRC_HDR() macro stores the listed data fields in the 
 *	stream buffer (in that order):
 *	
 *	- Trace event ID [1-byte].
 *
 *	- Sequence number [1-byte]. If the RKH_TRC_EN_NSEQ is set to 1 then RKH 
 *	will add to the trace record an incremental number (1-byte), used like 
 *	a sequence number.
 *
 *	- Timestamp [1, 2 or 4 bytes]. If the RKH_TRC_EN_TSTAMP is set to 1 then 
 *	RKH will add to the trace record a timestamp field. It's configurable by 
 *	means of RKH_TRC_SIZEOF_TSTAMP. 
 *	
 *	The next listing shows the implemented RKH_TRC_HDR() macro:
 *
 *	\code
 * 		RKH_TRC_HDR( eid ) 		\
 * 	(1)		chk = 0;			\
 * 	(2)		RKH_TRC_UI8( eid );	\
 * 	(3)		RKH_TRC_NSEQ();		\
 * 	(4)		RKH_TRC_TSTAMP()
 * 	\endcode
 *
 * 	\li (1)	Initialize the trace record checksum.
 *	\li (2)	Insert the event ID
 *	\li (3)	Insert the sequence number
 *	\li (4)	Insert the timestamp
 *
 * 	\note
 *	This function should be called indirectly through the macro 
 *	RKH_TRC_BEGIN.
 *
 *	\param eid		trace event ID. The available events are 
 * 					enumerated in RKH_TRC_EVENTS.
 */

void rkh_trc_begin( rkhui8_t eid );


/**
 * 	\brief
 * 	Terminate the recorded trace event.
 *
 *	This function inserts a the flag byte, which delimits the frame. 
 *	The flag is the 0x7E.
 *
 * 	\note
 *	This function should be called indirectly through the macro 
 *	RKH_TRC_END.
 */

void rkh_trc_end( void );


/**
 * 	\brief
 * 	Store a 8-bit data into the current trace event buffer without format 
 * 	information.
 *
 * 	\param d		data
 */

void rkh_trc_u8( rkhui8_t d );


/**
 * 	\brief
 * 	Store a 16-bit data into the current trace event buffer without format 
 * 	information.
 *
 * 	\param d		data
 */

void rkh_trc_u16( rkhui16_t d );


/**
 * 	\brief
 * 	Store a 32-bit data into the current trace event buffer without format 
 * 	information.
 *
 * 	\param d		data
 */

void rkh_trc_u32( rkhui32_t d );


/**
 * 	\brief
 * 	Store a string terminated in '\\0' into the current trace event buffer 
 * 	without format information.
 *
 * 	\param s		pointer to string treminated in '\\0'
 */

void rkh_trc_str( const char *s );


/**
 * 	\brief
 * 	Store a 8-bit data into the current trace event buffer with format 
 * 	information.
 *
 * 	\param fmt		format information
 * 	\param d		data
 */

void rkh_trc_fmt_u8( rkhui8_t fmt, rkhui8_t d );


/**
 * 	\brief
 * 	Store a 16-bit data into the current trace event buffer with format 
 * 	information.
 *
 * 	\param fmt		format information
 * 	\param d		data
 */

void rkh_trc_fmt_u16( rkhui8_t fmt, rkhui16_t d );


/**
 * 	\brief
 * 	Store a 32-bit data into the current trace event buffer with format 
 * 	information.
 *
 * 	\param fmt		format information
 * 	\param d		data
 */

void rkh_trc_fmt_u32( rkhui8_t fmt, rkhui32_t d );


/**
 * 	\brief
 * 	Store a string terminated in '\\0' into the current trace event buffer 
 * 	with format information.
 *
 * 	\param s		pointer to string terminated in '\\0'
 */

void rkh_trc_fmt_str( const char *s );


/**
 * 	\brief
 * 	Output memory block of up to 255-bytes with format information.
 *
 * 	\param mem		pointer to memory block.
 * 	\param size		size of memory block.
 */

void rkh_trc_fmt_mem( rkhui8_t const *mem, rkhui8_t size );


#endif
