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
 *  \file       rkhtmr.h
 *  \brief      Specifies the interface of software timer services.
 *  \ingroup    apiTmr
 *
 *  \addtogroup api
 *  @{
 *  \addtogroup apiTmr Timer
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
#ifndef __RKHTMR_H__
#define __RKHTMR_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhitl.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#if defined(RKH_USE_TRC_SENDER)
/**
 *  \brief
 *  Invoke the system clock tick processing rkh_tmr_tick().
 *
 *  This macro is the recommended way of invoke the clock tick processing,
 *  because it provides the vital information for software tracing and
 *  avoids any overhead when the tracing is disabled.
 *
 *  \param[in] _sender	pointer to the sender object. Typically
 *                      RKH_TIM_TICK() will be called from an interrupt,
 *                      in which case it would create a unique object
 *                      just to unambiguously identify the ISR as the
 *                      sender of the time events.
 *	\sa
 *	rkh_tmr_tick().
 *
 *	\ingroup apiBSPHook
 */
    #define RKH_TIM_TICK(_sender)     rkh_tmr_tick(_sender)
#else
    #define RKH_TIM_TICK(dummy_)      rkh_tmr_tick()
#endif

/**
 *  \brief
 *	Initializes the previously allocated timer structure RKH_TMR_T.
 *
 *  A timer is declared with the RKH_TMR_T data type and is defined with
 *  the RKH_TMR_INIT() service.
 *	The timer is initialized in a non-active state (stopped). In this
 *	case, a subsequent start service call is necessary to get the timer
 *	actually started.
 *  The following listing creates an application timer that executes
 *  "my_timer_hook" and send the event signal "TOUT" to "pwr" SMA after
 *  100 timer-ticks.
 *
 *	\param[in] t_	pointer to previously allocated timer structure. Any
 *					software module intending to install a software timer
 *					must first allocate a timer structure RKH_TMR_T.
 *	\param[in] e_	event to be directly posted (using the FIFO policy)
 *					into the event queue of the target agreed state
 *					machine application at the timer expiration.
 *	\param[in] th_  hook function to be called at the timer expiration.
 *					This argument is optional, thus it could be declared
 *					as NULL or eliminated in compile-time with
 *					RKH_CFG_TMR_HOOK_EN.
 *
 *	\note
 *	See RKH_TMR_T structure for more information.
 *
 *  \usage
 *  \code
 *	#define MY_TICK				100
 *
 *	static RKH_TMR_T my_timer;
 *	static RKH_ROM_STATIC_EVENT( e_timer, TOUT );
 *
 *  ...
 *  RKH_TMR_INIT( &my_timer, &e_timer, my_timer_hook );
 *  RKH_TMR_ONESHOT( &my_timer, pwr, MY_TICK );
 *  \endcode
 *
 *  \ingroup apiTmr
 */
#if RKH_CFG_TMR_HOOK_EN == RKH_ENABLED
    #define RKH_TMR_INIT(t_, e_, th_) \
        rkh_tmr_init_((t_), (e_), (th_))
#else
    #define RKH_TMR_INIT(t_, e_, th_) \
        rkh_tmr_init_((t_), (e_))
#endif

/**
 *  \brief
 *  Start a timer as one-shot timer.
 *
 *  This operation installs a previously created timer into	the
 *  timer-handling facility. The timer begins running at the completion of
 *  this operation. The timer won't be re-started automatically.
 *  The following listing creates an application timer that executes
 *  "my_timer_hook" and send the event signal "TOUT" to "pwr" SMA after 100
 *  timer-ticks.
 *
 *	\param[in] t	    pointer to previously created timer structure.
 *	\param[in] sma	    state machine application (SMA) that receives the timer
 *					    event.
 *  \param[in] itick    number of ticks for timer expiration.
 *
 *  \usage
 *  \code
 *	#define MY_TICK				100
 *
 *	static RKH_TMR_T my_timer;
 *	static RKH_ROM_STATIC_EVENT( e_timer, TOUT );
 *
 *  ...
 *  RKH_TMR_INIT( &my_timer, e_timer, my_timer_hook );
 *  RKH_TMR_ONESHOT( &my_timer, pwr, MY_TICK );
 *  \endcode
 *
 *  \ingroup apiTmr
 */
#define RKH_TMR_ONESHOT(t, sma, itick) \
    (t)->period = 0; \
    rkh_tmr_start(t, sma, itick)

/**
 *  \brief
 *  Start a timer as periodic timer.
 *
 *  This operation installs a previously created timer into	the
 *  timer-handling facility. The timer begins running at the completion of
 *  this operation. Once the timeout will expire the timer will be
 *  re-started (re-triggered) again automatically.
 *  The following listing creates an application timer that executes
 *  "my_timer_hook" and send the event signal "TOUT" to "pwr" SMA after 100
 *  timer-ticks initially and then after every 25 timer-ticks.
 *
 *	\param[in] t		pointer to previously created timer structure.
 *	\param[in] sma		state machine application (SMA) that receives the timer
 *					    event.
 *  \param[in] itick    number initial of ticks for timer expiration.
 *  \param[in] per	    number of ticks for all timer expirations after the 
 *                      first (expiration period). A zero for this parameter 
 *                      makes the timer a one-shot timer, otherwise, for 
 *                      periodic timers, any value in range.
 *
 *  \usage
 *  \code
 *	#define MY_TICK			100
 *
 *	static RKH_TMR_T my_timer;
 *	static RKH_ROM_STATIC_EVENT( e_timer, TOUT );
 *
 *  ...
 *  RKH_TMR_INIT( &my_timer, &e_timer, my_timer_hook );
 *  RKH_TMR_PERIODIC( &my_timer, pwr, MY_TICK, MY_TICK/4 );
 *  \endcode
 *
 *  \ingroup apiTmr
 */
#define RKH_TMR_PERIODIC(t, sma, itick, per) \
    (t)->period = (per); \
    rkh_tmr_start((t), (sma), (itick))

/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/**
 *  \brief
 *  The prototype of callback function (hook) to call when the timer expires.
 *
 *  \param[in] t		pointer to elapsed timer (RKH_TMR_T data structure).
 */
typedef void (*RKH_THK_T)(void *t);

/**
 *  \brief
 *  This data type defines the dynamic range of the time delays measured in
 *  clock ticks (maximum number of ticks).
 *
 *	The valid values [in bits] are 8, 16 or 32. Default is 8. This type is
 *	configurable via the preprocessor switch RKH_CFG_TMR_SIZEOF_NTIMER.
 */
#if RKH_CFG_TMR_SIZEOF_NTIMER == 8
typedef rui8_t RKH_TNT_T;
#elif RKH_CFG_TMR_SIZEOF_NTIMER == 16
typedef rui16_t RKH_TNT_T;
#elif RKH_CFG_TMR_SIZEOF_NTIMER == 32
typedef rui32_t RKH_TNT_T;
#else
typedef rui8_t RKH_TNT_T;
#endif

/**
 *  \brief
 *  Defines the data structure into which the performance information for
 *  software timers is stored.
 *
 *	The application must allocate an RKH_TINFO_T data structure used to
 *	receive information. The performance information is available during
 *	run-time for each of the RKH services. This can be useful in determining
 *	whether the application is performing properly, as well as helping to
 *	optimize the application.
 */
typedef struct RKH_TINFO_T
{
    rui16_t nexp;       /** # of expirations */
    rui16_t nstart;     /**	# of start requests */
    rui16_t nstop;      /**	# of stop requests */
} RKH_TINFO_T;

typedef struct RKH_TMR_T RKH_TMR_T;

/**
 *  \brief
 *  Defines the data structure used to maintain information that allows the
 *  timer-handling facility to update and expire software timers.
 *
 *  RKH software timers enables to execute application C functions and/or
 *  send an event to application state machine (SMA) at specific intervals of
 *  time. It can also set an application timer to expire only once. This type
 *  of timer is called a one-shot timer, while repeating interval timers are
 *  called periodic timers. Each application timer is a public resource.
 *	Time intervals are measured by periodic timer interrupts. Each timer
 *	interrupt is called a timer-tick. The actual time between timer-ticks is
 *	specified by the application. On the other hand, application timers
 *	execute in the order in which they become active.
 *
 *	\note
 *  RKH prohibits an application from explicitly modifying the RKH_TMR_T
 *  structure. The RKH's timer structures can be located anywhere in memory,
 *  but it is most common to make it a global structure by defining it
 *  outside the scope of any function.
 *  An RKH timer is created when an application timer is declared with the
 *  RKH_TMR_T data type. The following listing declares "my_timer" timer:
 *
 *  \code
 *  RKH_TMR_T my_timer;
 *  \endcode
 *
 *  \ingroup apiTmr
 */
struct RKH_TMR_T
{
    /**
     *  Points to timer event.
     */
    RKH_EVT_T *evt;

    /**
     *  Points to next timer structure in the doubly linked list.
     */
    RKH_TMR_T *tnext;

    /**
     *  \brief
     *  State machine application (a.k.a Active Object) that receives the
     *  timer event.
     */
    const struct RKH_SMA_T *sma;

    /**
     *  \brief
     *  Tick down-counter.
     */
    RKH_TNT_T ntick;

    /**
     *  \brief
     *  Number of ticks for all timer expirations after the first (expiration
     *  period). A zero for this parameter makes the timer a one-shot timer,
     *  otherwise, for periodic timers, any value in range.
     */
    RKH_TNT_T period;

    /**
     *  A non-zero value indicates that the timer is linked.
     */
    rui8_t used;

    /**
     *	Hook function to call when the timer expires. This member is optional,
     *	thus it could be declared as NULL or eliminated in compile-time with
     *	RKH_CFG_TMR_HOOK_EN.
     */
#if RKH_CFG_TMR_HOOK_EN == RKH_ENABLED
    RKH_THK_T timhk;
#endif

    /**
     *  Performance information. This member is optional, thus it could be
     *  eliminated in compile-time with RKH_CFG_TMR_GET_INFO_EN.
     */
#if RKH_CFG_TMR_GET_INFO_EN == RKH_ENABLED
    RKH_TINFO_T info;
#endif
};

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
#if RKH_CFG_TMR_HOOK_EN == RKH_ENABLED
    /**
     *  \brief
     *	Initializes the previously allocated timer structure RKH_TMR_T.
     */
    void rkh_tmr_init_(RKH_TMR_T *t, const RKH_EVT_T *e, RKH_THK_T thk);
#else
    void rkh_tmr_init_(RKH_TMR_T *t, const RKH_EVT_T *e);
#endif

/**
 *  \brief
 *  Start a timer.
 *
 *  This operation installs a previously created timer into	the
 *  timer-handling facility. The timer begins running at the completion of
 *  this operation.
 *
 *	\param[in] t		pointer to previously created timer structure.
 *	\param[in] sma		state machine application (SMA) that receives the 
 *	                    timer event.
 *  \param[in] itick    number of ticks for timer expiration.
 *
 *  \ingroup apiTmr
 */
void rkh_tmr_start(RKH_TMR_T *t,   const struct RKH_SMA_T *sma,
                   RKH_TNT_T itick);

/**
 *  \brief
 *	Stops a running timer.
 *
 *	This operation stops a timer by removing the currently running timer from
 *	the timer-handling facility. If the timer is already stopped, this
 *	service has no effect.
 *
 *	\param[in] t		pointer to previously created timer structure.
 *
 *  \ingroup apiTmr
 */
void rkh_tmr_stop(RKH_TMR_T *t);

/**
 *  \brief
 *  Retrieves performance information for a particular software timer.
 *
 *	The user application must allocate an RKH_TINFO_T data structure used
 *	to receive data. The performance information is available during run-time
 *	for each of the RKH services. This can be useful in determining whether
 *	the application is performing properly, as well as helping to optimize
 *	the application. This information provides a "snapshot" a particular
 *	instant in time, i.e., when the service is invoked.
 *
 *	\param[in] t		pointer to previously created timer structure.
 *  \param[in] info		pointer to the buffer into which the performance
 *                      information will be copied by reference.
 *
 *  \note
 *  See RKH_TINFO_T structure for more information. This function is
 *  optional, thus it could be eliminated in compile-time with
 *  RKH_CFG_TMR_GET_INFO_EN.
 *
 *  \ingroup apiTmr
 */
void rkh_tmr_get_info(RKH_TMR_T *t, RKH_TINFO_T *info);

/**
 *  \brief
 *  Clear performance information for a particular software timer.
 *
 *	\param[in] t		pointer to previously created timer structure.
 *
 *  \note
 *  See RKH_TINFO_T structure for more information. This function is
 *  optional, thus it could be eliminated in compile-time with
 *  RKH_CFG_TMR_GET_INFO_EN.
 *
 *  \ingroup apiTmr
 */
void rkh_tmr_clear_info(RKH_TMR_T *t);

#if defined(RKH_USE_TRC_SENDER)
/**
 *  \brief
 *  Keep tracks and updates the started timers.
 *
 *	Time intervals are measured by periodic timer interrupts. Each timer
 *	interrupt is called a timer-tick. The actual time between timer-ticks
 *	is specified by the application.
 *  This function must be placed where will be incrementing the system
 *  tick. Normally this function is placed in a timer ISR routine.
 *  If one or more timers expires the assigned event is directly posted
 *  into the state machine application (SMA) queue and associated hook
 *  function is executed (if it's used). The expiration events of timers
 *  that expire at the same time are executed in the order they were
 *  started.
 *
 *  \note
 *  This function is internal to RKH and the user application should
 *  not call it. Instead, use #RKH_TIM_TICK() macro.
 */
void rkh_tmr_tick(const void *const sender);
#else
void rkh_tmr_tick(void);
#endif

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
