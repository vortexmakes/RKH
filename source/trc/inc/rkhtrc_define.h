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
 *  RKH site: http://vortexmakes.com/que-es/
 *  RKH GitHub: https://github.com/vortexmakes/RKH
 *  RKH Sourceforge: https://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail: lf@vortexmakes.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       rkhtrc_define.h
 *  \brief      Defines constants and macros which are internally used by RKH 
 *              trace facility.
 *  \ingroup    apiTrc
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.04.15  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHTRC_DEF_H__
#define __RKHTRC_DEF_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhitl.h"

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
            && rkh_trc_symFil_isoff(RKHFilterSma, (RKH_TRC_FSLOT)(prio))
#else
    #define RKH_TRC_AO_ISOFF(prio)
#endif

/**
 */
#define RKH_TRC_IS_RESERVED_SIG(sig) \
    (sig == RKH_COMPLETION_EVENT) 
    
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
            && (RKH_TRC_IS_RESERVED_SIG(sig) || \
            rkh_trc_symFil_isoff(RKHFilterSignal, (RKH_TRC_FSLOT)(sig)))
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
#define RKH_QUE_START                GRPLSH(RKH_TG_QUE)
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
#define RKH_QUE_TTBL_RANGE           1
#define RKH_SMA_TTBL_RANGE          2
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
         RKH_QUE_TTBL_RANGE   + \
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
#define RKH_QUE_TTBL_OFFSET          (RKH_MP_TTBL_OFFSET + RKH_MP_TTBL_RANGE)
#define RKH_SMA_TTBL_OFFSET         (RKH_QUE_TTBL_OFFSET + RKH_QUE_TTBL_RANGE)
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

/** \brief  Reference Queue group (QUE) */
#define RKH_TG_QUE           1

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

/* --- Queue events (QUE group) --------------------------------------------- */
/** \copybrief RKH_TR_QUE_INIT */
#define RKH_TE_QUE_INIT          RKH_QUE_START         
/** \copybrief RKH_TR_QUE_GET */
#define RKH_TE_QUE_GET           (RKH_TE_QUE_INIT + 1)
/** \copybrief RKH_TR_QUE_FIFO */
#define RKH_TE_QUE_FIFO          (RKH_TE_QUE_GET + 1)
/** \copybrief RKH_TR_QUE_LIFO */
#define RKH_TE_QUE_LIFO          (RKH_TE_QUE_FIFO + 1)
/** \copybrief RKH_TR_QUE_FULL */
#define RKH_TE_QUE_FULL          (RKH_TE_QUE_LIFO + 1)
/** \copybrief RKH_TR_QUE_DPT */
#define RKH_TE_QUE_DPT           (RKH_TE_QUE_FULL + 1)
/** \copybrief RKH_TR_QUE_GET_LAST */
#define RKH_TE_QUE_GET_LAST      (RKH_TE_QUE_DPT +1 )
#define RKH_QUE_END              RKH_TE_QUE_GET_LAST

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
/** \copybrief RKH_TR_SMA_DEFER */
#define RKH_TE_SMA_DEFER        (RKH_TE_SMA_UNREG + 1)
/** \copybrief RKH_TR_SMA_RCALL */
#define RKH_TE_SMA_RCALL        (RKH_TE_SMA_DEFER + 1)
#define RKH_SMA_END             RKH_TE_SMA_RCALL

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
/** \copybrief RKH_TR_SM_DCH */
#define RKH_TE_SM_DCH           (RKH_TE_SM_EXE_ACT + 1)
#define RKH_SM_END              RKH_TE_SM_DCH

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
/** \copybrief RKH_TR_FWK_OBJ */
#define RKH_TE_FWK_OBJ          (RKH_TE_FWK_GCR + 1)
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

#if ((RKH_QUE_END - RKH_QUE_START) > ((RKH_QUE_TTBL_RANGE * 8) - 1))
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

#if ((RKH_TMR_END - RKH_TMR_START) > ((RKH_TIM_TTBL_RANGE * 8) - 1))
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
#if RKH_CFG_QUE_SIZEOF_NELEM == 8
        #define RKH_TRC_NE(ne) \
            RKH_TRC_UI8(ne)
        #if RKH_CFG_QUE_GET_LWMARK_EN == RKH_ENABLED
            #define RKH_TRC_QUE_NMIN(nm) \
                RKH_TRC_UI8(nm)
        #else
            #define RKH_TRC_QUE_NMIN(nm)
        #endif
#elif RKH_CFG_QUE_SIZEOF_NELEM == 16
        #define RKH_TRC_NE(ne) \
            RKH_TRC_UI16(ne)
        #if RKH_CFG_QUE_GET_LWMARK_EN == RKH_ENABLED
            #define RKH_TRC_QUE_NMIN(nm) \
                RKH_TRC_UI16(nm)
        #else
            #define RKH_TRC_QUE_NMIN(nm)
        #endif
#elif RKH_CFG_QUE_SIZEOF_NELEM == 32
        #define RKH_TRC_NE(ne) \
            RKH_TRC_UI32(ne)
        #if RKH_CFG_QUE_GET_LWMARK_EN == RKH_ENABLED
            #define RKH_TRC_QUE_NMIN(nm) \
                RKH_TRC_UI32(nm)
        #else
            #define RKH_TRC_QUE_NMIN(nm)
        #endif
#else
        #define RKH_TRC_NE(ne) \
            RKH_TRC_UI8(ne)
        #if RKH_CFG_QUE_GET_LWMARK_EN == RKH_ENABLED
            #define RKH_TRC_QUE_NMIN(nm) \
                RKH_TRC_UI8(nm)
        #else
            #define RKH_TRC_QUE_NMIN(nm)
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
 *  Insert an event size value as trace record argument.
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

/* ------------------------------- Data types ------------------------------ */
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

#if RKH_CFG_TRC_SIZEOF_STREAM < 255u
    typedef rui8_t TRCQTY_T;
#else
    typedef rui16_t TRCQTY_T;
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

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
