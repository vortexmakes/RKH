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
 *  2015.10.24  LeFr  v2.4.05  Initial version
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

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/**
 *	\brief
 *	This macro appears at the top of each C/C++ source file defining
 *	the version string for that file (module).
 *
 *  \param[in] __fname		file (module) name.
 *  \param[in] __version    file (module) version.
 */
#define RKH_MODULE_VERSION(__fname, __version) \
    static RKHROM char *const m_version = # __version;

/**
 *	\brief
 *	Get the module version.
 */
#define RKH_MODULE_GET_VERSION() \
    ((const char *)m_version);

/**
 *	\brief
 *	This macro appears at the top of each C/C++ source file defining
 *	the description string for that file (module).
 *
 *  \param[in] __fname		file (module) name.
 *  \param[in] __desc	    file (module) description.
 */
#define RKH_MODULE_DESC(__fname, __desc) \
    static RKHROM char *const m_desc = __desc;

/**
 *	\brief
 *	Get the module description.
 */
#define RKH_MODULE_GET_DESC() \
    ((const char *)m_desc)

#if RKH_CFGPORT_NATIVE_DYN_EVT_EN == RKH_ENABLED && \
    RKH_EN_DOXYGEN == RKH_DISABLED
    #define RKH_DYNE_TYPE           RKH_MP_T
    #define RKH_DYNE_INIT(mp, sstart, ssize, esize) \
        rkh_mp_init((mp),sstart,(rui16_t)ssize,(RKH_MPBS_T)esize)
    #define RKH_DYNE_GET_ESIZE(mp)  ((mp)->bsize)
    #define RKH_DYNE_GET(mp, e)     ((e) = (RKH_EVT_T *)rkh_mp_get((mp)))
    #define RKH_DYNE_PUT(mp, e)     (rkh_mp_put((mp), e))
    #define RKH_DYNE_GET_NUSED(mp)  ((mp)->nblocks - (mp)->nfree)
    #if RKH_CFG_MP_GET_LWM_EN == RKH_ENABLED
        #define RKH_DYNE_GET_NMIN(mp)   ((mp)->nmin)
    #else
        #define RKH_DYNE_GET_NMIN(mp)   (0)
    #endif
    #define RKH_DYNE_GET_PSIZE(mp)  ((mp)->nblocks)
#else
    #define RKH_DYNE_TYPE           rui8_t
    #define RKH_DYNE_INIT(mp, sstart, ssize, esize)   (void)0
    #define RKH_DYNE_GET_ESIZE(mp)  (void)0
    #define RKH_DYNE_GET(mp, e)     (void)0
    #define RKH_DYNE_PUT(mp, e)     (void)0
    #define RKH_DYNE_GET_NBLOCK(mp) (void)0
    #define RKH_DYNE_GET_NUSED(mp)  (void)0
    #define RKH_DYNE_GET_NMIN(mp)   (void)0
    #define RKH_DYNE_GET_PSIZE(mp)  (void)0
#endif

/**
 *  \brief
 *  Convert a pointer to a base-class. 
 *
 *  In other words, upcasting allows us to treat a derived type as though 
 *  it were its base type.
 *
 *  \ingroup apiAO
 */
#define RKH_UPCAST(BaseType_, me_)          ((BaseType_ *)me_)

/**
 *  \brief
 *  Converts a base-class pointer to a derived-class pointer.
 *
 *  \ingroup apiAO
 */
#define RKH_DOWNCAST(DerivedType_, me_)     ((DerivedType_ *)me_)

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
 *  Perform downcast of a reference of a base class to one of its derived
 *  classes.
 *
 *	\sa
 *	\link RKH_EVT_T single inheritance in C \endlink, and
 *	\link RKH_CREATE_BASIC_STATE another example \endlink.
 *
 *  \usage
 *  \code
 *  void
 *  svr_start( const struct RKH_SMA_T *me, RKH_EVT_T *pe )
 *  {
 *      START_EVT_T *e_start;
 *
 *      e_start = RKH_ALLOC_EVT( START_EVT_T, START, me );
 *      e_start->clino = RKH_CAST(REQ_EVT_T, pe)->clino;
 *      RKH_SMA_POST_FIFO( RKH_GET_SMA( RKH_CAST(REQ_EVT_T, pe)->clino ),
 *												RKH_EVT_CAST(e_start), me );
 *  }
 *  \endcode
 */
#define RKH_CAST(_type, _obj)     ((_type *)(_obj))

/* -------------------------------- Constants ------------------------------ */
#ifndef NULL
#define NULL    (void *)0
#endif

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/**
 *  \brief
 *  Priority arranged table of registered SMA.
 *
 *  Register a state machine application into the framework implies to store
 *  a pointer to the SMA in the priority table. A unique priority number must
 *  be assigned to each SMA from 0 to RKH_LOWEST_PRIO. The lower the number,
 *  the higher the priority.
 */
extern RKH_SMA_T *rkh_sptbl[RKH_CFG_FWK_MAX_SMA];

/**
 *  \brief
 *  String describing the RKH version.
 */
extern RKHROM char rkh_version[];

/**
 *  \brief
 *  String representing the name of undefined object name.
 */
extern RKHROM char noname[];

/* -------------------------- Function prototypes -------------------------- */
/**
 *  \brief
 *  Initializes the RKH framework.
 *
 *  A requirement of RKH is that must be called rkh_fwk_init() before call any
 *  of its other services. This function initializes all of RKH's variables
 *  and data structures.
 *
 *  \note
 *	Platform-dependent function. All RKH ports must be define it in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \usage
 *	Implementation example for x86, linux emulator of simple cooperative 
 *	scheduler non-preemptive.
 *  \snippet linux_st_rkhport.c Initializes the RKH framework
 *
 *  \ingroup apiPortMisc
 */
void rkh_fwk_init(void);

/**
 *  \brief
 *  RKH framework is started.
 *
 *  This entry function turns over control to RKH (and does not return!).
 *  This function runs the highest priority state machine application (SMA)
 *  that is ready to run in run-to-completation model.
 *
 *  \note
 *  The call to this function does not return. Hence, any code after it will
 *  never be executed.
 *
 *  \note
 *	Platform-dependent function. All RKH ports must be define it in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \usage
 *	Implementation example for x86, linux emulator of simple cooperative 
 *	scheduler non-preemptive.
 *  \snippet linux_st_rkhport.c Run RKH framework
 *
 *	Here is the basic algorithm for interpreting the listing shown above.
 *	A pseudocode description of the procedure is:
 *  \include pseudo_cooperative_emulator.c
 *
 *  \ingroup apiPortMisc
 */
void rkh_fwk_enter(void);

/**
 *  \brief
 *  Exit the RKH framework.
 *
 *  Function invoked by the application layer to exit the RKH application and
 *  return control to the underlying OS/Kernel.
 *
 *  \note
 *	This function is strongly platform-dependent. All RKH ports and must be
 *	defined in the RKH port to a particular platform.
 *	Some RKH ports might not require implementing this function at all,
 *	because many embedded applications don't have anything to exit to.
 *
 *  \note
 *	Platform-dependent function. All RKH ports must be defined in the RKH
 *	port file to a particular platform. However, only the ports to the
 *	external OS/RTOS usually need some code to bolt the framework to the
 *	external OS/RTOS.
 *
 *  \usage
 *	Implementation example for x86, linux emulator of simple cooperative 
 *	scheduler non-preemptive.
 *  \snippet linux_st_rkhport.c Exit the RKH framework
 *
 *  \ingroup apiPortMisc
 */
void rkh_fwk_exit(void);

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
