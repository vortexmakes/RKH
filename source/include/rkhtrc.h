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


#include "rkhtype.h"
#include "rkhcfg.h"
#include <string.h>


/**
 * 	\brief
 * 	The size of trceftbl table depends on #RKH_TRC_MAX_EVENTS (see rkhcfg.h).
 */

#if RKH_TRC_MAX_EVENTS <= 64
	#define RKH_TRC_MAX_EVENTS_PER_GROUP	8
#elif RKH_TRC_MAX_EVENTS > 64 && RKH_TRC_MAX_EVENTS <= 128
	#define RKH_TRC_MAX_EVENTS_PER_GROUP	16
#else
	#define RKH_TRC_MAX_EVENTS_PER_GROUP	8
#endif


/**
 * 	\brief
 * 	Filter table of trace events.
 *
 * 	The trace filter management is similar to the native priority scheme.
 * 	In this case, each trace event is assigned a unique number 
 * 	(#RKH_TRC_EVENTS). When a event is ready to record a trace its 
 * 	corresponding bit in the filter table must be clear. The size of 
 * 	#trceftbl[] depends on #RKH_TRC_MAX_EVENTS (see rkhcfg.h).
 *
 * 	Trace event number = | 0 | Y | Y | Y | Y | X | X | X |\n
 *
 * 	Y's:	index into trceftbl[ #RKH_TRC_MAX_EVENTS_PER_GROUP ] table.\n
 * 	X's:	bit position in trceftbl[ Y's ].\n
 *
 * 	The lower 3 bits (X's) of the trace event number are used to determine 
 * 	the bit position in trceftbl[], while the next four most significant bits 
 * 	(Y's) are used to determine the index into trceftbl[].
 */

extern rkhui8_t trceftbl[ RKH_TRC_MAX_EVENTS_PER_GROUP ];


/**
 * 	\brief
 * 	Filter table of trace groups.
 *
 * 	Each bit in #trcgfilter is used to indicate whenever any trace group 
 * 	is filtered out its events. See #RKH_TRC_GROUPS.
 *
 * 	\code
 *  bit position =   7   6   5   4   3   2   1   0   -- Groups   
 * 	trcgfilter   = | Y | Y | Y | Y | Y | Y | Y | Y |
 * 				   		     |		   	     |   |___ RKH_TG_MP
 *						     |			     |_______ RKH_TG_RQ
 * 						     |				  		  ...
 * 				             |_______________________ RKH_TG_FWK
 *	\endcode
 */

extern rkhui8_t trcgfilter;


/**
 * 	\brief
 * 	The size of trcsmaftbl (trace SMA filter table) depends on #RKH_MAX_SMA 
 * 	(see rkhcfg.h).
 */

#if RKH_MAX_SMA <= 8
	#define RKH_TRC_MAX_SMA		1
#elif RKH_MAX_SMA > 8 && RKH_MAX_SMA <= 16
	#define RKH_TRC_MAX_SMA		2
#elif RKH_MAX_SMA > 16 && RKH_MAX_SMA <= 24
	#define RKH_TRC_MAX_SMA		3
#elif RKH_MAX_SMA > 24 && RKH_MAX_SMA <= 32
	#define RKH_TRC_MAX_SMA		4
#elif RKH_MAX_SMA > 32 && RKH_MAX_SMA <= 40
	#define RKH_TRC_MAX_SMA		5
#elif RKH_MAX_SMA > 40 && RKH_MAX_SMA <= 48
	#define RKH_TRC_MAX_SMA		6
#elif RKH_MAX_SMA > 48 && RKH_MAX_SMA <= 56
	#define RKH_TRC_MAX_SMA		7
#elif RKH_MAX_SMA > 56 && RKH_MAX_SMA <= 64
	#define RKH_TRC_MAX_SMA		8
#endif


/**
 * 	\brief
 * 	Filter table of trace points associated with the SMA (AO).
 *
 * 	The trace filter management is similar to the native priority scheme.
 * 	In this case, each SMA is assigned a unique priority number. When a SMA 
 * 	is ready to record a trace its corresponding bit in the filter table 
 * 	must be clear. The size of #trcsmaftbl[] depends on 
 * 	#RKH_MAX_SMA (see rkhcfg.h).
 *
 * 	SMA priority number = | Y | Y | Y | Y | Y | X | X | X |\n
 *
 * 	Y's:	index into trcsmaftbl[ #RKH_TRC_MAX_SMA ] table.\n
 * 	X's:	bit position in trcsmaftbl[ Y's ].\n
 *
 * 	The lower 3 bits (X's) of the SMA priority number are used to determine 
 * 	the bit position in trcsmaftbl[], while the next five most significant bits 
 * 	(Y's) are used to determine the index into trcsmaftbl[].
 */

extern rkhui8_t trcsmaftbl[ RKH_TRC_MAX_SMA ];


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
 * 	Emit or suppress tracing for all groups and events.
 */

#define RKH_TRC_ALL_GROUPS		RKH_TG_NGROUP


/**
 * 	\brief
 * 	Emit or suppress all trace events.
 */

#define RKH_TRC_ALL_EVENTS		RKH_TE_NEVENT


typedef enum
{
	FILTER_ON, FILTER_OFF,
} RKH_TRC_FOPT;


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


#define ECHANGE				0
#define EUNCHANGE			1


/*
 * 	The trace event ID is arranged as:
 *
 * 	event number = | G | G | G | E | E | E | E | E |\n
 *
 * 	G's:	group number.\n
 * 	X's:	event's group.\n
 *
 * 	The lower 5 bits (E's) of the event ID are used to determine 
 * 	the trace event, while the next three most significant bits 
 * 	(G's) are used to determine the corresponding group.
 * 
 * 	Therefore, is able to define 3 groups and 32 events per group.
 */

#define RKH_NUM_TE_PER_GROUP		32 /* 2^5 = 32 */
#define GRPSH( grp )				(rkhui8_t)(((grp)&7) << NGSH)

#if RKH_NUM_TE_PER_GROUP <= 32
	#define NGSH					5
#else
	#define NGSH					5
#endif

#define RKH_MP_START				GRPSH( RKH_TG_MP	)
#define RKH_RQ_START				GRPSH( RKH_TG_RQ 	)
#define RKH_SMA_START				GRPSH( RKH_TG_SMA 	)
#define RKH_SM_START				GRPSH( RKH_TG_SM 	)
#define RKH_TIM_START				GRPSH( RKH_TG_TIM 	)
#define RKH_FWK_START				GRPSH( RKH_TG_FWK 	)
#define RKH_USR_START				GRPSH( RKH_TG_USR 	)


/**
 * 	\brief
 * 	RKH trace events.
 *
 * 	<EM>RKH trace event structure</EM>
 *
 *	\code
 *	(1) RKH_TRC_BEGIN( event, sma )	\
 *	(2)		RKH_TRC_ARG0( arg0 ); 			\
 *	(3)		RKH_TRC_ARG1( arg1 ); 			\
 *	(4)		RKH_TRC_....( ... ); 			\	
 *	(5)	RKH_TRC_END()
 *	\endcode
 *
 *	\li (1,5)	Each trace event always begins with the macro RKH_TRC_BEGIN() 
 *				and ends with the matching macro RKH_TRC_END().
 *			 	These macros are not terminated with the semicolon.
 *			 	The record-begin macro RKH_TRC_BEGIN() takes three arguments. 
 *			 	The first argument 'event' is the trace event ID, and the 
 *			 	second argument 'sma' is the state machine application 
 *			 	(active object). These arguments are used in the on/off 
 *			 	filters. 
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
 *	#define RKH_TR_RQ_INIT( q, nelem, sma )						\
 *				RKH_TRC_BEGIN( RKH_TE_RQ_INIT, NVS )	\
 *					RKH_TRC_SYM( q ); 							\
 *					RKH_TRC_SYM( sma ); 						\
 *					RKH_TRC_NE( nelem ); 						\
 *				RKH_TRC_END()
 *	
 *	#define RKH_TR_SMA_FIFO( sma, ev )							\
 *				RKH_TRC_BEGIN( 	RKH_TE_SMA_FIFO, 	\
 *								sma->romrkh->prio )				\
 *					RKH_TRC_SYM( sma ); 						\
 *					RKH_TRC_SIG( ev->e ); 						\
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
	RKH_TE_RQ_DPT,					/**< \copydetails RKH_TR_RQ_DEPLETE */
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
	RKH_TE_SM_CSTATE,				/**< \copydetails RKH_TR_SM_CSTATE */
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
	RKH_TE_TIM_RESTART,				/**< \copydetails RKH_TR_TIM_RESTART */
	RKH_TE_TIM_STOP,				/**< \copydetails RKH_TR_TIM_STOP */
	RKH_TE_TIM_TOUT,				/**< \copydetails RKH_TR_TIM_TOUT */
	RKH_TE_TIM_REM,					/**< \copydetails RKH_TR_TIM_REM */

	/* --- Framework events (RKH group) ------------------- */
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

	RKH_TE_USER = RKH_USR_START,

	RKH_TE_NEVENT
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

#if RKH_TRC_EN_CHK == 1
	#define RKH_TRC_CHK()					\
				chk = (rkhui8_t)(~chk + 1); \
				rkh_trc_ui8( chk )
#else
	#define RKH_TRC_CHK()
#endif


/**
 * 	\brief
 * 	Inserts directly into the trace stream the flag byte in a raw (without 
 * 	escaped sequence) manner.
 */

#define RKH_TRC_FLG()						\
				RKH_TRC_UI8_RAW( RKH_FLG )


/** 
 * 	\brief
 * 	Defines the size of trace timestamp. 
 *
 * 	The valid values [in bits] are 8, 16 or 32. Default is 16. This type is 
 * 	configurable via the RKH_TRC_SIZEOF_TSTAMP preprocessor option.
 */

#if RKH_TRC_EN_TSTAMP == 1
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


#if RKH_TRC_RUNTIME_FILTER == 1

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
	 *	\param eid		is the trace event ID (RKH_TRC_EVENTS).
	 *	\param prio		priority of state machine application.
	 */

	#define RKH_TRC_BEGIN( eid, prio )			\
				RKH_SR_CRITICAL_;					\
				if(	rkh_trc_isoff_( eid ) && 		\
					rkh_trc_sma_isoff_( prio ) )	\
				{									\
					RKH_ENTER_CRITICAL_();			\
					rkh_trc_begin( eid );

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
#else
	#define RKH_TRC_BEGIN( eid, prio )		\
				RKH_SR_CRITICAL_;				\
				RKH_ENTER_CRITICAL_();			\
				rkh_trc_begin( eid );

	#define RKH_TRC_END()						\
				rkh_trc_end();					\
				RKH_EXIT_CRITICAL_();
#endif


/**
 * 	Idem RKH_TRC_BEGIN() macro but use it for trace events that are 
 * 	independent of any runtime filter.
 */

#define RKH_TRC_BEGIN_WOFIL( eid, prio )		\
			RKH_SR_CRITICAL_;					\
			RKH_ENTER_CRITICAL_();				\
			rkh_trc_begin( eid );

/**
 * 	Idem RKH_TRC_END() macro but use it for trace events that are 
 * 	independent of any runtime filter.
 */

#define RKH_TRC_END_WOFIL()						\
			rkh_trc_end();						\
			RKH_EXIT_CRITICAL_();


/**
 * 	\brief
 * 	Insert a 1-byte without escaping it.
 */

#define RKH_TRC_UI8_RAW( d )	\
			rkh_trc_put( (d) )

/**
 * 	\brief
 * 	Insert a 1-byte data.
 */

#define RKH_TRC_UI8( d )	\
			rkh_trc_ui8( (d) )

/**
 * 	\brief
 * 	Insert a 2-byte data.
 */

#define RKH_TRC_UI16( d )	\
			rkh_trc_ui16( (d) )

/**
 * 	\brief
 * 	Insert a 4-byte data.
 */

#define RKH_TRC_UI32( d )	\
			rkh_trc_ui32( (d) )

/**
 * 	\brief
 * 	Insert a string.
 */

#define RKH_TRC_STR( s )	\
			rkh_trc_str( (s) )

/**
 * 	\brief
 * 	Insert the sequence number byte.
 */

#if RKH_TRC_EN_NSEQ == 1
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
#elif RKH_MP_SIZEOF_NBLOCK == 16
	#define RKH_TRC_NBLK( nb )	\
				RKH_TRC_UI16( nb )
#elif RKH_MP_SIZEOF_NBLOCK == 32
	#define RKH_TRC_NBLK( nb )	\
				RKH_TRC_UI32( nb )
#else
	#define RKH_TRC_NBLK( nb )	\
				RKH_TRC_UI8( nb )
#endif


/**
 * 	Insert a nelem value as trace record argument.
 */

#if RKH_RQ_SIZEOF_NELEM == 8
	#define RKH_TRC_NE( ne )	\
				RKH_TRC_UI8( ne )
#elif RKH_MP_SIZEOF_NELEM == 16
	#define RKH_TRC_NE( ne )	\
				RKH_TRC_UI16( ne )
#elif RKH_MP_SIZEOF_NELEM == 32
	#define RKH_TRC_NE( ne )	\
				RKH_TRC_UI32( ne )
#else
	#define RKH_TRC_NE( ne )	\
				RKH_TRC_UI8( ne )
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

#define NVS			RKH_MAX_SMA


#if RKH_TRC_EN == 1
	/* --- Memory Pool (MP) ------------------ */
	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_MP == 1

		/**
		 * 	Desc	= initialize a memory block pool\n
		 * 	Group 	= RKH_TG_MP\n
		 * 	Id 		= RKH_TE_MP_INIT\n
		 * 	Args	= memory pool, nblock\n
		 */

		#define RKH_TR_MP_INIT( mp, nblock )							\
					RKH_TRC_BEGIN( RKH_TE_MP_INIT, NVS )		\
						RKH_TRC_SYM( mp ); 								\
						RKH_TRC_NBLK( nblock ); 						\
					RKH_TRC_END()

		/**
		 * 	Desc 	= get a block from the pool\n
		 * 	Group 	= RKH_TG_MP\n
		 * 	Id 		= RKH_TE_MP_GET\n
		 * 	Args	= memory pool, nfree\n
		 */

		#define RKH_TR_MP_GET( mp, nfree )								\
					RKH_TRC_BEGIN( RKH_TE_MP_GET, NVS )		\
						RKH_TRC_SYM( mp ); 								\
						RKH_TRC_NBLK( nfree ); 							\
					RKH_TRC_END()
	
		/**
		 * 	Desc 	= put the block to the pool\n
		 * 	Group 	= RKH_TG_MP\n
		 * 	id 		= RKH_TE_MP_PUT\n
		 * 	Args	= memory pool, nfree\n
		 */

		#define RKH_TR_MP_PUT( mp, nfree )								\
					RKH_TRC_BEGIN( RKH_TE_MP_PUT, NVS )		\
						RKH_TRC_SYM( mp ); 								\
						RKH_TRC_NBLK( nfree ); 							\
					RKH_TRC_END()
	#else
		#define RKH_TR_MP_INIT( mp, nblock )
		#define RKH_TR_MP_GET( mp, nfree )
		#define RKH_TR_MP_PUT( mp, nfree )
	#endif

	/* --- Queue (RQ) ------------------------ */
	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_RQ == 1

		/**
		 * 	Desc 	= initialize a queue\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_INIT\n
		 * 	Args	= queue, sma, nelem\n
		 */

		#define RKH_TR_RQ_INIT( q, nelem, sma )							\
					RKH_TRC_BEGIN( RKH_TE_RQ_INIT, NVS )		\
						RKH_TRC_SYM( q ); 								\
						RKH_TRC_SYM( sma ); 							\
						RKH_TRC_NE( nelem ); 							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= get a element from the queue\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_GET\n
		 * 	Args	= queue, qty\n
		 */

		#define RKH_TR_RQ_GET( q, qty )									\
					RKH_TRC_BEGIN( RKH_TE_RQ_GET, NVS )		\
						RKH_TRC_SYM( q ); 								\
						RKH_TRC_NE( qty ); 								\
					RKH_TRC_END()
	
		/**
		 * 	Desc 	= put a element to the queue in a FIFO manner\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_FIFO\n
		 * 	Args	= queue, qty\n
		 */

		#define RKH_TR_RQ_FIFO( q, qty )								\
					RKH_TRC_BEGIN( RKH_TE_RQ_FIFO, NVS )		\
						RKH_TRC_SYM( q ); 								\
						RKH_TRC_NE( qty ); 								\
					RKH_TRC_END()

		/**
		 * 	Desc 	= put a element to the queue in a LIFO manner\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_LIFO\n
		 * 	Args	= queue, qty\n
		 */

		#define RKH_TR_RQ_LIFO( q, qty )								\
					RKH_TRC_BEGIN( RKH_TE_RQ_LIFO, NVS )		\
						RKH_TRC_SYM( q ); 								\
						RKH_TRC_NE( qty ); 								\
					RKH_TRC_END()

		/**
		 * 	Desc 	= query the queue\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_FULL\n
		 * 	Args	= queue\n
		 */

		#define RKH_TR_RQ_FULL( q )										\
					RKH_TRC_BEGIN( RKH_TE_RQ_FULL, NVS )		\
						RKH_TRC_SYM( q ); 								\
					RKH_TRC_END()

		/**
		 * 	Desc 	= deplete the queue\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_DPT\n
		 * 	Args	= queue\n
		 */

		#define RKH_TR_RQ_DEPLETE( q )									\
					RKH_TRC_BEGIN( RKH_TE_RQ_DPT, NVS )		\
						RKH_TRC_SYM( q ); 								\
					RKH_TRC_END()

		/**
		 * 	Desc 	= get the last element from the queue\n
		 * 	Group 	= RKH_TG_RQ\n
		 * 	Id 		= RKH_TE_RQ_GET_LAST\n
		 * 	Args	= queue\n
		 */

		#define RKH_TR_RQ_GET_LAST( q )									\
					RKH_TRC_BEGIN( RKH_TE_RQ_GET_LAST, NVS )	\
						RKH_TRC_SYM( q ); 								\
					RKH_TRC_END()
	#else
		#define RKH_TR_RQ_INIT( q, nelem, sma )
		#define RKH_TR_RQ_GET( q, qty )
		#define RKH_TR_RQ_FIFO( q, qty )
		#define RKH_TR_RQ_LIFO( q, qty )
		#define RKH_TR_RQ_FULL( q )
		#define RKH_TR_RQ_DEPLETE( q )
		#define RKH_TR_RQ_GET_LAST( q )
	#endif

	/* --- State Machine Application (SMA) --- */
	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_SMA == 1

		/**
		 * 	Desc 	= activate a SMA\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_ACT\n
		 * 	Args	= sma\n
		 */

		#define RKH_TR_SMA_ACT( sma )									\
					RKH_TRC_BEGIN( 	RKH_TE_SMA_ACT, 		\
									sma->romrkh->prio )					\
						RKH_TRC_SYM( sma ); 							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= terminate a SMA\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_ACT\n
		 * 	Args	= sma\n
		 */

		#define RKH_TR_SMA_TERM( sma )									\
					RKH_TRC_BEGIN( 	RKH_TE_SMA_TERM, 		\
									sma->romrkh->prio )					\
						RKH_TRC_SYM( sma ); 							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= get a event from the SMA's queue\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_ACT\n
		 * 	Args	= sma, signal\n
		 */

		#define RKH_TR_SMA_GET( sma, ev )								\
					RKH_TRC_BEGIN( RKH_TE_SMA_GET, 			\
									sma->romrkh->prio )					\
						RKH_TRC_SYM( sma ); 							\
						RKH_TRC_SIG( ev->e ); 							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= send a event to SMA's queue in a FIFO manner\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_FIFO\n
		 * 	Args	= sma, signal\n
		 */

		#define RKH_TR_SMA_FIFO( sma, ev )								\
					RKH_TRC_BEGIN( RKH_TE_SMA_FIFO, 		\
									sma->romrkh->prio )					\
						RKH_TRC_SYM( sma ); 							\
						RKH_TRC_SIG( ev->e ); 							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= send a event to SMA's queue in a LIFO manner\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_LIFO\n
		 * 	Args	= sma, signal\n
		 */

		#define RKH_TR_SMA_LIFO( sma, ev )								\
					RKH_TRC_BEGIN( RKH_TE_SMA_LIFO, 		\
									sma->romrkh->prio )					\
						RKH_TRC_SYM( sma ); 							\
						RKH_TRC_SIG( ev->e ); 							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= register a SMA\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_REG\n
		 * 	Args	= sma, prio\n
		 */

		#define RKH_TR_SMA_REG( sma, prio )								\
					RKH_TRC_BEGIN( RKH_TE_SMA_REG, 			\
									sma->romrkh->prio )					\
						RKH_TRC_SYM( sma ); 							\
						RKH_TRC_UI8( prio ); 							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= unregister a SMA\n
		 * 	Group 	= RKH_TG_SMA\n
		 * 	Id 		= RKH_TE_SMA_UNREG\n
		 * 	Args	= sma, prio\n
		 */

		#define RKH_TR_SMA_UNREG( sma, prio )							\
					RKH_TRC_BEGIN( RKH_TE_SMA_UNREG, 		\
									sma->romrkh->prio )					\
						RKH_TRC_SYM( sma ); 							\
						RKH_TRC_UI8( prio ); 							\
					RKH_TRC_END()
	#else
		#define RKH_TR_SMA_ACT( sma )
		#define RKH_TR_SMA_TERM( sma )
		#define RKH_TR_SMA_GET( sma, ev )
		#define RKH_TR_SMA_FIFO( sma, ev )
		#define RKH_TR_SMA_LIFO( sma, ev )
		#define RKH_TR_SMA_REG( sma, prio )
		#define RKH_TR_SMA_UNREG( sma, prio )
	#endif

	/* --- State machine (SM) ---------------- */
	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_SM == 1

		/**
		 * 	Desc 	= start (initialize) a state machine\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_INIT\n
		 * 	Args	= sma, initial state\n
		 */

		#if RKH_TRC_EN_SM_INIT == 1
			#define RKH_TR_SM_INIT( sma, is )							\
						RKH_TRC_BEGIN( RKH_TE_SM_INIT, 		\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
							RKH_TRC_SYM( is ); 							\
						RKH_TRC_END()
		#endif

		/**
		 * 	Desc 	= dispatch an event to a state machine\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_DCH\n
		 * 	Args	= sma, signal\n
		 */

		#if RKH_TRC_EN_SM_DCH == 1
			#define RKH_TR_SM_DCH( sma, ev )							\
						RKH_TRC_BEGIN( RKH_TE_SM_DCH, 		\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
							RKH_TRC_SIG( ev->e ); 						\
						RKH_TRC_END()
		#endif

		/**
		 * 	Desc 	= clear history pseudostate\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_CLRH\n
		 * 	Args	= sma, history pseudostate\n
		 */

		#if RKH_TRC_EN_SM_CLRH == 1
			#define RKH_TR_SM_CLRH( sma, h )							\
						RKH_TRC_BEGIN( RKH_TE_SM_CLRH, 		\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
							RKH_TRC_SYM( h ); 							\
						RKH_TRC_END()
		#endif

		/**
		 * 	Desc 	= source and target state of transition\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_TRN\n
		 * 	Args	= sma, source state, target state\n
		 */

		#if RKH_TRC_EN_SM_TRN == 1 
			#define RKH_TR_SM_TRN( sma, ss, ts )						\
						RKH_TRC_BEGIN( RKH_TE_SM_TRN, 		\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
							RKH_TRC_SYM( ss ); 							\
							RKH_TRC_SYM( ts ); 							\
						RKH_TRC_END()
		#endif

		/**
		 * 	Desc 	= final state of transition\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_STATE\n
		 * 	Args	= sma, final state\n
		 */

		#if RKH_TRC_EN_SM_STATE == 1
			#define RKH_TR_SM_STATE( sma, s )							\
						RKH_TRC_BEGIN( RKH_TE_SM_STATE, 		\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
							RKH_TRC_SYM( s ); 							\
						RKH_TRC_END()
		#endif

		/**
		 * 	Desc 	= entry state\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_ENSTATE\n
		 * 	Args	= sma, entry state\n
		 */

		#if RKH_TRC_EN_SM_ENSTATE == 1
			#define RKH_TR_SM_ENSTATE( sma, s )							\
						RKH_TRC_BEGIN( RKH_TE_SM_ENSTATE, 	\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
							RKH_TRC_SYM( s ); 							\
						RKH_TRC_END()
		#endif

		/**
		 * 	Desc 	= exit state\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_EXSTATE\n
		 * 	Args	= sma, exit state\n
		 */

		#if RKH_TRC_EN_SM_EXSTATE == 1
			#define RKH_TR_SM_EXSTATE( sma, s )							\
						RKH_TRC_BEGIN( RKH_TE_SM_EXSTATE, 	\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
							RKH_TRC_SYM( s ); 							\
						RKH_TRC_END()
		#endif

		/**
		 * 	Desc 	= number of entry and exit states in transition\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_NENEX\n
		 * 	Args	= sma, nenex\n
		 */

		#if RKH_TRC_EN_SM_NENEX == 1 
			#define RKH_TR_SM_NENEX( sma, nen, nex )					\
						RKH_TRC_BEGIN( RKH_TE_SM_NENEX, 		\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
							RKH_TRC_UI8( nen ); 						\
							RKH_TRC_UI8( nex ); 						\
						RKH_TRC_END()
		#endif

		/**
		 * 	Desc 	= number of executed actions in transition\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_NTRNACT\n
		 * 	Args	= sma, nta, nts\n
		 */

		#if RKH_TRC_EN_SM_NTRNACT == 1
			#define RKH_TR_SM_NTRNACT( sma, nta, nts )					\
						RKH_TRC_BEGIN( RKH_TE_SM_NTRNACT, 	\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
							RKH_TRC_UI8( nta ); 						\
							RKH_TRC_UI8( nts ); 						\
						RKH_TRC_END()
		#endif

		/**
		 * 	Desc 	= state or pseudostate in a compound transition\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_CSTATE\n
		 * 	Args	= sma, state/pseudosstate\n
		 */

		#if RKH_TRC_EN_SM_CSTATE == 1
			#define RKH_TR_SM_CSTATE( sma, s )							\
						RKH_TRC_BEGIN( RKH_TE_SM_CSTATE, 	\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
							RKH_TRC_SYM( s ); 							\
						RKH_TRC_END()
		#endif

		#if RKH_TRC_EN_SM_PROCESS == 1

		/**
		 * 	Desc 	= the arrived event was succesfully processed and HSM 
		 * 			  resides in an allowed state.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_EVT_PROC\n
		 * 	Args	= sma\n
		 */

			#define RKH_TR_SM_EVT_PROC( sma )							\
						RKH_TRC_BEGIN( RKH_TE_SM_EVT_PROC, 	\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
						RKH_TRC_END()

		/**
		 * 	Desc 	= the arrived event was't founded in the transition 
		 * 			  table.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_EVT_NFOUND\n
		 * 	Args	= sma\n
		 */

			#define RKH_TR_SM_EVT_NFOUND( sma )							\
						RKH_TRC_BEGIN( RKH_TE_SM_EVT_NFOUND,	\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
						RKH_TRC_END()

		/**
		 * 	Desc 	= the branch function returned a value not founded 
		 * 			  in the branch table.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_CND_NFOUND\n
		 * 	Args	= sma\n
		 */

			#define RKH_TR_SM_CND_NFOUND( sma )							\
						RKH_TRC_BEGIN( RKH_TE_SM_CND_NFOUND,	\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
						RKH_TRC_END()

		/**
		 * 	Desc 	= The transition was cancelled by guard function.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_GRD_FALSE\n
		 * 	Args	= sma\n
		 */

			#define RKH_TR_SM_GRD_FALSE( sma )							\
						RKH_TRC_BEGIN( RKH_TE_SM_GRD_FALSE,	\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
						RKH_TRC_END()

		/**
		 * 	Desc 	= unknown state.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_UNKN_STATE\n
		 * 	Args	= sma\n
		 */

			#define RKH_TR_SM_UNKN_STATE( sma )							\
						RKH_TRC_BEGIN( RKH_TE_SM_UNKN_STATE,	\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
						RKH_TRC_END()

		/**
		 * 	Desc 	= the transition exceeded the allowed hierarchical 
		 * 			  level.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_EX_HLEVEL\n
		 * 	Args	= sma\n
		 */
			#define RKH_TR_SM_EX_HLEVEL( sma )							\
						RKH_TRC_BEGIN( RKH_TE_SM_EX_HLEVEL,	\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
						RKH_TRC_END()

		/**
		 * 	Desc 	= the transition exceeded the allowed number of 
		 * 			  segments within a compound transtion.\n
		 * 	Group 	= RKH_TG_SM\n
		 * 	Id 		= RKH_TE_SM_EX_TSEG\n
		 * 	Args	= sma\n
		 */
			#define RKH_TR_SM_EX_TSEG( sma )							\
						RKH_TRC_BEGIN( RKH_TE_SM_EX_TSEG,	\
									sma->romrkh->prio )					\
							RKH_TRC_SYM( sma ); 						\
						RKH_TRC_END()
		#endif
	#else
		#define RKH_TR_SM_INIT( sma, is )				(void)0
		#define RKH_TR_SM_CLRH( sma, h )				(void)0
		#define RKH_TR_SM_DCH( sma, ev )				(void)0
		#define RKH_TR_SM_TRN( sma, ss, ts )			(void)0
		#define RKH_TR_SM_STATE( sma, s )				(void)0
		#define RKH_TR_SM_ENSTATE( sma, s )				(void)0
		#define RKH_TR_SM_EXSTATE( sma, s )				(void)0
		#define RKH_TR_SM_NENEX( sma, nen, nex )		(void)0
		#define RKH_TR_SM_NTRNACT( sma, nta, nts )		(void)0
		#define RKH_TR_SM_CSTATE( sma, s )				(void)0
		#define RKH_TR_SM_EVT_PROC( sma )				(void)0
		#define RKH_TR_SM_EVT_NFOUND( sma )				(void)0
		#define RKH_TR_SM_GRD_FALSE( sma )				(void)0
		#define RKH_TR_SM_CND_NFOUND( sma )				(void)0
		#define RKH_TR_SM_UNKN_STATE( sma )				(void)0
		#define RKH_TR_SM_EX_HLEVEL( sma )				(void)0
		#define RKH_TR_SM_EX_TSEG( sma )				(void)0
	#endif

	/* --- Timer (TIM) ----------------------- */
	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_TIM == 1

		/**
		 * 	Desc 	= initialize a timer\n
		 * 	Group 	= RKH_TG_TIM\n
		 * 	Id 		= RKH_TE_TIM_INIT\n
		 * 	Args	= timer, signal\n
		 */

		#define RKH_TR_TIM_INIT( t, sig )								\
					RKH_TRC_BEGIN( RKH_TE_TIM_INIT, NVS )	\
						RKH_TRC_SYM( t ); 								\
						RKH_TRC_SIG( sig ); 							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= start a timer\n
		 * 	Group 	= RKH_TG_TIM\n
		 * 	Id 		= RKH_TE_TIM_START\n
		 * 	Args	= timer, sma, nticks\n
		 */

		#define RKH_TR_TIM_START(	t, nt, sma )						\
					RKH_TRC_BEGIN( RKH_TE_TIM_START, NVS )	\
						RKH_TRC_SYM( t ); 								\
						RKH_TRC_SYM( sma ); 							\
						RKH_TRC_NTICK( nt ); 							\
					RKH_TRC_END()
	
		/**
		 * 	Desc 	= restart a timer\n
		 * 	Group 	= RKH_TG_TIM\n
		 * 	Id 		= RKH_TE_TIM_RESTART\n
		 * 	Args	= timer, nticks\n
		 */

		#define RKH_TR_TIM_RESTART( t, nt )								\
					RKH_TRC_BEGIN( RKH_TE_TIM_RESTART, NVS )\
						RKH_TRC_SYM( t ); 								\
						RKH_TRC_NTICK( nt ); 							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= stop a timer\n
		 * 	Group 	= RKH_TG_TIM\n
		 * 	Id 		= RKH_TE_TIM_STOP\n
		 * 	Args	= timer\n
		 */

		#define RKH_TR_TIM_STOP( t )									\
					RKH_TRC_BEGIN( RKH_TE_TIM_STOP, NVS )	\
						RKH_TRC_SYM( t ); 								\
					RKH_TRC_END()

		/**
		 * 	Desc 	= timer expired\n
		 * 	Group 	= RKH_TG_TIM\n
		 * 	Id 		= RKH_TE_TIM_TOUT\n
		 * 	Args	= timer\n
		 */

		#define RKH_TR_TIM_TOUT( t )									\
					RKH_TRC_BEGIN( RKH_TE_TIM_TOUT, NVS )	\
						RKH_TRC_SYM( t ); 								\
					RKH_TRC_END()

		/**
		 * 	Desc 	= remove timer from the active timer list\n
		 * 	Group 	= RKH_TG_TIM\n
		 * 	Id 		= RKH_TE_TIM_REM\n
		 * 	Args	= timer\n
		 */

		#define RKH_TR_TIM_REM( t )										\
					RKH_TRC_BEGIN( RKH_TE_TIM_REM, NVS )	\
						RKH_TRC_SYM( t ); 								\
					RKH_TRC_END()
	#else
		#define RKH_TR_TIM_INIT( t, sig )
		#define RKH_TR_TIM_START( t, nt, sma )
		#define RKH_TR_TIM_RESTART( t, nt )
		#define RKH_TR_TIM_STOP( t )
		#define RKH_TR_TIM_TOUT( t )
		#define RKH_TR_TIM_REM( t )
	#endif

	/* --- Framework (RKH) ----------------------- */
	#if RKH_TRC_ALL == 1 || RKH_TRC_EN_RKH == 1

		/**
		 * 	Desc 	= initialize the RKH\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_EN\n
		 * 	Args	= \n
		 */

		#define RKH_TR_FWK_EN()										\
					RKH_TRC_BEGIN( RKH_TE_FWK_EN, NVS )	\
					RKH_TRC_END()

		/**
		 * 	Desc 	= exit the RKH\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_EX\n
		 * 	Args	= \n
		 */

		#define RKH_TR_FWK_EX()											\
					RKH_TRC_BEGIN( RKH_TE_FWK_EX, NVS )		\
					RKH_TRC_END()

		/**
		 * 	Desc 	= event pool register\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_EPREG\n
		 * 	Args	= event pool index, storage size, event size\n
		 */

		#define RKH_TR_FWK_EPREG( epix, ssize, esize )					\
					RKH_TRC_BEGIN( RKH_TE_FWK_EPREG, NVS )	\
						RKH_TRC_UI8( epix );							\
						RKH_TRC_UI32( ssize );							\
						RKH_TRC_ES( esize );							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= allocate an event\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_AE\n
		 * 	Args	= event size, signal\n
		 */

		#define RKH_TR_FWK_AE( esize, ev )								\
					RKH_TRC_BEGIN( RKH_TE_FWK_AE, NVS )		\
						RKH_TRC_ES( esize );							\
						RKH_TRC_SIG( ev->e );							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= attempt to recycle an event\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_GC\n
		 * 	Args	= signal\n
		 */

		#define RKH_TR_FWK_GC( ev )										\
					RKH_TRC_BEGIN( RKH_TE_FWK_GC, NVS )		\
						RKH_TRC_SIG( ev->e );							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= effective recycling event\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_GCR\n
		 * 	Args	= signal\n
		 */

		#define RKH_TR_FWK_GCR( ev )									\
					RKH_TRC_BEGIN( RKH_TE_FWK_GCR, NVS )	\
						RKH_TRC_SIG( ev->e );							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= defer an event\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_DEFER\n
		 * 	Args	= signal\n
		 */

		#define RKH_TR_FWK_DEFER( q, ev )								\
					RKH_TRC_BEGIN( RKH_TE_FWK_DEFER, NVS )	\
						RKH_TRC_SYM( q );								\
						RKH_TRC_SIG( ev->e );							\
					RKH_TRC_END()

		/**
		 * 	Desc 	= recall an event\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_RCALL\n
		 * 	Args	= sma, signal\n
		 */

		#define RKH_TR_FWK_RCALL( sma, ev )								\
					RKH_TRC_BEGIN( RKH_TE_FWK_RCALL, NVS )	\
						RKH_TRC_SYM( sma );								\
						RKH_TRC_SIG( ev->e );							\
					RKH_TRC_END()

		/* --- Symbol entry table for objects --------- */

		/**
		 * 	Desc 	= entry symbol table for memory object\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_OBJ\n
		 * 	Args	= object address\n
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
					RKH_TRC_BEGIN_WOFIL( RKH_TE_FWK_OBJ, NVS )			\
						RKH_TRC_SYM( __o );								\
						RKH_TRC_STR( __o_n );							\
					RKH_TRC_END_WOFIL();										\
					RKH_TRC_FLUSH();									\
				} while(0)

		/* --- Symbol entry table for event signals ---- */

		/**
		 * 	Desc 	= entry symbol table for signal\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_SIG\n
		 * 	Args	= signal number\n
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
					RKH_TRC_BEGIN( RKH_TE_FWK_SIG, NVS )		\
						RKH_TRC_SIG( __s );								\
						RKH_TRC_STR( __s_n );							\
					RKH_TRC_END();										\
					RKH_TRC_FLUSH();									\
				} while(0)

		/* --- Symbol entry table for functions ---- */

		/**
		 * 	Desc 	= entry symbol table for function\n
		 * 	Group 	= RKH_TG_FWK\n
		 * 	Id 		= RKH_TE_FWK_FUN\n
		 * 	Args	= function address\n
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
					RKH_TRC_BEGIN( RKH_TE_FWK_FUN, NVS )		\
						RKH_TRC_FUN( __f );								\
						RKH_TRC_STR( __f_n );							\
					RKH_TRC_END();										\
					RKH_TRC_FLUSH();									\
				} while(0)

		/**
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

		#define RKH_TR_FWK_EXE_FUN( function )							\
					RKH_TRC_BEGIN( RKH_TE_FWK_EXE_FUN, NVS )	\
						RKH_TRC_FUN( function );						\
					RKH_TRC_END()
	#else
		#define RKH_TR_FWK_EN()							(void)0
		#define RKH_TR_FWK_EX()							(void)0
		#define RKH_TR_FWK_EPREG( epix, ssize, esize )	(void)0
		#define RKH_TR_FWK_AE( esize, ev )				(void)0
		#define RKH_TR_FWK_GC( ev )						(void)0
		#define RKH_TR_FWK_GCR( ev )					(void)0
		#define RKH_TR_FWK_DEFER( q, ev )				(void)0
		#define RKH_TR_FWK_RCALL( sma, ev )				(void)0
		#define RKH_TR_FWK_OBJ( __o )					(void)0
		#define RKH_TR_FWK_SIG( __s )					(void)0
		#define RKH_TR_FWK_FUN( __s )					(void)0
		#define RKH_TR_FWK_EXE_FUN( __f )				(void)0
	#endif
	
#else
	/* --- Memory Pool (MP) ------------------ */
	#define RKH_TR_MP_INIT( mp, nblock )				(void)0
	#define RKH_TR_MP_GET( mp, nfree )					(void)0
	#define RKH_TR_MP_PUT( mp, nfree )					(void)0

	/* --- Queue (RQ) ------------------------ */
	#define RKH_TR_RQ_INIT( q, nelem, sma )				(void)0
	#define RKH_TR_RQ_GET( q, qty )						(void)0
	#define RKH_TR_RQ_FIFO( q, qty )					(void)0
	#define RKH_TR_RQ_LIFO( q, qty )					(void)0
	#define RKH_TR_RQ_FULL( q )							(void)0
	#define RKH_TR_RQ_DEPLETE( q )						(void)0
	#define RKH_TR_RQ_GET_LAST( q )						(void)0

	/* --- State Machine Application (SMA) --- */
	#define RKH_TR_SMA_ACT( sma )						(void)0
	#define RKH_TR_SMA_TERM( sma )						(void)0
	#define RKH_TR_SMA_GET( sma, ev )					(void)0
	#define RKH_TR_SMA_FIFO( sma, ev )					(void)0
	#define RKH_TR_SMA_LIFO( sma, ev )					(void)0
	#define RKH_TR_SMA_REG( sma, prio )					(void)0
	#define RKH_TR_SMA_UNREG( sma, prio )				(void)0

	/* --- State machine (SM) ---------------- */
	#define RKH_TR_SM_INIT( sma, is )					(void)0
	#define RKH_TR_SM_CLRH( sma, h )					(void)0
	#define RKH_TR_SM_DCH( sma, ev )					(void)0
	#define RKH_TR_SM_TRN( sma, ss, ts )				(void)0
	#define RKH_TR_SM_STATE( sma, s )					(void)0
	#define RKH_TR_SM_ENSTATE( sma, s )					(void)0
	#define RKH_TR_SM_EXSTATE( sma, s )					(void)0
	#define RKH_TR_SM_NENEX( sma, nen, nex )			(void)0
	#define RKH_TR_SM_NTRNACT( sma, nta, nts )			(void)0
	#define RKH_TR_SM_CSTATE( sma, s )					(void)0
	#define RKH_TR_SM_EVT_PROC( sma )					(void)0
	#define RKH_TR_SM_EVT_NFOUND( sma )					(void)0
	#define RKH_TR_SM_GRD_FALSE( sma )					(void)0
	#define RKH_TR_SM_CND_NFOUND( sma )					(void)0
	#define RKH_TR_SM_UNKN_STATE( sma )					(void)0
	#define RKH_TR_SM_EX_HLEVEL( sma )					(void)0
	#define RKH_TR_SM_EX_TSEG( sma )					(void)0

	/* --- Timer (TIM) ----------------------- */
	#define RKH_TR_TIM_INIT( t, sig )					(void)0
	#define RKH_TR_TIM_START( t, nt, sma )				(void)0
	#define RKH_TR_TIM_RESTART( t, nt )					(void)0
	#define RKH_TR_TIM_STOP( t )						(void)0
	#define RKH_TR_TIM_TOUT( t )						(void)0
	#define RKH_TR_TIM_REM( t )							(void)0

	/* --- Framework (RKH) ----------------------- */
	#define RKH_TR_FWK_EN()								(void)0
	#define RKH_TR_FWK_EX()								(void)0
	#define RKH_TR_FWK_EPREG( epix, ssize, esize )		(void)0
	#define RKH_TR_FWK_AE( esize, ev )					(void)0
	#define RKH_TR_FWK_GC( ev )							(void)0
	#define RKH_TR_FWK_GCR( ev )						(void)0
	#define RKH_TR_FWK_DEFER( q, ev )					(void)0
	#define RKH_TR_FWK_RCALL( sma, ev )					(void)0
	#define RKH_TR_FWK_OBJ( __o )						(void)0
	#define RKH_TR_FWK_SIG( __s )						(void)0
	#define RKH_TR_FWK_FUN( __f )						(void)0
	#define RKH_TR_FWK_EXE_FUN( __f )					(void)0
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
 */

void rkh_trc_init( void );


/**
 * 	\brief
 * 	Starts or stops the tracing session. 
 *
 * 	The stream can be in two different states: running (RKH_TRC_START) or 
 * 	suspended (RKH_TRC_STOP). These two states determine whether or not the 
 * 	stream is accepting events to be stored.
 *
 * 	\param opt		control option.
 */

void rkh_trc_control( HUInt opt );


/**
 * 	\brief
 *	Retrieves a pointer to oldest stored byte in the trace stream. 
 *	Frequently, this function is used by the called trace analyzer.
 *
 * \note
 * 	The data is stored in a single ring buffer, called trace stream. In this 
 *	manner the recorder always holds the most recent history.
 *
 * 	\returns
 * 	A pointer to the oldest stored byte if trace stream was not empty, 
 * 	otherwise NULL pointer.
 */

rkhui8_t *rkh_trc_get( void );


/**
 * 	\brief
 * 	Put a data byte into the trace stream. 
 *
 * 	The data is stored in a single ring buffer, called trace stream. In this 
 *	manner the recorder always holds the most recent history.
 */

void rkh_trc_put( rkhui8_t b );


#if RKH_TRC_EN == 1 && RKH_TRC_RUNTIME_FILTER == 1
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
				rkh_trc_filter_group_( FILTER_ON, (grp), ECHANGE );	\
				rkh_trc_filter_event_( FILTER_ON, RKH_TRC_ALL_EVENTS )

	/**
	 * 	\brief
	 * 	Emit (enable) all events in a specific group. 
	 *
	 * 	\note
	 *	The container group is enabled, reglardless of its previous status.
	 */

	#define RKH_FILTER_OFF_GROUP_ALL_EVENTS( grp )			\
				rkh_trc_filter_group_( FILTER_OFF, (grp), ECHANGE );	\
				rkh_trc_filter_event_( FILTER_OFF, RKH_TRC_ALL_EVENTS )

	/**
	 * 	\brief
	 * 	Suppresse the enable trace events from a specified state machine 
	 * 	application, SMA (or active object). 
	 */

	#define RKH_FILTER_ON_SMA( sma )						\
				rkh_trc_filter_sma_( FILTER_ON, (sma)->romrkh->prio )

	/**
	 * 	\brief
	 * 	Emmit the enabled trace events from a specified state machine 
	 * 	application, SMA (or active object). 
	 */

	#define RKH_FILTER_OFF_SMA( sma )						\
				rkh_trc_filter_sma_( FILTER_OFF, (sma)->romrkh->prio )

#else
	#define RKH_FILTER_ON_GROUP( grp ) 				(void)0
	#define RKH_FILTER_OFF_GROUP( grp )				(void)0
	#define RKH_FILTER_ON_EVENT( evt )				(void)0
	#define RKH_FILTER_OFF_EVENT( evt )				(void)0
	#define RKH_FILTER_ON_GROUP_ALL_EVENTS( grp )	(void)0
	#define RKH_FILTER_OFF_GROUP_ALL_EVENTS( grp )	(void)0
	#define RKH_FILTER_ON_SMA( sma )				(void)0
	#define RKH_FILTER_OFF_SMA( sma )				(void)0
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
 * 	Test the state machine application (SMA) filter condition.
 *
 *	\note
 * 	This function is internal to RKH and the user application should not call 
 * 	it.
 *
 * 	\param prio		SMA priority.
 *	
 *	\return
 * 	'1' (TRUE) if the SMA is not filtered, otherwise '0' (FALSE).
 */

HUInt rkh_trc_sma_isoff_( rkhui8_t prio );


/**
 * 	\brief
 * 	Emmit or suppresse all events from a specified state machine 
 * 	application, SMA (AO). 
 *
 * 	The stream is initially created with an empty filter (that is, without 
 * 	filtering any state machine application). 
 *
 * 	Example:
 * 	
 * 	\code
 * 	void 
 * 	some_function( ... )
 * 	{
 * 		RKH_FILTER_ON_SMA( lnmgr );
 * 		RKH_FILTER_OFF_SMA( ledmgr );
 * 		...
 * 	}
 * 	\endcode
 *
 *	\note
 * 	This function is internal to RKH and the user application should not call 
 * 	it. Please use RKH_FILTER_ON_SMA(), or RKH_FILTER_OFF_SMA() macros 
 * 	instead.
 * 
 * 	\param ctrl		filter option, the available options are FILTER_ON or 
 * 					FILTER_OFF.
 * 	\param prio		SMA priority.
 */

void rkh_trc_filter_sma_( rkhui8_t ctrl, rkhui8_t prio );


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
 * 	Store a 8-bit data into the current trace event buffer.
 *
 * 	\param d		data
 */

void rkh_trc_ui8( rkhui8_t d );


/**
 * 	\brief
 * 	Store a 16-bit data into the current trace event buffer.
 *
 * 	\param d		data
 */

void rkh_trc_ui16( rkhui16_t d );


/**
 * 	\brief
 * 	Store a 32-bit data into the current trace event buffer.
 *
 * 	\param d		data
 */

void rkh_trc_ui32( rkhui32_t d );


/**
 * 	\brief
 * 	Store a string terminated in '\\0' into the current trace event buffer.
 *
 * 	\param s		pointer to string treminated in '\\0'
 */

void rkh_trc_str( const char *s );


#endif
