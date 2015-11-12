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
 *  \file       rkhitl.h
 *  \ingroup    fwk
 *
 *  \brief      RKH engine interface.This header file is directly included in 
 *              RKH interface file, rkh.h.
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

#ifndef __RKHITL_H__
#define __RKHITL_H__

/* ----------------------------- Include files ----------------------------- */

/**
 *  Defines standard constants and macros.
 */

#include "rkhdef.h"

/**
 *  Application specific configuration options.
 */

#include "rkhcfg.h"

/**
 *  Specific definitions to the platform being used.
 */

#include "rkhplat.h"
#include "rkhtype.h"

/**
 *  Trace facility.
 */

#include "rkhtrc.h"

/**
 *  Event data type and related macros.
 */

#include "rkhevt.h"

/* ---------------------- External C language linkage ---------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */

/**
 *  \brief
 *	This macro expands to the binary representation of the RKH version.
 *
 *	The version number is composed as 0xABCC, where:
 *	the number A (1-digit) denoted the major revision, the number B (1-digit)
 *	denoted the minor revision, and the number C (2-digit) indicated the
 *	release number. For example, the code for 2.2.04 is 0x2204.
 *
 *  Release date: 08/11/2014
 */
#define RKH_VERSION_CODE            0x2404u

/**
 *  \brief
 *  This macro retrieves a pointer to string describing the RKH version.
 *  For example, "2.2.04".
 */
#define RKH_RELEASE                 rkh_version

/**
 *  \brief
 *  This is the macro used to build an integer version code from the
 *  individual numbers that build up a version number.
 *
 *  For example, RKH_VERSION(2,2,04) expands to 0x2204. This macro is very
 *  useful when needs to compare the current version (#RKH_VERSION_CODE) and
 *  a known checkpoint version at compile-time.
 *
 *  \param[in] a    major revision
 *  \param[in] b    minor revision
 *  \param[in] c    release number
 *
 *  \usage
 *  \code
 *  #if RKH_VERSION_CODE <= RKH_VERSION(1, 2, 03)
 *  ...
 *  #else
 *  ...
 *  #endif
 *  \endcode
 */
#define RKH_VERSION(a, b, c) \
    (((((a) <<   12) & 0xF000) | \
      (((b) <<    8) & 0x0F00) | \
      (((c) &  0xFF) & 0x00FF)) & 0xFFFF)

/**
 *  \brief
 *	This macro is used to indicate the end of a transition table.
 */
#define RKH_ANY                     ((RKH_SIG_T)(-1))

/**
 *  \brief
 *  RKH allows up to RKH_CFG_FWK_MAX_SMA different priority levels
 *  (see rkhcfg.h).
 *
 *  In RKH, a low-priority number corresponds to a high-priority level.
 *  Priority level zero (0) is thus the highest priority level. Priority
 *	RKH_LOWEST_PRIO (RKH_CFG_FWK_MAX_SMA - 1) is the lowest priority level.
 */
#define RKH_LOWEST_PRIO             (RKH_CFG_FWK_MAX_SMA - 1)

/*
 *  Verifies port file from rkhport.h included in rkhplat.h.
 */

#ifndef RKHROM
#error "rkhport.h, Missing RKHROM: Qualifier for ROM data storage. \
    See Porting chapter in readme file for more information"
#endif

#define FOREVER                     for (;; )

/*
 *  Macros for casting
 */
#define CB(p)           ((RKH_BASE_T *)(p))
#define CST(p)          ((RKH_ST_T *)(p))
#define CCMP(p)         ((RKH_SCMP_T *)(p))
#define CBSC(p)         ((RKH_SBSC_T *)(p))
#define CCD(p)          ((RKH_SCOND_T *)(p))
#define CCH(p)          ((RKH_SCHOICE_T *)(p))
#define CH(p)           ((RKH_SHIST_T *)(p))
#define CSBM(p)         ((RKH_SSBM_T *)(p))
#define CRSM(p)         ((RKH_RSM_T *)(p))
#define CM(p)           ((RKHROM RKH_SMA_T *)(p))
#define CT(p)           ((RKHROM RKH_TR_T *)(p))
#define CPT(p)          ((RKHROM struct RKH_SCMP_T *)(p))
#define CPP(p)          ((RKH_PPRO_T)(p))
#define CG(p)           ((RKH_GUARD_T)(p))
#define CA(p)           ((RKH_TRN_ACT_T)(p))
#define CENP(p)         ((RKH_SENP_T *)(p))
#define CEXP(p)         ((RKH_SEXP_T *)(p))
#define CENPCN(p)       ((RKH_ENPCN_T *)(p))
#define CEXPCN(p)       ((RKH_EXPCN_T *)(p))
#define CE(p)           ((RKH_EVT_T *)(p))
#define CCE(p)          ((const RKH_EVT_T *)(p))
#define CV(p)           ((void *)(p))
#define CSMA(p)         ((const struct RKH_SMA_T *)(p))
#define CQ(p)           ((RKH_RQ_T *)(p))
#define CIA(s)          ((RKH_INIT_ACT_T)((s)->romrkh->iaction))
#define CTA(ta)         ((RKH_TRN_ACT_T)(ta))



/* ------------------------- Configuration errors -------------------------- */

/*
 *  LOOK FOR MISSING #define CONSTANTS
 *
 *  This section is used to generate ERROR messages at compile time if
 *  certain #define constants are MISSING in rkhcfg.h.  This allows you to
 *  quickly determine the source of the error.
 *
 *  You SHOULD NOT change this section UNLESS you would like to add more
 *  comments as to the source of the compile time error.
 */

/*  MEMORY POOL   --------------------------------------------------------- */

#ifndef RKH_CFG_MP_EN
    #error "RKH_CFG_MP_EN                         not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_MP_EN != RKH_ENABLED) && \
    (RKH_CFG_MP_EN != RKH_DISABLED))
    #error "RKH_CFG_MP_EN                   illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#elif   (RKH_CFG_MP_EN == RKH_ENABLED)

    #ifndef RKH_CFG_MP_REDUCED_EN
    #error "RKH_CFG_MP_REDUCED_EN                 not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

    #elif   ((RKH_CFG_MP_REDUCED_EN != RKH_ENABLED) && \
    (RKH_CFG_MP_REDUCED_EN != RKH_DISABLED))
    #error "RKH_CFG_MP_REDUCED_EN           illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "
    #endif

    #ifndef RKH_CFG_MP_SIZEOF_BSIZE
    #error "RKH_CFG_MP_SIZEOF_BSIZE               not #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]      "
    #error  "                               [     || 16  (16-bit size)]      "
    #error  "                               [     || 32  (32-bit size)]      "

    #elif  ((RKH_CFG_MP_SIZEOF_BSIZE != 8) && \
    (RKH_CFG_MP_SIZEOF_BSIZE != 16) && \
    (RKH_CFG_MP_SIZEOF_BSIZE != 32))
    #error  "RKH_CFG_MP_SIZEOF_BSIZE        illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]      "
    #error  "                               [     || 16  (16-bit size)]      "
    #error  "                               [     || 32  (32-bit size)]      "
    #endif

    #ifndef RKH_CFG_MP_SIZEOF_NBLOCK
    #error "RKH_CFG_MP_SIZEOF_NBLOCK              not #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]      "
    #error  "                               [     || 16  (16-bit size)]      "
    #error  "                               [     || 32  (32-bit size)]      "

    #elif  ((RKH_CFG_MP_SIZEOF_NBLOCK != 8) && \
    (RKH_CFG_MP_SIZEOF_NBLOCK != 16) && \
    (RKH_CFG_MP_SIZEOF_NBLOCK != 32))
    #error  "RKH_CFG_MP_SIZEOF_NBLOCK       illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]      "
    #error  "                               [     || 16  (16-bit size)]      "
    #error  "                               [     || 32  (32-bit size)]      "
    #endif

    #ifndef RKH_CFG_MP_GET_BSIZE_EN
    #error "RKH_CFG_MP_GET_BSIZE_EN               not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

    #elif   ((RKH_CFG_MP_GET_BSIZE_EN != RKH_ENABLED) && \
    (RKH_CFG_MP_GET_BSIZE_EN != RKH_DISABLED))
    #error "RKH_CFG_MP_GET_BSIZE_EN         illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "
    #endif

    #ifndef RKH_CFG_MP_GET_NFREE_EN
    #error "RKH_CFG_MP_GET_NFREE_EN               not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

    #elif   ((RKH_CFG_MP_GET_NFREE_EN != RKH_ENABLED) && \
    (RKH_CFG_MP_GET_NFREE_EN != RKH_DISABLED))
    #error "RKH_CFG_MP_GET_NFREE_EN         illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "
    #endif

    #ifndef RKH_CFG_MP_GET_LWM_EN
    #error "RKH_CFG_MP_GET_LWM_EN                 not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

    #elif   ((RKH_CFG_MP_GET_LWM_EN != RKH_ENABLED) && \
    (RKH_CFG_MP_GET_LWM_EN != RKH_DISABLED))
    #error "RKH_CFG_MP_GET_LWM_EN           illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "
    #endif

    #ifndef RKH_CFG_MP_GET_INFO_EN
    #error "RKH_CFG_MP_GET_INFO_EN                not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

    #elif   ((RKH_CFG_MP_GET_INFO_EN != RKH_ENABLED) && \
    (RKH_CFG_MP_GET_INFO_EN != RKH_DISABLED))
    #error "RKH_CFG_MP_GET_INFO_EN          illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "
    #endif

#endif

/*  QUEUE         --------------------------------------------------------- */

#ifndef RKH_CFG_RQ_EN
    #error "RKH_CFG_RQ_EN                         not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_RQ_EN != RKH_ENABLED) && \
    (RKH_CFG_RQ_EN != RKH_DISABLED))
    #error "RKH_CFG_RQ_EN                   illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_RQ_SIZEOF_NELEM
    #error "RKH_CFG_RQ_SIZEOF_NELEM               not #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]      "
    #error  "                               [     || 16  (16-bit size)]      "
    #error  "                               [     || 32  (32-bit size)]      "

#elif  ((RKH_CFG_RQ_SIZEOF_NELEM != 8) && \
    (RKH_CFG_RQ_SIZEOF_NELEM != 16) && \
    (RKH_CFG_RQ_SIZEOF_NELEM != 32))
    #error  "RKH_CFG_RQ_SIZEOF_NELEM        illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]      "
    #error  "                               [     || 16  (16-bit size)]      "
    #error  "                               [     || 32  (32-bit size)]      "

#endif

#ifndef RKH_CFG_RQ_GET_LWMARK_EN
    #error "RKH_CFG_RQ_GET_LWMARK_EN              not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_RQ_GET_LWMARK_EN != RKH_ENABLED) && \
    (RKH_CFG_RQ_GET_LWMARK_EN != RKH_DISABLED))
    #error "RKH_CFG_RQ_GET_LWMARK_EN        illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_RQ_READ_EN
    #error "RKH_CFG_RQ_READ_EN                    not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_RQ_READ_EN != RKH_ENABLED) && \
    (RKH_CFG_RQ_READ_EN != RKH_DISABLED))
    #error "RKH_CFG_RQ_READ_EN              illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_RQ_DEPLETE_EN
    #error "RKH_CFG_RQ_DEPLETE_EN                 not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_RQ_DEPLETE_EN != RKH_ENABLED) && \
    (RKH_CFG_RQ_DEPLETE_EN != RKH_DISABLED))
    #error "RKH_CFG_RQ_DEPLETE_EN           illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_RQ_IS_FULL_EN
    #error "RKH_CFG_RQ_IS_FULL_EN                 not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_RQ_IS_FULL_EN != RKH_ENABLED) && \
    (RKH_CFG_RQ_IS_FULL_EN != RKH_DISABLED))
    #error "RKH_CFG_RQ_IS_FULL_EN           illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_RQ_GET_NELEMS_EN
    #error "RKH_CFG_RQ_GET_NELEMS_EN              not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_RQ_GET_NELEMS_EN != RKH_ENABLED) && \
    (RKH_CFG_RQ_GET_NELEMS_EN != RKH_DISABLED))
    #error "RKH_CFG_RQ_GET_NELEMS_EN        illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_RQ_PUT_LIFO_EN
    #error "RKH_CFG_RQ_PUT_LIFO_EN                not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_RQ_PUT_LIFO_EN != RKH_ENABLED) && \
    (RKH_CFG_RQ_PUT_LIFO_EN != RKH_DISABLED))
    #error "RKH_CFG_RQ_PUT_LIFO_EN          illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_RQ_GET_INFO_EN
    #error "RKH_CFG_RQ_GET_INFO_EN                not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_RQ_GET_INFO_EN != RKH_ENABLED) && \
    (RKH_CFG_RQ_GET_INFO_EN != RKH_DISABLED))
    #error "RKH_CFG_RQ_GET_INFO_EN          illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

/*  TIMER         --------------------------------------------------------- */

#ifndef RKH_CFG_TMR_EN
    #error "RKH_CFG_TMR_EN                        not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_TMR_EN != RKH_ENABLED) && \
    (RKH_CFG_TMR_EN != RKH_DISABLED))
    #error "RKH_CFG_TMR_EN                  illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#elif   (RKH_CFG_TMR_EN == RKH_ENABLED)
    #ifndef RKH_CFG_FWK_TICK_RATE_HZ
    #error "RKH_CFG_FWK_TICK_RATE_HZ              not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "
    #elif (RKH_CFG_FWK_TICK_RATE_HZ <= 0u)
    #error "RKH_CFG_FWK_TICK_RATE_HZ        illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be > 0]                    "
    #endif

    #ifndef RKH_CFG_TMR_SIZEOF_NTIMER
    #error "RKH_CFG_TMR_SIZEOF_NTIMER             not #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]      "
    #error  "                               [     || 16  (16-bit size)]      "
    #error  "                               [     || 32  (32-bit size)]      "

    #elif  ((RKH_CFG_TMR_SIZEOF_NTIMER != 8) && \
    (RKH_CFG_TMR_SIZEOF_NTIMER != 16) && \
    (RKH_CFG_TMR_SIZEOF_NTIMER != 32))
    #error  "RKH_CFG_TMR_SIZEOF_NTIMER      illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]      "
    #error  "                               [     || 16  (16-bit size)]      "
    #error  "                               [     || 32  (32-bit size)]      "
    #endif

    #ifndef RKH_CFG_TMR_HOOK_EN
    #error "RKH_CFG_TMR_HOOK_EN                   not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

    #elif   ((RKH_CFG_TMR_HOOK_EN != RKH_ENABLED) && \
    (RKH_CFG_TMR_HOOK_EN != RKH_DISABLED))
    #error "RKH_CFG_TMR_HOOK_EN             illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "
    #endif

    #ifndef RKH_CFG_TMR_GET_INFO_EN
    #error "RKH_CFG_TMR_GET_INFO_EN               not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

    #elif   ((RKH_CFG_TMR_GET_INFO_EN != RKH_ENABLED) && \
    (RKH_CFG_TMR_GET_INFO_EN != RKH_DISABLED))
    #error "RKH_CFG_TMR_GET_INFO_EN         illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "
    #endif

#endif

/*  STATE MACHINE APPLICATIONS  -------------------------------------------- */

#ifndef RKH_CFG_SMA_GET_INFO_EN
    #error "RKH_CFG_SMA_GET_INFO_EN               not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_GET_INFO_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_GET_INFO_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_GET_INFO_EN         illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_PPRO_EN
    #error "RKH_CFG_SMA_PPRO_EN                   not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_PPRO_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_PPRO_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_PPRO_EN             illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_HCAL_EN
    #error "RKH_CFG_SMA_HCAL_EN                   not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_HCAL_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_HCAL_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_HCAL_EN             illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_MAX_HCAL_DEPTH
    #error "RKH_CFG_SMA_MAX_HCAL_DEPTH            not #define'd in 'rkhcfg.h'"
    #error "                                [MUST be >  0]                   "
    #error "                                [     && <= 8]                   "

#elif   ((RKH_CFG_SMA_MAX_HCAL_DEPTH == 0) || \
    (RKH_CFG_SMA_MAX_HCAL_DEPTH > 8))
    #error "RKH_CFG_SMA_MAX_HCAL_DEPTH      illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be >= 0]                   "
    #error  "                               [     && <= 8]                   "

#endif

#ifndef RKH_CFG_SMA_MAX_TRC_SEGS
    #error "RKH_CFG_SMA_MAX_TRC_SEGS              not #define'd in 'rkhcfg.h'"
    #error "                                [MUST be >  0]                   "
    #error "                                [     && <= 8]                   "

#elif   ((RKH_CFG_SMA_MAX_TRC_SEGS == 0) || \
    (RKH_CFG_SMA_MAX_TRC_SEGS > 8))
    #error "RKH_CFG_SMA_MAX_TRC_SEGS        illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be >= 0]                   "
    #error  "                               [     && <= 8]                   "

#endif

#ifndef RKH_CFG_SMA_PSEUDOSTATE_EN
    #error "RKH_CFG_SMA_PSEUDOSTATE_EN            not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_PSEUDOSTATE_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_PSEUDOSTATE_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_PSEUDOSTATE_EN      illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_DEEP_HIST_EN
    #error "RKH_CFG_SMA_DEEP_HIST_EN              not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_DEEP_HIST_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_DEEP_HIST_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_DEEP_HIST_EN        illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_SHALLOW_HIST_EN
    #error "RKH_CFG_SMA_SHALLOW_HIST_EN           not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_SHALLOW_HIST_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_SHALLOW_HIST_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_SHALLOW_HIST_EN     illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_CHOICE_EN
    #error "RKH_CFG_SMA_CHOICE_EN                 not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_CHOICE_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_CHOICE_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_CHOICE_EN           illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]     "

#endif

#ifndef RKH_CFG_SMA_CONDITIONAL_EN
    #error "RKH_CFG_SMA_CONDITIONAL_EN            not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_CONDITIONAL_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_CONDITIONAL_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_CONDITIONAL_EN      illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_SUBMACHINE_EN
    #error "RKH_CFG_SMA_SUBMACHINE_EN             not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_SUBMACHINE_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_SUBMACHINE_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_SUBMACHINE_EN       illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_TRC_SNDR_EN
    #error "RKH_CFG_SMA_TRC_SNDR_EN               not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_TRC_SNDR_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_TRC_SNDR_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_TRC_SNDR_EN         illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_INIT_ARG_SMA_EN
    #error "RKH_CFG_SMA_INIT_ARG_SMA_EN           not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_INIT_ARG_SMA_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_INIT_ARG_SMA_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_INIT_ARG_SMA_EN     illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_ENT_ARG_SMA_EN
    #error "RKH_CFG_SMA_ENT_ARG_SMA_EN            not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_ENT_ARG_SMA_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_ENT_ARG_SMA_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_ENT_ARG_SMA_EN      illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_ENT_ARG_STATE_EN
    #error "RKH_CFG_SMA_ENT_ARG_STATE_EN          not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_ENT_ARG_STATE_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_ENT_ARG_STATE_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_ENT_ARG_STATE_EN    illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_EXT_ARG_SMA_EN
    #error "RKH_CFG_SMA_EXT_ARG_SMA_EN            not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_EXT_ARG_SMA_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_EXT_ARG_SMA_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_EXT_ARG_SMA_EN      illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_EXT_ARG_STATE_EN
    #error "RKH_CFG_SMA_EXT_ARG_STATE_EN          not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_EXT_ARG_STATE_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_EXT_ARG_STATE_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_EXT_ARG_STATE_EN    illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_ACT_ARG_SMA_EN
    #error "RKH_CFG_SMA_ACT_ARG_SMA_EN            not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_ACT_ARG_SMA_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_ACT_ARG_SMA_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_ACT_ARG_SMA_EN      illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_ACT_ARG_EVT_EN
    #error "RKH_CFG_SMA_ACT_ARG_EVT_EN            not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_ACT_ARG_EVT_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_ACT_ARG_EVT_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_ACT_ARG_EVT_EN      illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_GRD_ARG_EVT_EN
    #error "RKH_CFG_SMA_GRD_ARG_EVT_EN            not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_GRD_ARG_EVT_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_GRD_ARG_EVT_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_GRD_ARG_EVT_EN      illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_GRD_ARG_SMA_EN
    #error "RKH_CFG_SMA_GRD_ARG_SMA_EN            not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_GRD_ARG_SMA_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_GRD_ARG_SMA_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_GRD_ARG_SMA_EN      illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

#ifndef RKH_CFG_SMA_PPRO_ARG_SMA_EN
    #error "RKH_CFG_SMA_PPRO_ARG_SMA_EN           not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_SMA_PPRO_ARG_SMA_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_PPRO_ARG_SMA_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_PPRO_ARG_SMA_EN     illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#endif

/*  TRACE         --------------------------------------------------------- */

#ifndef RKH_CFG_TRC_EN
    #error "RKH_CFG_TRC_EN                        not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

#elif   ((RKH_CFG_TRC_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_EN                  illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "

#elif   (RKH_CFG_TRC_EN == RKH_ENABLED)

    #ifndef RKH_CFG_TRC_RTFIL_EN
    #error "RKH_CFG_TRC_RTFIL_EN                  not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

    #elif   ((RKH_CFG_TRC_RTFIL_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_RTFIL_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_RTFIL_EN            illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "
    #endif

    #ifndef RKH_CFG_TRC_RTFIL_SMA_EN
    #error "RKH_CFG_TRC_RTFIL_SMA_EN              not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

    #elif   ((RKH_CFG_TRC_RTFIL_SMA_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_RTFIL_SMA_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_RTFIL_SMA_EN        illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "
    #endif

    #ifndef RKH_CFG_TRC_RTFIL_SIGNAL_EN
    #error "RKH_CFG_TRC_RTFIL_SIGNAL_EN           not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]       "
    #error "                                    [     || RKH_DISABLED]       "

    #elif   ((RKH_CFG_TRC_RTFIL_SIGNAL_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_RTFIL_SIGNAL_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_RTFIL_SIGNAL_EN     illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]      "
    #error "                                    [     ||  RKH_DISABLED]      "
    #endif

    #ifndef RKH_CFG_TRC_USER_TRACE_EN
    #error "RKH_CFG_TRC_USER_TRACE_EN             not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_USER_TRACE_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_USER_TRACE_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_USER_TRACE_EN       illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_ALL_EN
    #error "RKH_CFG_TRC_ALL_EN                    not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_ALL_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_ALL_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_ALL_EN              illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_MP_EN
    #error "RKH_CFG_TRC_MP_EN                     not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_MP_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_MP_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_MP_EN               illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_RQ_EN
    #error "RKH_CFG_TRC_RQ_EN                     not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_RQ_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_RQ_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_RQ_EN               illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SMA_EN
    #error "RKH_CFG_TRC_SMA_EN                    not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SMA_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SMA_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SMA_EN              illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_TMR_EN
    #error "RKH_CFG_TRC_TMR_EN                    not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_TMR_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_TMR_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_TMR_EN              illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SM_EN
    #error "RKH_CFG_TRC_SM_EN                     not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SM_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SM_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SM_EN               illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_FWK_EN
    #error "RKH_CFG_TRC_FWK_EN                    not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_FWK_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_FWK_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_FWK_EN              illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_ASSERT_EN
    #error "RKH_CFG_TRC_ASSERT_EN                 not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_ASSERT_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_ASSERT_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_ASSERT_EN           illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SM_INIT_EN
    #error "RKH_CFG_TRC_SM_INIT_EN                not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SM_INIT_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SM_INIT_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SM_INIT_EN          illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SMA_DCH_EN
    #error "RKH_CFG_TRC_SMA_DCH_EN                not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SMA_DCH_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SMA_DCH_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SMA_DCH_EN          illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SM_CLRH_EN
    #error "RKH_CFG_TRC_SM_CLRH_EN                not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SM_CLRH_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SM_CLRH_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SM_CLRH_EN          illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SM_TRN_EN
    #error "RKH_CFG_TRC_SM_TRN_EN                 not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SM_TRN_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SM_TRN_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SM_TRN_EN           illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SM_STATE_EN
    #error "RKH_CFG_TRC_SM_STATE_EN               not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SM_STATE_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SM_STATE_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SM_STATE_EN         illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SM_ENSTATE_EN
    #error "RKH_CFG_TRC_SM_ENSTATE_EN             not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SM_ENSTATE_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SM_ENSTATE_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SM_ENSTATE_EN       illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SM_EXSTATE_EN
    #error "RKH_CFG_TRC_SM_EXSTATE_EN             not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SM_EXSTATE_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SM_EXSTATE_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SM_EXSTATE_EN       illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SM_NENEX_EN
    #error "RKH_CFG_TRC_SM_NENEX_EN               not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SM_NENEX_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SM_NENEX_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SM_NENEX_EN         illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SM_NTRNACT_EN
    #error "RKH_CFG_TRC_SM_NTRNACT_EN             not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SM_NTRNACT_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SM_NTRNACT_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SM_NTRNACT_EN       illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SM_TS_STATE_EN
    #error "RKH_CFG_TRC_SM_TS_STATE_EN            not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SM_TS_STATE_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SM_TS_STATE_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SM_TS_STATE_EN      illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SM_PROCESS_EN
    #error "RKH_CFG_TRC_SM_PROCESS_EN             not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SM_PROCESS_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SM_PROCESS_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SM_PROCESS_EN       illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SM_EXE_ACT_EN
    #error "RKH_CFG_TRC_SM_EXE_ACT_EN              not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_SM_EXE_ACT_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_SM_EXE_ACT_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_SM_EXE_ACT_EN        illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_NSEQ_EN
    #error "RKH_CFG_TRC_NSEQ_EN                   not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_NSEQ_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_NSEQ_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_NSEQ_EN             illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_CHK_EN
    #error "RKH_CFG_TRC_CHK_EN                    not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_CHK_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_CHK_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_CHK_EN              illegally #define'd in 'rkhcfg.h'"
    #error "                                     MUST be  RKH_ENABLED ]       "
    #error "                                          ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_TSTAMP_EN
    #error "RKH_CFG_TRC_TSTAMP_EN                 not #define'd in 'rkhcfg.h'"
    #error "                                     MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFG_TRC_TSTAMP_EN != RKH_ENABLED) && \
    (RKH_CFG_TRC_TSTAMP_EN != RKH_DISABLED))
    #error "RKH_CFG_TRC_TSTAMP_EN           illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFGPORT_TRC_SIZEOF_TSTAMP
    #error "RKH_CFGPORT_TRC_SIZEOF_TSTAMP         not #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]       "
    #error  "                               [     || 16  (16-bit size)]       "
    #error  "                               [     || 32  (32-bit size)]       "

    #elif  ((RKH_CFGPORT_TRC_SIZEOF_TSTAMP != 8) && \
    (RKH_CFGPORT_TRC_SIZEOF_TSTAMP != 16) && \
    (RKH_CFGPORT_TRC_SIZEOF_TSTAMP != 32))
    #error  "RKH_CFGPORT_TRC_SIZEOF_TSTAMP  illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]       "
    #error  "                               [     || 16  (16-bit size)]       "
    #error  "                               [     || 32  (32-bit size)]       "
    #endif

    #ifndef RKH_CFGPORT_SMA_QSTO_EN
    #error "RKH_CFGPORT_SMA_QSTO_EN                not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFGPORT_SMA_QSTO_EN != RKH_ENABLED) && \
    (RKH_CFGPORT_SMA_QSTO_EN != RKH_DISABLED))
    #error "RKH_CFGPORT_SMA_QSTO_EN          illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFGPORT_SMA_STK_EN
    #error "RKH_CFGPORT_SMA_STK_EN                 not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

    #elif   ((RKH_CFGPORT_SMA_STK_EN != RKH_ENABLED) && \
    (RKH_CFGPORT_SMA_STK_EN != RKH_DISABLED))
    #error "RKH_CFGPORT_SMA_STK_EN           illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "
    #endif

    #ifndef RKH_CFG_TRC_SIZEOF_STREAM
    #error "RKH_CFG_TRC_SIZEOF_STREAM             not #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be >     0]                 "
    #error  "                               [     && <= 2048]                 "

    #elif   ((RKH_CFG_TRC_SIZEOF_STREAM == 0) || \
    (RKH_CFG_TRC_SIZEOF_STREAM > 2048))
    #error "RKH_CFG_TRC_SIZEOF_STREAM       illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be >    0]                  "
    #error  "                               [     && <= 2048]                 "
    #endif

#endif

/*  FRAMEWORK     --------------------------------------------------------- */

#ifndef RKH_CFG_FWK_MAX_SMA
    #error "RKH_CFG_FWK_MAX_SMA                   not #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be >=  1]                   "
    #error  "                               [     && <= 64]                   "

#elif ((RKH_CFG_FWK_MAX_SMA == 0) || (RKH_CFG_FWK_MAX_SMA > 64))
    #error "RKH_CFG_FWK_MAX_SMA             illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be >=  1]                   "
    #error  "                               [     && <= 64]                   "

#endif

#ifndef RKH_CFG_FWK_DYN_EVT_EN
    #error "RKH_CFG_FWK_DYN_EVT_EN                not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   (RKH_CFG_FWK_DYN_EVT_EN == RKH_DISABLED)

    /*
     *	If the dynamic event support is disabled, RKH not allows to use
     *	events with parameters, defer/recall mechanism, allocating and
     *	recycling dynamic events, among other features.
     */
    #undef RKH_CFGPORT_NATIVE_DYN_EVT_EN
    #define RKH_CFGPORT_NATIVE_DYN_EVT_EN           RKH_DISABLED

#endif

#ifndef RKH_CFG_FWK_MAX_EVT_POOL
    #error "RKH_CFG_FWK_MAX_EVT_POOL              not #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be >    0]                  "
    #error  "                               [     && <  256]                  "

#elif   (RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED)
    #if ((RKH_CFG_FWK_MAX_EVT_POOL == 0) || (RKH_CFG_MAX_EPOOL > 255))
    #error "RKH_CFG_FWK_MAX_EVT_POOL        illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be >    0]                  "
    #error  "                               [     && <  256]                  "
    #endif

#endif

#ifndef RKH_CFG_FWK_SIZEOF_EVT
    #error "RKH_CFG_FWK_SIZEOF_EVT                not #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]       "
    #error  "                               [     || 16  (16-bit size)]       "
    #error  "                               [     || 32  (32-bit size)]       "

#elif  ((RKH_CFG_FWK_SIZEOF_EVT != 8) && \
    (RKH_CFG_FWK_SIZEOF_EVT != 16) && \
    (RKH_CFG_FWK_SIZEOF_EVT != 32))
    #error  "RKH_CFG_FWK_SIZEOF_EVT         illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]       "
    #error  "                               [     || 16  (16-bit size)]       "
    #error  "                               [     || 32  (32-bit size)]       "

#endif

#ifndef RKH_CFG_FWK_MAX_SIGNALS
    #error "RKH_CFG_FWK_MAX_SIGNALS               not #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be >  0]                    "
    #error  "                        [MUST be <  2^RKH_CFG_FWK_SIZEOF_EVT    "

#elif ((RKH_CFG_FWK_MAX_SIGNALS == 0u) || \
    (RKH_CFG_FWK_MAX_SIGNALS >= RKH_BIT(RKH_CFG_FWK_SIZEOF_EVT)))
    #error "RKH_CFG_FWK_MAX_SIGNALS         illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be >  0]                    "
    #error  "                        [MUST be <  2^RKH_CFG_FWK_SIZEOF_EVT    "

#endif

#ifndef RKH_CFG_FWK_SIZEOF_EVT_SIZE
    #error "RKH_CFG_FWK_SIZEOF_EVT_SIZE           not #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]       "
    #error  "                               [     || 16  (16-bit size)]       "
    #error  "                               [     || 32  (32-bit size)]       "

#elif  ((RKH_CFG_FWK_SIZEOF_EVT_SIZE != 8) && \
    (RKH_CFG_FWK_SIZEOF_EVT_SIZE != 16) && \
    (RKH_CFG_FWK_SIZEOF_EVT_SIZE != 32))
    #error  "RKH_CFG_FWK_SIZEOF_EVT_SIZE    illegally #define'd in 'rkhcfg.h'"
    #error  "                               [MUST be  8  ( 8-bit size)]       "
    #error  "                               [     || 16  (16-bit size)]       "
    #error  "                               [     || 32  (32-bit size)]       "

#endif

#ifndef RKH_CFG_FWK_DEFER_EVT_EN
    #error "RKH_CFG_FWK_DEFER_EVT_EN              not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFG_FWK_DEFER_EVT_EN == RKH_ENABLED) && \
    (RKH_CFG_RQ_EN == RKH_DISABLED))
    #error "RKH_CFG_RQ_EN                    illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "

#endif

#ifndef RKH_CFG_FWK_ASSERT_EN
    #error "RKH_CFG_FWK_ASSERT_EN                not #define'd in 'rkhport.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFG_FWK_ASSERT_EN != RKH_ENABLED) && \
    (RKH_CFG_FWK_ASSERT_EN != RKH_DISABLED))
    #error "RKH_CFG_FWK_ASSERT_EN          illegally #define'd in 'rkhport.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#endif

#ifndef RKH_CFG_HOOK_DISPATCH_EN
    #error "RKH_CFG_HOOK_DISPATCH_EN              not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFG_HOOK_DISPATCH_EN != RKH_ENABLED) && \
    (RKH_CFG_HOOK_DISPATCH_EN != RKH_DISABLED))
    #error "RKH_CFG_HOOK_DISPATCH_EN        illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#endif

#ifndef RKH_CFG_HOOK_SIGNAL_EN
    #error "RKH_CFG_HOOK_SIGNAL_EN                not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFG_HOOK_SIGNAL_EN != RKH_ENABLED) && \
    (RKH_CFG_HOOK_SIGNAL_EN != RKH_DISABLED))
    #error "RKH_CFG_HOOK_SIGNAL_EN          illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#endif

#ifndef RKH_CFG_HOOK_TIMEOUT_EN
    #error "RKH_CFG_HOOK_TIMEOUT_EN               not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFG_HOOK_TIMEOUT_EN != RKH_ENABLED) && \
    (RKH_CFG_HOOK_TIMEOUT_EN != RKH_DISABLED))
    #error "RKH_CFG_HOOK_TIMEOUT_EN         illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#endif

#ifndef RKH_CFG_HOOK_START_EN
    #error "RKH_CFG_HOOK_START_EN                 not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFG_HOOK_START_EN != RKH_ENABLED) && \
    (RKH_CFG_HOOK_START_EN != RKH_DISABLED))
    #error "RKH_CFG_HOOK_START_EN           illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#endif

#ifndef RKH_CFG_HOOK_EXIT_EN
    #error "RKH_CFG_HOOK_EXIT_EN                  not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFG_HOOK_EXIT_EN != RKH_ENABLED) && \
    (RKH_CFG_HOOK_EXIT_EN != RKH_DISABLED))
    #error "RKH_CFG_HOOK_EXIT_EN            illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#endif

#ifndef RKH_CFG_HOOK_TIMETICK_EN
    #error "RKH_CFG_HOOK_TIMETICK_EN              not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFG_HOOK_TIMETICK_EN != RKH_ENABLED) && \
    (RKH_CFG_HOOK_TIMETICK_EN != RKH_DISABLED))
    #error "RKH_CFG_HOOK_TIMETICK_EN        illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#endif

#ifndef RKH_CFG_SMA_INIT_EVT_EN
    #error "RKH_CFG_SMA_INIT_EVT_EN               not #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFG_SMA_INIT_EVT_EN != RKH_ENABLED) && \
    (RKH_CFG_SMA_INIT_EVT_EN != RKH_DISABLED))
    #error "RKH_CFG_SMA_INIT_EVT_EN         illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#endif

/*  PORT          --------------------------------------------------------- */

#ifndef RKH_CFGPORT_SMA_THREAD_EN
    #error "RKH_CFGPORT_SMA_THREAD_EN            not #define'd in 'rkhport.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFGPORT_SMA_THREAD_EN != RKH_ENABLED) && \
    (RKH_CFGPORT_SMA_THREAD_EN != RKH_DISABLED))
    #error "RKH_CFGPORT_SMA_THREAD_EN      illegally #define'd in 'rkhport.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#endif

#ifndef RKH_CFGPORT_SMA_THREAD_DATA_EN
    #error "RKH_CFGPORT_SMA_THREAD_DATA_EN       not #define'd in 'rkhport.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFGPORT_SMA_THREAD_DATA_EN != RKH_ENABLED) && \
    (RKH_CFGPORT_SMA_THREAD_DATA_EN != RKH_DISABLED))
    #error "RKH_CFGPORT_SMA_THREAD_DATA_EN illegally #define'd in 'rkhport.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#endif

#ifndef RKH_CFGPORT_NATIVE_SCHEDULER_EN
    #error "RKH_CFGPORT_NATIVE_SCHEDULER_EN      not #define'd in 'rkhport.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFGPORT_NATIVE_SCHEDULER_EN != RKH_ENABLED) && \
    (RKH_CFGPORT_NATIVE_SCHEDULER_EN != RKH_DISABLED))
    #error "RKH_CFGPORT_NATIVE_SCHEDULER_EN illegally #define'd in 'rkhport.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#endif

#ifndef RKH_CFGPORT_NATIVE_EQUEUE_EN
    #error "RKH_CFGPORT_NATIVE_EQUEUE_EN         not #define'd in 'rkhport.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFGPORT_NATIVE_EQUEUE_EN != RKH_ENABLED) && \
    (RKH_CFGPORT_NATIVE_EQUEUE_EN != RKH_DISABLED))
    #error "RKH_CFGPORT_NATIVE_EQUEUE_EN   illegally #define'd in 'rkhport.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#elif   ((RKH_CFGPORT_NATIVE_EQUEUE_EN == RKH_ENABLED) && \
    (RKH_CFG_RQ_EN != RKH_ENABLED))
    #error "RKH_CFG_RQ_EN                   illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#endif

#ifndef RKH_CFGPORT_NATIVE_DYN_EVT_EN
    #error "RKH_CFGPORT_NATIVE_DYN_EVT_EN        not #define'd in 'rkhport.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFGPORT_NATIVE_DYN_EVT_EN != RKH_ENABLED) && \
    (RKH_CFGPORT_NATIVE_DYN_EVT_EN != RKH_DISABLED))
    #error "RKH_CFGPORT_NATIVE_DYN_EVT_EN  illegally #define'd in 'rkhport.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#elif   (RKH_CFGPORT_NATIVE_DYN_EVT_EN == RKH_ENABLED)
    #if ((RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED) && \
    (RKH_CFG_MP_EN == RKH_DISABLED))
    #error "RKH_CFG_FWK_DYN_EVT_EN          illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "RKH_CFG_MP_EN                   illegally #define'd in 'rkhcfg.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #endif

#endif

#ifndef RKH_CFGPORT_REENTRANT_EN
    #error "RKH_CFGPORT_REENTRANT_EN             not #define'd in 'rkhport.h'"
    #error "                                    [MUST be RKH_ENABLED ]        "
    #error "                                    [     || RKH_DISABLED]        "

#elif   ((RKH_CFGPORT_REENTRANT_EN != RKH_ENABLED) && \
    (RKH_CFGPORT_REENTRANT_EN != RKH_DISABLED))
    #error "RKH_CFGPORT_REENTRANT_EN       illegally #define'd in 'rkhport.h'"
    #error "                                    [MUST be  RKH_ENABLED ]       "
    #error "                                    [     ||  RKH_DISABLED]       "

#endif

#ifndef RKH_CFGPORT_TRC_SIZEOF_PTR
    #error "RKH_CFGPORT_TRC_SIZEOF_PTR       not #define'd in 'rkhport.h'"
    #error  "                               [MUST be  8  ( 8-bit pointer)]    "
    #error  "                               [     || 16  (16-bit pointer)]    "
    #error  "                               [     || 32  (32-bit pointer)]    "

#elif  ((RKH_CFGPORT_TRC_SIZEOF_PTR != 8) && \
    (RKH_CFGPORT_TRC_SIZEOF_PTR != 16) && \
    (RKH_CFGPORT_TRC_SIZEOF_PTR != 32))
    #error  "RKH_CFGPORT_TRC_SIZEOF_PTR illegally #define'd in 'rkhport.h'"
    #error  "                               [MUST be  8  ( 8-bit pointer)]    "
    #error  "                               [     || 16  (16-bit pointer)]    "
    #error  "                               [     || 32  (32-bit pointer)]    "

#endif

#ifndef RKH_CFGPORT_TRC_SIZEOF_FUN_PTR
    #error "RKH_CFGPORT_TRC_SIZEOF_FUN_PTR       not #define'd in 'rkhport.h'"
    #error  "                               [MUST be  8  ( 8-bit pointer)]    "
    #error  "                               [     || 16  (16-bit pointer)]    "
    #error  "                               [     || 32  (32-bit pointer)]    "

#elif  ((RKH_CFGPORT_TRC_SIZEOF_FUN_PTR != 8) && \
    (RKH_CFGPORT_TRC_SIZEOF_FUN_PTR != 16) && \
    (RKH_CFGPORT_TRC_SIZEOF_FUN_PTR != 32))
    #error  "RKH_CFGPORT_TRC_SIZEOF_FUN_PTR illegally #define'd in 'rkhport.h'"
    #error  "                               [MUST be  8  ( 8-bit pointer)]    "
    #error  "                               [     || 16  (16-bit pointer)]    "
    #error  "                               [     || 32  (32-bit pointer)]    "

#endif

/**
 *  It can be used to convert ticks to milliseconds.
 *  This format is more convenient and natural than ticks.
 *  This configuration constant is not used by RKH, it is just
 *  a value to allow an application to deal with time when
 *  using timer services.
 *  You can use the global constant RKH_CFG_FWK_TICK_RATE_HZ (see
 *  rkhcfg.h) to convert time to ticks using the macros like
 *  RKH_TIME_MS(), RKH_TIME_SEC(), and RKH_TIME_MIN().
 */
#define RKH_TICK_RATE_MS    \
    ((RKH_TNT_T)(1000 / RKH_CFG_FWK_TICK_RATE_HZ))

/** @{
 *  \brief
 *  It can be used to convert ticks to time.
 *
 *  This format is more convenient and natural than ticks. You can use
 *  the global constant RKH_CFG_FWK_TICK_RATE_HZ (see rkhcfg.h) to convert
 *  time to ticks using the macros like RKH_TIME_MS(), RKH_TIME_SEC(),
 *  and RKH_TIME_MIN().
 */
#define RKH_TIME_MS(ms_)      ((ms_) / RKH_TICK_RATE_MS)
#define RKH_TIME_SEC(s_)      ((s_) * 1000u / RKH_TICK_RATE_MS)
#define RKH_TIME_MIN(m_)      ((m_) * 60 * 1000u / RKH_TICK_RATE_MS)
/*@}*/

/*
 *  The following macros and constants are INTERNAL to RKH and
 *  the user application should NOT call it.
 */

#define RKH_REGULAR                     0x80
#define RKH_PSEUDO                      0
#define RKH_TYPE(t,i)                   (t | i)

#define RKH_BASIC                       RKH_TYPE(RKH_REGULAR,  0)
#define RKH_COMPOSITE                   RKH_TYPE(RKH_REGULAR,  0x01)
#define RKH_SUBMACHINE                  RKH_TYPE(RKH_REGULAR,  0x02)
#define RKH_REF_SUBMACHINE              RKH_TYPE(RKH_REGULAR,  0x04)

#define RKH_CONDITIONAL                 RKH_TYPE(RKH_PSEUDO,   0x02)
#define RKH_CHOICE                      RKH_TYPE(RKH_PSEUDO,   0x04)
#define RKH_SHISTORY                    RKH_TYPE(RKH_PSEUDO,   0x08)
#define RKH_DHISTORY                    RKH_TYPE(RKH_PSEUDO,   0x10)
#define RKH_ENPOINT                     RKH_TYPE(RKH_PSEUDO,   0x20)
#define RKH_EXPOINT                     RKH_TYPE(RKH_PSEUDO,   0x40)

#if (RKH_CFG_SMA_PSEUDOSTATE_EN  == RKH_DISABLED || \
     (RKH_CFG_SMA_DEEP_HIST_EN    == RKH_DISABLED && \
      RKH_CFG_SMA_SHALLOW_HIST_EN == RKH_DISABLED && \
      RKH_CFG_SMA_SUBMACHINE_EN   == RKH_DISABLED && \
      RKH_CFG_SMA_CONDITIONAL_EN  == RKH_DISABLED && \
      RKH_CFG_SMA_CHOICE_EN       == RKH_DISABLED))
    #define RKH_PSEUDOSTATE     RKH_DISABLED
#else
    #define RKH_PSEUDOSTATE     RKH_ENABLED
#endif

#if (RKH_CFG_SMA_HCAL_EN         == RKH_ENABLED &&   \
     RKH_CFG_SMA_PSEUDOSTATE_EN  == RKH_ENABLED &&   \
     (RKH_CFG_SMA_SHALLOW_HIST_EN == RKH_ENABLED ||   \
      RKH_CFG_SMA_DEEP_HIST_EN    == RKH_ENABLED))
    #define RKH_HISTORY_ENABLED
#endif

#if (RKH_CFG_SMA_HCAL_EN         == RKH_ENABLED && \
     RKH_CFG_SMA_PSEUDOSTATE_EN  == RKH_ENABLED && \
     RKH_CFG_SMA_DEEP_HIST_EN    == RKH_ENABLED)
    #define RKH_DEEP_ENABLED
#endif

#if (RKH_CFG_SMA_HCAL_EN         == RKH_ENABLED && \
     RKH_CFG_SMA_PSEUDOSTATE_EN  == RKH_ENABLED && \
     RKH_CFG_SMA_SHALLOW_HIST_EN == RKH_ENABLED)
    #define RKH_SHALLOW_ENABLED
#endif

#if (RKH_CFG_SMA_PSEUDOSTATE_EN  == RKH_ENABLED && \
     RKH_CFG_SMA_SUBMACHINE_EN   == RKH_ENABLED)
    #define RKH_SUBMACHINE_ENABLED
#endif

#if (RKH_CFG_SMA_PSEUDOSTATE_EN  == RKH_ENABLED && \
     RKH_CFG_SMA_CHOICE_EN       == RKH_ENABLED)
    #define RKH_CHOICE_ENABLED
#endif

#if (RKH_CFG_SMA_PSEUDOSTATE_EN  == RKH_ENABLED && \
     (RKH_CFG_SMA_CONDITIONAL_EN  == RKH_ENABLED || \
      RKH_CFG_SMA_CHOICE_EN       == RKH_ENABLED))
    #define RKH_CHOICE_OR_CONDITIONAL_ENABLED
#endif

#if RKH_CFG_HOOK_DISPATCH_EN == RKH_ENABLED
    #define RKH_HOOK_DISPATCH(sma, e) \
    rkh_hook_dispatch((sma), (RKH_EVT_T *)(e))

#else
    #define RKH_HOOK_DISPATCH(sma, e)     (void)0
#endif

#if (RKH_CFG_HOOK_TIMEOUT_EN == RKH_ENABLED)
    #define RKH_HOOK_TIMEOUT(t)   \
        rkh_hook_timeout((t))
#else
    #define RKH_HOOK_TIMEOUT(t)           (void)0
#endif

#if (RKH_CFG_HOOK_SIGNAL_EN == RKH_ENABLED)
    #define RKH_HOOK_SIGNAL(e)    \
        rkh_hook_signal((RKH_EVT_T *)(e))
#else
    #define RKH_HOOK_SIGNAL(e)            (void)0
#endif

#if (RKH_CFG_HOOK_START_EN == RKH_ENABLED)
    #define RKH_HOOK_START()    \
        rkh_hook_start()
#else
    #define RKH_HOOK_START()                (void)0
#endif

#if (RKH_CFG_HOOK_EXIT_EN == RKH_ENABLED)
    #define RKH_HOOK_EXIT() \
        rkh_hook_exit()
#else
    #define RKH_HOOK_EXIT()                 (void)0
#endif

#if (RKH_CFG_HOOK_TIMETICK_EN == RKH_ENABLED)
    #define RKH_HOOK_TIMETICK() \
        rkh_hook_timetick()
#else
    #define RKH_HOOK_TIMETICK()             (void)0
#endif

#if (RKH_CFG_TRC_EN      == RKH_ENABLED  && \
     (RKH_CFG_TRC_ALL_EN  == RKH_ENABLED  || \
      RKH_CFG_TRC_FWK_EN  == RKH_ENABLED))
    #define R_TRC_AO_NAME_EN    RKH_ENABLED
#endif

#if (RKH_CFG_SMA_INIT_EVT_EN == RKH_ENABLED)
    #if defined(R_TRC_AO_NAME_EN)
        #define MKRRKH(name, prio, ppty, is, ia, ie) \
            {(prio), (ppty), # name, (RKHROM struct RKH_ST_T *)is, (ia), (ie)}
    #else
        #define MKRRKH(name, prio, ppty, is, ia, ie) \
            {(prio), (ppty), (RKHROM struct RKH_ST_T *)is, (ia), (ie)}
    #endif
#else
    #if defined(R_TRC_AO_NAME_EN)
        #define MKRRKH(name, prio, ppty, is, ia, ie) \
            {(prio), (ppty), # name, (RKHROM struct RKH_ST_T *)is, (ia)}
    #else
        #define MKRRKH(name, prio, ppty, is, ia, ie) \
            {(prio), (ppty), (RKHROM struct RKH_ST_T *)is, (ia)}
    #endif
#endif

#define MKSMA(rr, s) \
    { \
        { \
            (RKHROM RKH_ROM_T *)(rr), \
            (RKHROM struct RKH_ST_T *)(s) \
        } \
    }

#if defined(R_TRC_AO_NAME_EN)
    #define MKBASE(t, n)        {t, # n}
#else
    #define MKBASE(t, n)        {t}
#endif

#if (RKH_CFG_SMA_HCAL_EN == RKH_ENABLED)
    #if (RKH_CFG_SMA_PPRO_EN == RKH_ENABLED)
        #if defined(RKH_HISTORY_ENABLED)
            #define MKBASIC(n,pp)       n##_trtbl,pp
            #define MKCOMP(n,d,h)       n##_trtbl,NULL,d,h
        #else
            #define MKBASIC(n,pp)       n##_trtbl,pp
            #define MKCOMP(n,d,h)       n##_trtbl,NULL,d
        #endif
    #else
        #if defined(RKH_HISTORY_ENABLED)
            #define MKBASIC(n,pp)       n##_trtbl
            #define MKCOMP(n,d,h)       n##_trtbl,d,h
        #else
            #define MKBASIC(n,pp)       n##_trtbl
            #define MKCOMP(n,d,h)       n##_trtbl,d
        #endif
    #endif
    #define MKST(en,ex,p)           en,ex,(RKHROM struct RKH_ST_T *)p
    #define MKSBM(n,sbm)            n##_trtbl,n##_exptbl,sbm
    #define MKMCH(d,i,n)            d,i,(RKHROM RKH_ST_T * *)&rdyp_##n
    #define MKENP(e,s)              e,(RKHROM struct RKH_ST_T *)s
#else
    #if (RKH_CFG_SMA_PPRO_EN == RKH_ENABLED)
        #define MKBASIC(n,pp)       n##_trtbl,pp
        #define MKCOMP(n,d,h)       n##_trtbl,NULL
    #else
        #define MKBASIC(n,pp)       n##_trtbl
        #define MKCOMP(n,d,h)       n##_trtbl
    #endif
    #define MKST(en,ex,p)
    #define MKSBM(n,sbm)            n##_trtbl,n##_exptbl,sbm
    #define MKMCH(d,i,n)            d,i,(RKHROM RKH_ST_T *)&rdyp_##n
    #define MKENP(e,s)              e,(RKHROM struct RKH_ST_T *)s
#endif

#define MK_SET_EVT(ev_obj, ev_sig)                                \
    ((RKH_EVT_T *)(ev_obj))->e = (RKH_SIG_T)ev_sig;  \
    ((RKH_EVT_T *)(ev_obj))->nref = 0;               \
    ((RKH_EVT_T *)(ev_obj))->pool = 0

#define MK_EVT(ev_obj, ev_sig)                                    \
    RKH_EVT_T ev_obj = {ev_sig, 0, 0}

#define MK_ROM_EVT(ev_obj, ev_sig)                                \
    RKHROM RKH_EVT_T ev_obj = {ev_sig,  0, 0}

#define MK_EVT_STRUCT(ev_sig)                                     \
    {ev_sig, 0, 0}

#ifndef RKH_DIS_INTERRUPT
    #error \
    "rkhport.h, Must be defined the platform-dependent macro RKH_DIS_INTERRUPT"
#endif

#ifndef RKH_ENA_INTERRUPT
    #error \
    "rkhport.h, Must be defined the platform-dependent macro RKH_ENA_INTERRUPT"
#endif

#ifndef RKH_EN_DOXYGEN
    #define RKH_EN_DOXYGEN  0
#endif

#if RKH_EN_DOXYGEN == RKH_ENABLED
    /**
     *	If the #RKH_CFGPORT_SMA_THREAD_EN is set to 1, each SMA (active
     *	object) has its own thread of execution.
     */
    #define RKH_CFGPORT_SMA_THREAD_EN           RKH_ENABLED

    /**
     *	If the #RKH_CFGPORT_SMA_THREAD_EN and
     *	#RKH_CFGPORT_SMA_THREAD_DATA_EN are set to 1, each SMA (active
     *	object) has its own thread of execution and its own object data.
     */
    #define RKH_CFGPORT_SMA_THREAD_DATA_EN      RKH_ENABLED

    /**
     *  If the #RKH_CFGPORT_NATIVE_SCHEDULER_EN is set to 1 then RKH will
     *  include the simple, cooperative, and nonpreemptive scheduler RKHS.
     *  When #RKH_CFGPORT_NATIVE_SCHEDULER_EN is enabled RKH also will
     *  automatically define #RKH_EQ_TYPE, RKH_SMA_BLOCK(), RKH_SMA_READY(),
     *  RKH_SMA_UNREADY(), and assume the native priority scheme.
     */
    #define RKH_CFGPORT_NATIVE_SCHEDULER_EN     RKH_ENABLED

    /**
     *  If the #RKH_CFGPORT_NATIVE_EQUEUE_EN is set to 1 and the native
     *  event queue is enabled (see #RKH_CFG_RQ_EN) then RKH will include
     *  its own implementation of rkh_sma_post_fifo(), rkh_sma_post_lifo(),
     *  and rkh_sma_get() functions.
     */
    #define RKH_CFGPORT_NATIVE_EQUEUE_EN        RKH_ENABLED

    /**
     *  If the #RKH_CFGPORT_NATIVE_DYN_EVT_EN is set to 1 and the native
     *  fixed-size memory block facility is enabled (see #RKH_CFG_MP_EN)
     *  then RKH will include its own implementation of dynamic memory
     *  management. When #RKH_CFGPORT_NATIVE_DYN_EVT_EN is enabled RKH
     *  also will automatically define RKH_DYNE_TYPE, RKH_DYNE_INIT(),
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
    #define RKH_CFGPORT_SMA_STK_EN              RKH_ENABLED

    /**
     *  Defines the data type of the event queue for active objects.
     *  The event queue can be implemented with a message queue of
     *  the RTOS/OS. But it is also possible to use the native RKH
     *  queue RKH_RQ_T type if the underlying RTOS/OS does not provide
     *  an adequate queue.
     *
     *  <EM>Example for using the native queue</EM>
     *  \code
     *	// RKH's native queue
     *  #define RKH_EQ_TYPE			RKH_RQ_T
     *	// Message queue of ucos/II
     *  #define RKH_EQ_TYPE			OS_EVENT
     *	// Message queue of FreeRTOS
     *  #define RKH_EQ_TYPE			xQueueHandle
     *  \endcode
     */
    #define RKH_EQ_TYPE

    /**
     *  Frequently, the active object has its own task processing loop that
     *  waits for the signal to be posted, and when it is, loops to remove
     *  and process all events that are currently queued.
     *  The RKH_SMA_POST_FIFO() macro enqueues an event and signals	the OS
     *  that an event has arrived. In this case, \c os_signal holds the OS
     *  object used to signal that an event has been queued.
     *  The data type RKH_THREAD_TYPE holds the thread handle associated
     *  with the active object.
     *
     *  <EM>Example for using the uCOS/II, FreeRTOS, Linux (Posix) and
     *  Win32</EM>
     *  \code
     *	// For uCOS/II
     *  #define RKH_THREAD_TYPE		INT8U
     *	// For FreeRTOS
     *  #define RKH_THREAD_TYPE		xTaskHandle
     *	// For Linux (Posix)
     *  #define RKH_THREAD_TYPE		pthread_t
     *	// For Win32
     *  #define RKH_THREAD_TYPE		void*
     *  \endcode
     */
    #define RKH_THREAD_TYPE

    /**
     *  The \c os_signal member of RKH_SMA_T is necessary when the underlying
     *  OS does not provide an adequate queue facility, so the native RKH
     *  queue RKH_RQ_T must be used. In this case the RKH_OSSIGNAL_TYPE
     *  indicates an operating system specific primitive to efficiently
     *  block the native RKH event queue when the queue is empty.
     *  Frequently, the active object has its own task processing loop that
     *  waits for the signal to be posted, and when it is, loops to remove
     *  and process all events that are currently queued.
     *  The RKH_SMA_POST_FIFO() macro enqueues an event and signals	the OS
     *  that an event has arrived. In this case, \c os_signal holds the OS
     *  object used to signal that an event has been queued.
     *
     *  <EM>Example for using the Linux (Posix) and Win32</EM>
     *  \code
     *	// For Linux (Posix)
     *  #define RKH_OSSIGNAL_TYPE	pthread_cond_t
     *	// For Win32
     *  #define RKH_OSSIGNAL_TYPE	void*
     *  \endcode
     */
    #define RKH_OSSIGNAL_TYPE

    /**@{
     *  RKH need to disable interrupts in order to access critical sections
     *  of code, and re-enable interrupts when done. This allows RKH to
     *  protect critical code from being entered simultaneously. To hide the
     *  implementation method chosen by the processor, compiler, etc, RKH
     *  defines two macros to unconditionally disable and enable interrupts:
     *  RKH_DIS_INTERRUPT() and RKH_ENA_INTERRUPT() respectively. Obviously,
     *  they resides in \b rkhport.h file, which the user always need to
     *  provide.
     *
     *  <EM>Example for HCS08 CW6.3 from C:</EM>
     *  \code
     *  #define RKH_DIS_INTERRUPT()			DisableInterrupts
     *  #define RKH_ENA_INTERRUPT()			EnableInterrupts
     *  \endcode
     */
    #define RKH_DIS_INTERRUPT()
    #define RKH_ENA_INTERRUPT()
    /*@}*/

    /**@{
     *  \brief
     *  RKH need to disable interrupts in order to access critical sections of
     *  code, and re-enable interrupts when done.
     *
     *  This allows RKH to protect
     *  critical code from being entered simultaneously from either multiple
     *  SMAs or ISRs. Every processor generally provide instructions to
     *  disable/enable interrupts and the C compiler must have a mechanism to
     *  perform these operations directly from C. Some compilers will allows
     *  to insert in-line assembly language statements in the C source code.
     *  This makes it quite easy to insert processor instructions to enable and
     *  disable interrupts. Other compilers will actually contain language
     *  extensions to enable and disable interrupts directly from C. To hide
     *  the implementation method chosen by the compiler manufacturer, RKH
     *  defines two macros to disable and enable interrupts:
     *  RKH_ENTER_CRITICAL() and RKH_EXIT_CRITICAL().
     *
     *  The RKH_ENTER_CRITICAL() macro saves the interrupt disable status onto
     *  the stack and then, disable interrupts.
     *  RKH_EXIT_CRITICAL() would simply be implemented by restoring the
     *  interrupt status from the stack. Using this scheme, if it's called a
     *  RKH service with either interrupts enabled or disabled then, the
     *  status would be preserved across the call. If calls a RKH service with
     *  interrupts disabled, is potentially extending the interrupt latency of
     *  application. The application can use RKH_ENTER_CRITICAL() and
     *  RKH_EXIT_CRITICAL() to also protect critical sections of code. As a
     *  general rule, should always call RKH services with interrupts enabled!.
     *
     *  \note
     *  These macros are internal to RKH and the user application should
     *  not call it.
     *
     *  <EM>Example for x86, VC2008, and win32 single thread:</EM>
     *  \code
     *  //#define RKH_CPUSR_TYPE
     *  #define RKH_ENTER_CRITICAL( dummy )		EnterCriticalSection(&csection)
     *  #define RKH_EXIT_CRITICAL( dummy )		LeaveCriticalSection(&csection)
     *  \endcode
     */
    #define RKH_CPUSR_TYPE
    #define RKH_SR_ALLOC() \
        RKH_CPUSR_TYPE sr = (RKH_CPUSR_TYPE)0
    #define RKH_ENTER_CRITICAL(dummy)
    #define RKH_EXIT_CRITICAL(dummy)
    /*@}*/

    /**
     *  \brief
     *  Encapsulates the mechanism of blocking the event queue.
     *
     *  \param[in] sma		pointer to SMA.
     */
    #define RKH_SMA_BLOCK(sma)

    /**
     *  \brief
     *  Encapsulates the mechanism of signaling the thread waiting on the
     *  used event queue. Thus, the SMA is inserted in the ready list as
     *  ready-to-dispatch.
     *
     *  \param[in] rg		ready group.
     *  \param[in] sma		pointer to SMA.
     */
    #define RKH_SMA_READY(rg, sma)

    /**
     *  \brief
     *  Informs the underlying kernel that the SMA event queue is becoming
     *  empty. Thus, the SMA is removed from the ready list.
     *
     *  \param[in] rg		ready group.
     *  \param[in] sma		pointer to SMA.
     */
    #define RKH_SMA_UNREADY(rg, sma)

    /**
     *  \brief
     *  Defines the data type of the fixed-size memory block for
     *  dynamic event support.
     *
     *  The fixed-size memory block can be implemented with a RTOS/OS
     *  service provided to that. But it's also possible to use the native
     *  RKH fixed-size memory block RKH_MP_T type if the underlying RTOS/OS
     *  does not provide an adequate support.
     */
    #define RKH_DYNE_TYPE

    /**
     *  \brief
     *  Encapsulates the creation of a event pool.
     *
     *  Platform-dependent macro. Typically, must be define it in the
     *  specific port file (rkhport.h).
     *
     *  \param[in] mp	    pointer to previously allocated memory pool 
     *                      structure.
     *  \param[in] sstart	storage start. Pointer to memory from which 
     *                      memory blocks are allocated.
     *  \param[in] ssize:	storage size. Size of the memory pool storage in 
     *                      bytes.
     *  \param[in] esize	event size. This number determines the size of each
     *                      memory block in the pool.
     */
    #define RKH_DYNE_INIT(mp, sstart, ssize, esize)

    /**
     *  \brief
     *  Encapsulates how RKH should obtain the block size of pool.
     *
     *  Platform-dependent macro. Typically, must be define it in the
     *  specific port file (rkhport.h).
     *
     *  \param[in] mp		pointer to previously allocated memory pool 
     *                      structure.
     */
    #define RKH_DYNE_GET_ESIZE(mp)

    /**
     *  \brief
     *	Encapsulates how RKH should obtain an event \c e from the
     *	event pool \c mp.
     *
     *  Platform-dependent macro. Typically, must be define it in the
     *  specific port file (rkhport.h).
     *
     *  \param[in] mp		pointer to previously allocated memory pool 
     *                      structure.
     *  \param[in] e		pointer to a new event or NULL if the pool runs 
     *                      out of blocks.
     */
    #define RKH_DYNE_GET(mp, e)

    /**
     *  \brief
     *	Encapsulates how RKH should return an event \c e to the event
     *	pool \c mp.
     *
     *  Platform-dependent macro. Typically, must be define it in the
     *  specific port file (rkhport.h).
     *
     *  \param[in] mp		pointer to previously allocated memory pool 
     *                      structure.
     *  \param[in] e		pointer to the returned event.
     */
    #define RKH_DYNE_PUT(mp, e)
#endif

#ifdef RKH_CPUSR_TYPE
    #if RKH_EN_DOXYGEN == RKH_DISABLED
        #define RKH_SR_ALLOC()          RKH_CPUSR_TYPE sr = (RKH_CPUSR_TYPE)0
        #define RKH_ENTER_CRITICAL_()   RKH_ENTER_CRITICAL(sr)
        #define RKH_EXIT_CRITICAL_()    RKH_EXIT_CRITICAL(sr)
    #endif
#else
    #define RKH_SR_ALLOC()
    #define RKH_ENTER_CRITICAL_()       RKH_ENTER_CRITICAL(dummy)
    #define RKH_EXIT_CRITICAL_()        RKH_EXIT_CRITICAL(dummy)
#endif

#if (RKH_CFG_SMA_INIT_ARG_SMA_EN == RKH_ENABLED && \
     RKH_CFG_SMA_INIT_EVT_EN == RKH_ENABLED)
    #define RKH_EXEC_INIT(h) \
    { \
        if (CIA(h) != NULL) \
        { \
            (*CIA(h))((h), CIA(h)->romrkh->ievent); \
            RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_INI, \
                              (h), \
                              0, \
                              CIA(h)); \
        } \
    }
#elif (RKH_CFG_SMA_INIT_ARG_SMA_EN == RKH_ENABLED && \
       RKH_CFG_SMA_INIT_EVT_EN == RKH_DISABLED)
    #define RKH_EXEC_INIT(h) \
    { \
        if (CIA(h) != NULL) \
        { \
            (*CIA(h))((h)); \
            RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_INI, \
                              (h), \
                              0, \
                              CIA(h)); \
        } \
    }
#elif (RKH_CFG_SMA_INIT_ARG_SMA_EN == RKH_DISABLED && \
       RKH_CFG_SMA_INIT_EVT_EN == RKH_ENABLED)
    #define RKH_EXEC_INIT(h) \
    { \
        if (CIA(h) != NULL) \
        { \
            (*CIA(h))(CIA(h)->romrkh->ievent); \
            RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_INI, \
                              (h), \
                              0, \
                              CIA(h)); \
        } \
    }
#else
    #define RKH_EXEC_INIT(h) \
    { \
        if (CIA(h) != NULL) \
        { \
            (*CIA(h))(); \
            RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_INI, \
                              (h), \
                              0, \
                              CIA(h)); \
        } \
    }
#endif

#if RKH_CFG_SMA_ENT_ARG_SMA_EN == RKH_ENABLED
    #if RKH_CFG_SMA_ENT_ARG_STATE_EN == RKH_ENABLED
    #define RKH_EXEC_ENTRY(s, h) \
    { \
        if ((s)->enter != NULL) \
        { \
            (*(s)->enter)(h, s); \
            RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_EN, \
                              (h), \
                              (s), \
                              (s)->enter); \
        } \
    }
    #else
    #define RKH_EXEC_ENTRY(s, h) \
    { \
        if ((s)->enter != NULL) \
        { \
            (*(s)->enter)(h); \
            RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_EN, \
                              (h), \
                              (s), \
                              (s)->enter); \
        } \
    }
    #endif
#else
    #if RKH_CFG_SMA_ENT_ARG_STATE_EN == RKH_ENABLED
    #define RKH_EXEC_ENTRY(s, h) \
    { \
        if ((s)->enter != NULL) \
        { \
            (*(s)->enter)(s); \
            RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_EN, \
                              (h), \
                              (s), \
                              (s)->enter); \
        } \
    }
    #else
    #define RKH_EXEC_ENTRY(s, h) \
    { \
        if ((s)->enter != NULL) \
        { \
            (*(s)->enter)(); \
            RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_EN, \
                              (h), \
                              (s), \
                              (s)->enter); \
        } \
    }
    #endif
#endif

#if RKH_CFG_SMA_EXT_ARG_SMA_EN == RKH_ENABLED
    #if RKH_CFG_SMA_ENT_ARG_STATE_EN == RKH_ENABLED
    #define RKH_EXEC_EXIT(s, h) \
    { \
        if ((s)->exit != NULL) \
        { \
            (*(s)->exit)(h, s); \
            RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_EX, \
                              (h), \
                              (s), \
                              (s)->exit); \
        } \
    }
    #else
    #define RKH_EXEC_EXIT(s, h) \
    {                                                       \
        if ((s)->exit != NULL) \
        { \
            (*(s)->exit)(h); \
            RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_EX,  \
                              (h), \
                              (s), \
                              (s)->exit); \
        } \
    }
    #endif
#else
    #if RKH_CFG_SMA_ENT_ARG_STATE_EN == RKH_ENABLED
    #define RKH_EXEC_EXIT(s, h) \
    { \
        if ((s)->exit != NULL) \
        { \
            (*(s)->exit)(s); \
            RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_EX, \
                              (h), \
                              (s), \
                              (s)->exit); \
        } \
    }
    #else
    #define RKH_EXEC_EXIT(s, h) \
    { \
        if ((s)->exit != NULL) \
        {  \
            (*(s)->exit)(); \
            RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_EX, \
                              (h), \
                              (s), \
                              (s)->exit); \
        } \
    }
    #endif
#endif

#if RKH_CFG_SMA_PPRO_ARG_SMA_EN == RKH_ENABLED
    #define RKH_EXEC_PREPRO(s, h, e) \
        (*(s)->prepro)(h, e); \
        RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_PP, \
                          (h), \
                          (h)->state, \
                          (s)->prepro)
#else
    #define RKH_EXEC_PREPRO(s, h, e) \
        (*(s)->prepro)(e); \
        RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_PP, \
                          (h), \
                          (h)->state, \
                          (s)->prepro)
#endif

#if (RKH_CFG_SMA_ACT_ARG_EVT_EN == RKH_ENABLED && \
     RKH_CFG_SMA_ACT_ARG_SMA_EN == RKH_ENABLED)
    #define RKH_EXEC_EFF(a, h, e) \
        (*CTA(a))((h), (e)); \
        RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_EFF, \
                          (h), \
                          (h)->state, \
                          (a))
#elif (RKH_CFG_SMA_ACT_ARG_EVT_EN == RKH_ENABLED && \
       RKH_CFG_SMA_ACT_ARG_SMA_EN == RKH_DISABLED)
    #define RKH_EXEC_EFF(a, h, e) \
        (*CTA(a))((e)); \
        RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_EFF, \
                          (h), \
                          (h)->state, \
                          (a))
#elif (RKH_CFG_SMA_ACT_ARG_EVT_EN == RKH_DISABLED && \
       RKH_CFG_SMA_ACT_ARG_SMA_EN == RKH_ENABLED)
    #define RKH_EXEC_EFF(a, h, e) \
        (*CTA(a))((h)); \
        RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_EFF, \
                          (h), \
                          (h)->state, \
                          (a))
#else
    #define RKH_EXEC_EFF(a, h, e) \
        (*CTA(a))(); \
        RKH_TR_SM_EXE_ACT(RKH_SUBTE_SM_EXE_ACT_EFF, \
                          (h), \
                          (h)->state, \
                          (a))
#endif

#if (RKH_CFG_SMA_GRD_ARG_EVT_EN == RKH_ENABLED && \
     RKH_CFG_SMA_GRD_ARG_SMA_EN == RKH_ENABLED)
    #define RKH_EXEC_GUARD(t, h, e)     (*(t)->guard)(h, e)
#elif (RKH_CFG_SMA_GRD_ARG_EVT_EN == RKH_ENABLED && \
       RKH_CFG_SMA_GRD_ARG_SMA_EN == RKH_DISABLED)
    #define RKH_EXEC_GUARD(t, h, e)     (*(t)->guard)(e)
#elif (RKH_CFG_SMA_GRD_ARG_EVT_EN == RKH_DISABLED && \
       RKH_CFG_SMA_GRD_ARG_SMA_EN == RKH_ENABLED)
    #define RKH_EXEC_GUARD(t, h, e)     (*(t)->guard)(h)
#else
    #define RKH_EXEC_GUARD(t, h, e)     (*(t)->guard)()
#endif

/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */

/*
 *  For GNU compatibility.
 */

struct rkh_t;
struct RKH_SMA_T;

/**
 *  \brief
 *  Initialization action.
 *
 *  Frequently, the state transition originating at the black ball is called
 *  the initial transition. Such transition designates the first active state
 *  after the state machine object is created. An initial transition can have
 *  associated actions, which in the UML notation are enlisted after the
 *  forward slash (/). In RKH framework, the application code must trigger
 *  the initial transition explicitly by invoking rkh_sma_activate() function.
 */
#if (RKH_CFG_SMA_INIT_ARG_SMA_EN == RKH_ENABLED && \
     RKH_CFG_SMA_INIT_EVT_EN == RKH_ENABLED)
    typedef void (*RKH_INIT_ACT_T)(const struct RKH_SMA_T *sma,
                                   const struct RKH_EVT_T *e);
#elif (RKH_CFG_SMA_INIT_ARG_SMA_EN == RKH_ENABLED && \
       RKH_CFG_SMA_INIT_EVT_EN == RKH_DISABLED)
    typedef void (*RKH_INIT_ACT_T)(const struct RKH_SMA_T *sma);
#elif (RKH_CFG_SMA_INIT_ARG_SMA_EN == RKH_DISABLED && \
       RKH_CFG_SMA_INIT_EVT_EN == RKH_ENABLED)
    typedef void (*RKH_INIT_ACT_T)(const struct RKH_EVT_T *e);
#else
    typedef void (*RKH_INIT_ACT_T)(void);
#endif

/**
 *  \brief
 *  Defines the data structure into which the collected performance
 *  information for state machine is stored.
 *
 *  This member is optional, thus it could be declared as NULL or eliminated
 *  in compile-time with RKH_EN_SMA_GET_INFO = 0.
 */
typedef struct RKH_SMAI_T
{
    rui16_t ndevt;          /**< # of dispatched events */
    rui16_t exectr;         /**< # of executed transitions */
} RKH_SMAI_T;

/**
 *  \brief
 *  Constant parameters of state machine.
 *
 *	The constant key parameters of a state machine are allocated within.
 *	RKH_ROM_T is a ROM base structure of RKH_T.
 *
 *	\sa
 *	RKH_SMA_T structure definition for more information. Also,
 *	\link RKH_EVT_T single inheritance in C \endlink, and
 *	\link RKH_CREATE_BASIC_STATE another example \endlink.
 */
typedef struct ROMRKH_T
{
    /**
     *  \brief
     *  SMA (a.k.a Active Object) priority.
     *
     *  A unique priority number must be assigned to each SMA from 0 to
     *  RKH_LOWEST_PRIO. The lower the number, the higher the priority.
     */
    rui8_t prio;

    /**
     *  \brief
     *  State machine properties.
     *
     *  The available properties are enumerated in RKH_HPPTY_T enumeration in
     *  the rkh.h file.
     */
    rui8_t ppty;

    /**
     *  \brief
     *  Name of State Machine Application (a.k.a Active Object).
     *
     *  Pointer to an ASCII string (NULL terminated) to assign a name to the
     *	State Machine Application (a.k.a Active Object). The name can be
     *	displayed by debuggers or by Trazer.
     */
#if defined(R_TRC_AO_NAME_EN)
    const char *name;
#endif

    /**
     *  \brief
     *  Points to initial state.
     *
     *  This state could be defined either composite or basic
     *  (not pseudo-state).
     */
    RKHROM struct RKH_ST_T *istate;

    /**
     *  \brief
     *  Points to initializing action (optional).
     *
     *  The function prototype is defined as RKH_INIT_ACT_T. This argument is
     *  optional, thus it could be declared as NULL.
     */
    RKH_INIT_ACT_T iaction;

    /**
     *  \brief
     *	Pointer to an event that will be passed to state machine application
     *	when it starts. Could be used to pass arguments to the state machine
     *	like an argc/argv. This argument is optional, thus it could be
     *	declared as NULL or eliminated in compile-time with
     *	RKH_CFG_SMA_INIT_EVT_EN = 0.
     */
#if RKH_CFG_SMA_INIT_EVT_EN == RKH_ENABLED
    const RKH_EVT_T *ievent;
#endif
} RKH_ROM_T;

/**
 *  \brief
 *  Describes the SMA (active object in UML).
 *
 *	This structure resides in RAM because its members are dinamically updated
 *	by RKH (context of state machine).
 *	The \b #romrkh member points to RKH_ROM_T structure, allocated in ROM,
 *	to reduce the size of RAM consume. The key parameters of a state machine
 *	are allocated within. Therefore cannot be modified in runtime.
 *
 *  RKH_SMA_T is not intended to be instantiated directly, but rather
 *  serves as the base structure for derivation of state machines in the
 *  application code.
 *  The following example illustrates how to derive an state machine from
 *  RKH_T. Please note that the RKH_SMA_T member sm is defined as the
 *  FIRST member of the derived struct.
 *
 *	Example:
 *	\code
 *	//	...within state-machine's module
 *
 *	typedef struct
 *	{
 *		RKH_SMA_T sm;	// base structure
 *		rui8_t x;		// private member
 *		rui8_t y;		// private member
 *	} MYSM_T;
 *
 *  //	static instance of SMA object
 *	RKH_SMA_CREATE( MYSM_T, my, HCAL, &S1, my_iaction, &my_ievent );
 *	\endcode
 *
 *	\sa
 *	RKH_SMA_T structure definition for more information. Also,
 *	\link RKH_EVT_T single inheritance in C \endlink, and
 *	\link RKH_CREATE_BASIC_STATE another example \endlink.
 */
typedef struct RKH_SMA_T
{
    /**
     *  \brief
     *  Points to state machine object.
     */
    RKHROM RKH_ROM_T *romrkh;

    /**
     *  \brief
     *  Points to current state (basic state).
     */
    RKHROM struct RKH_ST_T *state;

    /**
     *  \brief
     *  OS-dependent thread of control of the active object.
     *
     *  Frequently, the active object has its own task processing loop that
     *  waits for the signal to be posted, and when it is, loops to remove
     *  and process all events that are currently queued.
     *  The RKH_SMA_POST_FIFO() macro enqueues an event and signals	the OS
     *  that an event has arrived. In this case, \c os_signal holds the OS
     *  object used to signal that an event has been queued.
     *	This data might be used in various ways, depending on the RKH port.
     *  In some ports it's used to store the thread handler.
     *
     *  \note
     *  This member is optional, thus it could be declared as NULL or
     *  eliminated in compile-time with RKH_CFGPORT_SMA_THREAD_EN = 0.
     */
#if RKH_CFGPORT_SMA_THREAD_EN == RKH_ENABLED
    RKH_THREAD_TYPE thread;

    /**
     *  \brief
     *	OS-dependent object used to signal that an event has been queued.
     *
     *  Frequently, the active object has its own task processing loop that
     *  waits for the signal to be posted, and when it is, loops to remove
     *  and process all events that are currently queued.
     *  The RKH_SMA_POST_FIFO() macro enqueues an event and signals	the OS
     *  that an event has arrived. In this case, \c os_signal holds the OS
     *  object used to signal that an event has been queued.
     *  This data might be used in various ways, depending on the RKH port.
     *  In some ports it's used to block the calling thread when the native
     *  RKH queue is empty. In other RKH ports the OS-dependent	data object
     *  might be used differently.
     *
     *  \note
     *  This member is optional, thus it could be eliminated in compile-time
     *  with RKH_CFGPORT_SMA_THREAD_DATA_EN = 0.
     */
#if RKH_CFGPORT_SMA_THREAD_DATA_EN == RKH_ENABLED
    RKH_OSSIGNAL_TYPE os_signal;
#endif
#endif

    /**
     *  \brief
     *  Event queue of the SMA (a.k.a Active Object).
     */
    RKH_EQ_TYPE equeue;

    /**
     *  \brief
     *  The Boolean loop variable determining if the thread routine
     *  of the SMA is running.
     */
    rbool_t running;

    /**
     *  \brief
     *  Performance information. This member is optional, thus it could be
     *  declared as NULL or eliminated in compile-time with
     *  RKH_CFG_SMA_GET_INFO_EN = 0.
     */
#if RKH_CFG_SMA_GET_INFO_EN == RKH_ENABLED
    RKH_SMAI_T sinfo;
#endif
} RKH_SMA_T;

/**
 *  \brief
 *  Entry action.
 *
 *  The actions that are always executed when a state is entered
 *  should be specified as entry actions. UML statecharts provide optional
 *  entry and exit actions, which are associated with states rather than
 *  transitions, as in a Moore automaton.
 *  An entry function takes the state machine pointer as argument.
 *  This argument is optional, thus it could be eliminated in
 *  compile-time by means of RKH_CFG_SMA_ENT_ARG_SMA_EN.
 *
 *  The RKH implementation preserves the transition sequence imposed by
 *  Harel's Statechart and UML. Specifically, the implemented transition
 *  sequence is as follows:
 *
 *  - Execute exit actions of the source state.
 *  - Execute the transition actions.
 *  - Execute entry actions of the target state.
 *
 *  \note
 *  This callback is referenced from RKH_CREATE_COMP_STATE() and
 *  RKH_CREATE_BASIC_STATE() macros.
 *  \b RKH_CFG_SMA_ENT_ARG_SMA_EN macro.
 */

#if RKH_CFG_SMA_ENT_ARG_SMA_EN == RKH_ENABLED
    #if RKH_CFG_SMA_ENT_ARG_STATE_EN == RKH_ENABLED
    typedef void (*RKH_ENT_ACT_T)(const struct RKH_SMA_T *sma,
                                  const struct RKH_ST_T *state);
    #else
    typedef void (*RKH_ENT_ACT_T)(const struct RKH_SMA_T *sma);
    #endif
#else
    #if RKH_CFG_SMA_ENT_ARG_STATE_EN == RKH_ENABLED
    typedef void (*RKH_ENT_ACT_T)(const struct RKH_ST_T *state);
    #else
    typedef void (*RKH_ENT_ACT_T)(void);
    #endif
#endif

/**
 *  \brief
 *  Exit action.
 *
 *  The actions that are always execute when a state is exited should be
 *  exit actions. UML statecharts provide optional entry and exit actions,
 *  which are associated with states rather than transitions, as in a
 *  Moore automaton.
 *  An exit function takes the state machine pointer as argument.
 *  This argument is optional, thus it could be eliminated in
 *  compile-time by means of RKH_CFG_SMA_EXT_ARG_SMA_EN.
 *
 *  The RKH implementation preserves the transition sequence imposed by
 *  Harel's Statechart and UML. Specifically, the implemented transition
 *  sequence is as follows:
 *
 *  - Execute exit actions of the source state.
 *  - Execute the transition actions.
 *  - Execute entry actions of the target state.
 *
 *  \note
 *  This callback is referenced from RKH_CREATE_COMP_STATE() and
 *  RKH_CREATE_BASIC_STATE() macros.
 */

#if RKH_CFG_SMA_EXT_ARG_SMA_EN == RKH_ENABLED
    #if RKH_CFG_SMA_ENT_ARG_STATE_EN == RKH_ENABLED
    typedef void (*RKH_EXT_ACT_T)(const struct RKH_SMA_T *sma,
                                  const struct RKH_ST_T *state);
    #else
    typedef void (*RKH_EXT_ACT_T)(const struct RKH_SMA_T *sma);
    #endif
#else
    #if RKH_CFG_SMA_ENT_ARG_STATE_EN == RKH_ENABLED
    typedef void (*RKH_EXT_ACT_T)(const struct RKH_ST_T *state);
    #else
    typedef void (*RKH_EXT_ACT_T)(void);
    #endif
#endif

/**
 *  \brief
 *  Event preprocessor.
 *
 *  Before sending the arrived event to state machine, it can be previously
 *  processed using the	event preprocessor function.
 *  The RKH framework provides optional event preprocessor
 *  action, which are associated with states rather than transitions,
 *  as in a Moore automaton.
 *  This action takes the state machine pointer and the event
 *  pointer as arguments.
 *  This argument is optional, thus it could be eliminated in
 *  compile-time by means of RKH_CFG_SMA_PPRO_ARG_SMA_EN.
 *
 *  \note
 *  This callback is referenced from RKH_CREATE_COMP_STATE() and
 *  RKH_CREATE_BASIC_STATE() macros.
 */
#if RKH_CFG_SMA_PPRO_ARG_SMA_EN == RKH_ENABLED
    typedef RKH_SIG_T (*RKH_PPRO_T)(const struct RKH_SMA_T *sma,
                                    RKH_EVT_T *pe);
#else
    typedef RKH_SIG_T (*RKH_PPRO_T)(RKH_EVT_T *pe);
#endif

/**
 *  \brief
 *  Transition action.
 *
 *  Transition actions are small atomic behaviors executed at specified points
 *  in a state machine. This actions are assumed to take an insignificant
 *  amount of time to execute and are noninterruptible. UML statecharts
 *  are extended state machines with characteristics of both Mealy and
 *  Moore automata. In statecharts, actions generally depend on both
 *  the state of the system and the triggering event, as in a Mealy
 *  automaton. Additionally, UML statecharts provide optional entry and
 *  exit actions, which are associated with states rather than transitions,
 *  as in a Moore automaton.
 *  An action function takes the state machine pointer and the event
 *  pointer as arguments.
 *  These arguments are optional, thus they could be eliminated in
 *  compile-time by means of RKH_CFG_SMA_ACT_ARG_EVT_EN and \b
 *  RKH_CFG_SMA_ACT_ARG_SMA_EN.
 *
 *  The RKH implementation preserves the transition sequence imposed by
 *  Harel's Statechart and UML. Specifically, the implemented transition
 *  sequence is as follows:
 *
 *  - Execute exit actions of the source state.
 *  - Execute the transition actions.
 *  - Execute entry actions of the target state.
 *
 *  \note
 *  This callback is referenced from RKH_TRREG() and RKH_TRINT()macro.
 */

#if (RKH_CFG_SMA_ACT_ARG_EVT_EN == RKH_ENABLED && \
     RKH_CFG_SMA_ACT_ARG_SMA_EN == RKH_ENABLED)
    typedef void (*RKH_TRN_ACT_T)(const struct RKH_SMA_T *sma,
                                  RKH_EVT_T *pe);
#elif (RKH_CFG_SMA_ACT_ARG_EVT_EN == RKH_ENABLED && \
       RKH_CFG_SMA_ACT_ARG_SMA_EN == RKH_DISABLED)
    typedef void (*RKH_TRN_ACT_T)(RKH_EVT_T *pe);
#elif (RKH_CFG_SMA_ACT_ARG_EVT_EN == RKH_DISABLED && \
       RKH_CFG_SMA_ACT_ARG_SMA_EN == RKH_ENABLED)
    typedef void (*RKH_TRN_ACT_T)(const struct RKH_SMA_T *sma);
#else
    typedef void (*RKH_TRN_ACT_T)(void);
#endif

/**
 *  \brief
 *  Guard.
 *
 *	A guard is a boolean condition that returns a true (RKH_GTRUE) or
 *	false (RKH_GFALSE) value that controls whether or not a transition
 *	is taken following the receipt of a triggering event. A transition
 *	with a guard is only take if the triggering event occurs and the
 *	guard evaluates to true. As long as the guard evaluated to false,
 *	the triggering event would be discarded and the transition would
 *	not be taken.
 *	Each condition connector can have one special branch with a guard
 *	labeled rkh_else, which is taken if all the guards on the other
 *	branches are false.
 *  A guard function takes the state machine pointer and the event
 *  pointer as arguments.
 *  These arguments are optional, thus they could be eliminated in
 *  compile-time by means of \b RKH_CFG_SMA_GRD_ARG_EVT_EN and
 *  \b RKH_CFG_SMA_GRD_ARG_SMA_EN.
 *
 *  \note
 *  This callback is referenced from RKH_BRANCH() macro.
 */

#if (RKH_CFG_SMA_GRD_ARG_EVT_EN == RKH_ENABLED && \
     RKH_CFG_SMA_GRD_ARG_SMA_EN == RKH_ENABLED)

    typedef rbool_t (*RKH_GUARD_T)(const struct RKH_SMA_T *sma,
                                   RKH_EVT_T *pe);
#elif (RKH_CFG_SMA_GRD_ARG_EVT_EN == RKH_ENABLED && \
       RKH_CFG_SMA_GRD_ARG_SMA_EN == RKH_DISABLED)
    typedef rbool_t (*RKH_GUARD_T)(RKH_EVT_T *pe);
#elif (RKH_CFG_SMA_GRD_ARG_EVT_EN == RKH_DISABLED && \
       RKH_CFG_SMA_GRD_ARG_SMA_EN == RKH_ENABLED)
    typedef rbool_t (*RKH_GUARD_T)(const struct RKH_SMA_T *sma);
#else
    typedef rbool_t (*RKH_GUARD_T)(void);
#endif

/**
 *  \brief
 *  Maintains the basic information of a state.
 */
typedef struct RKH_BASE_T
{
    /**
     *  \brief
     *  State type.
     *
     *	Contains the type of a particular state and can have
     *	the following values:
     *
     *	- \b RKH_COMPOSITE:     composite state.
     *	- \b RKH_BASIC:         basic state.
     *	- \b RKH_CHOICE:        choice pseudostate.
     *	- \b RKH_CONDITIONAL:   conditional pseudostate.
     *	- \b RKH_SHISTORY:      shadow history pseudostate.
     *	- \b RKH_DHISTORY:      deep history pseudostate.
     */
    ruint type;

    /**
     *  \brief
     *  Name of state or pseudostate.
     *
     *  Pointer to an ASCII string (NULL terminated) to assign a name to the
     *	state object or pseudostate object. The name can be displayed by
     *	debuggers or by Trazer.
     */
#if defined(R_TRC_AO_NAME_EN)
    const char *name;
#endif
} RKH_BASE_T;

/**
 *  \brief
 *  Describes the state transition.
 *
 *  Transitions represent the response of a state machine to events.
 *  Any event that is not explicitly listed as causing an event to occur
 *  in a given state is quietly discarded should it occur.
 */
typedef struct RKH_TR_T
{
    /**
     *  \brief
     *  Triggering event.
     */
    RKH_SIG_T event;

    /**
     *  \brief
     *	Points to guard function.
     */
    RKH_GUARD_T guard;

    /**
     *  \brief
     *  Points to transition action.
     */
    RKH_TRN_ACT_T action;

    /**
     *  \brief
     *  Points to target state.
     */
    RKHROM void *target;
} RKH_TR_T;

/**
 *	\brief
 *  Describes the common properties of regular states (basic, composite,
 *  and submachine).
 */
typedef struct RKH_ST_T
{
    /**
     *  \brief
     *	Maintains the basic information of state.
     */
    struct RKH_BASE_T base;

#if RKH_CFG_SMA_HCAL_EN == RKH_ENABLED
    /**
     *  \brief
     *	Points to entry action.
     */
    RKH_ENT_ACT_T enter;

    /**
     *  \brief
     *	Points to exit action.
     */
    RKH_EXT_ACT_T exit;

    /**
     *  \brief
     *	Points to state's parent.
     */
    RKHROM struct RKH_ST_T *parent;
#endif
} RKH_ST_T;

/**
 *	\brief
 *  Describes a basic state.
 */
typedef struct RKH_SBSC_T
{
    RKH_ST_T st;

    /**
     *  \brief
     *	Points to state transition table.
     */
    RKHROM struct RKH_TR_T *trtbl;

    /**
     *  \brief
     *	Points to event preprocessor.
     *
     *	Aditionally, by means of single inheritance in C it could be
     *	used as state's abstract data.
     *	Aditionally, implementing the single inheritance in C is very
     *	simply by literally embedding the base type, RKH_PPRO_T in
     *	this case, as the first member of the derived structure.
     *
     *	This argument is optional, thus it could be declared as NULL.
     *
     *	Example:
     *
     *  \code
     *	static
     *	RKH_SIG_T
     *	preprocessor( RKH_EVT_T *pe )
     *	{
     *		...
     *	}
     *
     *	typedef struct
     *	{
     *		RKH_PPRO_T prepro;  // extend the RKH_PPRO_T class
     *		unsigned min:4;
     *		unsigned max:4;
     *		char *buff;
     *	} SDATA_T;
     *
     *	static const SDATA_T option = { preprocessor, 4, 8, token1 };
     *
     *	RKH_CREATE_BASIC_STATE( S111, set_x_1,
     *							NULL, &S11, preprocessor );
     *	RKH_CREATE_BASIC_STATE( S22, set_x_4,
     *							NULL, &S2, (RKH_PPRO_T*)&option );
     * \endcode
     */
#if RKH_CFG_SMA_PPRO_EN == RKH_ENABLED
    RKH_PPRO_T prepro;
#endif
} RKH_SBSC_T;

/**
 *	\brief
 *  Describes a composite state.
 */
typedef struct RKH_SCMP_T
{
    RKH_ST_T st;

    /**
     *  \brief
     *	Points to state transition table.
     */
    RKHROM struct RKH_TR_T *trtbl;

    /**
     *  \brief
     *	Points to event preprocessor.
     *
     *	Aditionally, by means of single inheritance in C it could be
     *	used as state's abstract data.
     *	Aditionally, implementing the single inheritance in C is very
     *	simply by literally embedding the base type, RKH_PPRO_T in
     *	this case, as the first member of the derived structure.
     *
     *	This argument is optional, thus it could be declared as NULL.
     *
     *	Example:
     *
     *  \code
     *	static
     *	RKH_SIG_T
     *	preprocessor( RKH_EVT_T *pe )
     *	{
     *		...
     *	}
     *
     *	typedef struct
     *	{
     *		RKH_PPRO_T prepro;  // extend the RKH_PPRO_T class
     *		unsigned min:4;
     *		unsigned max:4;
     *		char *buff;
     *	} SDATA_T;
     *
     *	static const SDATA_T option = { preprocessor, 4, 8, token1 };
     *
     *	RKH_CREATE_BASIC_STATE( S111, set_x_1,
     *							NULL, &S11, preprocessor );
     *	RKH_CREATE_BASIC_STATE( S22, set_x_4,
     *							NULL, &S2, (RKH_PPRO_T*)&option );
     * \endcode
     */
#if RKH_CFG_SMA_PPRO_EN == RKH_ENABLED
    RKH_PPRO_T prepro;
#endif

#if RKH_CFG_SMA_HCAL_EN == RKH_ENABLED
    /**
     *  \brief
     *	Points to state's default child.
     */
    RKHROM void *defchild;

    /**
     *  \brief
     *	Points to state's history.
     */
#if defined(RKH_HISTORY_ENABLED)
    RKHROM struct RKH_SHIST_T *history;
#endif
#endif
} RKH_SCMP_T;

/**
 *  \brief
 *  Describes the exit point connection.
 */
#if defined(RKH_SUBMACHINE_ENABLED)
typedef struct RKH_EXPCN_T
{
    /**
     *  \brief
     *  Points to transition action.
     */
    RKH_TRN_ACT_T action;

    /**
     *  \brief
     *  Points to target state.
     */
    RKHROM void *target;
} RKH_EXPCN_T;

/**
 *  \brief
 *  Describes the entry point connection.
 */
typedef struct RKH_ENPCN_T
{
    /**
     *  \brief
     *  Points to transition action.
     */
    RKH_TRN_ACT_T action;

    /**
     *  \brief
     *  Points to target state.
     */
    RKHROM void *target;
} RKH_ENPCN_T;

/**
 *	\brief
 *  Describes a submachine state.
 *
 *  A submachine state is a kind of a state that actually refers to
 *  another defined state machine.
 *  A submachine state is logically equivalent to the insertion of the
 *  referenced state machine as a composite state in the place of
 *  the submachine state. Consequently, every entrance to a submachine
 *  state is equivalent to the corresponding entrance to the inserted
 *  (referenced) composite state. In particular, it can be entered
 *  thruough its initial pseudostate (as any other composite state), or
 *  through one of its entry points.
 *
 *  Similary, every exit from a submachine state is equivalent to the
 *  corresponding exit from the inserted composite state. It can be exited
 *  through one of its exit points. When it is exited through its exit point
 *  the effect of the transition targeting the exit point is executed first,
 *  followed by the exit behavior of the composite state.
 *
 *  The entry, exit, and behavior actions and internal transitions are
 *  defined as part of the state. Submachine state is a decomposition
 *  mechanism that allows factoring of common behaviors and their reuse.
 *
 *  The purpose od defining submachine states is to decompose and localize
 *  repetitive parts because the same state machine can be referenced from
 *  more than one submachine state.
 *
 *	The diagram in following figure shows a fragment from a state machine
 *	diagram in which a submachine state (the \c SB) is referenced.
 *
 *	\anchor fig_sbm1
 *	\image html sbm1.png "Submachine state"
 *
 *	In the above example, the transition triggered by event \c TWO will
 *	terminate on entry point \c ENS12 of the \c SB state machine.
 *	The \c ONE transition implies taking of the default transition of the
 *	\c SB and executes the \c act5() action. The transition emanating from
 *	the \c EX1S12 exit point of the submachine will execute the \c act1()
 *	behavior in addition to what is executed within the \c SB state machine.
 *	Idem transition emanating from the \c EX2S12.
 *	This transition must have been triggered within the \c SB state machine.
 *	Finally, the transition emanating from the edge of the submachine state
 *	is triggered by event \c THREE.
 *
 *	The following figure is an example of a state machine \c SB defined with
 *	two exit points, \c EXPNT1 and \c EXPNT2, and one entry point \c ENPNT.
 *
 *	\anchor fig_sbm2
 *	\image html sbm2.png "State machine with two exit points and one entry
 *point"
 *
 *	In the following figure the state machine shown above is referenced twice in
 *	a submachine state \c S12 and \c S2.
 *
 *	\anchor fig_sbm3
 *	\image html sbm3.png "Submachine state with usage of exit and entry points"
 */
typedef struct RKH_SSBM_T
{
    RKH_ST_T st;

    /**
     *  \brief
     *	Points to state transition table.
     */
    RKHROM struct RKH_TR_T *trtbl;

    /**
     *  \brief
     *	Points to state transition table.
     */
    RKHROM struct RKH_EXPCN_T *exptbl;

    /**
     *  \brief
     *	Points to submachine object.
     */
    RKHROM struct RKH_RSM_T *sbm;
} RKH_SSBM_T;

/**
 *	\brief
 *  Describes a (referenced) submachine state machine.
 */
typedef struct RKH_RSM_T
{
    /**
     *  \brief
     *	Maintains the basic information of state.
     */
    struct RKH_BASE_T base;

    /**
     *  \brief
     *	Points to state's default child.
     */
    RKHROM void *defchild;

    /**
     *  \brief
     *  Points to initializing action (optional).
     *
     *  The function prototype is defined as RKH_TRN_ACT_T. This argument is
     *  optional, thus it could be declared as NULL.
     */
    RKH_TRN_ACT_T iaction;

    /**
     *  \brief
     *	Points to RAM memory location which stores
     *	the dynamic parent.
     */
    RKHROM struct RKH_ST_T * *dyp;
} RKH_RSM_T;

/**
 *  \brief
 *  Describes the entry point pseudostate.
 *
 *  An entry pseudostate is used to join an external transition terminating
 *  on that entry point to an internal transition emanating from that entry
 *  point.
 *  The main purpose of such entry and exit points is to execute the state
 *  entry and exit actions respectively in between the actions that are
 *  associated with the joined transitions.
 */
typedef struct RKH_SENP_T
{
    /**
     *  \brief
     *	Maintains the basic information of state.
     */
    struct RKH_BASE_T base;

    /**
     *  \brief
     *	Points to entry point connection.
     */
    RKHROM RKH_ENPCN_T *enpcn;

    /**
     *  \brief
     *	Points to state's parent (submachine state).
     */
    RKHROM struct RKH_ST_T *parent;
} RKH_SENP_T;

/**
 *  \brief
 *  Describes the exit point pseudostate.
 *
 *  An exit pseudostate is used to join an internal transition terminating on
 *  that exit point to an external transition emanating from that exit point.
 *  The main purpose of such entry and exit points is to execute the state
 *  entry and exit actions respectively in between the actions that are
 *  associated with the joined transitions.
 */
typedef struct RKH_SEXP_T
{
    /**
     *  \brief
     *	Maintains the basic information of state.
     */
    struct RKH_BASE_T base;

    /**
     *  \brief
     *	Index of exit point table.
     */
    rui8_t ix;

    /**
     *  \brief
     *	Points to state's parent (referenced submachine).
     */
    RKHROM RKH_RSM_T *parent;
} RKH_SEXP_T;
#endif

/**
 *  \brief
 *  Describes the conditional pseudostate.
 */
#if defined(RKH_CHOICE_OR_CONDITIONAL_ENABLED)
typedef struct RKH_SCOND_T
{
    /**
     *  \brief
     *	Maintains the basic information of state.
     */
    struct RKH_BASE_T base;

    /**
     *  \brief
     *	Points to branch table.
     */
    RKHROM struct RKH_TR_T *trtbl;
} RKH_SCOND_T;
#endif

/**
 *  \brief
 *  Describes the choice pseudostate.
 */
#if defined(RKH_CHOICE_ENABLED)
typedef struct RKH_SCHOICE_T
{
    /**
     *  \brief
     *	Maintains the basic information of state.
     */
    struct RKH_BASE_T base;

    /**
     *  \brief
     *	Points to branch table.
     */
    RKHROM struct RKH_TR_T *trtbl;
} RKH_SCHOICE_T;
#endif

/**
 *  \brief
 *  Describes the history pseudostate
 *
 *  It can be either be shallow or deep.
 */
#if defined(RKH_HISTORY_ENABLED)
typedef struct RKH_SHIST_T
{
    /**
     *  \brief
     *	Maintains the basic information of state.
     */
    struct RKH_BASE_T base;

    /**
     *  \brief
     *	Points to state's parent.
     */
    RKHROM RKH_ST_T *parent;

    /**
     *  \brief
     *	Points to RAM memory location which stores
     *	the state's history.
     */
    RKHROM RKH_ST_T * *target;
} RKH_SHIST_T;
#endif

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */

#if (RKH_CFG_SMA_GRD_ARG_EVT_EN == RKH_ENABLED && \
     RKH_CFG_SMA_GRD_ARG_SMA_EN == RKH_ENABLED)
    rbool_t rkh_else(const struct RKH_SMA_T *sma, RKH_EVT_T *pe);
#elif (RKH_CFG_SMA_GRD_ARG_EVT_EN == RKH_ENABLED && \
       RKH_CFG_SMA_GRD_ARG_SMA_EN == RKH_DISABLED)
    rbool_t rkh_else(RKH_EVT_T *pe);
#elif (RKH_CFG_SMA_GRD_ARG_EVT_EN == RKH_DISABLED && \
       RKH_CFG_SMA_GRD_ARG_SMA_EN == RKH_ENABLED)
    rbool_t rkh_else(const struct RKH_SMA_T *sma);
#else
    rbool_t rkh_else(void);
#endif

/* -------------------- External C language linkage end -------------------- */

#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */

#endif

/* ------------------------------ End of file ------------------------------ */
