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
 *  \file       test_sm_runner.c
 *  \ingroup    Test
 *
 *  \brief      ---
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.11.11  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  francuccilea@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */

#include "unity_fixture.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */

TEST_GROUP_RUNNER(trace_filter)
{
	RUN_TEST_CASE(trace_filter, getBitIndex0);
	RUN_TEST_CASE(trace_filter, getBitIndexX);
	RUN_TEST_CASE(trace_filter, setBitIndex0);
	RUN_TEST_CASE(trace_filter, resetBitIndex0);
	RUN_TEST_CASE(trace_filter, setBitIndexX);
	RUN_TEST_CASE(trace_filter, resetBitIndexX);
}

TEST_GROUP_RUNNER(trace)
{
	RUN_TEST_CASE(trace, filEventsAreOnAfterInit);
	RUN_TEST_CASE(trace, turnOffOneFilEvent);
	RUN_TEST_CASE(trace, turnOnOneFilEvent);
	RUN_TEST_CASE(trace, turnOffMultipleFilEvent);
	RUN_TEST_CASE(trace, allOffFilEvent);
	RUN_TEST_CASE(trace, allOnFilEvent);
	RUN_TEST_CASE(trace, isOnOffFilEvent);
}

/* ------------------------------ End of file ------------------------------ */
