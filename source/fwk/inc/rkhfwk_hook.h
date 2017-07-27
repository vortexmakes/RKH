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
 *  \file       rkhfwk_hook.h
 *  \brief      Specifies the interface of hook functions.
 *  \ingroup    fwk
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.25.04  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHFWK_HOOK_H__
#define __RKHFWK_HOOK_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtype.h"
#include "rkhsma.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#if (RKH_CFG_HOOK_DISPATCH_EN == RKH_ENABLED)
    #define RKH_HOOK_DISPATCH(sma, e) \
        rkh_hook_dispatch((sma), (RKH_EVT_T *)(e))
#else
    #define RKH_HOOK_DISPATCH(sma, e)   (void)0
#endif

#if (RKH_CFG_HOOK_TIMEOUT_EN == RKH_ENABLED)
    #define RKH_HOOK_TIMEOUT(t)     rkh_hook_timeout((t))
#else
    #define RKH_HOOK_TIMEOUT(t)     (void)0
#endif

#if (RKH_CFG_HOOK_SIGNAL_EN == RKH_ENABLED)
    #define RKH_HOOK_SIGNAL(e)      rkh_hook_signal((RKH_EVT_T *)(e))
#else
    #define RKH_HOOK_SIGNAL(e)      (void)0
#endif

#if (RKH_CFG_HOOK_START_EN == RKH_ENABLED)
    #define RKH_HOOK_START()        rkh_hook_start()
#else
    #define RKH_HOOK_START()        (void)0
#endif

#if (RKH_CFG_HOOK_EXIT_EN == RKH_ENABLED)
    #define RKH_HOOK_EXIT()         rkh_hook_exit()
#else
    #define RKH_HOOK_EXIT()         (void)0
#endif

#if (RKH_CFG_HOOK_TIMETICK_EN == RKH_ENABLED)
    #define RKH_HOOK_TIMETICK()     rkh_hook_timetick()
#else
    #define RKH_HOOK_TIMETICK()     (void)0
#endif

#if (RKH_CFG_HOOK_PUT_TRCEVT_EN == RKH_ENABLED)
    #define RKH_HOOK_PUT_TRCEVT()   rkh_hook_putTrcEvt()
#else
    #define RKH_HOOK_PUT_TRCEVT()   (void)0
#endif

/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/**
 *  \brief
 *  When dispatching an event to a SMA the dispatch hook function will be
 *  executed.
 *
 *  \param[in] me  pointer to previously created state machine application.
 *	\param[in] e    pointer to arrived event.
 *
 *	\note
 *	The dispatch hook will only get called if RKH_CFG_HOOK_DISPATCH_EN is
 *	set to 1 within rkhcfg.h file. When this is set the application must
 *	provide the hook function.
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_dispatch(RKH_SMA_T *me, RKH_EVT_T *e);

/**
 *  \brief
 *  When the producer of an event directly posts the event to the event queue
 *  of the consumer SMA the rkh_hook_signal() will optionally called.
 *
 *	\param[in] e    pointer to arrived event.
 *
 *	\note
 *	The signal hook will only get called if RKH_CFG_HOOK_SIGNAL_EN is set
 *	to 1 within rkhcfg.h file. When this is set the application must provide
 *	the hook function.
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_signal(RKH_EVT_T *e);

/**
 *  \brief
 *  If a timer expires the rkh_hook_timeout() function is called just before
 *  the assigned event is directly posted into the state machine application
 *  queue.
 *
 *	\param[in] t    pointer to previously allocated timer structure.
 *					A cast to RKH_TMR_T data type must be internally
 *					implemented to get the appropiated timer control block.
 *
 *	\note
 *	The timeout hook will only get called if RKH_CFG_HOOK_TIMEOUT_EN is set
 *	to 1 within rkhcfg.h file. When this is set the application must provide
 *	the hook function.
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_timeout(const void *t);

/**
 *  \brief
 *  This hook function is called just before the RKH takes over control of
 *  the application.
 *
 *	\note
 *	The start hook will only get called if RKH_CFG_HOOK_START_EN is set to 1
 *	within rkhcfg.h file. When this is set the application must provide the
 *	hook function.
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_start(void);

/**
 *  \brief
 *  This hook function is called just before the RKH returns to the
 *  underlying OS/RTOS. Usually, the rkh_hook_exit() is useful when executing
 *  clean-up code upon SMA terminate or framework exit.
 *
 *	\note
 *	The exit hook will only get called if RKH_CFG_HOOK_EXIT_EN is set to 1
 *	within rkhcfg.h file. When this is set the application must provide the
 *	hook function.
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_exit(void);

/**
 *  \brief
 *  An idle hook function will only get executed (with interrupts LOCKED)
 *  when there are no SMAs of higher priority that are ready to run.
 *
 *  This makes the idle hook function an ideal place to put the processor
 *  into a low power state - providing an automatic power saving whenever
 *  there is no processing to be performed.
 *
 *  \note
 *	The rkh_hook_idle() callback is called with interrupts locked, because the
 *	determination of the idle condition might change by any interrupt posting
 *	an event. This function must internally unlock interrupts, ideally
 *	atomically with putting the CPU to the power-saving mode.
 *
 *  \usage
 *	\code
 *	void
 *	rkh_hook_idle( void )       // NOTE: entered with interrupts DISABLED
 *	{
 *		RKH_ENA_INTERRUPT();	// must at least enable interrupts
 *		...
 *	}
 *	\endcode
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_idle(void);

/**
 *  \brief
 *  This function is called by rkh_tmr_tick(), which is assumed to be called
 *  from an ISR. rkh_hook_timetick() is called at the very beginning of
 *  rkh_tmr_tick(), to give priority to user or port-specific code when the
 *  tick interrupt occurs.
 *
 *	Usually, this hook allows to the application to extend the functionality
 *	of RKH, giving the port developer the opportunity to add code that will
 *	be called by rkh_tmr_tick(). Frequently, the rkh_hook_timetick() is
 *	called from the tick ISR and must not make any blocking calls and must
 *	execute as quickly as possible.
 *
 *	\note
 *	The time tick hook will only get called if RKH_CFG_HOOK_TIMETICK_EN is
 *	set to 1 within rkhcfg.h file. When this is set the application must
 *	provide the hook function.
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_timetick(void);

/**
 *  \brief
 *  This function is called from rkh_trc_end() function, at the end of that, 
 *  to allow to the application to extend the functionality of RKH, giving 
 *  the port developer the opportunity to add code that will be called when 
 *  is put a trace event into the stream buffer.
 *
 *	\ingroup apiBSPHook
 */
void rkh_hook_putTrcEvt(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
