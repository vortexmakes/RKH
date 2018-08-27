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
 *  \file       rkhfwk_sched.h
 *  \brief      Specifies the interface of RKH control operations.
 *  \ingroup    fwk
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.17.05 LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHFWK_SCHED_H__
#define __RKHFWK_SCHED_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtype.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
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

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
