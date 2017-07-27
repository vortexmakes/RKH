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
 *  \file       rkhsma_prio.h
 *  \brief      Specifies the native priority mechanism for active object 
 *              scheduling
 *  \ingroup    sma
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.05.15  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __RKHSMA_PRIO_H__
#define __RKHSMA_PRIO_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkhcfg.h"
#include "rkhtype.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/**
 *  \brief
 *  Initializes the native priority mechanism for active object scheduling.
 */
void rkh_smaPrio_init(void);

/**
 *  \brief
 *	Evaluates to true if all active objects are not ready to run.
 */
rbool_t rkh_smaPrio_isNotReady(void);

/**
 *  \brief
 *	Evaluates to true if any active object is ready to run.
 */
rbool_t rkh_smaPrio_isReady(void);

/**
 *  \brief
 *  Making an active object ready-to-run inserting it into the ready list.
 *
 *  The lower 3 bits of the SMA's priority are used to determine the bit
 *  position in rkhrg.tbl[], while the next three most significant bits are
 *  used to determine the index into rkhrg.tbl[].
 *
 *  \param[in] prio     number of active object's priority.
 */
void rkh_smaPrio_setReady(rui8_t prio);

/**
 *  \brief
 *  Removing an active object from the ready list.
 *
 *  Clears the ready bit of the active object in rkhrg.tbl[] and clears the 
 *  bit in rkhrg.grp only if all active objects in a group are not ready to 
 *  run, i.e. all bits in rkhrg.tbl[prio >> 3] are 0.
 *
 *  \param[in] prio		number of active object's priority.
 */
void rkh_smaPrio_setUnready(rui8_t prio);

/**
 *  \brief
 *	Finding the highest priority active object ready to run.
 *
 *	Another table lookup is performed, rather than scanning through the table
 *	starting with rkhrg.tbl[0] to find the highest priority task ready to
 *	run. Eight bits are used to represent when tasks are ready in a group. The 
 *  least significant bit has the highest priority. Using this byte to index 
 *  the table returns the bit position of the highest priority bit set, a 
 *  number between 0 and 7.
 */
rui8_t rkh_smaPrio_findHighest(void);

/* -------------------------------- Constants ------------------------------ */
/* ------------------------------- Data types ------------------------------ */
/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
