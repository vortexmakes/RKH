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
 *  \file       rkhport.h
 *  \ingroup    prt
 *
 *  \brief      CIAA Osek multithread port
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  DaBa  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 *  DaBa  Darío Baliña  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
#ifndef __RKHPORT_H__
#define __RKHPORT_H__

/* ----------------------------- Include files ----------------------------- */

#include "os.h"
#include "Os_Internal_Arch_Cfg.h"
#include "Os_Internal_Cfg.h"

#include "rkhtype.h"
#include "rkhrq.h"
#include "rkhmp.h"
#include "rkhrdy.h"

/* ---------------------- External C language linkage ---------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#define RKH_SMA_BLOCK(sma) \
    while (((RKH_SMA_T*)(sma))->equeue.qty == (RKH_RQNE_T)0) \
    { \
        RKH_EXIT_CRITICAL_(); \
        WaitEvent(((RKH_SMA_T*)(sma))->os_signal); \
        ClearEvent(((RKH_SMA_T*)(sma))->os_signal); \
        RKH_ENTER_CRITICAL_(); \
    }

#define RKH_SMA_READY(rg, sma) \
    SetEvent(((RKH_SMA_T*)(sma))->thread, \
             ((RKH_SMA_T*)(sma))->os_signal)

#define RKH_SMA_UNREADY(rg, sma)      (void)0

#define RKH_SMA(x)              ((struct SMA**)&x)
#define RKH_TASK_FUNCTION(sma)  rkh_task_function(RKH_SMA(sma))

/*
 *	CIAA OSEK Ent. critical section operations.
 *	Note: the CIAA OSEK critical section must be able to nest.
 *	Note: SuspendOSInterrupts()/ suspends/resumes all ISR2 type interrupts,
 *	to also suspend/resume ISR1 interrupts use
 *	SuspendAllInterrupts()/ResumeAllInterrupts()
 *	In this porting version the critical sections are protected by disabling
 *	CPU interrupts. A better way would be using the Resource mechanism.
 *	This avoid the priority inversion problem and longer delays that disabling
 *	interrupts can cause (Avoided with AO concepts).
 */

#define RKH_DIS_INTERRUPT()             DisableAllInterrupts()
#define RKH_ENA_INTERRUPT()             EnableAllInterrupts()
#define RKH_ENTER_CRITICAL(dummy)       SuspendAllInterrupts()
#define RKH_EXIT_CRITICAL(dummy)        ResumeAllInterrupts()

#define RKH_EQ_TYPE                     RKH_RQ_T
#define RKH_OSSIGNAL_TYPE               EventMaskType
#define RKH_THREAD_TYPE                 TaskType

/* -------------------------------- Constants ------------------------------ */
/**
 *	If the #RKH_CFGPORT_SMA_THREAD_EN is set to 1, each SMA (active object)
 *	has its own thread of execution.
 */

#define RKH_CFGPORT_SMA_THREAD_EN           RKH_ENABLED

/**
 *	If the #RKH_CFGPORT_SMA_THREAD_EN and #RKH_CFGPORT_SMA_THREAD_DATA_EN
 *	are set to 1, each SMA (active object) has its own thread of execution
 *	and its own object data.
 */

#define RKH_CFGPORT_SMA_THREAD_DATA_EN      RKH_ENABLED

/**
 *  If the #RKH_CFGPORT_NATIVE_SCHEDULER_EN is set to 1 then RKH will
 *  include the simple, cooperative, and nonpreemptive scheduler RKHS.
 *  When #RKH_CFGPORT_NATIVE_SCHEDULER_EN is enabled RKH also will
 *  automatically define #RKH_EQ_TYPE, RKH_SMA_BLOCK(), RKH_SMA_READY(),
 *  RKH_SMA_UNREADY(), and assume the native priority scheme.
 */

#define RKH_CFGPORT_NATIVE_SCHEDULER_EN     RKH_DISABLED

/**
 *  If the #RKH_CFGPORT_NATIVE_EQUEUE_EN is set to 1 and the native event
 *  queue is enabled (see #RKH_CFG_RQ_EN) then RKH will include its own
 *  implementation of rkh_sma_post_fifo(), rkh_sma_post_lifo(), and
 *  rkh_sma_get() functions.
 */

#define RKH_CFGPORT_NATIVE_EQUEUE_EN        RKH_ENABLED

/**
 *  If the #RKH_CFGPORT_NATIVE_DYN_EVT_EN is set to 1 and the native
 *  fixed-size memory block facility is enabled (see #RKH_CFG_MP_EN) then
 *  RKH will include its own implementation of dynamic memory management.
 *  When #RKH_CFGPORT_NATIVE_DYN_EVT_EN is enabled RKH also will
 *  automatically define RKH_DYNE_TYPE, RKH_DYNE_INIT(),
 *  RKH_DYNE_GET_ESIZE(), RKH_DYNE_GET(), and RKH_DYNE_PUT().
 */

#define RKH_CFGPORT_NATIVE_DYN_EVT_EN       RKH_ENABLED

/**
 *	If the #RKH_CFGPORT_REENTRANT_EN is set to 1, the RKH event dispatch
 *	allows to be invoked from several threads of executions. Enable this
 *	only if the application is based on a multi-thread architecture.
 */

#define RKH_CFGPORT_REENTRANT_EN            RKH_ENABLED

/**
 *  Specify the size of void pointer. The valid values [in bits] are
 *  16 or 32. Default is 32. See RKH_TRC_SYM() macro.
 */

#define RKH_CFGPORT_TRC_SIZEOF_PTR          32u

/**
 *  Specify the size of function pointer. The valid values [in bits] are
 *  16 or 32. Default is 32. See RKH_TUSR_FUN() and RKH_TRC_FUN() macros.
 */

#define RKH_CFGPORT_TRC_SIZEOF_FUN_PTR      32u

/**
 *  Specify the number of bytes (size) used by the trace record timestamp.
 *  The valid values [in bits] are 8, 16 or 32. Default is 16.
 */

#define RKH_CFGPORT_TRC_SIZEOF_TSTAMP       32u

/**
 *  If the #RKH_CFGPORT_SMA_QSTO_EN is set to 1 then RKH_SMA_ACTIVATE()
 *  macro invokes the rkh_sma_activate() function ignoring the external
 *  event queue storage argument, \c qs.
 */

#define RKH_CFGPORT_SMA_QSTO_EN             RKH_ENABLED

/**
 *  If the #RKH_CFGPORT_SMA_STK_EN is set to 0 then RKH_SMA_ACTIVATE()
 *  macro invokes the rkh_sma_activate() function ignoring the thread's
 *  stack related arguments, \c stks and \c stksize.
 */

#define RKH_CFGPORT_SMA_STK_EN              RKH_DISABLED

/*
 *  Declaring an object RKHROM announces that its value will
 *  not be changed and it will be stored in ROM.
 */

#define RKHROM                              const

/* ------------------------------- Data types ------------------------------ */
typedef struct
{
    struct SMA **sma;
    TaskType tsk;
} SMA_TASK_TBL_T;

/* -------------------------- External variables --------------------------- */
extern const SMA_TASK_TBL_T rkh_sma_task_tbl[];

/* -------------------------- Function prototypes -------------------------- */
const char *rkh_get_port_version(void);
const char *rkh_get_port_desc(void);
void rkh_task_function(struct SMA **sma);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
