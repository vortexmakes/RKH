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
 *  \file       unitrazer.c
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
/* ----------------------------- Include files ----------------------------- */

#include "rkh.h"
#include "unity_fixture.h"
#include "unitrazer.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

/* ============================ Expect functions =========================== */

void
unitrazer_sm_trn_expect(UNITY_LINE_TYPE cmock_line, 
                        const RKH_ST_T *exp_sourceState, 
                        const RKH_ST_T *exp_targetState)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_EXPECT)
    RKH_TRC_UI32(cmock_line);
    RKH_TRC_UI8(RKH_TE_SM_TRN);
    RKH_TRC_SYM(exp_sourceState);
    RKH_TRC_SYM(exp_targetState);
    RKH_TRC_END_WOFIL();
    RKH_TRC_FLUSH();    
}

void
unitrazer_evtProc_expect(UNITY_LINE_TYPE cmock_line)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_EXPECT)
    RKH_TRC_UI32(cmock_line);
    RKH_TRC_UI8(RKH_TE_SM_EVT_PROC);
    RKH_TRC_END_WOFIL();
    RKH_TRC_FLUSH();    
}

/* ... */

/* ======================== Common expect functions ======================== */

void 
unitrazer_init(void)
{
}

void 
unitrazer_cleanup(void)
{
}

void 
unitrazer_verify(void)
{
}

void
unitrazer_expectAnyArgs(UNITY_LINE_TYPE cmock_line, rui8_t trcEvt)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_EXPECT_ANYARGS)
    RKH_TRC_UI32(cmock_line);
    RKH_TRC_TE_ID(trcEvt);
    RKH_TRC_END_WOFIL();
    RKH_TRC_FLUSH();    
}

void
unitrazer_ignore(UNITY_LINE_TYPE cmock_line, rui8_t trcEvt)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_IGNORE)
    RKH_TRC_UI32(cmock_line);
    RKH_TRC_TE_ID(trcEvt);
    RKH_TRC_END_WOFIL();
    RKH_TRC_FLUSH();    
}

void
unitrazer_ignoreArg(UNITY_LINE_TYPE cmock_line, rui8_t trcEvt, rui8_t noArg)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_IGNORE_ARG)
    RKH_TRC_UI32(cmock_line);
    RKH_TRC_TE_ID(trcEvt);
    RKH_TRC_UI8(noArg);
    RKH_TRC_END_WOFIL();
    RKH_TRC_FLUSH();    
}

void 
unitrazer_ignoreGroup(UNITY_LINE_TYPE cmock_line, RKH_TRC_GROUPS group)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_IGNORE_GROUP)
    RKH_TRC_UI32(cmock_line);
    RKH_TRC_UI8(group);
    RKH_TRC_END_WOFIL();
    RKH_TRC_FLUSH();    
}

/* ------------------------------ File footer ------------------------------ */
