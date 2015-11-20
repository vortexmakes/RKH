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
 *  \file       unitrazer.h
 *  \ingroup    Test
 *
 *  \brief      ---
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */

#ifndef __UNITRAZER_H__
#define __UNITRAZER_H__

/* ----------------------------- Include files ----------------------------- */

#include "unity_fixture.h"
#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */

/* ============================= Expect macros ============================= */

/* RKH_TE_SM_TRN */
#define sm_trn_expect(sourceState, targetState) \
    unitrazer_sm_trn_expect(__LINE__, sourceState, targetState)

#define sm_trn_expectAnyArgs() \
    unitrazer_expectAnyArgs(__LINE__, RKH_TE_SM_TRN)

#define sm_trn_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_TRN)

#define sm_trn_ignoreArg_sourceState() \
    unitrazer_ignoreArg(__LINE__, RKH_TE_SM_TRN, UT_ARGNO_1)

#define sm_trn_ignoreArg_targetState() \
    unitrazer_ignoreArg(__LINE__, RKH_TE_SM_TRN, UT_ARGNO_2)

/* RKH_TE_SM_EVT_PROC */
#define sm_evtProc_expect() \
    unitrazer_sm_evtProc_expect(__LINE__)

#define sm_evtProc_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_EVT_PROC)

/* ... */

#define sm_ignore() \
    unitrazer_ignoreGroup(__LINE__, group)

/* -------------------------------- Constants ------------------------------ */

#define UT_ARGNO_1      (rui8_t)0
#define UT_ARGNO_2      (rui8_t)1
#define UT_ARGNO_3      (rui8_t)2
#define UT_ARGNO_4      (rui8_t)3
#define UT_ARGNO_5      (rui8_t)4
#define UT_ARGNO_6      (rui8_t)5

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */

/* ============================ Expect functions =========================== */

/** 
 *  \brief 
 *  Identifies the RKH_TE_SM_TRN trace event to expect and its arguments.
 *
 *  \param[in] cmock_line       line number from which this function is called
 *  \param[in] exp_sourceState  expected source state of transition
 *  \param[in] exp_targetState  expected target state of transition
 */
void unitrazer_sm_trn_expect(UNITY_LINE_TYPE cmock_line, 
                             const RKH_ST_T *exp_sourceState, 
                             const RKH_ST_T *exp_targetState);

/** 
 *  \brief 
 *  Identifies the RKH_TE_SM_EVT_PROC trace event to expect.
 *
 *  \param[in] cmock_line   line number from which this function is called
 */
void unitrazer_evtProc_expect(UNITY_LINE_TYPE cmock_line);

/* ... */

/* ======================== Common expect functions ======================== */

/** 
 *  \brief 
 *  Establish the preconditions to the tests.
 */
void unitrazer_init(void);

/** 
 *  \brief 
 *  Return the system under test to its initial state after the test.
 */
void unitrazer_cleanup(void);

/** 
 *  \brief 
 *  Makes sure there are no unused expectations, if there are, this function 
 *  causes the test to fail.
 */
void unitrazer_verify(void);

/** 
 *  \brief 
 *  Expect a specific trace event regardless its arguments.
 *
 *  \param[in] cmock_line   line number from which this function is called
 *  \param[in] trcEvt       produced trace event to expect but it ignores its 
 *                          arguments
 */
void unitrazer_expectAnyArgs(UNITY_LINE_TYPE cmock_line, rui8_t trcEvt);

/** 
 *  \brief 
 *  Ignore a specific trace event.
 *
 *  \param[in] cmock_line   line number from which this function is called
 *  \param[in] trcEvt       produced trace event to ignore
 */
void unitrazer_ignore(UNITY_LINE_TYPE cmock_line, rui8_t trcEvt);

/** 
 *  \brief 
 *  Adds the ability to specify specifc arguments to ignore for a produced 
 *  trace event, instead of ignoring all the arguments or the entire generated 
 *  trace event, as the unitrazer_ignore() function supports.
 *
 *  \param[in] cmock_line   line number from which this function is called
 *  \param[in] trcEvt       produced trace event to expect
 *  \param[in] noArg        number of argument to ignore. See UT_ARGNO_<x> 
 *                          macro.
 */
void unitrazer_ignoreArg(UNITY_LINE_TYPE cmock_line, rui8_t trcEvt, 
                         rui8_t noArg);

/** 
 *  \brief 
 *  Force to ignore every produced trace event from a specifc trace group.
 *
 *  \param[in] cmock_line   line number from which this function is called
 *  \param[in] group        group to ignore
 */
void unitrazer_ignoreGroup(UNITY_LINE_TYPE cmock_line, RKH_TRC_GROUPS group);

/* -------------------- External C language linkage end -------------------- */

#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */

#endif

/* ------------------------------ File footer ------------------------------ */
