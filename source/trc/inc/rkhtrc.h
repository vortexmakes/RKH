/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       rkhtrc.h
 *  \brief      Specifies the interface of trace facility.
 *
 *  <EM>RKH trace event structure</EM>
 *
 *	\code
 *	(1) RKH_TRC_BEGIN(trc_evt, ao_prio, signal)	\
 *	(2)		RKH_TRC_ARG0(arg0);                   \
 *	(3)		RKH_TRC_ARG1(arg1);                   \
 *	(4)		RKH_TRC_....(...);                    \
 *	(5)	RKH_TRC_END()
 *	\endcode
 *
 *	\li (1,5)	Each trace event always begins with the macro 
 *	            RKH_TRC_BEGIN() and ends with the matching macro 
 *	            RKH_TRC_END(). These macros are not terminated with the 
 *	            semicolon. The record-begin macro RKH_TRC_BEGIN() takes 
 *	            three arguments.
 *			    The first argument 'trc_evt' is the trace event ID, the
 *			    second argument 'ao_prio' is the active object priority,
 *			    and the third argument 'signal' is the event signal number.
 *			    These arguments are used in the on/off filters.
 *			    The runtime filter is optional and could be enabled or
 *			    disabled with the #RKH_CFG_TRC_RTFIL_EN in the
 *			    \b rkhcfg.h file. This pair of macros locks interrupts at
 *			    the beginning and unlocks at the end of each record.
 *	\li (2-4)   Sandwiched between these two macros are the
 *				argument-generating macros that actually insert individual
 *				event argument elements into the trace stream.
 *
 *  Example:
 *
 *	\code
 *	#define RKH_TR_QUE_INIT(q, ao, nelem) \
 *				RKH_TRC_BEGIN_WOAOSIG(RKH_TE_QUE_INITS) \
 *					RKH_TRC_SYM(q); \
 *					RKH_TRC_SYM(ao); \
 *					RKH_TRC_NE(nelem); \
 *				RKH_TRC_END()
 *
 *  #define RKH_TR_SMA_FIFO(actObj_, evt_, sender_, poolID_, refCntr_, \
 *                          nElem_, nMin_) \
 *      RKH_TRC_BEGIN_NOCRIT(RKH_TE_SMA_FIFO, \
 *                           RKH_SMA_ACCESS_CONST(actObj_, prio), \
 *                          (evt_)->e) \
 *          RKH_TRC_SYM(actObj_); \
 *          RKH_TRC_SIG((evt_)->e); \
 *          RKH_TRC_SNDR(sender_); \
 *          RKH_TRC_UI8(poolID_); \
 *          RKH_TRC_UI8(refCntr_); \
 *          RKH_TRC_NE(nElem_); \
 *          RKH_TRC_QUE_NMIN(nMin_); \
 *      RKH_TRC_END_NOCRIT()
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
 *  \code
 *      | ...               |
 *  (1) | event ID          | 1,2,4-byte
 *  (2) | sequence number   | 1-byte
 *  (3) | timestamp         | 2,4-bytes
 *  (4) | args              | n-byte
 *  (5) | checksum          | 1-byte
 *  (6) | flag              | 1-byte
 *      | ...               |
 *	\endcode
 *
 *	-   (1) Each frame starts with the <B>trace event ID</B> bytes, which is
 *		one of the predefined RKH records or an application-specific record.
 *	-   (2) Following the <B>sequence number</B> is the sequence number 
 *	        byte.
 *		    The target component increments this number for every frame 
 *		    inserted into the stream. The sequence number allows the 
 *		    trazer tool to detect any data discontinuities. If the 
 *		    #RKH_CFG_TRC_NSEQ_EN is set to 1 then RKH will add to the 
 *		    trace record the sequence number.
 *	-	(3) Following the sequence number is the <B>timestamp</B>. The 
 *	        number of bytes used by the timestamp is configurable by the 
 *	        macro #RKH_CFGPORT_TRC_SIZEOF_TSTAMP.
 *		    If the #RKH_CFG_TRC_TSTAMP_EN is set to 1 then RKH will add to 
 *		    the trace record the timestamp field.
 *	-   (4) Following the timestamp is zero or more data bytes for
 *		    <B>args</B>.
 *	-   (5) Following the data is the <B>checksum</B> byte. The checksum is
 *		computed over the sequence number, the trace event ID, and all the
 *		data bytes.
 *		If the #RKH_CFG_TRC_CHK_EN is set to 1 then RKH will add to the 
 *		trace record a checksum byte.
 *	-   (6) Following the checksum is the <B>flag</B> byte, which delimits
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
 *  <em>User trace events</em>
 *
 *  The user application could defined its own trace events to be placed
 *  at anywhere in the application level. Allowing to generate tracing
 *  information from the application-level code like a "printf" but with
 *  much less overhead.
 *
 *	\code
 *	(1) RKH_TRC_USR_BEGIN(MY_TRACE)	\
 *	(2)		RKH_TRC_ARG0(arg0); \
 *	(3)		RKH_TRC_ARG1(arg1); \
 *	(4)		RKH_TRC_....(...); \
 *	(5)	RKH_TRC_USR_END();
 *	\endcode
 *
 *	\li (1,5)	Each trace event always begins with the macro
 *				RKH_TRC_USR_BEGIN() and ends with the matching macro
 *				RKH_TRC_USR_END(). The record-begin macro 
 *				RKH_TRC_USR_BEGIN() takes one argument, 'eid_' is the 
 *				user trace event ID, from the RKH_TE_USER value. This pair 
 *				of macros locks interrupts at the beginning and unlocks at 
 *				the end of each record.
 *	\li (2-4)   Sandwiched between these two macros are the
 *				argument-generating macros that actually insert individual
 *				event argument elements into the trace stream.
 *
 *	Argument-generating macros for building user trace events:
 *
 *	\li RKH_TUSR_I8()   \copydoc RKH_TUSR_I8
 *	\li RKH_TUSR_UI8()  \copydoc RKH_TUSR_UI8
 *	\li RKH_TUSR_I16()  \copydoc RKH_TUSR_I16
 *	\li RKH_TUSR_UI16() \copydoc RKH_TUSR_UI16
 *	\li RKH_TUSR_I32()  \copydoc RKH_TUSR_I32
 *	\li RKH_TUSR_UI32() \copydoc RKH_TUSR_UI32
 *	\li RKH_TUSR_X32()  \copydoc RKH_TUSR_X32
 *	\li RKH_TUSR_STR()  \copydoc RKH_TUSR_STR
 *	\li RKH_TUSR_MEM()  \copydoc RKH_TUSR_MEM
 *	\li RKH_TUSR_OBJ()  \copydoc RKH_TUSR_OBJ
 *	\li RKH_TUSR_FUN()  \copydoc RKH_TUSR_FUN
 *	\li RKH_TUSR_SIG()  \copydoc RKH_TUSR_SIG
 *
 *  Example:
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
 *	some_function(...)
 *	{
 *		rui8_t d1 = 255;
 *		rui16_t d2 = 65535;
 *		rui32_t d3 = 65535;
 *		char *str = "hello";
 *
 *		RKH_TRC_USR_BEGIN(LOWPWR_USR_TRACE)
 *			RKH_TUSR_I8(3, d1);
 *			RKH_TUSR_UI8(3, d1);
 *			RKH_TUSR_I16(4, d2);
 *			RKH_TUSR_UI16(4, d2);
 *			RKH_TUSR_I32(5, d3);
 *			RKH_TUSR_UI32(5, d3);
 *			RKH_TUSR_X32(4, d3);
 *			RKH_TUSR_STR(str);
 *			RKH_TUSR_MEM((rui8_t*)&d3, sizeof(rui32_t));
 *			RKH_TUSR_OBJ(my);
 *			RKH_TUSR_FUN(main);
 *			RKH_TUSR_SIG(ZERO);
 *		RKH_TRC_USR_END();
 *	}
 *	\endcode
 *
 *	\sa RKH_TRC_END()
 *  \ingroup    apiTrc
 *
 *  \addtogroup api
 *  @{
 *  \addtogroup apiTrc Trace
 *  @{@}
 *  @}
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHTRC_H__
#define __RKHTRC_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtrc_record.h"
#include "rkhtrc_filter.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
    extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */

#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */

#endif

/* ------------------------------ End of file ------------------------------ */
