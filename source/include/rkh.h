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
 *  \file       rkh.h
 *  \brief      RKH framwwork platform - independent interface.
 *
 *  \ingroup    apiSM
 *  \ingroup    apiAO
 *
 *  \addtogroup api
 *  @{
 *      \addtogroup apiSM State machines
 *      @{@}
 *      \addtogroup apiAO Active objects
 *      @{@}
 *      \addtogroup apiPort Port
 *      @{
 *          \addtogroup apiPortMisc Miscellaneous
 *          @{@}
 *          \addtogroup apiPortAO Active objects
 *          @{
 *          \brief Related to underlying OS/RTOS
 *          @}
 *      @}
 *      \addtogroup apiBSP BSP
 *      @{
 *          \addtogroup apiBSPHook Hooks
 *          @{
 *          \brief The hook functions allows to bsp/port developer to extend
 *                 the functionality of the framework.
 *
 *                 A RKH port cannot and should not define all the functions 
 *                 that it calls, because this would render the port too 
 *                 inflexible. The functions that RKH calls but doesn't 
 *                 actually implement are referred to as callback or hook 
 *                 functions. All these functions in RKH are easily 
 *                 indentifiable by the \b "_hook_" key word used in the 
 *                 function name, rkh_hook_dispatch(), rkh_hook_signal(), 
 *                 rkh_hook_timeout(), rkh_hook_start(), rkh_hook_exit(), and 
 *                 rkh_hook_idle(). 
 *                 Please, see RKH_CFG_HOOK_DISPATCH_EN, 
 *                 RKH_CFG_HOOK_SIGNAL_EN, RKH_CFG_HOOK_TIMEOUT_EN, 
 *                 RKH_CFG_HOOK_START_EN, and RKH_CFG_HOOK_EXIT_EN options 
 *                 from the \c rkhcfg.h.\n
 *          @}
 *          \addtogroup apiBSPTrc Trace
 *          @{
 *          \brief Related to manage a trace session with Trazer application.
*           See the \ref dbg section for more information. 
 *          @}
 *      @}
 *  @}
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.17.05  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/*
 *  (1) This header file must be included in all modules (*.c) that use RKH.
 */

/* --------------------------------- Module -------------------------------- */
#ifndef __RKH_H__
#define __RKH_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtrc.h"
#include "rkhsma.h"
#include "rkhrq.h"
#include "rkhmp.h"
#include "rkhtim.h"
#include "rkhassert.h"
#include "rkhfwk_hook.h"
#include "rkhfwk_bittbl.h"
#include "rkhfwk_module.h"
#include "rkhfwk_cast.h"

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

/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
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
