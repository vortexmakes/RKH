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
 *  \file       test_smInitialPseudostate_runner.c
 *  \ingroup    test_sm
 *
 *  \brief      Test runner of state machine module
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.02.16  LeFr  v1.0.00  ---
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
TEST_GROUP_RUNNER(InitPseudostate)
{
	RUN_TEST_CASE(InitPseudostate, firstStateAfterInit);
	RUN_TEST_CASE(InitPseudostate, trnToEmptyShHistoryToSimpleState);
	RUN_TEST_CASE(InitPseudostate, trnToLoadedShHistory);
	RUN_TEST_CASE(InitPseudostate, trnToEmptyShHistoryToCmpState);
	RUN_TEST_CASE(InitPseudostate, trnToEmptyShHistoryToNestedSimpleState);
	RUN_TEST_CASE(InitPseudostate, trnToEmptyDeepHistoryToSimpleState);
	RUN_TEST_CASE(InitPseudostate, trnToLoadedDeepHistory);
	RUN_TEST_CASE(InitPseudostate, trnToLoadedDeepHistoryToNestedState);
	RUN_TEST_CASE(InitPseudostate, trnToBranchToSimpleState);
	RUN_TEST_CASE(InitPseudostate, trnToBranchToCmpState);
	RUN_TEST_CASE(InitPseudostate, trnToBranchToNestedCmpState);
	RUN_TEST_CASE(InitPseudostate, trnToBranchToNestedSimpleState);
	RUN_TEST_CASE(InitPseudostate, trnToJunctionToSimpleState);
	RUN_TEST_CASE(InitPseudostate, trnToJunctionToCmpState);
	RUN_TEST_CASE(InitPseudostate, SMInitialToSimpleState);
	RUN_TEST_CASE(InitPseudostate, SMInitialToCmpState);
	RUN_TEST_CASE(InitPseudostate, SMInitialToNestedSimpleState);
	RUN_TEST_CASE(InitPseudostate, SMInitialToNestedCmpState);
	RUN_TEST_CASE(InitPseudostate, SMInitialToJunctionToSimpleState);
	RUN_TEST_CASE(InitPseudostate, SMInitialToJunctionToCmpState);
	RUN_TEST_CASE(InitPseudostate, SMInitialToBranchToSimpleState);
	RUN_TEST_CASE(InitPseudostate, SMInitialToBranchToCmpState);
}

/* ------------------------------ End of file ------------------------------ */
