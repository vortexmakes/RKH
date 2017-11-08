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
 *  \file       rkhtmr_base.h
 *  \brief      Specifies the software timer base.
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
 *  2017.07.11  LeFr  v3.0.01  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHTMR_BASE_H__
#define __RKHTMR_BASE_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhitl.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
typedef struct RKHTmrBase RKHTmrBase;

/**
 *  \brief
 *  Defines the data structure used to maintain information that allows the
 *  timer-handling facility to send an event to active object when a timer 
 *  expires.
 *
 *  \ingroup apiTmr
 */
struct RKHTmrBase
{
    /**
     *  Timer event.
     */
    RKH_EVT_T evt;

    /**
     *  \brief
     *  Active object that receives the timer event.
     */
    RKH_SMA_T *ao;
};

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
