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
 *  \brief      Platform - independent interface for RKH trace facility.
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
 *	#define RKH_TR_RQ_INIT(q, ao, nelem) \
 *				RKH_TRC_BEGIN_WOAOSIG(RKH_TE_RQ_INITS) \
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
 *          RKH_TRC_NE(nMin_); \
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
#include "rkhcfg.h"
#include "rkhtype.h"
#include "rkhplat.h"
#include "rkhevt.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
    extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/**
 *  \brief
 * 	Specify the size of the trace event identification. The valid values 
 * 	[in bits] are 8, 16 or 32. Default is 8. 
 *
 * 	\sa #RKH_TE_ID_T data type.
 *
 *  \note In the future releases, it should be defined in the configuration 
 *  file of the RKH framework.
 */
#define RKH_CFG_TRC_SIZEOF_TE_ID        8

#if RKH_CFG_TRC_SIZEOF_TE_ID == 8
        #define RKH_TRC_TE_ID(teid) \
            RKH_TRC_UI8(teid)
#elif RKH_CFG_TRC_SIZEOF_TE_ID == 16
        #define RKH_TRC_TE_ID(teid) \
            RKH_TRC_UI16(teid)
#elif RKH_CFG_TRC_SIZEOF_TE_ID == 32
        #define RKH_TRC_TE_ID(teid) \
            RKH_TRC_UI32(teid)
#else
        #define RKH_TRC_TE_ID(teid) \
            RKH_TRC_UI8(teid)
#endif

#if RKH_CFG_TRC_EN == RKH_ENABLED && \
        RKH_CFG_TRC_RTFIL_EN == RKH_ENABLED
        /**
         *  \brief
         *  Suppress the enabled trace events from a specific group.
         *  Use the RKH_TRC_ALL_GROUPS to disable all groups.
         *
         *  \ingroup apiTrc 
         */
        #define RKH_FILTER_ON_GROUP(grp) \
            rkh_trc_filter_group_(FILTER_ON, (grp), EUNCHANGE)

        /**
         *  \brief
         *  Emit the enabled trace events from a specific group.
         *  Use the RKH_TRC_ALL_GROUPS to enable all groups.
         *
         *  \ingroup apiTrc 
         */
        #define RKH_FILTER_OFF_GROUP(grp) \
            rkh_trc_filter_group_(FILTER_OFF, (grp), EUNCHANGE)

        /**
         *  \brief
         *  Suppress (disable) one trace event.
         *  Use the RKH_TRC_ALL_EVENTS to disable all trace events.
         *
         *  \ingroup apiTrc 
         */
        #define RKH_FILTER_ON_EVENT(evt) \
            rkh_trc_filter_event_(FILTER_ON, (evt))

        /**
         *  \brief
         *  Emit (enable) one trace event.
         *  Use the RKH_TRC_ALL_EVENTS to enable all trace events.
         *
         *  \note
         *	The container group is enabled, reglardless of its previous status.
         *
         *  \ingroup apiTrc 
         */
        #define RKH_FILTER_OFF_EVENT(evt) \
            rkh_trc_filter_event_(FILTER_OFF, (evt))

        /**
         *  \brief
         *  Suppress (disable) all events in a specific group.
         *
         *  \ingroup apiTrc 
         */
        #define RKH_FILTER_ON_GROUP_ALL_EVENTS(grp) \
            rkh_trc_filter_group_(FILTER_ON, (grp), ECHANGE)

        /**
         *  \brief
         *  Emit (enable) all events in a specific group.
         *
         *  \note
         *	The container group is enabled, reglardless of its previous status.
         *
         *  \ingroup apiTrc 
         */
        #define RKH_FILTER_OFF_GROUP_ALL_EVENTS(grp) \
            rkh_trc_filter_group_(FILTER_OFF, (grp), ECHANGE)

        #if RKH_CFG_TRC_RTFIL_SMA_EN == RKH_ENABLED

        /**
         *  \brief
         *  Suppress the enable trace events related to a specified active
         *  object.
         *
         *  \ingroup apiTrc 
         */
            #define RKH_FILTER_ON_SMA(sma) \
                rkh_trc_symFil(&fsma, RKH_SMA_ACCESS_CONST(sma, prio), \
                               FILTER_ON)

        /**
         *  \brief
         *  Suppress all enabled trace events related to active objects.
         *
         *  \ingroup apiTrc 
         */
            #define RKH_FILTER_ON_ALL_SMA() \
                rkh_trc_symFil(&fsma, 0, RKH_TRC_SET_ALL(FILTER_ON))

        /**
         *  \brief
         *  Emmit the enabled trace events related to a specified active
         *  object.
         *
         *  \ingroup apiTrc 
         */
            #define RKH_FILTER_OFF_SMA(sma) \
                rkh_trc_symFil(&fsma, RKH_SMA_ACCESS_CONST(sma, prio), \
                               FILTER_OFF)

        /**
         *  \brief
         *  Emmit all enabled trace events related to active objects.
         *
         *  \ingroup apiTrc 
         */
            #define RKH_FILTER_OFF_ALL_SMA() \
                rkh_trc_symFil(&fsma, 0, RKH_TRC_SET_ALL(FILTER_OFF))

        #else
            #define RKH_FILTER_ON_SMA(sma)          (void)0
            #define RKH_FILTER_ON_ALL_SMA()         (void)0
            #define RKH_FILTER_OFF_SMA(sma)         (void)0
            #define RKH_FILTER_OFF_ALL_SMA()        (void)0
        #endif

        #if RKH_CFG_TRC_RTFIL_SIGNAL_EN == RKH_ENABLED
        /**
         *  \brief
         *  Suppress the enabled trace events related to a specified event
         *  signal.
         *
         *  \ingroup apiTrc 
         */
            #define RKH_FILTER_ON_SIGNAL(sig) \
                rkh_trc_symFil(&fsig, (sig), FILTER_ON)

        /**
         *  \brief
         *  Suppress all enabled trace events related to signals.
         *
         *  \ingroup apiTrc 
         */
            #define RKH_FILTER_ON_ALL_SIGNALS() \
                rkh_trc_symFil(&fsig, 0, RKH_TRC_SET_ALL(FILTER_ON))

        /**
         *  \brief
         *  Emmit the enabled trace events related to a specified event
         *  signal.
         *
         *  \ingroup apiTrc 
         */
            #define RKH_FILTER_OFF_SIGNAL(sig) \
                rkh_trc_symFil(&fsig, (sig), FILTER_OFF)

        /**
         *  \brief
         *  Emmit all enabled trace events related to signals.
         *
         *  \ingroup apiTrc 
         */
            #define RKH_FILTER_OFF_ALL_SIGNALS() \
                rkh_trc_symFil(&fsig, 0, RKH_TRC_SET_ALL(FILTER_OFF))
        #else
            #define RKH_FILTER_ON_SIGNAL(sig)       (void)0
            #define RKH_FILTER_ON_ALL_SIGNALS()     (void)0
            #define RKH_FILTER_OFF_SIGNAL(sig)      (void)0
            #define RKH_FILTER_OFF_ALL_SIGNALS()    (void)0
        #endif
#else
        #define RKH_FILTER_ON_GROUP(grp)                (void)0
        #define RKH_FILTER_OFF_GROUP(grp)               (void)0
        #define RKH_FILTER_ON_EVENT(evt)                (void)0
        #define RKH_FILTER_OFF_EVENT(evt)               (void)0
        #define RKH_FILTER_ON_GROUP_ALL_EVENTS(grp)     (void)0
        #define RKH_FILTER_OFF_GROUP_ALL_EVENTS(grp)    (void)0
        #define RKH_FILTER_ON_SMA(sma)                  (void)0
        #define RKH_FILTER_ON_ALL_SMA()                 (void)0
        #define RKH_FILTER_OFF_SMA(sma)                 (void)0
        #define RKH_FILTER_OFF_ALL_SMA()                (void)0
        #define RKH_FILTER_ON_SIGNAL(sig)               (void)0
        #define RKH_FILTER_ON_ALL_SIGNALS()             (void)0
        #define RKH_FILTER_OFF_SIGNAL(sig)              (void)0
        #define RKH_FILTER_OFF_ALL_SIGNALS()            (void)0
#endif

/**
 *  \brief
 *  Test the state machine application (SMA) filter condition.
 *
 *  \param[in] prio		SMA priority.
 *
 *	\return
 *  '1' (RKH_TRUE) if the SMA is not filtered, otherwise '0' (RKH_FALSE).
 *
 *	\note
 *  This macro is internal to RKH and the user application should not call
 *  it.
 */
#if RKH_CFG_TRC_RTFIL_SMA_EN == RKH_ENABLED
    #define RKH_TRC_AO_ISOFF(prio) \
            && rkh_trc_symFil_isoff(&fsma, (RKH_TRC_FSLOT)(prio))
#else
    #define RKH_TRC_AO_ISOFF(prio)
#endif

/**
 *  \brief
 *  Test the event signal filter condition.
 *
 *  \param[in] sig		event signal.
 *
 *	\return
 *  '1' (RKH_TRUE) if the signal is not filtered, otherwise '0' (RKH_FALSE).
 *
 *	\note
 *  This macro is internal to RKH and the user application should not call
 *  it.
 */
#if RKH_CFG_TRC_RTFIL_SIGNAL_EN == RKH_ENABLED
    #define RKH_TRC_SIG_ISOFF(sig) \
            && rkh_trc_symFil_isoff(&fsig, (RKH_TRC_FSLOT)(sig))
#else
    #define RKH_TRC_SIG_ISOFF(sig)
#endif

/* -------------------------------- Constants ------------------------------ */
#if RKH_CFG_TRC_SIZEOF_TE_ID == 8
        #define RKH_NBITS_GROUP             3
#elif RKH_CFG_TRC_SIZEOF_TE_ID == 16
        #define RKH_NBITS_GROUP             8
#elif RKH_CFG_TRC_SIZEOF_TE_ID == 32
        #define RKH_NBITS_GROUP             8
#else
        #define RKH_NBITS_GROUP             3
#endif

#define RKH_NBIT_EVENT_PER_GROUP   (RKH_CFG_TRC_SIZEOF_TE_ID - \
                                        RKH_NBITS_GROUP)
#define RKH_TRC_MAX_GROUPS          RKH_BIT(RKH_NBITS_GROUP)
#define RKH_MAX_NUM_TE_PER_GROUP    RKH_BIT(RKH_NBIT_EVENT_PER_GROUP)
#define NGSH                        RKH_NBIT_EVENT_PER_GROUP
#define RKH_GRP_MASK \
        (RKH_TE_ID_T)((RKH_BIT(RKH_NBITS_GROUP) - 1) << \
                       RKH_NBIT_EVENT_PER_GROUP)
#define RKH_TE_MASK \
        (RKH_TE_ID_T)(RKH_BIT(RKH_NBIT_EVENT_PER_GROUP) - 1)

/**
 *	Specify the maximum number of trace events, this number is direclty
 *	related with the RKH_TE_<group>_<event> definitions. The smaller this 
 *	number, the lower the RAM consumption.
 *	See \c trceftbl table.
 */
#define RKH_TRC_MAX_EVENTS \
        (RKH_MAX_NUM_TE_PER_GROUP * RKH_TRC_MAX_GROUPS)

#if ((RKH_CFG_FWK_MAX_SMA & (8 - 1)) == 0)
        /**
         *  \brief
         *  The size of trcsmaftbl[] (trace SMA filter table) depends on
         *  #RKH_CFG_FWK_MAX_SMA (see rkhcfg.h).
         */
        #define RKH_TRC_MAX_SMA     (RKH_CFG_FWK_MAX_SMA / 8)
#else
        #define RKH_TRC_MAX_SMA     (RKH_CFG_FWK_MAX_SMA / 8 + 1)
#endif

#if ((RKH_CFG_FWK_MAX_SIGNALS & (8 - 1)) == 0)
        /**
         *  \brief
         *  The size of trcsigftbl[] (trace signal filter table) depends on
         *  #RKH_CFG_FWK_MAX_SIGNALS and #RKH_CFG_FWK_SIZEOF_EVT (see rkhcfg.h).
         */
        #define RKH_TRC_MAX_SIGNALS (RKH_CFG_FWK_MAX_SIGNALS / 8)
#else
        #define RKH_TRC_MAX_SIGNALS (RKH_CFG_FWK_MAX_SIGNALS / 8 + 1)
#endif

/**@{
 *
 *  \brief
 *  Trace event offset.
 *
 *  The trace event ID is arranged as:
 *
 *  event number = | G | G | G | E | E | E | E | E |\n
 *
 *  G's:	group number.\n
 *  E's:	event's group.\n
 *
 *  The lower 5 bits (E's) of the event ID are used to determine
 *  the trace event, while the next three most significant bits
 *  (G's) are used to determine the corresponding group.
 *  Therefore, is able to define 8 groups and 32 events per group.
 */
#define RKH_MP_START                GRPLSH(RKH_TG_MP)
#define RKH_RQ_START                GRPLSH(RKH_TG_RQ)
#define RKH_SMA_START               GRPLSH(RKH_TG_SMA)
#define RKH_SM_START                GRPLSH(RKH_TG_SM)
#define RKH_TMR_START               GRPLSH(RKH_TG_TMR)
#define RKH_FWK_START               GRPLSH(RKH_TG_FWK)
#define RKH_USR_START               GRPLSH(RKH_TG_USR)
#define RKH_UT_START                GRPLSH(RKH_TG_UT)
/*@}*/

/**@{
 *  Max. number of used trace events in a particular group in octets, thus
 *  the desired value must be divided by 8 (1 -> 8 events).
 *  \note
 *  Must be less than or equal to RKH_MAX_NUM_TE_PER_GROUP/8.
 */
#define RKH_MP_TTBL_RANGE           1
#define RKH_RQ_TTBL_RANGE           1
#define RKH_SMA_TTBL_RANGE          1
#define RKH_SM_TTBL_RANGE           3
#define RKH_TIM_TTBL_RANGE          1
#define RKH_FWK_TTBL_RANGE          3
#define RKH_USR_TTBL_RANGE          4
#define RKH_UT_TTBL_RANGE           2
/*@}*/

/**
 *  Defines the total number of trace events.
 */
#define RKH_TOT_NUM_TRC_EVTS \
        (RKH_MP_TTBL_RANGE   + \
         RKH_RQ_TTBL_RANGE   + \
         RKH_SMA_TTBL_RANGE  + \
         RKH_SM_TTBL_RANGE   + \
         RKH_TIM_TTBL_RANGE  + \
         RKH_FWK_TTBL_RANGE  + \
         RKH_USR_TTBL_RANGE  + \
         RKH_UT_TTBL_RANGE)

/**
 *  \brief
 *  Defines the size of trace filter table according to RKH_TOT_NUM_TRC_EVTS
 *  and RKH_TRC_MAX_EVENTS.
 */
#if (RKH_TOT_NUM_TRC_EVTS <= RKH_TOT_NUM_TRC_EVTS)
        #define RKH_TRC_MAX_EVENTS_IN_BYTES     RKH_TOT_NUM_TRC_EVTS
#else
        #error  "rkhtrc.h, the total number of trace events represented"
        #error  "by RKH_TOT_NUM_TRC_EVTS must be <= RKH_TRC_MAX_EVENTS"
#endif

#define RKH_MP_TTBL_OFFSET          0
#define RKH_RQ_TTBL_OFFSET          (RKH_MP_TTBL_OFFSET + RKH_MP_TTBL_RANGE)
#define RKH_SMA_TTBL_OFFSET         (RKH_RQ_TTBL_OFFSET + RKH_RQ_TTBL_RANGE)
#define RKH_SM_TTBL_OFFSET          (RKH_SMA_TTBL_OFFSET + RKH_SMA_TTBL_RANGE)
#define RKH_TIM_TTBL_OFFSET         (RKH_SM_TTBL_OFFSET + RKH_SM_TTBL_RANGE)
#define RKH_FWK_TTBL_OFFSET         (RKH_TIM_TTBL_OFFSET + RKH_TIM_TTBL_RANGE)
#define RKH_USR_TTBL_OFFSET         (RKH_FWK_TTBL_OFFSET + RKH_FWK_TTBL_RANGE)
#define RKH_UT_TTBL_OFFSET          (RKH_USR_TTBL_OFFSET + RKH_USR_TTBL_RANGE)

#define GRPLSH(grp) \
        /*(RKH_TE_ID_T)(((grp) & (rui8_t)(RKH_TRC_MAX_GROUPS - 1)) << NGSH)*/ \
        (((grp) & (RKH_TRC_MAX_GROUPS - 1)) << NGSH)

#define EXTE(te, grp) \
        (RKH_TE_ID_T)((te) - GRPLSH(grp))

#define GETGRP(e) \
        (RKH_TG_T)(((e) & RKH_GRP_MASK) >> RKH_NBIT_EVENT_PER_GROUP)
#define GETEVT(e) \
        (RKH_TE_ID_T)((e) & RKH_TE_MASK)

#define ECHANGE                     0
#define EUNCHANGE                   1

#if (((RKH_CFG_TRC_EN == 1) && (RKH_CFG_SMA_TRC_SNDR_EN == 1)) || \
         (defined(RKH_EN_DOXYGEN) && RKH_EN_DOXYGEN == 1))
        /**
         *  \brief
         *  This macro is used to verify the sender object usage on post an 
         *  event.
         *
         *  The macros RKH_TIM_TICK(), RKH_SMA_POST_FIFO(), and
         *  RKH_SMA_POST_LIFO() takes an additional argument \a sender, which 
         *  is a pointer to the sender object. This argument is actually only 
         *  used when software tracing is enabled (macro #RKH_USE_TRC_SENDER is
         *  defined).
         *  When software tracing is disabled, the macros RKH_TIM_TICK(),
         *  RKH_SMA_POST_FIFO(), and RKH_SMA_POST_LIFO() calls rkh_tmr_tick(),
         *  rkh_sma_post_fifo(), and rkh_sma_post_lifo() respectively without 
         *  any arguments, so the overhead of passing this extra argument is 
         *  entirely avoided.
         */
        #define RKH_USE_TRC_SENDER
#endif

/**
 *  \brief
 *  Emit or suppress tracing for all groups and events.
 */
#define RKH_TRC_ALL_GROUPS      RKH_TG_NGROUP

/**
 *  \brief
 *  Emit or suppress all trace events.
 */
#define RKH_TRC_ALL_EVENTS      RKH_TE_NEVENT

/**
 *  \brief
 *  Emit or supress tracing for all signal/active objects.
 */
#define RKH_TRC_SET_ALL(mode_) \
        ((mode_) | RKH_TRC_ALL_FILTERS)

#define RKH_TRC_ALL_FILTERS     0x80
#define RKH_FILTER_MODE_MASK    ~RKH_TRC_ALL_FILTERS

/** x-ored byte for stuffing a single byte */
#define RKH_XOR     0x20

/** flag byte, used as a trace event delimiter */
#define RKH_FLG     0x7E

/** escape byte stuffing a single byte */
#define RKH_ESC     0x7D

/* --- RKH group of trace events ------------------------------------------- */
/** \brief  Memory Pool group (MP) */
#define RKH_TG_MP           0

/** \brief  Reference Queue group (RQ) */
#define RKH_TG_RQ           1

/** \brief  State Machine Application group (SMA) */
#define RKH_TG_SMA          2

/** \brief  State Machine group (SM) */
#define RKH_TG_SM           3

/** \brief  Timer group (TIM) */
#define RKH_TG_TMR          4

/** \brief  Framework RKH group (FWK) */
#define RKH_TG_FWK          5

/** \brief  User group (USR) */
#define RKH_TG_USR          6

/** \brief  Unit test harness group (UT) */
#define RKH_TG_UT           7

/** \brief  Number of trace groups */
#define RKH_TG_NGROUP       8

/* --- Memory Pool events (MP group) --------------------------------------- */
/** \copybrief RKH_TR_MP_INIT */
#define RKH_TE_MP_INIT          RKH_MP_START
/** \copybrief RKH_TR_MP_GET */
#define RKH_TE_MP_GET           (RKH_TE_MP_INIT + 1)
/** \copybrief RKH_TR_MP_PUT */
#define RKH_TE_MP_PUT           (RKH_TE_MP_GET + 1)
#define RKH_MP_END              RKH_TE_MP_PUT

/* --- Queue events (RQ group) --------------------------------------------- */
/** \copybrief RKH_TR_RQ_INIT */
#define RKH_TE_RQ_INIT          RKH_RQ_START         
/** \copybrief RKH_TR_RQ_GET */
#define RKH_TE_RQ_GET           (RKH_TE_RQ_INIT + 1)
/** \copybrief RKH_TR_RQ_FIFO */
#define RKH_TE_RQ_FIFO          (RKH_TE_RQ_GET + 1)
/** \copybrief RKH_TR_RQ_LIFO */
#define RKH_TE_RQ_LIFO          (RKH_TE_RQ_FIFO + 1)
/** \copybrief RKH_TR_RQ_FULL */
#define RKH_TE_RQ_FULL          (RKH_TE_RQ_LIFO + 1)
/** \copybrief RKH_TR_RQ_DPT */
#define RKH_TE_RQ_DPT           (RKH_TE_RQ_FULL + 1)
/** \copybrief RKH_TR_RQ_GET_LAST */
#define RKH_TE_RQ_GET_LAST      (RKH_TE_RQ_DPT +1 )
#define RKH_RQ_END              RKH_TE_RQ_GET_LAST

/* --- State Machine Application events (SMA group) ------------------------ */
/** \copybrief RKH_TR_SMA_ACT */
#define RKH_TE_SMA_ACT          RKH_SMA_START
/** \copybrief RKH_TR_SMA_TERM */
#define RKH_TE_SMA_TERM         (RKH_TE_SMA_ACT + 1)
/** \copybrief RKH_TR_SMA_GET */
#define RKH_TE_SMA_GET          (RKH_TE_SMA_TERM + 1)
/** \copybrief RKH_TR_SMA_FIFO */
#define RKH_TE_SMA_FIFO         (RKH_TE_SMA_GET + 1)
/** \copybrief RKH_TR_SMA_LIFO */
#define RKH_TE_SMA_LIFO         (RKH_TE_SMA_FIFO + 1)
/** \copybrief RKH_TR_SMA_REG */
#define RKH_TE_SMA_REG          (RKH_TE_SMA_LIFO + 1)
/** \copybrief RKH_TR_SMA_UNREG */
#define RKH_TE_SMA_UNREG        (RKH_TE_SMA_REG + 1)
/** \copybrief RKH_TR_SMA_DCH */
#define RKH_TE_SMA_DCH          (RKH_TE_SMA_UNREG + 1)
#define RKH_SMA_END             RKH_TE_SMA_DCH

/* --- State machine events (SM group) ------------------------------------- */
/** \copybrief RKH_TR_SM_INIT */
#define RKH_TE_SM_INIT          RKH_SM_START
/** \copybrief RKH_TR_SM_CLRH */
#define RKH_TE_SM_CLRH          (RKH_TE_SM_INIT + 1)
/** \copybrief RKH_TR_SM_TRN */
#define RKH_TE_SM_TRN           (RKH_TE_SM_CLRH + 1)
/** \copybrief RKH_TR_SM_STATE */
#define RKH_TE_SM_STATE         (RKH_TE_SM_TRN + 1)
/** \copybrief RKH_TR_SM_ENSTATE */
#define RKH_TE_SM_ENSTATE       (RKH_TE_SM_STATE + 1)
/** \copybrief RKH_TR_SM_EXSTATE */
#define RKH_TE_SM_EXSTATE       (RKH_TE_SM_ENSTATE + 1)
/** \copybrief RKH_TR_SM_NENEX */
#define RKH_TE_SM_NENEX         (RKH_TE_SM_EXSTATE + 1)
/** \copybrief RKH_TR_SM_NTRNACT */
#define RKH_TE_SM_NTRNACT       (RKH_TE_SM_NENEX + 1)
/** \copybrief RKH_TR_SM_TS_STATE */
#define RKH_TE_SM_TS_STATE      (RKH_TE_SM_NTRNACT + 1)
/** \copybrief RKH_TR_SM_EVT_PROC */
#define RKH_TE_SM_EVT_PROC      (RKH_TE_SM_TS_STATE + 1)
/** \copybrief RKH_TR_SM_EVT_NFOUND */
#define RKH_TE_SM_EVT_NFOUND    (RKH_TE_SM_EVT_PROC + 1)
/** \copybrief RKH_TR_SM_GRD_FALSE */
#define RKH_TE_SM_GRD_FALSE     (RKH_TE_SM_EVT_NFOUND + 1)
/** \copybrief RKH_TR_SM_CND_NFOUND */
#define RKH_TE_SM_CND_NFOUND    (RKH_TE_SM_GRD_FALSE + 1)
/** \copybrief RKH_TR_SM_UNKN_STATE */
#define RKH_TE_SM_UNKN_STATE    (RKH_TE_SM_CND_NFOUND + 1)
/** \copybrief RKH_TR_SM_EX_HLEVEL */
#define RKH_TE_SM_EX_HLEVEL     (RKH_TE_SM_UNKN_STATE + 1)
/** \copybrief RKH_TR_SM_EX_TSEG */
#define RKH_TE_SM_EX_TSEG       (RKH_TE_SM_EX_HLEVEL + 1)
/** \copybrief RKH_TR_SM_EXE_ACT */
#define RKH_TE_SM_EXE_ACT       (RKH_TE_SM_EX_TSEG + 1)
#define RKH_SM_END              RKH_TE_SM_EXE_ACT

/* --- Timer events (TMR group) -------------------------------------------- */
/** \copybrief RKH_TR_TMR_INIT */
#define RKH_TE_TMR_INIT         RKH_TMR_START
/** \copybrief RKH_TR_TMR_START */
#define RKH_TE_TMR_START        (RKH_TE_TMR_INIT + 1)
/** \copybrief RKH_TR_TMR_STOP */
#define RKH_TE_TMR_STOP         (RKH_TE_TMR_START + 1)
/** \copybrief RKH_TR_TMR_TOUT */
#define RKH_TE_TMR_TOUT         (RKH_TE_TMR_STOP + 1)
/** \copybrief RKH_TR_TMR_REM */
#define RKH_TE_TMR_REM          (RKH_TE_TMR_TOUT + 1)
#define RKH_TMR_END             RKH_TE_TMR_REM

/* --- Framework and misc. events (FWK group) ------------------------------ */
/** \copybrief RKH_TR_FWK_EN */
#define RKH_TE_FWK_EN           RKH_FWK_START
/** \copybrief RKH_TR_FWK_EX */
#define RKH_TE_FWK_EX           (RKH_TE_FWK_EN + 1)
/** \copybrief RKH_TR_FWK_EPREG */
#define RKH_TE_FWK_EPREG        (RKH_TE_FWK_EX + 1)
/** \copybrief RKH_TR_FWK_AE */
#define RKH_TE_FWK_AE           (RKH_TE_FWK_EPREG + 1)
/** \copybrief RKH_TR_FWK_GC */
#define RKH_TE_FWK_GC           (RKH_TE_FWK_AE + 1)
/** \copybrief RKH_TR_FWK_GCR */
#define RKH_TE_FWK_GCR          (RKH_TE_FWK_GC + 1)
/** \copybrief RKH_TR_FWK_DEFER */
#define RKH_TE_FWK_DEFER        (RKH_TE_FWK_GCR + 1)
/** \copybrief RKH_TR_FWK_RCALL */
#define RKH_TE_FWK_RCALL        (RKH_TE_FWK_DEFER + 1)
/** \copybrief RKH_TR_FWK_OBJ */
#define RKH_TE_FWK_OBJ          (RKH_TE_FWK_RCALL + 1)
/** \copybrief RKH_TR_FWK_SIG */
#define RKH_TE_FWK_SIG          (RKH_TE_FWK_OBJ + 1)
/** \copybrief RKH_TR_FWK_FUN */
#define RKH_TE_FWK_FUN          (RKH_TE_FWK_SIG + 1)
/** \copybrief RKH_TR_FWK_EXE_FUN */
#define RKH_TE_FWK_EXE_FUN      (RKH_TE_FWK_FUN + 1)
/** \copybrief RKH_TR_FWK_SYNC_EVT */
#define RKH_TE_FWK_SYNC_EVT     (RKH_TE_FWK_EXE_FUN + 1)
/** \copybrief RKH_TR_FWK_TUSR */
#define RKH_TE_FWK_TUSR         (RKH_TE_FWK_SYNC_EVT + 1)
/** \copybrief RKH_TR_FWK_TCFG */
#define RKH_TE_FWK_TCFG         (RKH_TE_FWK_TUSR + 1)
/** \copybrief RKH_TR_FWK_ASSERT */
#define RKH_TE_FWK_ASSERT       (RKH_TE_FWK_TCFG + 1)
/** \copybrief RKH_TR_FWK_AO */
#define RKH_TE_FWK_AO           (RKH_TE_FWK_ASSERT + 1)
/** \copybrief RKH_TR_FWK_STATE */
#define RKH_TE_FWK_STATE        (RKH_TE_FWK_AO + 1)
/** \copybrief RKH_TR_FWK_PSTATE */
#define RKH_TE_FWK_PSTATE       (RKH_TE_FWK_STATE + 1)
/** \copybrief RKH_TR_FWK_TIMER */
#define RKH_TE_FWK_TIMER        (RKH_TE_FWK_PSTATE + 1)
/** \copybrief RKH_TR_FWK_EPOOL */
#define RKH_TE_FWK_EPOOL        (RKH_TE_FWK_TIMER + 1)
/** \copybrief RKH_TR_FWK_QUEUE */
#define RKH_TE_FWK_QUEUE        (RKH_TE_FWK_EPOOL + 1)
/** \copybrief RKH_TR_FWK_ACTOR */
#define RKH_TE_FWK_ACTOR        (RKH_TE_FWK_QUEUE + 1)
#define RKH_FWK_END             RKH_TE_FWK_ACTOR

/* --- User events (USR group) --------------------------------------------- */
#define RKH_TE_USER             RKH_USR_START

/* --- Unit test harness events (UT group) --------------------------------- */
#define RKH_TE_UT_INIT          RKH_UT_START
#define RKH_TE_UT_CLEANUP       (RKH_TE_UT_INIT + 1)
#define RKH_TE_UT_VERIFY        (RKH_TE_UT_CLEANUP + 1)
#define RKH_TE_UT_IGNORE_GROUP  (RKH_TE_UT_VERIFY + 1)
#define RKH_TE_UT_EXPECT        (RKH_TE_UT_IGNORE_GROUP + 1)
#define RKH_TE_UT_EXPECT_ANYARGS    (RKH_TE_UT_EXPECT + 1)
#define RKH_TE_UT_IGNORE        (RKH_TE_UT_EXPECT_ANYARGS + 1)
#define RKH_TE_UT_IGNORE_ARG    (RKH_TE_UT_IGNORE + 1)
#define RKH_TE_UT_SUCCESS       (RKH_TE_UT_IGNORE_ARG + 1)
#define RKH_TE_UT_FAIL          (RKH_TE_UT_SUCCESS + 1)
#define RKH_UT_END              RKH_TE_UT_IGNORE_ARG

/* The last trace event */
#define RKH_TE_NEVENT           (RKH_UT_END + 1)

/* ------------------------- Configuration errors -------------------------- */
/*
 *  LOOK FOR WRONG #define CONSTANTS
 *
 *  This section is used to generate ERROR messages at compile time if
 *  certain #define constants are WRONG in rkhtrc.h.  This allows you to
 *  quickly determine the source of the error.
 *
 *  You SHOULD NOT change this section UNLESS you would like to add more
 *  comments as to the source of the compile time error.
 */
#if ((RKH_MP_END - RKH_MP_START) > ((RKH_MP_TTBL_RANGE * 8) - 1))
    #error  "rkhtrc.h, the total number of trace events represented"
    #error  "by RKH_TOT_NUM_TRC_EVTS must be <= RKH_TRC_MAX_EVENTS"
#endif

#if ((RKH_RQ_END - RKH_RQ_START) > ((RKH_RQ_TTBL_RANGE * 8) - 1))
    #error  "rkhtrc.h, the total number of trace events represented"
    #error  "by RKH_TOT_NUM_TRC_EVTS must be <= RKH_TRC_MAX_EVENTS"
#endif

#if ((RKH_SMA_END - RKH_SMA_START) > ((RKH_SMA_TTBL_RANGE * 8) - 1))
    #error  "rkhtrc.h, the total number of trace events represented"
    #error  "by RKH_TOT_NUM_TRC_EVTS must be <= RKH_TRC_MAX_EVENTS"
#endif

#if ((RKH_SM_END - RKH_SM_START) > ((RKH_SM_TTBL_RANGE * 8) - 1))
    #error  "rkhtrc.h, the total number of trace events represented"
    #error  "by RKH_TOT_NUM_TRC_EVTS must be <= RKH_TRC_MAX_EVENTS"
#endif

#if ((RKH_TMR_END - RKH_TMR_START) > ((RKH_TMR_TTBL_RANGE * 8) - 1))
    #error  "rkhtrc.h, the total number of trace events represented"
    #error  "by RKH_TOT_NUM_TRC_EVTS must be <= RKH_TRC_MAX_EVENTS"
#endif

#if ((RKH_FWK_END - RKH_FWK_START) > ((RKH_FWK_TTBL_RANGE * 8) - 1))
    #error  "rkhtrc.h, the total number of trace events represented"
    #error  "by RKH_TOT_NUM_TRC_EVTS must be <= RKH_TRC_MAX_EVENTS"
#endif

#if ((RKH_UT_END - RKH_UT_START) > ((RKH_UT_TTBL_RANGE * 8) - 1))
    #error  "rkhtrc.h, the total number of trace events represented"
    #error  "by RKH_TOT_NUM_TRC_EVTS must be <= RKH_TRC_MAX_EVENTS"
#endif

#if RKH_CFG_TRC_RTFIL_EN == RKH_ENABLED
        /**
         *	Each trace event always begins with the macro RKH_TRC_BEGIN()
         *	and ends with the matching macro RKH_TRC_END(). These macros are
         *	not terminated with the semicolon.
         *  This pair of macros locks interrupts at the beginning and unlocks
         *  at the end of each record.
         *
         *	\param[in] eid_		is the trace event ID.
         *	                    See RKH_TE_<group>_<event> definitions.
         *	\param[in] prio_	priority of active object.
         *	\param[in] sig_		signal.
         *
         *  \note
         *  Both arguments are used in the on/off filter.
         *  \note
         *  The runtime filter is optional and could be enabled or
         *  disabled with the RKH_CFG_TRC_RTFIL_EN in the rkhcfg.h file.
         *  \note
         *  This macro always invokes the rkh_trc_begin() function.
         */
        #define RKH_TRC_BEGIN(eid_, prio_, sig_)  \
            if (rkh_trc_isoff_(eid_) \
                RKH_TRC_AO_ISOFF(prio_) \
                RKH_TRC_SIG_ISOFF(sig_)) \
            { \
                RKH_ENTER_CRITICAL_(); \
                rkh_trc_begin(eid_);

        #define RKH_TRC_BEGIN_WOAO(eid_, sig_) \
            if (rkh_trc_isoff_(eid_) \
                RKH_TRC_SIG_ISOFF(sig_)) \
            { \
                RKH_ENTER_CRITICAL_(); \
                rkh_trc_begin(eid_);

        #define RKH_TRC_BEGIN_WOSIG(eid_, prio_) \
            if (rkh_trc_isoff_(eid_) \
                RKH_TRC_AO_ISOFF(prio_)) \
            { \
                RKH_ENTER_CRITICAL_(); \
                rkh_trc_begin(eid_);

        #define RKH_TRC_BEGIN_WOAOSIG(eid_) \
            if (rkh_trc_isoff_(eid_)) \
            { \
                RKH_ENTER_CRITICAL_(); \
                rkh_trc_begin(eid_);

        /**
         *	Each trace event always begins with the macro RKH_TRC_BEGIN()
         *	and ends with the matching macro RKH_TRC_END(). These macros are
         *	not terminated with the semicolon.
         *  This pair of macros locks interrupts at the beginning and unlocks
         *  at the end of each record.
         *
         *  \note
         *  This macro always invokes the rkh_trc_end() function.
         */
        #define RKH_TRC_END() \
            rkh_trc_end(); \
            RKH_EXIT_CRITICAL_(); \
            }

        /**
         *  Idem RKH_TRC_BEGIN() macro but without entering critical section.
         *
         *	\param[in] eid_		is the trace event ID.
         *	                    See RKH_TE_<group>_<event> definitions.
         *	\param[in] prio_	priority of active object.
         *	\param[in] sig_		signal.
         */
        #define RKH_TRC_BEGIN_NOCRIT(eid_, prio_, sig_) \
            if (rkh_trc_isoff_(eid_) \
                RKH_TRC_AO_ISOFF(prio_) \
                RKH_TRC_SIG_ISOFF(sig_)) \
            { \
                rkh_trc_begin(eid_);

        /**
         *  Idem RKH_TRC_BEGIN_WOAO() macro but without entering critical
         *  section.
         *
         *	\param[in] eid_		is the trace event ID.
         *	                    See RKH_TE_<group>_<event> definitions.
         *	\param[in] sig_		signal.
         */
        #define RKH_TRC_BEGIN_WOAO_NOCRIT(eid_, sig_) \
            if (rkh_trc_isoff_(eid_) \
                RKH_TRC_SIG_ISOFF(sig_)) \
            { \
                rkh_trc_begin(eid_);

        /**
         *  Idem RKH_TRC_BEGIN_WOSIG() macro but without entering critical
         *  section.
         *
         *	\param[in] eid_		is the trace event ID.
         *	                    See RKH_TE_<group>_<event> definitions.
         *	\param[in] prio_	priority of active object.
         */
        #define RKH_TRC_BEGIN_WOSIG_NOCRIT(eid_, prio_) \
            if (rkh_trc_isoff_(eid_) \
                RKH_TRC_AO_ISOFF(prio_)) \
            { \
                rkh_trc_begin(eid_);

        /**
         *  Idem RKH_TRC_BEGIN_WOAOSIG() macro but without entering critical
         *  section.
         *
         *	\param[in] eid_		is the trace event ID.
         *	                    See RKH_TE_<group>_<event> definitions.
         */
        #define RKH_TRC_BEGIN_WOAOSIG_NOCRIT(eid_) \
            if (rkh_trc_isoff_(eid_)) \
            { \
                rkh_trc_begin(eid_);

        /**
         *  Idem RKH_TRC_EXIT() macro but without exiting critical section.
         */
        #define RKH_TRC_END_NOCRIT() \
            rkh_trc_end(); \
            }
#else
        #define RKH_TRC_BEGIN(eid_, prio_, sig_) \
            RKH_ENTER_CRITICAL_(); \
            rkh_trc_begin(eid_);

        #define RKH_TRC_BEGIN_WOAO(eid_, sig_) \
            RKH_ENTER_CRITICAL_(); \
            rkh_trc_begin(eid_);

        #define RKH_TRC_BEGIN_WOSIG(eid_, prio_) \
            RKH_ENTER_CRITICAL_(); \
            rkh_trc_begin(eid_);

        #define RKH_TRC_BEGIN_WOAOSIG(eid_) \
            RKH_ENTER_CRITICAL_(); \
            rkh_trc_begin(eid_);

        #define RKH_TRC_END() \
            rkh_trc_end();  \
            RKH_EXIT_CRITICAL_();

        #define RKH_TRC_BEGIN_NOCRIT(eid_, prio_, sig_) \
            rkh_trc_begin(eid_);

        #define RKH_TRC_BEGIN_WOAO_NOCRIT(eid_, sig_) \
            rkh_trc_begin(eid_);

        #define RKH_TRC_BEGIN_WOSIG_NOCRIT(eid_, prio_) \
            rkh_trc_begin(eid_);

        #define RKH_TRC_BEGIN_WOAOSIG_NOCRIT(eid_) \
            rkh_trc_begin(eid_);

        #define RKH_TRC_END_NOCRIT() \
            rkh_trc_end();
#endif

/**
 *  Idem RKH_TRC_BEGIN() macro but use it for trace events that are
 *  independent of any runtime filter.
 */
#define RKH_TRC_BEGIN_WOFIL(eid_) \
        RKH_SR_ALLOC(); \
        RKH_ENTER_CRITICAL_(); \
        rkh_trc_begin(eid_);

/**
 *  Idem RKH_TRC_END() macro but use it for trace events that are
 *  independent of any runtime filter.
 */
#define RKH_TRC_END_WOFIL() \
        rkh_trc_end(); \
        RKH_EXIT_CRITICAL_();

/**
 *  Idem RKH_TRC_BEGIN_WOFIL() macro but without entering critical section.
 */
#define RKH_TRC_BEGIN_WOFIL_NOCRIT(eid_) \
        rkh_trc_begin(eid_);

/**
 *  Idem RKH_TRC_END_WOFIL_NOCRIT() macro but without entering critical
 *  section.
 */
#define RKH_TRC_END_WOFIL_NOCRIT() \
        rkh_trc_end();  \

/**
 *  Idem RKH_TRC_BEGIN() macro with default configuration, i.e.
 *  without timestamp, and number of sequence, but with 8-bit checksum.
 */
#define RKH_TRC_BEGIN_DFT(eid_) \
        RKH_SR_ALLOC(); \
        RKH_ENTER_CRITICAL_(); \
        rkh_trc_clear_chk(); \
        RKH_TRC_TE_ID(eid_);

/**
 *  Idem RKH_TRC_END() macro but use it for trace events that are
 *  independent of any runtime filter.
 */
#define RKH_TRC_END_DFT() \
        rkh_trc_end(); \
        RKH_EXIT_CRITICAL_();

/**
 *  \brief
 *  Insert a 1-byte without escaping it.
 */
#define RKH_TRC_U8_RAW(d) \
        rkh_trc_put((d))

/**
 *  \brief
 *  Insert a 1-byte data.
 */
#define RKH_TRC_UI8(d) \
        rkh_trc_u8((rui8_t)(d))

/**
 *  \brief
 *  Insert a 2-byte data.
 */
#define RKH_TRC_UI16(d) \
        rkh_trc_u16((d))

/**
 *  \brief
 *  Insert a 4-byte data.
 */
#define RKH_TRC_UI32(d) \
        rkh_trc_u32((d))

/**
 *  \brief
 *  Insert a string.
 */
#define RKH_TRC_STR(s) \
        rkh_trc_str((s))

#if RKH_CFG_TRC_USER_TRACE_EN == RKH_ENABLED
        /**
         *  Idem RKH_TRC_BEGIN() macro but use it for user trace events.
         */
        #define RKH_TRC_USR_BEGIN(eid_) \
            RKH_SR_ALLOC(); \
            if (rkh_trc_isoff_(eid_)) \
            { \
                RKH_ENTER_CRITICAL_(); \
                rkh_trc_begin(eid_);

        /**
         *  Idem RKH_TRC_END() macro but use it for user trace events.
         */
        #define RKH_TRC_USR_END() \
            rkh_trc_end(); \
            RKH_EXIT_CRITICAL_(); \
            }

        /**
         *  Idem RKH_TRC_USR_BEGIN() macro but without entering critical 
         *  section.
         */
        #define RKH_TRC_USR_BEGIN_NOCRIT(eid_) \
            if (rkh_trc_isoff_(eid_)) \
            { \
                rkh_trc_begin(eid_);

        /**
         *  Idem RKH_TRC_USR_END() macro but without exiting critical section.
         */
        #define RKH_TRC_USR_END_NOCRIT() \
            rkh_trc_end(); \
            }

        /**
         *  \brief
         *  Output formatted ri8_t to the trace record.
         */
        #define RKH_TUSR_I8(w_, d_) \
            rkh_trc_fmt_u8((rui8_t)(((w_) << 4)) | (rui8_t)RKH_I8_T, \
                           (d_))

        /**
         *  \brief
         *  Output formatted rui8_t to the trace record.
         */
        #define RKH_TUSR_UI8(w_, d_) \
            rkh_trc_fmt_u8((rui8_t)(((w_) << 4)) | (rui8_t)RKH_UI8_T, \
                           (d_))

        /**
         *  \brief
         *  Output formatted ri16_t to the trace record.
         */
        #define RKH_TUSR_I16(w_, d_) \
            rkh_trc_fmt_u16((rui8_t)(((w_) << 4)) | (rui8_t)RKH_I16_T, \
                            (d_))

        /**
         *  \brief
         *  Output formatted rui16_t to the trace record.
         */
        #define RKH_TUSR_UI16(w_, d_) \
            rkh_trc_fmt_u16((rui8_t)(((w_) << 4)) | (rui8_t)RKH_UI16_T, \
                            (d_))

        /**
         *  \brief
         *  Output formatted ri32_t to the trace record.
         */
        #define RKH_TUSR_I32(w_, d_) \
            rkh_trc_fmt_u32((rui8_t)(((w_) << 4)) | (rui8_t)RKH_I32_T, \
                            (d_))

        /**
         *  \brief
         *  Output formatted rui32_t to the trace record.
         */
        #define RKH_TUSR_UI32(w_, d_) \
            rkh_trc_fmt_u32((rui8_t)(((w_) << 4)) | (rui8_t)RKH_UI32_T, \
                            (d_))

        /**
         *  \brief
         *  Output formatted rui32_t to the trace record.
         */
        #define RKH_TUSR_X32(w_, d_) \
            rkh_trc_fmt_u32((rui8_t)(((w_) << 4)) | (rui8_t)RKH_X32_T, \
                            (d_))

        /**
         *  \brief
         *  Output formatted zero-terminated ASCII string to the trace record.
         */
        #define RKH_TUSR_STR(s_) \
            rkh_trc_fmt_str((s_))

        /**
         *  \brief
         *  Output formatted memory block of up to 255 bytes to the trace 
         *  record.
         */
        #define RKH_TUSR_MEM(mem_, size_) \
            rkh_trc_fmt_mem((mem_), (size_))

        /**
         *  \brief
         *  Output formatted object pointer to the trace record.
         */
        #if RKH_CFGPORT_TRC_SIZEOF_PTR == 16
            #define RKH_TUSR_OBJ(obj_)    \
                rkh_trc_fmt_u16((rui8_t)RKH_OBJ_T, (rui16_t)(obj_))
        #elif RKH_CFGPORT_TRC_SIZEOF_PTR == 32
            #define RKH_TUSR_OBJ(obj_)    \
                rkh_trc_fmt_u32((rui8_t)RKH_OBJ_T, (rui32_t)(obj_))
        #else
            #define RKH_TUSR_OBJ(obj_)    \
                rkh_trc_fmt_u32((rui8_t)RKH_OBJ_T, (rui32_t)(obj_))
        #endif

        /**
         *  \brief
         *  Output formatted function pointer to the trace record.
         */
        #if RKH_CFGPORT_TRC_SIZEOF_FUN_PTR == 16u
            #define RKH_TUSR_FUN(fun_)    \
                rkh_trc_fmt_u16((rui8_t)RKH_FUN_T, (rui16_t)(fun_))
        #elif RKH_CFGPORT_TRC_SIZEOF_FUN_PTR == 32
            #define RKH_TUSR_FUN(fun_)    \
                rkh_trc_fmt_u32((rui8_t)RKH_FUN_T, (rui32_t)(fun_))
        #else
            #define RKH_TUSR_FUN(fun_)    \
                rkh_trc_fmt_u32((rui8_t)RKH_FUN_T, (rui32_t)(fun_))
        #endif

        /**
         *  \brief
         *  Output formatted event signal to the trace record.
         */
        #if RKH_CFG_FWK_SIZEOF_EVT == 8
            #define RKH_TUSR_SIG(sig_) \
                rkh_trc_fmt_u8((rui8_t)RKH_ESIG_T, (rui8_t)(sig_))
        #elif RKH_CFG_FWK_SIZEOF_EVT == 16
            #define RKH_TUSR_SIG(sig_) \
                rkh_trc_fmt_u16((rui8_t)RKH_ESIG_T, (rui16_t)(sig_))
        #elif RKH_CFG_FWK_SIZEOF_EVT == 32
            #define RKH_TUSR_SIG(sig_) \
                rkh_trc_fmt_u32((rui8_t)RKH_ESIG_T, (rui32_t)(sig_))
        #else
            #define RKH_TUSR_SIG(sig_) \
                rkh_trc_fmt_u8((rui8_t)RKH_ESIG_T, (rui8_t)(sig_))
        #endif
#else
        #define RKH_TRC_USR_BEGIN(eid_)           (void)0;
        #define RKH_TRC_USR_END()                 (void)0
        #define RKH_TRC_USR_BEGIN_NOCRIT(eid_)    (void)0
        #define RKH_TRC_USR_END_NOCRIT()          (void)0
        #define RKH_TUSR_I8(w_, d_)               (void)0
        #define RKH_TUSR_UI8(w_, d_)              (void)0
        #define RKH_TUSR_I16(w_, d_)              (void)0
        #define RKH_TUSR_UI16(w_, d_)             (void)0
        #define RKH_TUSR_I32(w_, d_)              (void)0
        #define RKH_TUSR_UI32(w_, d_)             (void)0
        #define RKH_TUSR_X32(w_, d_)              (void)0
        #define RKH_TUSR_STR(s_)                  (void)0
        #define RKH_TUSR_MEM(mem_, size_)         (void)0
        #define RKH_TUSR_OBJ(obj_)                (void)0
        #define RKH_TUSR_FUN(fun_)                (void)0
        #define RKH_TUSR_SIG(sig_)                (void)0
#endif

/**
 *  \brief
 *  Insert a object address as trace record argument.
 */
#if RKH_CFGPORT_TRC_SIZEOF_PTR == 16
        #define RKH_TRC_SYM(sym)  \
            RKH_TRC_UI16((rui16_t)sym)
#elif RKH_CFGPORT_TRC_SIZEOF_PTR == 32
        #define RKH_TRC_SYM(sym)  \
            RKH_TRC_UI32((rui32_t)sym)
#else
        #define RKH_TRC_SYM(sym)  \
            RKH_TRC_UI32((rui32_t)sym)
#endif

/**
 *  \brief
 *  Insert a sender object address as trace record argument.
 */
#if defined(RKH_USE_TRC_SENDER)
        #define RKH_TRC_SNDR(sym) \
            RKH_TRC_SYM(sym)
#else
        #define RKH_TRC_SNDR(sym)
#endif

/**
 *  \brief
 *  Insert a function address as trace record argument.
 */
#if RKH_CFGPORT_TRC_SIZEOF_FUN_PTR == 16
        #define RKH_TRC_FUN(sym)  \
            RKH_TRC_UI16((rui16_t)sym)
#elif RKH_CFGPORT_TRC_SIZEOF_FUN_PTR == 32
        #define RKH_TRC_FUN(sym)  \
            RKH_TRC_UI32((rui32_t)sym)
#else
        #define RKH_TRC_FUN(sym)  \
            RKH_TRC_UI32((rui32_t)sym)
#endif

/**
 *  Insert a ntick value as trace record argument.
 */
#if RKH_CFG_TMR_SIZEOF_NTIMER == 8
        #define RKH_TRC_NTICK(nt) \
            RKH_TRC_UI8(nt)
#elif RKH_CFG_TMR_SIZEOF_NTIMER == 16
        #define RKH_TRC_NTICK(nt) \
            RKH_TRC_UI16(nt)
#elif RKH_CFG_TMR_SIZEOF_NTIMER == 32
        #define RKH_TRC_NTICK(nt) \
            RKH_TRC_UI32(nt)
#else
        #define RKH_TRC_NTICK(nt) \
            RKH_TRC_UI8(nt)
#endif

/**
 *  Insert a nblock value as trace record argument.
 */
#if RKH_CFG_MP_SIZEOF_NBLOCK == 8
        #define RKH_TRC_NBLK(nb) \
            RKH_TRC_UI8(nb)
        #if RKH_CFG_MP_GET_LWM_EN == RKH_ENABLED
            #define RKH_TRC_MP_NMIN(nm) \
                RKH_TRC_UI8(nm)
        #else
            #define RKH_TRC_MP_NMIN(nm)
        #endif
#elif RKH_CFG_MP_SIZEOF_NBLOCK == 16
        #define RKH_TRC_NBLK(nb) \
            RKH_TRC_UI16(nb)
        #if RKH_CFG_MP_GET_LWM_EN == RKH_ENABLED
            #define RKH_TRC_MP_NMIN(nm) \
                RKH_TRC_UI16(nm)
        #else
            #define RKH_TRC_MP_NMIN(nm)
        #endif
#elif RKH_CFG_MP_SIZEOF_NBLOCK == 32
        #define RKH_TRC_NBLK(nb) \
            RKH_TRC_UI32(nb)
        #if RKH_CFG_MP_GET_LWM_EN == RKH_ENABLED
            #define RKH_TRC_MP_NMIN(nm) \
                RKH_TRC_UI32(nm)
        #else
            #define RKH_TRC_MP_NMIN(nm)
        #endif
#else
        #define RKH_TRC_NBLK(nb) \
            RKH_TRC_UI8(nb)
        #if RKH_CFG_MP_GET_LWM_EN == RKH_ENABLED
            #define RKH_TRC_MP_NMIN(nm) \
                RKH_TRC_UI8(nm)
        #else
            #define RKH_TRC_MP_NMIN(nm)
        #endif
#endif

/**
 *  Insert the block size value as trace record argument.
 */
#if RKH_CFG_MP_SIZEOF_BSIZE == 8
        #define RKH_TRC_BSIZE(bs) \
            RKH_TRC_UI8(bs)
#elif RKH_CFG_MP_SIZEOF_BSIZE == 16
        #define RKH_TRC_BSIZE(bs) \
            RKH_TRC_UI16(bs)
#elif RKH_CFG_MP_SIZEOF_BSIZE == 32
        #define RKH_TRC_BSIZE(bs) \
            RKH_TRC_UI32(bs)
#else
        #define RKH_TRC_BSIZE(bs) \
            RKH_TRC_UI8(bs)
#endif

/**
 *  Insert a nelem value as trace record argument.
 */
#if RKH_CFG_RQ_SIZEOF_NELEM == 8
        #define RKH_TRC_NE(ne) \
            RKH_TRC_UI8(ne)
        #if RKH_CFG_RQ_GET_LWMARK_EN == RKH_ENABLED
            #define RKH_TRC_RQ_NMIN(nm) \
                RKH_TRC_UI8(nm)
        #else
            #define RKH_TRC_RQ_NMIN(nm)
        #endif
#elif RKH_CFG_RQ_SIZEOF_NELEM == 16
        #define RKH_TRC_NE(ne) \
            RKH_TRC_UI16(ne)
        #if RKH_CFG_RQ_GET_LWMARK_EN == RKH_ENABLED
            #define RKH_TRC_RQ_NMIN(nm) \
                RKH_TRC_UI16(nm)
        #else
            #define RKH_TRC_RQ_NMIN(nm)
        #endif
#elif RKH_CFG_RQ_SIZEOF_NELEM == 32
        #define RKH_TRC_NE(ne) \
            RKH_TRC_UI32(ne)
        #if RKH_CFG_RQ_GET_LWMARK_EN == RKH_ENABLED
            #define RKH_TRC_RQ_NMIN(nm) \
                RKH_TRC_UI32(nm)
        #else
            #define RKH_TRC_RQ_NMIN(nm)
        #endif
#else
        #define RKH_TRC_NE(ne) \
            RKH_TRC_UI8(ne)
        #if RKH_CFG_RQ_GET_LWMARK_EN == RKH_ENABLED
            #define RKH_TRC_RQ_NMIN(nm) \
                RKH_TRC_UI8(nm)
        #else
            #define RKH_TRC_RQ_NMIN(nm)
        #endif
#endif

/**
 *  Insert a signal number as trace record argument.
 */
#if RKH_CFG_FWK_SIZEOF_EVT == 8
        #define RKH_TRC_SIG(e) \
            RKH_TRC_UI8(e)
#elif RKH_CFG_FWK_SIZEOF_EVT == 16
        #define RKH_TRC_SIG(e) \
            RKH_TRC_UI16(e)
#elif RKH_CFG_FWK_SIZEOF_EVT == 32
        #define RKH_TRC_SIG(e) \
            RKH_TRC_UI32(e)
#else
        #define RKH_TRC_SIG(e) \
            RKH_TRC_UI8(e)
#endif

/**
 *  Insert a event size value as trace record argument.
 */
#if RKH_CFG_FWK_SIZEOF_EVT_SIZE == 8
        #define RKH_TRC_ES(es) \
            RKH_TRC_UI8(es)
#elif RKH_CFG_FWK_SIZEOF_EVT_SIZE == 16
        #define RKH_TRC_ES(es) \
            RKH_TRC_UI16(es)
#elif RKH_CFG_FWK_SIZEOF_EVT_SIZE == 32
        #define RKH_TRC_ES(es) \
            RKH_TRC_UI32(es)
#else
        #define RKH_TRC_ES(es) \
            RKH_TRC_UI8(es)
#endif

#if RKH_CFG_TRC_EN == RKH_ENABLED
        /* --- Memory Pool (MP) -------------------------------------------- */
        #if RKH_CFG_TRC_ALL_EN == RKH_ENABLED || \
            RKH_CFG_TRC_MP_EN == RKH_ENABLED
            /**
             *  \addtogroup trc
             *  @{
             *  \addtogroup traceMP Traces of memory pool services
             *  @{
             *  \brief      Macros for tracing the memory pool execution
             */

            /**
             *  \brief
             *  \copybrief rkh_mp_init
             *
             *  \description    Initialize a memory block pool
             *  \trcGroup       RKH_TG_MP
             *  \trcEvent       RKH_TE_MP_INIT
             *
             *  \param[in] memPool_     Memory pool
             *  \param[in] nBlocks_     Total number of blocks in bytes
             *  \param[in] blockSize_   Maximum block size in bytes
             */
            #define RKH_TR_MP_INIT(memPool_, nBlocks_, blockSize_) \
                RKH_TRC_BEGIN_WOAOSIG(RKH_TE_MP_INIT) \
                    RKH_TRC_SYM(memPool_); \
                    RKH_TRC_NBLK(nBlocks_); \
                    RKH_TRC_BSIZE(blockSize_); \
                RKH_TRC_END()

            /**
             *  \brief
             *  \copybrief rkh_mp_get
             *
             *  \description    Get a block from the pool
             *  \trcGroup       RKH_TG_MP
             *  \trcEvent       RKH_TE_MP_GET
             *
             *  \param[in] memPool_     Memory pool
             *  \param[in] nFree_       Number of free blocks remaining
             *  \param[in] nMin_        Minimum number of free blocks ever in 
             *                          this pool, i.e. holds the lowest 
             *                          number of free blocks ever present in 
             *                          the pool.
             */
            #define RKH_TR_MP_GET(memPool_, nFree_, nMin_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_MP_GET) \
                    RKH_TRC_SYM(memPool_); \
                    RKH_TRC_NBLK(nFree_); \
                    RKH_TRC_MP_NMIN(nMin_); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *  \copybrief rkh_mp_put
             *
             *  \description    Put the block to the pool
             *  \trcGroup       RKH_TG_MP
             *  \trcEvent       RKH_TE_MP_PUT
             *
             *  \param[in] memPool_     Memory pool
             *  \param[in] nFree_       Number of free blocks remaining
             */
            #define RKH_TR_MP_PUT(memPool_, nFree_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_MP_PUT) \
                    RKH_TRC_SYM(memPool_); \
                    RKH_TRC_NBLK(nFree_); \
                RKH_TRC_END_NOCRIT()

            /** @} doxygen end group definition */
            /** @} doxygen end group definition */
        #else
            #define RKH_TR_MP_INIT(memPool_, nBlocks_, blockSize_)  (void)0
            #define RKH_TR_MP_GET(memPool_, nFree_, nMin_)          (void)0
            #define RKH_TR_MP_PUT(memPool_, nFree_)                 (void)0
        #endif

        /* --- Queue (RQ) -------------------------------------------------- */
        #if RKH_CFG_TRC_ALL_EN == RKH_ENABLED || RKH_CFG_TRC_RQ_EN == RKH_ENABLED
            /**
             *  \addtogroup trc
             *  @{
             *  \addtogroup traceQ Traces of event queue services
             *  @{
             *  \brief      Macros for tracing the event queue execution
             */

            /**
             *  \brief
             *	\copybrief rkh_rq_init
             *
             *  \description    Initialize a event queue
             *  \trcGroup       RKH_TG_RQ
             *  \trcEvent       RKH_TE_RQ_INIT
             *
             *  \param[in] queue_   Event queue
             *  \param[in] actObj_  Associated active object that receives the 
             *                      equeued events.
             *  \param[in] nElem_   Storage size [in the units of void pointers]
             */
            #define RKH_TR_RQ_INIT(queue_, actObj_, nElem_) \
                RKH_TRC_BEGIN_WOAOSIG(RKH_TE_RQ_INIT) \
                    RKH_TRC_SYM(queue_); \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_NE(nElem_); \
                RKH_TRC_END()

            /**
             *  \brief
             *  \copybrief rkh_rq_get
             *
             *  \description    Get and remove an element from a queue
             *  \trcGroup       RKH_TG_RQ
             *  \trcEvent       RKH_TE_RQ_GET
             *
             *  \param[in] queue_   Event queue
             *  \param[in] nElem_   Number of elements currently in the queue
             */
            #define RKH_TR_RQ_GET(queue_, nElem_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_RQ_GET) \
                    RKH_TRC_SYM(queue_); \
                    RKH_TRC_NE(nElem_); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *  \copybrief rkh_rq_put_fifo
             *
             *  \description    Puts an element on a queue in a FIFO manner
             *  \trcGroup       RKH_TG_RQ
             *  \trcEvent       RKH_TE_RQ_FIFO
             *
             *  \param[in] queue_   Event queue
             *  \param[in] nElem_   Number of elements currently in the queue
             *  \param[in] nMin_    Minimum number of free elements ever in 
             *                      this queue
             */
            #define RKH_TR_RQ_FIFO(queue_, nElem_, nMin_) \
                RKH_TRC_BEGIN_WOAOSIG(RKH_TE_RQ_FIFO) \
                    RKH_TRC_SYM(queue_); \
                    RKH_TRC_NE(nElem_); \
                    RKH_TRC_RQ_NMIN(nMin_); \
                RKH_TRC_END()

            /**
             *  \brief
             *  \copybrief rkh_rq_put_lifo
             *
             *  \description    Puts an element on a queue in a LIFO manner
             *  \trcGroup       RKH_TG_RQ
             *  \trcEvent       RKH_TE_RQ_LIFO
             *
             *  \param[in] queue_   Event queue
             *  \param[in] nElem_   Number of elements currently in the queue
             *  \param[in] nMin_    Minimum number of free elements ever in 
             *                      this queue
             */
            #define RKH_TR_RQ_LIFO(queue_, nElem_, nMin_) \
                RKH_TRC_BEGIN_WOAOSIG(RKH_TE_RQ_LIFO) \
                    RKH_TRC_SYM(queue_); \
                    RKH_TRC_NE(nElem_); \
                    RKH_TRC_RQ_NMIN(nMin_); \
                RKH_TRC_END()

            /**
             *  \brief
             *  Queue is full.
             *
             *  \description    Queue is full
             *  \trcGroup       RKH_TG_RQ
             *  \trcEvent       RKH_TE_RQ_FULL
             *
             *  \param[in] queue_   Event queue
             */
            #define RKH_TR_RQ_FULL(queue_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_RQ_FULL) \
                    RKH_TRC_SYM(queue_); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *  \copybrief rkh_rq_deplete
             *
             *  \description    Depletes a queue
             *  \trcGroup       RKH_TG_RQ
             *  \trcEvent       RKH_TE_RQ_DPT
             *
             *  \param[in] queue_   Event queue
             */
            #define RKH_TR_RQ_DPT(queue_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_RQ_DPT) \
                    RKH_TRC_SYM(queue_); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *  Get the last element from the queue
             *
             *  \description    Get the last element from the queue
             *  \trcGroup       RKH_TG_RQ
             *  \trcEvent       RKH_TE_RQ_GET_LAST
             *
             *  \param[in] queue_   Event queue
             */
            #define RKH_TR_RQ_GET_LAST(queue_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_RQ_GET_LAST)  \
                    RKH_TRC_SYM(queue_); \
                RKH_TRC_END_NOCRIT()

            /** @} doxygen end group definition */
            /** @} doxygen end group definition */
        #else
            #define RKH_TR_RQ_INIT(queue_, actObj_, nElem_)     (void)0
            #define RKH_TR_RQ_GET(queue_, nElem_)               (void)0
            #define RKH_TR_RQ_FIFO(queue_, nElem_, nMin_)       (void)0
            #define RKH_TR_RQ_LIFO(queue_, nElem_, nMin_)       (void)0
            #define RKH_TR_RQ_FULL(queue_)                      (void)0
            #define RKH_TR_RQ_DPT(queue_)                       (void)0
            #define RKH_TR_RQ_GET_LAST(queue_)                  (void)0
        #endif

        /* --- State Machine Application (SMA) ----------------------------- */
        #if RKH_CFG_TRC_ALL_EN == RKH_ENABLED || \
            RKH_CFG_TRC_SMA_EN == RKH_ENABLED
            /**
             *  \addtogroup trc
             *  @{
             *  \addtogroup traceAO Traces of active objects
             *  @{
             *  \brief      Macros for tracing the active object execution
             */
            /**
             *  \brief
             *  \copybrief rkh_sma_activate
             *
             *  \description    Activate an active object
             *  \trcGroup       RKH_TG_SMA
             *  \trcEvent       RKH_TE_SMA_ACT
             *
             *  \param[in] actObj_          Active object
             *  \param[in] actObjPrio_      Active object priority
             *  \param[in] actObjQueSize_   Size of active object queue
             */
            #define RKH_TR_SMA_ACT(actObj_, actObjPrio_, actObjQueSize_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SMA_ACT, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_UI8(actObjPrio_); \
                    RKH_TRC_UI8(actObjQueSize_); \
                RKH_TRC_END()

            /**
             *  \brief
             *  \copybrief rkh_sma_terminate
             *
             *  \description    Terminate an active object
             *  \trcGroup       RKH_TG_SMA
             *  \trcEvent       RKH_TE_SMA_TERM
             *
             *  \param[in] actObj_   Active object
             *  \param[in] actObjPrio_    Active object priority
             */
            #define RKH_TR_SMA_TERM(actObj_, actObjPrio_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SMA_TERM, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_UI8(actObjPrio_); \
                RKH_TRC_END()

            /**
             *  \brief
             *  Get an event from the active object's queue.
             *
             *  \description    
             *  \trcGroup       RKH_TG_SMA
             *  \trcEvent       RKH_TE_SMA_GET
             *
             *  \param[in] actObj_      Get an event from the active object 
             *                          queue
             *  \param[in] evt_         Event signal
             *  \param[in] poolID_      Pool ID (for dynamic events) 
             *  \param[in] refCntr_     Reference count (for dynamic events)
             *  \param[in] nElem_       Number of elements currently in the 
             *                          queue
             *  \param[in] nMin_        Minimum number of free elements ever 
             *                          in this queue
             */
            #define RKH_TR_SMA_GET(actObj_, evt_, poolID_, refCntr_, \
                                   nElem_, nMin_) \
                RKH_TRC_BEGIN(RKH_TE_SMA_GET, \
                              RKH_SMA_ACCESS_CONST(actObj_, prio), (evt_)->e) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_SIG((evt_)->e); \
                    RKH_TRC_UI8(poolID_); \
                    RKH_TRC_UI8(refCntr_); \
                    RKH_TRC_NE(nElem_); \
                    RKH_TRC_NE(nMin_); \
                RKH_TRC_END()

            /**
             *  \brief
             *  \copybrief rkh_sma_post_fifo
             *
             *  \description    Send a event to SMA's queue in a FIFO manner
             *  \trcGroup       RKH_TG_SMA
             *  \trcEvent       RKH_TE_SMA_FIFO
             *
             *  \param[in] actObj_  Active object
             *  \param[in] evt_     Event signal
             *  \param[in] sender_  Event sender
             *  \param[in] poolID_  Pool ID (for dynamic events) 
             *  \param[in] refCntr_ Reference count (for dynamic events)
             *  \param[in] nElem_   Number of elements currently in the 
             *                      queue
             *  \param[in] nMin_    Minimum number of free elements ever 
             *                      in this queue
             */
            #define RKH_TR_SMA_FIFO(actObj_, evt_, sender_, poolID_, refCntr_, \
                                    nElem_, nMin_) \
                RKH_TRC_BEGIN_NOCRIT(RKH_TE_SMA_FIFO, \
                                     RKH_SMA_ACCESS_CONST(actObj_, prio), \
                                     (evt_)->e) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_SIG((evt_)->e); \
                    RKH_TRC_SNDR(sender_); \
                    RKH_TRC_UI8(poolID_); \
                    RKH_TRC_UI8(refCntr_); \
                    RKH_TRC_NE(nElem_); \
                    RKH_TRC_NE(nMin_); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *  \copybrief rkh_sma_post_lifo
             *
             *  \description    Send a event to SMA's queue in a LIFO manner
             *  \trcGroup       RKH_TG_SMA
             *  \trcEvent       RKH_TE_SMA_LIFO
             *
             *  \param[in] actObj_  Active object
             *  \param[in] evt_     Event signal
             *  \param[in] sender_  Event sender
             *  \param[in] poolID_  Pool ID (for dynamic events) 
             *  \param[in] refCntr_ Reference count (for dynamic events)
             *  \param[in] nElem_   Number of elements currently in the 
             *                      queue
             *  \param[in] nMin_    Minimum number of free elements ever 
             *                      in this queue
             */
            #define RKH_TR_SMA_LIFO(actObj_, evt_, sender_, poolID_, refCntr_, \
                                    nElem_, nMin_) \
                RKH_TRC_BEGIN_NOCRIT(RKH_TE_SMA_LIFO, \
                                     RKH_SMA_ACCESS_CONST(actObj_, prio), \
                                     (evt_)->e) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_SIG((evt_)->e); \
                    RKH_TRC_SNDR(sender_); \
                    RKH_TRC_UI8(poolID_); \
                    RKH_TRC_UI8(refCntr_); \
                    RKH_TRC_NE(nElem_); \
                    RKH_TRC_NE(nMin_); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *  \copybrief rkh_sma_register
             *
             *  \description    Register an active object
             *  \trcGroup       RKH_TG_SMA
             *  \trcEvent       RKH_TE_SMA_REG
             *
             *  \param[in] actObj_   Active object
             *  \param[in] prio Active object priority
             */
            #define RKH_TR_SMA_REG(actObj_, prio) \
                RKH_TRC_BEGIN_WOSIG_NOCRIT(RKH_TE_SMA_REG, \
                                           RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_UI8(prio); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *  \copybrief rkh_sma_unregister
             *
             *  \description    Unregister an active object
             *  \trcGroup       RKH_TG_SMA
             *  \trcEvent       RKH_TE_SMA_UNREG
             *
             *  \param[in] actObj_   Active object
             *  \param[in] prio Active object priority
             */
            #define RKH_TR_SMA_UNREG(actObj_, prio) \
                RKH_TRC_BEGIN_WOSIG_NOCRIT(RKH_TE_SMA_UNREG, \
                                           RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_UI8(prio); \
                RKH_TRC_END_NOCRIT()

            /** @} doxygen end group definition */
            /** @} doxygen end group definition */
        #else
            #define RKH_TR_SMA_ACT(actObj_, actObjPrio_, actObjQueSize_) \
                (void)0
            #define RKH_TR_SMA_TERM(actObj_, actObjPrio_) \
                (void)0
            #define RKH_TR_SMA_GET(actObj_, evt_, poolID_, refCntr_, nElem_, \
                                   nMin_) \
                (void)0
            #define RKH_TR_SMA_FIFO(actObj_, evt_, sender_, poolID_, refCntr_, \
                                    nElem_, nMin_) \
                (void)0
            #define RKH_TR_SMA_LIFO(actObj_, evt_, sender_, poolID_, refCntr_, \
                                    nElem_, nMin_) \
                (void)0
            #define RKH_TR_SMA_REG(actObj_, prio) \
                (void)0
            #define RKH_TR_SMA_UNREG(actObj_, prio) \
                (void)0
        #endif

        /* --- State machine (SM) ------------------------------------------ */
        #if RKH_CFG_TRC_ALL_EN == RKH_ENABLED || \
            RKH_CFG_TRC_SM_EN == RKH_ENABLED
            /**
             *  \addtogroup trc
             *  @{
             *  \addtogroup traceSM Traces of state machine
             *  @{
             *  \brief      Macros for tracing the state machine execution
             */
            /**
             *  \brief
             *  \copybrief rkh_sm_init
             *
             *  \description    Initialize a state machine
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_INIT
             *
             *  \param[in] actObj_      Active object
             *  \param[in] initState_   Initial state of state machine
             */
            #if RKH_CFG_TRC_SM_INIT_EN == RKH_ENABLED
                #define RKH_TR_SM_INIT(actObj_, initState_) \
                    RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_INIT, \
                                        RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                        RKH_TRC_SYM(actObj_); \
                        RKH_TRC_SYM(initState_); \
                    RKH_TRC_END()
            #else
                #define RKH_TR_SM_INIT(actObj_, initState_)     (void)0
            #endif

            /**
             *  \brief
             *	\copybrief rkh_sm_clear_history
             *
             *  Desc    = clear history pseudostate\n
             *  Group   = RKH_TG_SM\n
             *  Id      = RKH_TE_SM_CLRH\n
             *  Args	= actObj_, history pseudostate\n
             *
             *  \description    Clear a history pseudostate
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_CLRH
             *
             *  \param[in] actObj_      Active object
             *  \param[in] history_     History pseudostate
             */
            #if RKH_CFG_TRC_SM_CLRH_EN == RKH_ENABLED
                #define RKH_TR_SM_CLRH(actObj_, history_) \
                    RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_CLRH, \
                                        RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_SYM(history_); \
                    RKH_TRC_END()
            #else
                #define RKH_TR_SM_CLRH(actObj_, history_)       (void)0
            #endif

            /**
             *  \brief
             *  \copybrief rkh_sm_dispatch
             *
             *  \description    Dispatch an event to a state machine
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_DCH
             *
             *  \param[in] actObj_  Active object
             *  \param[in] evt_     Dispatched event
             *  \param[in] state_   Current state
             */
            #if RKH_CFG_TRC_SMA_DCH_EN == RKH_ENABLED
                #define RKH_TR_SMA_DCH(actObj_, evt_, state_) \
                    RKH_TRC_BEGIN(RKH_TE_SMA_DCH, \
                                  RKH_SMA_ACCESS_CONST(actObj_, prio), \
                                  (evt_)->e) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_SIG((evt_)->e); \
                    RKH_TRC_SYM(state_); \
                    RKH_TRC_END()
            #else
                #define RKH_TR_SMA_DCH(actObj_, evt_, state_)   (void)0
            #endif

            /**
             *  \brief
             *	Source and target state of the transition. The target could be
             *	either basic state, composite state or pseudostate.
             *
             *  \description    Source and target state of transition
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_TRN
             *
             *  \param[in] actObj_          Active object
             *  \param[in] sourceState_     Source state
             *  \param[in] targetState_     Target state
             */
            #if RKH_CFG_TRC_SM_TRN_EN == RKH_ENABLED
                #define RKH_TR_SM_TRN(actObj_, sourceState_, targetState_) \
                    RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_TRN, \
                                        RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_SYM(sourceState_); \
                    RKH_TRC_SYM(targetState_); \
                    RKH_TRC_END()
            #else
                #define RKH_TR_SM_TRN(actObj_, sourceState_, targetState_)           (void)0
            #endif

            /**
             *  \brief
             *	Legal, stable and final state of transition.
             *
             *  \description    Main target state of transition
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_STATE
             *
             *  \param[in] actObj_  Active object
             *  \param[in] state_   Target state of transition
             */
            #if RKH_CFG_TRC_SM_STATE_EN == RKH_ENABLED
                #define RKH_TR_SM_STATE(actObj_, state_) \
                    RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_STATE, \
                                        RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_SYM(state_); \
                    RKH_TRC_END()
            #else
                #define RKH_TR_SM_STATE(actObj_, state_)        (void)0
            #endif

            /**
             *  \brief
             *  Entered state.
             *
             *  \description    Entry state
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_ENSTATE
             *
             *  \param[in] actObj_  Active object
             *  \param[in] state_   Entry state
             */
            #if RKH_CFG_TRC_SM_ENSTATE_EN == RKH_ENABLED
                #define RKH_TR_SM_ENSTATE(actObj_, state_) \
                    RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_ENSTATE, \
                                        RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_SYM(state_); \
                    RKH_TRC_END()
            #else
                #define RKH_TR_SM_ENSTATE(actObj_, state_)      (void)0
            #endif

            /**
             *  \brief
             *  Exited state.
             *
             *  \description    Exit state
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_EXSTATE
             *
             *  \param[in] actObj_  Active object
             *  \param[in] state_   Exit state
             */
            #if RKH_CFG_TRC_SM_EXSTATE_EN == RKH_ENABLED
                #define RKH_TR_SM_EXSTATE(actObj_, state_) \
                    RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_EXSTATE, \
                                        RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_SYM(state_); \
                    RKH_TRC_END()
            #else
                #define RKH_TR_SM_EXSTATE(actObj_, state_)      (void)0
            #endif

            /**
             *  \brief
             *	Number of entry and exit states in transition.
             *
             *  \description    Number of entry and exit states in transition
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_NENEX
             *
             *  \param[in] actObj_      Active object
             *  \param[in] nEnState_    Number of entry states  
             *  \param[in] nExState_    Number of exit states
             */
            #if RKH_CFG_TRC_SM_NENEX_EN == RKH_ENABLED
                #define RKH_TR_SM_NENEX(actObj_, nEnState_, nExState_) \
                    RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_NENEX, \
                                        RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_UI8(nEnState_); \
                    RKH_TRC_UI8(nExState_); \
            RKH_TRC_END()
            #else
                #define RKH_TR_SM_NENEX(actObj_, nEnState_, nExState_) \
                    (void)nEnState_
            #endif

            /**
             *  \brief
             *	Number of executed actions and segments of the transition.
             *
             *  \description    Number of executed actions in transition
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_NTRNACT
             *
             *  \param[in] actObj_  Active object
             *  \param[in] nta      Number of executed effect action 
             *  \param[in] nts      Number of transition segments
             */
            #if RKH_CFG_TRC_SM_NTRNACT_EN == RKH_ENABLED
                #define RKH_TR_SM_NTRNACT(actObj_, nta, nts) \
                    RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_NTRNACT, \
                                        RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_UI8(nta); \
                    RKH_TRC_UI8(nts); \
                    RKH_TRC_END()
            #else
                #define RKH_TR_SM_NTRNACT(actObj_, nta, nts)    (void)0
            #endif

            /**
             *  \brief
             *	Destination state or pseudostate of a transition segment.
             *
             *  \description    Next vertex in a compound transition
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_TS_STATE
             *
             *  \param[in] actObj_  Active object
             *  \param[in] state_   Target state of transition segment
             */
            #if RKH_CFG_TRC_SM_TS_STATE_EN == RKH_ENABLED
                #define RKH_TR_SM_TS_STATE(actObj_, state_) \
                    RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_TS_STATE, \
                                        RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_SYM(state_); \
                    RKH_TRC_END()
            #else
                #define RKH_TR_SM_TS_STATE(actObj_, state_)     (void)0
            #endif

            #if RKH_CFG_TRC_SM_PROCESS_EN == RKH_ENABLED

            /**
             *  \brief
             *	The arrived event was succesfully processed and HSM resides in 
             *	an allowed state
             *
             *  \description    The ocurred event was succesfully processed and 
             *                  the state machine resides in a stable state
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_EVT_PROC
             *
             *  \param[in] actObj_   Active object
             */
            #define RKH_TR_SM_EVT_PROC(actObj_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_EVT_PROC, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_END()

            /**
             *  \brief
             *	The arrived event was't founded in the transition table.
             *
             *  \description    the arrived event was't founded in the 
             *                  transition table
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_EVT_NFOUND
             *
             *  \param[in] actObj_   Active object
             *  \param[in] evt_   Dispatched event 
             */
            #define RKH_TR_SM_EVT_NFOUND(actObj_, evt_) \
                RKH_TRC_BEGIN(RKH_TE_SM_EVT_NFOUND, \
                              RKH_SMA_ACCESS_CONST(actObj_, prio), \
                              (evt_)->e) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_SIG((evt_)->e); \
                RKH_TRC_END()

            /**
             *  \brief
             *	The transition was cancelled by guard function.
             *
             *  \description    The transition was cancelled by a guard 
             *                  function 
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_GRD_FALSE
             *
             *  \param[in] actObj_   Active object
             */
            #define RKH_TR_SM_GRD_FALSE(actObj_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_GRD_FALSE, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_END()

            /**
             *  \brief
             *	The branch function returned a value not founded in the branch
             *	table.
             *
             *  \description    The branch function returned a value not founded
             *                  in the branch table
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_CND_NFOUND
             *
             *  \param[in] actObj_   Active object
             */
            #define RKH_TR_SM_CND_NFOUND(actObj_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_CND_NFOUND, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_END()

            /**
             *  \brief
             *	Unknown state.
             *
             *  \description    Unknown state
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_UNKN_STATE
             *
             *  \param[in] actObj_   Active object
             */

            #define RKH_TR_SM_UNKN_STATE(actObj_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_UNKN_STATE, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_END()

            /**
             *  \brief
             *	The transition exceeded the allowed hierarchical level.
             *
             *  \description    The transition exceeded the allowed hierarchical
             *                  level
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_EX_HLEVEL
             *
             *  \param[in] actObj_   Active object
             */
            #define RKH_TR_SM_EX_HLEVEL(actObj_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_EX_HLEVEL, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_END()

            /**
             *  \brief
             *	The transition exceeded the allowed number of segments within a
             *	compound transtion.
             *
             *  \description    The transition exceeded the allowed number of
             *                  segments within a compound transtion
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_EX_TSEG
             *
             *  \param[in] actObj_   Active object
             */
            #define RKH_TR_SM_EX_TSEG(actObj_) \
                RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_EX_TSEG, \
                                    RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                RKH_TRC_SYM(actObj_); \
                RKH_TRC_END()
            #else
                #define RKH_TR_SM_EVT_PROC(actObj_)             (void)0
                #define RKH_TR_SM_EVT_NFOUND(actObj_, evt_)     (void)0
                #define RKH_TR_SM_CND_NFOUND(actObj_)           (void)0
                #define RKH_TR_SM_GRD_FALSE(actObj_)            (void)0
                #define RKH_TR_SM_UNKN_STATE(actObj_)           (void)0
                #define RKH_TR_SM_EX_HLEVEL(actObj_)            (void)0
                #define RKH_TR_SM_EX_TSEG(actObj_)              (void)0
            #endif

            /**
             *  \brief
             *	Executes a behavior (action) of state machine, it could be an 
             *	entry, exit, effect, init, preprocessor or guard.
             *
             *  \description    Executed behavior of state machine
             *  \trcGroup       RKH_TG_SM
             *  \trcEvent       RKH_TE_SM_EXE_ACT
             *
             *  \param[in] actionType_  Action type
             *  \param[in] actObj_      Active object
             *  \param[in] state_       State
             *  \param[in] action_      Action
             */
            #if RKH_CFG_TRC_SM_EXE_ACT_EN == RKH_ENABLED
                #define RKH_TR_SM_EXE_ACT(actionType_, actObj_, state_, action_) \
                    RKH_TRC_BEGIN_WOSIG(RKH_TE_SM_EXE_ACT, \
                                        RKH_SMA_ACCESS_CONST(actObj_, prio)) \
                    RKH_TRC_UI8(actionType_); \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_SYM(state_); \
                    RKH_TRC_FUN(action_); \
                    RKH_TRC_END()
            #else
                #define RKH_TR_SM_EXE_ACT(actionType_, actObj_, state_, action_)     (void)0
            #endif

            /** @} doxygen end group definition */
            /** @} doxygen end group definition */
        #else
            #define RKH_TR_SM_INIT(actObj_, initState_)     (void)0
            #define RKH_TR_SM_CLRH(actObj_, history_)       (void)0
            #define RKH_TR_SMA_DCH(actObj_, evt_, state_)   (void)0
            #define RKH_TR_SM_TRN(actObj_, sourceState_, targetState_) \
                (void)0
            #define RKH_TR_SM_STATE(actObj_, state_)        (void)0
            #define RKH_TR_SM_ENSTATE(actObj_, state_)      (void)0
            #define RKH_TR_SM_EXSTATE(actObj_, state_)      (void)0
            #define RKH_TR_SM_NENEX(actObj_, nEnState_, nExState_) \
                (void)0
            #define RKH_TR_SM_NTRNACT(actObj_, nta, nts)    (void)0
            #define RKH_TR_SM_TS_STATE(aaost)               (void)0
            #define RKH_TR_SM_EVT_PROC(actObj_)             (void)0
            #define RKH_TR_SM_EVT_NFOUND(actObj_, evt_)     (void)0
            #define RKH_TR_SM_GRD_FALSE(actObj_)            (void)0
            #define RKH_TR_SM_CND_NFOUND(actObj_)           (void)0
            #define RKH_TR_SM_UNKN_STATE(actObj_)           (void)0
            #define RKH_TR_SM_EX_HLEVEL(actObj_)            (void)0
            #define RKH_TR_SM_EX_TSEG(actObj_)              (void)0
            #define RKH_TR_SM_EXE_ACT(actionType_, actObj_, state_, action_) \
                (void)0
        #endif

        /* --- Timer (TIM) ------------------------------------------------- */
        #if RKH_CFG_TRC_ALL_EN == RKH_ENABLED || \
            RKH_CFG_TRC_TMR_EN == RKH_ENABLED
            /**
             *  \addtogroup trc
             *  @{
             *  \addtogroup traceTMR Traces of timer services
             *  @{
             *  \brief      Macros for tracing the timer execution
             */
            /**
             *  \brief
             *  \copybrief RKH_TMR_INIT
             *
             *  \description    Initialize a timer
             *  \trcGroup       RKH_TG_TMR
             *  \trcEvent       RKH_TE_TMR_INIT
             *
             *  \param[in] timer_    Timer
             *  \param[in] signal_  Event to enqueued 
             */
            #define RKH_TR_TMR_INIT(timer_, signal_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_TMR_INIT) \
                    RKH_TRC_SYM(timer_); \
                    RKH_TRC_SIG(signal_); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *  \copybrief rkh_tmr_start
             *
             *  \description    Start a timer
             *  \trcGroup       RKH_TG_TMR
             *  \trcEvent       RKH_TE_TMR_START
             *
             *  \param[in] timer_    Timer
             *  \param[in] actObj_   Active object target
             *  \param[in] nTicks_   Load in ticks
             *  \param[in] period_  Period in ticks
             */
            #define RKH_TR_TMR_START(timer_, actObj_, nTicks_, period_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_TMR_START) \
                    RKH_TRC_SYM(timer_); \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_NTICK(nTicks_); \
                    RKH_TRC_NTICK(period_); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *  \copybrief rkh_tmr_stop
             *
             *  \description    Stop a timer
             *  \trcGroup       RKH_TG_TMR
             *  \trcEvent       RKH_TE_TMR_STOP
             *
             *  \param[in] timer_    Timer
             *  \param[in] nTicks_   Load in ticks
             *  \param[in] period_  Period in ticks
             */
            #define RKH_TR_TMR_STOP(timer_, nTicks_, period_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_TMR_STOP) \
                    RKH_TRC_SYM(timer_); \
                    RKH_TRC_NTICK(nTicks_); \
                    RKH_TRC_NTICK(period_); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *  Timer expired.
             *
             *  \description    Timer has expired
             *  \trcGroup       RKH_TG_TMR
             *  \trcEvent       RKH_TE_TMR_TOUT
             *
             *  \param[in] timer_    Timer
             *  \param[in] signal_  Event to enqueued 
             *  \param[in] actObj_   Active object target
             */
            #define RKH_TR_TMR_TOUT(timer_, signal_, actObj_) \
                RKH_TRC_BEGIN_NOCRIT(RKH_TE_TMR_TOUT, \
                                     RKH_SMA_ACCESS_CONST(actObj_, prio), \
                                     signal_) \
                    RKH_TRC_SYM(timer_); \
                    RKH_TRC_SIG(signal_); \
                    RKH_TRC_SYM(actObj_); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *	Removes timer from the active timer list.
             *
             *  \description    Remove timer from the active timer list
             *  \trcGroup       RKH_TG_TMR
             *  \trcEvent       RKH_TE_TMR_REM
             *
             *  \param[in] timer_    Timer
             */
            #define RKH_TR_TMR_REM(timer_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_TMR_REM) \
                    RKH_TRC_SYM(timer_); \
                RKH_TRC_END_NOCRIT()

            /** @} doxygen end group definition */
            /** @} doxygen end group definition */
        #else
            #define RKH_TR_TMR_INIT(timer_, signal_)                    (void)0
            #define RKH_TR_TMR_START(timer_, actObj_, nTicks_, period_) (void)0
            #define RKH_TR_TMR_STOP(timer_, nTicks_, period_)           (void)0
            #define RKH_TR_TMR_TOUT(timer_, signal_, actObj_)           (void)0
            #define RKH_TR_TMR_REM(timer_)                              (void)0
        #endif

        /* --- Framework (RKH) --------------------------------------------- */
        #if RKH_CFG_TRC_ALL_EN == RKH_ENABLED || \
            RKH_CFG_TRC_FWK_EN == RKH_ENABLED
            /**
             *  \addtogroup trc
             *  @{
             *  \addtogroup traceFWK Traces of miscellaneous framework
             *  @{
             *  \brief Macros for tracing the framework execution
             */
            /**
             *  \brief
             *  \copybrief rkh_fwk_init
             *
             *  \description    Initialize the RKH framework
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_EN
             */
            #define RKH_TR_FWK_EN() \
                RKH_TRC_BEGIN_WOAOSIG(RKH_TE_FWK_EN) \
                RKH_TRC_END()

            /**
             *  \brief
             *  \copybrief rkh_fwk_exit
             *
             *  \description    Terminate the RKH framework
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_EX
             */
            #define RKH_TR_FWK_EX() \
                RKH_TRC_BEGIN_WOAOSIG(RKH_TE_FWK_EX) \
                RKH_TRC_END()

            /**
             *  \brief
             *  \copybrief rkh_fwk_epool_register
             *
             *  \description    Register an event pool
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_EPREG
             *
             *  \param[in] evtPool_   Event pool id
             *  \param[in] storageSize_   Storage size
             *  \param[in] evtSize_   Event size
             */
            #define RKH_TR_FWK_EPREG(evtPool_, storageSize_, evtSize_) \
                RKH_TRC_BEGIN_WOAOSIG(RKH_TE_FWK_EPREG) \
                    RKH_TRC_UI8(evtPool_); \
                    RKH_TRC_UI32(storageSize_); \
                    RKH_TRC_ES(evtSize_); \
                RKH_TRC_END()

            /**
             *  \brief
             *  \copybrief rkh_fwk_ae
             *
             *  \description    Allocate an event from pool
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_AE
             *
             *  \param[in] evtSize_   Event size
             *  \param[in] evt_   Event
             *  \param[in] poolID_  Event pool id
             *  \param[in] refCnt_   Reference count
             */
            #define RKH_TR_FWK_AE(evtSize_, evt_, poolID_, refCnt_) \
                RKH_TRC_BEGIN_WOAOSIG(RKH_TE_FWK_AE) \
                    RKH_TRC_ES(evtSize_); \
                    RKH_TRC_SIG((evt_)->e); \
                    RKH_TRC_UI8(poolID_); \
                    RKH_TRC_UI8(refCnt_); \
                RKH_TRC_END()

            /**
             *  \brief
             *  Attempt to recycle an event.
             *
             *  \description    Attempt to recycle an event
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_GC
             *
             *  \param[in] evt_   Event
             *  \param[in] poolID_  Event pool id
             *  \param[in] refCnt_   Reference count
             */
            #define RKH_TR_FWK_GC(evt_, poolID_, refCnt_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_FWK_GC) \
                    RKH_TRC_SIG((evt_)->e); \
                    RKH_TRC_UI8(poolID_); \
                    RKH_TRC_UI8(refCnt_); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *  Effective recycling event.
             *
             *  \description    Effective recycling of event
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_GCR
             *
             *  \param[in] evt_   Event
             *  \param[in] poolID_  Event pool id
             *  \param[in] refCnt_   Reference count
             */
            #define RKH_TR_FWK_GCR(evt_, poolID_, refCnt_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_FWK_GCR) \
                    RKH_TRC_SIG((evt_)->e); \
                    RKH_TRC_UI8(poolID_); \
                    RKH_TRC_UI8(refCnt_); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *  \copybrief rkh_fwk_defer
             *
             *  \description    Defer an event
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_DEFER
             *
             *  \param[in] queue_    Target queue to store deferred event
             *  \param[in] evt_   Event
             */
            #define RKH_TR_FWK_DEFER(queue_, evt_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_FWK_DEFER) \
                    RKH_TRC_SYM(queue_); \
                    RKH_TRC_SIG((evt_)->e); \
                RKH_TRC_END_NOCRIT()

            /**
             *  \brief
             *  \copybrief rkh_fwk_recall
             *
             *  \description    Recall an event
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_RCALL
             *
             *  \param[in] actObj_   Active object
             *  \param[in] evt_   Event
             */
            #define RKH_TR_FWK_RCALL(actObj_, evt_) \
                RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_FWK_RCALL) \
                    RKH_TRC_SYM(actObj_); \
                    RKH_TRC_SIG((evt_)->e); \
                RKH_TRC_END_NOCRIT()

            /* --- Symbol entry table for objects -------------------------- */

            /**
             *  \brief
             *	Entry symbol table for memory object.
             *
             *  \description    Entry symbol table for memory object
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_OBJ
             *
             *  \param[in] obj_  Object address
             *
             *  e.g.\n
             *  Associates the address of the object, in memory
             *  with its symbolic name.
             *
             *  \code
             *  ...
             *  static int g_status;
             *  static RKH_TMR_T tdll;
             *
             *  RKH_TR_FWK_OBJ(&g_status);
             *  RKH_TR_FWK_OBJ(&tdll);
             *  \endcode
             */
            #define RKH_TR_FWK_OBJ(obj_) \
                do \
                { \
                    static RKHROM char __o_n[] = # obj_; \
                    rkh_trc_obj(RKH_TE_FWK_OBJ, (rui8_t *)obj_, \
                                __o_n); \
                } \
                while (0)

            /* --- Symbol entry table for objects with name ---------------- */

            /**
             *  \brief
             *	Entry symbol table for memory object. Very similar to
             *	RKH_TR_FWK_OBJ() but the name of object must be explicitely
             *	defined.
             *
             *  \description    Entry symbol table for memory object
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_OBJ
             *
             *  \param[in] obj_  Object address
             *  \param[in] name_  Name of object
             *
             *	\note
             *	This macro uses the same trace event that RKH_TR_FWK_OBJ().
             *	Use when the object name is very long and the Trazer's view is
             *	unclear.
             *
             *  e.g.\n
             *  Associates the address of the object, in memory with a name.
             *
             *  \code
             *  ...
             *  RKH_TR_FWK_OBJ_NAME(&RKH_CAST(CLI_T, sma)->cli_utmr, "cliutmr");
             *  \endcode
             */
            #define RKH_TR_FWK_OBJ_NAME(obj_, name_) \
                do \
                { \
                    rkh_trc_obj(RKH_TE_FWK_OBJ, (rui8_t *)obj_, name_); \
                } \
                while (0)

            /* --- Symbol entry table for event signals -------------------- */

            /**
             *  \brief
             *	Entry symbol table for event signal.
             *
             *  \description    Entry symbol table for signal
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_SIG
             *
             *  \param[in] stateObj_  Signal
             *
             *  e.g.\n
             *  Associates the numerical value of the event signal to the
             *  symbolic name of the signal.
             *
             *  \code
             *  // in the dedicated application header file resides the signal
             *  // enumeration
             *
             *  enum
             *  {
             *      ...
             *      PWR_FAIL,
             *      PRESS_ENTER,
             *      ...
             *  };
             *
             *  // frequently, the macro RKH_TR_FWK_SIG() is used in the
             *  // \b main.c file.
             *
             *  RKH_TR_FWK_SIG(PWR_FAIL);
             *  RKH_TR_FWK_SIG(PRESS_ENTER);
             *  \endcode
             */
            #define RKH_TR_FWK_SIG(stateObj_) \
                do \
                { \
                    static RKHROM char __s_n[] = # stateObj_; \
                    rkh_trc_sig(stateObj_, __s_n); \
                } \
                while (0)

            /* --- Symbol entry table for functions ------------------------ */

            /**
             *  \brief
             *	Entry symbol table for function object.
             *
             *  \description    Entry symbol table for function
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_FUN
             *
             *  \param[in] function_  Function address
             *
             *  e.g.\n
             *  Associates the address of the function in memory
             *  with its symbolic name.
             *
             *  \code
             *  // frequently, the macro RKH_TR_FWK_FUN() is used in the
             *  // \b main.c file.
             *
             *  RKH_TR_FWK_FUN(my_init);
             *  RKH_TR_FWK_FUN(set_x_1);
             *  RKH_TR_FWK_FUN(set_x_2);
             *  RKH_TR_FWK_FUN(set_x_3);
             *  RKH_TR_FWK_FUN(set_y_0);
             *  RKH_TR_FWK_FUN(dummy_exit);
             *  ...
             *  \endcode
             */
            #define RKH_TR_FWK_FUN(function_) \
                do \
                { \
                    static RKHROM char __f_n[] = #function_; \
                    rkh_trc_obj(RKH_TE_FWK_FUN, (rui8_t *)function_, \
                                __f_n); \
                } \
                while (0)

            /**
             *  \brief
             *  The function was executed.
             *
             *  \description    Executed function
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_EXE_FUN
             *
             *  \param[in] function_   Function address
             *
             *  Example:
             *
             *  \code
             *  void
             *  my_init(const void *sma)
             *  {
             *      CMY(sma)->x = CMY(sma)->y = 0;
             *      RKH_TR_FWK_EXE_FUN(my_init);
             *  }
             *  \endcode
             */
            #define RKH_TR_FWK_EXE_FUN(function_) \
                RKH_TRC_BEGIN_WOFIL(RKH_TE_FWK_EXE_FUN) \
                    RKH_TRC_FUN(function_); \
                RKH_TRC_END_WOFIL()

            /**
             *  \brief
             *  The function was synchronously executed. It is not explicitely
             *  used by the RKH, instead it's frequently placed on application
             *  source code.
             *
             *  \description    Function was synchronously executed
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_SYNC_EVT
             *
             *  \param[in] function_   Function address
             *  \param[in] senderObj_  Sender object
             *  \param[in] receiverObj_  Receiver object
             *
             *  Example:
             *
             *  \code
             *  void
             *  Gas_setCommandedFlow(Gas *me, unsigned int p_commandedFlow)
             *  {
             *      (void)pe;
             *      Valve_setAperture(me->itsValve, 0);
             *      RKH_TR_FWK_SYNC_EVT(Valve_setAperture, &itsGas, 
             *                          me->itsValve);
             *  }
             *  \endcode
             */
            #define RKH_TR_FWK_SYNC_EVT(function_, senderObj_, receiverObj_) \
                RKH_TRC_BEGIN_WOFIL(RKH_TE_FWK_SYNC_EVT) \
                    RKH_TRC_FUN(function_); \
                    RKH_TRC_SNDR(senderObj_); \
                    RKH_TRC_SNDR(receiverObj_); \
                RKH_TRC_END_WOFIL()

            /* --- Symbol entry table for user user-defined trace events --- */

            /**
             *  \brief
             *	Entry symbol table for user-defined trace events.
             *
             *  \description    Entry symbol table for user-defined trace events
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_TUSR
             *
             *  \param[in] __e  User trace event ID
             *
             *  e.g.\n
             *  Associates the numerical value of the user-defined trace event 
             *  to the symbolic name of that.
             *
             *  \code
             *  ...
             *  // frequently, the macro RKH_TR_FWK_TUSR() is used in the
             *  // \b main.c file.
             *
             *	enum // define the user trace events
             *	{
             *		LOWPWR_USRT = RKH_TE_USER,
             *		DISCONNECTED_USRT,
             *		...
             *	};
             *
             *  void
             *  main(void)
             *  {
             *      RKH_TR_FWK_TUSR(LOWPWR_USRT);
             *      RKH_TR_FWK_TUSR(DISCONNECTED_USRT);
             *      ...
             *  }
             *  \endcode
             */
            #define RKH_TR_FWK_TUSR(__e) \
                do \
                { \
                    static RKHROM char __e_n[] = # __e; \
                    RKH_TRC_BEGIN_WOFIL(RKH_TE_FWK_TUSR) \
                        RKH_TRC_TE_ID(EXTE(__e, RKH_TG_USR)); \
                        RKH_TRC_STR(__e_n); \
                        RKH_TRC_END_WOFIL() \
                    RKH_TRC_FLUSH(); \
                } \
                while (0)

            /* --- Trace configuration ------------------------------------- */

            /**
             *  \brief
             *	Send trace configuration to Trazer.
             *
             *  \description    Send trace configuration table to Trazer
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_TCFG
             *
             *  \param[in] timeStamp_    Trace timestamp in Hz [ticks per 
             *                          second]
             *
             *  \note
             *  The following table shows the format of RKH_TE_FWK_TCFG 
             *  arguments.
             *  The first column means ["byte index", "bit index":"# of 
             *  bits"] in the data stream.
             *
             *  [byte_index:size in bits] \n
             *  [ 0, 0:16] - RKH_VERSION_CODE \n
             *  [ 2, 0: 1] - RKH_CFG_SMA_TRC_SNDR_EN \n
             *  [ 2, 1: 1] - RKH_CFG_TRC_RTFIL_EN \n
             *  [ 2, 2: 1] - RKH_CFG_TRC_USER_TRACE_EN \n
             *  [ 2, 3: 1] - RKH_CFG_TRC_ALL_EN \n
             *  [ 2, 4: 1] - RKH_CFG_TRC_MP_EN \n
             *  [ 2, 5: 1] - RKH_CFG_TRC_RQ_EN \n
             *  [ 2, 6: 1] - RKH_CFG_TRC_SMA_EN \n
             *  [ 2, 7: 1] - RKH_CFG_TRC_TMR_EN \n
             *  [ 3, 8: 1] - RKH_CFG_TRC_SM_EN \n
             *  [ 3, 9: 1] - RKH_CFG_TRC_FWK_EN \n
             *  [ 3,10: 1] - RKH_CFG_TRC_ASSERT_EN \n
             *  [ 3,11: 1] - RKH_CFG_RQ_GET_LWMARK_EN \n
             *  [ 3,12: 1] - RKH_CFG_MP_GET_LWM_EN \n
             *  [ 3,13: 1] - RKH_CFG_TRC_RTFIL_SMA_EN \n
             *  [ 3,14: 1] - RKH_CFG_TRC_RTFIL_SIGNAL_EN \n
             *  [ 3,15: 1] - RKH_CFG_TRC_NSEQ_EN \n
             *  [ 4,16: 1] - RKH_CFG_TRC_TSTAMP_EN \n
             *  [ 4,17: 1] - RKH_CFG_TRC_CHK_EN \n
             *  [ 4,18:14] - 0 (Reserved) \n
             *  [ 6, 0: 4] - RKH_CFG_FWK_SIZEOF_EVT \n
             *  [ 6, 4: 4] - RKH_CFGPORT_TRC_SIZEOF_TSTAMP \n
             *  [ 7, 0: 4] - RKH_CFGPORT_TRC_SIZEOF_PTR \n
             *  [ 7, 4: 4] - RKH_CFG_TMR_SIZEOF_NTIMER \n
             *  [ 8, 0: 4] - RKH_CFG_MP_SIZEOF_NBLOCK \n
             *  [ 8, 4: 4] - RKH_CFG_RQ_SIZEOF_NELEM \n
             *  [ 9, 0: 4] - RKH_CFG_FWK_SIZEOF_EVT_SIZE \n
             *  [ 9, 4: 4] - 0 (Reserved) \n
             *  [10, 0: 4] - RKH_CFG_MP_SIZEOF_BSIZE \n
             *  [10, 4: 4] - RKH_CFG_FWK_MAX_EVT_POOL \n
             *  [11, 0:16] - Timestamp HZ (ticks per second)
             */
            #define RKH_TR_FWK_TCFG(timeStamp_) \
                RKH_TRC_BEGIN_DFT(RKH_TE_FWK_TCFG) \
                    RKH_TRC_UI16((rui16_t)RKH_VERSION_CODE); \
                    RKH_TRC_UI32( \
                        (rui32_t)( \
                            ((rui32_t)RKH_CFG_SMA_TRC_SNDR_EN) | \
                            ((rui32_t)RKH_CFG_TRC_RTFIL_EN << 1) | \
                            ((rui32_t)RKH_CFG_TRC_USER_TRACE_EN << 2) | \
                            ((rui32_t)RKH_CFG_TRC_ALL_EN << 3) | \
                            ((rui32_t)RKH_CFG_TRC_MP_EN << 4) | \
                            ((rui32_t)RKH_CFG_TRC_RQ_EN << 5) | \
                            ((rui32_t)RKH_CFG_TRC_SMA_EN << 6) | \
                            ((rui32_t)RKH_CFG_TRC_TMR_EN << 7) | \
                            ((rui32_t)RKH_CFG_TRC_SM_EN << 8) | \
                            ((rui32_t)RKH_CFG_TRC_FWK_EN << 9) | \
                            ((rui32_t)RKH_CFG_TRC_ASSERT_EN << 10) | \
                            ((rui32_t)RKH_CFG_RQ_GET_LWMARK_EN << 11) | \
                            ((rui32_t)RKH_CFG_MP_GET_LWM_EN << 12) | \
                            ((rui32_t)RKH_CFG_TRC_RTFIL_SMA_EN << 13) | \
                            ((rui32_t)RKH_CFG_TRC_RTFIL_SIGNAL_EN << 14) | \
                            ((rui32_t)RKH_CFG_TRC_NSEQ_EN << 15) | \
                            ((rui32_t)RKH_CFG_TRC_TSTAMP_EN << 16) | \
                            ((rui32_t)RKH_CFG_TRC_CHK_EN << 17))); \
                    RKH_TRC_UI8( \
                        (rui8_t)((RKH_CFG_FWK_SIZEOF_EVT / 8 << 4) | \
                                 RKH_CFGPORT_TRC_SIZEOF_TSTAMP / 8)); \
                    RKH_TRC_UI8( \
                        (rui8_t)((RKH_CFGPORT_TRC_SIZEOF_PTR / 8 << 4) | \
                                 RKH_CFG_TMR_SIZEOF_NTIMER / 8)); \
                    RKH_TRC_UI8( \
                        (rui8_t)((RKH_CFG_MP_SIZEOF_NBLOCK / 8 << 4) | \
                                 RKH_CFG_RQ_SIZEOF_NELEM / 8)); \
                    RKH_TRC_UI8( \
                        (rui8_t)(RKH_CFG_FWK_SIZEOF_EVT_SIZE / 8)); \
                    RKH_TRC_UI8( \
                        (rui8_t)((RKH_CFG_MP_SIZEOF_BSIZE / 8 << 4) | \
                                 RKH_CFG_FWK_MAX_EVT_POOL)); \
                    RKH_TRC_UI16( \
                        (rui16_t)(timeStamp_)); \
                RKH_TRC_END_DFT() \
                RKH_TRC_FLUSH()

            /* --- Assertion ----------------------------------------------- */

            /**
             *  \brief
             *	Assertion expression was evaluated to false.
             *
             *  \description    Assertion expression was evaluated to false
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_EXE_ASSERT
             *
             *  \param[in] mod_ Module name (*.c)
             *  \param[in] ln_  Line of code
             */
            #if RKH_CFG_TRC_ASSERT_EN == RKH_ENABLED
                #define RKH_TR_FWK_ASSERT(mod_, ln_) \
                    RKH_TRC_BEGIN_WOAOSIG_NOCRIT(RKH_TE_FWK_ASSERT) \
                        RKH_TRC_STR((RKHROM char *)mod_); \
                        RKH_TRC_UI16((rui16_t)ln_); \
                        RKH_TRC_END_NOCRIT() \
                    RKH_TRC_FLUSH()
            #else
                #define RKH_TR_FWK_ASSERT(mod_, ln_)      (void)0
            #endif

            /* --- Symbol entry table for active objects ------------------- */

            /**
             *  \brief
             *	Entry symbol table for active object.
             *
             *  \description    Entry symbol table for active object
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_OBJ
             *
             *  \param[in] actObj_ Active object address
             *
             *  e.g.\n
             *  Associates the address of the active object, in memory
             *  with its symbolic name.
             *
             *  \code
             *  ...
             *  typedef struct
             *  {
             *      RKH_SMA_T actObj_;
             *      rui8_t x;
             *      rui8_t y;
             *  } AO_T;
             *
             *  RKH_SMA_CREATE(AO_T, actObj_, 0, HCAL, &S1, ao_init, NULL);
             *  RKH_TR_FWK_OBJ(&actObj_);
             *  \endcode
             */
            #define RKH_TR_FWK_AO(actObj_) \
                do \
                { \
                    rkh_trc_ao((struct RKH_SMA_T *)actObj_); \
                } \
                while (0)

            /* --- Symbol entry table for state objects -------------------- */

            /**
             *  \brief
             *	Entry symbol table for state object.
             *
             *  \description    Entry symbol table for state object
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_OBJ
             *
             *  \param[in] actObj_ Active object address
             *  \param[in] stateObj_ State object address
             *
             *  e.g.\n
             *  Associates the address of the state object, in memory
             *  with its symbolic name.
             *
             *  \code
             *  ...
             *  RKH_CREATE_COMP_STATE(S1, en, ex, RKH_ROOT, &S11);
             *  RKH_CREATE_TRANS_TABLE(S1)
             *      RKH_TRINT(SIX,     NULL,       show_data),
             *      RKH_TRREG(TWO,     NULL,       set_y_2,	&S2),
             *  RKH_END_TRANS_TABLE
             *
             *  ...
             *  RKH_TR_FWK_STATE(my, &S1);
             *  \endcode
             */
            #define RKH_TR_FWK_STATE(actObj_, stateObj_) \
                do \
                { \
                    rkh_trc_state((struct RKH_SMA_T *)actObj_, \
                                  (rui8_t *)stateObj_); \
                } \
                while (0)

            /* --- Symbol entry table for pseudostate objects -------------- */

            /**
             *  \brief
             *	Entry symbol table for pseudostate object.
             *
             *  \description    Entry symbol table for pseudostate object
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_OBJ
             *
             *  \param[in] actObj_     Active object address
             *  \param[in] pseudoStObj_    Pseudostate object address
             *
             *  e.g.\n
             *  Associates the address of the pseudostate object, in memory
             *  with its symbolic name.
             *
             *  \code
             *  ...
             *  RKH_CREATE_COND_STATE(C1, 12);
             *  RKH_CREATE_BRANCH_TABLE(C1)
             *      RKH_BRANCH(y_1,    NULL,           &H),
             *      RKH_BRANCH(y_2,    dummy_act,      &DH),
             *      RKH_BRANCH(y_0,    NULL,           &S1),
             *  RKH_END_BRANCH_TABLE
             *
             *  ...
             *  RKH_TR_FWK_PSTATE(my, &C1);
             *  \endcode
             */
            #define RKH_TR_FWK_PSTATE(actObj_, pseudoStObj_) \
                do \
                { \
                    rkh_trc_state((struct RKH_SMA_T *)actObj_, \
                                  (rui8_t *)pseudoStObj_); \
                } \
                while (0)

            /* --- Symbol entry table for timer objects -------------------- */

            /**
             *  \brief
             *	Entry symbol table for timer object.
             *
             *  \description    Entry symbol table for timer object
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_OBJ
             *
             *  \param[in] timerObj_ Timer object address
             *
             *  e.g.\n
             *  Associates the address of the timer object, in memory
             *  with its symbolic name.
             *
             *  \code
             *  ...
             *  static RKH_TMR_T bky_tmr;
             *
             *  RKH_TR_FWK_TIMER(&bky_tmr);
             *  \endcode
             */
            #define RKH_TR_FWK_TIMER(timerObj_) \
                do \
                { \
                    static RKHROM char __to_n[] = # timerObj_; \
                    rkh_trc_obj(RKH_TE_FWK_TIMER, (rui8_t *)timerObj_, \
                                __to_n); \
                } \
                while (0)

            /* --- Symbol entry table for event pool objects --------------- */

            /**
             *  \brief
             *	Entry symbol table for event pool object.
             *
             *  \description    Entry symbol table for event pool object
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_OBJ
             *
             *  \param[in] poolId_   Event pool ID (index of event pool list)
             *  \param[in] poolName_ String terminated in '\\0'.
             *
             *  e.g.\n
             *  Associates the ID of the event pool, with a symbolic name.
             *
             *  \code
             *	...
             *	rkh_fwk_epool_register(ep0_sto,	SIZEOF_EP0STO,
             *						   SIZEOF_EP0_BLOCK);
             *	rkh_fwk_epool_register(ep1_sto, SIZEOF_EP1STO,
             *						   SIZEOF_EP1_BLOCK);
             *	rkh_fwk_epool_register(ep2_sto, SIZEOF_EP2STO,
             *						   SIZEOF_EP2_BLOCK);
             *
             *  RKH_TR_FWK_EPOOL(0, "ep0");
             *  RKH_TR_FWK_EPOOL(1, "ep1");
             *  RKH_TR_FWK_EPOOL(2, "ep2");
             *	...
             *  \endcode
             */
            #define RKH_TR_FWK_EPOOL(poolId_, poolName_) \
                RKH_TRC_BEGIN_WOFIL(RKH_TE_FWK_EPOOL) \
                    RKH_TRC_UI8(poolId_); \
                    RKH_TRC_STR(poolName_); \
                RKH_TRC_END_WOFIL() \
                RKH_TRC_FLUSH();

            /* --- Symbol entry table for queue objects -------------------- */

            /**
             *  \brief
             *	Entry symbol table for queue object.
             *
             *  \description    Entry symbol table for queue object
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_OBJ
             *
             *  \param[in] queueObj_ Queue object address
             *
             *  e.g.\n
             *  Associates the address of the queue object, in memory
             *  with its symbolic name.
             *
             *  \code
             *  ...
             *  #define QSTO_SIZE			4
             *  static RKH_EVT_T *qsto[QSTO_SIZE];
             *
             *  ...
             *  RKH_TR_FWK_QUEUE(&blinky->equeue);
             *  rkh_sma_activate(blinky, (const RKH_EVT_T **)qsto,
             *                   QSTO_SIZE, CV(0), 0);
             *	...
             *  \endcode
             */
            #define RKH_TR_FWK_QUEUE(queueObj_) \
                do \
                { \
                    static RKHROM char __qo_n[] = #queueObj_; \
                    rkh_trc_obj(RKH_TE_FWK_QUEUE, (rui8_t *)queueObj_, \
                                __qo_n); \
                } \
                while (0)

            /**
             *  \brief
             *	Entry symbol table for actor object.
             *
             *  \description    Entry symbol table for actor object
             *  \trcGroup       RKH_TG_FWK
             *  \trcEvent       RKH_TE_FWK_ACTOR
             *
             *  \param[in] actorObj_    Actor object address. Generally, it's 
             *                          used for active object and ISR, i.e. 
             *                          event producers.
             *  \param[in] nm_          String terminated in '\\0'
             *
             *  e.g.\n
             *  Associates the address of an actor object, in memory
             *  with its symbolic name.
             *
             *  \code
             *  RKH_TR_FWK_ACTOR(blinky, RKH_GET_AO_NAME(blinky));
             *  ...
             *  static int buttonManager;
             *
             *  RKH_TR_FWK_ACTOR(&buttonManager, "buttonManager");
             *  \endcode
             */
            #define RKH_TR_FWK_ACTOR(actorObj_, nm_) \
                do \
                { \
                    rkh_trc_obj(RKH_TE_FWK_ACTOR, (rui8_t *)actorObj_, nm_); \
                } \
                while (0)

            /** @} doxygen end group definition */
            /** @} doxygen end group definition */
        #else
            #define RKH_TR_FWK_EN()                                     (void)0
            #define RKH_TR_FWK_EX()                                     (void)0
            #define RKH_TR_FWK_EPREG(evtPool_, storageSize_, evtSize_)  (void)0
            #define RKH_TR_FWK_AE(evtSize_, evt_, poolID_, refCnt_)     (void)0
            #define RKH_TR_FWK_GC(evt_, poolID_, refCnt_)               (void)0
            #define RKH_TR_FWK_GCR(evt_, poolID_, refCnt_)              (void)0
            #define RKH_TR_FWK_DEFER(queue_, evt_)                      (void)0
            #define RKH_TR_FWK_RCALL(actObj_, evt_)                     (void)0
            #define RKH_TR_FWK_OBJ(obj_)                                (void)0
            #define RKH_TR_FWK_OBJ_NAME(obj_, name_)                    (void)0
            #define RKH_TR_FWK_SIG(stateObj_)                           (void)0
            #define RKH_TR_FWK_FUN(stateObj_)                           (void)0
            #define RKH_TR_FWK_EXE_FUN(function_)                       (void)0
            #define RKH_TR_FWK_SYNC_EVT(function_, senderObj_, receiverObj_) \
                (void)0
            #define RKH_TR_FWK_TUSR(__e)                                (void)0
            #define RKH_TR_FWK_TCFG(timeStamp_)                         (void)0
            #define RKH_TR_FWK_ASSERT(mod_, ln_)                        (void)0
            #define RKH_TR_FWK_AO(actObj_)                              (void)0
            #define RKH_TR_FWK_STATE(actObj_, stateObj_)                (void)0
            #define RKH_TR_FWK_PSTATE(actObj_, pseudoStObj_)            (void)0
            #define RKH_TR_FWK_TIMER(timerObj_)                         (void)0
            #define RKH_TR_FWK_EPOOL(evtPoolObj_)                       (void)0
            #define RKH_TR_FWK_QUEUE(queueObj_)                         (void)0
            #define RKH_TR_FWK_ACTOR(actObj_, nm_)                      (void)0
        #endif
#else
        /* --- Memory Pool (MP) -------------------------------------------- */
        #define RKH_TR_MP_INIT(mp, nb, bs)                (void)0
        #define RKH_TR_MP_GET(mp, nfree, nmin)            (void)0
        #define RKH_TR_MP_PUT(mp, nfree)                  (void)0

        /* --- Queue (RQ) -------------------------------------------------- */
        #define RKH_TR_RQ_INIT(q, ao, nelem)              (void)0
        #define RKH_TR_RQ_GET(q, nelem)                   (void)0
        #define RKH_TR_RQ_FIFO(q, nelem, nmin)            (void)0
        #define RKH_TR_RQ_LIFO(q, nelem, nmin)            (void)0
        #define RKH_TR_RQ_FULL(q)                         (void)0
        #define RKH_TR_RQ_DPT(q)                          (void)0
        #define RKH_TR_RQ_GET_LAST(q)                     (void)0

        /* --- State Machine Application (SMA) ----------------------------- */
        #define RKH_TR_SMA_ACT(ao, p, s)                  (void)0
        #define RKH_TR_SMA_TERM(ao, p)                    (void)0
        #define RKH_TR_SMA_GET(ao, ev, pid, rc, ne, nm)   (void)0
        #define RKH_TR_SMA_FIFO(ao, ev, snr, pid, rc, ne, nm) \
                (void)0
        #define RKH_TR_SMA_LIFO(ao, ev, snr, pid, rc, ne, nm) \
                (void)0
        #define RKH_TR_SMA_REG(ao, prio)                  (void)0
        #define RKH_TR_SMA_UNREG(ao, prio)                (void)0

        /* --- State machine (SM) ------------------------------------------ */
        #define RKH_TR_SM_INIT(ao, ist)                   (void)0
        #define RKH_TR_SM_CLRH(ao, h)                     (void)0
        #define RKH_TR_SMA_DCH(ao, ev, st)                (void)0
        #define RKH_TR_SM_TRN(ao, sst, tst)               (void)0
        #define RKH_TR_SM_STATE(ao, st)                   (void)0
        #define RKH_TR_SM_ENSTATE(ao, st)                 (void)0
        #define RKH_TR_SM_EXSTATE(ao, st)                 (void)0
        #define RKH_TR_SM_NENEX(ao, nen, nex)             (void)0
        #define RKH_TR_SM_NTRNACT(ao, nta, nts)           (void)0
        #define RKH_TR_SM_TS_STATE(ao, st)                (void)0
        #define RKH_TR_SM_EVT_PROC(ao)                    (void)0
        #define RKH_TR_SM_EVT_NFOUND(ao, ev)              (void)0
        #define RKH_TR_SM_GRD_FALSE(ao)                   (void)0
        #define RKH_TR_SM_CND_NFOUND(ao)                  (void)0
        #define RKH_TR_SM_UNKN_STATE(ao)                  (void)0
        #define RKH_TR_SM_EX_HLEVEL(ao)                   (void)0
        #define RKH_TR_SM_EX_TSEG(ao)                     (void)0
        #define RKH_TR_SM_EXE_ACT(act_t, ao, st, act)     (void)0

        /* --- Timer (TIM) ------------------------------------------------- */
        #define RKH_TR_TMR_INIT(t, sig)                   (void)0
        #define RKH_TR_TMR_START(t, ao, nt, per)          (void)0
        #define RKH_TR_TMR_STOP(t, nt, per)               (void)0
        #define RKH_TR_TMR_TOUT(t, sig, ao)               (void)0
        #define RKH_TR_TMR_REM(t)                         (void)0

        /* --- Framework (RKH) --------------------------------------------- */
        #define RKH_TR_FWK_EN()                           (void)0
        #define RKH_TR_FWK_EX()                           (void)0
        #define RKH_TR_FWK_EPREG(ep, ss, es)              (void)0
        #define RKH_TR_FWK_AE(es, ev, pid, rc)            (void)0
        #define RKH_TR_FWK_GC(ev, pid, rc)                (void)0
        #define RKH_TR_FWK_GCR(ev, pid, rc)               (void)0
        #define RKH_TR_FWK_DEFER(q, ev)                   (void)0
        #define RKH_TR_FWK_RCALL(ao, ev)                  (void)0
        #define RKH_TR_FWK_OBJ(__o)                       (void)0
        #define RKH_TR_FWK_OBJ_NAME(__o, __n)             (void)0
        #define RKH_TR_FWK_SIG(__s)                       (void)0
        #define RKH_TR_FWK_FUN(__f)                       (void)0
        #define RKH_TR_FWK_EXE_FUN(__f)                   (void)0
        #define RKH_TR_FWK_SYNC_EVT(fn, snr, rcr)         (void)0
        #define RKH_TR_FWK_TUSR(__e)                      (void)0
        #define RKH_TR_FWK_TCFG(ts_hz)                    (void)0
        #define RKH_TR_FWK_ASSERT(mod_, ln_)              (void)0
        #define RKH_TR_FWK_AO(__ao)                       (void)0
        #define RKH_TR_FWK_STATE(__ao, __so)              (void)0
        #define RKH_TR_FWK_PSTATE(__ao, __pso)            (void)0
        #define RKH_TR_FWK_TIMER(__to)                    (void)0
        #define RKH_TR_FWK_EPOOL(__epo)                   (void)0
        #define RKH_TR_FWK_QUEUE(__qo)                    (void)0
        #define RKH_TR_FWK_ACTOR(actObj_, nm_)            (void)0
#endif

    /**
     *  \brief
     *  Enumerates data formats recognized by Trazer.
     *
     *  Trazer uses this enumeration is used only internally for the formatted
     *  user data elements.
     */
    enum RKH_TRC_FMT
    {
        RKH_I8_T,       /**< signed 8-bit integer format */
        RKH_UI8_T,      /**< unsigned 8-bit integer format */
        RKH_I16_T,      /**< signed 16-bit integer format */
        RKH_UI16_T,     /**< unsigned 16-bit integer format */
        RKH_I32_T,      /**< signed 32-bit integer format */
        RKH_UI32_T,     /**< unsigned 16-bit integer format */
        RKH_X32_T,      /**< signed 16-bit integer in hex format */
        RKH_STR_T,      /**< zero-terminated ASCII string format */
        RKH_MEM_T,      /**< up to 255-bytes memory block format */
        RKH_OBJ_T,      /**< object pointer format */
        RKH_FUN_T,      /**< function pointer format */
        RKH_ESIG_T      /**< event signal format */
    };

    /* ------------------------------- Data types -------------------------- */

    /**
     *  \brief
     *  This data type defines the size of filter table for AO and signals.
     */
#if RKH_TRC_MAX_SMA > RKH_TRC_MAX_SIGNALS
        #if (RKH_TRC_MAX_SMA * 8) <= RKH_BIT(8)
            typedef rui8_t RKH_TRC_FSLOT;
        #elif (RKH_TRC_MAX_SMA * 8) <= RKH_BIT(16)
            typedef rui16_t RKH_TRC_FSLOT;
        #elif (RKH_TRC_MAX_SMA * 8) <= RKH_BIT(32)
            typedef rui32_t RKH_TRC_FSLOT;
        #else
            typedef rui8_t RKH_TRC_FSLOT;
        #endif
#else
        #if (RKH_TRC_MAX_SIGNALS * 8) <= RKH_BIT(8)
            typedef rui8_t RKH_TRC_FSLOT;
        #elif (RKH_TRC_MAX_SIGNALS * 8) <= RKH_BIT(16)
            typedef rui16_t RKH_TRC_FSLOT;
        #elif (RKH_TRC_MAX_SIGNALS * 8) <= RKH_BIT(32)
            typedef rui32_t RKH_TRC_FSLOT;
        #else
            typedef rui8_t RKH_TRC_FSLOT;
        #endif
#endif

    /**
     *  \brief
     *	Represents the filter of signal and active object.
     */
    typedef struct RKH_TRC_FIL_T
    {
        RKH_TRC_FSLOT size;     /** Size of filter table in bytes */
        rui8_t *const tbl;      /** Points to filter table in RAM */
    } RKH_TRC_FIL_T;

#if RKH_CFG_TRC_SIZEOF_STREAM < 255u
        typedef rui8_t TRCQTY_T;
#else
        typedef rui16_t TRCQTY_T;
#endif

    typedef enum
    {
        FILTER_ON, FILTER_OFF
    } RKH_TRC_FOPT;

    typedef enum RKH_FIL_T
    {
        RKH_FIL_TRCE, RKH_FIL_SIG, RKH_FIL_SMA
    } RKH_FIL_T;

/**
 *  \brief
 *  Describes a trace event identification (ID).
 *
 *  The trace event ID is arranged as:
 *  event number = | G | G | G | E | E | E | E | E |\n
 *
 *  G's:	group number.\n
 *  E's:	event's group.\n
 *
 *  Where the lower 5 bits (E's) of the event ID are used to determine
 *  the trace event, while the next three most significant bits
 *  (G's) are used to determine the corresponding group.
 *  Therefore, is able to define 8 groups and 32 events per group.
 *
 *  Trace events are binary data consisting of a trace header and its
 *  associated event data. Every trace header is made up of a ID and a
 *  timestamp. The number of bytes used by the timestamp is configurable by
 *  RKH_TRC_SIZEOF_TS (1, 2 or 4 bytes). After the timestamp follows the
 *  event data. The content and size of the data portion of a trace event is
 *  determined by the event ID.
 *	All types of events are stored in a single ring buffer, called trace
 *	stream, using a variable event size. In this manner the recorder always
 *	holds the most recent history.
 *	On the other hand, all data are stored in little-endian order (least
 *	significant byte first). Also, they are stored into the trace stream 1
 *	byte at a time, thus avoiding any potential data misalignment problems.
 *
 *	\note
 *	The timestamp is optional, thus it could be eliminated from the trace
 *	event in compile-time with RKH_CFG_TRC_TSTAMP_EN = 0.
 */
#if RKH_CFG_TRC_SIZEOF_TE_ID == 8
    typedef rui8_t RKH_TE_ID_T;
#elif RKH_CFG_TRC_SIZEOF_TE_ID == 16
    typedef rui16_t RKH_TE_ID_T;
#elif RKH_CFG_TRC_SIZEOF_TE_ID == 32
    typedef rui32_t RKH_TE_ID_T;
#else
    typedef rui8_t RKH_TE_ID_T;
#endif

/**
 *  \brief
 *  Group of events 
 */
typedef rui8_t RKH_TG_T;

/**
 *  \brief
 *  Sub-event of RKH_TE_SM_EXE_ACT event.
 */
typedef enum RKH_SUBTE_SM_EXE_ACT
{
    RKH_SUBTE_SM_EXE_ACT_EFF,       /**< \copybrief RKH_TR_SM_EXE_ACT */
    RKH_SUBTE_SM_EXE_ACT_EN,        /**< \copybrief RKH_TR_SM_EXE_ACT */
    RKH_SUBTE_SM_EXE_ACT_EX,        /**< \copybrief RKH_TR_SM_EXE_ACT */
    RKH_SUBTE_SM_EXE_ACT_INI,       /**< \copybrief RKH_TR_SM_EXE_ACT */
    RKH_SUBTE_SM_EXE_ACT_PP,        /**< \copybrief RKH_TR_SM_EXE_ACT */
    RKH_SUBTE_SM_EXE_ACT_GRD        /**< \copybrief RKH_TR_SM_EXE_ACT */
} RKH_SUBTE_SM_EXE_ACT;

/**
 *  \brief
 *  Defines the size of trace timestamp.
 *
 *  The valid values [in bits] are 8, 16 or 32. Default is 16. This type is
 *  configurable via the RKH_CFGPORT_TRC_SIZEOF_TSTAMP preprocessor option.
 */
#if RKH_CFG_TRC_TSTAMP_EN == RKH_ENABLED
    #if RKH_CFGPORT_TRC_SIZEOF_TSTAMP == 8
        typedef rui8_t RKH_TS_T;
    #elif RKH_CFGPORT_TRC_SIZEOF_TSTAMP == 16
        typedef rui16_t RKH_TS_T;
    #elif RKH_CFGPORT_TRC_SIZEOF_TSTAMP == 32
        typedef rui32_t RKH_TS_T;
    #else
        typedef rui16_t RKH_TS_T;
    #endif
#else
    typedef rui16_t RKH_TS_T;
#endif

#if RKH_CFG_TRC_SIZEOF_TE_ID == 8
typedef rui8_t RKH_GM_OFFSET_T;
typedef rui8_t RKH_GM_RANGE_T;
#elif RKH_CFG_TRC_SIZEOF_TE_ID == 16
typedef rui16_t RKH_GM_OFFSET_T;
typedef rui8_t RKH_GM_RANGE_T;
#elif RKH_CFG_TRC_SIZEOF_TE_ID == 32
typedef rui32_t RKH_GM_OFFSET_T;
typedef rui32_t RKH_GM_RANGE_T;
#else
typedef rui8_t RKH_GM_OFFSET_T;
typedef rui8_t RKH_GM_RANGE_T;
#endif

typedef struct
{
    RKH_GM_OFFSET_T offset;
    RKH_GM_RANGE_T range;
} RKH_GMTBL_T;

typedef struct RKH_FilterTbl
{
    const RKH_TRC_FIL_T *signal;
    const RKH_TRC_FIL_T *ao;
    rui8_t *event;
    rui8_t *group;
    const RKH_GMTBL_T *grpFilMap;
} RKH_FilterTbl;

/* -------------------------- External variables --------------------------- */
extern const RKH_TRC_FIL_T fsig;
extern const RKH_TRC_FIL_T fsma;

/* -------------------------- Function prototypes -------------------------- */
/**
 *  \brief
 *  Initializes the RKH's trace record service.
 *
 *  \note
 *  rkh_trc_init() is NOT protected with a critical section.
 */
void rkh_trc_init(void);

/**
 *  \brief
 *	Retrieves a pointer to oldest stored byte in the trace stream.
 *	Frequently, this function is used by the called trace analyzer.
 *
 *  \note
 *  The data is stored in a single ring buffer, called trace stream. In this
 *	manner the recorder always holds the most recent history.
 *  rkh_trc_get() is NOT protected with a critical section.
 *
 *  \returns
 *  A pointer to the oldest stored byte if trace stream was not empty,
 *  otherwise NULL pointer.
 */
rui8_t *rkh_trc_get(void);

/**
 *  \brief
 *  Retrieves a pointer to a contiguous block of data from the trace stream.
 *
 *  The function returns the pointer to the beginning of the block, and writes
 *  the number of bytes in the block to the location pointed to by \a nget.
 *  The argument \a nget is also used as input to provide the maximum size
 *  of the data block that the caller can accept.
 *	Frequently, this function is used by the called trace analyzer.
 *
 *  \param[in] nget	when this function is invoked \a nget is used as an input
 *                  to provide the maximum size of the data block to be
 *                  retrieved. Also, it is used as an output retrieving the
 *                  size of block.
 *
 *  \returns
 *  The pointer to the beginning of the block, and writes the number of bytes
 *  in the block to the location pointed to by \a nget. If this number
 *  differs from the \a nget parameter, the end-of-stream was reached. If
 *  the trace stream is empty, the function returns NULL and the content
 *  pointed by \a nget is set to zero.
 *
 *  \note
 *  The data is stored in a single ring buffer, called trace stream. In this
 *	manner the recorder always holds the most recent history.
 *  rkh_trc_get_block() is NOT protected with a critical section.
 */
rui8_t *rkh_trc_get_block(TRCQTY_T *nget);

/**
 *  \brief
 *  Put a data byte into the trace stream.
 *
 *  \param[in] b	data to be written in the trace stream.
 *
 *  \note
 *  The data is stored in a single ring buffer, called trace stream. In this
 *	manner the recorder always holds the most recent history.
 *  rkh_trc_put() is NOT protected with a critical section.
 */
void rkh_trc_put(rui8_t b);

/**
 *  \brief
 *  Emit or suppress all trace events from a specific group.
 *
 *  The stream is initially created with an empty filter (that is, without
 *  filtering any event type). If this is not the required behavior, the
 *  application can build a set of event types, include the appropriate event
 *  types in it, and apply it as a filter to the stream. After that, the
 *  stream will reject any event whose type is in the filter set.
 *
 *	Gathering many events generates a lot of data, which requires memory and
 *	processor time. It also makes the task of interpreting the data more
 *	difficult. Because the amount of data that the instrumented framework
 *	generates can be overwhelming, the RKH supports several types of filters
 *	that can use it to reduce the amount of data to be processed. The
 *	available groups are enumerated in RKH_TG_<group> definitions.
 *
 *  \param[in] ctrl	filter option, the available options are FILTER_ON or
 *                  FILTER_OFF.
 *  \param[in] grp	trace group. The available groups are enumerated in
 *                  RKH_TG_<group> definitions.
 *  \param[in] mode	filter mode. ECHANGE indicates that the all event's group
 *                  are accordingly changed as filter option value, otherwise
 *                  EUNCHANGE.
 *
 *  \usage
 *  \code
 *  void
 *  some_function(...)
 *  {
 *      RKH_FILTER_ON_GROUP(RKH_TRC_ALL_GROUPS);
 *      RKH_FILTER_ON_EVENT(RKH_TRC_ALL_EVENTS);
 *      ...
 *  }
 *  \endcode
 *
 *	\note
 *  This function is internal to RKH and the user application should not call
 *  it. Please use RKH_FILTER_ON_GROUP(), or RKH_FILTER_OFF_GROUP() macros
 *  instead.
 */
void rkh_trc_filter_group_(rui8_t ctrl, RKH_TG_T grp, rui8_t mode);

/**
 *  \brief
 *  Emit or suppress a specific event.
 *
 *  The stream is initially created with an empty filter (that is, without
 *  filtering any event type). If this is not the required behavior, the
 *  application can build a set of event types, include the appropriate event
 *  types in it, and apply it as a filter to the stream. After that, the
 *  stream will reject any event whose type is in the filter set.
 *
 *	Gathering many events generates a lot of data, which requires memory and
 *	processor time. It also makes the task of interpreting the data more
 *	difficult. Because the amount of data that the instrumented framework
 *	generates can be overwhelming, the RKH supports several types of filters
 *	that can use it to reduce the amount of data to be processed. The
 *	available events are enumerated in RKH_TE_<group>_<event> definitions.
 *
 *  \param[in] ctrl		filter option, the available options are FILTER_ON or
 *                      FILTER_OFF.
 *  \param[in] evt		trace event. The available events are enumerated in
 *                      RKH_TE_<group>_<event> definitions.
 *
 *  \usage
 *  \code
 *  void
 *  some_function(...)
 *  {
 *      RKH_FILTER_OFF_EVENT(RKH_TE_MP_INIT);
 *      RKH_FILTER_OFF_EVENT(RKH_TE_SMA_DCH);
 *      RKH_FILTER_OFF_EVENT(RKH_TE_FWK_OBJ);
 *      RKH_FILTER_OFF_EVENT(RKH_TE_FWK_SIG);
 *      RKH_FILTER_OFF_EVENT(RKH_TE_TMR_START);
 *      RKH_FILTER_OFF_EVENT(RKH_TE_TMR_TOUT);
 *      ...
 *	}
 *  \endcode
 *
 *	\note
 *  This function is internal to RKH and the user application should not call
 *  it. Please use RKH_FILTER_ON_EVENT(), or RKH_FILTER_OFF_EVENT() macros
 *  instead.
 */
void rkh_trc_filter_event_(rui8_t ctrl, RKH_TE_ID_T evt);

/**
 *  \brief
 *  Test the group and event filter condition.
 *
 *  \param[in] e	trace event ID. The available events are enumerated in
 *                  RKH_TE_<group>_<event> definitions.
 *
 *	\return
 *  '1' (RKH_TRUE) if the group and event is not filtered,
 *  otherwise '0' (RKH_FALSE).
 *
 *	\note
 *  This function is internal to RKH and the user application should not call
 *  it.
 */
rbool_t rkh_trc_isoff_(RKH_TE_ID_T e);

/**
 *  \brief
 *  Emmit or suppresse trace events related to a particular active
 *  object or event signal.
 *
 *  \param[in] filter	filter type.
 *  \param[in] slot		indicates the filter slot to be applied.
 *  \param[in] mode		filter option, the available options are FILTER_ON or
 *                      FILTER_OFF.
 *
 *	\note
 *  This function is internal to RKH and the user application should not call
 *  it. Please use RKH_FILTER_ON_SMA()/RKH_FILTER_ON_SIGNAL(), or
 *  RKH_FILTER_OFF_SMA()/RKH_FILTER_OFF_SIGNAL() macros instead.
 */
void rkh_trc_symFil(const RKH_TRC_FIL_T *filter,
                    RKH_TRC_FSLOT slot, rui8_t mode);

/**
 *  \brief
 *  Test the active objecto or signal filter condition.
 *
 *  \param[in] filter	filter type.
 *  \param[in] slot		indicates the filter slot to be applied.
 *
 *	\return
 *  '1' (RKH_TRUE) if the group and event is not filtered,
 *  otherwise '0' (RKH_FALSE).
 *
 *	\note
 *  This function is internal to RKH and the user application should not call
 *  it.
 */
rbool_t rkh_trc_symFil_isoff(const RKH_TRC_FIL_T *filter,
                             RKH_TRC_FSLOT slot);

/**
 *  \brief
 *  Store the trace record header in the stream.
 *
 *	- Trace event ID [n-bytes]. The number of bytes that it uses is specified 
 *	by the size of RKH_TE_ID_T data type.
 *
 *	- Sequence number [1-byte]. If the RKH_CFG_TRC_NSEQ_EN is set to 1 then
 *	RKH will add to the trace record an incremental number (1-byte), used
 *	like a sequence number.
 *
 *	- Timestamp [1, 2 or 4 bytes]. If the RKH_CFG_TRC_TSTAMP_EN is set to 1
 *	then RKH will add to the trace record a timestamp field. It's
 *	configurable by means of RKH_CFGPORT_TRC_SIZEOF_TSTAMP.
 *
 *	\param[in] eid		trace event ID. The available events are
 *                      enumerated in RKH_TE_<group>_<event> definitions.
 *
 *  \note
 *	This function should be called indirectly through the macro
 *	RKH_TRC_BEGIN.
 */
void rkh_trc_begin(RKH_TE_ID_T eid);

/**
 *  \brief
 *  Terminate the recorded trace event.
 *
 *	This function inserts a the flag byte, which delimits the frame.
 *	The flag is the 0x7E.
 *
 *  \note
 *	This function should be called indirectly through the macro
 *	RKH_TRC_END.
 */
void rkh_trc_end(void);

/**
 *  \brief
 *  Clear to zero the trace record checksum.
 *
 *  \note
 *	This function should be called indirectly through the macro
 *	RKH_TRC_BEGIN_DFT().
 */
void rkh_trc_clear_chk(void);

/**
 *  \brief
 *  Store a 8-bit data into the current trace event buffer without format
 *  information.
 *
 *  \param[in] d		data
 */
void rkh_trc_u8(rui8_t d);

/**
 *  \brief
 *  Store a 16-bit data into the current trace event buffer without format
 *  information.
 *
 *  \param[in] d		data
 */
void rkh_trc_u16(rui16_t d);

/**
 *  \brief
 *  Store a 32-bit data into the current trace event buffer without format
 *  information.
 *
 *  \param[in] d		data
 */
void rkh_trc_u32(rui32_t d);

/**
 *  \brief
 *  Store a string terminated in '\\0' into the current trace event buffer
 *  without format information.
 *
 *  \param[in] s		pointer to string treminated in '\\0'
 */
void rkh_trc_str(const char *s);

/**
 *  \brief
 *  Output object symbol record.
 *
 *  \param[in] tre		trace event ID. The available events are enumerated in
 *                      RKH_TE_<group>_<event> definitions.
 *  \param[in] obj		address of the object in memory.
 *  \param[in] obj_name	string terminated in '\\0'.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it.
 */
void rkh_trc_obj(RKH_TE_ID_T tre, rui8_t *obj, const char *obj_name);

/**
 *  \brief
 *  Output signal symbol record.
 *
 *  \param[in] sig		signal number.
 *  \param[in] sig_name	string terminated in '\\0'.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it.
 */
void rkh_trc_sig(RKH_SIG_T sig, const char *sig_name);

/**
 *  \brief
 *  Output active object (AO) symbol record.
 *
 *  \param[in] ao		address of active object symbol.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it.
 */
void rkh_trc_ao(struct RKH_SMA_T *ao);

/**
 *  \brief
 *  Output state symbol record.
 *
 *  \param[in] ao		address of active object symbol.
 *  \param[in] state	address of state symbol.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it.
 */
void rkh_trc_state(struct RKH_SMA_T *ao, rui8_t *state);

/**
 *  \brief
 *  Store a 8-bit data into the current trace event buffer with format
 *  information.
 *
 *  \param[in] fmt		format information
 *  \param[in] d		data
 */
void rkh_trc_fmt_u8(rui8_t fmt, rui8_t d);

/**
 *  \brief
 *  Store a 16-bit data into the current trace event buffer with format
 *  information.
 *
 *  \param[in] fmt		format information
 *  \param[in] d		data
 */
void rkh_trc_fmt_u16(rui8_t fmt, rui16_t d);

/**
 *  \brief
 *  Store a 32-bit data into the current trace event buffer with format
 *  information.
 *
 *  \param[in] fmt		format information
 *  \param[in] d		data
 */
void rkh_trc_fmt_u32(rui8_t fmt, rui32_t d);

/**
 *  \brief
 *  Store a string terminated in '\\0' into the current trace event buffer
 *  with format information.
 *
 *  \param[in] s		pointer to string terminated in '\\0'
 */
void rkh_trc_fmt_str(const char *s);

/**
 *  \brief
 *  Output memory block of up to 255-bytes with format information.
 *
 *  \param[in] mem		pointer to memory block.
 *  \param[in] size		size of memory block.
 */
void rkh_trc_fmt_mem(rui8_t const *mem, rui8_t size);

/**
 *  \brief
 *  Get a memory reference to every trace filter table.
 *
 *  \param[out] outFilterTbl   pointer to every filter table.
 */
void rkh_trc_filter_get(RKH_FilterTbl *outFilterTbl);

/* -------------------- External C language linkage end -------------------- */

#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */

#endif

/* ------------------------------ End of file ------------------------------ */
