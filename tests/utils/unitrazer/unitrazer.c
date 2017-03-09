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
unitrazer_expect_wSymArg(UNITY_LINE_TYPE cmockLine, RKH_TE_ID_T trcEvt,
                         rui8_t nArgs, ...)
{
    va_list args;

    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_EXPECT);
    RKH_TRC_UI32(cmockLine);
    RKH_TRC_UI8(trcEvt);
    va_start(args, nArgs);
    while (nArgs--)
    {
        RKH_TRC_SYM(va_arg(args, const void *));
    }
    va_end(args);
    RKH_TRC_END_WOFIL();
}

void
unitrazer_expect_wNumArg(UNITY_LINE_TYPE cmockLine, RKH_TE_ID_T trcEvt,
                         rui8_t nArgs, ...)
{
    va_list args;

    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_EXPECT);
    RKH_TRC_UI32(cmockLine);
    RKH_TRC_UI8(trcEvt);
    va_start(args, nArgs);
    while (nArgs--)
    {
        RKH_TRC_UI8(va_arg(args, rui8_t));
    }
    va_end(args);
    RKH_TRC_END_WOFIL();
}

void
unitrazer_expect_wSig(UNITY_LINE_TYPE cmockLine, RKH_TE_ID_T trcEvt,
                      RKH_SIG_T signal)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_EXPECT);
    RKH_TRC_UI32(cmockLine);
    RKH_TRC_UI8(trcEvt);
    RKH_TRC_SIG(signal);
    RKH_TRC_END_WOFIL();
}

void
unitrazer_expect_noArgs(UNITY_LINE_TYPE cmockLine, RKH_TE_ID_T trcEvt)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_EXPECT)
    RKH_TRC_UI32(cmockLine);
    RKH_TRC_UI8(trcEvt);
    RKH_TRC_END_WOFIL();
}

void
unitrazer_sm_exeAct_expect(UNITY_LINE_TYPE cmockLine,
                           rui8_t actType, RKH_ST_T *state, void * action)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_EXPECT)
    RKH_TRC_UI32(cmockLine);
    RKH_TRC_UI8(RKH_TE_SM_EXE_ACT);
    RKH_TRC_UI8(actType);
    RKH_TRC_SYM(state);
    RKH_TRC_FUN(action);
    RKH_TRC_END_WOFIL();
}

/* ============================ Init function ============================== */

void
unitrazer_init(void)
{
    unitrazer_resetOut();

    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_INIT);
    RKH_TRC_UI32(TEST_LINE_NUM);
    RKH_TRC_END_WOFIL();
}

/* ============================ CleanUp function =========================== */

void
unitrazer_cleanup(void)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_CLEANUP);
    RKH_TRC_UI32(TEST_LINE_NUM);
    RKH_TRC_END_WOFIL();
}

/* ============================ Verify function ============================ */

void
unitrazer_verify(void)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_VERIFY);
    RKH_TRC_UI32(TEST_LINE_NUM);
    RKH_TRC_END_WOFIL();
}

/* ============================ Ignore functions =========================== */

void
unitrazer_ignoreGroup(UNITY_LINE_TYPE cmockLine, RKH_TG_T group)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_IGNORE_GROUP)
    RKH_TRC_UI32(cmockLine);
    RKH_TRC_UI8(group);
    RKH_TRC_END_WOFIL();
}

void
unitrazer_expectAnyArgs(UNITY_LINE_TYPE cmockLine, rui8_t trcEvt)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_EXPECT_ANYARGS)
    RKH_TRC_UI32(cmockLine);
    RKH_TRC_TE_ID(trcEvt);
    RKH_TRC_END_WOFIL();
}

void
unitrazer_ignore(UNITY_LINE_TYPE cmockLine, rui8_t trcEvt)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_IGNORE)
    RKH_TRC_UI32(cmockLine);
    RKH_TRC_TE_ID(trcEvt);
    RKH_TRC_END_WOFIL();
}

void
unitrazer_ignoreArg(UNITY_LINE_TYPE cmockLine, rui8_t trcEvt, rui8_t noArg)
{
    RKH_TRC_BEGIN_WOFIL(RKH_TE_UT_IGNORE_ARG)
    RKH_TRC_UI32(cmockLine);
    RKH_TRC_TE_ID(trcEvt);
    RKH_TRC_UI8(noArg);
    RKH_TRC_END_WOFIL();
}

/* ------------------------------ File footer ------------------------------ */
