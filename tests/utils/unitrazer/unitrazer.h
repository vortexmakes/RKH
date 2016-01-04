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

/* RKH_TE_SM_INIT */
#define unitrazer_sm_init_expect(line, initState) \
    unitrazer_expect_wSymArg(line, RKH_TE_SM_INIT, 1, initState)

#define sm_init_expect(initState) \
    unitrazer_sm_init_expect(__LINE__, initState )

#define sm_init_expectAnyArgs() \
    unitrazer_expectAnyArgs(__LINE__, RKH_TE_SM_INIT)

/* RKH_TE_SM_CLRH */
#define unitrazer_sm_clrh_expect(line, historyState) \
    unitrazer_expect_wSymArg(line, RKH_TE_SM_CLRH, 1, historyState)

#define sm_clrh_expect(historyState) \
    unitrazer_sm_clrh_expect(__LINE__, historyState )

#define sm_clrh_expectAnyArgs() \
    unitrazer_expectAnyArgs(__LINE__, RKH_TE_SM_CLRH)

/* RKH_TE_SM_TRN */
#define unitrazer_sm_trn_expect(line, sourceState, targetState) \
    unitrazer_expect_wSymArg(line, RKH_TE_SM_TRN, 2, sourceState, targetState)

#define sm_trn_expect(sourceState, targetState) \
    unitrazer_sm_trn_expect(__LINE__, sourceState, targetState)

#define sm_trn_expectAnyArgs() \
    unitrazer_expectAnyArgs(__LINE__, RKH_TE_SM_TRN)

/* RKH_TE_SM_STATE */
#define unitrazer_sm_state_expect(line, nextState) \
    unitrazer_expect_wSymArg(line, RKH_TE_SM_STATE, 1, nextState)

#define sm_state_expect(nextState) \
    unitrazer_sm_state_expect(__LINE__, nextState)

#define sm_state_expectAnyArgs() \
    unitrazer_expectAnyArgs(__LINE__, RKH_TE_SM_STATE)

/* RKH_TE_SM_ENSTATE */
#define unitrazer_enstate_expect(line, entryState) \
    unitrazer_expect_wSymArg(line, RKH_TE_SM_ENSTATE, 1, entryState)

#define sm_enstate_expect(entryState) \
    unitrazer_enstate_expect(__LINE__, entryState)

#define sm_enstate_expectAnyArgs() \
    unitrazer_expectAnyArgs(__LINE__, RKH_TE_SM_ENSTATE)

/* RKH_TE_SM_EXSTATE */
#define unitrazer_exstate_expect(line, exitState) \
    unitrazer_expect_wSymArg(line, RKH_TE_SM_EXSTATE, 1, exitState)

#define sm_exstate_expect(exitState) \
    unitrazer_exstate_expect(__LINE__, exitState)

#define sm_exstate_expectAnyArgs() \
    unitrazer_expectAnyArgs(__LINE__, RKH_TE_SM_EXSTATE)

/* RKH_TE_SM_NENEX */
#define unitrazer_sm_nenex_expect(line, nEntry, nExit) \
    unitrazer_expect_wNumArg(line, RKH_TE_SM_NENEX, 2, nEntry, nExit )

#define sm_nenex_expect(nEntry, nExit) \
    unitrazer_sm_nenex_expect(__LINE__, nEntry, nExit)

#define sm_nenex_expectAnyArgs() \
    unitrazer_expectAnyArgs(__LINE__, RKH_TE_SM_NENEX)

/* RKH_TE_SM_NTRNACT */
#define unitrazer_sm_ntrnact_expect(line, nActions, nSegments) \
    unitrazer_expect_wNumArg(line, RKH_TE_SM_NTRNACT, 2, nActions, nSegments)

#define sm_ntrnact_expect(nActions, nSegments) \
    unitrazer_sm_ntrnact_expect(__LINE__, nActions, nSegments)

#define sm_ntrnact_expectAnyArgs() \
    unitrazer_expectAnyArgs(__LINE__, RKH_TE_SM_NTRNACT)

/* RKH_TE_SM_TS_STATE */
#define unitrazer_sm_tsState_expect(line, targetState) \
    unitrazer_expect_wSymArg(line, RKH_TE_SM_TS_STATE, 1, targetState)

#define sm_tsState_expect(targetState) \
    unitrazer_sm_tsState_expect(__LINE__, targetState)

#define sm_tsState_expectAnyArgs() \
    unitrazer_expectAnyArgs(__LINE__, RKH_TE_SM_TS_STATE)

/* RKH_TE_SM_EVT_PROC */
#define unitrazer_sm_evtProc_expect(line) \
    unitrazer_expect_noArgs(line, RKH_TE_SM_EVT_PROC)

#define sm_evtProc_expect() \
    unitrazer_sm_evtProc_expect(__LINE__)

/* RKH_TE_SM_EVT_NFOUND */
#define unitrazer_sm_evtNotFound_expect(line, signal) \
    unitrazer_expect_wSig(line, RKH_TE_SM_EVT_NFOUND, signal)

#define sm_evtNotFound_expect(signal) \
    unitrazer_sm_evtNotFound_expect(__LINE__, signal)

#define sm_evtNotFound_expectAnyArgs() \
    unitrazer_expectAnyArgs(__LINE__, RKH_TE_SM_EVT_NFOUND)

/* RKH_TE_SM_GRD_FALSE */
#define unitrazer_sm_grdFalse_expect(line) \
    unitrazer_expect_noArgs(line, RKH_TE_SM_GRD_FALSE)

#define sm_grdFalse_expect() \
    unitrazer_sm_grdFalse_expect(__LINE__)

/* RKH_TE_SM_CND_NFOUND */
#define unitrazer_sm_cndNotFound_expect(line) \
    unitrazer_expect_noArgs(line, RKH_TE_SM_CND_NFOUND)

#define sm_cndNotFound_expect() \
    unitrazer_sm_cndNotFound_expect(__LINE__)

/* RKH_TE_SM_UNKN_STATE */
#define unitrazer_sm_unknState_expect(line) \
    unitrazer_expect_noArgs(line, RKH_TE_SM_UNKN_STATE)

#define sm_unknState_expect() \
    unitrazer_sm_unknState_expect(__LINE__)

/* RKH_TE_SM_EX_HLEVEL */
#define unitrazer_sm_exHLevel_expect(line) \
    unitrazer_expect_noArgs(line, RKH_TE_SM_EX_HLEVEL)

#define sm_exHLevel_expect() \
    unitrazer_sm_exHLevel_expect(__LINE__)

/* RKH_TE_SM_EX_TSEG */
#define unitrazer_sm_exTSeg_expect(line) \
    unitrazer_expect_noArgs(line, RKH_TE_SM_EX_TSEG)

#define sm_exTSeg_expect() \
    unitrazer_sm_exTSeg_expect(__LINE__)

/* RKH_TE_SM_EXE_ACT */
#define sm_exeAct_expect(actType, state, action) \
    unitrazer_sm_exeAct_expect(__LINE__, actType, state, action)    

#define sm_exeAct_expectAnyArgs() \
    unitrazer_expectAnyArgs(__LINE__, RKH_TE_SM_EXE_ACT)

/* ============================= Ignore macros ============================= */

/* RKH_TE_SM_INIT */
#define sm_init_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_INIT)

/* RKH_TE_SM_CLRH */
#define sm_clrh_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_CLRH)

/* RKH_TE_SM_TRN */
#define sm_trn_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_TRN)

#define sm_trn_ignoreArg_sourceState() \
    unitrazer_ignoreArg(__LINE__, RKH_TE_SM_TRN, UT_ARGNO_1)

#define sm_trn_ignoreArg_targetState() \
    unitrazer_ignoreArg(__LINE__, RKH_TE_SM_TRN, UT_ARGNO_2)

/* RKH_TE_SM_STATE */
#define sm_state_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_STATE)

/* RKH_TE_SM_ENSTATE */
#define sm_enstate_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_ENSTATE)

/* RKH_TE_SM_EXSTATE */
#define sm_exstate_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_EXSTATE)

/* RKH_TE_SM_NENEX */
#define sm_nenex_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_NENEX)

#define sm_nenex_ignoreArg_nEntry() \
    unitrazer_ignoreArg(__LINE__, RKH_TE_SM_NENEX, UT_ARGNO_1)

#define sm_nenex_ignoreArg_nExit() \
    unitrazer_ignoreArg(__LINE__, RKH_TE_SM_NENEX, UT_ARGNO_2)

/* RKH_TE_SM_NTRNACT */
#define sm_ntrnact_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_NTRNACT)

#define sm_ntrnact_ignoreArg_nActions() \
    unitrazer_ignoreArg(__LINE__, RKH_TE_SM_NTRNACT, UT_ARGNO_1)

#define sm_ntrnact_ignoreArg_nSegments() \
    unitrazer_ignoreArg(__LINE__, RKH_TE_SM_NTRNACT, UT_ARGNO_2)

/* RKH_TE_SM_TS_STATE */
#define sm_tsState_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_TS_STATE)

/* RKH_TE_SM_EVT_PROC */
#define sm_evtProc_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_EVT_PROC)

/* RKH_TE_SM_EVT_NFOUND */
#define sm_evtNotFound_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_EVT_NFOUND)

/* RKH_TE_SM_GRD_FALSE */
#define sm_grdFalse_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_GRD_FALSE)

/* RKH_TE_SM_CND_NFOUND */
#define sm_cndNotFound_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_CND_NFOUND)

/* RKH_TE_SM_UNKN_STATE */
#define sm_unknState_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_UNKN_STATE)
    
/* RKH_TE_SM_EX_HLEVEL */
#define sm_exHLevel_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_EX_HLEVEL)
    
/* RKH_TE_SM_EX_TSEG */
#define sm_exTSeg_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_EX_TSEG)

/* RKH_TE_SM_EXE_ACT */
#define sm_exeAct_ignore() \
    unitrazer_ignore(__LINE__, RKH_TE_SM_EXE_ACT)

#define sm_exeAct_ignoreArg_actType() \
    unitrazer_ignoreArg(__LINE__, RKH_TE_SM_EXE_ACT, UT_ARGNO_1)

#define sm_exeAct_ignoreArg_state() \
    unitrazer_ignoreArg(__LINE__, RKH_TE_SM_EXE_ACT, UT_ARGNO_2)

#define sm_exeAct_ignoreArg_action() \
    unitrazer_ignoreArg(__LINE__, RKH_TE_SM_EXE_ACT, UT_ARGNO_3)
    
/* -------------------------------- Ignore Groups--------------------------- */

/* RKH_MP_GROUP */
#define mp_ignore() \
    unitrazer_ignoreGroup(__LINE__, RKH_TG_MP)

/* RKH_SMA_GROUP */
#define sma_ignore() \
    unitrazer_ignoreGroup(__LINE__, RKH_TG_SMA)

/* RKH_FWK_GROUP */
#define fwk_ignore() \
    unitrazer_ignoreGroup(__LINE__, RKH_TG_FWK)

/* RKH_SM_GROUP */
#define sm_ignore() \
    unitrazer_ignoreGroup(__LINE__, RKH_TG_SM)

/* -------------------------------- Constants ------------------------------ */

#define UT_ARGNO_1      (rui8_t)0
#define UT_ARGNO_2      (rui8_t)1
#define UT_ARGNO_3      (rui8_t)2
#define UT_ARGNO_4      (rui8_t)3
#define UT_ARGNO_5      (rui8_t)4
#define UT_ARGNO_6      (rui8_t)5

#define UT_SIZEOF_MSG       256

/* ------------------------------- Data types ------------------------------ */
typedef enum
{
    UT_PROC_SUCCESS, UT_PROC_FAIL, UT_PROC_BUSY, UT_PROC_INIT
} UT_RET_CODE;

typedef struct UtrzProcessOut UtrzProcessOut;

struct UtrzProcessOut
{
	UT_RET_CODE status;			/* result code UT_PROC_SUCCESS/FAIL */
    char msg[UT_SIZEOF_MSG];    /* String terminated in '\0' according to */
                                /* cmock's ruby scripts */
    UNITY_LINE_TYPE line;       /* Line number of expectation */
    /* Another parameters from trazer */
};

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */

UtrzProcessOut * ut_getLastOut(void);
void ut_resetOut(void);

/* ============================ Expect functions =========================== */

/** 
 *  \brief 
 *  Identifies the trace event to expect with one or more arguments.
 *
 *  \param[in] cmockLine    line number from which this function is called
 *  \param[in] trcEvt        trace event to expect
 *  \param[in] nArgs         number of trace event arguments
 *  \param[in] ...           list of arguments
 */
void unitrazer_expect_wSymArg( UNITY_LINE_TYPE cmock_line, 
                            RKH_TRC_EVENTS trace_event, rui8_t nArgs, ... );

/** 
 *  \brief 
 *  Identifies the trace event to expect with one or more arguments.
 *
 *  \param[in] cmockLine    line number from which this function is called
 *  \param[in] trcEvt        trace event to expect
 *  \param[in] nArgs         number of trace event arguments
 *  \param[in] ...           list of arguments
 */
void unitrazer_expect_wNumArg( UNITY_LINE_TYPE cmock_line, 
                            RKH_TRC_EVENTS trace_event, rui8_t nArgs, ... );

/** 
 *  \brief 
 *  Identifies the trace event to expect and one signal argument.
 *
 *  \param[in] cmockLine    line number from which this function is called
 *  \param[in] trcEvt       trace event to expect
 *  \param[in] signal       argument of trace event with signal 
 */
void unitrazer_expect_wSig( UNITY_LINE_TYPE cmockLine, 
                            RKH_TRC_EVENTS trcEvt, RKH_SIG_T signal );

/** 
 *  \brief 
 *  Identifies the trace event to expect without arguments.
 *
 *  \param[in] cmockLine    line number from which this function is called
 *  \param[in] trcEvt       trace event to expect
 */
void unitrazer_expect_noArgs( UNITY_LINE_TYPE cmockLine, 
                                RKH_TRC_EVENTS trcEvt );

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
 *  Expect for RKH_TE_SM_EXE_ACT trace event.
 *
 *  \param[in] cmock_line   line number from which this function is called
 *  \param[in] actType      action type according to RKH_SUBTE_SM_EXE_ACT enum 
 *  \param[in] state        action execution context
 *  \param[in] action       executed action
 */
void unitrazer_sm_exeAct_expect( UNITY_LINE_TYPE cmockLine, 
                            rui8_t actType, RKH_ST_T *state, void * action );

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
