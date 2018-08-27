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
 *  \file       test_rkhtrc_filter_runner.c
 *  \ingroup    test_trace
 *
 *  \brief      Test runner of filter module
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.20.04  LeFr  v2.4.05  ---
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
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
TEST_GROUP_RUNNER(toolForTest)
{
	RUN_TEST_CASE(toolForTest, getBitIndex0);
	RUN_TEST_CASE(toolForTest, getBitIndexX);
	RUN_TEST_CASE(toolForTest, setBitIndex0);
	RUN_TEST_CASE(toolForTest, resetBitIndex0);
	RUN_TEST_CASE(toolForTest, setBitIndexX);
	RUN_TEST_CASE(toolForTest, resetBitIndexX);
}

TEST_GROUP_RUNNER(filter)
{
	RUN_TEST_CASE(filter, filEventsAreOnAfterInit);
	RUN_TEST_CASE(filter, turnOffOneFilEvent);
	RUN_TEST_CASE(filter, turnOnOneFilEvent);
	RUN_TEST_CASE(filter, turnOffMultipleFilEvent);
	RUN_TEST_CASE(filter, allOffFilEvent);
	RUN_TEST_CASE(filter, allOnFilEvent);
	RUN_TEST_CASE(filter, isOnOffFilEvent);
    RUN_TEST_CASE(filter, setAllEventsFromOneGroup);
	RUN_TEST_CASE(filter, upperAndLowerBoundsFilEvent);
	RUN_TEST_CASE(filter, outOfBoundsProducesRuntimeError);

	RUN_TEST_CASE(filter, turnOffOneGroup);
	RUN_TEST_CASE(filter, turnOnOneGroup);
	RUN_TEST_CASE(filter, allOnOffGroup);
    RUN_TEST_CASE(filter, turnOnOffMultipleGroups);
    RUN_TEST_CASE(filter, turnOffOneGroupChangedItsEventFilters);

	RUN_TEST_CASE(filter, turnOffOneSymFil);
	RUN_TEST_CASE(filter, turnOnOneSymFil);
	RUN_TEST_CASE(filter, turnOnOffMultipleSymFil);
	RUN_TEST_CASE(filter, allOffOnSymFil);
	RUN_TEST_CASE(filter, isOnOffSymFil);
	RUN_TEST_CASE(filter, upperAndLowerBoundsSymFil);
	RUN_TEST_CASE(filter, outOfBoundsProducesRuntimeErrorSymFil);
}

/* ------------------------------ End of file ------------------------------ */
