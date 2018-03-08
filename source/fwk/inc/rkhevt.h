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
 *  \file       rkhevt.h
 *  \brief      Defines event data type and other related macros.
 *  \ingroup    apiEvt
 *
 *  \addtogroup api
 *  @{
 *  \addtogroup apiEvt Events
 *  @{@}
 *  @}
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  LeFr  v2.4.05  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHEVT_H__
#define __RKHEVT_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhtype.h"
#include "rkhcfg.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/**
 *  \brief
 *  Perform cast to pointer to RKH event structure (RKH_EVT_T*).
 *
 *  \ingroup apiEvt
 */
#define RKH_EVT_CAST(_e)      ((RKH_EVT_T *)(_e))

#define RKH_CAST_EVT(e)       ((RKH_EVT_T *)(e))

#if RKH_CFG_FWK_DYN_EVT_EN == RKH_ENABLED
    #define RKH_INC_REF(evt) \
        if (RKH_CAST_EVT(evt)->pool != 0) \
        { \
            ++RKH_CAST_EVT(evt)->nref; \
        }
#else
    #define RKH_INC_REF(evt) \
        (void)0
#endif

/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/**
 *  Defines the size of event. The valid values [in bits] are 8, 16 or 32. 
 *  Default is 8. This type is configurable via the preprocessor switch 
 *  RKH_CFG_FWK_SIZEOF_EVT.
 */
#if RKH_CFG_FWK_SIZEOF_EVT == 8
typedef rui8_t RKH_SIG_T;
#elif RKH_CFG_FWK_SIZEOF_EVT == 16
typedef rui16_t RKH_SIG_T;
#elif RKH_CFG_FWK_SIZEOF_EVT == 32
typedef rui32_t RKH_SIG_T;
#else
typedef rui8_t RKH_SIG_T;
#endif

/**
 *  Defines the data type of event size. The valid values [in bits] are
 *  8, 16 or 32. Default is 8. This type is configurable via the
 *  preprocessor switch RKH_CFG_FWK_SIZEOF_EVT_SIZE.
 */

#if RKH_CFG_FWK_SIZEOF_EVT_SIZE == 8
typedef rui8_t RKH_ES_T;
#elif RKH_CFG_FWK_SIZEOF_EVT_SIZE == 16
typedef rui16_t RKH_ES_T;
#elif RKH_CFG_FWK_SIZEOF_EVT_SIZE == 32
typedef rui32_t RKH_ES_T;
#else
typedef rui8_t RKH_ES_T;
#endif

/**
 *  \brief
 *  Represents events without parameters.
 *
 *  An event can have associated parameters, allowing the event
 *  instance to convey not only the occurrence of some interesting
 *  incident but also quantitative information regarding that occurrence.
 *	Implementing the single inheritance in C is very simply by literally
 *	embedding the base structure, RKH_EVT_T in this case, as the first
 *	member of the derived structure.
 *  For example, the structure MYEVT_T derived from the base structure
 *  RKH_EVT_T by embedding the RKH_EVT_T instance as the first member of
 *	MYEVT_T.
 *
 *  \code
 *  typedef struct
 *  {
 *      RKH_EVT_T evt;	// base structure
 *		int x;			// parameter 'x'
 *		int y;			// parameter 'y'
 *  } MYEVT_T;
 *  \endcode
 *
 *	Such nesting of structures always aligns the data member 'evt' at the
 *	beginning of every instance of the derived structure. In particular, this
 *	alignment lets you treat a pointer to the derived MYEVT_T structure as a
 *	pointer to the RKH_EVT_T base structure. Consequently, you can always
 *	safely pass a pointer to MYEVT_T to any C function that expects a pointer
 *	to RKH_EVT_T. (To be strictly correct in C, you should explicitly cast this
 *	pointer. In OOP such casting is called upcasting and is always safe.)
 *	Therefore, all functions designed for the RKH_EVT_T structure are
 *	automatically available to the MYEVT_T structure as well as other
 *	structures derived from RKH_EVT_T.
 *
 *  \note
 *  The RKH takes the \a 'e' member of RKH_EVT_T structure for triggering a
 *  state transition.
 *
 *  \sa rkh_put_fifo(), rkh_put_lifo(), rkh_alloc_event(),
 *  rkh_set_static_event() and rkh_fwk_gc().
 *
 *  \ingroup apiEvt 
 */

typedef struct RKH_EVT_T
{
    /**
     *  \brief
     *	Signal of the event instance.
     */
    RKH_SIG_T e;

    /**
     *  \brief
     *  Attribute of dynamic events.
     */
    rui8_t nref;

    /**
     *  \brief
     *  Attribute of dynamic events (0 for static event).
     */
    rui8_t pool;
} RKH_EVT_T;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
