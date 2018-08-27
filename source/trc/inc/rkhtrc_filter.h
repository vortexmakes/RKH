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
 *  \file       rkhtrc_filter.h
 *  \brief      Specifies the runtime filter operations for the trace facility.
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
#ifndef __RKHTRC_FILTER_H__
#define __RKHTRC_FILTER_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtrc_define.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#if RKH_CFG_TRC_EN == RKH_ENABLED && RKH_CFG_TRC_RTFIL_EN == RKH_ENABLED
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
            rkh_trc_symFil(RKHFilterSma, RKH_SMA_ACCESS_CONST(sma, prio), \
                           FILTER_ON)

    /**
     *  \brief
     *  Suppress all enabled trace events related to active objects.
     *
     *  \ingroup apiTrc 
     */
        #define RKH_FILTER_ON_ALL_SMA() \
            rkh_trc_symFil(RKHFilterSma, 0, RKH_TRC_SET_ALL(FILTER_ON))

    /**
     *  \brief
     *  Emmit the enabled trace events related to a specified active
     *  object.
     *
     *  \ingroup apiTrc 
     */
        #define RKH_FILTER_OFF_SMA(sma) \
            rkh_trc_symFil(RKHFilterSma, RKH_SMA_ACCESS_CONST(sma, prio), \
                           FILTER_OFF)

    /**
     *  \brief
     *  Emmit all enabled trace events related to active objects.
     *
     *  \ingroup apiTrc 
     */
        #define RKH_FILTER_OFF_ALL_SMA() \
            rkh_trc_symFil(RKHFilterSma, 0, RKH_TRC_SET_ALL(FILTER_OFF))

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
            rkh_trc_symFil(RKHFilterSignal, (sig), FILTER_ON)

    /**
     *  \brief
     *  Suppress all enabled trace events related to signals.
     *
     *  \ingroup apiTrc 
     */
        #define RKH_FILTER_ON_ALL_SIGNALS() \
            rkh_trc_symFil(RKHFilterSignal, 0, RKH_TRC_SET_ALL(FILTER_ON))

    /**
     *  \brief
     *  Emmit the enabled trace events related to a specified event
     *  signal.
     *
     *  \ingroup apiTrc 
     */
        #define RKH_FILTER_OFF_SIGNAL(sig) \
            rkh_trc_symFil(RKHFilterSignal, (sig), FILTER_OFF)

    /**
     *  \brief
     *  Emmit all enabled trace events related to signals.
     *
     *  \ingroup apiTrc 
     */
        #define RKH_FILTER_OFF_ALL_SIGNALS() \
            rkh_trc_symFil(RKHFilterSignal, 0, RKH_TRC_SET_ALL(FILTER_OFF))
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

/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
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

typedef enum
{
    FILTER_ON, FILTER_OFF
} RKH_TRC_FOPT;

typedef enum RKHFilter
{
    RKHFilterTrcEvt, RKHFilterSignal, RKHFilterSma,
    RKHFilterNums
} RKHFilter;

typedef struct RKH_FilterTbl
{
    const RKH_TRC_FIL_T *signal;
    const RKH_TRC_FIL_T *ao;
    rui8_t *event;
    rui8_t *group;
    const RKH_GMTBL_T *grpFilMap;
} RKH_FilterTbl;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
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
 *  \param[in] fd    	filter type.
 *  \param[in] slot		indicates the filter slot to be applied.
 *  \param[in] mode		filter option, the available options are FILTER_ON or
 *                      FILTER_OFF.
 *
 *	\note
 *  This function is internal to RKH and the user application should not call
 *  it. Please use RKH_FILTER_ON_SMA()/RKH_FILTER_ON_SIGNAL(), or
 *  RKH_FILTER_OFF_SMA()/RKH_FILTER_OFF_SIGNAL() macros instead.
 */
void rkh_trc_symFil(RKHFilter fd, RKH_TRC_FSLOT slot, rui8_t mode);

/**
 *  \brief
 *  Test the active objecto or signal filter condition.
 *
 *  \param[in] fd    	filter type.
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
rbool_t rkh_trc_symFil_isoff(RKHFilter fd, RKH_TRC_FSLOT slot);

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
